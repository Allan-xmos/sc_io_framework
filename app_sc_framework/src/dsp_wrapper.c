// Copyright 2024 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include <print.h>
#include <stdio.h>
#include <string.h>

#include "xua_conf.h"
#include "app_dsp.h"
#include "dsp.h"


void UserBufferManagementInit(unsigned sampFreq)
{
    // printstrln("UserBufferManagementInit");
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
}
