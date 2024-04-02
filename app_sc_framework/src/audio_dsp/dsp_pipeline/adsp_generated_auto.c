
#include <stages/adsp_pipeline.h>
#include <xcore/select.h>
#include <xcore/channel.h>
#include <xcore/hwtimer.h>
#include <xcore/thread.h>
#include <print.h>
#include "cmds.h" // Autogenerated
#include "cmd_offsets.h" // Autogenerated
#include <stages/bump_allocator.h>
#include <dsp/signal_chain.h>

// MAX macro
#define _ADSP_MAX(A, B) (((A) > (B)) ? (A) : (B))

#include <stages/pipeline.h>
#include <stages/dsp_thread.h>
#include <stages/adder.h>
#include <stages/adder.h>
#include <stages/volume_control.h>
#include <stages/volume_control.h>
#include <stages/fork.h>
#include <stages/envelope_detector_rms.h>
#include <stages/cascaded_biquads.h>
#include <stages/noise_gate.h>
#include <stages/dsp_thread.h>
#include <stages/fork.h>
#include <stages/compressor_sidechain.h>
#include <stages/compressor_sidechain.h>
#include <stages/fork.h>
#include <stages/adder.h>
#include <stages/adder.h>
#include <stages/switch.h>
#include <stages/switch.h>
#include <stages/volume_control.h>
#include <stages/volume_control.h>
#include <stages/fork.h>
#include <stages/envelope_detector_rms.h>
#include <stages/fork.h>
#include <stages/mixer.h>
#include <pipeline_config.h>
#include <dsp_thread_config.h>
#include <volume_control_config.h>
#include <volume_control_config.h>
#include <envelope_detector_rms_config.h>
#include <cascaded_biquads_config.h>
#include <noise_gate_config.h>
#include <dsp_thread_config.h>
#include <compressor_sidechain_config.h>
#include <compressor_sidechain_config.h>
#include <switch_config.h>
#include <switch_config.h>
#include <volume_control_config.h>
#include <volume_control_config.h>
#include <envelope_detector_rms_config.h>
#include <mixer_config.h>
DECLARE_JOB(dsp_auto_thread0, (chanend_t*, chanend_t*, module_instance_t**));
void dsp_auto_thread0(chanend_t* c_source, chanend_t* c_dest, module_instance_t** modules) {
	local_thread_mode_set_bits(thread_mode_high_priority);	int32_t edge0[1] = {0};
	int32_t edge1[1] = {0};
	int32_t edge2[1] = {0};
	int32_t edge3[1] = {0};
	int32_t edge4[1] = {0};
	int32_t edge5[1] = {0};
	int32_t edge6[1] = {0};
	int32_t edge7[1] = {0};
	int32_t edge8[1] = {0};
	int32_t edge9[1] = {0};
	int32_t edge10[1] = {0};
	int32_t edge11[1] = {0};
	int32_t edge12[1] = {0};
	int32_t edge13[1] = {0};
	int32_t* stage_2_input[] = {edge0, edge2};
	int32_t* stage_2_output[] = {edge5};
	int32_t* stage_3_input[] = {edge1, edge3};
	int32_t* stage_3_output[] = {edge6};
	int32_t* stage_4_input[] = {edge4};
	int32_t* stage_4_output[] = {edge7};
	int32_t* stage_5_input[] = {edge5, edge6};
	int32_t* stage_5_output[] = {edge11, edge12};
	int32_t* stage_6_input[] = {edge7};
	int32_t* stage_6_output[] = {edge8, edge9};
	int32_t* stage_7_input[] = {edge9};
	int32_t** stage_7_output = NULL;
	int32_t* stage_8_input[] = {edge8};
	int32_t* stage_8_output[] = {edge10};
	int32_t* stage_9_input[] = {edge10};
	int32_t* stage_9_output[] = {edge13};
	uint32_t start_ts, end_ts, start_control_ts, control_ticks;
	bool control_done;
	while(1) {
	control_done = false;
	int read_count = 1;
	SELECT_RES(
		CASE_THEN(c_source[0], case_0),
		DEFAULT_THEN(do_control)
	) {
		case_0: {
			for(int idx = 0; idx < 1; ++idx) edge0[idx] = adsp_from_q31((int32_t)chan_in_word(c_source[0]));
			for(int idx = 0; idx < 1; ++idx) edge1[idx] = adsp_from_q31((int32_t)chan_in_word(c_source[0]));
			for(int idx = 0; idx < 1; ++idx) edge2[idx] = adsp_from_q31((int32_t)chan_in_word(c_source[0]));
			for(int idx = 0; idx < 1; ++idx) edge3[idx] = adsp_from_q31((int32_t)chan_in_word(c_source[0]));
			for(int idx = 0; idx < 1; ++idx) edge4[idx] = adsp_from_q31((int32_t)chan_in_word(c_source[0]));
			if(!--read_count) break;
			else continue;
		}
		do_control: {
		start_control_ts = get_reference_time();
		pipeline_control(modules[0]->state, &modules[0]->control);
		dsp_thread_control(modules[1]->state, &modules[1]->control);
		volume_control_control(modules[4]->state, &modules[4]->control);
		volume_control_control(modules[5]->state, &modules[5]->control);
		envelope_detector_rms_control(modules[7]->state, &modules[7]->control);
		cascaded_biquads_control(modules[8]->state, &modules[8]->control);
		noise_gate_control(modules[9]->state, &modules[9]->control);
		control_done = true;
		control_ticks = get_reference_time() - start_control_ts;
		continue; }
	}
	if(!control_done){
		start_control_ts = get_reference_time();
		pipeline_control(modules[0]->state, &modules[0]->control);
		dsp_thread_control(modules[1]->state, &modules[1]->control);
		volume_control_control(modules[4]->state, &modules[4]->control);
		volume_control_control(modules[5]->state, &modules[5]->control);
		envelope_detector_rms_control(modules[7]->state, &modules[7]->control);
		cascaded_biquads_control(modules[8]->state, &modules[8]->control);
		noise_gate_control(modules[9]->state, &modules[9]->control);
		control_ticks = get_reference_time() - start_control_ts;
	}
	start_ts = get_reference_time();

	adder_process(
		stage_2_input,
		stage_2_output,
		modules[2]->state);
	adder_process(
		stage_3_input,
		stage_3_output,
		modules[3]->state);
	volume_control_process(
		stage_4_input,
		stage_4_output,
		modules[4]->state);
	volume_control_process(
		stage_5_input,
		stage_5_output,
		modules[5]->state);
	fork_process(
		stage_6_input,
		stage_6_output,
		modules[6]->state);
	envelope_detector_rms_process(
		stage_7_input,
		stage_7_output,
		modules[7]->state);
	cascaded_biquads_process(
		stage_8_input,
		stage_8_output,
		modules[8]->state);
	noise_gate_process(
		stage_9_input,
		stage_9_output,
		modules[9]->state);

	end_ts = get_reference_time();
	uint32_t process_plus_control_ticks = (end_ts - start_ts) + control_ticks;
	if(process_plus_control_ticks > ((dsp_thread_state_t*)(modules[1]->state))->max_cycles)
	{
		((dsp_thread_state_t*)(modules[1]->state))->max_cycles = process_plus_control_ticks;
	}
	chan_out_buf_word(c_dest[0], (void*)edge11, 1);
	chan_out_buf_word(c_dest[0], (void*)edge12, 1);
	chan_out_buf_word(c_dest[0], (void*)edge13, 1);
	}
}
DECLARE_JOB(dsp_auto_thread1, (chanend_t*, chanend_t*, module_instance_t**));
void dsp_auto_thread1(chanend_t* c_source, chanend_t* c_dest, module_instance_t** modules) {
	local_thread_mode_set_bits(thread_mode_high_priority);	int32_t edge0[1] = {0};
	int32_t edge1[1] = {0};
	int32_t edge2[1] = {0};
	int32_t edge3[1] = {0};
	int32_t edge4[1] = {0};
	int32_t edge5[1] = {0};
	int32_t edge6[1] = {0};
	int32_t edge7[1] = {0};
	int32_t edge8[1] = {0};
	int32_t edge9[1] = {0};
	int32_t edge10[1] = {0};
	int32_t edge11[1] = {0};
	int32_t edge12[1] = {0};
	int32_t edge13[1] = {0};
	int32_t edge14[1] = {0};
	int32_t edge15[1] = {0};
	int32_t edge16[1] = {0};
	int32_t edge17[1] = {0};
	int32_t edge18[1] = {0};
	int32_t edge19[1] = {0};
	int32_t edge20[1] = {0};
	int32_t edge21[1] = {0};
	int32_t edge22[1] = {0};
	int32_t edge23[1] = {0};
	int32_t edge24[1] = {0};
	int32_t edge25[1] = {0};
	int32_t edge26[1] = {0};
	int32_t edge27[1] = {0};
	int32_t edge28[1] = {0};
	int32_t edge29[1] = {0};
	int32_t* stage_1_input[] = {edge2};
	int32_t* stage_1_output[] = {edge3, edge4, edge5, edge6, edge7, edge8};
	int32_t* stage_2_input[] = {edge0, edge3};
	int32_t* stage_2_output[] = {edge9};
	int32_t* stage_3_input[] = {edge1, edge4};
	int32_t* stage_3_output[] = {edge10};
	int32_t* stage_4_input[] = {edge9, edge10};
	int32_t* stage_4_output[] = {edge11, edge12, edge13, edge14};
	int32_t* stage_5_input[] = {edge12, edge5};
	int32_t* stage_5_output[] = {edge15};
	int32_t* stage_6_input[] = {edge14, edge6};
	int32_t* stage_6_output[] = {edge16};
	int32_t* stage_7_input[] = {edge11, edge13};
	int32_t* stage_7_output[] = {edge19, edge25};
	int32_t* stage_8_input[] = {edge7, edge15};
	int32_t* stage_8_output[] = {edge17};
	int32_t* stage_9_input[] = {edge8, edge16};
	int32_t* stage_9_output[] = {edge18};
	int32_t* stage_10_input[] = {edge19};
	int32_t* stage_10_output[] = {edge26, edge22};
	int32_t* stage_11_input[] = {edge17, edge18};
	int32_t* stage_11_output[] = {edge20, edge21};
	int32_t* stage_12_input[] = {edge22};
	int32_t** stage_12_output = NULL;
	int32_t* stage_13_input[] = {edge20, edge21};
	int32_t* stage_13_output[] = {edge27, edge23, edge28, edge24};
	int32_t* stage_14_input[] = {edge23, edge24};
	int32_t* stage_14_output[] = {edge29};
	uint32_t start_ts, end_ts, start_control_ts, control_ticks;
	bool control_done;
	while(1) {
	control_done = false;
	for(int idx = 0; idx < 1; ++idx) chan_out_word(c_dest[0], adsp_to_q31(edge25[idx]));
	for(int idx = 0; idx < 1; ++idx) chan_out_word(c_dest[0], adsp_to_q31(edge26[idx]));
	for(int idx = 0; idx < 1; ++idx) chan_out_word(c_dest[0], adsp_to_q31(edge27[idx]));
	for(int idx = 0; idx < 1; ++idx) chan_out_word(c_dest[0], adsp_to_q31(edge28[idx]));
	for(int idx = 0; idx < 1; ++idx) chan_out_word(c_dest[0], adsp_to_q31(edge29[idx]));
	int read_count = 1;
	SELECT_RES(
		CASE_THEN(c_source[0], case_0),
		DEFAULT_THEN(do_control)
	) {
		case_0: {
			chan_in_buf_word(c_source[0], (void*)edge0, 1);
			chan_in_buf_word(c_source[0], (void*)edge1, 1);
			chan_in_buf_word(c_source[0], (void*)edge2, 1);
			if(!--read_count) break;
			else continue;
		}
		do_control: {
		start_control_ts = get_reference_time();
		dsp_thread_control(modules[0]->state, &modules[0]->control);
		compressor_sidechain_control(modules[2]->state, &modules[2]->control);
		compressor_sidechain_control(modules[3]->state, &modules[3]->control);
		volume_control_control(modules[7]->state, &modules[7]->control);
		switch_control(modules[8]->state, &modules[8]->control);
		switch_control(modules[9]->state, &modules[9]->control);
		volume_control_control(modules[11]->state, &modules[11]->control);
		envelope_detector_rms_control(modules[12]->state, &modules[12]->control);
		mixer_control(modules[14]->state, &modules[14]->control);
		control_done = true;
		control_ticks = get_reference_time() - start_control_ts;
		continue; }
	}
	if(!control_done){
		start_control_ts = get_reference_time();
		dsp_thread_control(modules[0]->state, &modules[0]->control);
		compressor_sidechain_control(modules[2]->state, &modules[2]->control);
		compressor_sidechain_control(modules[3]->state, &modules[3]->control);
		volume_control_control(modules[7]->state, &modules[7]->control);
		switch_control(modules[8]->state, &modules[8]->control);
		switch_control(modules[9]->state, &modules[9]->control);
		volume_control_control(modules[11]->state, &modules[11]->control);
		envelope_detector_rms_control(modules[12]->state, &modules[12]->control);
		mixer_control(modules[14]->state, &modules[14]->control);
		control_ticks = get_reference_time() - start_control_ts;
	}
	start_ts = get_reference_time();

	fork_process(
		stage_1_input,
		stage_1_output,
		modules[1]->state);
	compressor_sidechain_process(
		stage_2_input,
		stage_2_output,
		modules[2]->state);
	compressor_sidechain_process(
		stage_3_input,
		stage_3_output,
		modules[3]->state);
	fork_process(
		stage_4_input,
		stage_4_output,
		modules[4]->state);
	adder_process(
		stage_5_input,
		stage_5_output,
		modules[5]->state);
	adder_process(
		stage_6_input,
		stage_6_output,
		modules[6]->state);
	volume_control_process(
		stage_7_input,
		stage_7_output,
		modules[7]->state);
	switch_process(
		stage_8_input,
		stage_8_output,
		modules[8]->state);
	switch_process(
		stage_9_input,
		stage_9_output,
		modules[9]->state);
	fork_process(
		stage_10_input,
		stage_10_output,
		modules[10]->state);
	volume_control_process(
		stage_11_input,
		stage_11_output,
		modules[11]->state);
	envelope_detector_rms_process(
		stage_12_input,
		stage_12_output,
		modules[12]->state);
	fork_process(
		stage_13_input,
		stage_13_output,
		modules[13]->state);
	mixer_process(
		stage_14_input,
		stage_14_output,
		modules[14]->state);

	end_ts = get_reference_time();
	uint32_t process_plus_control_ticks = (end_ts - start_ts) + control_ticks;
	if(process_plus_control_ticks > ((dsp_thread_state_t*)(modules[0]->state))->max_cycles)
	{
		((dsp_thread_state_t*)(modules[0]->state))->max_cycles = process_plus_control_ticks;
	}
	}
}
adsp_pipeline_t * adsp_auto_pipeline_init() {
	static adsp_pipeline_t adsp_auto;

	static channel_t adsp_auto_in_chans[1];
	static channel_t adsp_auto_out_chans[1];
	static channel_t adsp_auto_link_chans[1];
	static module_instance_t adsp_auto_modules[25];
	static adsp_mux_elem_t adsp_auto_in_mux_cfgs[] = {
		{ .channel_idx = 0, .data_idx = 0, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 1, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 2, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 3, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 4, .frame_size = 1},
	};
	static adsp_mux_elem_t adsp_auto_out_mux_cfgs[] = {
		{ .channel_idx = 0, .data_idx = 3, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 2, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 0, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 1, .frame_size = 1},
		{ .channel_idx = 0, .data_idx = 4, .frame_size = 1},
	};
	adsp_auto.input_mux.n_chan = 5;
	adsp_auto.input_mux.chan_cfg = (adsp_mux_elem_t *) adsp_auto_in_mux_cfgs;
	adsp_auto.output_mux.n_chan = 5;
	adsp_auto.output_mux.chan_cfg = (adsp_mux_elem_t *) adsp_auto_out_mux_cfgs;
	adsp_auto_in_chans[0] = chan_alloc();
	adsp_auto_out_chans[0] = chan_alloc();
	adsp_auto_link_chans[0] = chan_alloc();
	adsp_auto.p_in = (channel_t *) adsp_auto_in_chans;
	adsp_auto.n_in = 1;
	adsp_auto.p_out = (channel_t *) adsp_auto_out_chans;
	adsp_auto.n_out = 1;
	adsp_auto.p_link = (channel_t *) adsp_auto_link_chans;
	adsp_auto.n_link = 1;
	adsp_auto.modules = adsp_auto_modules;
	adsp_auto.n_modules = 25;
	static pipeline_config_t config0 = { .checksum = {28, 90, 0, 69, 70, 105, 179, 92, 210, 124, 231, 249, 187, 87, 65, 11} };

            static pipeline_state_t state0;
            static uint8_t memory0[_ADSP_MAX(1, PIPELINE_REQUIRED_MEMORY(0, 0, 1))];
            static adsp_bump_allocator_t allocator0 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory0);

            adsp_auto.modules[0].state = (void*)&state0;

            // Control stuff
            adsp_auto.modules[0].control.id = 0;
            adsp_auto.modules[0].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[0].control.config = (void*)&config0;
                adsp_auto.modules[0].control.module_type = e_dsp_stage_pipeline;
                adsp_auto.modules[0].control.num_control_commands = NUM_CMDS_PIPELINE;
                pipeline_init(&adsp_auto.modules[0], &allocator0, 0, 0, 0, 1);
	static dsp_thread_config_t config1 = {  };

            static dsp_thread_state_t state1;
            static uint8_t memory1[_ADSP_MAX(1, DSP_THREAD_REQUIRED_MEMORY(0, 0, 1))];
            static adsp_bump_allocator_t allocator1 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory1);

            adsp_auto.modules[1].state = (void*)&state1;

            // Control stuff
            adsp_auto.modules[1].control.id = 1;
            adsp_auto.modules[1].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[1].control.config = (void*)&config1;
                adsp_auto.modules[1].control.module_type = e_dsp_stage_dsp_thread;
                adsp_auto.modules[1].control.num_control_commands = NUM_CMDS_DSP_THREAD;
                dsp_thread_init(&adsp_auto.modules[1], &allocator1, 1, 0, 0, 1);

            static adder_state_t state2;
            static uint8_t memory2[_ADSP_MAX(1, ADDER_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator2 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory2);

            adsp_auto.modules[2].state = (void*)&state2;

            // Control stuff
            adsp_auto.modules[2].control.id = 2;
            adsp_auto.modules[2].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[2].control.config = NULL;
                adsp_auto.modules[2].control.num_control_commands = 0;
                adder_init(&adsp_auto.modules[2], &allocator2, 2, 2, 1, 1);

            static adder_state_t state3;
            static uint8_t memory3[_ADSP_MAX(1, ADDER_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator3 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory3);

            adsp_auto.modules[3].state = (void*)&state3;

            // Control stuff
            adsp_auto.modules[3].control.id = 3;
            adsp_auto.modules[3].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[3].control.config = NULL;
                adsp_auto.modules[3].control.num_control_commands = 0;
                adder_init(&adsp_auto.modules[3], &allocator3, 3, 2, 1, 1);
	static volume_control_config_t config4 = { .target_gain = 134217728, .slew_shift = 7, .mute = 0 };

            static volume_control_state_t state4;
            static uint8_t memory4[_ADSP_MAX(1, VOLUME_CONTROL_REQUIRED_MEMORY(1, 1, 1))];
            static adsp_bump_allocator_t allocator4 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory4);

            adsp_auto.modules[4].state = (void*)&state4;

            // Control stuff
            adsp_auto.modules[4].control.id = 4;
            adsp_auto.modules[4].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[4].control.config = (void*)&config4;
                adsp_auto.modules[4].control.module_type = e_dsp_stage_volume_control;
                adsp_auto.modules[4].control.num_control_commands = NUM_CMDS_VOLUME_CONTROL;
                volume_control_init(&adsp_auto.modules[4], &allocator4, 4, 1, 1, 1);
	static volume_control_config_t config5 = { .target_gain = 134217728, .slew_shift = 7, .mute = 0 };

            static volume_control_state_t state5;
            static uint8_t memory5[_ADSP_MAX(1, VOLUME_CONTROL_REQUIRED_MEMORY(2, 2, 1))];
            static adsp_bump_allocator_t allocator5 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory5);

            adsp_auto.modules[5].state = (void*)&state5;

            // Control stuff
            adsp_auto.modules[5].control.id = 5;
            adsp_auto.modules[5].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[5].control.config = (void*)&config5;
                adsp_auto.modules[5].control.module_type = e_dsp_stage_volume_control;
                adsp_auto.modules[5].control.num_control_commands = NUM_CMDS_VOLUME_CONTROL;
                volume_control_init(&adsp_auto.modules[5], &allocator5, 5, 2, 2, 1);

            static fork_state_t state6;
            static uint8_t memory6[_ADSP_MAX(1, FORK_REQUIRED_MEMORY(1, 2, 1))];
            static adsp_bump_allocator_t allocator6 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory6);

            adsp_auto.modules[6].state = (void*)&state6;

            // Control stuff
            adsp_auto.modules[6].control.id = 6;
            adsp_auto.modules[6].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[6].control.config = NULL;
                adsp_auto.modules[6].control.num_control_commands = 0;
                fork_init(&adsp_auto.modules[6], &allocator6, 6, 1, 2, 1);
	static envelope_detector_rms_config_t config7 = { .attack_alpha = 298262, .release_alpha = 298262 };

            static envelope_detector_rms_state_t state7;
            static uint8_t memory7[_ADSP_MAX(1, ENVELOPE_DETECTOR_RMS_REQUIRED_MEMORY(1, 0, 1))];
            static adsp_bump_allocator_t allocator7 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory7);

            adsp_auto.modules[7].state = (void*)&state7;

            // Control stuff
            adsp_auto.modules[7].control.id = 7;
            adsp_auto.modules[7].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[7].control.config = (void*)&config7;
                adsp_auto.modules[7].control.module_type = e_dsp_stage_envelope_detector_rms;
                adsp_auto.modules[7].control.num_control_commands = NUM_CMDS_ENVELOPE_DETECTOR_RMS;
                envelope_detector_rms_init(&adsp_auto.modules[7], &allocator7, 7, 1, 0, 1);
	static cascaded_biquads_config_t config8 = { .left_shift = {0, 0, 0, 0, 0, 0, 0, 0}, .filter_coeffs = {1068783281, -2137566562, 1068783281, 2137543670, -1063847630, 1073741824, 0, 0, 0, 0, 1073741824, 0, 0, 0, 0, 1073741824, 0, 0, 0, 0, 1073741824, 0, 0, 0, 0, 1073741824, 0, 0, 0, 0, 1073741824, 0, 0, 0, 0, 1073741824, 0, 0, 0, 0} };

            static cascaded_biquads_state_t state8;
            static uint8_t memory8[_ADSP_MAX(1, CASCADED_BIQUADS_REQUIRED_MEMORY(1, 1, 1))];
            static adsp_bump_allocator_t allocator8 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory8);

            adsp_auto.modules[8].state = (void*)&state8;

            // Control stuff
            adsp_auto.modules[8].control.id = 8;
            adsp_auto.modules[8].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[8].control.config = (void*)&config8;
                adsp_auto.modules[8].control.module_type = e_dsp_stage_cascaded_biquads;
                adsp_auto.modules[8].control.num_control_commands = NUM_CMDS_CASCADED_BIQUADS;
                cascaded_biquads_init(&adsp_auto.modules[8], &allocator8, 8, 1, 1, 1);
	static noise_gate_config_t config9 = { .attack_alpha = 17895697, .release_alpha = 745654, .threshold = 4244337 };

            static noise_gate_state_t state9;
            static uint8_t memory9[_ADSP_MAX(1, NOISE_GATE_REQUIRED_MEMORY(1, 1, 1))];
            static adsp_bump_allocator_t allocator9 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory9);

            adsp_auto.modules[9].state = (void*)&state9;

            // Control stuff
            adsp_auto.modules[9].control.id = 9;
            adsp_auto.modules[9].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[9].control.config = (void*)&config9;
                adsp_auto.modules[9].control.module_type = e_dsp_stage_noise_gate;
                adsp_auto.modules[9].control.num_control_commands = NUM_CMDS_NOISE_GATE;
                noise_gate_init(&adsp_auto.modules[9], &allocator9, 9, 1, 1, 1);
	static dsp_thread_config_t config10 = {  };

            static dsp_thread_state_t state10;
            static uint8_t memory10[_ADSP_MAX(1, DSP_THREAD_REQUIRED_MEMORY(0, 0, 1))];
            static adsp_bump_allocator_t allocator10 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory10);

            adsp_auto.modules[10].state = (void*)&state10;

            // Control stuff
            adsp_auto.modules[10].control.id = 10;
            adsp_auto.modules[10].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[10].control.config = (void*)&config10;
                adsp_auto.modules[10].control.module_type = e_dsp_stage_dsp_thread;
                adsp_auto.modules[10].control.num_control_commands = NUM_CMDS_DSP_THREAD;
                dsp_thread_init(&adsp_auto.modules[10], &allocator10, 10, 0, 0, 1);

            static fork_state_t state11;
            static uint8_t memory11[_ADSP_MAX(1, FORK_REQUIRED_MEMORY(1, 6, 1))];
            static adsp_bump_allocator_t allocator11 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory11);

            adsp_auto.modules[11].state = (void*)&state11;

            // Control stuff
            adsp_auto.modules[11].control.id = 11;
            adsp_auto.modules[11].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[11].control.config = NULL;
                adsp_auto.modules[11].control.num_control_commands = 0;
                fork_init(&adsp_auto.modules[11], &allocator11, 11, 1, 6, 1);
	static compressor_sidechain_config_t config12 = { .attack_alpha = 8947849, .release_alpha = 178957, .threshold = 134217, .slope = 0.4 };

            static compressor_sidechain_state_t state12;
            static uint8_t memory12[_ADSP_MAX(1, COMPRESSOR_SIDECHAIN_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator12 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory12);

            adsp_auto.modules[12].state = (void*)&state12;

            // Control stuff
            adsp_auto.modules[12].control.id = 12;
            adsp_auto.modules[12].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[12].control.config = (void*)&config12;
                adsp_auto.modules[12].control.module_type = e_dsp_stage_compressor_sidechain;
                adsp_auto.modules[12].control.num_control_commands = NUM_CMDS_COMPRESSOR_SIDECHAIN;
                compressor_sidechain_init(&adsp_auto.modules[12], &allocator12, 12, 2, 1, 1);
	static compressor_sidechain_config_t config13 = { .attack_alpha = 8947849, .release_alpha = 178957, .threshold = 134217, .slope = 0.4 };

            static compressor_sidechain_state_t state13;
            static uint8_t memory13[_ADSP_MAX(1, COMPRESSOR_SIDECHAIN_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator13 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory13);

            adsp_auto.modules[13].state = (void*)&state13;

            // Control stuff
            adsp_auto.modules[13].control.id = 13;
            adsp_auto.modules[13].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[13].control.config = (void*)&config13;
                adsp_auto.modules[13].control.module_type = e_dsp_stage_compressor_sidechain;
                adsp_auto.modules[13].control.num_control_commands = NUM_CMDS_COMPRESSOR_SIDECHAIN;
                compressor_sidechain_init(&adsp_auto.modules[13], &allocator13, 13, 2, 1, 1);

            static fork_state_t state14;
            static uint8_t memory14[_ADSP_MAX(1, FORK_REQUIRED_MEMORY(2, 4, 1))];
            static adsp_bump_allocator_t allocator14 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory14);

            adsp_auto.modules[14].state = (void*)&state14;

            // Control stuff
            adsp_auto.modules[14].control.id = 14;
            adsp_auto.modules[14].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[14].control.config = NULL;
                adsp_auto.modules[14].control.num_control_commands = 0;
                fork_init(&adsp_auto.modules[14], &allocator14, 14, 2, 4, 1);

            static adder_state_t state15;
            static uint8_t memory15[_ADSP_MAX(1, ADDER_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator15 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory15);

            adsp_auto.modules[15].state = (void*)&state15;

            // Control stuff
            adsp_auto.modules[15].control.id = 15;
            adsp_auto.modules[15].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[15].control.config = NULL;
                adsp_auto.modules[15].control.num_control_commands = 0;
                adder_init(&adsp_auto.modules[15], &allocator15, 15, 2, 1, 1);

            static adder_state_t state16;
            static uint8_t memory16[_ADSP_MAX(1, ADDER_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator16 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory16);

            adsp_auto.modules[16].state = (void*)&state16;

            // Control stuff
            adsp_auto.modules[16].control.id = 16;
            adsp_auto.modules[16].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[16].control.config = NULL;
                adsp_auto.modules[16].control.num_control_commands = 0;
                adder_init(&adsp_auto.modules[16], &allocator16, 16, 2, 1, 1);
	static volume_control_config_t config19 = { .target_gain = 134217728, .slew_shift = 7, .mute = 0 };

            static volume_control_state_t state19;
            static uint8_t memory19[_ADSP_MAX(1, VOLUME_CONTROL_REQUIRED_MEMORY(2, 2, 1))];
            static adsp_bump_allocator_t allocator19 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory19);

            adsp_auto.modules[19].state = (void*)&state19;

            // Control stuff
            adsp_auto.modules[19].control.id = 19;
            adsp_auto.modules[19].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[19].control.config = (void*)&config19;
                adsp_auto.modules[19].control.module_type = e_dsp_stage_volume_control;
                adsp_auto.modules[19].control.num_control_commands = NUM_CMDS_VOLUME_CONTROL;
                volume_control_init(&adsp_auto.modules[19], &allocator19, 19, 2, 2, 1);
	static switch_config_t config17 = { .position = 1 };

            static switch_state_t state17;
            static uint8_t memory17[_ADSP_MAX(1, SWITCH_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator17 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory17);

            adsp_auto.modules[17].state = (void*)&state17;

            // Control stuff
            adsp_auto.modules[17].control.id = 17;
            adsp_auto.modules[17].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[17].control.config = (void*)&config17;
                adsp_auto.modules[17].control.module_type = e_dsp_stage_switch;
                adsp_auto.modules[17].control.num_control_commands = NUM_CMDS_SWITCH;
                switch_init(&adsp_auto.modules[17], &allocator17, 17, 2, 1, 1);
	static switch_config_t config18 = { .position = 1 };

            static switch_state_t state18;
            static uint8_t memory18[_ADSP_MAX(1, SWITCH_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator18 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory18);

            adsp_auto.modules[18].state = (void*)&state18;

            // Control stuff
            adsp_auto.modules[18].control.id = 18;
            adsp_auto.modules[18].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[18].control.config = (void*)&config18;
                adsp_auto.modules[18].control.module_type = e_dsp_stage_switch;
                adsp_auto.modules[18].control.num_control_commands = NUM_CMDS_SWITCH;
                switch_init(&adsp_auto.modules[18], &allocator18, 18, 2, 1, 1);

            static fork_state_t state21;
            static uint8_t memory21[_ADSP_MAX(1, FORK_REQUIRED_MEMORY(1, 2, 1))];
            static adsp_bump_allocator_t allocator21 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory21);

            adsp_auto.modules[21].state = (void*)&state21;

            // Control stuff
            adsp_auto.modules[21].control.id = 21;
            adsp_auto.modules[21].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[21].control.config = NULL;
                adsp_auto.modules[21].control.num_control_commands = 0;
                fork_init(&adsp_auto.modules[21], &allocator21, 21, 1, 2, 1);
	static volume_control_config_t config20 = { .target_gain = 134217728, .slew_shift = 7, .mute = 0 };

            static volume_control_state_t state20;
            static uint8_t memory20[_ADSP_MAX(1, VOLUME_CONTROL_REQUIRED_MEMORY(2, 2, 1))];
            static adsp_bump_allocator_t allocator20 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory20);

            adsp_auto.modules[20].state = (void*)&state20;

            // Control stuff
            adsp_auto.modules[20].control.id = 20;
            adsp_auto.modules[20].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[20].control.config = (void*)&config20;
                adsp_auto.modules[20].control.module_type = e_dsp_stage_volume_control;
                adsp_auto.modules[20].control.num_control_commands = NUM_CMDS_VOLUME_CONTROL;
                volume_control_init(&adsp_auto.modules[20], &allocator20, 20, 2, 2, 1);
	static envelope_detector_rms_config_t config22 = { .attack_alpha = 298262, .release_alpha = 298262 };

            static envelope_detector_rms_state_t state22;
            static uint8_t memory22[_ADSP_MAX(1, ENVELOPE_DETECTOR_RMS_REQUIRED_MEMORY(1, 0, 1))];
            static adsp_bump_allocator_t allocator22 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory22);

            adsp_auto.modules[22].state = (void*)&state22;

            // Control stuff
            adsp_auto.modules[22].control.id = 22;
            adsp_auto.modules[22].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[22].control.config = (void*)&config22;
                adsp_auto.modules[22].control.module_type = e_dsp_stage_envelope_detector_rms;
                adsp_auto.modules[22].control.num_control_commands = NUM_CMDS_ENVELOPE_DETECTOR_RMS;
                envelope_detector_rms_init(&adsp_auto.modules[22], &allocator22, 22, 1, 0, 1);

            static fork_state_t state23;
            static uint8_t memory23[_ADSP_MAX(1, FORK_REQUIRED_MEMORY(2, 4, 1))];
            static adsp_bump_allocator_t allocator23 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory23);

            adsp_auto.modules[23].state = (void*)&state23;

            // Control stuff
            adsp_auto.modules[23].control.id = 23;
            adsp_auto.modules[23].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[23].control.config = NULL;
                adsp_auto.modules[23].control.num_control_commands = 0;
                fork_init(&adsp_auto.modules[23], &allocator23, 23, 2, 4, 1);
	static mixer_config_t config24 = { .gain = 67268211 };

            static mixer_state_t state24;
            static uint8_t memory24[_ADSP_MAX(1, MIXER_REQUIRED_MEMORY(2, 1, 1))];
            static adsp_bump_allocator_t allocator24 = ADSP_BUMP_ALLOCATOR_INITIALISER(memory24);

            adsp_auto.modules[24].state = (void*)&state24;

            // Control stuff
            adsp_auto.modules[24].control.id = 24;
            adsp_auto.modules[24].control.config_rw_state = config_none_pending;
            
                adsp_auto.modules[24].control.config = (void*)&config24;
                adsp_auto.modules[24].control.module_type = e_dsp_stage_mixer;
                adsp_auto.modules[24].control.num_control_commands = NUM_CMDS_MIXER;
                mixer_init(&adsp_auto.modules[24], &allocator24, 24, 2, 1, 1);
	return &adsp_auto;
}

