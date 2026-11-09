/*
 * Lab1_CD_Step02.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab1_CD_Step02".
 *
 * Model version              : 11.6
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Mon Nov  9 14:45:56 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab1_CD_Step02.h"
#include "Lab1_CD_Step02_private.h"

/* Block signals (default storage) */
B_Lab1_CD_Step02_T Lab1_CD_Step02_B;

/* Continuous states */
X_Lab1_CD_Step02_T Lab1_CD_Step02_X;

/* Block states (default storage) */
DW_Lab1_CD_Step02_T Lab1_CD_Step02_DW;

/* Real-time model */
static RT_MODEL_Lab1_CD_Step02_T Lab1_CD_Step02_M_;
RT_MODEL_Lab1_CD_Step02_T *const Lab1_CD_Step02_M = &Lab1_CD_Step02_M_;
static void rate_monotonic_scheduler(void);
time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(Lab1_CD_Step02_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(Lab1_CD_Step02_M, 2);
  UNUSED_PARAMETER(rtmNumSampTimes);
  UNUSED_PARAMETER(rtmTimingData);
  UNUSED_PARAMETER(rtmPerTaskSampleHits);
  return(-1);
}

/*
 *   This function updates active task flag for each subrate
 * and rate transition flags for tasks that exchange data.
 * The function assumes rate-monotonic multitasking scheduler.
 * The function must be called at model base rate so that
 * the generated code self-manages all its subrates and rate
 * transition flags.
 */
