// Copyright 2024 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include <print.h>
#include <stdio.h>
#include <string.h>
#include <platform.h>

#include "app_config.h"
#include "gpio_control_task.h"
#include "neopixel.h"
#include "adc_pot.h"
#include "app_dsp.h"
#include "dsp/adsp.h"

#define VU_GREEN    0x000010
#define VU_RED      0x002000
#define VU_OFF      0x000000


void vu_to_pixels(unsigned levels[2], neopixel_state &np_state){
    for(int i = 0; i < VU_NUM_PIXELS; i++){
        if(levels[0] > i){
            if(i < VU_NUM_PIXELS * 3 / 4){
                np_state.data[i] = VU_GREEN;
            } else {
                np_state.data[i] = VU_RED;
            }
        } else {
            np_state.data[i] = VU_OFF;
        }

        if(levels[1] > i){
            if(i < VU_NUM_PIXELS * 3 / 4){
                np_state.data[(VU_NUM_PIXELS * 2 - 1) - i] = VU_GREEN;
            } else {
                np_state.data[(VU_NUM_PIXELS * 2 - 1) - i] = VU_RED;
            }
        } else {
            np_state.data[(VU_NUM_PIXELS * 2- 1) - i] = VU_OFF;
        }
    }
}


void gpio_control_task( client uart_tx_if i_uart_tx,
                        chanend c_qadc,
                        client interface adsp_control_if i_adsp_control,
                        out buffered port:32 p_neopixel, clock cb_neo,
                        client interface i2c_master_if i_i2c,
                        client input_gpio_if i_gpio_mc_buttons[NUM_BUTTONS],
                        client output_gpio_if i_gpio_mc_leds[NUM_LEDS]
                        ){
    printf("gpio_control_task\n");

    // Neopixel setup
    neopixel_state np_state = {0};
    const unsigned length = VU_NUM_PIXELS * 2;
    neopixel_init(np_state, length, p_neopixel, cb_neo, 3);
    unsigned levels[2];
        

    // UART data
    const uint8_t msg[] = "Hello world!\n";
    unsigned msg_idx = 0;

    // DSP control init
    app_dsp_input_control_t dsp_input = {0};
    dsp_input.game_loopback_switch_pos = 1;
    dsp_input.mic_vol = UNITY_VOLUME;
    dsp_input.mic_mute = 0;
    dsp_input.music_vol = UNITY_VOLUME;
    dsp_input.music_mute = 0;
    dsp_input.monitor_vol = UNITY_VOLUME;
    dsp_input.monitor_mute = 0;
    dsp_input.output_vol = UNITY_VOLUME;
    dsp_input.output_mute = 0;
    dsp_input.reverb_level = 0;
    dsp_input.reverb_enable = 1;
    dsp_input.denoise_enable = 1;
    dsp_input.ducking_enable = 1;

    app_dsp_output_control_t dsp_output = {0};

    // ADC results
    unsigned qadc[NUM_ADC_POTS] = {0};

    // Buttons state
    unsigned button_state_old[3] = {1, 1, 1}; // Active low 
    unsigned button_action[3] = {0, 0, 0}; // Inactive 

    unsigned loop_counter = 0;
    unsigned blinky_state = 0;

    // Main control super loop
    while(1){
        // Read ADCs for slider input
        for(unsigned ch = 0; ch < NUM_ADC_POTS; ch++){
            c_qadc <: (uint32_t)(ADC_CMD_READ | ch);
            c_qadc :> qadc[ch];
        }

        // Convert to volume signals  
        dsp_input.monitor_vol = control_to_volume_setting(qadc[0]);
        dsp_input.output_vol = control_to_volume_setting(qadc[1]);
        // dsp_input.mic_vol = control_to_volume_setting(qadc[2]);
        // dsp_input.music_vol = control_to_volume_setting(qadc[3]);
        // dsp_input.reverb_level = control_to_volume_setting(qadc[4]);

        // Do the control input/output transaction
        dsp_output = i_adsp_control.do_control(dsp_input);

        // Convert envelopes to VU
        levels[0] = envelope_to_vu(dsp_output.headphone_envelope);
        levels[1] = envelope_to_vu(dsp_output.mic_envelope);
        vu_to_pixels(levels, np_state);
        while(!neopixel_drive_pins(np_state, p_neopixel)); // Takes about 1.2 ms for 24 neopixels

        // Read buttons and toggle action flags if pressed
        for(int i = 0; i < NUM_BUTTONS; i++){
            unsigned pb = i_gpio_mc_buttons[i].input();
            if(pb == 0){ // Button pressed
                if(button_state_old[i] == 1){
                    button_action[i] ^= 1; // toggle
                }
            }
            button_state_old[i] = pb;
            i_gpio_mc_leds[NUM_BUTTONS - i - 1].output(button_action[i]); // Mirror LEDs so they line up
        }

        // Blinky LED to show looping
        if(++loop_counter == 10){
            blinky_state ^= 1;
            i_gpio_mc_leds[3].output(blinky_state);
            loop_counter = 0;
        }

        // Set boolean controls from button states
        dsp_input.game_loopback_switch_pos = button_action[0];
        dsp_input.denoise_enable = button_action[1];
        dsp_input.ducking_enable = button_action[2];

        // Send a character to the UART from the string
        i_uart_tx.write(msg[msg_idx]);
        if(++msg_idx == strlen((const char*)msg)){
            msg_idx = 0;
        }

        // Do an I2C access
        // i2c_regop_res_t result;
        // val = i2c.read_reg(I2C_ADDR, REG_NUM, result);

        // Arbitrary rate limit for control loop. Loop time for logic is around 2ms
        delay_milliseconds(10);
    }
}



void gpio_control_slave(server interface adsp_control_if i_adsp_control){
    while(1){
        select{
            case i_adsp_control.do_control(app_dsp_input_control_t dsp_input) -> app_dsp_output_control_t dsp_output:
                app_dsp_do_control(dsp_input, dsp_output);
            break;
        }
    }
}

