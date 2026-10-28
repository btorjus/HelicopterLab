/*
 * heli_p2_lqr.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_p2_lqr".
 *
 * Model version              : 11.10
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Sep 23 19:15:53 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "heli_p2_lqr.h"
#include "heli_p2_lqr_private.h"
#include "heli_p2_lqr_dt.h"

/* Block signals (default storage) */
B_heli_p2_lqr_T heli_p2_lqr_B;

/* Continuous states */
X_heli_p2_lqr_T heli_p2_lqr_X;

/* Block states (default storage) */
DW_heli_p2_lqr_T heli_p2_lqr_DW;

/* Real-time model */
static RT_MODEL_heli_p2_lqr_T heli_p2_lqr_M_;
RT_MODEL_heli_p2_lqr_T *const heli_p2_lqr_M = &heli_p2_lqr_M_;
static void rate_monotonic_scheduler(void);

/*
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

time_T rt_SimUpdateDiscreteEvents(
  int_T rtmNumSampTimes, void *rtmTimingData, int_T *rtmSampleHitPtr, int_T
  *rtmPerTaskSampleHits )
{
  rtmSampleHitPtr[1] = rtmStepTask(heli_p2_lqr_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(heli_p2_lqr_M, 2);
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
  /* To ensure a deterministic data transfer between two rates,
   * data is transferred at the priority of a fast task and the frequency
   * of the slow task.  The following flags indicate when the data transfer
   * happens.  That is, a rate interaction flag is set true when both rates
   * will run, and false otherwise.
   */

  /* tid 1 shares data with slower tid rate: 2 */
  if (heli_p2_lqr_M->Timing.TaskCounters.TID[1] == 0) {
    heli_p2_lqr_M->Timing.RateInteraction.TID1_2 =
      (heli_p2_lqr_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    heli_p2_lqr_M->Timing.perTaskSampleHits[5] =
      heli_p2_lqr_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (heli_p2_lqr_M->Timing.TaskCounters.TID[2])++;
  if ((heli_p2_lqr_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    heli_p2_lqr_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 3;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  heli_p2_lqr_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void heli_p2_lqr_output0(void)         /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtHeli3D[6];
  real_T rtb_TmpSignalConversionAtp2RunI[4];
  real_T rtb_PulseGenerator;
  real_T rtb_Backgain;
  real_T rtb_Frontgain;
  real_T u0;
  int32_T i;
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    /* set solver stop time */
    if (!(heli_p2_lqr_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&heli_p2_lqr_M->solverInfo,
                            ((heli_p2_lqr_M->Timing.clockTickH0 + 1) *
        heli_p2_lqr_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&heli_p2_lqr_M->solverInfo,
                            ((heli_p2_lqr_M->Timing.clockTick0 + 1) *
        heli_p2_lqr_M->Timing.stepSize0 + heli_p2_lqr_M->Timing.clockTickH0 *
        heli_p2_lqr_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(heli_p2_lqr_M)) {
    heli_p2_lqr_M->Timing.t[0] = rtsiGetT(&heli_p2_lqr_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: heli_p2_lqr/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(heli_p2_lqr_DW.HILReadEncoderTimebase_Task,
        1, &heli_p2_lqr_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          heli_p2_lqr_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          heli_p2_lqr_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_PulseGenerator = heli_p2_lqr_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S2>/Travel: Count to rad' */
    heli_p2_lqr_B.TravelCounttorad = heli_p2_lqr_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S2>/Pitch: Count to rad' */
    heli_p2_lqr_B.PitchCounttorad = heli_p2_lqr_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;
  }

  /* TransferFcn: '<S2>/Travel: Transfer Fcn' */
  heli_p2_lqr_B.TravelTransferFcn = 0.0;
  heli_p2_lqr_B.TravelTransferFcn += heli_p2_lqr_P.TravelTransferFcn_C *
    heli_p2_lqr_X.TravelTransferFcn_CSTATE;
  heli_p2_lqr_B.TravelTransferFcn += heli_p2_lqr_P.TravelTransferFcn_D *
    heli_p2_lqr_B.TravelCounttorad;

  /* TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  heli_p2_lqr_B.PitchTransferFcn = 0.0;
  heli_p2_lqr_B.PitchTransferFcn += heli_p2_lqr_P.PitchTransferFcn_C *
    heli_p2_lqr_X.PitchTransferFcn_CSTATE;
  heli_p2_lqr_B.PitchTransferFcn += heli_p2_lqr_P.PitchTransferFcn_D *
    heli_p2_lqr_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    /* Gain: '<S2>/Elevation: Count to rad' */
    heli_p2_lqr_B.ElevationCounttorad = heli_p2_lqr_P.ElevationCounttorad_Gain *
      rtb_PulseGenerator;
  }

  /* TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  heli_p2_lqr_B.ElevationTransferFcn = 0.0;
  heli_p2_lqr_B.ElevationTransferFcn += heli_p2_lqr_P.ElevationTransferFcn_C *
    heli_p2_lqr_X.ElevationTransferFcn_CSTATE;
  heli_p2_lqr_B.ElevationTransferFcn += heli_p2_lqr_P.ElevationTransferFcn_D *
    heli_p2_lqr_B.ElevationCounttorad;

  /* RateTransition: '<S3>/Rate Transition: x' */
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    /* SignalConversion generated from: '<Root>/Heli3DLog' */
    rtb_TmpSignalConversionAtHeli3D[0] = heli_p2_lqr_B.TravelCounttorad;
    rtb_TmpSignalConversionAtHeli3D[1] = heli_p2_lqr_B.TravelTransferFcn;
    rtb_TmpSignalConversionAtHeli3D[2] = heli_p2_lqr_B.PitchCounttorad;
    rtb_TmpSignalConversionAtHeli3D[3] = heli_p2_lqr_B.PitchTransferFcn;
    rtb_TmpSignalConversionAtHeli3D[4] = heli_p2_lqr_B.ElevationCounttorad;
    rtb_TmpSignalConversionAtHeli3D[5] = heli_p2_lqr_B.ElevationTransferFcn;

    /* ToFile: '<Root>/Heli3DLog' */
    if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
      if (rtmIsMajorTimeStep(heli_p2_lqr_M) ) {
        {
          if (!(++heli_p2_lqr_DW.Heli3DLog_IWORK.Decimation % 1) &&
              (heli_p2_lqr_DW.Heli3DLog_IWORK.Count * (6 + 1)) + 1 < 100000000 )
          {
            FILE *fp = (FILE *) heli_p2_lqr_DW.Heli3DLog_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[6 + 1];
              heli_p2_lqr_DW.Heli3DLog_IWORK.Decimation = 0;
              u[0] = heli_p2_lqr_M->Timing.t[1];
              u[1] = rtb_TmpSignalConversionAtHeli3D[0];
              u[2] = rtb_TmpSignalConversionAtHeli3D[1];
              u[3] = rtb_TmpSignalConversionAtHeli3D[2];
              u[4] = rtb_TmpSignalConversionAtHeli3D[3];
              u[5] = rtb_TmpSignalConversionAtHeli3D[4];
              u[6] = rtb_TmpSignalConversionAtHeli3D[5];
              if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
                rtmSetErrorStatus(heli_p2_lqr_M,
                                  "Error writing to MAT-file HeliRun.mat");
                return;
              }

              if (((++heli_p2_lqr_DW.Heli3DLog_IWORK.Count) * (6 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file HeliRun.mat.\n");
              }
            }
          }
        }
      }
    }

    if (heli_p2_lqr_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S3>/Rate Transition: x' */
      heli_p2_lqr_B.RateTransitionx = heli_p2_lqr_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S3>/Dead Zone: x' */
    if (heli_p2_lqr_B.RateTransitionx > heli_p2_lqr_P.DeadZonex_End) {
      /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
      rtb_PulseGenerator = heli_p2_lqr_B.RateTransitionx -
        heli_p2_lqr_P.DeadZonex_End;
    } else if (heli_p2_lqr_B.RateTransitionx >= heli_p2_lqr_P.DeadZonex_Start) {
      /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
      rtb_PulseGenerator = 0.0;
    } else {
      /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
      rtb_PulseGenerator = heli_p2_lqr_B.RateTransitionx -
        heli_p2_lqr_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: x' */

    /* Gain: '<S3>/Joystick_gain_x' incorporates:
     *  Gain: '<S3>/Gain: x'
     */
    heli_p2_lqr_B.Joystick_gain_x = heli_p2_lqr_P.Gainx_Gain *
      rtb_PulseGenerator * heli_p2_lqr_P.Joystick_gain_x;
  }

  /* End of RateTransition: '<S3>/Rate Transition: x' */

  /* ManualSwitch: '<Root>/Manual Switch' */
  if (heli_p2_lqr_P.ManualSwitch_CurrentSetting == 1) {
    /* Step: '<Root>/Step' */
    if (heli_p2_lqr_M->Timing.t[0] < heli_p2_lqr_P.Step_Time) {
      /* ManualSwitch: '<Root>/Manual Switch' */
      heli_p2_lqr_B.ManualSwitch = heli_p2_lqr_P.Step_Y0;
    } else {
      /* ManualSwitch: '<Root>/Manual Switch' */
      heli_p2_lqr_B.ManualSwitch = heli_p2_lqr_P.pc_step;
    }

    /* End of Step: '<Root>/Step' */
  } else {
    /* ManualSwitch: '<Root>/Manual Switch' */
    heli_p2_lqr_B.ManualSwitch = heli_p2_lqr_B.Joystick_gain_x;
  }

  /* End of ManualSwitch: '<Root>/Manual Switch' */
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    /* RateTransition: '<S3>/Rate Transition: y' */
    if (heli_p2_lqr_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S3>/Rate Transition: y' */
      heli_p2_lqr_B.RateTransitiony = heli_p2_lqr_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S3>/Rate Transition: y' */

    /* DeadZone: '<S3>/Dead Zone: y' */
    if (heli_p2_lqr_B.RateTransitiony > heli_p2_lqr_P.DeadZoney_End) {
      /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
      rtb_PulseGenerator = heli_p2_lqr_B.RateTransitiony -
        heli_p2_lqr_P.DeadZoney_End;
    } else if (heli_p2_lqr_B.RateTransitiony >= heli_p2_lqr_P.DeadZoney_Start) {
      /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
      rtb_PulseGenerator = 0.0;
    } else {
      /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
      rtb_PulseGenerator = heli_p2_lqr_B.RateTransitiony -
        heli_p2_lqr_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S3>/Dead Zone: y' */

    /* Gain: '<S3>/Joystick_gain_y' incorporates:
     *  Gain: '<S3>/Gain: y'
     */
    heli_p2_lqr_B.Joystick_gain_y = heli_p2_lqr_P.Gainy_Gain *
      rtb_PulseGenerator * heli_p2_lqr_P.Joystick_gain_y;

    /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
    rtb_PulseGenerator = (heli_p2_lqr_DW.clockTickCounter <
                          heli_p2_lqr_P.PulseGenerator_Duty) &&
      (heli_p2_lqr_DW.clockTickCounter >= 0) ? heli_p2_lqr_P.edot_pulse : 0.0;

    /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
    if (heli_p2_lqr_DW.clockTickCounter >= heli_p2_lqr_P.PulseGenerator_Period -
        1.0) {
      heli_p2_lqr_DW.clockTickCounter = 0;
    } else {
      heli_p2_lqr_DW.clockTickCounter++;
    }

    /* ManualSwitch: '<Root>/Manual Switch1' */
    if (heli_p2_lqr_P.ManualSwitch1_CurrentSetting == 1) {
      /* ManualSwitch: '<Root>/Manual Switch1' */
      heli_p2_lqr_B.ManualSwitch1 = heli_p2_lqr_B.Joystick_gain_y;
    } else {
      /* ManualSwitch: '<Root>/Manual Switch1' */
      heli_p2_lqr_B.ManualSwitch1 = rtb_PulseGenerator;
    }

    /* End of ManualSwitch: '<Root>/Manual Switch1' */
  }

  for (i = 0; i < 2; i++) {
    /* Sum: '<S4>/Subtract' incorporates:
     *  Gain: '<S4>/Gain'
     *  Gain: '<S4>/Multiply'
     *  SignalConversion generated from: '<S4>/Gain'
     *  SignalConversion generated from: '<S4>/Multiply'
     */
    heli_p2_lqr_B.u[i] = (heli_p2_lqr_P.F[i + 2] * heli_p2_lqr_B.ManualSwitch1 +
                          heli_p2_lqr_P.F[i] * heli_p2_lqr_B.ManualSwitch) -
      (heli_p2_lqr_P.K[i + 4] * heli_p2_lqr_B.ElevationTransferFcn +
       (heli_p2_lqr_P.K[i + 2] * heli_p2_lqr_B.PitchTransferFcn +
        heli_p2_lqr_P.K[i] * heli_p2_lqr_B.PitchCounttorad));
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_trim'
   */
  rtb_Frontgain = heli_p2_lqr_P.Vd_trim + heli_p2_lqr_B.u[1];

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Vs0'
   */
  rtb_Backgain = heli_p2_lqr_B.u[0] + heli_p2_lqr_P.Vs0;
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  u0 = (rtb_Backgain - rtb_Frontgain) * heli_p2_lqr_P.Frontgain_Gain;

  /* Saturate: '<S2>/Front motor: Saturation' */
  if (u0 > heli_p2_lqr_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S2>/Front motor: Saturation' */
    heli_p2_lqr_B.FrontmotorSaturation =
      heli_p2_lqr_P.FrontmotorSaturation_UpperSat;
  } else if (u0 < heli_p2_lqr_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S2>/Front motor: Saturation' */
    heli_p2_lqr_B.FrontmotorSaturation =
      heli_p2_lqr_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S2>/Front motor: Saturation' */
    heli_p2_lqr_B.FrontmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  u0 = (rtb_Backgain + rtb_Frontgain) * heli_p2_lqr_P.Backgain_Gain;

  /* Saturate: '<S2>/Back motor: Saturation' */
  if (u0 > heli_p2_lqr_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S2>/Back motor: Saturation' */
    heli_p2_lqr_B.BackmotorSaturation =
      heli_p2_lqr_P.BackmotorSaturation_UpperSat;
  } else if (u0 < heli_p2_lqr_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S2>/Back motor: Saturation' */
    heli_p2_lqr_B.BackmotorSaturation =
      heli_p2_lqr_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S2>/Back motor: Saturation' */
    heli_p2_lqr_B.BackmotorSaturation = u0;
  }

  /* End of Saturate: '<S2>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: heli_p2_lqr/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      heli_p2_lqr_DW.HILWriteAnalog_Buffer[0] =
        heli_p2_lqr_B.FrontmotorSaturation;
      heli_p2_lqr_DW.HILWriteAnalog_Buffer[1] =
        heli_p2_lqr_B.BackmotorSaturation;
      result = hil_write_analog(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILWriteAnalog_channels, 2,
        &heli_p2_lqr_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
      }
    }

    /* SignalConversion generated from: '<S4>/p2Run' */
    rtb_TmpSignalConversionAtp2RunI[0] = heli_p2_lqr_B.ManualSwitch;
    rtb_TmpSignalConversionAtp2RunI[1] = heli_p2_lqr_B.ManualSwitch1;
    rtb_TmpSignalConversionAtp2RunI[2] = heli_p2_lqr_B.u[0];
    rtb_TmpSignalConversionAtp2RunI[3] = heli_p2_lqr_B.u[1];

    /* ToFile: '<S4>/p2Run' */
    if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
      if (rtmIsMajorTimeStep(heli_p2_lqr_M) ) {
        {
          if (!(++heli_p2_lqr_DW.p2Run_IWORK.Decimation % 1) &&
              (heli_p2_lqr_DW.p2Run_IWORK.Count * (4 + 1)) + 1 < 100000000 ) {
            FILE *fp = (FILE *) heli_p2_lqr_DW.p2Run_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[4 + 1];
              heli_p2_lqr_DW.p2Run_IWORK.Decimation = 0;
              u[0] = heli_p2_lqr_M->Timing.t[1];
              u[1] = rtb_TmpSignalConversionAtp2RunI[0];
              u[2] = rtb_TmpSignalConversionAtp2RunI[1];
              u[3] = rtb_TmpSignalConversionAtp2RunI[2];
              u[4] = rtb_TmpSignalConversionAtp2RunI[3];
              if (fwrite(u, sizeof(real_T), 4 + 1, fp) != 4 + 1) {
                rtmSetErrorStatus(heli_p2_lqr_M,
                                  "Error writing to MAT-file p2Run.mat");
                return;
              }

              if (((++heli_p2_lqr_DW.p2Run_IWORK.Count) * (4 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file p2Run.mat.\n");
              }
            }
          }
        }
      }
    }
  }
}

/* Model update function for TID0 */
void heli_p2_lqr_update0(void)         /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(heli_p2_lqr_M)) {
    rt_ertODEUpdateContinuousStates(&heli_p2_lqr_M->solverInfo);
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
  if (!(++heli_p2_lqr_M->Timing.clockTick0)) {
    ++heli_p2_lqr_M->Timing.clockTickH0;
  }

  heli_p2_lqr_M->Timing.t[0] = rtsiGetSolverStopTime(&heli_p2_lqr_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++heli_p2_lqr_M->Timing.clockTick1)) {
    ++heli_p2_lqr_M->Timing.clockTickH1;
  }

  heli_p2_lqr_M->Timing.t[1] = heli_p2_lqr_M->Timing.clockTick1 *
    heli_p2_lqr_M->Timing.stepSize1 + heli_p2_lqr_M->Timing.clockTickH1 *
    heli_p2_lqr_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void heli_p2_lqr_derivatives(void)
{
  XDot_heli_p2_lqr_T *_rtXdot;
  _rtXdot = ((XDot_heli_p2_lqr_T *) heli_p2_lqr_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += heli_p2_lqr_P.TravelTransferFcn_A *
    heli_p2_lqr_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += heli_p2_lqr_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += heli_p2_lqr_P.PitchTransferFcn_A *
    heli_p2_lqr_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += heli_p2_lqr_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_p2_lqr_P.ElevationTransferFcn_A *
    heli_p2_lqr_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += heli_p2_lqr_B.ElevationCounttorad;
}

/* Model output function for TID2 */
void heli_p2_lqr_output2(void)         /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_GameController_o4;
  real_T rtb_GameController_o5;

  /* S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: heli_p2_lqr/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_p2_lqr_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(heli_p2_lqr_DW.GameController_Controller,
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

  /* RateTransition: '<S3>/Rate Transition: x' */
  heli_p2_lqr_DW.RateTransitionx_Buffer0 = rtb_GameController_o4;

  /* RateTransition: '<S3>/Rate Transition: y' */
  heli_p2_lqr_DW.RateTransitiony_Buffer0 = rtb_GameController_o5;
}

/* Model update function for TID2 */
void heli_p2_lqr_update2(void)         /* Sample time: [0.01s, 0.0s] */
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
  if (!(++heli_p2_lqr_M->Timing.clockTick2)) {
    ++heli_p2_lqr_M->Timing.clockTickH2;
  }

  heli_p2_lqr_M->Timing.t[2] = heli_p2_lqr_M->Timing.clockTick2 *
    heli_p2_lqr_M->Timing.stepSize2 + heli_p2_lqr_M->Timing.clockTickH2 *
    heli_p2_lqr_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void heli_p2_lqr_output(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_p2_lqr_output0();
    break;

   case 2 :
    heli_p2_lqr_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void heli_p2_lqr_update(int_T tid)
{
  switch (tid) {
   case 0 :
    heli_p2_lqr_update0();
    break;

   case 2 :
    heli_p2_lqr_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void heli_p2_lqr_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_p2_lqr/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &heli_p2_lqr_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(heli_p2_lqr_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(heli_p2_lqr_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
      return;
    }

    if ((heli_p2_lqr_P.HILInitialize_AIPStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &heli_p2_lqr_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (heli_p2_lqr_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &heli_p2_lqr_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = heli_p2_lqr_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_AIChannels, 8U,
        &heli_p2_lqr_DW.HILInitialize_AIMinimums[0],
        &heli_p2_lqr_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if ((heli_p2_lqr_P.HILInitialize_AOPStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &heli_p2_lqr_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (heli_p2_lqr_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &heli_p2_lqr_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = heli_p2_lqr_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_AOChannels, 8U,
        &heli_p2_lqr_DW.HILInitialize_AOMinimums[0],
        &heli_p2_lqr_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if ((heli_p2_lqr_P.HILInitialize_AOStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_p2_lqr_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_p2_lqr_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_AOChannels, 8U,
        &heli_p2_lqr_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if (heli_p2_lqr_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_p2_lqr_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_p2_lqr_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (heli_p2_lqr_DW.HILInitialize_Card,
         heli_p2_lqr_P.HILInitialize_AOChannels, 8U,
         &heli_p2_lqr_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if ((heli_p2_lqr_P.HILInitialize_EIPStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &heli_p2_lqr_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = heli_p2_lqr_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode *)
        &heli_p2_lqr_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if ((heli_p2_lqr_P.HILInitialize_EIStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &heli_p2_lqr_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = heli_p2_lqr_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_EIChannels, 8U,
        &heli_p2_lqr_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if ((heli_p2_lqr_P.HILInitialize_POPStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_p2_lqr_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_p2_lqr_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &heli_p2_lqr_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          heli_p2_lqr_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &heli_p2_lqr_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            heli_p2_lqr_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            heli_p2_lqr_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              heli_p2_lqr_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            heli_p2_lqr_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = (p_HILInitialize_POChannels[i1]);
            heli_p2_lqr_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = heli_p2_lqr_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(heli_p2_lqr_DW.HILInitialize_Card,
          &heli_p2_lqr_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &heli_p2_lqr_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(heli_p2_lqr_DW.HILInitialize_Card,
          &heli_p2_lqr_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &heli_p2_lqr_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &heli_p2_lqr_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = heli_p2_lqr_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues = &heli_p2_lqr_DW.HILInitialize_POAlignValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = heli_p2_lqr_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &heli_p2_lqr_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = heli_p2_lqr_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &heli_p2_lqr_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &heli_p2_lqr_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &heli_p2_lqr_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &heli_p2_lqr_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = heli_p2_lqr_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &heli_p2_lqr_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_p2_lqr_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_POChannels, 8U,
        &heli_p2_lqr_DW.HILInitialize_POSortedFreqs[0],
        &heli_p2_lqr_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if ((heli_p2_lqr_P.HILInitialize_POStart && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_p2_lqr_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_p2_lqr_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(heli_p2_lqr_DW.HILInitialize_Card,
        heli_p2_lqr_P.HILInitialize_POChannels, 8U,
        &heli_p2_lqr_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }

    if (heli_p2_lqr_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_p2_lqr_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_p2_lqr_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (heli_p2_lqr_DW.HILInitialize_Card,
         heli_p2_lqr_P.HILInitialize_POChannels, 8U,
         &heli_p2_lqr_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: heli_p2_lqr/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(heli_p2_lqr_DW.HILInitialize_Card,
      heli_p2_lqr_P.HILReadEncoderTimebase_SamplesI,
      heli_p2_lqr_P.HILReadEncoderTimebase_Channels, 3,
      &heli_p2_lqr_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (heli_p2_lqr_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (heli_p2_lqr_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/Heli3DLog' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "HeliRun.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_p2_lqr_M, "Error creating .mat file HeliRun.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(heli_p2_lqr_M,
                        "Error writing mat file header to file HeliRun.mat");
      return;
    }

    heli_p2_lqr_DW.Heli3DLog_IWORK.Count = 0;
    heli_p2_lqr_DW.Heli3DLog_IWORK.Decimation = -1;
    heli_p2_lqr_DW.Heli3DLog_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S3>/Rate Transition: x' */
  heli_p2_lqr_B.RateTransitionx = heli_p2_lqr_P.RateTransitionx_InitialConditio;

  /* Start for RateTransition: '<S3>/Rate Transition: y' */
  heli_p2_lqr_B.RateTransitiony = heli_p2_lqr_P.RateTransitiony_InitialConditio;

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  heli_p2_lqr_DW.clockTickCounter = -2500;

  /* Start for ToFile: '<S4>/p2Run' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "p2Run.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(heli_p2_lqr_M, "Error creating .mat file p2Run.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 4 + 1, 0, "ans")) {
      rtmSetErrorStatus(heli_p2_lqr_M,
                        "Error writing mat file header to file p2Run.mat");
      return;
    }

    heli_p2_lqr_DW.p2Run_IWORK.Count = 0;
    heli_p2_lqr_DW.p2Run_IWORK.Decimation = -1;
    heli_p2_lqr_DW.p2Run_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: heli_p2_lqr/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_p2_lqr_P.GameController_Enabled) {
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
        (heli_p2_lqr_P.GameController_ControllerNumber,
         heli_p2_lqr_P.GameController_BufferSize, deadzone, saturation,
         heli_p2_lqr_P.GameController_AutoCenter, 0, 1.0,
         &heli_p2_lqr_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  heli_p2_lqr_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  heli_p2_lqr_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  heli_p2_lqr_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition: x' */
  heli_p2_lqr_DW.RateTransitionx_Buffer0 =
    heli_p2_lqr_P.RateTransitionx_InitialConditio;

  /* InitializeConditions for RateTransition: '<S3>/Rate Transition: y' */
  heli_p2_lqr_DW.RateTransitiony_Buffer0 =
    heli_p2_lqr_P.RateTransitiony_InitialConditio;
}

/* Model terminate function */
void heli_p2_lqr_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: heli_p2_lqr/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(heli_p2_lqr_DW.HILInitialize_Card);
    hil_monitor_stop_all(heli_p2_lqr_DW.HILInitialize_Card);
    is_switching = false;
    if ((heli_p2_lqr_P.HILInitialize_AOTerminate && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &heli_p2_lqr_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = heli_p2_lqr_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((heli_p2_lqr_P.HILInitialize_POTerminate && !is_switching) ||
        (heli_p2_lqr_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &heli_p2_lqr_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = heli_p2_lqr_P.HILInitialize_POFinal;
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
      result = hil_write(heli_p2_lqr_DW.HILInitialize_Card
                         , heli_p2_lqr_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , heli_p2_lqr_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &heli_p2_lqr_DW.HILInitialize_AOVoltages[0]
                         , &heli_p2_lqr_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(heli_p2_lqr_DW.HILInitialize_Card,
            heli_p2_lqr_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &heli_p2_lqr_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(heli_p2_lqr_DW.HILInitialize_Card,
            heli_p2_lqr_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &heli_p2_lqr_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(heli_p2_lqr_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(heli_p2_lqr_DW.HILInitialize_Card);
    hil_monitor_delete_all(heli_p2_lqr_DW.HILInitialize_Card);
    hil_close(heli_p2_lqr_DW.HILInitialize_Card);
    heli_p2_lqr_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/Heli3DLog' */
  {
    FILE *fp = (FILE *) heli_p2_lqr_DW.Heli3DLog_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "HeliRun.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_p2_lqr_M, "Error closing MAT-file HeliRun.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_p2_lqr_M, "Error reopening MAT-file HeliRun.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1, heli_p2_lqr_DW.Heli3DLog_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(heli_p2_lqr_M,
                          "Error writing header for ans to MAT-file HeliRun.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_p2_lqr_M, "Error closing MAT-file HeliRun.mat");
        return;
      }

      heli_p2_lqr_DW.Heli3DLog_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S4>/p2Run' */
  {
    FILE *fp = (FILE *) heli_p2_lqr_DW.p2Run_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "p2Run.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_p2_lqr_M, "Error closing MAT-file p2Run.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(heli_p2_lqr_M, "Error reopening MAT-file p2Run.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 4 + 1, heli_p2_lqr_DW.p2Run_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(heli_p2_lqr_M,
                          "Error writing header for ans to MAT-file p2Run.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(heli_p2_lqr_M, "Error closing MAT-file p2Run.mat");
        return;
      }

      heli_p2_lqr_DW.p2Run_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S3>/Game Controller' */

  /* S-Function Block: heli_p2_lqr/Joystick/Game Controller (game_controller_block) */
  {
    if (heli_p2_lqr_P.GameController_Enabled) {
      game_controller_close(heli_p2_lqr_DW.GameController_Controller);
      heli_p2_lqr_DW.GameController_Controller = NULL;
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
  heli_p2_lqr_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  heli_p2_lqr_update(tid);
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
  heli_p2_lqr_initialize();
}

void MdlTerminate(void)
{
  heli_p2_lqr_terminate();
}

/* Registration function */
RT_MODEL_heli_p2_lqr_T *heli_p2_lqr(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)heli_p2_lqr_M, 0,
                sizeof(RT_MODEL_heli_p2_lqr_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&heli_p2_lqr_M->solverInfo,
                          &heli_p2_lqr_M->Timing.simTimeStep);
    rtsiSetTPtr(&heli_p2_lqr_M->solverInfo, &rtmGetTPtr(heli_p2_lqr_M));
    rtsiSetStepSizePtr(&heli_p2_lqr_M->solverInfo,
                       &heli_p2_lqr_M->Timing.stepSize0);
    rtsiSetdXPtr(&heli_p2_lqr_M->solverInfo, &heli_p2_lqr_M->derivs);
    rtsiSetContStatesPtr(&heli_p2_lqr_M->solverInfo, (real_T **)
                         &heli_p2_lqr_M->contStates);
    rtsiSetNumContStatesPtr(&heli_p2_lqr_M->solverInfo,
      &heli_p2_lqr_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&heli_p2_lqr_M->solverInfo,
      &heli_p2_lqr_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&heli_p2_lqr_M->solverInfo,
      &heli_p2_lqr_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&heli_p2_lqr_M->solverInfo,
      &heli_p2_lqr_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&heli_p2_lqr_M->solverInfo, (&rtmGetErrorStatus
      (heli_p2_lqr_M)));
    rtsiSetRTModelPtr(&heli_p2_lqr_M->solverInfo, heli_p2_lqr_M);
  }

  rtsiSetSimTimeStep(&heli_p2_lqr_M->solverInfo, MAJOR_TIME_STEP);
  heli_p2_lqr_M->intgData.f[0] = heli_p2_lqr_M->odeF[0];
  heli_p2_lqr_M->contStates = ((real_T *) &heli_p2_lqr_X);
  rtsiSetSolverData(&heli_p2_lqr_M->solverInfo, (void *)&heli_p2_lqr_M->intgData);
  rtsiSetSolverName(&heli_p2_lqr_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = heli_p2_lqr_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    heli_p2_lqr_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    heli_p2_lqr_M->Timing.sampleTimes = (&heli_p2_lqr_M->
      Timing.sampleTimesArray[0]);
    heli_p2_lqr_M->Timing.offsetTimes = (&heli_p2_lqr_M->
      Timing.offsetTimesArray[0]);

    /* task periods */
    heli_p2_lqr_M->Timing.sampleTimes[0] = (0.0);
    heli_p2_lqr_M->Timing.sampleTimes[1] = (0.002);
    heli_p2_lqr_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    heli_p2_lqr_M->Timing.offsetTimes[0] = (0.0);
    heli_p2_lqr_M->Timing.offsetTimes[1] = (0.0);
    heli_p2_lqr_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(heli_p2_lqr_M, &heli_p2_lqr_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = heli_p2_lqr_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = heli_p2_lqr_M->Timing.perTaskSampleHitsArray;
    heli_p2_lqr_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    heli_p2_lqr_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(heli_p2_lqr_M, 30.0);
  heli_p2_lqr_M->Timing.stepSize0 = 0.002;
  heli_p2_lqr_M->Timing.stepSize1 = 0.002;
  heli_p2_lqr_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  heli_p2_lqr_M->Sizes.checksums[0] = (865634684U);
  heli_p2_lqr_M->Sizes.checksums[1] = (158174478U);
  heli_p2_lqr_M->Sizes.checksums[2] = (2431088616U);
  heli_p2_lqr_M->Sizes.checksums[3] = (4931258U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    heli_p2_lqr_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(heli_p2_lqr_M->extModeInfo,
      &heli_p2_lqr_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(heli_p2_lqr_M->extModeInfo,
                        heli_p2_lqr_M->Sizes.checksums);
    rteiSetTPtr(heli_p2_lqr_M->extModeInfo, rtmGetTPtr(heli_p2_lqr_M));
  }

  heli_p2_lqr_M->solverInfoPtr = (&heli_p2_lqr_M->solverInfo);
  heli_p2_lqr_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&heli_p2_lqr_M->solverInfo, 0.002);
  rtsiSetSolverMode(&heli_p2_lqr_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  heli_p2_lqr_M->blockIO = ((void *) &heli_p2_lqr_B);

  {
    heli_p2_lqr_B.TravelCounttorad = 0.0;
    heli_p2_lqr_B.TravelTransferFcn = 0.0;
    heli_p2_lqr_B.PitchCounttorad = 0.0;
    heli_p2_lqr_B.PitchTransferFcn = 0.0;
    heli_p2_lqr_B.ElevationCounttorad = 0.0;
    heli_p2_lqr_B.ElevationTransferFcn = 0.0;
    heli_p2_lqr_B.RateTransitionx = 0.0;
    heli_p2_lqr_B.Joystick_gain_x = 0.0;
    heli_p2_lqr_B.ManualSwitch = 0.0;
    heli_p2_lqr_B.RateTransitiony = 0.0;
    heli_p2_lqr_B.Joystick_gain_y = 0.0;
    heli_p2_lqr_B.ManualSwitch1 = 0.0;
    heli_p2_lqr_B.u[0] = 0.0;
    heli_p2_lqr_B.u[1] = 0.0;
    heli_p2_lqr_B.FrontmotorSaturation = 0.0;
    heli_p2_lqr_B.BackmotorSaturation = 0.0;
  }

  /* parameters */
  heli_p2_lqr_M->defaultParam = ((real_T *)&heli_p2_lqr_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &heli_p2_lqr_X;
    heli_p2_lqr_M->contStates = (x);
    (void) memset((void *)&heli_p2_lqr_X, 0,
                  sizeof(X_heli_p2_lqr_T));
  }

  /* states (dwork) */
  heli_p2_lqr_M->dwork = ((void *) &heli_p2_lqr_DW);
  (void) memset((void *)&heli_p2_lqr_DW, 0,
                sizeof(DW_heli_p2_lqr_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      heli_p2_lqr_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  heli_p2_lqr_DW.RateTransitionx_Buffer0 = 0.0;
  heli_p2_lqr_DW.RateTransitiony_Buffer0 = 0.0;
  heli_p2_lqr_DW.HILWriteAnalog_Buffer[0] = 0.0;
  heli_p2_lqr_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    heli_p2_lqr_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  heli_p2_lqr_M->Sizes.numContStates = (3);/* Number of continuous states */
  heli_p2_lqr_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  heli_p2_lqr_M->Sizes.numY = (0);     /* Number of model outputs */
  heli_p2_lqr_M->Sizes.numU = (0);     /* Number of model inputs */
  heli_p2_lqr_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  heli_p2_lqr_M->Sizes.numSampTimes = (3);/* Number of sample times */
  heli_p2_lqr_M->Sizes.numBlocks = (54);/* Number of blocks */
  heli_p2_lqr_M->Sizes.numBlockIO = (15);/* Number of block outputs */
  heli_p2_lqr_M->Sizes.numBlockPrms = (157);/* Sum of parameter "widths" */
  return heli_p2_lqr_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
