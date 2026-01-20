/*
 * s_bb01_pos.c
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
#include "s_bb01_pos_dt.h"

/* Block signals (default storage) */
B_s_bb01_pos_T s_bb01_pos_B;

/* Continuous states */
X_s_bb01_pos_T s_bb01_pos_X;

/* Block states (default storage) */
DW_s_bb01_pos_T s_bb01_pos_DW;

/* Real-time model */
static RT_MODEL_s_bb01_pos_T s_bb01_pos_M_;
RT_MODEL_s_bb01_pos_T *const s_bb01_pos_M = &s_bb01_pos_M_;

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 7;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  s_bb01_pos_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  s_bb01_pos_output();
  s_bb01_pos_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  s_bb01_pos_output();
  s_bb01_pos_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  s_bb01_pos_output();
  s_bb01_pos_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_modd_snf(real_T u0, real_T u1)
{
  real_T q;
  real_T y;
  boolean_T yEq;
  y = u0;
  if (u1 == 0.0) {
    if (u0 == 0.0) {
      y = u1;
    }
  } else if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (u0 == 0.0) {
    y = 0.0 / u1;
  } else if (rtIsInf(u1)) {
    if ((u1 < 0.0) != (u0 < 0.0)) {
      y = u1;
    }
  } else {
    y = fmod(u0, u1);
    yEq = (y == 0.0);
    if ((!yEq) && (u1 > floor(u1))) {
      q = fabs(u0 / u1);
      yEq = !(fabs(q - floor(q + 0.5)) > DBL_EPSILON * q);
    }

    if (yEq) {
      y = u1 * 0.0;
    } else if ((u0 < 0.0) != (u1 < 0.0)) {
      y += u1;
    }
  }

  return y;
}

