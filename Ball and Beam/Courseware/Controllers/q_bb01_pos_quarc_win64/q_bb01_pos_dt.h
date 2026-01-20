/*
 * q_bb01_pos_dt.h
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

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(int32_T),
  sizeof(t_task),
  sizeof(t_card),
  sizeof(t_boolean),
  sizeof(char_T),
  sizeof(uchar_T),
  sizeof(time_T)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "physical_connection",
  "t_task",
  "t_card",
  "t_boolean",
  "char_T",
  "uchar_T",
  "time_T"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&q_bb01_pos_B.HILReadAnalogTimebase_o1), 0, 0, 51 },

  { (char_T *)(&q_bb01_pos_B.Compare), 3, 0, 2 },

  { (char_T *)(&q_bb01_pos_B.LogicalOperator), 8, 0, 2 }
  ,

  { (char_T *)(&q_bb01_pos_DW.HILInitialize_AIMinimums[0]), 0, 0, 66 },

  { (char_T *)(&q_bb01_pos_DW.HILReadAnalogTimebase_Task), 15, 0, 1 },

  { (char_T *)(&q_bb01_pos_DW.HILInitialize_Card), 16, 0, 1 },

  { (char_T *)(&q_bb01_pos_DW.HILReadEncoder_PWORK), 11, 0, 6 },

  { (char_T *)(&q_bb01_pos_DW.HILInitialize_ClockModes[0]), 6, 0, 52 },

  { (char_T *)(&q_bb01_pos_DW.HILInitialize_POSortedChans[0]), 7, 0, 8 },

  { (char_T *)(&q_bb01_pos_DW.HILInitialize_DOBits[0]), 8, 0, 8 },

  { (char_T *)(&q_bb01_pos_DW.HILWriteDigital_Buffer[0]), 17, 0, 4 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  11U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&q_bb01_pos_P.K_AMP), 0, 0, 21 },

  { (char_T *)(&q_bb01_pos_P.HILReadEncoder_channels), 7, 0, 6 },

  { (char_T *)(&q_bb01_pos_P.Setpointm_Gain), 0, 0, 36 },

  { (char_T *)(&q_bb01_pos_P.HILInitialize_CKChannels[0]), 6, 0, 10 },

  { (char_T *)(&q_bb01_pos_P.HILInitialize_AIChannels[0]), 7, 0, 44 },

  { (char_T *)(&q_bb01_pos_P.HILInitialize_Active), 8, 0, 39 },

  { (char_T *)(&q_bb01_pos_P.HILReadAnalogTimebase_OverflowM), 3, 0, 2 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  7U,
  rtPTransitions
};

/* [EOF] q_bb01_pos_dt.h */