static void rate_monotonic_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Lab1_CD_Step02_M->Timing.TaskCounters.TID[2])++;
  if ((Lab1_CD_Step02_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    Lab1_CD_Step02_M->Timing.TaskCounters.TID[2] = 0;
  }
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  Lab1_CD_Step02_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void Lab1_CD_Step02_output0(void)      /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Sum_k;
  real_T rtb_Frontgain;
  real_T rtb_e;
  real_T u0;
  if (rtmIsMajorTimeStep(Lab1_CD_Step02_M)) {
    /* set solver stop time */
    if (!(Lab1_CD_Step02_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Lab1_CD_Step02_M->solverInfo,
                            ((Lab1_CD_Step02_M->Timing.clockTickH0 + 1) *
        Lab1_CD_Step02_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Lab1_CD_Step02_M->solverInfo,
                            ((Lab1_CD_Step02_M->Timing.clockTick0 + 1) *
        Lab1_CD_Step02_M->Timing.stepSize0 +
        Lab1_CD_Step02_M->Timing.clockTickH0 *
        Lab1_CD_Step02_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Lab1_CD_Step02_M)) {
    Lab1_CD_Step02_M->Timing.t[0] = rtsiGetT(&Lab1_CD_Step02_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Lab1_CD_Step02_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: Lab1_CD_Step02/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (Lab1_CD_Step02_DW.HILReadEncoderTimebase_Task, 1,
         &Lab1_CD_Step02_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          Lab1_CD_Step02_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_Sum_k = Lab1_CD_Step02_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          Lab1_CD_Step02_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S3>/Pitch: Count to rad' */
    Lab1_CD_Step02_B.PitchCounttorad = Lab1_CD_Step02_P.PitchCounttorad_Gain *
      rtb_Sum_k;
  }

  /* Step: '<Root>/Step' */
  if (Lab1_CD_Step02_M->Timing.t[0] < Lab1_CD_Step02_P.Step_Time) {
    rtb_Frontgain = Lab1_CD_Step02_P.Step_Y0;
  } else {
    rtb_Frontgain = Lab1_CD_Step02_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Sum: '<S5>/Sum1' incorporates:
   *  Gain: '<S5>/Kpd'
   *  Gain: '<S5>/Kpp'
   *  Sum: '<S5>/Sum'
   *  TransferFcn: '<S3>/Pitch: Transfer Fcn'
   */
  rtb_Frontgain = (rtb_Frontgain - Lab1_CD_Step02_B.PitchCounttorad) *
    Lab1_CD_Step02_P.Kpp_Gain - (Lab1_CD_Step02_P.PitchTransferFcn_C *
    Lab1_CD_Step02_X.PitchTransferFcn_CSTATE +
    Lab1_CD_Step02_P.PitchTransferFcn_D * Lab1_CD_Step02_B.PitchCounttorad) *
    Lab1_CD_Step02_P.Kpd_Gain;

  /* Integrator: '<S6>/Integrator' */
  /* Limited  Integrator  */
  if (Lab1_CD_Step02_X.Integrator_CSTATE >= Lab1_CD_Step02_P.Integrator_UpperSat)
  {
    Lab1_CD_Step02_X.Integrator_CSTATE = Lab1_CD_Step02_P.Integrator_UpperSat;
  } else {
    if (Lab1_CD_Step02_X.Integrator_CSTATE <=
        Lab1_CD_Step02_P.Integrator_LowerSat) {
      Lab1_CD_Step02_X.Integrator_CSTATE = Lab1_CD_Step02_P.Integrator_LowerSat;
    }
  }

  if (rtmIsMajorTimeStep(Lab1_CD_Step02_M)) {
    /* Sum: '<S2>/Sum' */
    rtb_Sum_k = 0.0;

    /* Gain: '<S6>/K_ep' */
    Lab1_CD_Step02_B.K_ep = Lab1_CD_Step02_P.K_ep_Gain * rtb_Sum_k;

    /* Gain: '<S6>/K_ed' */
    Lab1_CD_Step02_B.K_ed = Lab1_CD_Step02_P.K_ed_Gain * 0.0;

    /* Gain: '<S6>/K_ei' */
    Lab1_CD_Step02_B.K_ei = Lab1_CD_Step02_P.K_ei_Gain * rtb_Sum_k;

    /* Gain: '<S3>/Elevation: Count to rad' */
    Lab1_CD_Step02_B.ElevationCounttorad =
      Lab1_CD_Step02_P.ElevationCounttorad_Gain * rtb_HILReadEncoderTimebase_o3;

    /* Gain: '<S3>/Travel: Count to rad' */
    Lab1_CD_Step02_B.TravelCounttorad = Lab1_CD_Step02_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Vs0'
   *  Integrator: '<S6>/Integrator'
   *  Sum: '<S6>/Sum'
   */
  rtb_e = ((Lab1_CD_Step02_X.Integrator_CSTATE + Lab1_CD_Step02_B.K_ep) -
           Lab1_CD_Step02_B.K_ed) + Lab1_CD_Step02_P.Vs0_Value;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  u0 = (rtb_e - rtb_Frontgain) * Lab1_CD_Step02_P.Frontgain_Gain;

  /* Saturate: '<S3>/Front motor: Saturation' */
  if (u0 > Lab1_CD_Step02_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S3>/Front motor: Saturation' */
    Lab1_CD_Step02_B.FrontmotorSaturation =
      Lab1_CD_Step02_P.FrontmotorSaturation_UpperSat;
  } else if (u0 < Lab1_CD_Step02_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S3>/Front motor: Saturation' */
    Lab1_CD_Step02_B.FrontmotorSaturation =
      Lab1_CD_Step02_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S3>/Front motor: Saturation' */
    Lab1_CD_Step02_B.FrontmotorSaturation = u0;
  }

  /* End of Saturate: '<S3>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  u0 = (rtb_e + rtb_Frontgain) * Lab1_CD_Step02_P.Backgain_Gain;

  /* Saturate: '<S3>/Back motor: Saturation' */
  if (u0 > Lab1_CD_Step02_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S3>/Back motor: Saturation' */
    Lab1_CD_Step02_B.BackmotorSaturation =
      Lab1_CD_Step02_P.BackmotorSaturation_UpperSat;
  } else if (u0 < Lab1_CD_Step02_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S3>/Back motor: Saturation' */
    Lab1_CD_Step02_B.BackmotorSaturation =
      Lab1_CD_Step02_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S3>/Back motor: Saturation' */
    Lab1_CD_Step02_B.BackmotorSaturation = u0;
  }

  /* End of Saturate: '<S3>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(Lab1_CD_Step02_M)) {
    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: Lab1_CD_Step02/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      Lab1_CD_Step02_DW.HILWriteAnalog_Buffer[0] =
        Lab1_CD_Step02_B.FrontmotorSaturation;
      Lab1_CD_Step02_DW.HILWriteAnalog_Buffer[1] =
        Lab1_CD_Step02_B.BackmotorSaturation;
      result = hil_write_analog(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILWriteAnalog_channels, 2,
        &Lab1_CD_Step02_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
      }
    }
  }
}

/* Model update function for TID0 */
void Lab1_CD_Step02_update0(void)      /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(Lab1_CD_Step02_M)) {
    rt_ertODEUpdateContinuousStates(&Lab1_CD_Step02_M->solverInfo);
  }

  /* Update absolute time */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab1_CD_Step02_M->Timing.clockTick0)) {
    ++Lab1_CD_Step02_M->Timing.clockTickH0;
  }

  Lab1_CD_Step02_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Lab1_CD_Step02_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab1_CD_Step02_M->Timing.clockTick1)) {
    ++Lab1_CD_Step02_M->Timing.clockTickH1;
  }

  Lab1_CD_Step02_M->Timing.t[1] = Lab1_CD_Step02_M->Timing.clockTick1 *
    Lab1_CD_Step02_M->Timing.stepSize1 + Lab1_CD_Step02_M->Timing.clockTickH1 *
    Lab1_CD_Step02_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void Lab1_CD_Step02_derivatives(void)
{
  XDot_Lab1_CD_Step02_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_Lab1_CD_Step02_T *) Lab1_CD_Step02_M->derivs);

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += Lab1_CD_Step02_P.PitchTransferFcn_A *
    Lab1_CD_Step02_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += Lab1_CD_Step02_B.PitchCounttorad;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  lsat = (Lab1_CD_Step02_X.Integrator_CSTATE <=
          Lab1_CD_Step02_P.Integrator_LowerSat);
  usat = (Lab1_CD_Step02_X.Integrator_CSTATE >=
          Lab1_CD_Step02_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (Lab1_CD_Step02_B.K_ei > 0.0)) || (usat &&
       (Lab1_CD_Step02_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = Lab1_CD_Step02_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S6>/Integrator' */

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    Lab1_CD_Step02_P.ElevationTransferFcn_A *
    Lab1_CD_Step02_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += Lab1_CD_Step02_B.ElevationCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += Lab1_CD_Step02_P.TravelTransferFcn_A *
    Lab1_CD_Step02_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += Lab1_CD_Step02_B.TravelCounttorad;
}

/* Model output function for TID2 */
void Lab1_CD_Step02_output2(void)      /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_GameController_o4;
  real_T rtb_GameController_o5;

  /* S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab1_CD_Step02/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab1_CD_Step02_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(Lab1_CD_Step02_DW.GameController_Controller,
        &state, &new_data);
      if (result < 0) {
        new_data = false;
      }

      rtb_GameController_o4 = state.x;
      rtb_GameController_o5 = state.y;
    } else {
      rtb_GameController_o4 = 0;
      rtb_GameController_o5 = 0;
    }
  }
}

/* Model update function for TID2 */
void Lab1_CD_Step02_update2(void)      /* Sample time: [0.01s, 0.0s] */
{
  /* Update absolute time */
  /* The "clockTick2" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick2"
   * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick2 and the high bits
   * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab1_CD_Step02_M->Timing.clockTick2)) {
    ++Lab1_CD_Step02_M->Timing.clockTickH2;
  }

  Lab1_CD_Step02_M->Timing.t[2] = Lab1_CD_Step02_M->Timing.clockTick2 *
    Lab1_CD_Step02_M->Timing.stepSize2 + Lab1_CD_Step02_M->Timing.clockTickH2 *
    Lab1_CD_Step02_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void Lab1_CD_Step02_output(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab1_CD_Step02_output0();
    break;

   case 2 :
    Lab1_CD_Step02_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void Lab1_CD_Step02_update(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab1_CD_Step02_update0();
    break;

   case 2 :
    Lab1_CD_Step02_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void Lab1_CD_Step02_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab1_CD_Step02/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab1_CD_Step02_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Lab1_CD_Step02_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab1_CD_Step02_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
      return;
    }

    if ((Lab1_CD_Step02_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab1_CD_Step02_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab1_CD_Step02_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab1_CD_Step02_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab1_CD_Step02_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_AIChannels, 8U,
        &Lab1_CD_Step02_DW.HILInitialize_AIMinimums[0],
        &Lab1_CD_Step02_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_CD_Step02_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab1_CD_Step02_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab1_CD_Step02_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab1_CD_Step02_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab1_CD_Step02_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_AOChannels, 8U,
        &Lab1_CD_Step02_DW.HILInitialize_AOMinimums[0],
        &Lab1_CD_Step02_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_CD_Step02_P.HILInitialize_AOStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab1_CD_Step02_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_AOChannels, 8U,
        &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if (Lab1_CD_Step02_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab1_CD_Step02_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab1_CD_Step02_DW.HILInitialize_Card,
         Lab1_CD_Step02_P.HILInitialize_AOChannels, 8U,
         &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_CD_Step02_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab1_CD_Step02_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab1_CD_Step02_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Lab1_CD_Step02_DW.HILInitialize_Card,
         Lab1_CD_Step02_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Lab1_CD_Step02_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_CD_Step02_P.HILInitialize_EIStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab1_CD_Step02_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab1_CD_Step02_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_EIChannels, 8U,
        &Lab1_CD_Step02_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_CD_Step02_P.HILInitialize_POPStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab1_CD_Step02_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab1_CD_Step02_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab1_CD_Step02_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab1_CD_Step02_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &Lab1_CD_Step02_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab1_CD_Step02_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Lab1_CD_Step02_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab1_CD_Step02_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = Lab1_CD_Step02_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab1_CD_Step02_DW.HILInitialize_Card,
          &Lab1_CD_Step02_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab1_CD_Step02_DW.HILInitialize_Card,
          &Lab1_CD_Step02_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab1_CD_Step02_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab1_CD_Step02_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Lab1_CD_Step02_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab1_CD_Step02_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab1_CD_Step02_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab1_CD_Step02_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab1_CD_Step02_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Lab1_CD_Step02_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab1_CD_Step02_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab1_CD_Step02_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab1_CD_Step02_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_CD_Step02_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_POChannels, 8U,
        &Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[0],
        &Lab1_CD_Step02_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_CD_Step02_P.HILInitialize_POStart && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab1_CD_Step02_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_CD_Step02_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab1_CD_Step02_DW.HILInitialize_Card,
        Lab1_CD_Step02_P.HILInitialize_POChannels, 8U,
        &Lab1_CD_Step02_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }

    if (Lab1_CD_Step02_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab1_CD_Step02_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_CD_Step02_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab1_CD_Step02_DW.HILInitialize_Card,
         Lab1_CD_Step02_P.HILInitialize_POChannels, 8U,
         &Lab1_CD_Step02_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: Lab1_CD_Step02/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(Lab1_CD_Step02_DW.HILInitialize_Card,
      Lab1_CD_Step02_P.HILReadEncoderTimebase_SamplesI,
      Lab1_CD_Step02_P.HILReadEncoderTimebase_Channels, 3,
      &Lab1_CD_Step02_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Lab1_CD_Step02_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (Lab1_CD_Step02_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
    }
  }

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab1_CD_Step02/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab1_CD_Step02_P.GameController_Enabled) {
      t_double deadzone[6];
      t_double saturation[6];
      t_int index;
      t_error result;
      for (index = 0; index < 6; index++) {
        deadzone[index] = -1;
      }

      for (index = 0; index < 6; index++) {
        saturation[index] = -1;
      }

      result = game_controller_open
        (Lab1_CD_Step02_P.GameController_ControllerNumber,
         Lab1_CD_Step02_P.GameController_BufferSize, deadzone, saturation,
         Lab1_CD_Step02_P.GameController_AutoCenter, 0, 1.0,
         &Lab1_CD_Step02_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  Lab1_CD_Step02_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  Lab1_CD_Step02_X.Integrator_CSTATE = Lab1_CD_Step02_P.Integrator_IC;

  /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  Lab1_CD_Step02_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  Lab1_CD_Step02_X.TravelTransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void Lab1_CD_Step02_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab1_CD_Step02/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab1_CD_Step02_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab1_CD_Step02_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab1_CD_Step02_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab1_CD_Step02_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab1_CD_Step02_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab1_CD_Step02_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab1_CD_Step02_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_CD_Step02_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(Lab1_CD_Step02_DW.HILInitialize_Card
                         , Lab1_CD_Step02_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab1_CD_Step02_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0]
                         , &Lab1_CD_Step02_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab1_CD_Step02_DW.HILInitialize_Card,
            Lab1_CD_Step02_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Lab1_CD_Step02_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab1_CD_Step02_DW.HILInitialize_Card,
            Lab1_CD_Step02_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab1_CD_Step02_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab1_CD_Step02_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab1_CD_Step02_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab1_CD_Step02_DW.HILInitialize_Card);
    hil_close(Lab1_CD_Step02_DW.HILInitialize_Card);
    Lab1_CD_Step02_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab1_CD_Step02/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab1_CD_Step02_P.GameController_Enabled) {
      game_controller_close(Lab1_CD_Step02_DW.GameController_Controller);
      Lab1_CD_Step02_DW.GameController_Controller = NULL;
    }
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
  if (tid == 1)
    tid = 0;
  Lab1_CD_Step02_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  Lab1_CD_Step02_update(tid);
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
  Lab1_CD_Step02_initialize();
}

void MdlTerminate(void)
{
  Lab1_CD_Step02_terminate();
}

/* Registration function */
RT_MODEL_Lab1_CD_Step02_T *Lab1_CD_Step02(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  Lab1_CD_Step02_P.Integrator_UpperSat = rtInf;
  Lab1_CD_Step02_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)Lab1_CD_Step02_M, 0,
                sizeof(RT_MODEL_Lab1_CD_Step02_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Lab1_CD_Step02_M->solverInfo,
                          &Lab1_CD_Step02_M->Timing.simTimeStep);
    rtsiSetTPtr(&Lab1_CD_Step02_M->solverInfo, &rtmGetTPtr(Lab1_CD_Step02_M));
    rtsiSetStepSizePtr(&Lab1_CD_Step02_M->solverInfo,
                       &Lab1_CD_Step02_M->Timing.stepSize0);
    rtsiSetdXPtr(&Lab1_CD_Step02_M->solverInfo, &Lab1_CD_Step02_M->derivs);
    rtsiSetContStatesPtr(&Lab1_CD_Step02_M->solverInfo, (real_T **)
                         &Lab1_CD_Step02_M->contStates);
    rtsiSetNumContStatesPtr(&Lab1_CD_Step02_M->solverInfo,
      &Lab1_CD_Step02_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Lab1_CD_Step02_M->solverInfo,
      &Lab1_CD_Step02_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Lab1_CD_Step02_M->solverInfo,
      &Lab1_CD_Step02_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Lab1_CD_Step02_M->solverInfo,
      &Lab1_CD_Step02_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Lab1_CD_Step02_M->solverInfo, (&rtmGetErrorStatus
      (Lab1_CD_Step02_M)));
    rtsiSetRTModelPtr(&Lab1_CD_Step02_M->solverInfo, Lab1_CD_Step02_M);
  }

  rtsiSetSimTimeStep(&Lab1_CD_Step02_M->solverInfo, MAJOR_TIME_STEP);
  Lab1_CD_Step02_M->intgData.f[0] = Lab1_CD_Step02_M->odeF[0];
  Lab1_CD_Step02_M->contStates = ((real_T *) &Lab1_CD_Step02_X);
  rtsiSetSolverData(&Lab1_CD_Step02_M->solverInfo, (void *)
                    &Lab1_CD_Step02_M->intgData);
  rtsiSetSolverName(&Lab1_CD_Step02_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab1_CD_Step02_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    Lab1_CD_Step02_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab1_CD_Step02_M->Timing.sampleTimes =
      (&Lab1_CD_Step02_M->Timing.sampleTimesArray[0]);
    Lab1_CD_Step02_M->Timing.offsetTimes =
      (&Lab1_CD_Step02_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab1_CD_Step02_M->Timing.sampleTimes[0] = (0.0);
    Lab1_CD_Step02_M->Timing.sampleTimes[1] = (0.002);
    Lab1_CD_Step02_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    Lab1_CD_Step02_M->Timing.offsetTimes[0] = (0.0);
    Lab1_CD_Step02_M->Timing.offsetTimes[1] = (0.0);
    Lab1_CD_Step02_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(Lab1_CD_Step02_M, &Lab1_CD_Step02_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab1_CD_Step02_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      Lab1_CD_Step02_M->Timing.perTaskSampleHitsArray;
    Lab1_CD_Step02_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    Lab1_CD_Step02_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab1_CD_Step02_M, -1);
  Lab1_CD_Step02_M->Timing.stepSize0 = 0.002;
  Lab1_CD_Step02_M->Timing.stepSize1 = 0.002;
  Lab1_CD_Step02_M->Timing.stepSize2 = 0.01;
  Lab1_CD_Step02_M->solverInfoPtr = (&Lab1_CD_Step02_M->solverInfo);
  Lab1_CD_Step02_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Lab1_CD_Step02_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Lab1_CD_Step02_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  Lab1_CD_Step02_M->blockIO = ((void *) &Lab1_CD_Step02_B);

  {
    Lab1_CD_Step02_B.PitchCounttorad = 0.0;
    Lab1_CD_Step02_B.K_ep = 0.0;
    Lab1_CD_Step02_B.K_ed = 0.0;
    Lab1_CD_Step02_B.K_ei = 0.0;
    Lab1_CD_Step02_B.ElevationCounttorad = 0.0;
    Lab1_CD_Step02_B.TravelCounttorad = 0.0;
    Lab1_CD_Step02_B.FrontmotorSaturation = 0.0;
    Lab1_CD_Step02_B.BackmotorSaturation = 0.0;
  }

  /* parameters */
  Lab1_CD_Step02_M->defaultParam = ((real_T *)&Lab1_CD_Step02_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Lab1_CD_Step02_X;
    Lab1_CD_Step02_M->contStates = (x);
    (void) memset((void *)&Lab1_CD_Step02_X, 0,
                  sizeof(X_Lab1_CD_Step02_T));
  }

  /* states (dwork) */
  Lab1_CD_Step02_M->dwork = ((void *) &Lab1_CD_Step02_DW);
  (void) memset((void *)&Lab1_CD_Step02_DW, 0,
                sizeof(DW_Lab1_CD_Step02_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_CD_Step02_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  Lab1_CD_Step02_DW.HILWriteAnalog_Buffer[0] = 0.0;
  Lab1_CD_Step02_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* Initialize Sizes */
  Lab1_CD_Step02_M->Sizes.numContStates = (4);/* Number of continuous states */
  Lab1_CD_Step02_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Lab1_CD_Step02_M->Sizes.numY = (0);  /* Number of model outputs */
  Lab1_CD_Step02_M->Sizes.numU = (0);  /* Number of model inputs */
  Lab1_CD_Step02_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab1_CD_Step02_M->Sizes.numSampTimes = (3);/* Number of sample times */
  Lab1_CD_Step02_M->Sizes.numBlocks = (29);/* Number of blocks */
  Lab1_CD_Step02_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  Lab1_CD_Step02_M->Sizes.numBlockPrms = (138);/* Sum of parameter "widths" */
  return Lab1_CD_Step02_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
