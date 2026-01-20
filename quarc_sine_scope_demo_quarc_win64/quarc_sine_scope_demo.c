/*
 * quarc_sine_scope_demo.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "quarc_sine_scope_demo".
 *
 * Model version              : 1.24
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Wed Dec 21 05:16:55 2022
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "quarc_sine_scope_demo.h"
#include "quarc_sine_scope_demo_private.h"
#include "quarc_sine_scope_demo_dt.h"

/* Block signals (default storage) */
B_quarc_sine_scope_demo_T quarc_sine_scope_demo_B;

/* Block states (default storage) */
DW_quarc_sine_scope_demo_T quarc_sine_scope_demo_DW;

/* Real-time model */
static RT_MODEL_quarc_sine_scope_dem_T quarc_sine_scope_demo_M_;
RT_MODEL_quarc_sine_scope_dem_T *const quarc_sine_scope_demo_M =
  &quarc_sine_scope_demo_M_;

/* Model output function */
void quarc_sine_scope_demo_output(void)
{
  /* Sin: '<Root>/Sine Wave' */
  quarc_sine_scope_demo_B.SineWave = sin(quarc_sine_scope_demo_P.SineWave_Freq *
    quarc_sine_scope_demo_M->Timing.t[0] +
    quarc_sine_scope_demo_P.SineWave_Phase) *
    quarc_sine_scope_demo_P.SineWave_Amp + quarc_sine_scope_demo_P.SineWave_Bias;
}

/* Model update function */
void quarc_sine_scope_demo_update(void)
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
  if (!(++quarc_sine_scope_demo_M->Timing.clockTick0)) {
    ++quarc_sine_scope_demo_M->Timing.clockTickH0;
  }

  quarc_sine_scope_demo_M->Timing.t[0] =
    quarc_sine_scope_demo_M->Timing.clockTick0 *
    quarc_sine_scope_demo_M->Timing.stepSize0 +
    quarc_sine_scope_demo_M->Timing.clockTickH0 *
    quarc_sine_scope_demo_M->Timing.stepSize0 * 4294967296.0;

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
    if (!(++quarc_sine_scope_demo_M->Timing.clockTick1)) {
      ++quarc_sine_scope_demo_M->Timing.clockTickH1;
    }

    quarc_sine_scope_demo_M->Timing.t[1] =
      quarc_sine_scope_demo_M->Timing.clockTick1 *
      quarc_sine_scope_demo_M->Timing.stepSize1 +
      quarc_sine_scope_demo_M->Timing.clockTickH1 *
      quarc_sine_scope_demo_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void quarc_sine_scope_demo_initialize(void)
{
}

/* Model terminate function */
void quarc_sine_scope_demo_terminate(void)
{
  /* (no terminate code required) */
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  quarc_sine_scope_demo_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  quarc_sine_scope_demo_update();
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
  quarc_sine_scope_demo_initialize();
}

void MdlTerminate(void)
{
  quarc_sine_scope_demo_terminate();
}

