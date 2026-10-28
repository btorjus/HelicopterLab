/*
 * Lab1_OD_Step04.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab1_OD_Step04".
 *
 * Model version              : 11.11
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Sep  2 18:50:28 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab1_OD_Step04.h"
#include "Lab1_OD_Step04_private.h"
#include "Lab1_OD_Step04_dt.h"

/* Block signals (default storage) */
B_Lab1_OD_Step04_T Lab1_OD_Step04_B;

/* Continuous states */
X_Lab1_OD_Step04_T Lab1_OD_Step04_X;

/* Block states (default storage) */
DW_Lab1_OD_Step04_T Lab1_OD_Step04_DW;

/* Real-time model */
static RT_MODEL_Lab1_OD_Step04_T Lab1_OD_Step04_M_;
RT_MODEL_Lab1_OD_Step04_T *const Lab1_OD_Step04_M = &Lab1_OD_Step04_M_;
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
  rtmSampleHitPtr[1] = rtmStepTask(Lab1_OD_Step04_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(Lab1_OD_Step04_M, 2);
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
  if (Lab1_OD_Step04_M->Timing.TaskCounters.TID[1] == 0) {
    Lab1_OD_Step04_M->Timing.RateInteraction.TID1_2 =
      (Lab1_OD_Step04_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    Lab1_OD_Step04_M->Timing.perTaskSampleHits[5] =
      Lab1_OD_Step04_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Lab1_OD_Step04_M->Timing.TaskCounters.TID[2])++;
  if ((Lab1_OD_Step04_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    Lab1_OD_Step04_M->Timing.TaskCounters.TID[2] = 0;
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
  Lab1_OD_Step04_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void Lab1_OD_Step04_output0(void)      /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtHeli3D[6];
  real_T rtb_TmpSignalConversionAtToFile[5];
  real_T rtb_DeadZoney;
  real_T u0;
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* set solver stop time */
    if (!(Lab1_OD_Step04_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Lab1_OD_Step04_M->solverInfo,
                            ((Lab1_OD_Step04_M->Timing.clockTickH0 + 1) *
        Lab1_OD_Step04_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Lab1_OD_Step04_M->solverInfo,
                            ((Lab1_OD_Step04_M->Timing.clockTick0 + 1) *
        Lab1_OD_Step04_M->Timing.stepSize0 +
        Lab1_OD_Step04_M->Timing.clockTickH0 *
        Lab1_OD_Step04_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Lab1_OD_Step04_M)) {
    Lab1_OD_Step04_M->Timing.t[0] = rtsiGetT(&Lab1_OD_Step04_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: Lab1_OD_Step04/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (Lab1_OD_Step04_DW.HILReadEncoderTimebase_Task, 1,
         &Lab1_OD_Step04_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          Lab1_OD_Step04_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          Lab1_OD_Step04_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZoney = Lab1_OD_Step04_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S3>/Travel: Count to rad' */
    Lab1_OD_Step04_B.TravelCounttorad = Lab1_OD_Step04_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S3>/Pitch: Count to rad' */
    Lab1_OD_Step04_B.PitchCounttorad = Lab1_OD_Step04_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;
  }

  /* TransferFcn: '<S3>/Travel: Transfer Fcn' */
  Lab1_OD_Step04_B.TravelTransferFcn = 0.0;
  Lab1_OD_Step04_B.TravelTransferFcn += Lab1_OD_Step04_P.TravelTransferFcn_C *
    Lab1_OD_Step04_X.TravelTransferFcn_CSTATE;
  Lab1_OD_Step04_B.TravelTransferFcn += Lab1_OD_Step04_P.TravelTransferFcn_D *
    Lab1_OD_Step04_B.TravelCounttorad;

  /* TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  Lab1_OD_Step04_B.PitchTransferFcn = 0.0;
  Lab1_OD_Step04_B.PitchTransferFcn += Lab1_OD_Step04_P.PitchTransferFcn_C *
    Lab1_OD_Step04_X.PitchTransferFcn_CSTATE;
  Lab1_OD_Step04_B.PitchTransferFcn += Lab1_OD_Step04_P.PitchTransferFcn_D *
    Lab1_OD_Step04_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* Gain: '<S3>/Elevation: Count to rad' */
    Lab1_OD_Step04_B.ElevationCounttorad =
      Lab1_OD_Step04_P.ElevationCounttorad_Gain * rtb_DeadZoney;
  }

  /* TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  Lab1_OD_Step04_B.ElevationTransferFcn = 0.0;
  Lab1_OD_Step04_B.ElevationTransferFcn +=
    Lab1_OD_Step04_P.ElevationTransferFcn_C *
    Lab1_OD_Step04_X.ElevationTransferFcn_CSTATE;
  Lab1_OD_Step04_B.ElevationTransferFcn +=
    Lab1_OD_Step04_P.ElevationTransferFcn_D *
    Lab1_OD_Step04_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* SignalConversion generated from: '<Root>/Heli3DLog' */
    rtb_TmpSignalConversionAtHeli3D[0] = Lab1_OD_Step04_B.TravelCounttorad;
    rtb_TmpSignalConversionAtHeli3D[1] = Lab1_OD_Step04_B.TravelTransferFcn;
    rtb_TmpSignalConversionAtHeli3D[2] = Lab1_OD_Step04_B.PitchCounttorad;
    rtb_TmpSignalConversionAtHeli3D[3] = Lab1_OD_Step04_B.PitchTransferFcn;
    rtb_TmpSignalConversionAtHeli3D[4] = Lab1_OD_Step04_B.ElevationCounttorad;
    rtb_TmpSignalConversionAtHeli3D[5] = Lab1_OD_Step04_B.ElevationTransferFcn;

    /* ToFile: '<Root>/Heli3DLog' */
    if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
      if (rtmIsMajorTimeStep(Lab1_OD_Step04_M) ) {
        {
          if (!(++Lab1_OD_Step04_DW.Heli3DLog_IWORK.Decimation % 1) &&
              (Lab1_OD_Step04_DW.Heli3DLog_IWORK.Count * (6 + 1)) + 1 <
              100000000 ) {
            FILE *fp = (FILE *) Lab1_OD_Step04_DW.Heli3DLog_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[6 + 1];
              Lab1_OD_Step04_DW.Heli3DLog_IWORK.Decimation = 0;
              u[0] = Lab1_OD_Step04_M->Timing.t[1];
              u[1] = rtb_TmpSignalConversionAtHeli3D[0];
              u[2] = rtb_TmpSignalConversionAtHeli3D[1];
              u[3] = rtb_TmpSignalConversionAtHeli3D[2];
              u[4] = rtb_TmpSignalConversionAtHeli3D[3];
              u[5] = rtb_TmpSignalConversionAtHeli3D[4];
              u[6] = rtb_TmpSignalConversionAtHeli3D[5];
              if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
                rtmSetErrorStatus(Lab1_OD_Step04_M,
                                  "Error writing to MAT-file Heli3D.mat");
                return;
              }

              if (((++Lab1_OD_Step04_DW.Heli3DLog_IWORK.Count) * (6 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file Heli3D.mat.\n");
              }
            }
          }
        }
      }
    }
  }

  /* Integrator: '<S6>/Integrator' */
  /* Limited  Integrator  */
  if (Lab1_OD_Step04_X.Integrator_CSTATE >= Lab1_OD_Step04_P.Integrator_UpperSat)
  {
    Lab1_OD_Step04_X.Integrator_CSTATE = Lab1_OD_Step04_P.Integrator_UpperSat;
  } else {
    if (Lab1_OD_Step04_X.Integrator_CSTATE <=
        Lab1_OD_Step04_P.Integrator_LowerSat) {
      Lab1_OD_Step04_X.Integrator_CSTATE = Lab1_OD_Step04_P.Integrator_LowerSat;
    }
  }

  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* DeadZone: '<S4>/Dead Zone: y' incorporates:
     *  Sum: '<S2>/Sum'
     */
    rtb_DeadZoney = 0.0;

    /* Gain: '<S6>/K_ep' */
    Lab1_OD_Step04_B.K_ep = Lab1_OD_Step04_P.K_ep_Gain * rtb_DeadZoney;

    /* Gain: '<S6>/K_ed' */
    Lab1_OD_Step04_B.K_ed = Lab1_OD_Step04_P.K_ed_Gain * 0.0;
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Vs0'
   *  Integrator: '<S6>/Integrator'
   *  Sum: '<S6>/Sum'
   */
  Lab1_OD_Step04_B.Sum = ((Lab1_OD_Step04_X.Integrator_CSTATE +
    Lab1_OD_Step04_B.K_ep) - Lab1_OD_Step04_B.K_ed) + Lab1_OD_Step04_P.Vs0_Value;
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* ToFile: '<Root>/To File1' */
    if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
      if (rtmIsMajorTimeStep(Lab1_OD_Step04_M) ) {
        {
          if (!(++Lab1_OD_Step04_DW.ToFile1_IWORK.Decimation % 1) &&
              (Lab1_OD_Step04_DW.ToFile1_IWORK.Count * (1 + 1)) + 1 < 100000000 )
          {
            FILE *fp = (FILE *) Lab1_OD_Step04_DW.ToFile1_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[1 + 1];
              Lab1_OD_Step04_DW.ToFile1_IWORK.Decimation = 0;
              u[0] = Lab1_OD_Step04_M->Timing.t[1];
              u[1] = Lab1_OD_Step04_B.Sum;
              if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
                rtmSetErrorStatus(Lab1_OD_Step04_M,
                                  "Error writing to MAT-file Vs.mat");
                return;
              }

              if (((++Lab1_OD_Step04_DW.ToFile1_IWORK.Count) * (1 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file Vs.mat.\n");
              }
            }
          }
        }
      }
    }
  }

  /* Step: '<Root>/Step' */
  if (Lab1_OD_Step04_M->Timing.t[0] < Lab1_OD_Step04_P.Step_Time) {
    /* Step: '<Root>/Step' */
    Lab1_OD_Step04_B.Step = Lab1_OD_Step04_P.Step_Y0;
  } else {
    /* Step: '<Root>/Step' */
    Lab1_OD_Step04_B.Step = Lab1_OD_Step04_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
  }

  /* Sum: '<S5>/Sum' */
  Lab1_OD_Step04_B.e = Lab1_OD_Step04_B.Step - Lab1_OD_Step04_B.PitchCounttorad;

  /* Gain: '<S5>/Kpp' */
  Lab1_OD_Step04_B.Kpp = Lab1_OD_Step04_P.Kpp_Gain * Lab1_OD_Step04_B.e;

  /* Gain: '<S5>/Kpd' */
  Lab1_OD_Step04_B.Kpd = Lab1_OD_Step04_P.Kpd_Gain *
    Lab1_OD_Step04_B.PitchTransferFcn;

  /* Sum: '<S5>/Sum1' */
  Lab1_OD_Step04_B.Vd = Lab1_OD_Step04_B.Kpp - Lab1_OD_Step04_B.Kpd;
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* Gain: '<S6>/K_ei' */
    Lab1_OD_Step04_B.K_ei = Lab1_OD_Step04_P.K_ei_Gain * rtb_DeadZoney;
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  u0 = (Lab1_OD_Step04_B.Sum - Lab1_OD_Step04_B.Vd) *
    Lab1_OD_Step04_P.Frontgain_Gain;

  /* Saturate: '<S3>/Front motor: Saturation' */
  if (u0 > Lab1_OD_Step04_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S3>/Front motor: Saturation' */
    Lab1_OD_Step04_B.FrontmotorSaturation =
      Lab1_OD_Step04_P.FrontmotorSaturation_UpperSat;
  } else if (u0 < Lab1_OD_Step04_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S3>/Front motor: Saturation' */
    Lab1_OD_Step04_B.FrontmotorSaturation =
      Lab1_OD_Step04_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S3>/Front motor: Saturation' */
    Lab1_OD_Step04_B.FrontmotorSaturation = u0;
  }

  /* End of Saturate: '<S3>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  u0 = (Lab1_OD_Step04_B.Sum + Lab1_OD_Step04_B.Vd) *
    Lab1_OD_Step04_P.Backgain_Gain;

  /* Saturate: '<S3>/Back motor: Saturation' */
  if (u0 > Lab1_OD_Step04_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S3>/Back motor: Saturation' */
    Lab1_OD_Step04_B.BackmotorSaturation =
      Lab1_OD_Step04_P.BackmotorSaturation_UpperSat;
  } else if (u0 < Lab1_OD_Step04_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S3>/Back motor: Saturation' */
    Lab1_OD_Step04_B.BackmotorSaturation =
      Lab1_OD_Step04_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S3>/Back motor: Saturation' */
    Lab1_OD_Step04_B.BackmotorSaturation = u0;
  }

  /* End of Saturate: '<S3>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: Lab1_OD_Step04/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      Lab1_OD_Step04_DW.HILWriteAnalog_Buffer[0] =
        Lab1_OD_Step04_B.FrontmotorSaturation;
      Lab1_OD_Step04_DW.HILWriteAnalog_Buffer[1] =
        Lab1_OD_Step04_B.BackmotorSaturation;
      result = hil_write_analog(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILWriteAnalog_channels, 2,
        &Lab1_OD_Step04_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
      }
    }

    /* SignalConversion generated from: '<S5>/To File' */
    rtb_TmpSignalConversionAtToFile[0] = Lab1_OD_Step04_B.Step;
    rtb_TmpSignalConversionAtToFile[1] = Lab1_OD_Step04_B.e;
    rtb_TmpSignalConversionAtToFile[2] = Lab1_OD_Step04_B.Kpp;
    rtb_TmpSignalConversionAtToFile[3] = Lab1_OD_Step04_B.Kpd;
    rtb_TmpSignalConversionAtToFile[4] = Lab1_OD_Step04_B.Vd;

    /* ToFile: '<S5>/To File' */
    if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
      if (rtmIsMajorTimeStep(Lab1_OD_Step04_M) ) {
        {
          if (!(++Lab1_OD_Step04_DW.ToFile_IWORK.Decimation % 1) &&
              (Lab1_OD_Step04_DW.ToFile_IWORK.Count * (5 + 1)) + 1 < 100000000 )
          {
            FILE *fp = (FILE *) Lab1_OD_Step04_DW.ToFile_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[5 + 1];
              Lab1_OD_Step04_DW.ToFile_IWORK.Decimation = 0;
              u[0] = Lab1_OD_Step04_M->Timing.t[1];
              u[1] = rtb_TmpSignalConversionAtToFile[0];
              u[2] = rtb_TmpSignalConversionAtToFile[1];
              u[3] = rtb_TmpSignalConversionAtToFile[2];
              u[4] = rtb_TmpSignalConversionAtToFile[3];
              u[5] = rtb_TmpSignalConversionAtToFile[4];
              if (fwrite(u, sizeof(real_T), 5 + 1, fp) != 5 + 1) {
                rtmSetErrorStatus(Lab1_OD_Step04_M,
                                  "Error writing to MAT-file pitchdata.mat");
                return;
              }

              if (((++Lab1_OD_Step04_DW.ToFile_IWORK.Count) * (5 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file pitchdata.mat.\n");
              }
            }
          }
        }
      }
    }

    /* RateTransition: '<S4>/Rate Transition: x' */
    if (Lab1_OD_Step04_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S4>/Rate Transition: x' */
      Lab1_OD_Step04_B.RateTransitionx =
        Lab1_OD_Step04_DW.RateTransitionx_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: x' */

    /* DeadZone: '<S4>/Dead Zone: x' */
    if (Lab1_OD_Step04_B.RateTransitionx > Lab1_OD_Step04_P.DeadZonex_End) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab1_OD_Step04_B.RateTransitionx -
        Lab1_OD_Step04_P.DeadZonex_End;
    } else if (Lab1_OD_Step04_B.RateTransitionx >=
               Lab1_OD_Step04_P.DeadZonex_Start) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = 0.0;
    } else {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab1_OD_Step04_B.RateTransitionx -
        Lab1_OD_Step04_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: x' */

    /* Gain: '<S4>/Joystick_gain_x' incorporates:
     *  Gain: '<S4>/Gain: x'
     */
    Lab1_OD_Step04_B.Joystick_gain_x = Lab1_OD_Step04_P.Gainx_Gain *
      rtb_DeadZoney * Lab1_OD_Step04_P.Joystick_gain_x;

    /* RateTransition: '<S4>/Rate Transition: y' */
    if (Lab1_OD_Step04_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S4>/Rate Transition: y' */
      Lab1_OD_Step04_B.RateTransitiony =
        Lab1_OD_Step04_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: y' */

    /* DeadZone: '<S4>/Dead Zone: y' */
    if (Lab1_OD_Step04_B.RateTransitiony > Lab1_OD_Step04_P.DeadZoney_End) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab1_OD_Step04_B.RateTransitiony -
        Lab1_OD_Step04_P.DeadZoney_End;
    } else if (Lab1_OD_Step04_B.RateTransitiony >=
               Lab1_OD_Step04_P.DeadZoney_Start) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = 0.0;
    } else {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab1_OD_Step04_B.RateTransitiony -
        Lab1_OD_Step04_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: y' */

    /* Gain: '<S4>/Joystick_gain_y' incorporates:
     *  Gain: '<S4>/Gain: y'
     */
    Lab1_OD_Step04_B.Joystick_gain_y = Lab1_OD_Step04_P.Gainy_Gain *
      rtb_DeadZoney * Lab1_OD_Step04_P.Joystick_gain_y;
  }
}

/* Model update function for TID0 */
void Lab1_OD_Step04_update0(void)      /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(Lab1_OD_Step04_M)) {
    rt_ertODEUpdateContinuousStates(&Lab1_OD_Step04_M->solverInfo);
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
  if (!(++Lab1_OD_Step04_M->Timing.clockTick0)) {
    ++Lab1_OD_Step04_M->Timing.clockTickH0;
  }

  Lab1_OD_Step04_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Lab1_OD_Step04_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab1_OD_Step04_M->Timing.clockTick1)) {
    ++Lab1_OD_Step04_M->Timing.clockTickH1;
  }

  Lab1_OD_Step04_M->Timing.t[1] = Lab1_OD_Step04_M->Timing.clockTick1 *
    Lab1_OD_Step04_M->Timing.stepSize1 + Lab1_OD_Step04_M->Timing.clockTickH1 *
    Lab1_OD_Step04_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void Lab1_OD_Step04_derivatives(void)
{
  XDot_Lab1_OD_Step04_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_Lab1_OD_Step04_T *) Lab1_OD_Step04_M->derivs);

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += Lab1_OD_Step04_P.TravelTransferFcn_A *
    Lab1_OD_Step04_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += Lab1_OD_Step04_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += Lab1_OD_Step04_P.PitchTransferFcn_A *
    Lab1_OD_Step04_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += Lab1_OD_Step04_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    Lab1_OD_Step04_P.ElevationTransferFcn_A *
    Lab1_OD_Step04_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += Lab1_OD_Step04_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  lsat = (Lab1_OD_Step04_X.Integrator_CSTATE <=
          Lab1_OD_Step04_P.Integrator_LowerSat);
  usat = (Lab1_OD_Step04_X.Integrator_CSTATE >=
          Lab1_OD_Step04_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (Lab1_OD_Step04_B.K_ei > 0.0)) || (usat &&
       (Lab1_OD_Step04_B.K_ei < 0.0))) {
    _rtXdot->Integrator_CSTATE = Lab1_OD_Step04_B.K_ei;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S6>/Integrator' */
}

