/*
 * s_bb01_pos_data.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "s_bb01_pos".
 *
 * Model version              : 1.204
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Mon Jun 12 22:29:19 2023
 *
 * Target selection: quarc_windows.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-32 (Windows32)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "s_bb01_pos.h"
#include "s_bb01_pos_private.h"

/* Block parameters (default storage) */
P_s_bb01_pos_T s_bb01_pos_P = {
  /* Variable: K_AMP
   * Referenced by:
   *   '<S12>/Amplifier  Gain (V//V)'
   *   '<S12>/Inverse Amplifier  Gain (V//V)'
   */
  1.0,

  /* Variable: K_bb
   * Referenced by: '<S10>/Model Gain  (m//s^2//rad)'
   */
  0.41833688699360339,

  /* Variable: Kc
   * Referenced by: '<S2>/Proportional Gain  (rad.s//m)'
   */
  4.6904853992383195,

  /* Variable: THETA_MAX
   * Referenced by: '<S2>/Desired Angle  Saturation (rad)'
   */
  0.97738438111682457,

  /* Variable: THETA_MIN
   * Referenced by: '<S2>/Desired Angle  Saturation (rad)'
   */
  -0.97738438111682457,

  /* Variable: VMAX_AMP
   * Referenced by: '<S12>/Amplifier  Saturation (V)'
   */
  24.0,

  /* Variable: VMAX_DAC
   * Referenced by: '<S12>/DAQ Saturation (V)'
   */
  10.0,

  /* Variable: kp
   * Referenced by: '<S5>/Proportional Gain  (V//rad)'
   */
  11.558371093179357,

  /* Variable: kv
   * Referenced by: '<S5>/Velocity Gain  (V.s//rad)'
   */
  -0.10295983326809774,

  /* Variable: z
   * Referenced by: '<S2>/Zero Location (rad//s)'
   */
  1.403722216026992,

  /* Mask Parameter: SRV02SignalGenerator_a
   * Referenced by:
   *   '<S6>/Sine Wave'
   *   '<S6>/Square Wave'
   *   '<S9>/Amplitude'
   *   '<S9>/-R0*(t-1//(2*f))'
   *   '<S9>/R0'
   */
  1.0,

  /* Mask Parameter: SRV02SignalGenerator_f
   * Referenced by:
   *   '<S6>/Sine Wave'
   *   '<S6>/Square Wave'
   *   '<S9>/Half Period (s)'
   *   '<S9>/Period (s)'
   *   '<S9>/-R0*(t-1//(2*f))'
   *   '<S9>/R0'
   */
  0.05,

  /* Mask Parameter: Amplitudecm_gain
   * Referenced by: '<S1>/Slider Gain'
   */
  5.0,

  /* Mask Parameter: Constantcm_gain
   * Referenced by: '<S3>/Slider Gain'
   */
  0.0,

  /* Mask Parameter: SetPointWeight_gain
   * Referenced by: '<S8>/Slider Gain'
   */
  0.0,

  /* Mask Parameter: SRV02SignalGenerator_sig_type
   * Referenced by: '<S6>/Constant'
   */
  1.0,

  /* Expression: 1
   * Referenced by: '<Root>/Constant '
   */
  1.0,

  /* Expression: 0.01
   * Referenced by: '<Root>/Setpoint (m)'
   */
  0.01,

  /* Expression: 0
   * Referenced by: '<S10>/Vel to Pos'
   */
  0.0,

  /* Computed Parameter: HighPassFilterrads_A
   * Referenced by: '<S2>/High-Pass Filter (rad//s)'
   */
  -6.2831853071795862,

  /* Computed Parameter: HighPassFilterrads_C
   * Referenced by: '<S2>/High-Pass Filter (rad//s)'
   */
  -39.478417604357432,

  /* Computed Parameter: HighPassFilterrads_D
   * Referenced by: '<S2>/High-Pass Filter (rad//s)'
   */
  6.2831853071795862,

  /* Expression: 0
   * Referenced by: '<S11>/Vel to Pos'
   */
  0.0,

  /* Computed Parameter: Highpassfilter_A
   * Referenced by: '<S5>/High-pass filter'
   */
  { -565.48667764616278, -98696.044010893587 },

  /* Computed Parameter: Highpassfilter_C
   * Referenced by: '<S5>/High-pass filter'
   */
  { 98696.044010893587, 0.0 },

  /* Expression: 180/pi
   * Referenced by: '<S4>/Gain'
   */
  57.295779513082323,

  /* Expression: 100
   * Referenced by: '<Root>/cm//m'
   */
  100.0,

  /* Expression: -1
   * Referenced by: '<S5>/-theta_l (deg)'
   */
  -1.0,

  /* Expression: 0
   * Referenced by: '<S10>/Acc to Vel'
   */
  0.0,

  /* Computed Parameter: TransferFcn_A
   * Referenced by: '<S11>/Transfer Fcn'
   */
  -47.403497590106134,

  /* Computed Parameter: TransferFcn_C
   * Referenced by: '<S11>/Transfer Fcn'
   */
  72.459330717446676,

  /* Computed Parameter: ManualSwitch_CurrentSetting
   * Referenced by: '<S2>/Manual Switch'
   */
  1U
};
