/*
 * Ball_Beam_testing.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Ball_Beam_testing".
 *
 * Model version              : 12.1
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Mon Jan  9 01:45:35 2023
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Ball_Beam_testing.h"
#include "Ball_Beam_testing_private.h"
#include "Ball_Beam_testing_dt.h"

/* Block signals (default storage) */
B_Ball_Beam_testing_T Ball_Beam_testing_B;

/* Block states (default storage) */
DW_Ball_Beam_testing_T Ball_Beam_testing_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Ball_Beam_testing_T Ball_Beam_testing_Y;

/* Real-time model */
static RT_MODEL_Ball_Beam_testing_T Ball_Beam_testing_M_;
RT_MODEL_Ball_Beam_testing_T *const Ball_Beam_testing_M = &Ball_Beam_testing_M_;

/* Model output function */
void Ball_Beam_testing_output(void)
{
  /* local block i/o variables */
  real_T rtb_InverseAmplifierGainVV;
  real_T rtb_BB01CalibrationmV;

  /* S-Function (hil_read_analog_timebase_block): '<Root>/HIL Read Analog Timebase' */

  /* S-Function Block: Ball_Beam_testing/HIL Read Analog Timebase (hil_read_analog_timebase_block) */
  {
    t_error result;
    result = hil_task_read_analog
      (Ball_Beam_testing_DW.HILReadAnalogTimebase_Task, 1,
       &Ball_Beam_testing_DW.HILReadAnalogTimebase_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
    }

    Ball_Beam_testing_B.HILReadAnalogTimebase_o1 =
      Ball_Beam_testing_DW.HILReadAnalogTimebase_Buffer[0];
    rtb_InverseAmplifierGainVV =
      Ball_Beam_testing_DW.HILReadAnalogTimebase_Buffer[1];
  }

  /* RelationalOperator: '<S6>/Compare' incorporates:
   *  Constant: '<S6>/Constant'
   */
  Ball_Beam_testing_B.Compare = (uint8_T)
    (Ball_Beam_testing_B.HILReadAnalogTimebase_o1 <
     Ball_Beam_testing_P.ReadingZero_const);

  /* MultiPortSwitch: '<S4>/Multiport Switch' incorporates:
   *  Clock: '<S4>/Clock'
   *  Constant: '<S4>/Constant'
   *  Constant: '<S5>/Constant'
   *  Logic: '<S4>/Logical Operator'
   *  RelationalOperator: '<S5>/Compare'
   */
  if ((!(Ball_Beam_testing_M->Timing.t[0] <
         Ball_Beam_testing_P.InitialTimes_const)) ||
      (Ball_Beam_testing_B.Compare == 0)) {
    rtb_BB01CalibrationmV = Ball_Beam_testing_B.HILReadAnalogTimebase_o1;
  } else {
    rtb_BB01CalibrationmV = Ball_Beam_testing_P.Constant_Value;
  }

  /* End of MultiPortSwitch: '<S4>/Multiport Switch' */

  /* Gain: '<Root>/BB01 Calibration  (m//V)' */
  rtb_BB01CalibrationmV *= Ball_Beam_testing_P.K_BS;

  /* Outport: '<Root>/x (m)' */
  Ball_Beam_testing_Y.xm = rtb_BB01CalibrationmV;

  /* Gain: '<Root>/SS01 Calibration  (m//V)' */
  Ball_Beam_testing_B.SS01CalibrationmV = Ball_Beam_testing_P.K_BS *
    rtb_InverseAmplifierGainVV;

  /* Outport: '<Root>/x_d (m)' */
  Ball_Beam_testing_Y.x_dm = Ball_Beam_testing_B.SS01CalibrationmV;

  /* Gain: '<Root>/cm//m' */
  Ball_Beam_testing_B.cmm[0] = Ball_Beam_testing_P.cmm_Gain *
    rtb_BB01CalibrationmV;
  Ball_Beam_testing_B.cmm[1] = Ball_Beam_testing_P.cmm_Gain *
    Ball_Beam_testing_B.SS01CalibrationmV;

  /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

  /* S-Function Block: Ball_Beam_testing/HIL Read Encoder (hil_read_encoder_block) */
  {
    t_error result = hil_read_encoder(Ball_Beam_testing_DW.HILInitialize_Card,
      &Ball_Beam_testing_P.HILReadEncoder_channels, 1,
      &Ball_Beam_testing_DW.HILReadEncoder_Buffer);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
    } else {
      rtb_InverseAmplifierGainVV = Ball_Beam_testing_DW.HILReadEncoder_Buffer;
    }
  }

  /* Gain: '<S1>/Inverse Amplifier  Gain (V//V)' incorporates:
   *  Bias: '<Root>/Bias'
   *  Gain: '<Root>/Encoder Calibration  (rad//count)'
   */
  rtb_InverseAmplifierGainVV = Ball_Beam_testing_P.K_ENC *
    rtb_InverseAmplifierGainVV + Ball_Beam_testing_P.THETA_OFF;

  /* Outport: '<Root>/theta_l (rad)' */
  Ball_Beam_testing_Y.theta_lrad = rtb_InverseAmplifierGainVV;

  /* Gain: '<S3>/Gain' */
  Ball_Beam_testing_B.Gain[0] = Ball_Beam_testing_P.Gain_Gain *
    rtb_InverseAmplifierGainVV;
  Ball_Beam_testing_B.Gain[1] = Ball_Beam_testing_P.Gain_Gain * 0.0;

  /* Gain: '<S1>/Inverse Amplifier  Gain (V//V)' incorporates:
   *  Constant: '<Root>/Constant '
   *  Gain: '<S1>/Direction Convention: (Right-Hand) system'
   *  Gain: '<S2>/Slider Gain'
   */
  rtb_InverseAmplifierGainVV = Ball_Beam_testing_P.Constantcm_gain *
    Ball_Beam_testing_P.Constant_Value_j *
    Ball_Beam_testing_P.DirectionConventionRightHandsys;

  /* Saturate: '<S1>/Amplifier  Saturation (V)' */
  if (rtb_InverseAmplifierGainVV > Ball_Beam_testing_P.VMAX_AMP) {
    /* Gain: '<S1>/Inverse Amplifier  Gain (V//V)' */
    rtb_InverseAmplifierGainVV = Ball_Beam_testing_P.VMAX_AMP;
  } else if (rtb_InverseAmplifierGainVV < -Ball_Beam_testing_P.VMAX_AMP) {
    /* Gain: '<S1>/Inverse Amplifier  Gain (V//V)' */
    rtb_InverseAmplifierGainVV = -Ball_Beam_testing_P.VMAX_AMP;
  }

  /* End of Saturate: '<S1>/Amplifier  Saturation (V)' */

  /* Gain: '<S1>/Inverse Amplifier  Gain (V//V)' */
  rtb_InverseAmplifierGainVV *= 1.0 / Ball_Beam_testing_P.K_AMP;

  /* Saturate: '<S1>/DACB Saturation (V)' */
  if (rtb_InverseAmplifierGainVV > Ball_Beam_testing_P.VMAX_DAC) {
    /* Saturate: '<S1>/DACB Saturation (V)' */
    Ball_Beam_testing_B.DACBSaturationV = Ball_Beam_testing_P.VMAX_DAC;
  } else if (rtb_InverseAmplifierGainVV < -Ball_Beam_testing_P.VMAX_DAC) {
    /* Saturate: '<S1>/DACB Saturation (V)' */
    Ball_Beam_testing_B.DACBSaturationV = -Ball_Beam_testing_P.VMAX_DAC;
  } else {
    /* Saturate: '<S1>/DACB Saturation (V)' */
    Ball_Beam_testing_B.DACBSaturationV = rtb_InverseAmplifierGainVV;
  }

  /* End of Saturate: '<S1>/DACB Saturation (V)' */

  /* Outport: '<Root>/Vm (V)' incorporates:
   *  Gain: '<S1>/Amplifier  Gain (V//V)'
   */
  Ball_Beam_testing_Y.VmV = -Ball_Beam_testing_P.K_AMP *
    Ball_Beam_testing_B.DACBSaturationV;

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: Ball_Beam_testing/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(Ball_Beam_testing_DW.HILInitialize_Card,
      &Ball_Beam_testing_P.HILWriteAnalog_channels, 1,
      &Ball_Beam_testing_B.DACBSaturationV);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
    }
  }
}