/* Model output function for TID2 */
void Lab1_OD_Step04_output2(void)      /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_GameController_o4;
  real_T rtb_GameController_o5;

  /* S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab1_OD_Step04/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab1_OD_Step04_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(Lab1_OD_Step04_DW.GameController_Controller,
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

  /* RateTransition: '<S4>/Rate Transition: x' */
  Lab1_OD_Step04_DW.RateTransitionx_Buffer0 = rtb_GameController_o4;

  /* RateTransition: '<S4>/Rate Transition: y' */
  Lab1_OD_Step04_DW.RateTransitiony_Buffer0 = rtb_GameController_o5;
}

/* Model update function for TID2 */
void Lab1_OD_Step04_update2(void)      /* Sample time: [0.01s, 0.0s] */
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
  if (!(++Lab1_OD_Step04_M->Timing.clockTick2)) {
    ++Lab1_OD_Step04_M->Timing.clockTickH2;
  }

  Lab1_OD_Step04_M->Timing.t[2] = Lab1_OD_Step04_M->Timing.clockTick2 *
    Lab1_OD_Step04_M->Timing.stepSize2 + Lab1_OD_Step04_M->Timing.clockTickH2 *
    Lab1_OD_Step04_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void Lab1_OD_Step04_output(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab1_OD_Step04_output0();
    break;

   case 2 :
    Lab1_OD_Step04_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void Lab1_OD_Step04_update(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab1_OD_Step04_update0();
    break;

   case 2 :
    Lab1_OD_Step04_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void Lab1_OD_Step04_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab1_OD_Step04/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab1_OD_Step04_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Lab1_OD_Step04_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab1_OD_Step04_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
      return;
    }

    if ((Lab1_OD_Step04_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab1_OD_Step04_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab1_OD_Step04_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab1_OD_Step04_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab1_OD_Step04_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_AIChannels, 8U,
        &Lab1_OD_Step04_DW.HILInitialize_AIMinimums[0],
        &Lab1_OD_Step04_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_OD_Step04_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab1_OD_Step04_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab1_OD_Step04_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab1_OD_Step04_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab1_OD_Step04_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_AOChannels, 8U,
        &Lab1_OD_Step04_DW.HILInitialize_AOMinimums[0],
        &Lab1_OD_Step04_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_OD_Step04_P.HILInitialize_AOStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab1_OD_Step04_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_AOChannels, 8U,
        &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if (Lab1_OD_Step04_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab1_OD_Step04_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab1_OD_Step04_DW.HILInitialize_Card,
         Lab1_OD_Step04_P.HILInitialize_AOChannels, 8U,
         &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_OD_Step04_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab1_OD_Step04_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab1_OD_Step04_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Lab1_OD_Step04_DW.HILInitialize_Card,
         Lab1_OD_Step04_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Lab1_OD_Step04_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_OD_Step04_P.HILInitialize_EIStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab1_OD_Step04_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab1_OD_Step04_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_EIChannels, 8U,
        &Lab1_OD_Step04_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_OD_Step04_P.HILInitialize_POPStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab1_OD_Step04_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab1_OD_Step04_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab1_OD_Step04_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab1_OD_Step04_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &Lab1_OD_Step04_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab1_OD_Step04_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Lab1_OD_Step04_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab1_OD_Step04_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = Lab1_OD_Step04_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab1_OD_Step04_DW.HILInitialize_Card,
          &Lab1_OD_Step04_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes, &Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab1_OD_Step04_DW.HILInitialize_Card,
          &Lab1_OD_Step04_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab1_OD_Step04_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab1_OD_Step04_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Lab1_OD_Step04_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab1_OD_Step04_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab1_OD_Step04_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab1_OD_Step04_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab1_OD_Step04_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Lab1_OD_Step04_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab1_OD_Step04_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab1_OD_Step04_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab1_OD_Step04_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_OD_Step04_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_POChannels, 8U,
        &Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[0],
        &Lab1_OD_Step04_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if ((Lab1_OD_Step04_P.HILInitialize_POStart && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab1_OD_Step04_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_OD_Step04_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab1_OD_Step04_DW.HILInitialize_Card,
        Lab1_OD_Step04_P.HILInitialize_POChannels, 8U,
        &Lab1_OD_Step04_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }

    if (Lab1_OD_Step04_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab1_OD_Step04_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_OD_Step04_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab1_OD_Step04_DW.HILInitialize_Card,
         Lab1_OD_Step04_P.HILInitialize_POChannels, 8U,
         &Lab1_OD_Step04_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: Lab1_OD_Step04/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(Lab1_OD_Step04_DW.HILInitialize_Card,
      Lab1_OD_Step04_P.HILReadEncoderTimebase_SamplesI,
      Lab1_OD_Step04_P.HILReadEncoderTimebase_Channels, 3,
      &Lab1_OD_Step04_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Lab1_OD_Step04_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (Lab1_OD_Step04_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/Heli3DLog' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Heli3D.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab1_OD_Step04_M, "Error creating .mat file Heli3D.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab1_OD_Step04_M,
                        "Error writing mat file header to file Heli3D.mat");
      return;
    }

    Lab1_OD_Step04_DW.Heli3DLog_IWORK.Count = 0;
    Lab1_OD_Step04_DW.Heli3DLog_IWORK.Decimation = -1;
    Lab1_OD_Step04_DW.Heli3DLog_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Vs.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab1_OD_Step04_M, "Error creating .mat file Vs.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab1_OD_Step04_M,
                        "Error writing mat file header to file Vs.mat");
      return;
    }

    Lab1_OD_Step04_DW.ToFile1_IWORK.Count = 0;
    Lab1_OD_Step04_DW.ToFile1_IWORK.Decimation = -1;
    Lab1_OD_Step04_DW.ToFile1_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S5>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "pitchdata.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab1_OD_Step04_M,
                        "Error creating .mat file pitchdata.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 5 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab1_OD_Step04_M,
                        "Error writing mat file header to file pitchdata.mat");
      return;
    }

    Lab1_OD_Step04_DW.ToFile_IWORK.Count = 0;
    Lab1_OD_Step04_DW.ToFile_IWORK.Decimation = -1;
    Lab1_OD_Step04_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S4>/Rate Transition: x' */
  Lab1_OD_Step04_B.RateTransitionx =
    Lab1_OD_Step04_P.RateTransitionx_InitialConditio;

  /* Start for RateTransition: '<S4>/Rate Transition: y' */
  Lab1_OD_Step04_B.RateTransitiony =
    Lab1_OD_Step04_P.RateTransitiony_InitialConditio;

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab1_OD_Step04/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab1_OD_Step04_P.GameController_Enabled) {
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
        (Lab1_OD_Step04_P.GameController_ControllerNumber,
         Lab1_OD_Step04_P.GameController_BufferSize, deadzone, saturation,
         Lab1_OD_Step04_P.GameController_AutoCenter, 0, 1.0,
         &Lab1_OD_Step04_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  Lab1_OD_Step04_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  Lab1_OD_Step04_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  Lab1_OD_Step04_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S6>/Integrator' */
  Lab1_OD_Step04_X.Integrator_CSTATE = Lab1_OD_Step04_P.Integrator_IC;

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: x' */
  Lab1_OD_Step04_DW.RateTransitionx_Buffer0 =
    Lab1_OD_Step04_P.RateTransitionx_InitialConditio;

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: y' */
  Lab1_OD_Step04_DW.RateTransitiony_Buffer0 =
    Lab1_OD_Step04_P.RateTransitiony_InitialConditio;
}

/* Model terminate function */
void Lab1_OD_Step04_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab1_OD_Step04/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab1_OD_Step04_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab1_OD_Step04_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab1_OD_Step04_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab1_OD_Step04_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab1_OD_Step04_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab1_OD_Step04_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab1_OD_Step04_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab1_OD_Step04_P.HILInitialize_POFinal;
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
      result = hil_write(Lab1_OD_Step04_DW.HILInitialize_Card
                         , Lab1_OD_Step04_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab1_OD_Step04_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0]
                         , &Lab1_OD_Step04_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab1_OD_Step04_DW.HILInitialize_Card,
            Lab1_OD_Step04_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Lab1_OD_Step04_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab1_OD_Step04_DW.HILInitialize_Card,
            Lab1_OD_Step04_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab1_OD_Step04_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab1_OD_Step04_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab1_OD_Step04_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab1_OD_Step04_DW.HILInitialize_Card);
    hil_close(Lab1_OD_Step04_DW.HILInitialize_Card);
    Lab1_OD_Step04_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/Heli3DLog' */
  {
    FILE *fp = (FILE *) Lab1_OD_Step04_DW.Heli3DLog_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Heli3D.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab1_OD_Step04_M, "Error closing MAT-file Heli3D.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error reopening MAT-file Heli3D.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1,
           Lab1_OD_Step04_DW.Heli3DLog_IWORK.Count, "ans")) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error writing header for ans to MAT-file Heli3D.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab1_OD_Step04_M, "Error closing MAT-file Heli3D.mat");
        return;
      }

      Lab1_OD_Step04_DW.Heli3DLog_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/To File1' */
  {
    FILE *fp = (FILE *) Lab1_OD_Step04_DW.ToFile1_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Vs.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab1_OD_Step04_M, "Error closing MAT-file Vs.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab1_OD_Step04_M, "Error reopening MAT-file Vs.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1,
           Lab1_OD_Step04_DW.ToFile1_IWORK.Count, "ans")) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error writing header for ans to MAT-file Vs.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab1_OD_Step04_M, "Error closing MAT-file Vs.mat");
        return;
      }

      Lab1_OD_Step04_DW.ToFile1_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S5>/To File' */
  {
    FILE *fp = (FILE *) Lab1_OD_Step04_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "pitchdata.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error closing MAT-file pitchdata.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error reopening MAT-file pitchdata.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 5 + 1, Lab1_OD_Step04_DW.ToFile_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error writing header for ans to MAT-file pitchdata.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab1_OD_Step04_M,
                          "Error closing MAT-file pitchdata.mat");
        return;
      }

      Lab1_OD_Step04_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab1_OD_Step04/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab1_OD_Step04_P.GameController_Enabled) {
      game_controller_close(Lab1_OD_Step04_DW.GameController_Controller);
      Lab1_OD_Step04_DW.GameController_Controller = NULL;
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
  Lab1_OD_Step04_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  Lab1_OD_Step04_update(tid);
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
  Lab1_OD_Step04_initialize();
}

