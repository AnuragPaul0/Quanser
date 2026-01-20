/*
 * quarc_analog_loopback_demo.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "quarc_analog_loopback_demo".
 *
 * Model version              : 1.73
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Dec 23 03:53:50 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "quarc_analog_loopback_demo.h"
#include "quarc_analog_loopback_demo_private.h"
#include "quarc_analog_loopback_demo_dt.h"

/* Block signals (default storage) */
B_quarc_analog_loopback_demo_T quarc_analog_loopback_demo_B;

/* Block states (default storage) */
DW_quarc_analog_loopback_demo_T quarc_analog_loopback_demo_DW;

/* Real-time model */
static RT_MODEL_quarc_analog_loopbac_T quarc_analog_loopback_demo_M_;
RT_MODEL_quarc_analog_loopbac_T *const quarc_analog_loopback_demo_M =
  &quarc_analog_loopback_demo_M_;

/* Model output function */
void quarc_analog_loopback_demo_output(void)
{
  real_T SignalGenerator_tmp;

  /* S-Function (hil_read_analog_block): '<Root>/HIL Read Analog' */

  /* S-Function Block: quarc_analog_loopback_demo/HIL Read Analog (hil_read_analog_block) */
  {
    t_error result = hil_read_analog
      (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
       quarc_analog_loopback_demo_P.HILReadAnalog_channels, 2,
       &quarc_analog_loopback_demo_DW.HILReadAnalog_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
    }

    quarc_analog_loopback_demo_B.HILReadAnalog_o1 =
      quarc_analog_loopback_demo_DW.HILReadAnalog_Buffer[0];
    quarc_analog_loopback_demo_B.HILReadAnalog_o2 =
      quarc_analog_loopback_demo_DW.HILReadAnalog_Buffer[1];
  }

  /* SignalGenerator: '<Root>/Signal Generator' incorporates:
   *  SignalGenerator: '<Root>/Signal Generator1'
   */
  SignalGenerator_tmp = quarc_analog_loopback_demo_M->Timing.t[0];

  /* SignalGenerator: '<Root>/Signal Generator' */
  quarc_analog_loopback_demo_B.SignalGenerator = sin(6.2831853071795862 *
    SignalGenerator_tmp * quarc_analog_loopback_demo_P.SignalGenerator_Frequency)
    * quarc_analog_loopback_demo_P.SignalGenerator_Amplitude;

  /* SignalGenerator: '<Root>/Signal Generator1' */
  SignalGenerator_tmp *= quarc_analog_loopback_demo_P.SignalGenerator1_Frequency;
  if (SignalGenerator_tmp - floor(SignalGenerator_tmp) >= 0.5) {
    /* SignalGenerator: '<Root>/Signal Generator1' */
    quarc_analog_loopback_demo_B.SignalGenerator1 =
      quarc_analog_loopback_demo_P.SignalGenerator1_Amplitude;
  } else {
    /* SignalGenerator: '<Root>/Signal Generator1' */
    quarc_analog_loopback_demo_B.SignalGenerator1 =
      -quarc_analog_loopback_demo_P.SignalGenerator1_Amplitude;
  }

  /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

  /* S-Function Block: quarc_analog_loopback_demo/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    quarc_analog_loopback_demo_DW.HILWriteAnalog_Buffer[0] =
      quarc_analog_loopback_demo_B.SignalGenerator;
    quarc_analog_loopback_demo_DW.HILWriteAnalog_Buffer[1] =
      quarc_analog_loopback_demo_B.SignalGenerator1;
    result = hil_write_analog(quarc_analog_loopback_demo_DW.HILInitialize1_Card,
      quarc_analog_loopback_demo_P.HILWriteAnalog_channels, 2,
      &quarc_analog_loopback_demo_DW.HILWriteAnalog_Buffer[0]);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
    }
  }
}

/* Model update function */
void quarc_analog_loopback_demo_update(void)
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
  if (!(++quarc_analog_loopback_demo_M->Timing.clockTick0)) {
    ++quarc_analog_loopback_demo_M->Timing.clockTickH0;
  }

  quarc_analog_loopback_demo_M->Timing.t[0] =
    quarc_analog_loopback_demo_M->Timing.clockTick0 *
    quarc_analog_loopback_demo_M->Timing.stepSize0 +
    quarc_analog_loopback_demo_M->Timing.clockTickH0 *
    quarc_analog_loopback_demo_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.01s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++quarc_analog_loopback_demo_M->Timing.clockTick1)) {
      ++quarc_analog_loopback_demo_M->Timing.clockTickH1;
    }

    quarc_analog_loopback_demo_M->Timing.t[1] =
      quarc_analog_loopback_demo_M->Timing.clockTick1 *
      quarc_analog_loopback_demo_M->Timing.stepSize1 +
      quarc_analog_loopback_demo_M->Timing.clockTickH1 *
      quarc_analog_loopback_demo_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void quarc_analog_loopback_demo_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize1' */

  /* S-Function Block: quarc_analog_loopback_demo/HIL Initialize1 (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0",
                      &quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear
      (quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
      return;
    }

    if ((quarc_analog_loopback_demo_P.HILInitialize1_AIPStart && !is_switching) ||
        (quarc_analog_loopback_demo_P.HILInitialize1_AIPEnter && is_switching))
    {
      quarc_analog_loopback_demo_DW.HILInitialize1_AIMinimums[0] =
        (quarc_analog_loopback_demo_P.HILInitialize1_AILow);
      quarc_analog_loopback_demo_DW.HILInitialize1_AIMinimums[1] =
        (quarc_analog_loopback_demo_P.HILInitialize1_AILow);
      quarc_analog_loopback_demo_DW.HILInitialize1_AIMaximums[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_AIHigh;
      quarc_analog_loopback_demo_DW.HILInitialize1_AIMaximums[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_AIHigh;
      result = hil_set_analog_input_ranges
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_AIChannels, 2U,
         &quarc_analog_loopback_demo_DW.HILInitialize1_AIMinimums[0],
         &quarc_analog_loopback_demo_DW.HILInitialize1_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
        return;
      }
    }

    if ((quarc_analog_loopback_demo_P.HILInitialize1_AOPStart && !is_switching) ||
        (quarc_analog_loopback_demo_P.HILInitialize1_AOPEnter && is_switching))
    {
      quarc_analog_loopback_demo_DW.HILInitialize1_AOMinimums[0] =
        (quarc_analog_loopback_demo_P.HILInitialize1_AOLow);
      quarc_analog_loopback_demo_DW.HILInitialize1_AOMinimums[1] =
        (quarc_analog_loopback_demo_P.HILInitialize1_AOLow);
      quarc_analog_loopback_demo_DW.HILInitialize1_AOMaximums[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOHigh;
      quarc_analog_loopback_demo_DW.HILInitialize1_AOMaximums[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOHigh;
      result = hil_set_analog_output_ranges
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_AOChannels, 2U,
         &quarc_analog_loopback_demo_DW.HILInitialize1_AOMinimums[0],
         &quarc_analog_loopback_demo_DW.HILInitialize1_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
        return;
      }
    }

    if ((quarc_analog_loopback_demo_P.HILInitialize1_AOStart && !is_switching) ||
        (quarc_analog_loopback_demo_P.HILInitialize1_AOEnter && is_switching)) {
      quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOInitial;
      quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOInitial;
      result = hil_write_analog
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_AOChannels, 2U,
         &quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
        return;
      }
    }

    if (quarc_analog_loopback_demo_P.HILInitialize1_AOReset) {
      quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOWatchdog;
      quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_AOChannels, 2U,
         &quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
        return;
      }
    }

    if ((quarc_analog_loopback_demo_P.HILInitialize1_EIPStart && !is_switching) ||
        (quarc_analog_loopback_demo_P.HILInitialize1_EIPEnter && is_switching))
    {
      quarc_analog_loopback_demo_DW.HILInitialize1_QuadratureModes[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_EIQuadrature;
      quarc_analog_loopback_demo_DW.HILInitialize1_QuadratureModes[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &quarc_analog_loopback_demo_DW.HILInitialize1_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
        return;
      }
    }

    if ((quarc_analog_loopback_demo_P.HILInitialize1_EIStart && !is_switching) ||
        (quarc_analog_loopback_demo_P.HILInitialize1_EIEnter && is_switching)) {
      quarc_analog_loopback_demo_DW.HILInitialize1_InitialEICounts[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_EIInitial;
      quarc_analog_loopback_demo_DW.HILInitialize1_InitialEICounts[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_EIInitial;
      result = hil_set_encoder_counts
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_EIChannels, 2U,
         &quarc_analog_loopback_demo_DW.HILInitialize1_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
        return;
      }
    }
  }
}

/* Model terminate function */
void quarc_analog_loopback_demo_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize1' */

  /* S-Function Block: quarc_analog_loopback_demo/HIL Initialize1 (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    hil_monitor_stop_all(quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    is_switching = false;
    if ((quarc_analog_loopback_demo_P.HILInitialize1_AOTerminate &&
         !is_switching) || (quarc_analog_loopback_demo_P.HILInitialize1_AOExit &&
         is_switching)) {
      quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOFinal;
      quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[1] =
        quarc_analog_loopback_demo_P.HILInitialize1_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog
        (quarc_analog_loopback_demo_DW.HILInitialize1_Card,
         quarc_analog_loopback_demo_P.HILInitialize1_AOChannels,
         num_final_analog_outputs,
         &quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(quarc_analog_loopback_demo_M, _rt_error_message);
      }
    }

    hil_task_delete_all(quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    hil_monitor_delete_all(quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    hil_close(quarc_analog_loopback_demo_DW.HILInitialize1_Card);
    quarc_analog_loopback_demo_DW.HILInitialize1_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  quarc_analog_loopback_demo_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  quarc_analog_loopback_demo_update();
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
  quarc_analog_loopback_demo_initialize();
}

void MdlTerminate(void)
{
  quarc_analog_loopback_demo_terminate();
}

/* Registration function */
RT_MODEL_quarc_analog_loopbac_T *quarc_analog_loopback_demo(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)quarc_analog_loopback_demo_M, 0,
                sizeof(RT_MODEL_quarc_analog_loopbac_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&quarc_analog_loopback_demo_M->solverInfo,
                          &quarc_analog_loopback_demo_M->Timing.simTimeStep);
    rtsiSetTPtr(&quarc_analog_loopback_demo_M->solverInfo, &rtmGetTPtr
                (quarc_analog_loopback_demo_M));
    rtsiSetStepSizePtr(&quarc_analog_loopback_demo_M->solverInfo,
                       &quarc_analog_loopback_demo_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&quarc_analog_loopback_demo_M->solverInfo,
                          (&rtmGetErrorStatus(quarc_analog_loopback_demo_M)));
    rtsiSetRTModelPtr(&quarc_analog_loopback_demo_M->solverInfo,
                      quarc_analog_loopback_demo_M);
  }

  rtsiSetSimTimeStep(&quarc_analog_loopback_demo_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&quarc_analog_loopback_demo_M->solverInfo,
                    "FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = quarc_analog_loopback_demo_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "quarc_analog_loopback_demo_M points to
       static memory which is guaranteed to be non-NULL" */
    quarc_analog_loopback_demo_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    quarc_analog_loopback_demo_M->Timing.sampleTimes =
      (&quarc_analog_loopback_demo_M->Timing.sampleTimesArray[0]);
    quarc_analog_loopback_demo_M->Timing.offsetTimes =
      (&quarc_analog_loopback_demo_M->Timing.offsetTimesArray[0]);

    /* task periods */
    quarc_analog_loopback_demo_M->Timing.sampleTimes[0] = (0.0);
    quarc_analog_loopback_demo_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    quarc_analog_loopback_demo_M->Timing.offsetTimes[0] = (0.0);
    quarc_analog_loopback_demo_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(quarc_analog_loopback_demo_M,
             &quarc_analog_loopback_demo_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = quarc_analog_loopback_demo_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    quarc_analog_loopback_demo_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(quarc_analog_loopback_demo_M, -1);
  quarc_analog_loopback_demo_M->Timing.stepSize0 = 0.01;
  quarc_analog_loopback_demo_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  quarc_analog_loopback_demo_M->Sizes.checksums[0] = (1326062989U);
  quarc_analog_loopback_demo_M->Sizes.checksums[1] = (1111253509U);
  quarc_analog_loopback_demo_M->Sizes.checksums[2] = (935659910U);
  quarc_analog_loopback_demo_M->Sizes.checksums[3] = (1260770040U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    quarc_analog_loopback_demo_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(quarc_analog_loopback_demo_M->extModeInfo,
      &quarc_analog_loopback_demo_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(quarc_analog_loopback_demo_M->extModeInfo,
                        quarc_analog_loopback_demo_M->Sizes.checksums);
    rteiSetTPtr(quarc_analog_loopback_demo_M->extModeInfo, rtmGetTPtr
                (quarc_analog_loopback_demo_M));
  }

  quarc_analog_loopback_demo_M->solverInfoPtr =
    (&quarc_analog_loopback_demo_M->solverInfo);
  quarc_analog_loopback_demo_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&quarc_analog_loopback_demo_M->solverInfo, 0.01);
  rtsiSetSolverMode(&quarc_analog_loopback_demo_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  quarc_analog_loopback_demo_M->blockIO = ((void *)
    &quarc_analog_loopback_demo_B);

  {
    quarc_analog_loopback_demo_B.HILReadAnalog_o1 = 0.0;
    quarc_analog_loopback_demo_B.HILReadAnalog_o2 = 0.0;
    quarc_analog_loopback_demo_B.SignalGenerator = 0.0;
    quarc_analog_loopback_demo_B.SignalGenerator1 = 0.0;
  }

  /* parameters */
  quarc_analog_loopback_demo_M->defaultParam = ((real_T *)
    &quarc_analog_loopback_demo_P);

  /* states (dwork) */
  quarc_analog_loopback_demo_M->dwork = ((void *) &quarc_analog_loopback_demo_DW);
  (void) memset((void *)&quarc_analog_loopback_demo_DW, 0,
                sizeof(DW_quarc_analog_loopback_demo_T));
  quarc_analog_loopback_demo_DW.HILInitialize1_AIMinimums[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AIMinimums[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AIMaximums[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AIMaximums[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AOMinimums[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AOMinimums[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AOMaximums[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AOMaximums[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_AOVoltages[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_FilterFrequency[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILInitialize1_FilterFrequency[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILReadAnalog_Buffer[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILReadAnalog_Buffer[1] = 0.0;
  quarc_analog_loopback_demo_DW.HILWriteAnalog_Buffer[0] = 0.0;
  quarc_analog_loopback_demo_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    quarc_analog_loopback_demo_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  quarc_analog_loopback_demo_M->Sizes.numContStates = (0);/* Number of continuous states */
  quarc_analog_loopback_demo_M->Sizes.numY = (0);/* Number of model outputs */
  quarc_analog_loopback_demo_M->Sizes.numU = (0);/* Number of model inputs */
  quarc_analog_loopback_demo_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  quarc_analog_loopback_demo_M->Sizes.numSampTimes = (2);/* Number of sample times */
  quarc_analog_loopback_demo_M->Sizes.numBlocks = (7);/* Number of blocks */
  quarc_analog_loopback_demo_M->Sizes.numBlockIO = (4);/* Number of block outputs */
  quarc_analog_loopback_demo_M->Sizes.numBlockPrms = (71);/* Sum of parameter "widths" */
  return quarc_analog_loopback_demo_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
