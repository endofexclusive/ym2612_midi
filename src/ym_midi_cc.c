/* This file is automatically generated by the script
cc_functions.py. */

#define CC_CHANNEL_ALGORITHM_MIN 3
#define CC_CHANNEL_ALGORITHM_MAX 3
#define CC_OPERATOR_1_SELF_FEEDBACK_MIN 9
#define CC_OPERATOR_1_SELF_FEEDBACK_MAX 9
#define CC_CHANNEL_PAN_MIN 10
#define CC_CHANNEL_PAN_MAX 10
#define CC_CHANNEL_LFO_AM_SENSITIVITY_MIN 14
#define CC_CHANNEL_LFO_AM_SENSITIVITY_MAX 14
#define CC_CHANNEL_LFO_FM_SENSITIVITY_MIN 15
#define CC_CHANNEL_LFO_FM_SENSITIVITY_MAX 15
#define CC_LFO_FREQUENCY_MIN 16
#define CC_LFO_FREQUENCY_MAX 16
#define CC_CHANNEL_36_MODE_MIN 17
#define CC_CHANNEL_36_MODE_MAX 17
#define CC_OPERATOR_AMPLITUDE_MIN 20
#define CC_OPERATOR_AMPLITUDE_MAX 23
#define CC_OPERATOR_ATTACK_RATE_MIN 24
#define CC_OPERATOR_ATTACK_RATE_MAX 27
#define CC_OPERATOR_D1R_MIN 28
#define CC_OPERATOR_D1R_MAX 31
#define CC_OPERATOR_D1L_MIN 52
#define CC_OPERATOR_D1L_MAX 55
#define CC_OPERATOR_D2R_MIN 56
#define CC_OPERATOR_D2R_MAX 59
#define CC_OPERATOR_RR_MIN 60
#define CC_OPERATOR_RR_MAX 63
#define CC_OPERATOR_AM_MIN 104
#define CC_OPERATOR_AM_MAX 107
#define CC_OPERATOR_RATE_SCALING_MIN 108
#define CC_OPERATOR_RATE_SCALING_MAX 111
#define CC_OPERATOR_FREQ_MULTIPLIER_MIN 112
#define CC_OPERATOR_FREQ_MULTIPLIER_MAX 115
#define CC_OPERATOR_FREQ_DETUNE_MIN 116
#define CC_OPERATOR_FREQ_DETUNE_MAX 119

static struct cc_function_node cc_functions[] = {
    {.lower = CC_CHANNEL_ALGORITHM_MIN,
      .upper = CC_CHANNEL_ALGORITHM_MAX,
      .fun = cc_channel_algorithm},
    {.lower = CC_OPERATOR_1_SELF_FEEDBACK_MIN,
      .upper = CC_OPERATOR_1_SELF_FEEDBACK_MAX,
      .fun = cc_operator_1_self_feedback},
    {.lower = CC_CHANNEL_PAN_MIN,
      .upper = CC_CHANNEL_PAN_MAX,
      .fun = cc_channel_pan},
    {.lower = CC_CHANNEL_LFO_AM_SENSITIVITY_MIN,
      .upper = CC_CHANNEL_LFO_AM_SENSITIVITY_MAX,
      .fun = cc_channel_lfo_am_sensitivity},
    {.lower = CC_CHANNEL_LFO_FM_SENSITIVITY_MIN,
      .upper = CC_CHANNEL_LFO_FM_SENSITIVITY_MAX,
      .fun = cc_channel_lfo_fm_sensitivity},
    {.lower = CC_LFO_FREQUENCY_MIN,
      .upper = CC_LFO_FREQUENCY_MAX,
      .fun = cc_lfo_frequency},
    {.lower = CC_CHANNEL_36_MODE_MIN,
      .upper = CC_CHANNEL_36_MODE_MAX,
      .fun = cc_channel_36_mode},
    {.lower = CC_OPERATOR_AMPLITUDE_MIN,
      .upper = CC_OPERATOR_AMPLITUDE_MAX,
      .fun = cc_operator_amplitude},
    {.lower = CC_OPERATOR_ATTACK_RATE_MIN,
      .upper = CC_OPERATOR_ATTACK_RATE_MAX,
      .fun = cc_operator_attack_rate},
    {.lower = CC_OPERATOR_D1R_MIN,
      .upper = CC_OPERATOR_D1R_MAX,
      .fun = cc_operator_d1r},
    {.lower = CC_OPERATOR_D1L_MIN,
      .upper = CC_OPERATOR_D1L_MAX,
      .fun = cc_operator_d1l},
    {.lower = CC_OPERATOR_D2R_MIN,
      .upper = CC_OPERATOR_D2R_MAX,
      .fun = cc_operator_d2r},
    {.lower = CC_OPERATOR_RR_MIN,
      .upper = CC_OPERATOR_RR_MAX,
      .fun = cc_operator_rr},
    {.lower = CC_OPERATOR_AM_MIN,
      .upper = CC_OPERATOR_AM_MAX,
      .fun = cc_operator_am},
    {.lower = CC_OPERATOR_RATE_SCALING_MIN,
      .upper = CC_OPERATOR_RATE_SCALING_MAX,
      .fun = cc_operator_rate_scaling},
    {.lower = CC_OPERATOR_FREQ_MULTIPLIER_MIN,
      .upper = CC_OPERATOR_FREQ_MULTIPLIER_MAX,
      .fun = cc_operator_freq_multiplier},
    {.lower = CC_OPERATOR_FREQ_DETUNE_MIN,
      .upper = CC_OPERATOR_FREQ_DETUNE_MAX,
      .fun = cc_operator_freq_detune},
};