/* Registration function */
RT_MODEL_quarc_sine_scope_dem_T *quarc_sine_scope_demo(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)quarc_sine_scope_demo_M, 0,
                sizeof(RT_MODEL_quarc_sine_scope_dem_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&quarc_sine_scope_demo_M->solverInfo,
                          &quarc_sine_scope_demo_M->Timing.simTimeStep);
    rtsiSetTPtr(&quarc_sine_scope_demo_M->solverInfo, &rtmGetTPtr
                (quarc_sine_scope_demo_M));
    rtsiSetStepSizePtr(&quarc_sine_scope_demo_M->solverInfo,
                       &quarc_sine_scope_demo_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&quarc_sine_scope_demo_M->solverInfo,
                          (&rtmGetErrorStatus(quarc_sine_scope_demo_M)));
    rtsiSetRTModelPtr(&quarc_sine_scope_demo_M->solverInfo,
                      quarc_sine_scope_demo_M);
  }

  rtsiSetSimTimeStep(&quarc_sine_scope_demo_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&quarc_sine_scope_demo_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = quarc_sine_scope_demo_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "quarc_sine_scope_demo_M points to
       static memory which is guaranteed to be non-NULL" */
    quarc_sine_scope_demo_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    quarc_sine_scope_demo_M->Timing.sampleTimes =
      (&quarc_sine_scope_demo_M->Timing.sampleTimesArray[0]);
    quarc_sine_scope_demo_M->Timing.offsetTimes =
      (&quarc_sine_scope_demo_M->Timing.offsetTimesArray[0]);

    /* task periods */
    quarc_sine_scope_demo_M->Timing.sampleTimes[0] = (0.0);
    quarc_sine_scope_demo_M->Timing.sampleTimes[1] = (0.01);

    /* task offsets */
    quarc_sine_scope_demo_M->Timing.offsetTimes[0] = (0.0);
    quarc_sine_scope_demo_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(quarc_sine_scope_demo_M, &quarc_sine_scope_demo_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = quarc_sine_scope_demo_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    quarc_sine_scope_demo_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(quarc_sine_scope_demo_M, -1);
  quarc_sine_scope_demo_M->Timing.stepSize0 = 0.01;
  quarc_sine_scope_demo_M->Timing.stepSize1 = 0.01;

  /* External mode info */
  quarc_sine_scope_demo_M->Sizes.checksums[0] = (2346720373U);
  quarc_sine_scope_demo_M->Sizes.checksums[1] = (2815531026U);
  quarc_sine_scope_demo_M->Sizes.checksums[2] = (1581476000U);
  quarc_sine_scope_demo_M->Sizes.checksums[3] = (3599840432U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    quarc_sine_scope_demo_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(quarc_sine_scope_demo_M->extModeInfo,
      &quarc_sine_scope_demo_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(quarc_sine_scope_demo_M->extModeInfo,
                        quarc_sine_scope_demo_M->Sizes.checksums);
    rteiSetTPtr(quarc_sine_scope_demo_M->extModeInfo, rtmGetTPtr
                (quarc_sine_scope_demo_M));
  }

  quarc_sine_scope_demo_M->solverInfoPtr = (&quarc_sine_scope_demo_M->solverInfo);
  quarc_sine_scope_demo_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&quarc_sine_scope_demo_M->solverInfo, 0.01);
  rtsiSetSolverMode(&quarc_sine_scope_demo_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  quarc_sine_scope_demo_M->blockIO = ((void *) &quarc_sine_scope_demo_B);

  {
    quarc_sine_scope_demo_B.SineWave = 0.0;
  }

  /* parameters */
  quarc_sine_scope_demo_M->defaultParam = ((real_T *)&quarc_sine_scope_demo_P);

  /* states (dwork) */
  quarc_sine_scope_demo_M->dwork = ((void *) &quarc_sine_scope_demo_DW);
  (void) memset((void *)&quarc_sine_scope_demo_DW, 0,
                sizeof(DW_quarc_sine_scope_demo_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    quarc_sine_scope_demo_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 18;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  quarc_sine_scope_demo_M->Sizes.numContStates = (0);/* Number of continuous states */
  quarc_sine_scope_demo_M->Sizes.numY = (0);/* Number of model outputs */
  quarc_sine_scope_demo_M->Sizes.numU = (0);/* Number of model inputs */
  quarc_sine_scope_demo_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  quarc_sine_scope_demo_M->Sizes.numSampTimes = (2);/* Number of sample times */
  quarc_sine_scope_demo_M->Sizes.numBlocks = (2);/* Number of blocks */
  quarc_sine_scope_demo_M->Sizes.numBlockIO = (1);/* Number of block outputs */
  quarc_sine_scope_demo_M->Sizes.numBlockPrms = (4);/* Sum of parameter "widths" */
  return quarc_sine_scope_demo_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