/* Model update function */
void Ball_Beam_testing_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Ball_Beam_testing_M->Timing.clockTick0)) {
    ++Ball_Beam_testing_M->Timing.clockTickH0;
  }

  Ball_Beam_testing_M->Timing.t[0] = Ball_Beam_testing_M->Timing.clockTick0 *
    Ball_Beam_testing_M->Timing.stepSize0 +
    Ball_Beam_testing_M->Timing.clockTickH0 *
    Ball_Beam_testing_M->Timing.stepSize0 * 4294967296.0;

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
    if (!(++Ball_Beam_testing_M->Timing.clockTick1)) {
      ++Ball_Beam_testing_M->Timing.clockTickH1;
    }

    Ball_Beam_testing_M->Timing.t[1] = Ball_Beam_testing_M->Timing.clockTick1 *
      Ball_Beam_testing_M->Timing.stepSize1 +
      Ball_Beam_testing_M->Timing.clockTickH1 *
      Ball_Beam_testing_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void Ball_Beam_testing_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Ball_Beam_testing/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Ball_Beam_testing_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (Ball_Beam_testing_DW.HILInitialize_Card, "update_rate=normal", 19);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Ball_Beam_testing_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
      return;
    }

    if ((Ball_Beam_testing_P.HILInitialize_AIPStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Ball_Beam_testing_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Ball_Beam_testing_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Ball_Beam_testing_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Ball_Beam_testing_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (Ball_Beam_testing_DW.HILInitialize_Card,
         Ball_Beam_testing_P.HILInitialize_AIChannels, 8U,
         &Ball_Beam_testing_DW.HILInitialize_AIMinimums[0],
         &Ball_Beam_testing_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if ((Ball_Beam_testing_P.HILInitialize_AOPStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Ball_Beam_testing_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Ball_Beam_testing_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Ball_Beam_testing_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Ball_Beam_testing_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (Ball_Beam_testing_DW.HILInitialize_Card,
         Ball_Beam_testing_P.HILInitialize_AOChannels, 8U,
         &Ball_Beam_testing_DW.HILInitialize_AOMinimums[0],
         &Ball_Beam_testing_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if ((Ball_Beam_testing_P.HILInitialize_AOStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Ball_Beam_testing_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_AOChannels, 8U,
        &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if (Ball_Beam_testing_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Ball_Beam_testing_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Ball_Beam_testing_DW.HILInitialize_Card,
         Ball_Beam_testing_P.HILInitialize_AOChannels, 8U,
         &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(Ball_Beam_testing_DW.HILInitialize_Card,
      NULL, 0U, Ball_Beam_testing_P.HILInitialize_DOChannels, 8U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
      return;
    }

    if ((Ball_Beam_testing_P.HILInitialize_DOStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_DOEnter && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &Ball_Beam_testing_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = Ball_Beam_testing_P.HILInitialize_DOInitial;
        }
      }

      result = hil_write_digital(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_DOChannels, 8U, (t_boolean *)
        &Ball_Beam_testing_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if (Ball_Beam_testing_P.HILInitialize_DOReset) {
      {
        int_T i1;
        int32_T *dw_DOStates = &Ball_Beam_testing_DW.HILInitialize_DOStates[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOStates[i1] = Ball_Beam_testing_P.HILInitialize_DOWatchdog;
        }
      }

      result = hil_watchdog_set_digital_expiration_state
        (Ball_Beam_testing_DW.HILInitialize_Card,
         Ball_Beam_testing_P.HILInitialize_DOChannels, 8U, (const
          t_digital_state *) &Ball_Beam_testing_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if ((Ball_Beam_testing_P.HILInitialize_EIPStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Ball_Beam_testing_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            Ball_Beam_testing_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Ball_Beam_testing_DW.HILInitialize_Card,
         Ball_Beam_testing_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Ball_Beam_testing_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if ((Ball_Beam_testing_P.HILInitialize_EIStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Ball_Beam_testing_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Ball_Beam_testing_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_EIChannels, 8U,
        &Ball_Beam_testing_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if ((Ball_Beam_testing_P.HILInitialize_POPStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Ball_Beam_testing_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Ball_Beam_testing_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Ball_Beam_testing_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Ball_Beam_testing_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &Ball_Beam_testing_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Ball_Beam_testing_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            Ball_Beam_testing_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = Ball_Beam_testing_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Ball_Beam_testing_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Ball_Beam_testing_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              Ball_Beam_testing_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Ball_Beam_testing_DW.HILInitialize_Card,
          &Ball_Beam_testing_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes,
          &Ball_Beam_testing_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Ball_Beam_testing_DW.HILInitialize_Card,
          &Ball_Beam_testing_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Ball_Beam_testing_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Ball_Beam_testing_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            Ball_Beam_testing_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Ball_Beam_testing_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Ball_Beam_testing_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Ball_Beam_testing_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Ball_Beam_testing_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *)
        &Ball_Beam_testing_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Ball_Beam_testing_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Ball_Beam_testing_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Ball_Beam_testing_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Ball_Beam_testing_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Ball_Beam_testing_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Ball_Beam_testing_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_POChannels, 8U,
        &Ball_Beam_testing_DW.HILInitialize_POSortedFreqs[0],
        &Ball_Beam_testing_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if ((Ball_Beam_testing_P.HILInitialize_POStart && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Ball_Beam_testing_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Ball_Beam_testing_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Ball_Beam_testing_DW.HILInitialize_Card,
        Ball_Beam_testing_P.HILInitialize_POChannels, 8U,
        &Ball_Beam_testing_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }

    if (Ball_Beam_testing_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Ball_Beam_testing_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Ball_Beam_testing_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Ball_Beam_testing_DW.HILInitialize_Card,
         Ball_Beam_testing_P.HILInitialize_POChannels, 8U,
         &Ball_Beam_testing_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_analog_timebase_block): '<Root>/HIL Read Analog Timebase' */

  /* S-Function Block: Ball_Beam_testing/HIL Read Analog Timebase (hil_read_analog_timebase_block) */
  {
    t_error result;
    result = hil_task_create_analog_reader
      (Ball_Beam_testing_DW.HILInitialize_Card,
       Ball_Beam_testing_P.HILReadAnalogTimebase_SamplesIn,
       Ball_Beam_testing_P.HILReadAnalogTimebase_Channels, 2,
       &Ball_Beam_testing_DW.HILReadAnalogTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Ball_Beam_testing_DW.HILReadAnalogTimebase_Task,
         (t_buffer_overflow_mode)
         (Ball_Beam_testing_P.HILReadAnalogTimebase_OverflowM - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
    }
  }
}

/* Model terminate function */
void Ball_Beam_testing_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Ball_Beam_testing/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Ball_Beam_testing_DW.HILInitialize_Card);
    hil_monitor_stop_all(Ball_Beam_testing_DW.HILInitialize_Card);
    is_switching = false;
    if ((Ball_Beam_testing_P.HILInitialize_AOTerminate && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Ball_Beam_testing_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Ball_Beam_testing_P.HILInitialize_DOTerminate && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_DOExit && is_switching)) {
      {
        int_T i1;
        boolean_T *dw_DOBits = &Ball_Beam_testing_DW.HILInitialize_DOBits[0];
        for (i1=0; i1 < 8; i1++) {
          dw_DOBits[i1] = Ball_Beam_testing_P.HILInitialize_DOFinal;
        }
      }

      num_final_digital_outputs = 8U;
    } else {
      num_final_digital_outputs = 0;
    }

    if ((Ball_Beam_testing_P.HILInitialize_POTerminate && !is_switching) ||
        (Ball_Beam_testing_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Ball_Beam_testing_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Ball_Beam_testing_P.HILInitialize_POFinal;
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
      result = hil_write(Ball_Beam_testing_DW.HILInitialize_Card
                         , Ball_Beam_testing_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Ball_Beam_testing_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , Ball_Beam_testing_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , NULL, 0
                         , &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0]
                         , &Ball_Beam_testing_DW.HILInitialize_POValues[0]
                         , (t_boolean *)
                         &Ball_Beam_testing_DW.HILInitialize_DOBits[0]
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (Ball_Beam_testing_DW.HILInitialize_Card,
             Ball_Beam_testing_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &Ball_Beam_testing_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Ball_Beam_testing_DW.HILInitialize_Card,
            Ball_Beam_testing_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Ball_Beam_testing_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (Ball_Beam_testing_DW.HILInitialize_Card,
             Ball_Beam_testing_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &Ball_Beam_testing_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Ball_Beam_testing_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Ball_Beam_testing_DW.HILInitialize_Card);
    hil_monitor_delete_all(Ball_Beam_testing_DW.HILInitialize_Card);
    hil_close(Ball_Beam_testing_DW.HILInitialize_Card);
    Ball_Beam_testing_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  Ball_Beam_testing_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Ball_Beam_testing_update();
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
  Ball_Beam_testing_initialize();
}

void MdlTerminate(void)
{
  Ball_Beam_testing_terminate();
}

/* Registration function */
RT_MODEL_Ball_Beam_testing_T *Ball_Beam_testing(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Ball_Beam_testing_M, 0,
                sizeof(RT_MODEL_Ball_Beam_testing_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Ball_Beam_testing_M->solverInfo,
                          &Ball_Beam_testing_M->Timing.simTimeStep);
    rtsiSetTPtr(&Ball_Beam_testing_M->solverInfo, &rtmGetTPtr
                (Ball_Beam_testing_M));
    rtsiSetStepSizePtr(&Ball_Beam_testing_M->solverInfo,
                       &Ball_Beam_testing_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&Ball_Beam_testing_M->solverInfo, (&rtmGetErrorStatus
      (Ball_Beam_testing_M)));
    rtsiSetRTModelPtr(&Ball_Beam_testing_M->solverInfo, Ball_Beam_testing_M);
  }

  rtsiSetSimTimeStep(&Ball_Beam_testing_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&Ball_Beam_testing_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Ball_Beam_testing_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "Ball_Beam_testing_M points to
       static memory which is guaranteed to be non-NULL" */
    Ball_Beam_testing_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Ball_Beam_testing_M->Timing.sampleTimes =
      (&Ball_Beam_testing_M->Timing.sampleTimesArray[0]);
    Ball_Beam_testing_M->Timing.offsetTimes =
      (&Ball_Beam_testing_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Ball_Beam_testing_M->Timing.sampleTimes[0] = (0.0);
    Ball_Beam_testing_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    Ball_Beam_testing_M->Timing.offsetTimes[0] = (0.0);
    Ball_Beam_testing_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Ball_Beam_testing_M, &Ball_Beam_testing_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Ball_Beam_testing_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Ball_Beam_testing_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Ball_Beam_testing_M, -1);
  Ball_Beam_testing_M->Timing.stepSize0 = 0.002;
  Ball_Beam_testing_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  Ball_Beam_testing_M->Sizes.checksums[0] = (1002928623U);
  Ball_Beam_testing_M->Sizes.checksums[1] = (2751032461U);
  Ball_Beam_testing_M->Sizes.checksums[2] = (4272542429U);
  Ball_Beam_testing_M->Sizes.checksums[3] = (4269434791U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Ball_Beam_testing_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Ball_Beam_testing_M->extModeInfo,
      &Ball_Beam_testing_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Ball_Beam_testing_M->extModeInfo,
                        Ball_Beam_testing_M->Sizes.checksums);
    rteiSetTPtr(Ball_Beam_testing_M->extModeInfo, rtmGetTPtr(Ball_Beam_testing_M));
  }

  Ball_Beam_testing_M->solverInfoPtr = (&Ball_Beam_testing_M->solverInfo);
  Ball_Beam_testing_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Ball_Beam_testing_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Ball_Beam_testing_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Ball_Beam_testing_M->blockIO = ((void *) &Ball_Beam_testing_B);
  (void) memset(((void *) &Ball_Beam_testing_B), 0,
                sizeof(B_Ball_Beam_testing_T));

  /* parameters */
  Ball_Beam_testing_M->defaultParam = ((real_T *)&Ball_Beam_testing_P);

  /* states (dwork) */
  Ball_Beam_testing_M->dwork = ((void *) &Ball_Beam_testing_DW);
  (void) memset((void *)&Ball_Beam_testing_DW, 0,
                sizeof(DW_Ball_Beam_testing_T));

  /* external outputs */
  Ball_Beam_testing_M->outputs = (&Ball_Beam_testing_Y);
  (void)memset(&Ball_Beam_testing_Y, 0, sizeof(ExtY_Ball_Beam_testing_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Ball_Beam_testing_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Ball_Beam_testing_M->Sizes.numContStates = (0);/* Number of continuous states */
  Ball_Beam_testing_M->Sizes.numY = (4);/* Number of model outputs */
  Ball_Beam_testing_M->Sizes.numU = (0);/* Number of model inputs */
  Ball_Beam_testing_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Ball_Beam_testing_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Ball_Beam_testing_M->Sizes.numBlocks = (32);/* Number of blocks */
  Ball_Beam_testing_M->Sizes.numBlockIO = (6);/* Number of block outputs */
  Ball_Beam_testing_M->Sizes.numBlockPrms = (126);/* Sum of parameter "widths" */
  return Ball_Beam_testing_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