void adsp_auto_pipeline_main(adsp_pipeline_t* adsp) {
	module_instance_t* thread_0_modules[] = {
		&adsp->modules[0],
		&adsp->modules[1],
		&adsp->modules[2],
		&adsp->modules[3],
		&adsp->modules[4],
		&adsp->modules[5],
		&adsp->modules[6],
		&adsp->modules[7],
		&adsp->modules[8],
		&adsp->modules[9],
	};
	chanend_t thread_0_inputs[] = {
		adsp->p_in[0].end_b};
	chanend_t thread_0_outputs[] = {
		adsp->p_link[0].end_a};
	module_instance_t* thread_1_modules[] = {
		&adsp->modules[10],
		&adsp->modules[11],
		&adsp->modules[12],
		&adsp->modules[13],
		&adsp->modules[14],
		&adsp->modules[15],
		&adsp->modules[16],
		&adsp->modules[19],
		&adsp->modules[17],
		&adsp->modules[18],
		&adsp->modules[21],
		&adsp->modules[20],
		&adsp->modules[22],
		&adsp->modules[23],
		&adsp->modules[24],
	};
	chanend_t thread_1_inputs[] = {
		adsp->p_link[0].end_b};
	chanend_t thread_1_outputs[] = {
		adsp->p_out[0].end_a};
	PAR_JOBS(
		PJOB(dsp_auto_thread0, (thread_0_inputs, thread_0_outputs, thread_0_modules)),
		PJOB(dsp_auto_thread1, (thread_1_inputs, thread_1_outputs, thread_1_modules))
	);
}
