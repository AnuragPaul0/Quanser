/*
 * bb01_quick_start.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "bb01_quick_start".
 *
 * Model version              : 1.25
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Sun May 21 23:22:19 2023
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bb01_quick_start.h"
#include "bb01_quick_start_private.h"
#include "bb01_quick_start_dt.h"

/* Block signals (default storage) */
B_bb01_quick_start_T bb01_quick_start_B;

/* Block states (default storage) */
DW_bb01_quick_start_T bb01_quick_start_DW;

/* Real-time model */
static RT_MODEL_bb01_quick_start_T bb01_quick_start_M_;
RT_MODEL_bb01_quick_start_T *const bb01_quick_start_M = &bb01_quick_start_M_;

/* Model output function */
void bb01_quick_start_output(void)
{
  /* local block i/o variables */
  real_T rtb_BB01CalibrationmV;
  real_T rtb_SS01CalibrationmV;
  real_T rtb_Subtract56deg;
  real_T rtb_Saturation;
  real_T rtb_Sum;

  /* S-Function (hil_read_timebase_block): '<Root>/HIL Read Timebase' */

  /* S-Function Block: bb01_quick_start/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_read(bb01_quick_start_DW.HILReadTimebase_Task, 1,
      &bb01_quick_start_DW.HILReadTimebase_AnalogBuffer[0],
      &bb01_quick_start_DW.HILReadTimebase_EncoderBuffer,
      NULL,
      NULL
      );
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
    } else {
      rtb_BB01CalibrationmV = bb01_quick_start_DW.HILReadTimebase_AnalogBuffer[0];
      rtb_SS01CalibrationmV = bb01_quick_start_DW.HILReadTimebase_AnalogBuffer[1];
      rtb_Subtract56deg = bb01_quick_start_DW.HILReadTimebase_EncoderBuffer;
    }
  }

  /* S-Function (smooth_signal_generator_block): '<Root>/Smooth Signal Generator' */
  /* S-Function Block: bb01_quick_start/Smooth Signal Generator (smooth_signal_generator_block) */
  {
    real_T w = TWO_PI * bb01_quick_start_P.SmoothSignalGenerator_Frequency;
    boolean_T params_changed =
      (bb01_quick_start_P.SmoothSignalGenerator_Amplitude !=
       bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp || w !=
       bb01_quick_start_DW.SmoothSignalGenerator_RWORK.W);
    real_T T = TWO_PI / bb01_quick_start_DW.SmoothSignalGenerator_RWORK.W;
    if (bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T < 0.5 * T) {
      rtb_Saturation = bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp;
    } else {
      rtb_Saturation = -bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp;
    }

    /*
       If the amplitude or frequency parameter changes, then adjust the
       square wave parameters such that the square wave output is continuous.
     */
    if (params_changed) {
      /*
         Change the amplitude or frequency when the sign of the output
         changes. This technique ensures that we don't get intermediate
         jumps in amplitude and we don't get higher frequencies than
         expected due to a pulse being prematurely truncated.
       */
      if (bb01_quick_start_P.SmoothSignalGenerator_Amplitude == 0 ||
          rtb_Saturation == 0 ||
          bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Y == 0 ||
          (rtb_Saturation < 0) !=
          (bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Y < 0)) {
        bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp =
          bb01_quick_start_P.SmoothSignalGenerator_Amplitude;
        bb01_quick_start_DW.SmoothSignalGenerator_RWORK.W = w;
        T = TWO_PI / w;
        if (rtb_Saturation >= 0) {
          bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T = 0;
          rtb_Saturation = bb01_quick_start_P.SmoothSignalGenerator_Amplitude;
        } else {
          bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T = T / 2;
          rtb_Saturation = -bb01_quick_start_P.SmoothSignalGenerator_Amplitude;
        }
      }
    }

    bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T += 0.002;
    if (bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T >= T) {
      bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T = 0;
    }

    bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Y = rtb_Saturation;
  }

  /* Gain: '<Root>/SS01 Calibration  (m//V)' */
  rtb_SS01CalibrationmV *= bb01_quick_start_P.SS01CalibrationmV_Gain;

  /* ManualSwitch: '<Root>/S.P. Source' */
  if (bb01_quick_start_P.SPSource_CurrentSetting == 1) {
    /* Saturate: '<Root>/Saturation' incorporates:
     *  Gain: '<Root>/Setpoint (m)'
     *  Gain: '<S1>/Slider Gain'
     */
    rtb_Saturation = bb01_quick_start_P.Amplitudecm_gain * rtb_Saturation *
      bb01_quick_start_P.Setpointm_Gain;
  } else {
    /* Saturate: '<Root>/Saturation' */
    rtb_Saturation = rtb_SS01CalibrationmV;
  }

  /* End of ManualSwitch: '<Root>/S.P. Source' */

  /* Gain: '<Root>/BB01 Calibration  (m//V)' */
  rtb_BB01CalibrationmV *= bb01_quick_start_P.BB01CalibrationmV_Gain;

  /* Gain: '<Root>/m to cm' */
  bb01_quick_start_B.mtocm[0] = bb01_quick_start_P.mtocm_Gain * rtb_Saturation;
  bb01_quick_start_B.mtocm[1] = bb01_quick_start_P.mtocm_Gain *
    rtb_BB01CalibrationmV;

  /* Sum: '<Root>/Sum' */
  rtb_Sum = rtb_Saturation - rtb_BB01CalibrationmV;

  /* DiscreteTransferFcn: '<S2>/Discrete Transfer Fcn' incorporates:
   *  Gain: '<Root>/Neg Fdbk'
   */
  bb01_quick_start_DW.DiscreteTransferFcn_tmp = (bb01_quick_start_P.NegFdbk_Gain
    * rtb_BB01CalibrationmV - bb01_quick_start_P.DiscreteTransferFcn_DenCoef[1] *
    bb01_quick_start_DW.DiscreteTransferFcn_states) /
    bb01_quick_start_P.DiscreteTransferFcn_DenCoef[0];

  /* Saturate: '<Root>/Saturation' incorporates:
   *  DiscreteTransferFcn: '<S2>/Discrete Transfer Fcn'
   *  Gain: '<Root>/Derivative Gain'
   *  Gain: '<Root>/Proportional Gain'
   *  Sum: '<Root>/Add'
   */
  rtb_Saturation = bb01_quick_start_P.DiscreteTransferFcn_NumCoef[0] *
    bb01_quick_start_DW.DiscreteTransferFcn_tmp +
    bb01_quick_start_P.DiscreteTransferFcn_NumCoef[1] *
    bb01_quick_start_DW.DiscreteTransferFcn_states;
  rtb_Saturation = bb01_quick_start_P.ProportionalGain_Gain * rtb_Sum +
    bb01_quick_start_P.DerivativeGain_Gain * rtb_Saturation;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_Saturation > bb01_quick_start_P.Saturation_UpperSat) {
    /* Saturate: '<Root>/Saturation' */
    rtb_Saturation = bb01_quick_start_P.Saturation_UpperSat;
  } else if (rtb_Saturation < bb01_quick_start_P.Saturation_LowerSat) {
    /* Saturate: '<Root>/Saturation' */
    rtb_Saturation = bb01_quick_start_P.Saturation_LowerSat;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Bias: '<Root>/Subtract 56 deg' incorporates:
   *  Gain: '<Root>/Count to rad'
   */
  rtb_Subtract56deg = bb01_quick_start_P.Counttorad_Gain * rtb_Subtract56deg +
    bb01_quick_start_P.Subtract56deg_Bias;

  /* Gain: '<Root>/Servo Gain' incorporates:
   *  Sum: '<Root>/Sum1'
   */
  bb01_quick_start_B.ServoGain = (rtb_Saturation - rtb_Subtract56deg) *
    bb01_quick_start_P.ServoGain_Gain;

  /* S-Function (hil_write_block): '<Root>/HIL Write' */

  /* S-Function Block: bb01_quick_start/HIL Write (hil_write_block) */
  {
    t_error result;
    result = hil_write(bb01_quick_start_DW.HILInitialize_Card,
                       &bb01_quick_start_P.HILWrite_analog_channels, 1U,
                       NULL, 0U,
                       NULL, 0U,
                       NULL, 0U,
                       &bb01_quick_start_B.ServoGain,
                       NULL,
                       NULL,
                       NULL
                       );
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
    }
  }

  /* Gain: '<Root>/m to cm ' */
  bb01_quick_start_B.mtocm_e = bb01_quick_start_P.mtocm_Gain_a *
    rtb_SS01CalibrationmV;

  /* Gain: '<Root>/Radian  to degree ' */
  bb01_quick_start_B.Radiantodegree = bb01_quick_start_P.Radiantodegree_Gain *
    rtb_Subtract56deg;
}