void MdlTerminate(void)
{
  Lab1_OD_Step04_terminate();
}

/* Registration function */
RT_MODEL_Lab1_OD_Step04_T *Lab1_OD_Step04(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  Lab1_OD_Step04_P.Integrator_UpperSat = rtInf;
  Lab1_OD_Step04_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)Lab1_OD_Step04_M, 0,
                sizeof(RT_MODEL_Lab1_OD_Step04_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Lab1_OD_Step04_M->solverInfo,
                          &Lab1_OD_Step04_M->Timing.simTimeStep);
    rtsiSetTPtr(&Lab1_OD_Step04_M->solverInfo, &rtmGetTPtr(Lab1_OD_Step04_M));
    rtsiSetStepSizePtr(&Lab1_OD_Step04_M->solverInfo,
                       &Lab1_OD_Step04_M->Timing.stepSize0);
    rtsiSetdXPtr(&Lab1_OD_Step04_M->solverInfo, &Lab1_OD_Step04_M->derivs);
    rtsiSetContStatesPtr(&Lab1_OD_Step04_M->solverInfo, (real_T **)
                         &Lab1_OD_Step04_M->contStates);
    rtsiSetNumContStatesPtr(&Lab1_OD_Step04_M->solverInfo,
      &Lab1_OD_Step04_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Lab1_OD_Step04_M->solverInfo,
      &Lab1_OD_Step04_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Lab1_OD_Step04_M->solverInfo,
      &Lab1_OD_Step04_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Lab1_OD_Step04_M->solverInfo,
      &Lab1_OD_Step04_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Lab1_OD_Step04_M->solverInfo, (&rtmGetErrorStatus
      (Lab1_OD_Step04_M)));
    rtsiSetRTModelPtr(&Lab1_OD_Step04_M->solverInfo, Lab1_OD_Step04_M);
  }

  rtsiSetSimTimeStep(&Lab1_OD_Step04_M->solverInfo, MAJOR_TIME_STEP);
  Lab1_OD_Step04_M->intgData.f[0] = Lab1_OD_Step04_M->odeF[0];
  Lab1_OD_Step04_M->contStates = ((real_T *) &Lab1_OD_Step04_X);
  rtsiSetSolverData(&Lab1_OD_Step04_M->solverInfo, (void *)
                    &Lab1_OD_Step04_M->intgData);
  rtsiSetSolverName(&Lab1_OD_Step04_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab1_OD_Step04_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    Lab1_OD_Step04_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab1_OD_Step04_M->Timing.sampleTimes =
      (&Lab1_OD_Step04_M->Timing.sampleTimesArray[0]);
    Lab1_OD_Step04_M->Timing.offsetTimes =
      (&Lab1_OD_Step04_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab1_OD_Step04_M->Timing.sampleTimes[0] = (0.0);
    Lab1_OD_Step04_M->Timing.sampleTimes[1] = (0.002);
    Lab1_OD_Step04_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    Lab1_OD_Step04_M->Timing.offsetTimes[0] = (0.0);
    Lab1_OD_Step04_M->Timing.offsetTimes[1] = (0.0);
    Lab1_OD_Step04_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(Lab1_OD_Step04_M, &Lab1_OD_Step04_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab1_OD_Step04_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      Lab1_OD_Step04_M->Timing.perTaskSampleHitsArray;
    Lab1_OD_Step04_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    Lab1_OD_Step04_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab1_OD_Step04_M, -1);
  Lab1_OD_Step04_M->Timing.stepSize0 = 0.002;
  Lab1_OD_Step04_M->Timing.stepSize1 = 0.002;
  Lab1_OD_Step04_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  Lab1_OD_Step04_M->Sizes.checksums[0] = (3067661798U);
  Lab1_OD_Step04_M->Sizes.checksums[1] = (1261412650U);
  Lab1_OD_Step04_M->Sizes.checksums[2] = (2419187328U);
  Lab1_OD_Step04_M->Sizes.checksums[3] = (1668815004U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Lab1_OD_Step04_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab1_OD_Step04_M->extModeInfo,
      &Lab1_OD_Step04_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab1_OD_Step04_M->extModeInfo,
                        Lab1_OD_Step04_M->Sizes.checksums);
    rteiSetTPtr(Lab1_OD_Step04_M->extModeInfo, rtmGetTPtr(Lab1_OD_Step04_M));
  }

  Lab1_OD_Step04_M->solverInfoPtr = (&Lab1_OD_Step04_M->solverInfo);
  Lab1_OD_Step04_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Lab1_OD_Step04_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Lab1_OD_Step04_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  Lab1_OD_Step04_M->blockIO = ((void *) &Lab1_OD_Step04_B);

  {
    Lab1_OD_Step04_B.TravelCounttorad = 0.0;
    Lab1_OD_Step04_B.TravelTransferFcn = 0.0;
    Lab1_OD_Step04_B.PitchCounttorad = 0.0;
    Lab1_OD_Step04_B.PitchTransferFcn = 0.0;
    Lab1_OD_Step04_B.ElevationCounttorad = 0.0;
    Lab1_OD_Step04_B.ElevationTransferFcn = 0.0;
    Lab1_OD_Step04_B.K_ep = 0.0;
    Lab1_OD_Step04_B.K_ed = 0.0;
    Lab1_OD_Step04_B.Sum = 0.0;
    Lab1_OD_Step04_B.Step = 0.0;
    Lab1_OD_Step04_B.e = 0.0;
    Lab1_OD_Step04_B.Kpp = 0.0;
    Lab1_OD_Step04_B.Kpd = 0.0;
    Lab1_OD_Step04_B.Vd = 0.0;
    Lab1_OD_Step04_B.K_ei = 0.0;
    Lab1_OD_Step04_B.FrontmotorSaturation = 0.0;
    Lab1_OD_Step04_B.BackmotorSaturation = 0.0;
    Lab1_OD_Step04_B.RateTransitionx = 0.0;
    Lab1_OD_Step04_B.Joystick_gain_x = 0.0;
    Lab1_OD_Step04_B.RateTransitiony = 0.0;
    Lab1_OD_Step04_B.Joystick_gain_y = 0.0;
  }

  /* parameters */
  Lab1_OD_Step04_M->defaultParam = ((real_T *)&Lab1_OD_Step04_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Lab1_OD_Step04_X;
    Lab1_OD_Step04_M->contStates = (x);
    (void) memset((void *)&Lab1_OD_Step04_X, 0,
                  sizeof(X_Lab1_OD_Step04_T));
  }

  /* states (dwork) */
  Lab1_OD_Step04_M->dwork = ((void *) &Lab1_OD_Step04_DW);
  (void) memset((void *)&Lab1_OD_Step04_DW, 0,
                sizeof(DW_Lab1_OD_Step04_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab1_OD_Step04_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  Lab1_OD_Step04_DW.HILWriteAnalog_Buffer[0] = 0.0;
  Lab1_OD_Step04_DW.HILWriteAnalog_Buffer[1] = 0.0;
  Lab1_OD_Step04_DW.RateTransitionx_Buffer0 = 0.0;
  Lab1_OD_Step04_DW.RateTransitiony_Buffer0 = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab1_OD_Step04_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 17;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab1_OD_Step04_M->Sizes.numContStates = (4);/* Number of continuous states */
  Lab1_OD_Step04_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Lab1_OD_Step04_M->Sizes.numY = (0);  /* Number of model outputs */
  Lab1_OD_Step04_M->Sizes.numU = (0);  /* Number of model inputs */
  Lab1_OD_Step04_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab1_OD_Step04_M->Sizes.numSampTimes = (3);/* Number of sample times */
  Lab1_OD_Step04_M->Sizes.numBlocks = (55);/* Number of blocks */
  Lab1_OD_Step04_M->Sizes.numBlockIO = (21);/* Number of block outputs */
  Lab1_OD_Step04_M->Sizes.numBlockPrms = (148);/* Sum of parameter "widths" */
  return Lab1_OD_Step04_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
