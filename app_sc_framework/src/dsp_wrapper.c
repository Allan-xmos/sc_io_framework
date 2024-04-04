// Copyright 2024 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include <print.h>
#include <stdio.h>
#include <string.h>

#include "app_main.h"
#include "xua_conf.h"
#include "dsp_wrapper.h"
#include "app_dsp.h"
#include "dsp.h"


typedef struct vu_state_t{
    int32_t vu;
}vu_state_t;

#define ABS(x) ((x)<0 ? (-x) : (x))


volatile int32_t samples_from_host_g[NUM_USB_CHAN_OUT] = {0};
volatile int32_t samples_to_host_g[NUM_USB_CHAN_IN] = {0};
volatile int32_t output_gain_g[NUM_USB_CHAN_OUT];

void UserBufferManagementInit(unsigned sampFreq)
{
    printstrln("UserBufferManagementInit");
}

void UserBufferManagement(unsigned sampsFromUsbToAudio[], unsigned sampsFromAudioToUsb[]){
    /// From audio_dsp
    int32_t input[NUM_USB_CHAN_OUT + I2S_CHANS_ADC];
    for(int ch=0; ch<NUM_USB_CHAN_OUT; ch++) // From USB
    {
        input[ch] = (int32_t)sampsFromUsbToAudio[ch];
    }
    for(int ch=0; ch<I2S_CHANS_ADC; ch++) // From Audio
    {
        input[ch + NUM_USB_CHAN_OUT] = (int32_t)sampsFromAudioToUsb[ch];
    }

    app_dsp_source(input /*, NUM_USB_CHAN_OUT+NUM_USB_CHAN_IN*/);

    int32_t output[NUM_USB_CHAN_IN + I2S_CHANS_DAC];
    app_dsp_sink(output /*, NUM_USB_CHAN_OUT + NUM_USB_CHAN_IN*/);

    for(int ch=0; ch<NUM_USB_CHAN_IN; ch++) // To Audio
    {
        sampsFromAudioToUsb[ch] = (unsigned)output[ch];
    }
    for(int ch=0; ch<I2S_CHANS_DAC; ch++) // To USB
    {
        sampsFromUsbToAudio[ch] = (unsigned)output[NUM_USB_CHAN_IN + ch];
    }
    /// end from audio_dsp


    for(int i = 0; i < NUM_USB_CHAN_OUT; i++){
        samples_from_host_g[i] = sampsFromUsbToAudio[i];
        // sampsFromUsbToAudio[i] = ((int64_t)samples_from_host_g[i] * (int64_t)output_gain_g[i]) >> 31;
    }
    // chan_out_word(c_dsp_synch_end, 0);
}


// Quick and dirty VU
void process_vu(int32_t *samples, size_t n_ch, vu_state_t vu_state[NUM_USB_CHAN_OUT]){
    for(int ch = 0; ch < n_ch; ch++){
        // Apply decay
        const int32_t decay_constant = (int32_t)((float)((1<<31) - 1) * 0.9890);
        vu_state[ch].vu = ((int64_t)decay_constant * (int64_t)vu_state[ch].vu) >> 31;
        
        // Calc instantaneous approx VU
        uint32_t abs_sample = samples[ch] > 0 ? samples[ch] : - samples[ch];
        uq8_24 abs_sample_uq8_24 = abs_sample >> 7;
        q8_24 log_vu = dsp_math_log(abs_sample_uq8_24 + (1 << 24));

        if(log_vu > vu_state[ch].vu){
            vu_state[ch].vu = log_vu;
        }
    }
}

void dsp_task_1(chanend_t c_dsp, control_input_t *control_input){
    printstr("dsp_task_1\n");
    channel_t c_dsp_synch = chan_alloc();
    // c_dsp_synch_end = c_dsp_synch.end_b;

    vu_state_t vu_state[NUM_USB_CHAN_OUT] = {{0}};


    while(1){
        // Wait until samples have been populated by UserBufferManagement
        chan_in_word(c_dsp_synch.end_a);

        process_vu((int32_t *)samples_from_host_g, NUM_USB_CHAN_OUT, vu_state);

        control_input->vu[0] = vu_state[0].vu;
        control_input->vu[1] = vu_state[1].vu;
        output_gain_g[0] = control_input->output_gain[0];
        output_gain_g[1] = control_input->output_gain[1];

        // Now send them to dsp_task_0 in case we need them for processing on tile[0]
        transacting_chanend_t tc = chan_init_transaction_master(c_dsp);
        t_chan_out_word(&tc, NUM_USB_CHAN_OUT);
        t_chan_out_buf_word(&tc, (uint32_t*)samples_from_host_g, NUM_USB_CHAN_OUT);
        t_chan_in_buf_word(&tc, (uint32_t*)samples_to_host_g, NUM_USB_CHAN_IN);
        c_dsp = chan_complete_transaction(tc);

    }
}



void dsp_task_0(chanend_t c_dsp){
    printstr("dsp_task_0\n");

    int32_t samples_from_host[NUM_USB_CHAN_OUT] = {0};
    int32_t samples_to_host[NUM_USB_CHAN_IN] = {0};

    while(1){
        transacting_chanend_t tc = chan_init_transaction_slave(c_dsp);
        size_t n_ch = t_chan_in_word(&tc);
        t_chan_in_buf_word(&tc, (uint32_t*)samples_from_host, n_ch);
        t_chan_out_buf_word(&tc, (uint32_t*)samples_to_host, n_ch);
        c_dsp = chan_complete_transaction(tc);
    }
}