/* Model output function */
void s_bb01_pos_output(void)
{
  real_T temp;
  real_T u0;
  real_T u2;
  real_T *lastU;
  if (rtmIsMajorTimeStep(s_bb01_pos_M)) {
    /* set solver stop time */
    if (!(s_bb01_pos_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&s_bb01_pos_M->solverInfo,
                            ((s_bb01_pos_M->Timing.clockTickH0 + 1) *
        s_bb01_pos_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&s_bb01_pos_M->solverInfo,
                            ((s_bb01_pos_M->Timing.clockTick0 + 1) *
        s_bb01_pos_M->Timing.stepSize0 + s_bb01_pos_M->Timing.clockTickH0 *
        s_bb01_pos_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(s_bb01_pos_M)) {
    s_bb01_pos_M->Timing.t[0] = rtsiGetT(&s_bb01_pos_M->solverInfo);
  }

  /* SignalGenerator: '<S6>/Square Wave' */
  temp = s_bb01_pos_P.SRV02SignalGenerator_f * s_bb01_pos_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    /* SignalGenerator: '<S6>/Square Wave' */
    s_bb01_pos_B.SquareWave = s_bb01_pos_P.SRV02SignalGenerator_a;
  } else {
    /* SignalGenerator: '<S6>/Square Wave' */
    s_bb01_pos_B.SquareWave = -s_bb01_pos_P.SRV02SignalGenerator_a;
  }

  /* End of SignalGenerator: '<S6>/Square Wave' */

  /* Clock: '<S9>/Clock' */
  s_bb01_pos_B.Clock = s_bb01_pos_M->Timing.t[0];

  /* SignalGenerator: '<S6>/Sine Wave' */
  temp = 6.2831853071795862 * s_bb01_pos_M->Timing.t[0];

  /* SignalGenerator: '<S6>/Sine Wave' */
  s_bb01_pos_B.SineWave = sin(s_bb01_pos_P.SRV02SignalGenerator_f * temp) *
    s_bb01_pos_P.SRV02SignalGenerator_a;

  /* MultiPortSwitch: '<S6>/Multiport Switch' incorporates:
   *  Constant: '<S6>/Constant'
   */
  switch ((int32_T)s_bb01_pos_P.SRV02SignalGenerator_sig_type) {
   case 1:
    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    s_bb01_pos_B.MultiportSwitch = s_bb01_pos_B.SquareWave;
    break;

   case 2:
    /* Math: '<S9>/t' incorporates:
     *  Constant: '<S9>/Period (s)'
     */
    temp = 1.0 / s_bb01_pos_P.SRV02SignalGenerator_f;

    /* Math: '<S9>/t' */
    s_bb01_pos_B.t = rt_modd_snf(s_bb01_pos_B.Clock, temp);

    /* RelationalOperator: '<S9>/t >= 1//(2*f)?' incorporates:
     *  Constant: '<S9>/Half Period (s)'
     */
    temp = 1.0 / (2.0 * s_bb01_pos_P.SRV02SignalGenerator_f);

    /* RelationalOperator: '<S9>/t >= 1//(2*f)?' */
    s_bb01_pos_B.t12f_o = (s_bb01_pos_B.t >= temp);

    /* MultiPortSwitch: '<S9>/Multiport Switch' */
    if (!s_bb01_pos_B.t12f_o) {
      /* Gain: '<S9>/R0' */
      temp = 4.0 * s_bb01_pos_P.SRV02SignalGenerator_a *
        s_bb01_pos_P.SRV02SignalGenerator_f;

      /* Gain: '<S9>/R0' */
      s_bb01_pos_B.R0 = temp * s_bb01_pos_B.t;

      /* Sum: '<S9>/Sum' incorporates:
       *  Constant: '<S9>/Amplitude'
       */
      s_bb01_pos_B.Sum = s_bb01_pos_B.R0 - s_bb01_pos_P.SRV02SignalGenerator_a;

      /* MultiPortSwitch: '<S9>/Multiport Switch' */
      s_bb01_pos_B.MultiportSwitch_g = s_bb01_pos_B.Sum;
    } else {
      /* Sum: '<S9>/t-1//(2*f)' incorporates:
       *  Constant: '<S9>/Half Period (s)'
       */
      temp = 1.0 / (2.0 * s_bb01_pos_P.SRV02SignalGenerator_f);

      /* Sum: '<S9>/t-1//(2*f)' */
      s_bb01_pos_B.t12f = s_bb01_pos_B.t - temp;

      /* Gain: '<S9>/-R0*(t-1//(2*f))' */
      temp = -4.0 * s_bb01_pos_P.SRV02SignalGenerator_a *
        s_bb01_pos_P.SRV02SignalGenerator_f;

      /* Gain: '<S9>/-R0*(t-1//(2*f))' */
      s_bb01_pos_B.R0t12f = temp * s_bb01_pos_B.t12f;

      /* Sum: '<S9>/Sum1' incorporates:
       *  Constant: '<S9>/Amplitude'
       */
      s_bb01_pos_B.Sum1 = s_bb01_pos_P.SRV02SignalGenerator_a +
        s_bb01_pos_B.R0t12f;

      /* MultiPortSwitch: '<S9>/Multiport Switch' */
      s_bb01_pos_B.MultiportSwitch_g = s_bb01_pos_B.Sum1;
    }

    /* End of MultiPortSwitch: '<S9>/Multiport Switch' */

    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    s_bb01_pos_B.MultiportSwitch = s_bb01_pos_B.MultiportSwitch_g;
    break;

   default:
    /* MultiPortSwitch: '<S6>/Multiport Switch' */
    s_bb01_pos_B.MultiportSwitch = s_bb01_pos_B.SineWave;
    break;
  }

  /* End of MultiPortSwitch: '<S6>/Multiport Switch' */

  /* Gain: '<S1>/Slider Gain' */
  s_bb01_pos_B.SliderGain = s_bb01_pos_P.Amplitudecm_gain *
    s_bb01_pos_B.MultiportSwitch;
  if (rtmIsMajorTimeStep(s_bb01_pos_M)) {
    /* Gain: '<S3>/Slider Gain' incorporates:
     *  Constant: '<Root>/Constant '
     */
    s_bb01_pos_B.SliderGain_h = s_bb01_pos_P.Constantcm_gain *
      s_bb01_pos_P.Constant_Value;
  }

  /* Sum: '<Root>/Setpoint (cm)' */
  s_bb01_pos_B.Setpointcm = s_bb01_pos_B.SliderGain + s_bb01_pos_B.SliderGain_h;

  /* Gain: '<Root>/Setpoint (m)' */
  s_bb01_pos_B.Setpointm = s_bb01_pos_P.Setpointm_Gain * s_bb01_pos_B.Setpointcm;

  /* Integrator: '<S10>/Vel to Pos' */
  s_bb01_pos_B.VeltoPos = s_bb01_pos_X.VeltoPos_CSTATE;

  /* Sum: '<S2>/Position Error (m)' */
  s_bb01_pos_B.PositionErrorm = s_bb01_pos_B.Setpointm - s_bb01_pos_B.VeltoPos;

  /* Gain: '<S2>/Zero Location (rad//s)' */
  s_bb01_pos_B.ZeroLocationrads = s_bb01_pos_P.z * s_bb01_pos_B.PositionErrorm;

  /* Gain: '<S8>/Slider Gain' */
  s_bb01_pos_B.SliderGain_j = s_bb01_pos_P.SetPointWeight_gain *
    s_bb01_pos_B.Setpointm;

  /* Sum: '<S2>/Weighed Position Error (m//s)' */
  s_bb01_pos_B.WeighedPositionErrorms = s_bb01_pos_B.SliderGain_j -
    s_bb01_pos_B.VeltoPos;

  /* Derivative: '<S2>/Derivative (m//s)' */
  if ((s_bb01_pos_DW.TimeStampA >= s_bb01_pos_M->Timing.t[0]) &&
      (s_bb01_pos_DW.TimeStampB >= s_bb01_pos_M->Timing.t[0])) {
    /* Derivative: '<S2>/Derivative (m//s)' */
    s_bb01_pos_B.Derivativems = 0.0;
  } else {
    temp = s_bb01_pos_DW.TimeStampA;
    lastU = &s_bb01_pos_DW.LastUAtTimeA;
    if (s_bb01_pos_DW.TimeStampA < s_bb01_pos_DW.TimeStampB) {
      if (s_bb01_pos_DW.TimeStampB < s_bb01_pos_M->Timing.t[0]) {
        temp = s_bb01_pos_DW.TimeStampB;
        lastU = &s_bb01_pos_DW.LastUAtTimeB;
      }
    } else if (s_bb01_pos_DW.TimeStampA >= s_bb01_pos_M->Timing.t[0]) {
      temp = s_bb01_pos_DW.TimeStampB;
      lastU = &s_bb01_pos_DW.LastUAtTimeB;
    }

    temp = s_bb01_pos_M->Timing.t[0] - temp;

    /* Derivative: '<S2>/Derivative (m//s)' */
    s_bb01_pos_B.Derivativems = (s_bb01_pos_B.WeighedPositionErrorms - *lastU) /
      temp;
  }

  /* End of Derivative: '<S2>/Derivative (m//s)' */

  /* TransferFcn: '<S2>/High-Pass Filter (rad//s)' */
  s_bb01_pos_B.HighPassFilterrads = 0.0;
  s_bb01_pos_B.HighPassFilterrads += s_bb01_pos_P.HighPassFilterrads_C *
    s_bb01_pos_X.HighPassFilterrads_CSTATE;
  s_bb01_pos_B.HighPassFilterrads += s_bb01_pos_P.HighPassFilterrads_D *
    s_bb01_pos_B.WeighedPositionErrorms;

  /* ManualSwitch: '<S2>/Manual Switch' */
  if (s_bb01_pos_P.ManualSwitch_CurrentSetting == 1) {
    /* ManualSwitch: '<S2>/Manual Switch' */
    s_bb01_pos_B.ManualSwitch = s_bb01_pos_B.Derivativems;
  } else {
    /* ManualSwitch: '<S2>/Manual Switch' */
    s_bb01_pos_B.ManualSwitch = s_bb01_pos_B.HighPassFilterrads;
  }

  /* End of ManualSwitch: '<S2>/Manual Switch' */

  /* Sum: '<S2>/Control  Output (m//s)' */
  s_bb01_pos_B.ControlOutputms = s_bb01_pos_B.ZeroLocationrads +
    s_bb01_pos_B.ManualSwitch;

  /* Gain: '<S2>/Proportional Gain  (rad.s//m)' */
  s_bb01_pos_B.ProportionalGainradsm = s_bb01_pos_P.Kc *
    s_bb01_pos_B.ControlOutputms;

  /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
  u0 = s_bb01_pos_B.ProportionalGainradsm;
  temp = s_bb01_pos_P.THETA_MIN;
  u2 = s_bb01_pos_P.THETA_MAX;
  if (u0 > u2) {
    /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
    s_bb01_pos_B.DesiredAngleSaturationrad = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
    s_bb01_pos_B.DesiredAngleSaturationrad = temp;
  } else {
    /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
    s_bb01_pos_B.DesiredAngleSaturationrad = u0;
  }

  /* End of Saturate: '<S2>/Desired Angle  Saturation (rad)' */

  /* Integrator: '<S11>/Vel to Pos' */
  s_bb01_pos_B.VeltoPos_i = s_bb01_pos_X.VeltoPos_CSTATE_p;

  /* Sum: '<S5>/Position Error (rad)' */
  s_bb01_pos_B.PositionErrorrad = s_bb01_pos_B.DesiredAngleSaturationrad -
    s_bb01_pos_B.VeltoPos_i;

  /* Gain: '<S5>/Proportional Gain  (V//rad)' */
  s_bb01_pos_B.ProportionalGainVrad = s_bb01_pos_P.kp *
    s_bb01_pos_B.PositionErrorrad;

  /* TransferFcn: '<S5>/High-pass filter' */
  s_bb01_pos_B.Highpassfilter = 0.0;
  s_bb01_pos_B.Highpassfilter += s_bb01_pos_P.Highpassfilter_C[0] *
    s_bb01_pos_X.Highpassfilter_CSTATE[0];
  s_bb01_pos_B.Highpassfilter += s_bb01_pos_P.Highpassfilter_C[1] *
    s_bb01_pos_X.Highpassfilter_CSTATE[1];

  /* Gain: '<S5>/Velocity Gain  (V.s//rad)' */
  s_bb01_pos_B.VelocityGainVsrad = s_bb01_pos_P.kv * s_bb01_pos_B.Highpassfilter;

  /* Sum: '<S5>/Control  Output' */
  s_bb01_pos_B.ControlOutput = s_bb01_pos_B.ProportionalGainVrad +
    s_bb01_pos_B.VelocityGainVsrad;

  /* Saturate: '<S12>/Amplifier  Saturation (V)' */
  temp = -s_bb01_pos_P.VMAX_AMP;
  u0 = s_bb01_pos_B.ControlOutput;
  u2 = s_bb01_pos_P.VMAX_AMP;
  if (u0 > u2) {
    /* Saturate: '<S12>/Amplifier  Saturation (V)' */
    s_bb01_pos_B.AmplifierSaturationV = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S12>/Amplifier  Saturation (V)' */
    s_bb01_pos_B.AmplifierSaturationV = temp;
  } else {
    /* Saturate: '<S12>/Amplifier  Saturation (V)' */
    s_bb01_pos_B.AmplifierSaturationV = u0;
  }

  /* End of Saturate: '<S12>/Amplifier  Saturation (V)' */

  /* Gain: '<S12>/Inverse Amplifier  Gain (V//V)' */
  temp = 1.0 / s_bb01_pos_P.K_AMP;

  /* Gain: '<S12>/Inverse Amplifier  Gain (V//V)' */
  s_bb01_pos_B.InverseAmplifierGainVV = temp * s_bb01_pos_B.AmplifierSaturationV;

  /* Saturate: '<S12>/DAQ Saturation (V)' */
  temp = -s_bb01_pos_P.VMAX_DAC;
  u0 = s_bb01_pos_B.InverseAmplifierGainVV;
  u2 = s_bb01_pos_P.VMAX_DAC;
  if (u0 > u2) {
    /* Saturate: '<S12>/DAQ Saturation (V)' */
    s_bb01_pos_B.DAQSaturationV = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S12>/DAQ Saturation (V)' */
    s_bb01_pos_B.DAQSaturationV = temp;
  } else {
    /* Saturate: '<S12>/DAQ Saturation (V)' */
    s_bb01_pos_B.DAQSaturationV = u0;
  }

  /* End of Saturate: '<S12>/DAQ Saturation (V)' */

  /* Gain: '<S12>/Amplifier  Gain (V//V)' */
  s_bb01_pos_B.AmplifierGainVV = s_bb01_pos_P.K_AMP *
    s_bb01_pos_B.DAQSaturationV;
  if (rtmIsMajorTimeStep(s_bb01_pos_M)) {
  }

  /* Gain: '<S4>/Gain' */
  s_bb01_pos_B.Gain[0] = s_bb01_pos_P.Gain_Gain *
    s_bb01_pos_B.DesiredAngleSaturationrad;
  s_bb01_pos_B.Gain[1] = s_bb01_pos_P.Gain_Gain * s_bb01_pos_B.VeltoPos_i;
  if (rtmIsMajorTimeStep(s_bb01_pos_M)) {
  }

  /* Gain: '<Root>/cm//m' */
  s_bb01_pos_B.cmm[0] = s_bb01_pos_P.cmm_Gain * s_bb01_pos_B.Setpointm;
  s_bb01_pos_B.cmm[1] = s_bb01_pos_P.cmm_Gain * s_bb01_pos_B.VeltoPos;
  if (rtmIsMajorTimeStep(s_bb01_pos_M)) {
  }

  /* Gain: '<S5>/-theta_l (deg)' */
  s_bb01_pos_B.theta_ldeg = s_bb01_pos_P.theta_ldeg_Gain *
    s_bb01_pos_B.VeltoPos_i;

  /* Integrator: '<S10>/Acc to Vel' */
  s_bb01_pos_B.AcctoVel = s_bb01_pos_X.AcctoVel_CSTATE;

  /* Trigonometry: '<S10>/Trigonometric Function' */
  s_bb01_pos_B.TrigonometricFunction = sin(s_bb01_pos_B.VeltoPos_i);

  /* Gain: '<S10>/Model Gain  (m//s^2//rad)' */
  s_bb01_pos_B.ModelGainms2rad = s_bb01_pos_P.K_bb *
    s_bb01_pos_B.TrigonometricFunction;

  /* TransferFcn: '<S11>/Transfer Fcn' */
  s_bb01_pos_B.TransferFcn = 0.0;
  s_bb01_pos_B.TransferFcn += s_bb01_pos_P.TransferFcn_C *
    s_bb01_pos_X.TransferFcn_CSTATE;
}

/* Model update function */
void s_bb01_pos_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S2>/Derivative (m//s)' */
  if (s_bb01_pos_DW.TimeStampA == (rtInf)) {
    s_bb01_pos_DW.TimeStampA = s_bb01_pos_M->Timing.t[0];
    lastU = &s_bb01_pos_DW.LastUAtTimeA;
  } else if (s_bb01_pos_DW.TimeStampB == (rtInf)) {
    s_bb01_pos_DW.TimeStampB = s_bb01_pos_M->Timing.t[0];
    lastU = &s_bb01_pos_DW.LastUAtTimeB;
  } else if (s_bb01_pos_DW.TimeStampA < s_bb01_pos_DW.TimeStampB) {
    s_bb01_pos_DW.TimeStampA = s_bb01_pos_M->Timing.t[0];
    lastU = &s_bb01_pos_DW.LastUAtTimeA;
  } else {
    s_bb01_pos_DW.TimeStampB = s_bb01_pos_M->Timing.t[0];
    lastU = &s_bb01_pos_DW.LastUAtTimeB;
  }

  *lastU = s_bb01_pos_B.WeighedPositionErrorms;

  /* End of Update for Derivative: '<S2>/Derivative (m//s)' */
  if (rtmIsMajorTimeStep(s_bb01_pos_M)) {
    rt_ertODEUpdateContinuousStates(&s_bb01_pos_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++s_bb01_pos_M->Timing.clockTick0)) {
    ++s_bb01_pos_M->Timing.clockTickH0;
  }

  s_bb01_pos_M->Timing.t[0] = rtsiGetSolverStopTime(&s_bb01_pos_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++s_bb01_pos_M->Timing.clockTick1)) {
      ++s_bb01_pos_M->Timing.clockTickH1;
    }

    s_bb01_pos_M->Timing.t[1] = s_bb01_pos_M->Timing.clockTick1 *
      s_bb01_pos_M->Timing.stepSize1 + s_bb01_pos_M->Timing.clockTickH1 *
      s_bb01_pos_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void s_bb01_pos_derivatives(void)
{
  XDot_s_bb01_pos_T *_rtXdot;
  _rtXdot = ((XDot_s_bb01_pos_T *) s_bb01_pos_M->derivs);

  /* Derivatives for Integrator: '<S10>/Vel to Pos' */
  _rtXdot->VeltoPos_CSTATE = s_bb01_pos_B.AcctoVel;

  /* Derivatives for TransferFcn: '<S2>/High-Pass Filter (rad//s)' */
  _rtXdot->HighPassFilterrads_CSTATE = 0.0;
  _rtXdot->HighPassFilterrads_CSTATE += s_bb01_pos_P.HighPassFilterrads_A *
    s_bb01_pos_X.HighPassFilterrads_CSTATE;
  _rtXdot->HighPassFilterrads_CSTATE += s_bb01_pos_B.WeighedPositionErrorms;

  /* Derivatives for Integrator: '<S11>/Vel to Pos' */
  _rtXdot->VeltoPos_CSTATE_p = s_bb01_pos_B.TransferFcn;

  /* Derivatives for TransferFcn: '<S5>/High-pass filter' */
  _rtXdot->Highpassfilter_CSTATE[0] = 0.0;
  _rtXdot->Highpassfilter_CSTATE[0] += s_bb01_pos_P.Highpassfilter_A[0] *
    s_bb01_pos_X.Highpassfilter_CSTATE[0];
  _rtXdot->Highpassfilter_CSTATE[1] = 0.0;
  _rtXdot->Highpassfilter_CSTATE[0] += s_bb01_pos_P.Highpassfilter_A[1] *
    s_bb01_pos_X.Highpassfilter_CSTATE[1];
  _rtXdot->Highpassfilter_CSTATE[1] += s_bb01_pos_X.Highpassfilter_CSTATE[0];
  _rtXdot->Highpassfilter_CSTATE[0] += s_bb01_pos_B.theta_ldeg;

  /* Derivatives for Integrator: '<S10>/Acc to Vel' */
  _rtXdot->AcctoVel_CSTATE = s_bb01_pos_B.ModelGainms2rad;

  /* Derivatives for TransferFcn: '<S11>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += s_bb01_pos_P.TransferFcn_A *
    s_bb01_pos_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += s_bb01_pos_B.AmplifierGainVV;
}

/* Model initialize function */
void s_bb01_pos_initialize(void)
{
  /* InitializeConditions for Integrator: '<S10>/Vel to Pos' */
  s_bb01_pos_X.VeltoPos_CSTATE = s_bb01_pos_P.VeltoPos_IC;

  /* InitializeConditions for Derivative: '<S2>/Derivative (m//s)' */
  s_bb01_pos_DW.TimeStampA = (rtInf);
  s_bb01_pos_DW.TimeStampB = (rtInf);

  /* InitializeConditions for TransferFcn: '<S2>/High-Pass Filter (rad//s)' */
  s_bb01_pos_X.HighPassFilterrads_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S11>/Vel to Pos' */
  s_bb01_pos_X.VeltoPos_CSTATE_p = s_bb01_pos_P.VeltoPos_IC_h;

  /* InitializeConditions for TransferFcn: '<S5>/High-pass filter' */
  s_bb01_pos_X.Highpassfilter_CSTATE[0] = 0.0;
  s_bb01_pos_X.Highpassfilter_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S10>/Acc to Vel' */
  s_bb01_pos_X.AcctoVel_CSTATE = s_bb01_pos_P.AcctoVel_IC;

  /* InitializeConditions for TransferFcn: '<S11>/Transfer Fcn' */
  s_bb01_pos_X.TransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void s_bb01_pos_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  s_bb01_pos_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  s_bb01_pos_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  s_bb01_pos_initialize();
}

void MdlTerminate(void)
{
  s_bb01_pos_terminate();
}

/* Registration function */
RT_MODEL_s_bb01_pos_T *s_bb01_pos(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)s_bb01_pos_M, 0,
                sizeof(RT_MODEL_s_bb01_pos_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&s_bb01_pos_M->solverInfo,
                          &s_bb01_pos_M->Timing.simTimeStep);
    rtsiSetTPtr(&s_bb01_pos_M->solverInfo, &rtmGetTPtr(s_bb01_pos_M));
    rtsiSetStepSizePtr(&s_bb01_pos_M->solverInfo,
                       &s_bb01_pos_M->Timing.stepSize0);
    rtsiSetdXPtr(&s_bb01_pos_M->solverInfo, &s_bb01_pos_M->derivs);
    rtsiSetContStatesPtr(&s_bb01_pos_M->solverInfo, (real_T **)
                         &s_bb01_pos_M->contStates);
    rtsiSetNumContStatesPtr(&s_bb01_pos_M->solverInfo,
      &s_bb01_pos_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&s_bb01_pos_M->solverInfo,
      &s_bb01_pos_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&s_bb01_pos_M->solverInfo,
      &s_bb01_pos_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&s_bb01_pos_M->solverInfo,
      &s_bb01_pos_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&s_bb01_pos_M->solverInfo, (&rtmGetErrorStatus
      (s_bb01_pos_M)));
    rtsiSetRTModelPtr(&s_bb01_pos_M->solverInfo, s_bb01_pos_M);
  }

  rtsiSetSimTimeStep(&s_bb01_pos_M->solverInfo, MAJOR_TIME_STEP);
  s_bb01_pos_M->intgData.y = s_bb01_pos_M->odeY;
  s_bb01_pos_M->intgData.f[0] = s_bb01_pos_M->odeF[0];
  s_bb01_pos_M->intgData.f[1] = s_bb01_pos_M->odeF[1];
  s_bb01_pos_M->intgData.f[2] = s_bb01_pos_M->odeF[2];
  s_bb01_pos_M->intgData.f[3] = s_bb01_pos_M->odeF[3];
  s_bb01_pos_M->contStates = ((real_T *) &s_bb01_pos_X);
  rtsiSetSolverData(&s_bb01_pos_M->solverInfo, (void *)&s_bb01_pos_M->intgData);
  rtsiSetSolverName(&s_bb01_pos_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = s_bb01_pos_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "s_bb01_pos_M points to
       static memory which is guaranteed to be non-NULL" */
    s_bb01_pos_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    s_bb01_pos_M->Timing.sampleTimes = (&s_bb01_pos_M->Timing.sampleTimesArray[0]);
    s_bb01_pos_M->Timing.offsetTimes = (&s_bb01_pos_M->Timing.offsetTimesArray[0]);

    /* task periods */
    s_bb01_pos_M->Timing.sampleTimes[0] = (0.0);
    s_bb01_pos_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    s_bb01_pos_M->Timing.offsetTimes[0] = (0.0);
    s_bb01_pos_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(s_bb01_pos_M, &s_bb01_pos_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = s_bb01_pos_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    s_bb01_pos_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(s_bb01_pos_M, 25.0);
  s_bb01_pos_M->Timing.stepSize0 = 0.002;
  s_bb01_pos_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  s_bb01_pos_M->Sizes.checksums[0] = (563831290U);
  s_bb01_pos_M->Sizes.checksums[1] = (1666389058U);
  s_bb01_pos_M->Sizes.checksums[2] = (4076289450U);
  s_bb01_pos_M->Sizes.checksums[3] = (3849581701U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    s_bb01_pos_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(s_bb01_pos_M->extModeInfo,
      &s_bb01_pos_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(s_bb01_pos_M->extModeInfo, s_bb01_pos_M->Sizes.checksums);
    rteiSetTPtr(s_bb01_pos_M->extModeInfo, rtmGetTPtr(s_bb01_pos_M));
  }

  s_bb01_pos_M->solverInfoPtr = (&s_bb01_pos_M->solverInfo);
  s_bb01_pos_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&s_bb01_pos_M->solverInfo, 0.002);
  rtsiSetSolverMode(&s_bb01_pos_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  s_bb01_pos_M->blockIO = ((void *) &s_bb01_pos_B);
  (void) memset(((void *) &s_bb01_pos_B), 0,
                sizeof(B_s_bb01_pos_T));

  {
    s_bb01_pos_B.SquareWave = 0.0;
    s_bb01_pos_B.Clock = 0.0;
    s_bb01_pos_B.SineWave = 0.0;
    s_bb01_pos_B.MultiportSwitch = 0.0;
    s_bb01_pos_B.SliderGain = 0.0;
    s_bb01_pos_B.SliderGain_h = 0.0;
    s_bb01_pos_B.Setpointcm = 0.0;
    s_bb01_pos_B.Setpointm = 0.0;
    s_bb01_pos_B.VeltoPos = 0.0;
    s_bb01_pos_B.PositionErrorm = 0.0;
    s_bb01_pos_B.ZeroLocationrads = 0.0;
    s_bb01_pos_B.SliderGain_j = 0.0;
    s_bb01_pos_B.WeighedPositionErrorms = 0.0;
    s_bb01_pos_B.Derivativems = 0.0;
    s_bb01_pos_B.HighPassFilterrads = 0.0;
    s_bb01_pos_B.ManualSwitch = 0.0;
    s_bb01_pos_B.ControlOutputms = 0.0;
    s_bb01_pos_B.ProportionalGainradsm = 0.0;
    s_bb01_pos_B.DesiredAngleSaturationrad = 0.0;
    s_bb01_pos_B.VeltoPos_i = 0.0;
    s_bb01_pos_B.PositionErrorrad = 0.0;
    s_bb01_pos_B.ProportionalGainVrad = 0.0;
    s_bb01_pos_B.Highpassfilter = 0.0;
    s_bb01_pos_B.VelocityGainVsrad = 0.0;
    s_bb01_pos_B.ControlOutput = 0.0;
    s_bb01_pos_B.AmplifierSaturationV = 0.0;
    s_bb01_pos_B.InverseAmplifierGainVV = 0.0;
    s_bb01_pos_B.DAQSaturationV = 0.0;
    s_bb01_pos_B.AmplifierGainVV = 0.0;
    s_bb01_pos_B.Gain[0] = 0.0;
    s_bb01_pos_B.Gain[1] = 0.0;
    s_bb01_pos_B.cmm[0] = 0.0;
    s_bb01_pos_B.cmm[1] = 0.0;
    s_bb01_pos_B.theta_ldeg = 0.0;
    s_bb01_pos_B.AcctoVel = 0.0;
    s_bb01_pos_B.TrigonometricFunction = 0.0;
    s_bb01_pos_B.ModelGainms2rad = 0.0;
    s_bb01_pos_B.TransferFcn = 0.0;
    s_bb01_pos_B.t = 0.0;
    s_bb01_pos_B.MultiportSwitch_g = 0.0;
    s_bb01_pos_B.t12f = 0.0;
    s_bb01_pos_B.R0t12f = 0.0;
    s_bb01_pos_B.Sum1 = 0.0;
    s_bb01_pos_B.R0 = 0.0;
    s_bb01_pos_B.Sum = 0.0;
  }

  /* parameters */
  s_bb01_pos_M->defaultParam = ((real_T *)&s_bb01_pos_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &s_bb01_pos_X;
    s_bb01_pos_M->contStates = (x);
    (void) memset((void *)&s_bb01_pos_X, 0,
                  sizeof(X_s_bb01_pos_T));
  }

  /* states (dwork) */
  s_bb01_pos_M->dwork = ((void *) &s_bb01_pos_DW);
  (void) memset((void *)&s_bb01_pos_DW, 0,
                sizeof(DW_s_bb01_pos_T));
  s_bb01_pos_DW.TimeStampA = 0.0;
  s_bb01_pos_DW.LastUAtTimeA = 0.0;
  s_bb01_pos_DW.TimeStampB = 0.0;
  s_bb01_pos_DW.LastUAtTimeB = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    s_bb01_pos_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 18;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  s_bb01_pos_M->Sizes.numContStates = (7);/* Number of continuous states */
  s_bb01_pos_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  s_bb01_pos_M->Sizes.numY = (0);      /* Number of model outputs */
  s_bb01_pos_M->Sizes.numU = (0);      /* Number of model inputs */
  s_bb01_pos_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  s_bb01_pos_M->Sizes.numSampTimes = (2);/* Number of sample times */
  s_bb01_pos_M->Sizes.numBlocks = (55);/* Number of blocks */
  s_bb01_pos_M->Sizes.numBlockIO = (44);/* Number of block outputs */
  s_bb01_pos_M->Sizes.numBlockPrms = (34);/* Sum of parameter "widths" */
  return s_bb01_pos_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
