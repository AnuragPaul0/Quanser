/*
 * q_bb01_pos.c
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
#include "q_bb01_pos_dt.h"

/* Block signals (default storage) */
B_q_bb01_pos_T q_bb01_pos_B;

/* Continuous states */
X_q_bb01_pos_T q_bb01_pos_X;

/* Block states (default storage) */
DW_q_bb01_pos_T q_bb01_pos_DW;

/* Real-time model */
static RT_MODEL_q_bb01_pos_T q_bb01_pos_M_;
RT_MODEL_q_bb01_pos_T *const q_bb01_pos_M = &q_bb01_pos_M_;

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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  q_bb01_pos_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  q_bb01_pos_output();
  q_bb01_pos_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  q_bb01_pos_output();
  q_bb01_pos_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  q_bb01_pos_output();
  q_bb01_pos_derivatives();

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
void q_bb01_pos_output(void)
{
  real_T temp;
  real_T u0;
  real_T u2;
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* set solver stop time */
    if (!(q_bb01_pos_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_bb01_pos_M->solverInfo,
                            ((q_bb01_pos_M->Timing.clockTickH0 + 1) *
        q_bb01_pos_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_bb01_pos_M->solverInfo,
                            ((q_bb01_pos_M->Timing.clockTick0 + 1) *
        q_bb01_pos_M->Timing.stepSize0 + q_bb01_pos_M->Timing.clockTickH0 *
        q_bb01_pos_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_bb01_pos_M)) {
    q_bb01_pos_M->Timing.t[0] = rtsiGetT(&q_bb01_pos_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* S-Function (hil_read_analog_timebase_block): '<S8>/HIL Read Analog Timebase' */

    /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Read Analog Timebase (hil_read_analog_timebase_block) */
    {
      t_error result;
      result = hil_task_read_analog(q_bb01_pos_DW.HILReadAnalogTimebase_Task, 1,
        &q_bb01_pos_DW.HILReadAnalogTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      }

      q_bb01_pos_B.HILReadAnalogTimebase_o1 =
        q_bb01_pos_DW.HILReadAnalogTimebase_Buffer[0];
      q_bb01_pos_B.HILReadAnalogTimebase_o2 =
        q_bb01_pos_DW.HILReadAnalogTimebase_Buffer[1];
    }

    /* RelationalOperator: '<S15>/Compare' incorporates:
     *  Constant: '<S15>/Constant'
     */
    q_bb01_pos_B.Compare_j = (uint8_T)(q_bb01_pos_B.HILReadAnalogTimebase_o1 <
      q_bb01_pos_P.ReadingZero_const);
  }

  /* Clock: '<S13>/Clock' */
  q_bb01_pos_B.Clock = q_bb01_pos_M->Timing.t[0];

  /* RelationalOperator: '<S14>/Compare' incorporates:
   *  Constant: '<S14>/Constant'
   */
  q_bb01_pos_B.Compare = (uint8_T)(q_bb01_pos_B.Clock <
    q_bb01_pos_P.InitialTimes_const);

  /* Logic: '<S13>/Logical Operator' */
  q_bb01_pos_B.LogicalOperator = ((q_bb01_pos_B.Compare != 0) &&
    (q_bb01_pos_B.Compare_j != 0));

  /* MultiPortSwitch: '<S13>/Multiport Switch' */
  if (!q_bb01_pos_B.LogicalOperator) {
    /* MultiPortSwitch: '<S13>/Multiport Switch' */
    q_bb01_pos_B.MultiportSwitch = q_bb01_pos_B.HILReadAnalogTimebase_o1;
  } else {
    /* MultiPortSwitch: '<S13>/Multiport Switch' incorporates:
     *  Constant: '<S13>/Constant'
     */
    q_bb01_pos_B.MultiportSwitch = q_bb01_pos_P.Constant_Value;
  }

  /* End of MultiPortSwitch: '<S13>/Multiport Switch' */

  /* Gain: '<S8>/BB01 Calibration  (m//V)' */
  q_bb01_pos_B.BB01CalibrationmV = q_bb01_pos_P.K_BS *
    q_bb01_pos_B.MultiportSwitch;
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* Gain: '<S8>/SS01 Calibration  (m//V)' */
    q_bb01_pos_B.SS01CalibrationmV = q_bb01_pos_P.K_BS *
      q_bb01_pos_B.HILReadAnalogTimebase_o2;

    /* S-Function (hil_read_encoder_block): '<S8>/HIL Read Encoder' */

    /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(q_bb01_pos_DW.HILInitialize_Card,
        &q_bb01_pos_P.HILReadEncoder_channels, 1,
        &q_bb01_pos_DW.HILReadEncoder_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      } else {
        q_bb01_pos_B.HILReadEncoder = q_bb01_pos_DW.HILReadEncoder_Buffer;
      }
    }

    /* Gain: '<S8>/Encoder Calibration  (rad//count)' */
    q_bb01_pos_B.EncoderCalibrationradcount = q_bb01_pos_P.K_ENC *
      q_bb01_pos_B.HILReadEncoder;

    /* Bias: '<S8>/Bias' */
    q_bb01_pos_B.Bias = q_bb01_pos_B.EncoderCalibrationradcount +
      q_bb01_pos_P.THETA_OFF;
  }

  /* SignalGenerator: '<S7>/Square Wave' */
  temp = q_bb01_pos_P.SRV02SignalGenerator_f * q_bb01_pos_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    /* SignalGenerator: '<S7>/Square Wave' */
    q_bb01_pos_B.SquareWave = q_bb01_pos_P.SRV02SignalGenerator_a;
  } else {
    /* SignalGenerator: '<S7>/Square Wave' */
    q_bb01_pos_B.SquareWave = -q_bb01_pos_P.SRV02SignalGenerator_a;
  }

  /* End of SignalGenerator: '<S7>/Square Wave' */

  /* Clock: '<S11>/Clock' */
  q_bb01_pos_B.Clock_b = q_bb01_pos_M->Timing.t[0];

  /* SignalGenerator: '<S7>/Sine Wave' */
  temp = 6.2831853071795862 * q_bb01_pos_M->Timing.t[0];

  /* SignalGenerator: '<S7>/Sine Wave' */
  q_bb01_pos_B.SineWave = sin(q_bb01_pos_P.SRV02SignalGenerator_f * temp) *
    q_bb01_pos_P.SRV02SignalGenerator_a;

  /* MultiPortSwitch: '<S7>/Multiport Switch' incorporates:
   *  Constant: '<S7>/Constant'
   */
  switch ((int32_T)q_bb01_pos_P.SRV02SignalGenerator_sig_type) {
   case 1:
    /* MultiPortSwitch: '<S7>/Multiport Switch' */
    q_bb01_pos_B.MultiportSwitch_o = q_bb01_pos_B.SquareWave;
    break;

   case 2:
    /* Math: '<S11>/t' incorporates:
     *  Constant: '<S11>/Period (s)'
     */
    temp = 1.0 / q_bb01_pos_P.SRV02SignalGenerator_f;

    /* Math: '<S11>/t' */
    q_bb01_pos_B.t = rt_modd_snf(q_bb01_pos_B.Clock_b, temp);

    /* RelationalOperator: '<S11>/t >= 1//(2*f)?' incorporates:
     *  Constant: '<S11>/Half Period (s)'
     */
    temp = 1.0 / (2.0 * q_bb01_pos_P.SRV02SignalGenerator_f);

    /* RelationalOperator: '<S11>/t >= 1//(2*f)?' */
    q_bb01_pos_B.t12f_m = (q_bb01_pos_B.t >= temp);

    /* MultiPortSwitch: '<S11>/Multiport Switch' */
    if (!q_bb01_pos_B.t12f_m) {
      /* Gain: '<S11>/R0' */
      temp = 4.0 * q_bb01_pos_P.SRV02SignalGenerator_a *
        q_bb01_pos_P.SRV02SignalGenerator_f;

      /* Gain: '<S11>/R0' */
      q_bb01_pos_B.R0 = temp * q_bb01_pos_B.t;

      /* Sum: '<S11>/Sum' incorporates:
       *  Constant: '<S11>/Amplitude'
       */
      q_bb01_pos_B.Sum_p = q_bb01_pos_B.R0 - q_bb01_pos_P.SRV02SignalGenerator_a;

      /* MultiPortSwitch: '<S11>/Multiport Switch' */
      q_bb01_pos_B.MultiportSwitch_c = q_bb01_pos_B.Sum_p;
    } else {
      /* Sum: '<S11>/t-1//(2*f)' incorporates:
       *  Constant: '<S11>/Half Period (s)'
       */
      temp = 1.0 / (2.0 * q_bb01_pos_P.SRV02SignalGenerator_f);

      /* Sum: '<S11>/t-1//(2*f)' */
      q_bb01_pos_B.t12f = q_bb01_pos_B.t - temp;

      /* Gain: '<S11>/-R0*(t-1//(2*f))' */
      temp = -4.0 * q_bb01_pos_P.SRV02SignalGenerator_a *
        q_bb01_pos_P.SRV02SignalGenerator_f;

      /* Gain: '<S11>/-R0*(t-1//(2*f))' */
      q_bb01_pos_B.R0t12f = temp * q_bb01_pos_B.t12f;

      /* Sum: '<S11>/Sum1' incorporates:
       *  Constant: '<S11>/Amplitude'
       */
      q_bb01_pos_B.Sum1 = q_bb01_pos_P.SRV02SignalGenerator_a +
        q_bb01_pos_B.R0t12f;

      /* MultiPortSwitch: '<S11>/Multiport Switch' */
      q_bb01_pos_B.MultiportSwitch_c = q_bb01_pos_B.Sum1;
    }

    /* End of MultiPortSwitch: '<S11>/Multiport Switch' */

    /* MultiPortSwitch: '<S7>/Multiport Switch' */
    q_bb01_pos_B.MultiportSwitch_o = q_bb01_pos_B.MultiportSwitch_c;
    break;

   default:
    /* MultiPortSwitch: '<S7>/Multiport Switch' */
    q_bb01_pos_B.MultiportSwitch_o = q_bb01_pos_B.SineWave;
    break;
  }

  /* End of MultiPortSwitch: '<S7>/Multiport Switch' */

  /* Gain: '<S1>/Slider Gain' */
  q_bb01_pos_B.SliderGain = q_bb01_pos_P.Amplitudecm_gain *
    q_bb01_pos_B.MultiportSwitch_o;
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* Gain: '<S3>/Slider Gain' incorporates:
     *  Constant: '<Root>/Constant '
     */
    q_bb01_pos_B.SliderGain_n = q_bb01_pos_P.Constantcm_gain *
      q_bb01_pos_P.Constant_Value_a;
  }

  /* ManualSwitch: '<Root>/Setpoint Source' */
  if (q_bb01_pos_P.SetpointSource_CurrentSetting == 1) {
    /* Sum: '<Root>/Setpoint (cm)' */
    q_bb01_pos_B.Setpointcm = q_bb01_pos_B.SliderGain +
      q_bb01_pos_B.SliderGain_n;

    /* Gain: '<Root>/Setpoint (m)' */
    q_bb01_pos_B.Setpointm = q_bb01_pos_P.Setpointm_Gain *
      q_bb01_pos_B.Setpointcm;

    /* ManualSwitch: '<Root>/Setpoint Source' */
    q_bb01_pos_B.SetpointSource = q_bb01_pos_B.Setpointm;
  } else {
    /* ManualSwitch: '<Root>/Setpoint Source' */
    q_bb01_pos_B.SetpointSource = q_bb01_pos_B.SS01CalibrationmV;
  }

  /* End of ManualSwitch: '<Root>/Setpoint Source' */

  /* Sum: '<S2>/Position Error (m)' */
  q_bb01_pos_B.PositionErrorm = q_bb01_pos_B.SetpointSource -
    q_bb01_pos_B.BB01CalibrationmV;

  /* Gain: '<S2>/Zero Location (m.rad//s)' */
  q_bb01_pos_B.ZeroLocationmrads = q_bb01_pos_P.z * q_bb01_pos_B.PositionErrorm;

  /* Gain: '<S10>/Slider Gain' */
  q_bb01_pos_B.SliderGain_j = q_bb01_pos_P.SetPointWeight_gain *
    q_bb01_pos_B.BB01CalibrationmV;

  /* Sum: '<S2>/Weighed Position Error (m)' */
  q_bb01_pos_B.WeighedPositionErrorm = q_bb01_pos_B.SliderGain_j -
    q_bb01_pos_B.BB01CalibrationmV;

  /* TransferFcn: '<S2>/High-Pass Filter (m//s)' */
  q_bb01_pos_B.HighPassFilterms = 0.0;
  q_bb01_pos_B.HighPassFilterms += q_bb01_pos_P.HighPassFilterms_C *
    q_bb01_pos_X.HighPassFilterms_CSTATE;
  q_bb01_pos_B.HighPassFilterms += q_bb01_pos_P.HighPassFilterms_D *
    q_bb01_pos_B.WeighedPositionErrorm;

  /* Sum: '<S2>/Control  Output' */
  q_bb01_pos_B.ControlOutput = q_bb01_pos_B.ZeroLocationmrads +
    q_bb01_pos_B.HighPassFilterms;

  /* Gain: '<S2>/Proportional Gain ' */
  q_bb01_pos_B.ProportionalGain = q_bb01_pos_P.Kc * q_bb01_pos_B.ControlOutput;

  /* Integrator: '<S2>/Integrator' */
  /* Limited  Integrator  */
  if (q_bb01_pos_X.Integrator_CSTATE >= q_bb01_pos_P.THETA_MAX) {
    q_bb01_pos_X.Integrator_CSTATE = q_bb01_pos_P.THETA_MAX;
  } else if (q_bb01_pos_X.Integrator_CSTATE <= q_bb01_pos_P.THETA_MIN) {
    q_bb01_pos_X.Integrator_CSTATE = q_bb01_pos_P.THETA_MIN;
  }

  /* Integrator: '<S2>/Integrator' */
  q_bb01_pos_B.Integrator = q_bb01_pos_X.Integrator_CSTATE;

  /* Sum: '<S2>/Sum' */
  q_bb01_pos_B.Sum = q_bb01_pos_B.ProportionalGain + q_bb01_pos_B.Integrator;

  /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
  u0 = q_bb01_pos_B.Sum;
  temp = q_bb01_pos_P.THETA_MIN;
  u2 = q_bb01_pos_P.THETA_MAX;
  if (u0 > u2) {
    /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
    q_bb01_pos_B.DesiredAngleSaturationrad = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
    q_bb01_pos_B.DesiredAngleSaturationrad = temp;
  } else {
    /* Saturate: '<S2>/Desired Angle  Saturation (rad)' */
    q_bb01_pos_B.DesiredAngleSaturationrad = u0;
  }

  /* End of Saturate: '<S2>/Desired Angle  Saturation (rad)' */

  /* Sum: '<S6>/Position Error (rad)' */
  q_bb01_pos_B.PositionErrorrad = q_bb01_pos_B.DesiredAngleSaturationrad -
    q_bb01_pos_B.Bias;

  /* Gain: '<S6>/Proportional Gain  (V//rad)' */
  q_bb01_pos_B.ProportionalGainVrad = q_bb01_pos_P.kp *
    q_bb01_pos_B.PositionErrorrad;

  /* TransferFcn: '<S6>/High-pass filter' */
  q_bb01_pos_B.Highpassfilter = 0.0;
  q_bb01_pos_B.Highpassfilter += q_bb01_pos_P.Highpassfilter_C[0] *
    q_bb01_pos_X.Highpassfilter_CSTATE[0];
  q_bb01_pos_B.Highpassfilter += q_bb01_pos_P.Highpassfilter_C[1] *
    q_bb01_pos_X.Highpassfilter_CSTATE[1];

  /* Gain: '<S6>/Velocity Gain  (V.s//rad)' */
  q_bb01_pos_B.VelocityGainVsrad = q_bb01_pos_P.kv * q_bb01_pos_B.Highpassfilter;

  /* Sum: '<S6>/Control  Output' */
  q_bb01_pos_B.ControlOutput_m = q_bb01_pos_B.ProportionalGainVrad +
    q_bb01_pos_B.VelocityGainVsrad;

  /* Gain: '<S12>/Direction Convention: (Right-Hand) system' */
  q_bb01_pos_B.DirectionConventionRightHandsys =
    q_bb01_pos_P.DirectionConventionRightHandsys * q_bb01_pos_B.ControlOutput_m;

  /* Saturate: '<S12>/Amplifier  Saturation (V)' */
  temp = -q_bb01_pos_P.VMAX_AMP;
  u0 = q_bb01_pos_B.DirectionConventionRightHandsys;
  u2 = q_bb01_pos_P.VMAX_AMP;
  if (u0 > u2) {
    /* Saturate: '<S12>/Amplifier  Saturation (V)' */
    q_bb01_pos_B.AmplifierSaturationV = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S12>/Amplifier  Saturation (V)' */
    q_bb01_pos_B.AmplifierSaturationV = temp;
  } else {
    /* Saturate: '<S12>/Amplifier  Saturation (V)' */
    q_bb01_pos_B.AmplifierSaturationV = u0;
  }

  /* End of Saturate: '<S12>/Amplifier  Saturation (V)' */

  /* Gain: '<S12>/Inverse Amplifier  Gain (V//V)' */
  temp = 1.0 / q_bb01_pos_P.K_AMP;

  /* Gain: '<S12>/Inverse Amplifier  Gain (V//V)' */
  q_bb01_pos_B.InverseAmplifierGainVV = temp * q_bb01_pos_B.AmplifierSaturationV;

  /* Saturate: '<S12>/DACB Saturation (V)' */
  temp = -q_bb01_pos_P.VMAX_DAC;
  u0 = q_bb01_pos_B.InverseAmplifierGainVV;
  u2 = q_bb01_pos_P.VMAX_DAC;
  if (u0 > u2) {
    /* Saturate: '<S12>/DACB Saturation (V)' */
    q_bb01_pos_B.DACBSaturationV = u2;
  } else if (u0 < temp) {
    /* Saturate: '<S12>/DACB Saturation (V)' */
    q_bb01_pos_B.DACBSaturationV = temp;
  } else {
    /* Saturate: '<S12>/DACB Saturation (V)' */
    q_bb01_pos_B.DACBSaturationV = u0;
  }

  /* End of Saturate: '<S12>/DACB Saturation (V)' */
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* S-Function (hil_write_analog_block): '<S8>/HIL Write Analog' */

    /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(q_bb01_pos_DW.HILInitialize_Card,
        &q_bb01_pos_P.HILWriteAnalog_channels, 1, &q_bb01_pos_B.DACBSaturationV);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<S12>/Amplifier  Gain (V//V)' */
  temp = -q_bb01_pos_P.K_AMP;

  /* Gain: '<S12>/Amplifier  Gain (V//V)' */
  q_bb01_pos_B.AmplifierGainVV = temp * q_bb01_pos_B.DACBSaturationV;
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* S-Function (hil_write_digital_block): '<S8>/HIL Write Digital' incorporates:
     *  Constant: '<S8>/Enable VoltPAQ-X2,X4'
     */

    /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Write Digital (hil_write_digital_block) */
    {
      t_error result;
      q_bb01_pos_DW.HILWriteDigital_Buffer[0] =
        (q_bb01_pos_P.EnableVoltPAQX2X4_Value[0] != 0);
      q_bb01_pos_DW.HILWriteDigital_Buffer[1] =
        (q_bb01_pos_P.EnableVoltPAQX2X4_Value[1] != 0);
      q_bb01_pos_DW.HILWriteDigital_Buffer[2] =
        (q_bb01_pos_P.EnableVoltPAQX2X4_Value[2] != 0);
      q_bb01_pos_DW.HILWriteDigital_Buffer[3] =
        (q_bb01_pos_P.EnableVoltPAQX2X4_Value[3] != 0);
      result = hil_write_digital(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILWriteDigital_channels, 4,
        &q_bb01_pos_DW.HILWriteDigital_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      }
    }
  }

  /* Gain: '<S5>/Gain' */
  q_bb01_pos_B.Gain[0] = q_bb01_pos_P.Gain_Gain *
    q_bb01_pos_B.DesiredAngleSaturationrad;
  q_bb01_pos_B.Gain[1] = q_bb01_pos_P.Gain_Gain * q_bb01_pos_B.Bias;
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
  }

  /* Gain: '<Root>/cm//m' */
  q_bb01_pos_B.cmm[0] = q_bb01_pos_P.cmm_Gain * q_bb01_pos_B.SetpointSource;
  q_bb01_pos_B.cmm[1] = q_bb01_pos_P.cmm_Gain * q_bb01_pos_B.BB01CalibrationmV;
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    /* Gain: '<S6>/-theta_l (deg)' */
    q_bb01_pos_B.theta_ldeg = q_bb01_pos_P.theta_ldeg_Gain * q_bb01_pos_B.Bias;
  }

  /* Gain: '<S9>/Slider Gain' */
  q_bb01_pos_B.SliderGain_c = q_bb01_pos_P.IntegralGainradms_gain *
    q_bb01_pos_B.PositionErrorm;
}

