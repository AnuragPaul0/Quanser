/*
 * q_bb01_pos_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_bb01_pos".
 *
 * Model version              : 30.3
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Jan 16 17:34:12 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_bb01_pos.h"
#include "q_bb01_pos_private.h"

/* Block parameters (default storage) */
P_q_bb01_pos_T q_bb01_pos_P = {
  /* Variable: K_AMP
   * Referenced by:
   *   '<S12>/Amplifier  Gain (V//V)'
   *   '<S12>/Inverse Amplifier  Gain (V//V)'
   */
  1.0,

  /* Variable: K_BS
   * Referenced by:
   *   '<S8>/BB01 Calibration  (m//V)'
   *   '<S8>/SS01 Calibration  (m//V)'
   */
  -0.042545,

  /* Variable: K_ENC
   * Referenced by: '<S8>/Encoder Calibration  (rad//count)'
   */
  0.0015339807878856412,

  /* Variable: Kc
   * Referenced by: '<S2>/Proportional Gain '
   */
  3.5529261191393107,

  /* Variable: THETA_MAX
   * Referenced by:
   *   '<S2>/Integrator'
   *   '<S2>/Desired Angle  Saturation (rad)'
   */
  0.97738438111682457,

  /* Variable: THETA_MIN
   * Referenced by:
   *   '<S2>/Integrator'
   *   '<S2>/Desired Angle  Saturation (rad)'
   */
  -0.97738438111682457,

  /* Variable: THETA_OFF
   * Referenced by: '<S8>/Bias'
   */
  -0.97738438111682457,

  /* Variable: VMAX_AMP
   * Referenced by: '<S12>/Amplifier  Saturation (V)'
   */
  24.0,

  /* Variable: VMAX_DAC
   * Referenced by: '<S12>/DACB Saturation (V)'
   */
  10.0,

  /* Variable: kp
   * Referenced by: '<S6>/Proportional Gain  (V//rad)'
   */
  11.558371093179357,

  /* Variable: kv
   * Referenced by: '<S6>/Velocity Gain  (V.s//rad)'
   */
  -0.10295983326809774,

  /* Variable: z
   * Referenced by: '<S2>/Zero Location (m.rad//s)'
   */
  1.2744282759094618,

  /* Mask Parameter: SRV02SignalGenerator_a
   * Referenced by:
   *   '<S7>/Sine Wave'
   *   '<S7>/Square Wave'
   *   '<S11>/Amplitude'
   *   '<S11>/-R0*(t-1//(2*f))'
   *   '<S11>/R0'
   */
  2.0,

  /* Mask Parameter: InitialTimes_const
   * Referenced by: '<S14>/Constant'
   */
  0.1,

  /* Mask Parameter: ReadingZero_const
   * Referenced by: '<S15>/Constant'
   */
  0.05,

  /* Mask Parameter: SRV02SignalGenerator_f
   * Referenced by:
   *   '<S7>/Sine Wave'
   *   '<S7>/Square Wave'
   *   '<S11>/Half Period (s)'
   *   '<S11>/Period (s)'
   *   '<S11>/-R0*(t-1//(2*f))'
   *   '<S11>/R0'
   */
  0.4,

  /* Mask Parameter: Amplitudecm_gain
   * Referenced by: '<S1>/Slider Gain'
   */
  1.0,

  /* Mask Parameter: Constantcm_gain
   * Referenced by: '<S3>/Slider Gain'
   */
  0.0,

  /* Mask Parameter: SetPointWeight_gain
   * Referenced by: '<S10>/Slider Gain'
   */
  0.0,

  /* Mask Parameter: IntegralGainradms_gain
   * Referenced by: '<S9>/Slider Gain'
   */
  0.5,

  /* Mask Parameter: SRV02SignalGenerator_sig_type
   * Referenced by: '<S7>/Constant'
   */
  1.0,

  /* Mask Parameter: HILReadEncoder_channels
   * Referenced by: '<S8>/HIL Read Encoder'
   */
  0U,

  /* Mask Parameter: HILWriteAnalog_channels
   * Referenced by: '<S8>/HIL Write Analog'
   */
  0U,

  /* Mask Parameter: HILWriteDigital_channels
   * Referenced by: '<S8>/HIL Write Digital'
   */
  { 0U, 1U, 2U, 3U },

  /* Expression: 0.01
   * Referenced by: '<Root>/Setpoint (m)'
   */
  0.01,

  /* Expression: set_other_outputs_at_terminate
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_out
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_start
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: set_other_outputs_at_switch_in
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: final_analog_outputs
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: final_pwm_outputs
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: analog_input_maximums
   * Referenced by: '<S8>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_input_minimums
   * Referenced by: '<S8>/HIL Initialize'
   */
  -10.0,

  /* Expression: analog_output_maximums
   * Referenced by: '<S8>/HIL Initialize'
   */
  10.0,

  /* Expression: analog_output_minimums
   * Referenced by: '<S8>/HIL Initialize'
   */
  -10.0,

  /* Expression: initial_analog_outputs
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_analog_outputs
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_frequency
   * Referenced by: '<S8>/HIL Initialize'
   */
  24305.934065934067,

  /* Expression: pwm_leading_deadband
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: pwm_trailing_deadband
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: initial_pwm_outputs
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: watchdog_pwm_outputs
   * Referenced by: '<S8>/HIL Initialize'
   */
  0.0,

  /* Expression: -4.5
   * Referenced by: '<S13>/Constant'
   */
  -4.5,

  /* Expression: 1
   * Referenced by: '<Root>/Constant '
   */
  1.0,

  /* Computed Parameter: HighPassFilterms_A
   * Referenced by: '<S2>/High-Pass Filter (m//s)'
   */
  -6.2831853071795862,

  /* Computed Parameter: HighPassFilterms_C
   * Referenced by: '<S2>/High-Pass Filter (m//s)'
   */
  -39.478417604357432,

  /* Computed Parameter: HighPassFilterms_D
   * Referenced by: '<S2>/High-Pass Filter (m//s)'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S2>/Integrator'
   */
  0.0,

  /* Computed Parameter: Highpassfilter_A
   * Referenced by: '<S6>/High-pass filter'
   */
  { -565.48667764616278, -98696.044010893587 },

  /* Computed Parameter: Highpassfilter_C
   * Referenced by: '<S6>/High-pass filter'
   */
  { 98696.044010893587, 0.0 },

  /* Expression: -1
   * Referenced by: '<S12>/Direction Convention: (Right-Hand) system'
   */
  -1.0,

  /* Expression: [1 1 1 1]
   * Referenced by: '<S8>/Enable VoltPAQ-X2,X4'
   */
  { 1.0, 1.0, 1.0, 1.0 },

  /* Expression: 180/pi
   * Referenced by: '<S5>/Gain'
   */
  57.295779513082323,

  /* Expression: 100
   * Referenced by: '<Root>/cm//m'
   */
  100.0,

  /* Expression: -1
   * Referenced by: '<S6>/-theta_l (deg)'
   */
  -1.0,

  /* Computed Parameter: HILInitialize_CKChannels
   * Referenced by: '<S8>/HIL Initialize'
   */
  { 0, 1, 2 },

  /* Computed Parameter: HILInitialize_DOWatchdog
   * Referenced by: '<S8>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_EIInitial
   * Referenced by: '<S8>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POModes
   * Referenced by: '<S8>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POConfiguration
   * Referenced by: '<S8>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POAlignment
   * Referenced by: '<S8>/HIL Initialize'
   */
  0,

  /* Computed Parameter: HILInitialize_POPolarity
   * Referenced by: '<S8>/HIL Initialize'
   */
  1,

  /* Computed Parameter: HILReadAnalogTimebase_Clock
   * Referenced by: '<S8>/HIL Read Analog Timebase'
   */
  0,

  /* Computed Parameter: HILInitialize_AIChannels
   * Referenced by: '<S8>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_AOChannels
   * Referenced by: '<S8>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_DOChannels
   * Referenced by: '<S8>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIChannels
   * Referenced by: '<S8>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILInitialize_EIQuadrature
   * Referenced by: '<S8>/HIL Initialize'
   */
  4U,

  /* Computed Parameter: HILInitialize_POChannels
   * Referenced by: '<S8>/HIL Initialize'
   */
  { 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U },

  /* Computed Parameter: HILReadAnalogTimebase_Channels
   * Referenced by: '<S8>/HIL Read Analog Timebase'
   */
  { 0U, 1U },

  /* Computed Parameter: HILReadAnalogTimebase_SamplesIn
   * Referenced by: '<S8>/HIL Read Analog Timebase'
   */
  500U,

  /* Computed Parameter: HILInitialize_Active
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOTerminate
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOExit
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOTerminate
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOExit
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POTerminate
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POExit
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKPStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKPEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_CKEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AIPStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AIPEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOPStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOPEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_AOEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_AOReset
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOPStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOPEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_DOEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOReset
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_EIPStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_EIPEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_EIStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_EIEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POPStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POPEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POStart
   * Referenced by: '<S8>/HIL Initialize'
   */
  true,

  /* Computed Parameter: HILInitialize_POEnter
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_POReset
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_OOReset
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOFinal
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILInitialize_DOInitial
   * Referenced by: '<S8>/HIL Initialize'
   */
  false,

  /* Computed Parameter: HILReadAnalogTimebase_Active
   * Referenced by: '<S8>/HIL Read Analog Timebase'
   */
  true,

  /* Computed Parameter: HILReadEncoder_Active
   * Referenced by: '<S8>/HIL Read Encoder'
   */
  true,

  /* Computed Parameter: HILWriteAnalog_Active
   * Referenced by: '<S8>/HIL Write Analog'
   */
  false,

  /* Computed Parameter: HILWriteDigital_Active
   * Referenced by: '<S8>/HIL Write Digital'
   */
  false,

  /* Computed Parameter: HILReadAnalogTimebase_OverflowM
   * Referenced by: '<S8>/HIL Read Analog Timebase'
   */
  1U,

  /* Computed Parameter: SetpointSource_CurrentSetting
   * Referenced by: '<Root>/Setpoint Source'
   */
  1U
};