/* Model update function */
void bb01_quick_start_update(void)
{
  /* Update for DiscreteTransferFcn: '<S2>/Discrete Transfer Fcn' */
  bb01_quick_start_DW.DiscreteTransferFcn_states =
    bb01_quick_start_DW.DiscreteTransferFcn_tmp;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++bb01_quick_start_M->Timing.clockTick0)) {
    ++bb01_quick_start_M->Timing.clockTickH0;
  }

  bb01_quick_start_M->Timing.t[0] = bb01_quick_start_M->Timing.clockTick0 *
    bb01_quick_start_M->Timing.stepSize0 +
    bb01_quick_start_M->Timing.clockTickH0 *
    bb01_quick_start_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void bb01_quick_start_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: bb01_quick_start/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q4", "0", &bb01_quick_start_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (bb01_quick_start_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
      return;
    }

    if ((bb01_quick_start_P.HILInitialize_CKPStart && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_CKPEnter && is_switching)) {
      result = hil_set_clock_mode(bb01_quick_start_DW.HILInitialize_Card,
        (t_clock *) bb01_quick_start_P.HILInitialize_CKChannels, 2U,
        (t_clock_mode *) bb01_quick_start_P.HILInitialize_CKModes);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }

    result = hil_watchdog_clear(bb01_quick_start_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
      return;
    }

    if ((bb01_quick_start_P.HILInitialize_AIPStart && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_AIPEnter && is_switching)) {
      bb01_quick_start_DW.HILInitialize_AIMinimums[0] =
        (bb01_quick_start_P.HILInitialize_AILow);
      bb01_quick_start_DW.HILInitialize_AIMinimums[1] =
        (bb01_quick_start_P.HILInitialize_AILow);
      bb01_quick_start_DW.HILInitialize_AIMinimums[2] =
        (bb01_quick_start_P.HILInitialize_AILow);
      bb01_quick_start_DW.HILInitialize_AIMinimums[3] =
        (bb01_quick_start_P.HILInitialize_AILow);
      bb01_quick_start_DW.HILInitialize_AIMaximums[0] =
        bb01_quick_start_P.HILInitialize_AIHigh;
      bb01_quick_start_DW.HILInitialize_AIMaximums[1] =
        bb01_quick_start_P.HILInitialize_AIHigh;
      bb01_quick_start_DW.HILInitialize_AIMaximums[2] =
        bb01_quick_start_P.HILInitialize_AIHigh;
      bb01_quick_start_DW.HILInitialize_AIMaximums[3] =
        bb01_quick_start_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (bb01_quick_start_DW.HILInitialize_Card,
         bb01_quick_start_P.HILInitialize_AIChannels, 4U,
         &bb01_quick_start_DW.HILInitialize_AIMinimums[0],
         &bb01_quick_start_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((bb01_quick_start_P.HILInitialize_AOPStart && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_AOPEnter && is_switching)) {
      bb01_quick_start_DW.HILInitialize_AOMinimums[0] =
        (bb01_quick_start_P.HILInitialize_AOLow);
      bb01_quick_start_DW.HILInitialize_AOMinimums[1] =
        (bb01_quick_start_P.HILInitialize_AOLow);
      bb01_quick_start_DW.HILInitialize_AOMinimums[2] =
        (bb01_quick_start_P.HILInitialize_AOLow);
      bb01_quick_start_DW.HILInitialize_AOMinimums[3] =
        (bb01_quick_start_P.HILInitialize_AOLow);
      bb01_quick_start_DW.HILInitialize_AOMaximums[0] =
        bb01_quick_start_P.HILInitialize_AOHigh;
      bb01_quick_start_DW.HILInitialize_AOMaximums[1] =
        bb01_quick_start_P.HILInitialize_AOHigh;
      bb01_quick_start_DW.HILInitialize_AOMaximums[2] =
        bb01_quick_start_P.HILInitialize_AOHigh;
      bb01_quick_start_DW.HILInitialize_AOMaximums[3] =
        bb01_quick_start_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (bb01_quick_start_DW.HILInitialize_Card,
         bb01_quick_start_P.HILInitialize_AOChannels, 4U,
         &bb01_quick_start_DW.HILInitialize_AOMinimums[0],
         &bb01_quick_start_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((bb01_quick_start_P.HILInitialize_AOStart && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_AOEnter && is_switching)) {
      bb01_quick_start_DW.HILInitialize_AOVoltages[0] =
        bb01_quick_start_P.HILInitialize_AOInitial;
      bb01_quick_start_DW.HILInitialize_AOVoltages[1] =
        bb01_quick_start_P.HILInitialize_AOInitial;
      bb01_quick_start_DW.HILInitialize_AOVoltages[2] =
        bb01_quick_start_P.HILInitialize_AOInitial;
      bb01_quick_start_DW.HILInitialize_AOVoltages[3] =
        bb01_quick_start_P.HILInitialize_AOInitial;
      result = hil_write_analog(bb01_quick_start_DW.HILInitialize_Card,
        bb01_quick_start_P.HILInitialize_AOChannels, 4U,
        &bb01_quick_start_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }

    if (bb01_quick_start_P.HILInitialize_AOReset) {
      bb01_quick_start_DW.HILInitialize_AOVoltages[0] =
        bb01_quick_start_P.HILInitialize_AOWatchdog;
      bb01_quick_start_DW.HILInitialize_AOVoltages[1] =
        bb01_quick_start_P.HILInitialize_AOWatchdog;
      bb01_quick_start_DW.HILInitialize_AOVoltages[2] =
        bb01_quick_start_P.HILInitialize_AOWatchdog;
      bb01_quick_start_DW.HILInitialize_AOVoltages[3] =
        bb01_quick_start_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (bb01_quick_start_DW.HILInitialize_Card,
         bb01_quick_start_P.HILInitialize_AOChannels, 4U,
         &bb01_quick_start_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((bb01_quick_start_P.HILInitialize_EIPStart && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_EIPEnter && is_switching)) {
      bb01_quick_start_DW.HILInitialize_QuadratureModes[0] =
        bb01_quick_start_P.HILInitialize_EIQuadrature;
      bb01_quick_start_DW.HILInitialize_QuadratureModes[1] =
        bb01_quick_start_P.HILInitialize_EIQuadrature;
      bb01_quick_start_DW.HILInitialize_QuadratureModes[2] =
        bb01_quick_start_P.HILInitialize_EIQuadrature;
      bb01_quick_start_DW.HILInitialize_QuadratureModes[3] =
        bb01_quick_start_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (bb01_quick_start_DW.HILInitialize_Card,
         bb01_quick_start_P.HILInitialize_EIChannels, 4U,
         (t_encoder_quadrature_mode *)
         &bb01_quick_start_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }

      bb01_quick_start_DW.HILInitialize_FilterFrequency[0] =
        bb01_quick_start_P.HILInitialize_EIFrequency;
      bb01_quick_start_DW.HILInitialize_FilterFrequency[1] =
        bb01_quick_start_P.HILInitialize_EIFrequency;
      bb01_quick_start_DW.HILInitialize_FilterFrequency[2] =
        bb01_quick_start_P.HILInitialize_EIFrequency;
      bb01_quick_start_DW.HILInitialize_FilterFrequency[3] =
        bb01_quick_start_P.HILInitialize_EIFrequency;
      result = hil_set_encoder_filter_frequency
        (bb01_quick_start_DW.HILInitialize_Card,
         bb01_quick_start_P.HILInitialize_EIChannels, 4U,
         &bb01_quick_start_DW.HILInitialize_FilterFrequency[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }

    if ((bb01_quick_start_P.HILInitialize_EIStart && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_EIEnter && is_switching)) {
      bb01_quick_start_DW.HILInitialize_InitialEICounts[0] =
        bb01_quick_start_P.HILInitialize_EIInitial;
      bb01_quick_start_DW.HILInitialize_InitialEICounts[1] =
        bb01_quick_start_P.HILInitialize_EIInitial;
      bb01_quick_start_DW.HILInitialize_InitialEICounts[2] =
        bb01_quick_start_P.HILInitialize_EIInitial;
      bb01_quick_start_DW.HILInitialize_InitialEICounts[3] =
        bb01_quick_start_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(bb01_quick_start_DW.HILInitialize_Card,
        bb01_quick_start_P.HILInitialize_EIChannels, 4U,
        &bb01_quick_start_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_timebase_block): '<Root>/HIL Read Timebase' */

  /* S-Function Block: bb01_quick_start/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_create_reader(bb01_quick_start_DW.HILInitialize_Card,
      bb01_quick_start_P.HILReadTimebase_SamplesInBuffer,
      bb01_quick_start_P.HILReadTimebase_AnalogChannels, 2U,
      &bb01_quick_start_P.HILReadTimebase_EncoderChannels, 1U,
      NULL, 0U,
      NULL, 0U,
      &bb01_quick_start_DW.HILReadTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (bb01_quick_start_DW.HILReadTimebase_Task, (t_buffer_overflow_mode)
         (bb01_quick_start_P.HILReadTimebase_OverflowMode - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
    }
  }

  /* Start for S-Function (smooth_signal_generator_block): '<Root>/Smooth Signal Generator' */

  /* S-Function Block: bb01_quick_start/Smooth Signal Generator (smooth_signal_generator_block) */
  {
    real_T T = 1.0 / bb01_quick_start_P.SmoothSignalGenerator_Frequency;
    bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp =
      bb01_quick_start_P.SmoothSignalGenerator_Amplitude;
    bb01_quick_start_DW.SmoothSignalGenerator_RWORK.W = TWO_PI *
      bb01_quick_start_P.SmoothSignalGenerator_Frequency;
    bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T = fmod
      (bb01_quick_start_P.SmoothSignalGenerator_InitialPh, TWO_PI) * T / TWO_PI;
    if (bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T < 0) {
      bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T += T;
    }

    if (bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T < 0.5 * T) {
      bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Y =
        bb01_quick_start_P.SmoothSignalGenerator_Amplitude;
    } else {
      bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Y =
        -bb01_quick_start_P.SmoothSignalGenerator_Amplitude;
    }
  }

  /* InitializeConditions for DiscreteTransferFcn: '<S2>/Discrete Transfer Fcn' */
  bb01_quick_start_DW.DiscreteTransferFcn_states =
    bb01_quick_start_P.DiscreteTransferFcn_InitialStat;
}

/* Model terminate function */
void bb01_quick_start_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: bb01_quick_start/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(bb01_quick_start_DW.HILInitialize_Card);
    hil_monitor_stop_all(bb01_quick_start_DW.HILInitialize_Card);
    is_switching = false;
    if ((bb01_quick_start_P.HILInitialize_AOTerminate && !is_switching) ||
        (bb01_quick_start_P.HILInitialize_AOExit && is_switching)) {
      bb01_quick_start_DW.HILInitialize_AOVoltages[0] =
        bb01_quick_start_P.HILInitialize_AOFinal;
      bb01_quick_start_DW.HILInitialize_AOVoltages[1] =
        bb01_quick_start_P.HILInitialize_AOFinal;
      bb01_quick_start_DW.HILInitialize_AOVoltages[2] =
        bb01_quick_start_P.HILInitialize_AOFinal;
      bb01_quick_start_DW.HILInitialize_AOVoltages[3] =
        bb01_quick_start_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 4U;
    } else {
      num_final_analog_outputs = 0;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(bb01_quick_start_DW.HILInitialize_Card,
        bb01_quick_start_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &bb01_quick_start_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(bb01_quick_start_M, _rt_error_message);
      }
    }

    hil_task_delete_all(bb01_quick_start_DW.HILInitialize_Card);
    hil_monitor_delete_all(bb01_quick_start_DW.HILInitialize_Card);
    hil_close(bb01_quick_start_DW.HILInitialize_Card);
    bb01_quick_start_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  bb01_quick_start_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  bb01_quick_start_update();
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
  bb01_quick_start_initialize();
}

void MdlTerminate(void)
{
  bb01_quick_start_terminate();
}

/* Registration function */
RT_MODEL_bb01_quick_start_T *bb01_quick_start(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)bb01_quick_start_M, 0,
                sizeof(RT_MODEL_bb01_quick_start_T));

  /* Initialize timing info */
  {
    int_T *mdlTsMap = bb01_quick_start_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "bb01_quick_start_M points to
       static memory which is guaranteed to be non-NULL" */
    bb01_quick_start_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    bb01_quick_start_M->Timing.sampleTimes =
      (&bb01_quick_start_M->Timing.sampleTimesArray[0]);
    bb01_quick_start_M->Timing.offsetTimes =
      (&bb01_quick_start_M->Timing.offsetTimesArray[0]);

    /* task periods */
    bb01_quick_start_M->Timing.sampleTimes[0] = (0.002);

    /* task offsets */
    bb01_quick_start_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(bb01_quick_start_M, &bb01_quick_start_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = bb01_quick_start_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    bb01_quick_start_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(bb01_quick_start_M, -1);
  bb01_quick_start_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  bb01_quick_start_M->Sizes.checksums[0] = (1578729505U);
  bb01_quick_start_M->Sizes.checksums[1] = (1401491924U);
  bb01_quick_start_M->Sizes.checksums[2] = (17512705U);
  bb01_quick_start_M->Sizes.checksums[3] = (2220623830U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    bb01_quick_start_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(bb01_quick_start_M->extModeInfo,
      &bb01_quick_start_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(bb01_quick_start_M->extModeInfo,
                        bb01_quick_start_M->Sizes.checksums);
    rteiSetTPtr(bb01_quick_start_M->extModeInfo, rtmGetTPtr(bb01_quick_start_M));
  }

  bb01_quick_start_M->solverInfoPtr = (&bb01_quick_start_M->solverInfo);
  bb01_quick_start_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&bb01_quick_start_M->solverInfo, 0.002);
  rtsiSetSolverMode(&bb01_quick_start_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  bb01_quick_start_M->blockIO = ((void *) &bb01_quick_start_B);

  {
    bb01_quick_start_B.mtocm[0] = 0.0;
    bb01_quick_start_B.mtocm[1] = 0.0;
    bb01_quick_start_B.ServoGain = 0.0;
    bb01_quick_start_B.mtocm_e = 0.0;
    bb01_quick_start_B.Radiantodegree = 0.0;
  }

  /* parameters */
  bb01_quick_start_M->defaultParam = ((real_T *)&bb01_quick_start_P);

  /* states (dwork) */
  bb01_quick_start_M->dwork = ((void *) &bb01_quick_start_DW);
  (void) memset((void *)&bb01_quick_start_DW, 0,
                sizeof(DW_bb01_quick_start_T));
  bb01_quick_start_DW.DiscreteTransferFcn_states = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMinimums[0] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMinimums[1] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMinimums[2] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMinimums[3] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMaximums[0] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMaximums[1] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMaximums[2] = 0.0;
  bb01_quick_start_DW.HILInitialize_AIMaximums[3] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMinimums[0] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMinimums[1] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMinimums[2] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMinimums[3] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMaximums[0] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMaximums[1] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMaximums[2] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOMaximums[3] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOVoltages[0] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOVoltages[1] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOVoltages[2] = 0.0;
  bb01_quick_start_DW.HILInitialize_AOVoltages[3] = 0.0;
  bb01_quick_start_DW.HILInitialize_FilterFrequency[0] = 0.0;
  bb01_quick_start_DW.HILInitialize_FilterFrequency[1] = 0.0;
  bb01_quick_start_DW.HILInitialize_FilterFrequency[2] = 0.0;
  bb01_quick_start_DW.HILInitialize_FilterFrequency[3] = 0.0;
  bb01_quick_start_DW.HILReadTimebase_AnalogBuffer[0] = 0.0;
  bb01_quick_start_DW.HILReadTimebase_AnalogBuffer[1] = 0.0;
  bb01_quick_start_DW.DiscreteTransferFcn_tmp = 0.0;
  bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Amp = 0.0;
  bb01_quick_start_DW.SmoothSignalGenerator_RWORK.W = 0.0;
  bb01_quick_start_DW.SmoothSignalGenerator_RWORK.T = 0.0;
  bb01_quick_start_DW.SmoothSignalGenerator_RWORK.Y = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    bb01_quick_start_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  bb01_quick_start_M->Sizes.numContStates = (0);/* Number of continuous states */
  bb01_quick_start_M->Sizes.numY = (0);/* Number of model outputs */
  bb01_quick_start_M->Sizes.numU = (0);/* Number of model inputs */
  bb01_quick_start_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  bb01_quick_start_M->Sizes.numSampTimes = (1);/* Number of sample times */
  bb01_quick_start_M->Sizes.numBlocks = (28);/* Number of blocks */
  bb01_quick_start_M->Sizes.numBlockIO = (5);/* Number of block outputs */
  bb01_quick_start_M->Sizes.numBlockPrms = (103);/* Sum of parameter "widths" */
  return bb01_quick_start_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