/* Model update function */
void q_bb01_pos_update(void)
{
  if (rtmIsMajorTimeStep(q_bb01_pos_M)) {
    rt_ertODEUpdateContinuousStates(&q_bb01_pos_M->solverInfo);
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
  if (!(++q_bb01_pos_M->Timing.clockTick0)) {
    ++q_bb01_pos_M->Timing.clockTickH0;
  }

  q_bb01_pos_M->Timing.t[0] = rtsiGetSolverStopTime(&q_bb01_pos_M->solverInfo);

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
    if (!(++q_bb01_pos_M->Timing.clockTick1)) {
      ++q_bb01_pos_M->Timing.clockTickH1;
    }

    q_bb01_pos_M->Timing.t[1] = q_bb01_pos_M->Timing.clockTick1 *
      q_bb01_pos_M->Timing.stepSize1 + q_bb01_pos_M->Timing.clockTickH1 *
      q_bb01_pos_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_bb01_pos_derivatives(void)
{
  XDot_q_bb01_pos_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_q_bb01_pos_T *) q_bb01_pos_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/High-Pass Filter (m//s)' */
  _rtXdot->HighPassFilterms_CSTATE = 0.0;
  _rtXdot->HighPassFilterms_CSTATE += q_bb01_pos_P.HighPassFilterms_A *
    q_bb01_pos_X.HighPassFilterms_CSTATE;
  _rtXdot->HighPassFilterms_CSTATE += q_bb01_pos_B.WeighedPositionErrorm;

  /* Derivatives for Integrator: '<S2>/Integrator' */
  lsat = (q_bb01_pos_X.Integrator_CSTATE <= q_bb01_pos_P.THETA_MIN);
  usat = (q_bb01_pos_X.Integrator_CSTATE >= q_bb01_pos_P.THETA_MAX);
  if (((!lsat) && (!usat)) || (lsat && (q_bb01_pos_B.SliderGain_c > 0.0)) ||
      (usat && (q_bb01_pos_B.SliderGain_c < 0.0))) {
    _rtXdot->Integrator_CSTATE = q_bb01_pos_B.SliderGain_c;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S2>/Integrator' */

  /* Derivatives for TransferFcn: '<S6>/High-pass filter' */
  _rtXdot->Highpassfilter_CSTATE[0] = 0.0;
  _rtXdot->Highpassfilter_CSTATE[0] += q_bb01_pos_P.Highpassfilter_A[0] *
    q_bb01_pos_X.Highpassfilter_CSTATE[0];
  _rtXdot->Highpassfilter_CSTATE[1] = 0.0;
  _rtXdot->Highpassfilter_CSTATE[0] += q_bb01_pos_P.Highpassfilter_A[1] *
    q_bb01_pos_X.Highpassfilter_CSTATE[1];
  _rtXdot->Highpassfilter_CSTATE[1] += q_bb01_pos_X.Highpassfilter_CSTATE[0];
  _rtXdot->Highpassfilter_CSTATE[0] += q_bb01_pos_B.theta_ldeg;
}

/* Model initialize function */
void q_bb01_pos_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S8>/HIL Initialize' */

  /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &q_bb01_pos_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(q_bb01_pos_DW.HILInitialize_Card,
      "update_rate=normal", 19);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(q_bb01_pos_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      return;
    }

    if ((q_bb01_pos_P.HILInitialize_AIPStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &q_bb01_pos_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (q_bb01_pos_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &q_bb01_pos_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = q_bb01_pos_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_AIChannels, 8U,
        &q_bb01_pos_DW.HILInitialize_AIMinimums[0],
        &q_bb01_pos_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if ((q_bb01_pos_P.HILInitialize_AOPStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &q_bb01_pos_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (q_bb01_pos_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &q_bb01_pos_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = q_bb01_pos_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_AOChannels, 8U,
        &q_bb01_pos_DW.HILInitialize_AOMinimums[0],
        &q_bb01_pos_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if ((q_bb01_pos_P.HILInitialize_AOStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &q_bb01_pos_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_bb01_pos_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_AOChannels, 8U,
        &q_bb01_pos_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if (q_bb01_pos_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &q_bb01_pos_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_bb01_pos_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (q_bb01_pos_DW.HILInitialize_Card, q_bb01_pos_P.HILInitialize_AOChannels,
         8U, &q_bb01_pos_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(q_bb01_pos_DW.HILInitialize_Card, NULL,
      0U, q_bb01_pos_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
      return;
    }

    if ((q_bb01_pos_P.HILInitialize_DOStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &q_bb01_pos_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = q_bb01_pos_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &q_bb01_pos_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if (q_bb01_pos_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &q_bb01_pos_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = q_bb01_pos_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (q_bb01_pos_DW.HILInitialize_Card, q_bb01_pos_P.HILInitialize_DOChannels,
         8U, (const t_digital_state *) &q_bb01_pos_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if ((q_bb01_pos_P.HILInitialize_EIPStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &q_bb01_pos_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = q_bb01_pos_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &q_bb01_pos_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if ((q_bb01_pos_P.HILInitialize_EIStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &q_bb01_pos_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = q_bb01_pos_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_EIChannels, 8U,
        &q_bb01_pos_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if ((q_bb01_pos_P.HILInitialize_POPStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &q_bb01_pos_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = q_bb01_pos_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &q_bb01_pos_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          q_bb01_pos_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &q_bb01_pos_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            q_bb01_pos_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            q_bb01_pos_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              q_bb01_pos_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            q_bb01_pos_DW.HILInitialize_POSortedChans[7U - num_frequency_modes] =
              (p_HILInitialize_POChannels[i1]);
            q_bb01_pos_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes] =
              q_bb01_pos_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(q_bb01_pos_DW.HILInitialize_Card,
          &q_bb01_pos_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &q_bb01_pos_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(q_bb01_pos_DW.HILInitialize_Card,
          &q_bb01_pos_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &q_bb01_pos_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &q_bb01_pos_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = q_bb01_pos_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &q_bb01_pos_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = q_bb01_pos_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &q_bb01_pos_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = q_bb01_pos_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &q_bb01_pos_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &q_bb01_pos_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &q_bb01_pos_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &q_bb01_pos_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = q_bb01_pos_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &q_bb01_pos_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_bb01_pos_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_POChannels, 8U,
        &q_bb01_pos_DW.HILInitialize_POSortedFreqs[0],
        &q_bb01_pos_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if ((q_bb01_pos_P.HILInitialize_POStart && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &q_bb01_pos_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_bb01_pos_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(q_bb01_pos_DW.HILInitialize_Card,
        q_bb01_pos_P.HILInitialize_POChannels, 8U,
        &q_bb01_pos_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }

    if (q_bb01_pos_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &q_bb01_pos_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_bb01_pos_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (q_bb01_pos_DW.HILInitialize_Card, q_bb01_pos_P.HILInitialize_POChannels,
         8U, &q_bb01_pos_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_analog_timebase_block): '<S8>/HIL Read Analog Timebase' */

  /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Read Analog Timebase (hil_read_analog_timebase_block) */
  {
    t_error result;
    result = hil_task_create_analog_reader(q_bb01_pos_DW.HILInitialize_Card,
      q_bb01_pos_P.HILReadAnalogTimebase_SamplesIn,
      q_bb01_pos_P.HILReadAnalogTimebase_Channels, 2,
      &q_bb01_pos_DW.HILReadAnalogTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (q_bb01_pos_DW.HILReadAnalogTimebase_Task, (t_buffer_overflow_mode)
         (q_bb01_pos_P.HILReadAnalogTimebase_OverflowM - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
    }
  }

  /* InitializeConditions for TransferFcn: '<S2>/High-Pass Filter (m//s)' */
  q_bb01_pos_X.HighPassFilterms_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  q_bb01_pos_X.Integrator_CSTATE = q_bb01_pos_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<S6>/High-pass filter' */
  q_bb01_pos_X.Highpassfilter_CSTATE[0] = 0.0;
  q_bb01_pos_X.Highpassfilter_CSTATE[1] = 0.0;
}

/* Model terminate function */
void q_bb01_pos_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S8>/HIL Initialize' */

  /* S-Function Block: q_bb01_pos/SRV02-ET+BB01/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(q_bb01_pos_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_bb01_pos_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_bb01_pos_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &q_bb01_pos_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = q_bb01_pos_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((q_bb01_pos_P.HILInitialize_DOTerminate && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &q_bb01_pos_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = q_bb01_pos_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 8U;
    } else {
      num_final_digital_outputs = 0;
    }

    if ((q_bb01_pos_P.HILInitialize_POTerminate && !is_switching) ||
        (q_bb01_pos_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &q_bb01_pos_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = q_bb01_pos_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        || num_final_digital_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(q_bb01_pos_DW.HILInitialize_Card
                         , q_bb01_pos_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , q_bb01_pos_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , q_bb01_pos_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &q_bb01_pos_DW.HILInitialize_AOVoltages[0]
                         , &q_bb01_pos_DW.HILInitialize_POValues[0]
                         , (t_boolean *) &q_bb01_pos_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(q_bb01_pos_DW.HILInitialize_Card,
            q_bb01_pos_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &q_bb01_pos_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(q_bb01_pos_DW.HILInitialize_Card,
            q_bb01_pos_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &q_bb01_pos_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital(q_bb01_pos_DW.HILInitialize_Card,
            q_bb01_pos_P.HILInitialize_DOChannels, num_final_digital_outputs,
            (t_boolean *) &q_bb01_pos_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_bb01_pos_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_bb01_pos_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_bb01_pos_DW.HILInitialize_Card);
    hil_close(q_bb01_pos_DW.HILInitialize_Card);
    q_bb01_pos_DW.HILInitialize_Card = NULL;
  }
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
  q_bb01_pos_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_bb01_pos_update();
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
  q_bb01_pos_initialize();
}

void MdlTerminate(void)
{
  q_bb01_pos_terminate();
}

/* Registration function */
RT_MODEL_q_bb01_pos_T *q_bb01_pos(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_bb01_pos_M, 0,
                sizeof(RT_MODEL_q_bb01_pos_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_bb01_pos_M->solverInfo,
                          &q_bb01_pos_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_bb01_pos_M->solverInfo, &rtmGetTPtr(q_bb01_pos_M));
    rtsiSetStepSizePtr(&q_bb01_pos_M->solverInfo,
                       &q_bb01_pos_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_bb01_pos_M->solverInfo, &q_bb01_pos_M->derivs);
    rtsiSetContStatesPtr(&q_bb01_pos_M->solverInfo, (real_T **)
                         &q_bb01_pos_M->contStates);
    rtsiSetNumContStatesPtr(&q_bb01_pos_M->solverInfo,
      &q_bb01_pos_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&q_bb01_pos_M->solverInfo,
      &q_bb01_pos_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&q_bb01_pos_M->solverInfo,
      &q_bb01_pos_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&q_bb01_pos_M->solverInfo,
      &q_bb01_pos_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&q_bb01_pos_M->solverInfo, (&rtmGetErrorStatus
      (q_bb01_pos_M)));
    rtsiSetRTModelPtr(&q_bb01_pos_M->solverInfo, q_bb01_pos_M);
  }

  rtsiSetSimTimeStep(&q_bb01_pos_M->solverInfo, MAJOR_TIME_STEP);
  q_bb01_pos_M->intgData.y = q_bb01_pos_M->odeY;
  q_bb01_pos_M->intgData.f[0] = q_bb01_pos_M->odeF[0];
  q_bb01_pos_M->intgData.f[1] = q_bb01_pos_M->odeF[1];
  q_bb01_pos_M->intgData.f[2] = q_bb01_pos_M->odeF[2];
  q_bb01_pos_M->intgData.f[3] = q_bb01_pos_M->odeF[3];
  q_bb01_pos_M->contStates = ((real_T *) &q_bb01_pos_X);
  rtsiSetSolverData(&q_bb01_pos_M->solverInfo, (void *)&q_bb01_pos_M->intgData);
  rtsiSetSolverName(&q_bb01_pos_M->solverInfo,"ode4");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_bb01_pos_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "q_bb01_pos_M points to
       static memory which is guaranteed to be non-NULL" */
    q_bb01_pos_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_bb01_pos_M->Timing.sampleTimes = (&q_bb01_pos_M->Timing.sampleTimesArray[0]);
    q_bb01_pos_M->Timing.offsetTimes = (&q_bb01_pos_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_bb01_pos_M->Timing.sampleTimes[0] = (0.0);
    q_bb01_pos_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    q_bb01_pos_M->Timing.offsetTimes[0] = (0.0);
    q_bb01_pos_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_bb01_pos_M, &q_bb01_pos_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_bb01_pos_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_bb01_pos_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_bb01_pos_M, -1);
  q_bb01_pos_M->Timing.stepSize0 = 0.002;
  q_bb01_pos_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  q_bb01_pos_M->Sizes.checksums[0] = (3976318285U);
  q_bb01_pos_M->Sizes.checksums[1] = (3128140556U);
  q_bb01_pos_M->Sizes.checksums[2] = (1107914424U);
  q_bb01_pos_M->Sizes.checksums[3] = (2240706940U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    q_bb01_pos_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_bb01_pos_M->extModeInfo,
      &q_bb01_pos_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_bb01_pos_M->extModeInfo, q_bb01_pos_M->Sizes.checksums);
    rteiSetTPtr(q_bb01_pos_M->extModeInfo, rtmGetTPtr(q_bb01_pos_M));
  }

  q_bb01_pos_M->solverInfoPtr = (&q_bb01_pos_M->solverInfo);
  q_bb01_pos_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_bb01_pos_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_bb01_pos_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_bb01_pos_M->blockIO = ((void *) &q_bb01_pos_B);
  (void) memset(((void *) &q_bb01_pos_B), 0,
                sizeof(B_q_bb01_pos_T));

  {
    q_bb01_pos_B.HILReadAnalogTimebase_o1 = 0.0;
    q_bb01_pos_B.HILReadAnalogTimebase_o2 = 0.0;
    q_bb01_pos_B.Clock = 0.0;
    q_bb01_pos_B.MultiportSwitch = 0.0;
    q_bb01_pos_B.BB01CalibrationmV = 0.0;
    q_bb01_pos_B.SS01CalibrationmV = 0.0;
    q_bb01_pos_B.HILReadEncoder = 0.0;
    q_bb01_pos_B.EncoderCalibrationradcount = 0.0;
    q_bb01_pos_B.Bias = 0.0;
    q_bb01_pos_B.SquareWave = 0.0;
    q_bb01_pos_B.Clock_b = 0.0;
    q_bb01_pos_B.SineWave = 0.0;
    q_bb01_pos_B.MultiportSwitch_o = 0.0;
    q_bb01_pos_B.SliderGain = 0.0;
    q_bb01_pos_B.SliderGain_n = 0.0;
    q_bb01_pos_B.SetpointSource = 0.0;
    q_bb01_pos_B.PositionErrorm = 0.0;
    q_bb01_pos_B.ZeroLocationmrads = 0.0;
    q_bb01_pos_B.SliderGain_j = 0.0;
    q_bb01_pos_B.WeighedPositionErrorm = 0.0;
    q_bb01_pos_B.HighPassFilterms = 0.0;
    q_bb01_pos_B.ControlOutput = 0.0;
    q_bb01_pos_B.ProportionalGain = 0.0;
    q_bb01_pos_B.Integrator = 0.0;
    q_bb01_pos_B.Sum = 0.0;
    q_bb01_pos_B.DesiredAngleSaturationrad = 0.0;
    q_bb01_pos_B.PositionErrorrad = 0.0;
    q_bb01_pos_B.ProportionalGainVrad = 0.0;
    q_bb01_pos_B.Highpassfilter = 0.0;
    q_bb01_pos_B.VelocityGainVsrad = 0.0;
    q_bb01_pos_B.ControlOutput_m = 0.0;
    q_bb01_pos_B.DirectionConventionRightHandsys = 0.0;
    q_bb01_pos_B.AmplifierSaturationV = 0.0;
    q_bb01_pos_B.InverseAmplifierGainVV = 0.0;
    q_bb01_pos_B.DACBSaturationV = 0.0;
    q_bb01_pos_B.AmplifierGainVV = 0.0;
    q_bb01_pos_B.Gain[0] = 0.0;
    q_bb01_pos_B.Gain[1] = 0.0;
    q_bb01_pos_B.cmm[0] = 0.0;
    q_bb01_pos_B.cmm[1] = 0.0;
    q_bb01_pos_B.SliderGain_c = 0.0;
    q_bb01_pos_B.theta_ldeg = 0.0;
    q_bb01_pos_B.Setpointcm = 0.0;
    q_bb01_pos_B.Setpointm = 0.0;
    q_bb01_pos_B.t = 0.0;
    q_bb01_pos_B.MultiportSwitch_c = 0.0;
    q_bb01_pos_B.t12f = 0.0;
    q_bb01_pos_B.R0t12f = 0.0;
    q_bb01_pos_B.Sum1 = 0.0;
    q_bb01_pos_B.R0 = 0.0;
    q_bb01_pos_B.Sum_p = 0.0;
  }

  /* parameters */
  q_bb01_pos_M->defaultParam = ((real_T *)&q_bb01_pos_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_bb01_pos_X;
    q_bb01_pos_M->contStates = (x);
    (void) memset((void *)&q_bb01_pos_X, 0,
                  sizeof(X_q_bb01_pos_T));
  }

  /* states (dwork) */
  q_bb01_pos_M->dwork = ((void *) &q_bb01_pos_DW);
  (void) memset((void *)&q_bb01_pos_DW, 0,
                sizeof(DW_q_bb01_pos_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      q_bb01_pos_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  q_bb01_pos_DW.HILReadAnalogTimebase_Buffer[0] = 0.0;
  q_bb01_pos_DW.HILReadAnalogTimebase_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_bb01_pos_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_bb01_pos_M->Sizes.numContStates = (4);/* Number of continuous states */
  q_bb01_pos_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  q_bb01_pos_M->Sizes.numY = (0);      /* Number of model outputs */
  q_bb01_pos_M->Sizes.numU = (0);      /* Number of model inputs */
  q_bb01_pos_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_bb01_pos_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_bb01_pos_M->Sizes.numBlocks = (71);/* Number of blocks */
  q_bb01_pos_M->Sizes.numBlockIO = (53);/* Number of block outputs */
  q_bb01_pos_M->Sizes.numBlockPrms = (158);/* Sum of parameter "widths" */
  return q_bb01_pos_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
