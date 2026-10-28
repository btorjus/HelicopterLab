/*
 * Lab3_IMU_LQRI.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab3_IMU_LQRI".
 *
 * Model version              : 11.23
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Oct 14 20:36:51 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab3_IMU_LQRI.h"
#include "Lab3_IMU_LQRI_private.h"
#include "Lab3_IMU_LQRI_dt.h"

t_stream Lab3_IMU_LQRI_rtZt_stream = NULL;

/* Block signals (default storage) */
B_Lab3_IMU_LQRI_T Lab3_IMU_LQRI_B;

/* Continuous states */
X_Lab3_IMU_LQRI_T Lab3_IMU_LQRI_X;

/* Block states (default storage) */
DW_Lab3_IMU_LQRI_T Lab3_IMU_LQRI_DW;

/* Previous zero-crossings (trigger) states */
PrevZCX_Lab3_IMU_LQRI_T Lab3_IMU_LQRI_PrevZCX;

/* Real-time model */
static RT_MODEL_Lab3_IMU_LQRI_T Lab3_IMU_LQRI_M_;
RT_MODEL_Lab3_IMU_LQRI_T *const Lab3_IMU_LQRI_M = &Lab3_IMU_LQRI_M_;
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
  rtmSampleHitPtr[1] = rtmStepTask(Lab3_IMU_LQRI_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(Lab3_IMU_LQRI_M, 2);
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
  if (Lab3_IMU_LQRI_M->Timing.TaskCounters.TID[1] == 0) {
    Lab3_IMU_LQRI_M->Timing.RateInteraction.TID1_2 =
      (Lab3_IMU_LQRI_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    Lab3_IMU_LQRI_M->Timing.perTaskSampleHits[5] =
      Lab3_IMU_LQRI_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Lab3_IMU_LQRI_M->Timing.TaskCounters.TID[2])++;
  if ((Lab3_IMU_LQRI_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    Lab3_IMU_LQRI_M->Timing.TaskCounters.TID[2] = 0;
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
  int_T nXc = 10;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  Lab3_IMU_LQRI_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = atan2(u0_0, u1_0);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/* Model output function for TID0 */
void Lab3_IMU_LQRI_output0(void)       /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  t_stream_ptr rtb_StreamCall1_o1;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_TmpSignalConversionAtp2RunI[6];
  real_T rtb_DeadZoney;
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  boolean_T rtb_StreamRead1_o3;
  real_T tmp_1[9];
  real_T rtb_Sum[5];
  real_T tmp[5];
  real_T tmp_0[5];
  real_T euler_rates_tmp;
  real_T euler_rates_tmp_0;
  real_T euler_rates_tmp_1;
  real_T euler_rates_tmp_2;
  int32_T i;
  int32_T i_0;
  int32_T tmp_2;
  ZCEventType zcEvent;
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* set solver stop time */
    if (!(Lab3_IMU_LQRI_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Lab3_IMU_LQRI_M->solverInfo,
                            ((Lab3_IMU_LQRI_M->Timing.clockTickH0 + 1) *
        Lab3_IMU_LQRI_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Lab3_IMU_LQRI_M->solverInfo,
                            ((Lab3_IMU_LQRI_M->Timing.clockTick0 + 1) *
        Lab3_IMU_LQRI_M->Timing.stepSize0 + Lab3_IMU_LQRI_M->Timing.clockTickH0 *
        Lab3_IMU_LQRI_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Lab3_IMU_LQRI_M)) {
    Lab3_IMU_LQRI_M->Timing.t[0] = rtsiGetT(&Lab3_IMU_LQRI_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: Lab3_IMU_LQRI/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Task, 1,
         &Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZoney = Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S2>/Travel: Count to rad' */
    Lab3_IMU_LQRI_B.TravelCounttorad = Lab3_IMU_LQRI_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S2>/Pitch: Count to rad' */
    Lab3_IMU_LQRI_B.PitchCounttorad = Lab3_IMU_LQRI_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;
  }

  /* TransferFcn: '<S2>/Travel: Transfer Fcn' */
  Lab3_IMU_LQRI_B.TravelTransferFcn = 0.0;
  Lab3_IMU_LQRI_B.TravelTransferFcn += Lab3_IMU_LQRI_P.TravelTransferFcn_C *
    Lab3_IMU_LQRI_X.TravelTransferFcn_CSTATE;
  Lab3_IMU_LQRI_B.TravelTransferFcn += Lab3_IMU_LQRI_P.TravelTransferFcn_D *
    Lab3_IMU_LQRI_B.TravelCounttorad;

  /* TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  Lab3_IMU_LQRI_B.PitchTransferFcn = 0.0;
  Lab3_IMU_LQRI_B.PitchTransferFcn += Lab3_IMU_LQRI_P.PitchTransferFcn_C *
    Lab3_IMU_LQRI_X.PitchTransferFcn_CSTATE;
  Lab3_IMU_LQRI_B.PitchTransferFcn += Lab3_IMU_LQRI_P.PitchTransferFcn_D *
    Lab3_IMU_LQRI_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* Gain: '<S2>/Elevation: Count to rad' */
    Lab3_IMU_LQRI_B.ElevationCounttorad =
      Lab3_IMU_LQRI_P.ElevationCounttorad_Gain * rtb_DeadZoney;
  }

  /* TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  Lab3_IMU_LQRI_B.ElevationTransferFcn = 0.0;
  Lab3_IMU_LQRI_B.ElevationTransferFcn += Lab3_IMU_LQRI_P.ElevationTransferFcn_C
    * Lab3_IMU_LQRI_X.ElevationTransferFcn_CSTATE;
  Lab3_IMU_LQRI_B.ElevationTransferFcn += Lab3_IMU_LQRI_P.ElevationTransferFcn_D
    * Lab3_IMU_LQRI_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* S-Function (stream_call_block): '<S9>/Stream Call1' incorporates:
     *  Constant: '<S9>/Constant'
     *  S-Function (string_constant_block): '<S9>/String Constant'
     */

    /* S-Function Block: Lab3_IMU_LQRI/IMU/IMU/Stream Call1 (stream_call_block) */
    {
      t_error result = 0;
      t_boolean close_flag = (Lab3_IMU_LQRI_P.Constant_Value_p != 0);
      rtb_StreamCall1_o1 = NULL;
      switch (Lab3_IMU_LQRI_DW.StreamCall1_State) {
       case STREAM_CALL_STATE_NOT_CONNECTED:
        {
          if (!close_flag) {
            /* Make sure URI is null-terminated */
            if (string_length((char *) Lab3_IMU_LQRI_P.StringConstant_Value, 255)
                == 255) {
              rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                                "URI passed to Stream Call block is not null-terminated!");
              result = -QERR_STRING_NOT_TERMINATED;
            } else {
              result = stream_connect((char *)
                Lab3_IMU_LQRI_P.StringConstant_Value,
                Lab3_IMU_LQRI_P.StreamCall1_NonBlocking != 0,
                Lab3_IMU_LQRI_P.StreamCall1_SendBufferSize,
                Lab3_IMU_LQRI_P.StreamCall1_ReceiveBufferSize,
                &Lab3_IMU_LQRI_DW.StreamCall1_Stream);
              if (result == 0) {
                Lab3_IMU_LQRI_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
                stream_set_byte_order(Lab3_IMU_LQRI_DW.StreamCall1_Stream,
                                      (t_stream_byte_order)
                                      Lab3_IMU_LQRI_P.StreamCall1_Endian);
                rtb_StreamCall1_o1 = &Lab3_IMU_LQRI_DW.StreamCall1_Stream;
              } else if (result == -QERR_WOULD_BLOCK) {
                Lab3_IMU_LQRI_DW.StreamCall1_State =
                  STREAM_CALL_STATE_CONNECTING;
                result = 0;
              }
            }
          }
          break;
        }

       case STREAM_CALL_STATE_CONNECTING:
        {
          if (!close_flag) {
            const t_timeout timeout = { 0, 0, false };/* zero seconds */

            result = stream_poll(Lab3_IMU_LQRI_DW.StreamCall1_Stream, &timeout,
                                 STREAM_POLL_CONNECT);
            if (result > 0) {
              Lab3_IMU_LQRI_DW.StreamCall1_State = STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(Lab3_IMU_LQRI_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    Lab3_IMU_LQRI_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &Lab3_IMU_LQRI_DW.StreamCall1_Stream;
              result = 0;
              break;
            } else if (result == 0) {
              break;
            }
          }

          /* Fall through deliberately */
        }

       case STREAM_CALL_STATE_CONNECTED:
        {
          rtb_StreamCall1_o1 = &Lab3_IMU_LQRI_DW.StreamCall1_Stream;
          if (!close_flag) {
            break;
          }

          /* Fall through deliberately */
        }

       default:
        {
          t_error close_result = stream_close
            (Lab3_IMU_LQRI_DW.StreamCall1_Stream);
          if (close_result == 0) {
            Lab3_IMU_LQRI_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
            Lab3_IMU_LQRI_DW.StreamCall1_Stream = NULL;
            rtb_StreamCall1_o1 = NULL;
          } else if (result == 0) {
            result = close_result;
          }
          break;
        }
      }

      Lab3_IMU_LQRI_B.StreamCall1_o2 = Lab3_IMU_LQRI_DW.StreamCall1_State;
      rtb_StreamCall1_o3 = (int32_T) result;
    }

    /* S-Function (stream_formatted_write_block): '<S9>/Stream Formatted Write' incorporates:
     *  Constant: '<S9>/Constant1'
     */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          Lab3_IMU_LQRI_P.StreamFormattedWrite_MaxUnits,
          &rtb_StreamFormattedWrite_o2, "%c\n"
          , (char) Lab3_IMU_LQRI_P.Constant1_Value_i
          );
        if (result > 0) {
          result = stream_flush(*rtb_StreamCall1_o1);
        }

        if (result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      }
    }

    /* S-Function (stream_read_block): '<S9>/Stream Read1' incorporates:
     *  Constant: '<S9>/Constant1'
     *  S-Function (stream_call_block): '<S9>/Stream Call1'
     *  S-Function (stream_formatted_write_block): '<S9>/Stream Formatted Write'
     */

    /* S-Function Block: Lab3_IMU_LQRI/IMU/IMU/Stream Read1 (stream_read_block) */
    {
      t_error result;
      memset(&rtb_StreamRead1_o2[0], 0, 10 * sizeof(real32_T));
      if (((t_stream_ptr)rtb_StreamCall1_o1) != NULL) {
        result = stream_receive_unit_array(*((t_stream_ptr)rtb_StreamCall1_o1),
          &rtb_StreamRead1_o2[0], sizeof(real32_T), 10);
        rtb_StreamRead1_o3 = (result > 0);
        if (result > 0 || result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      } else {
        rtb_StreamRead1_o3 = false;
        result = 0;
      }
    }

    for (i = 0; i < 10; i++) {
      /* Switch: '<S9>/Switch' */
      if (rtb_StreamRead1_o3) {
        /* Switch: '<S9>/Switch' incorporates:
         *  DataTypeConversion: '<S9>/Data Type Conversion'
         */
        Lab3_IMU_LQRI_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        /* Switch: '<S9>/Switch' incorporates:
         *  Memory: '<S9>/Memory'
         */
        Lab3_IMU_LQRI_B.Switch[i] = Lab3_IMU_LQRI_DW.Memory_PreviousInput[i];
      }

      /* End of Switch: '<S9>/Switch' */
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S9>/Gain1' */
      Lab3_IMU_LQRI_B.Gain1[i] = 0.0;

      /* Gain: '<S9>/Gain2' */
      Lab3_IMU_LQRI_B.Gain2[i] = 0.0;

      /* Gain: '<S9>/Gain1' */
      Lab3_IMU_LQRI_B.Gain1[i] += Lab3_IMU_LQRI_P.Gain1_Gain[i] *
        Lab3_IMU_LQRI_B.Switch[3];

      /* Gain: '<S9>/Gain2' */
      Lab3_IMU_LQRI_B.Gain2[i] += Lab3_IMU_LQRI_P.Gain2_Gain[i] *
        Lab3_IMU_LQRI_B.Switch[0];

      /* Gain: '<S9>/Gain1' */
      Lab3_IMU_LQRI_B.Gain1[i] += Lab3_IMU_LQRI_P.Gain1_Gain[i + 3] *
        Lab3_IMU_LQRI_B.Switch[4];

      /* Gain: '<S9>/Gain2' */
      Lab3_IMU_LQRI_B.Gain2[i] += Lab3_IMU_LQRI_P.Gain2_Gain[i + 3] *
        Lab3_IMU_LQRI_B.Switch[1];

      /* Gain: '<S9>/Gain1' */
      Lab3_IMU_LQRI_B.Gain1[i] += Lab3_IMU_LQRI_P.Gain1_Gain[i + 6] *
        Lab3_IMU_LQRI_B.Switch[5];

      /* Gain: '<S9>/Gain2' */
      Lab3_IMU_LQRI_B.Gain2[i] += Lab3_IMU_LQRI_P.Gain2_Gain[i + 6] *
        Lab3_IMU_LQRI_B.Switch[2];
    }

    /* DataTypeConversion: '<Root>/Data Type Conversion' */
    Lab3_IMU_LQRI_B.DataTypeConversion = rtb_StreamRead1_o3;

    /* MATLAB Function: '<S3>/Acc til ang' */
    /* MATLAB Function 'IMU/Acc til ang': '<S7>:1' */
    /* '<S7>:1:2' */
    /* '<S7>:1:3' */
    /* '<S7>:1:4' */
    /* '<S7>:1:5' */
    Lab3_IMU_LQRI_B.angles[0] = rt_atan2d_snf(-Lab3_IMU_LQRI_B.Gain2[1],
      -Lab3_IMU_LQRI_B.Gain2[2]);
    Lab3_IMU_LQRI_B.angles[1] = rt_atan2d_snf(Lab3_IMU_LQRI_B.Gain2[0], sqrt
      (Lab3_IMU_LQRI_B.Gain2[1] * Lab3_IMU_LQRI_B.Gain2[1] +
       Lab3_IMU_LQRI_B.Gain2[2] * Lab3_IMU_LQRI_B.Gain2[2]));

    /* MATLAB Function: '<S3>/Gyro vector to [pitch rate, elevation rate, travle rate]' */
    /* MATLAB Function 'IMU/Gyro vector to [pitch rate, elevation rate, travle rate]': '<S8>:1' */
    /* '<S8>:1:3' */
    /* '<S8>:1:4' */
    /* '<S8>:1:10' */
    /* '<S8>:1:14' */
    euler_rates_tmp = tan(Lab3_IMU_LQRI_B.angles[1]);
    euler_rates_tmp_0 = sin(Lab3_IMU_LQRI_B.angles[0]);
    euler_rates_tmp_1 = cos(Lab3_IMU_LQRI_B.angles[0]);
    euler_rates_tmp_2 = cos(Lab3_IMU_LQRI_B.angles[1]);
    tmp_1[0] = 1.0;
    tmp_1[3] = euler_rates_tmp_0 * euler_rates_tmp;
    tmp_1[6] = euler_rates_tmp_1 * euler_rates_tmp;
    tmp_1[1] = 0.0;
    tmp_1[4] = euler_rates_tmp_1;
    tmp_1[7] = -euler_rates_tmp_0;
    tmp_1[2] = 0.0;
    tmp_1[5] = euler_rates_tmp_0 / euler_rates_tmp_2;
    tmp_1[8] = euler_rates_tmp_1 / euler_rates_tmp_2;
    for (i = 0; i < 3; i++) {
      Lab3_IMU_LQRI_B.euler_rates[i] = 0.0;
      Lab3_IMU_LQRI_B.euler_rates[i] += tmp_1[i] * Lab3_IMU_LQRI_B.Gain1[0];
      Lab3_IMU_LQRI_B.euler_rates[i] += tmp_1[i + 3] * Lab3_IMU_LQRI_B.Gain1[1];
      Lab3_IMU_LQRI_B.euler_rates[i] += tmp_1[i + 6] * Lab3_IMU_LQRI_B.Gain1[2];
    }

    /* End of MATLAB Function: '<S3>/Gyro vector to [pitch rate, elevation rate, travle rate]' */
  }

  for (i = 0; i < 5; i++) {
    /* Integrator: '<S6>/Integrator' */
    Lab3_IMU_LQRI_B.Integrator[i] = Lab3_IMU_LQRI_X.Integrator_CSTATE[i];
  }

  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* FromWorkspace: '<Root>/From Workspace' */
    {
      real_T *pDataValues = (real_T *)
        Lab3_IMU_LQRI_DW.FromWorkspace_PWORK.DataPtr;
      real_T *pTimeValues = (real_T *)
        Lab3_IMU_LQRI_DW.FromWorkspace_PWORK.TimePtr;
      int_T currTimeIndex = Lab3_IMU_LQRI_DW.FromWorkspace_IWORK.PrevIndex;
      real_T t = Lab3_IMU_LQRI_M->Timing.t[1];
      if (t >= pTimeValues[22500]) {
        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            (&Lab3_IMU_LQRI_B.FromWorkspace[0])[elIdx] = pDataValues[22500];
            pDataValues += 22501;
          }
        }
      } else {
        /* Get index */
        if (t <= pTimeValues[0]) {
          currTimeIndex = 0;
        } else if (t >= pTimeValues[22500]) {
          currTimeIndex = 22499;
        } else {
          if (t < pTimeValues[currTimeIndex]) {
            while (t < pTimeValues[currTimeIndex]) {
              currTimeIndex--;
            }
          } else {
            while (t >= pTimeValues[currTimeIndex + 1]) {
              currTimeIndex++;
            }
          }
        }

        Lab3_IMU_LQRI_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

        /* Post output */
        {
          real_T t1 = pTimeValues[currTimeIndex];
          real_T t2 = pTimeValues[currTimeIndex + 1];
          if (t1 == t2) {
            if (t < t1) {
              {
                int_T elIdx;
                for (elIdx = 0; elIdx < 2; ++elIdx) {
                  (&Lab3_IMU_LQRI_B.FromWorkspace[0])[elIdx] =
                    pDataValues[currTimeIndex];
                  pDataValues += 22501;
                }
              }
            } else {
              {
                int_T elIdx;
                for (elIdx = 0; elIdx < 2; ++elIdx) {
                  (&Lab3_IMU_LQRI_B.FromWorkspace[0])[elIdx] =
                    pDataValues[currTimeIndex + 1];
                  pDataValues += 22501;
                }
              }
            }
          } else {
            real_T f1 = (t2 - t) / (t2 - t1);
            real_T f2 = 1.0 - f1;
            real_T d1;
            real_T d2;
            int_T TimeIndex= currTimeIndex;

            {
              int_T elIdx;
              for (elIdx = 0; elIdx < 2; ++elIdx) {
                d1 = pDataValues[TimeIndex];
                d2 = pDataValues[TimeIndex + 1];
                (&Lab3_IMU_LQRI_B.FromWorkspace[0])[elIdx] = (real_T)
                  rtInterpolate(d1, d2, f1, f2);
                pDataValues += 22501;
              }
            }
          }
        }
      }
    }

    /* Gain: '<S5>/Multiply' */
    Lab3_IMU_LQRI_B.Fr[0] = 0.0;
    Lab3_IMU_LQRI_B.Fr[0] += Lab3_IMU_LQRI_P.F[0] *
      Lab3_IMU_LQRI_B.FromWorkspace[0];
    Lab3_IMU_LQRI_B.Fr[0] += Lab3_IMU_LQRI_P.F[2] *
      Lab3_IMU_LQRI_B.FromWorkspace[1];
    Lab3_IMU_LQRI_B.Fr[1] = 0.0;
    Lab3_IMU_LQRI_B.Fr[1] += Lab3_IMU_LQRI_P.F[1] *
      Lab3_IMU_LQRI_B.FromWorkspace[0];
    Lab3_IMU_LQRI_B.Fr[1] += Lab3_IMU_LQRI_P.F[3] *
      Lab3_IMU_LQRI_B.FromWorkspace[1];

    /* ManualSwitch: '<S5>/Manual Switch' */
    if (Lab3_IMU_LQRI_P.ManualSwitch_CurrentSetting == 1) {
      /* ManualSwitch: '<S5>/Manual Switch' incorporates:
       *  Constant: '<S5>/Constant'
       */
      Lab3_IMU_LQRI_B.ManualSwitch = Lab3_IMU_LQRI_P.Constant_Value;
    } else {
      /* ManualSwitch: '<S5>/Manual Switch' incorporates:
       *  Constant: '<S5>/Constant1'
       */
      Lab3_IMU_LQRI_B.ManualSwitch = Lab3_IMU_LQRI_P.Constant1_Value;
    }

    /* End of ManualSwitch: '<S5>/Manual Switch' */
  }

  /* Integrator: '<S5>/Integrator' */
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    zcEvent = rt_ZCFcn(ANY_ZERO_CROSSING,
                       &Lab3_IMU_LQRI_PrevZCX.Integrator_Reset_ZCE,
                       (Lab3_IMU_LQRI_B.ManualSwitch));

    /* evaluate zero-crossings and the level of the reset signal */
    if ((zcEvent != NO_ZCEVENT) || (Lab3_IMU_LQRI_B.ManualSwitch != 0.0)) {
      Lab3_IMU_LQRI_X.Integrator_CSTATE_i[0] = Lab3_IMU_LQRI_P.Integrator_IC_c;
      Lab3_IMU_LQRI_X.Integrator_CSTATE_i[1] = Lab3_IMU_LQRI_P.Integrator_IC_c;
    }
  }

  /* SignalConversion generated from: '<S5>/Gain' */
  tmp[2] = Lab3_IMU_LQRI_B.Integrator[3];

  /* Integrator: '<S5>/Integrator' */
  Lab3_IMU_LQRI_B.Integrator_m[0] = Lab3_IMU_LQRI_X.Integrator_CSTATE_i[0];

  /* SignalConversion generated from: '<S5>/Gain' */
  tmp[0] = Lab3_IMU_LQRI_B.Integrator[0];
  tmp[3] = Lab3_IMU_LQRI_B.Integrator_m[0];

  /* Integrator: '<S5>/Integrator' */
  Lab3_IMU_LQRI_B.Integrator_m[1] = Lab3_IMU_LQRI_X.Integrator_CSTATE_i[1];

  /* SignalConversion generated from: '<S5>/Gain' */
  tmp[1] = Lab3_IMU_LQRI_B.Integrator[1];
  tmp[4] = Lab3_IMU_LQRI_B.Integrator_m[1];
  for (i = 0; i < 2; i++) {
    /* Sum: '<S5>/Subtract' incorporates:
     *  Gain: '<S5>/Gain'
     */
    euler_rates_tmp = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      euler_rates_tmp += Lab3_IMU_LQRI_P.K[(i_0 << 1) + i] * tmp[i_0];
    }

    Lab3_IMU_LQRI_B.u[i] = Lab3_IMU_LQRI_B.Fr[i] - euler_rates_tmp;

    /* End of Sum: '<S5>/Subtract' */
  }

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<Root>/Vs0'
   */
  Lab3_IMU_LQRI_B.Sum = Lab3_IMU_LQRI_B.u[0] + Lab3_IMU_LQRI_P.Vs0;
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* SignalConversion generated from: '<Root>/To File' */
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[0] =
      Lab3_IMU_LQRI_B.TravelCounttorad;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[1] =
      Lab3_IMU_LQRI_B.TravelTransferFcn;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[2] =
      Lab3_IMU_LQRI_B.PitchCounttorad;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[3] =
      Lab3_IMU_LQRI_B.PitchTransferFcn;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[4] =
      Lab3_IMU_LQRI_B.ElevationCounttorad;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[5] =
      Lab3_IMU_LQRI_B.ElevationTransferFcn;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[6] = Lab3_IMU_LQRI_B.Gain1[0];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[9] = Lab3_IMU_LQRI_B.Gain2[0];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[7] = Lab3_IMU_LQRI_B.Gain1[1];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[10] = Lab3_IMU_LQRI_B.Gain2
      [1];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[8] = Lab3_IMU_LQRI_B.Gain1[2];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[11] = Lab3_IMU_LQRI_B.Gain2
      [2];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[12] =
      Lab3_IMU_LQRI_B.DataTypeConversion;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[13] =
      Lab3_IMU_LQRI_B.angles[0];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[14] =
      Lab3_IMU_LQRI_B.euler_rates[0];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[15] =
      Lab3_IMU_LQRI_B.angles[1];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[16] =
      Lab3_IMU_LQRI_B.euler_rates[1];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[17] =
      Lab3_IMU_LQRI_B.euler_rates[2];
    for (i = 0; i < 5; i++) {
      Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[i + 18] =
        Lab3_IMU_LQRI_B.Integrator[i];
    }

    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[23] =
      Lab3_IMU_LQRI_B.FromWorkspace[0];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[24] =
      Lab3_IMU_LQRI_B.FromWorkspace[1];
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[25] = Lab3_IMU_LQRI_B.Sum;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[26] = Lab3_IMU_LQRI_B.u[1];

    /* End of SignalConversion generated from: '<Root>/To File' */
    /* ToFile: '<Root>/To File' */
    if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
      if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M) ) {
        {
          if (!(++Lab3_IMU_LQRI_DW.ToFile_IWORK.Decimation % 1) &&
              (Lab3_IMU_LQRI_DW.ToFile_IWORK.Count * (27 + 1)) + 1 < 100000000 )
          {
            FILE *fp = (FILE *) Lab3_IMU_LQRI_DW.ToFile_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[27 + 1];
              Lab3_IMU_LQRI_DW.ToFile_IWORK.Decimation = 0;
              u[0] = Lab3_IMU_LQRI_M->Timing.t[1];
              u[1] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[0];
              u[2] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[1];
              u[3] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[2];
              u[4] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[3];
              u[5] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[4];
              u[6] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[5];
              u[7] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[6];
              u[8] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[7];
              u[9] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[8];
              u[10] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[9];
              u[11] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[10];
              u[12] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[11];
              u[13] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[12];
              u[14] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[13];
              u[15] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[14];
              u[16] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[15];
              u[17] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[16];
              u[18] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[17];
              u[19] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[18];
              u[20] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[19];
              u[21] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[20];
              u[22] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[21];
              u[23] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[22];
              u[24] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[23];
              u[25] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[24];
              u[26] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[25];
              u[27] = Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[26];
              if (fwrite(u, sizeof(real_T), 27 + 1, fp) != 27 + 1) {
                rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                                  "Error writing to MAT-file p3Run.mat");
                return;
              }

              if (((++Lab3_IMU_LQRI_DW.ToFile_IWORK.Count) * (27 + 1))+1 >=
                  100000000) {
                (void)fprintf(stdout,
                              "*** The ToFile block will stop logging data before\n"
                              "    the simulation has ended, because it has reached\n"
                              "    the maximum number of elements (100000000)\n"
                              "    allowed in MAT-file p3Run.mat.\n");
              }
            }
          }
        }
      }
    }
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  euler_rates_tmp = (Lab3_IMU_LQRI_B.Sum - Lab3_IMU_LQRI_B.u[1]) *
    Lab3_IMU_LQRI_P.Frontgain_Gain;

  /* Saturate: '<S2>/Front motor: Saturation' */
  if (euler_rates_tmp > Lab3_IMU_LQRI_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S2>/Front motor: Saturation' */
    Lab3_IMU_LQRI_B.FrontmotorSaturation =
      Lab3_IMU_LQRI_P.FrontmotorSaturation_UpperSat;
  } else if (euler_rates_tmp < Lab3_IMU_LQRI_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S2>/Front motor: Saturation' */
    Lab3_IMU_LQRI_B.FrontmotorSaturation =
      Lab3_IMU_LQRI_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S2>/Front motor: Saturation' */
    Lab3_IMU_LQRI_B.FrontmotorSaturation = euler_rates_tmp;
  }

  /* End of Saturate: '<S2>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  euler_rates_tmp = (Lab3_IMU_LQRI_B.Sum + Lab3_IMU_LQRI_B.u[1]) *
    Lab3_IMU_LQRI_P.Backgain_Gain;

  /* Saturate: '<S2>/Back motor: Saturation' */
  if (euler_rates_tmp > Lab3_IMU_LQRI_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S2>/Back motor: Saturation' */
    Lab3_IMU_LQRI_B.BackmotorSaturation =
      Lab3_IMU_LQRI_P.BackmotorSaturation_UpperSat;
  } else if (euler_rates_tmp < Lab3_IMU_LQRI_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S2>/Back motor: Saturation' */
    Lab3_IMU_LQRI_B.BackmotorSaturation =
      Lab3_IMU_LQRI_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S2>/Back motor: Saturation' */
    Lab3_IMU_LQRI_B.BackmotorSaturation = euler_rates_tmp;
  }

  /* End of Saturate: '<S2>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: Lab3_IMU_LQRI/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      Lab3_IMU_LQRI_DW.HILWriteAnalog_Buffer[0] =
        Lab3_IMU_LQRI_B.FrontmotorSaturation;
      Lab3_IMU_LQRI_DW.HILWriteAnalog_Buffer[1] =
        Lab3_IMU_LQRI_B.BackmotorSaturation;
      result = hil_write_analog(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILWriteAnalog_channels, 2,
        &Lab3_IMU_LQRI_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
      }
    }

    /* S-Function (stop_with_error_block): '<S9>/Stop with Call Error' */

    /* S-Function Block: Lab3_IMU_LQRI/IMU/IMU/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    /* SignalConversion generated from: '<S5>/p2Run' */
    rtb_TmpSignalConversionAtp2RunI[0] = Lab3_IMU_LQRI_B.FromWorkspace[0];
    rtb_TmpSignalConversionAtp2RunI[2] = Lab3_IMU_LQRI_B.u[0];
    rtb_TmpSignalConversionAtp2RunI[4] = Lab3_IMU_LQRI_B.Integrator_m[0];
    rtb_TmpSignalConversionAtp2RunI[1] = Lab3_IMU_LQRI_B.FromWorkspace[1];
    rtb_TmpSignalConversionAtp2RunI[3] = Lab3_IMU_LQRI_B.u[1];
    rtb_TmpSignalConversionAtp2RunI[5] = Lab3_IMU_LQRI_B.Integrator_m[1];

    /* ToFile: '<S5>/p2Run' */
    if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
      if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M) ) {
        {
          if (!(++Lab3_IMU_LQRI_DW.p2Run_IWORK.Decimation % 1) &&
              (Lab3_IMU_LQRI_DW.p2Run_IWORK.Count * (6 + 1)) + 1 < 100000000 ) {
            FILE *fp = (FILE *) Lab3_IMU_LQRI_DW.p2Run_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[6 + 1];
              Lab3_IMU_LQRI_DW.p2Run_IWORK.Decimation = 0;
              u[0] = Lab3_IMU_LQRI_M->Timing.t[1];
              u[1] = rtb_TmpSignalConversionAtp2RunI[0];
              u[2] = rtb_TmpSignalConversionAtp2RunI[1];
              u[3] = rtb_TmpSignalConversionAtp2RunI[2];
              u[4] = rtb_TmpSignalConversionAtp2RunI[3];
              u[5] = rtb_TmpSignalConversionAtp2RunI[4];
              u[6] = rtb_TmpSignalConversionAtp2RunI[5];
              if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
                rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                                  "Error writing to MAT-file p2Run.mat");
                return;
              }

              if (((++Lab3_IMU_LQRI_DW.p2Run_IWORK.Count) * (6 + 1))+1 >=
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

  /* SignalConversion generated from: '<S5>/Integrator' incorporates:
   *  Sum: '<S10>/Sum1'
   *  Sum: '<S10>/Sum2'
   */
  Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator[0] =
    Lab3_IMU_LQRI_B.FromWorkspace[0] - Lab3_IMU_LQRI_B.Integrator[0];
  Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator[1] =
    Lab3_IMU_LQRI_B.FromWorkspace[1] - Lab3_IMU_LQRI_B.Integrator[3];

  /* Gain: '<S6>/C_obs' */
  for (i = 0; i < 5; i++) {
    rtb_Sum[i] = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      rtb_Sum[i] += Lab3_IMU_LQRI_P.C_obs_Gain[5 * i_0 + i] *
        Lab3_IMU_LQRI_B.Integrator[i_0];
    }
  }

  /* End of Gain: '<S6>/C_obs' */

  /* Sum: '<S6>/Sum' incorporates:
   *  Gain: '<S6>/B_obs'
   */
  tmp[0] = Lab3_IMU_LQRI_B.angles[0] - rtb_Sum[0];
  tmp[1] = Lab3_IMU_LQRI_B.euler_rates[0] - rtb_Sum[1];
  tmp[2] = Lab3_IMU_LQRI_B.angles[1] - rtb_Sum[2];
  tmp[3] = Lab3_IMU_LQRI_B.euler_rates[1] - rtb_Sum[3];
  tmp[4] = Lab3_IMU_LQRI_B.euler_rates[2] - rtb_Sum[4];
  for (i = 0; i < 5; i++) {
    rtb_Sum[i] = tmp[i];
    tmp_0[i] = Lab3_IMU_LQRI_P.B_obs[i + 5] * Lab3_IMU_LQRI_B.u[1] +
      Lab3_IMU_LQRI_P.B_obs[i] * Lab3_IMU_LQRI_B.u[0];
  }

  /* End of Sum: '<S6>/Sum' */
  for (i = 0; i < 5; i++) {
    /* Gain: '<S6>/L' */
    tmp[i] = 0.0;

    /* Sum: '<S6>/Sum1' */
    euler_rates_tmp = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      /* Sum: '<S6>/Sum1' incorporates:
       *  Gain: '<S6>/A_obs'
       *  Gain: '<S6>/L'
       */
      tmp_2 = 5 * i_0 + i;

      /* Sum: '<S6>/Sum1' incorporates:
       *  Gain: '<S6>/A_obs'
       */
      euler_rates_tmp += Lab3_IMU_LQRI_P.A_obs[tmp_2] *
        Lab3_IMU_LQRI_B.Integrator[i_0];

      /* Gain: '<S6>/L' */
      tmp[i] += Lab3_IMU_LQRI_P.L_obs[tmp_2] * rtb_Sum[i_0];
    }

    /* Sum: '<S6>/Sum1' incorporates:
     *  Gain: '<S6>/A_obs'
     */
    Lab3_IMU_LQRI_B.Sum1[i] = (tmp_0[i] + tmp[i]) + euler_rates_tmp;
  }

  /* RateTransition: '<S4>/Rate Transition: x' */
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    if (Lab3_IMU_LQRI_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S4>/Rate Transition: x' */
      Lab3_IMU_LQRI_B.RateTransitionx = Lab3_IMU_LQRI_DW.RateTransitionx_Buffer0;
    }

    /* DeadZone: '<S4>/Dead Zone: x' */
    if (Lab3_IMU_LQRI_B.RateTransitionx > Lab3_IMU_LQRI_P.DeadZonex_End) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_LQRI_B.RateTransitionx -
        Lab3_IMU_LQRI_P.DeadZonex_End;
    } else if (Lab3_IMU_LQRI_B.RateTransitionx >=
               Lab3_IMU_LQRI_P.DeadZonex_Start) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = 0.0;
    } else {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_LQRI_B.RateTransitionx -
        Lab3_IMU_LQRI_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: x' */

    /* Gain: '<S4>/Joystick_gain_x' incorporates:
     *  Gain: '<S4>/Gain: x'
     */
    Lab3_IMU_LQRI_B.Joystick_gain_x = Lab3_IMU_LQRI_P.Gainx_Gain * rtb_DeadZoney
      * Lab3_IMU_LQRI_P.Joystick_gain_x;

    /* RateTransition: '<S4>/Rate Transition: y' */
    if (Lab3_IMU_LQRI_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S4>/Rate Transition: y' */
      Lab3_IMU_LQRI_B.RateTransitiony = Lab3_IMU_LQRI_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: y' */

    /* DeadZone: '<S4>/Dead Zone: y' */
    if (Lab3_IMU_LQRI_B.RateTransitiony > Lab3_IMU_LQRI_P.DeadZoney_End) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_LQRI_B.RateTransitiony -
        Lab3_IMU_LQRI_P.DeadZoney_End;
    } else if (Lab3_IMU_LQRI_B.RateTransitiony >=
               Lab3_IMU_LQRI_P.DeadZoney_Start) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = 0.0;
    } else {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_LQRI_B.RateTransitiony -
        Lab3_IMU_LQRI_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: y' */

    /* Gain: '<S4>/Joystick_gain_y' incorporates:
     *  Gain: '<S4>/Gain: y'
     */
    Lab3_IMU_LQRI_B.Joystick_gain_y = Lab3_IMU_LQRI_P.Gainy_Gain * rtb_DeadZoney
      * Lab3_IMU_LQRI_P.Joystick_gain_y;
  }

  /* End of RateTransition: '<S4>/Rate Transition: x' */
}

/* Model update function for TID0 */
void Lab3_IMU_LQRI_update0(void)       /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    /* Update for Memory: '<S9>/Memory' */
    memcpy(&Lab3_IMU_LQRI_DW.Memory_PreviousInput[0], &Lab3_IMU_LQRI_B.Switch[0],
           10U * sizeof(real_T));
  }

  if (rtmIsMajorTimeStep(Lab3_IMU_LQRI_M)) {
    rt_ertODEUpdateContinuousStates(&Lab3_IMU_LQRI_M->solverInfo);
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
  if (!(++Lab3_IMU_LQRI_M->Timing.clockTick0)) {
    ++Lab3_IMU_LQRI_M->Timing.clockTickH0;
  }

  Lab3_IMU_LQRI_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Lab3_IMU_LQRI_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab3_IMU_LQRI_M->Timing.clockTick1)) {
    ++Lab3_IMU_LQRI_M->Timing.clockTickH1;
  }

  Lab3_IMU_LQRI_M->Timing.t[1] = Lab3_IMU_LQRI_M->Timing.clockTick1 *
    Lab3_IMU_LQRI_M->Timing.stepSize1 + Lab3_IMU_LQRI_M->Timing.clockTickH1 *
    Lab3_IMU_LQRI_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void Lab3_IMU_LQRI_derivatives(void)
{
  XDot_Lab3_IMU_LQRI_T *_rtXdot;
  int32_T i;
  _rtXdot = ((XDot_Lab3_IMU_LQRI_T *) Lab3_IMU_LQRI_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += Lab3_IMU_LQRI_P.TravelTransferFcn_A *
    Lab3_IMU_LQRI_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += Lab3_IMU_LQRI_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += Lab3_IMU_LQRI_P.PitchTransferFcn_A *
    Lab3_IMU_LQRI_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += Lab3_IMU_LQRI_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += Lab3_IMU_LQRI_P.ElevationTransferFcn_A
    * Lab3_IMU_LQRI_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += Lab3_IMU_LQRI_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S6>/Integrator' */
  for (i = 0; i < 5; i++) {
    _rtXdot->Integrator_CSTATE[i] = Lab3_IMU_LQRI_B.Sum1[i];
  }

  /* End of Derivatives for Integrator: '<S6>/Integrator' */

  /* Derivatives for Integrator: '<S5>/Integrator' */
  if (Lab3_IMU_LQRI_B.ManualSwitch == 0.0) {
    _rtXdot->Integrator_CSTATE_i[0] =
      Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator[0];
    _rtXdot->Integrator_CSTATE_i[1] =
      Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator[1];
  } else {
    /* level reset is active */
    _rtXdot->Integrator_CSTATE_i[0] = 0.0;
    _rtXdot->Integrator_CSTATE_i[1] = 0.0;
  }

  /* End of Derivatives for Integrator: '<S5>/Integrator' */
}

/* Model output function for TID2 */
void Lab3_IMU_LQRI_output2(void)       /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_GameController_o4;
  real_T rtb_GameController_o5;

  /* S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab3_IMU_LQRI/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab3_IMU_LQRI_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll(Lab3_IMU_LQRI_DW.GameController_Controller,
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
  Lab3_IMU_LQRI_DW.RateTransitionx_Buffer0 = rtb_GameController_o4;

  /* RateTransition: '<S4>/Rate Transition: y' */
  Lab3_IMU_LQRI_DW.RateTransitiony_Buffer0 = rtb_GameController_o5;
}

/* Model update function for TID2 */
void Lab3_IMU_LQRI_update2(void)       /* Sample time: [0.01s, 0.0s] */
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
  if (!(++Lab3_IMU_LQRI_M->Timing.clockTick2)) {
    ++Lab3_IMU_LQRI_M->Timing.clockTickH2;
  }

  Lab3_IMU_LQRI_M->Timing.t[2] = Lab3_IMU_LQRI_M->Timing.clockTick2 *
    Lab3_IMU_LQRI_M->Timing.stepSize2 + Lab3_IMU_LQRI_M->Timing.clockTickH2 *
    Lab3_IMU_LQRI_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void Lab3_IMU_LQRI_output(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab3_IMU_LQRI_output0();
    break;

   case 2 :
    Lab3_IMU_LQRI_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void Lab3_IMU_LQRI_update(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab3_IMU_LQRI_update0();
    break;

   case 2 :
    Lab3_IMU_LQRI_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void Lab3_IMU_LQRI_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab3_IMU_LQRI/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab3_IMU_LQRI_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Lab3_IMU_LQRI_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab3_IMU_LQRI_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
      return;
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab3_IMU_LQRI_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab3_IMU_LQRI_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab3_IMU_LQRI_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab3_IMU_LQRI_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_AIChannels, 8U,
        &Lab3_IMU_LQRI_DW.HILInitialize_AIMinimums[0],
        &Lab3_IMU_LQRI_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab3_IMU_LQRI_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab3_IMU_LQRI_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab3_IMU_LQRI_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab3_IMU_LQRI_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_AOChannels, 8U,
        &Lab3_IMU_LQRI_DW.HILInitialize_AOMinimums[0],
        &Lab3_IMU_LQRI_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_AOStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_IMU_LQRI_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_AOChannels, 8U,
        &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if (Lab3_IMU_LQRI_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_IMU_LQRI_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab3_IMU_LQRI_DW.HILInitialize_Card,
         Lab3_IMU_LQRI_P.HILInitialize_AOChannels, 8U,
         &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab3_IMU_LQRI_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab3_IMU_LQRI_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Lab3_IMU_LQRI_DW.HILInitialize_Card,
         Lab3_IMU_LQRI_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Lab3_IMU_LQRI_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_EIStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab3_IMU_LQRI_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab3_IMU_LQRI_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_EIChannels, 8U,
        &Lab3_IMU_LQRI_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_POPStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab3_IMU_LQRI_DW.HILInitialize_POModeValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab3_IMU_LQRI_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab3_IMU_LQRI_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &Lab3_IMU_LQRI_DW.HILInitialize_POModeValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab3_IMU_LQRI_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              Lab3_IMU_LQRI_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab3_IMU_LQRI_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] = Lab3_IMU_LQRI_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab3_IMU_LQRI_DW.HILInitialize_Card,
          &Lab3_IMU_LQRI_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab3_IMU_LQRI_DW.HILInitialize_Card,
          &Lab3_IMU_LQRI_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &Lab3_IMU_LQRI_DW.HILInitialize_POModeValues
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Lab3_IMU_LQRI_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab3_IMU_LQRI_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab3_IMU_LQRI_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab3_IMU_LQRI_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &Lab3_IMU_LQRI_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab3_IMU_LQRI_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab3_IMU_LQRI_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_POChannels, 8U,
        &Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[0],
        &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_POStart && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab3_IMU_LQRI_DW.HILInitialize_Card,
        Lab3_IMU_LQRI_P.HILInitialize_POChannels, 8U,
        &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }

    if (Lab3_IMU_LQRI_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab3_IMU_LQRI_DW.HILInitialize_Card,
         Lab3_IMU_LQRI_P.HILInitialize_POChannels, 8U,
         &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: Lab3_IMU_LQRI/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(Lab3_IMU_LQRI_DW.HILInitialize_Card,
      Lab3_IMU_LQRI_P.HILReadEncoderTimebase_SamplesI,
      Lab3_IMU_LQRI_P.HILReadEncoderTimebase_Channels, 3,
      &Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Lab3_IMU_LQRI_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (Lab3_IMU_LQRI_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
    }
  }

  /* Start for S-Function (stream_call_block): '<S9>/Stream Call1' incorporates:
   *  Constant: '<S9>/Constant'
   *  S-Function (string_constant_block): '<S9>/String Constant'
   */

  /* S-Function Block: Lab3_IMU_LQRI/IMU/IMU/Stream Call1 (stream_call_block) */
  {
    Lab3_IMU_LQRI_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    Lab3_IMU_LQRI_DW.StreamCall1_Stream = NULL;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.002, 0.004, 0.006, 0.008, 0.01,
      0.012, 0.014, 0.016, 0.018000000000000002, 0.02, 0.022, 0.024,
      0.026000000000000002, 0.028, 0.03, 0.032, 0.034, 0.036000000000000004,
      0.038, 0.04, 0.042, 0.044, 0.046, 0.048, 0.05, 0.052000000000000005, 0.054,
      0.056, 0.058, 0.06, 0.062, 0.064, 0.066, 0.068, 0.07, 0.072000000000000008,
      0.074, 0.076, 0.078, 0.08, 0.082, 0.084, 0.086000000000000007, 0.088, 0.09,
      0.092, 0.094, 0.096, 0.098, 0.1, 0.10200000000000001, 0.10400000000000001,
      0.106, 0.108, 0.11, 0.112, 0.114, 0.116, 0.11800000000000001, 0.12, 0.122,
      0.124, 0.126, 0.128, 0.13, 0.132, 0.134, 0.136, 0.138, 0.14,
      0.14200000000000002, 0.14400000000000002, 0.146, 0.148, 0.15, 0.152, 0.154,
      0.156, 0.158, 0.16, 0.162, 0.164, 0.166, 0.168, 0.17, 0.17200000000000001,
      0.17400000000000002, 0.176, 0.178, 0.18, 0.182, 0.184, 0.186, 0.188, 0.19,
      0.192, 0.194, 0.196, 0.198, 0.2, 0.202, 0.20400000000000001,
      0.20600000000000002, 0.20800000000000002, 0.21, 0.212, 0.214, 0.216, 0.218,
      0.22, 0.222, 0.224, 0.226, 0.228, 0.23, 0.232, 0.234, 0.23600000000000002,
      0.23800000000000002, 0.24, 0.242, 0.244, 0.246, 0.248, 0.25, 0.252, 0.254,
      0.256, 0.258, 0.26, 0.262, 0.264, 0.266, 0.268, 0.27, 0.272, 0.274, 0.276,
      0.278, 0.28, 0.28200000000000003, 0.28400000000000003, 0.28600000000000003,
      0.28800000000000003, 0.29, 0.292, 0.294, 0.296, 0.298, 0.3, 0.302, 0.304,
      0.306, 0.308, 0.31, 0.312, 0.314, 0.316, 0.318, 0.32, 0.322, 0.324, 0.326,
      0.328, 0.33, 0.332, 0.334, 0.336, 0.338, 0.34, 0.342, 0.34400000000000003,
      0.34600000000000003, 0.34800000000000003, 0.35000000000000003, 0.352,
      0.354, 0.356, 0.358, 0.36, 0.362, 0.364, 0.366, 0.368, 0.37, 0.372, 0.374,
      0.376, 0.378, 0.38, 0.382, 0.384, 0.386, 0.388, 0.39, 0.392, 0.394, 0.396,
      0.398, 0.4, 0.402, 0.404, 0.406, 0.40800000000000003, 0.41000000000000003,
      0.41200000000000003, 0.41400000000000003, 0.41600000000000004, 0.418, 0.42,
      0.422, 0.424, 0.426, 0.428, 0.43, 0.432, 0.434, 0.436, 0.438, 0.44, 0.442,
      0.444, 0.446, 0.448, 0.45, 0.452, 0.454, 0.456, 0.458, 0.46, 0.462, 0.464,
      0.466, 0.468, 0.47000000000000003, 0.47200000000000003,
      0.47400000000000003, 0.47600000000000003, 0.47800000000000004, 0.48, 0.482,
      0.484, 0.486, 0.488, 0.49, 0.492, 0.494, 0.496, 0.498, 0.5, 0.502, 0.504,
      0.506, 0.508, 0.51, 0.512, 0.514, 0.516, 0.518, 0.52, 0.522, 0.524, 0.526,
      0.528, 0.53, 0.532, 0.534, 0.536, 0.538, 0.54, 0.542, 0.544, 0.546, 0.548,
      0.55, 0.552, 0.554, 0.556, 0.558, 0.56, 0.562, 0.56400000000000006,
      0.56600000000000006, 0.56800000000000006, 0.57000000000000006,
      0.57200000000000006, 0.57400000000000007, 0.57600000000000007, 0.578, 0.58,
      0.582, 0.584, 0.586, 0.588, 0.59, 0.592, 0.594, 0.596, 0.598, 0.6, 0.602,
      0.604, 0.606, 0.608, 0.61, 0.612, 0.614, 0.616, 0.618, 0.62, 0.622, 0.624,
      0.626, 0.628, 0.63, 0.632, 0.634, 0.636, 0.638, 0.64, 0.642, 0.644, 0.646,
      0.648, 0.65, 0.652, 0.654, 0.656, 0.658, 0.66, 0.662, 0.664, 0.666, 0.668,
      0.67, 0.672, 0.674, 0.676, 0.678, 0.68, 0.682, 0.684, 0.686,
      0.68800000000000006, 0.69000000000000006, 0.69200000000000006,
      0.69400000000000006, 0.69600000000000006, 0.69800000000000006,
      0.70000000000000007, 0.70200000000000007, 0.704, 0.706, 0.708, 0.71, 0.712,
      0.714, 0.716, 0.718, 0.72, 0.722, 0.724, 0.726, 0.728, 0.73, 0.732, 0.734,
      0.736, 0.738, 0.74, 0.742, 0.744, 0.746, 0.748, 0.75, 0.752, 0.754, 0.756,
      0.758, 0.76, 0.762, 0.764, 0.766, 0.768, 0.77, 0.772, 0.774, 0.776, 0.778,
      0.78, 0.782, 0.784, 0.786, 0.788, 0.79, 0.792, 0.794, 0.796, 0.798, 0.8,
      0.802, 0.804, 0.806, 0.808, 0.81, 0.812, 0.81400000000000006,
      0.81600000000000006, 0.81800000000000006, 0.82000000000000006,
      0.82200000000000006, 0.82400000000000007, 0.82600000000000007,
      0.82800000000000007, 0.83000000000000007, 0.83200000000000007, 0.834,
      0.836, 0.838, 0.84, 0.842, 0.844, 0.846, 0.848, 0.85, 0.852, 0.854, 0.856,
      0.858, 0.86, 0.862, 0.864, 0.866, 0.868, 0.87, 0.872, 0.874, 0.876, 0.878,
      0.88, 0.882, 0.884, 0.886, 0.888, 0.89, 0.892, 0.894, 0.896, 0.898, 0.9,
      0.902, 0.904, 0.906, 0.908, 0.91, 0.912, 0.914, 0.916, 0.918, 0.92, 0.922,
      0.924, 0.926, 0.928, 0.93, 0.932, 0.934, 0.936, 0.93800000000000006,
      0.94000000000000006, 0.94200000000000006, 0.94400000000000006,
      0.94600000000000006, 0.94800000000000006, 0.95000000000000007,
      0.95200000000000007, 0.95400000000000007, 0.95600000000000007,
      0.95800000000000007, 0.96, 0.962, 0.964, 0.966, 0.968, 0.97, 0.972, 0.974,
      0.976, 0.978, 0.98, 0.982, 0.984, 0.986, 0.988, 0.99, 0.992, 0.994, 0.996,
      0.998, 1.0, 1.002, 1.004, 1.006, 1.008, 1.01, 1.012, 1.014, 1.016, 1.018,
      1.02, 1.022, 1.024, 1.026, 1.028, 1.03, 1.032, 1.034, 1.036, 1.038, 1.04,
      1.042, 1.044, 1.046, 1.048, 1.05, 1.052, 1.054, 1.056, 1.058, 1.06, 1.062,
      1.064, 1.066, 1.068, 1.07, 1.072, 1.074, 1.076, 1.078, 1.08, 1.082, 1.084,
      1.086, 1.088, 1.09, 1.092, 1.094, 1.096, 1.098, 1.1, 1.102, 1.104, 1.106,
      1.108, 1.11, 1.112, 1.114, 1.116, 1.118, 1.12, 1.122, 1.124,
      1.1260000000000001, 1.1280000000000001, 1.1300000000000001,
      1.1320000000000001, 1.1340000000000001, 1.1360000000000001,
      1.1380000000000001, 1.1400000000000001, 1.1420000000000001,
      1.1440000000000001, 1.1460000000000001, 1.1480000000000001,
      1.1500000000000001, 1.1520000000000001, 1.154, 1.156, 1.158, 1.16, 1.162,
      1.164, 1.166, 1.168, 1.17, 1.172, 1.174, 1.176, 1.178, 1.18, 1.182, 1.184,
      1.186, 1.188, 1.19, 1.192, 1.194, 1.196, 1.198, 1.2, 1.202, 1.204, 1.206,
      1.208, 1.21, 1.212, 1.214, 1.216, 1.218, 1.22, 1.222, 1.224, 1.226, 1.228,
      1.23, 1.232, 1.234, 1.236, 1.238, 1.24, 1.242, 1.244, 1.246, 1.248, 1.25,
      1.252, 1.254, 1.256, 1.258, 1.26, 1.262, 1.264, 1.266, 1.268, 1.27, 1.272,
      1.274, 1.276, 1.278, 1.28, 1.282, 1.284, 1.286, 1.288, 1.29, 1.292, 1.294,
      1.296, 1.298, 1.3, 1.302, 1.304, 1.306, 1.308, 1.31, 1.312, 1.314, 1.316,
      1.318, 1.32, 1.322, 1.324, 1.326, 1.328, 1.33, 1.332, 1.334, 1.336, 1.338,
      1.34, 1.342, 1.344, 1.346, 1.348, 1.35, 1.352, 1.354, 1.356, 1.358, 1.36,
      1.362, 1.364, 1.366, 1.368, 1.37, 1.372, 1.374, 1.3760000000000001,
      1.3780000000000001, 1.3800000000000001, 1.3820000000000001,
      1.3840000000000001, 1.3860000000000001, 1.3880000000000001,
      1.3900000000000001, 1.3920000000000001, 1.3940000000000001,
      1.3960000000000001, 1.3980000000000001, 1.4000000000000001,
      1.4020000000000001, 1.4040000000000001, 1.4060000000000001, 1.408, 1.41,
      1.412, 1.414, 1.416, 1.418, 1.42, 1.422, 1.424, 1.426, 1.428, 1.43, 1.432,
      1.434, 1.436, 1.438, 1.44, 1.442, 1.444, 1.446, 1.448, 1.45, 1.452, 1.454,
      1.456, 1.458, 1.46, 1.462, 1.464, 1.466, 1.468, 1.47, 1.472, 1.474, 1.476,
      1.478, 1.48, 1.482, 1.484, 1.486, 1.488, 1.49, 1.492, 1.494, 1.496, 1.498,
      1.5, 1.502, 1.504, 1.506, 1.508, 1.51, 1.512, 1.514, 1.516, 1.518, 1.52,
      1.522, 1.524, 1.526, 1.528, 1.53, 1.532, 1.534, 1.536, 1.538, 1.54, 1.542,
      1.544, 1.546, 1.548, 1.55, 1.552, 1.554, 1.556, 1.558, 1.56, 1.562, 1.564,
      1.566, 1.568, 1.57, 1.572, 1.574, 1.576, 1.578, 1.58, 1.582, 1.584, 1.586,
      1.588, 1.59, 1.592, 1.594, 1.596, 1.598, 1.6, 1.602, 1.604, 1.606, 1.608,
      1.61, 1.612, 1.614, 1.616, 1.618, 1.62, 1.622, 1.624, 1.6260000000000001,
      1.6280000000000001, 1.6300000000000001, 1.6320000000000001,
      1.6340000000000001, 1.6360000000000001, 1.6380000000000001,
      1.6400000000000001, 1.6420000000000001, 1.6440000000000001,
      1.6460000000000001, 1.6480000000000001, 1.6500000000000001,
      1.6520000000000001, 1.6540000000000001, 1.6560000000000001,
      1.6580000000000001, 1.6600000000000001, 1.6620000000000001,
      1.6640000000000001, 1.666, 1.668, 1.67, 1.672, 1.674, 1.676, 1.678, 1.68,
      1.682, 1.684, 1.686, 1.688, 1.69, 1.692, 1.694, 1.696, 1.698, 1.7, 1.702,
      1.704, 1.706, 1.708, 1.71, 1.712, 1.714, 1.716, 1.718, 1.72, 1.722, 1.724,
      1.726, 1.728, 1.73, 1.732, 1.734, 1.736, 1.738, 1.74, 1.742, 1.744, 1.746,
      1.748, 1.75, 1.752, 1.754, 1.756, 1.758, 1.76, 1.762, 1.764, 1.766, 1.768,
      1.77, 1.772, 1.774, 1.776, 1.778, 1.78, 1.782, 1.784, 1.786, 1.788, 1.79,
      1.792, 1.794, 1.796, 1.798, 1.8, 1.802, 1.804, 1.806, 1.808, 1.81, 1.812,
      1.814, 1.816, 1.818, 1.82, 1.822, 1.824, 1.826, 1.828, 1.83, 1.832, 1.834,
      1.836, 1.838, 1.84, 1.842, 1.844, 1.846, 1.848, 1.85, 1.852, 1.854, 1.856,
      1.858, 1.86, 1.862, 1.864, 1.866, 1.868, 1.87, 1.872, 1.874,
      1.8760000000000001, 1.8780000000000001, 1.8800000000000001,
      1.8820000000000001, 1.8840000000000001, 1.8860000000000001,
      1.8880000000000001, 1.8900000000000001, 1.8920000000000001,
      1.8940000000000001, 1.8960000000000001, 1.8980000000000001,
      1.9000000000000001, 1.9020000000000001, 1.9040000000000001,
      1.9060000000000001, 1.9080000000000001, 1.9100000000000001,
      1.9120000000000001, 1.9140000000000001, 1.9160000000000001,
      1.9180000000000001, 1.92, 1.922, 1.924, 1.926, 1.928, 1.93, 1.932, 1.934,
      1.936, 1.938, 1.94, 1.942, 1.944, 1.946, 1.948, 1.95, 1.952, 1.954, 1.956,
      1.958, 1.96, 1.962, 1.964, 1.966, 1.968, 1.97, 1.972, 1.974, 1.976, 1.978,
      1.98, 1.982, 1.984, 1.986, 1.988, 1.99, 1.992, 1.994, 1.996, 1.998, 2.0,
      2.0020000000000002, 2.004, 2.0060000000000002, 2.008, 2.0100000000000002,
      2.012, 2.0140000000000002, 2.016, 2.0180000000000002, 2.02,
      2.0220000000000002, 2.024, 2.0260000000000002, 2.028, 2.0300000000000002,
      2.032, 2.0340000000000003, 2.036, 2.0380000000000003, 2.04,
      2.0420000000000003, 2.044, 2.0460000000000003, 2.048, 2.05, 2.052, 2.054,
      2.056, 2.058, 2.06, 2.062, 2.064, 2.066, 2.068, 2.07, 2.072, 2.074, 2.076,
      2.078, 2.08, 2.082, 2.084, 2.086, 2.088, 2.09, 2.092, 2.094, 2.096, 2.098,
      2.1, 2.102, 2.104, 2.106, 2.108, 2.11, 2.112, 2.114, 2.116, 2.118, 2.12,
      2.122, 2.124, 2.126, 2.128, 2.13, 2.132, 2.134, 2.136, 2.138, 2.14, 2.142,
      2.144, 2.146, 2.148, 2.15, 2.152, 2.154, 2.156, 2.158, 2.16, 2.162, 2.164,
      2.166, 2.168, 2.17, 2.172, 2.174, 2.176, 2.178, 2.18, 2.182, 2.184, 2.186,
      2.188, 2.19, 2.192, 2.194, 2.196, 2.198, 2.2, 2.202, 2.204, 2.206, 2.208,
      2.21, 2.212, 2.214, 2.216, 2.218, 2.22, 2.222, 2.224, 2.226, 2.228, 2.23,
      2.232, 2.234, 2.236, 2.238, 2.24, 2.242, 2.244, 2.246, 2.248, 2.25,
      2.2520000000000002, 2.254, 2.2560000000000002, 2.258, 2.2600000000000002,
      2.262, 2.2640000000000002, 2.266, 2.2680000000000002, 2.27,
      2.2720000000000002, 2.274, 2.2760000000000002, 2.278, 2.2800000000000002,
      2.282, 2.2840000000000003, 2.286, 2.2880000000000003, 2.29,
      2.2920000000000003, 2.294, 2.2960000000000003, 2.298, 2.3000000000000003,
      2.302, 2.3040000000000003, 2.306, 2.308, 2.31, 2.312, 2.314, 2.316, 2.318,
      2.32, 2.322, 2.324, 2.326, 2.328, 2.33, 2.332, 2.334, 2.336, 2.338, 2.34,
      2.342, 2.344, 2.346, 2.348, 2.35, 2.352, 2.354, 2.356, 2.358, 2.36, 2.362,
      2.364, 2.366, 2.368, 2.37, 2.372, 2.374, 2.376, 2.378, 2.38, 2.382, 2.384,
      2.386, 2.388, 2.39, 2.392, 2.394, 2.396, 2.398, 2.4, 2.402, 2.404, 2.406,
      2.408, 2.41, 2.412, 2.414, 2.416, 2.418, 2.42, 2.422, 2.424, 2.426, 2.428,
      2.43, 2.432, 2.434, 2.436, 2.438, 2.44, 2.442, 2.444, 2.446, 2.448, 2.45,
      2.452, 2.454, 2.456, 2.458, 2.46, 2.462, 2.464, 2.466, 2.468, 2.47, 2.472,
      2.474, 2.476, 2.478, 2.48, 2.482, 2.484, 2.486, 2.488, 2.49, 2.492, 2.494,
      2.496, 2.498, 2.5, 2.5020000000000002, 2.504, 2.5060000000000002, 2.508,
      2.5100000000000002, 2.512, 2.5140000000000002, 2.516, 2.5180000000000002,
      2.52, 2.5220000000000002, 2.524, 2.5260000000000002, 2.528,
      2.5300000000000002, 2.532, 2.5340000000000003, 2.536, 2.5380000000000003,
      2.54, 2.5420000000000003, 2.544, 2.5460000000000003, 2.548,
      2.5500000000000003, 2.552, 2.5540000000000003, 2.556, 2.5580000000000003,
      2.56, 2.562, 2.564, 2.566, 2.568, 2.57, 2.572, 2.574, 2.576, 2.578, 2.58,
      2.582, 2.584, 2.586, 2.588, 2.59, 2.592, 2.594, 2.596, 2.598, 2.6, 2.602,
      2.604, 2.606, 2.608, 2.61, 2.612, 2.614, 2.616, 2.618, 2.62, 2.622, 2.624,
      2.626, 2.628, 2.63, 2.632, 2.634, 2.636, 2.638, 2.64, 2.642, 2.644, 2.646,
      2.648, 2.65, 2.652, 2.654, 2.656, 2.658, 2.66, 2.662, 2.664, 2.666, 2.668,
      2.67, 2.672, 2.674, 2.676, 2.678, 2.68, 2.682, 2.684, 2.686, 2.688, 2.69,
      2.692, 2.694, 2.696, 2.698, 2.7, 2.702, 2.704, 2.706, 2.708, 2.71, 2.712,
      2.714, 2.716, 2.718, 2.72, 2.722, 2.724, 2.726, 2.728, 2.73, 2.732, 2.734,
      2.736, 2.738, 2.74, 2.742, 2.744, 2.746, 2.748, 2.75, 2.7520000000000002,
      2.754, 2.7560000000000002, 2.758, 2.7600000000000002, 2.762,
      2.7640000000000002, 2.766, 2.7680000000000002, 2.77, 2.7720000000000002,
      2.774, 2.7760000000000002, 2.778, 2.7800000000000002, 2.782,
      2.7840000000000003, 2.786, 2.7880000000000003, 2.79, 2.7920000000000003,
      2.794, 2.7960000000000003, 2.798, 2.8000000000000003, 2.802,
      2.8040000000000003, 2.806, 2.8080000000000003, 2.81, 2.8120000000000003,
      2.814, 2.816, 2.818, 2.82, 2.822, 2.824, 2.826, 2.828, 2.83, 2.832, 2.834,
      2.836, 2.838, 2.84, 2.842, 2.844, 2.846, 2.848, 2.85, 2.852, 2.854, 2.856,
      2.858, 2.86, 2.862, 2.864, 2.866, 2.868, 2.87, 2.872, 2.874, 2.876, 2.878,
      2.88, 2.882, 2.884, 2.886, 2.888, 2.89, 2.892, 2.894, 2.896, 2.898, 2.9,
      2.902, 2.904, 2.906, 2.908, 2.91, 2.912, 2.914, 2.916, 2.918, 2.92, 2.922,
      2.924, 2.926, 2.928, 2.93, 2.932, 2.934, 2.936, 2.938, 2.94, 2.942, 2.944,
      2.946, 2.948, 2.95, 2.952, 2.954, 2.956, 2.958, 2.96, 2.962, 2.964, 2.966,
      2.968, 2.97, 2.972, 2.974, 2.976, 2.978, 2.98, 2.982, 2.984, 2.986, 2.988,
      2.99, 2.992, 2.994, 2.996, 2.998, 3.0, 3.0020000000000002, 3.004,
      3.0060000000000002, 3.008, 3.0100000000000002, 3.012, 3.0140000000000002,
      3.016, 3.0180000000000002, 3.02, 3.0220000000000002, 3.024,
      3.0260000000000002, 3.028, 3.0300000000000002, 3.032, 3.0340000000000003,
      3.036, 3.0380000000000003, 3.04, 3.0420000000000003, 3.044,
      3.0460000000000003, 3.048, 3.0500000000000003, 3.052, 3.0540000000000003,
      3.056, 3.0580000000000003, 3.06, 3.0620000000000003, 3.064,
      3.0660000000000003, 3.068, 3.0700000000000003, 3.072, 3.074, 3.076, 3.078,
      3.08, 3.082, 3.084, 3.086, 3.088, 3.09, 3.092, 3.094, 3.096, 3.098, 3.1,
      3.102, 3.104, 3.106, 3.108, 3.11, 3.112, 3.114, 3.116, 3.118, 3.12, 3.122,
      3.124, 3.126, 3.128, 3.13, 3.132, 3.134, 3.136, 3.138, 3.14, 3.142, 3.144,
      3.146, 3.148, 3.15, 3.152, 3.154, 3.156, 3.158, 3.16, 3.162, 3.164, 3.166,
      3.168, 3.17, 3.172, 3.174, 3.176, 3.178, 3.18, 3.182, 3.184, 3.186, 3.188,
      3.19, 3.192, 3.194, 3.196, 3.198, 3.2, 3.202, 3.204, 3.206, 3.208, 3.21,
      3.212, 3.214, 3.216, 3.218, 3.22, 3.222, 3.224, 3.226, 3.228, 3.23, 3.232,
      3.234, 3.236, 3.238, 3.24, 3.242, 3.244, 3.246, 3.248, 3.25,
      3.2520000000000002, 3.254, 3.2560000000000002, 3.258, 3.2600000000000002,
      3.262, 3.2640000000000002, 3.266, 3.2680000000000002, 3.27,
      3.2720000000000002, 3.274, 3.2760000000000002, 3.278, 3.2800000000000002,
      3.282, 3.2840000000000003, 3.286, 3.2880000000000003, 3.29,
      3.2920000000000003, 3.294, 3.2960000000000003, 3.298, 3.3000000000000003,
      3.302, 3.3040000000000003, 3.306, 3.3080000000000003, 3.31,
      3.3120000000000003, 3.314, 3.3160000000000003, 3.318, 3.3200000000000003,
      3.322, 3.3240000000000003, 3.326, 3.3280000000000003, 3.33, 3.332, 3.334,
      3.336, 3.338, 3.34, 3.342, 3.344, 3.346, 3.348, 3.35, 3.352, 3.354, 3.356,
      3.358, 3.36, 3.362, 3.364, 3.366, 3.368, 3.37, 3.372, 3.374, 3.376, 3.378,
      3.38, 3.382, 3.384, 3.386, 3.388, 3.39, 3.392, 3.394, 3.396, 3.398, 3.4,
      3.402, 3.404, 3.406, 3.408, 3.41, 3.412, 3.414, 3.416, 3.418, 3.42, 3.422,
      3.424, 3.426, 3.428, 3.43, 3.432, 3.434, 3.436, 3.438, 3.44, 3.442, 3.444,
      3.446, 3.448, 3.45, 3.452, 3.454, 3.456, 3.458, 3.46, 3.462, 3.464, 3.466,
      3.468, 3.47, 3.472, 3.474, 3.476, 3.478, 3.48, 3.482, 3.484, 3.486, 3.488,
      3.49, 3.492, 3.494, 3.496, 3.498, 3.5, 3.5020000000000002, 3.504,
      3.5060000000000002, 3.508, 3.5100000000000002, 3.512, 3.5140000000000002,
      3.516, 3.5180000000000002, 3.52, 3.5220000000000002, 3.524,
      3.5260000000000002, 3.528, 3.5300000000000002, 3.532, 3.5340000000000003,
      3.536, 3.5380000000000003, 3.54, 3.5420000000000003, 3.544,
      3.5460000000000003, 3.548, 3.5500000000000003, 3.552, 3.5540000000000003,
      3.556, 3.5580000000000003, 3.56, 3.5620000000000003, 3.564,
      3.5660000000000003, 3.568, 3.5700000000000003, 3.572, 3.5740000000000003,
      3.576, 3.5780000000000003, 3.58, 3.5820000000000003, 3.584, 3.586, 3.588,
      3.59, 3.592, 3.594, 3.596, 3.598, 3.6, 3.602, 3.604, 3.606, 3.608, 3.61,
      3.612, 3.614, 3.616, 3.618, 3.62, 3.622, 3.624, 3.626, 3.628, 3.63, 3.632,
      3.634, 3.636, 3.638, 3.64, 3.642, 3.644, 3.646, 3.648, 3.65, 3.652, 3.654,
      3.656, 3.658, 3.66, 3.662, 3.664, 3.666, 3.668, 3.67, 3.672, 3.674, 3.676,
      3.678, 3.68, 3.682, 3.684, 3.686, 3.688, 3.69, 3.692, 3.694, 3.696, 3.698,
      3.7, 3.702, 3.704, 3.706, 3.708, 3.71, 3.712, 3.714, 3.716, 3.718, 3.72,
      3.722, 3.724, 3.726, 3.728, 3.73, 3.732, 3.734, 3.736, 3.738, 3.74, 3.742,
      3.744, 3.746, 3.748, 3.75, 3.7520000000000002, 3.754, 3.7560000000000002,
      3.758, 3.7600000000000002, 3.762, 3.7640000000000002, 3.766,
      3.7680000000000002, 3.77, 3.7720000000000002, 3.774, 3.7760000000000002,
      3.778, 3.7800000000000002, 3.782, 3.7840000000000003, 3.786,
      3.7880000000000003, 3.79, 3.7920000000000003, 3.794, 3.7960000000000003,
      3.798, 3.8000000000000003, 3.802, 3.8040000000000003, 3.806,
      3.8080000000000003, 3.81, 3.8120000000000003, 3.814, 3.8160000000000003,
      3.818, 3.8200000000000003, 3.822, 3.8240000000000003, 3.826,
      3.8280000000000003, 3.83, 3.8320000000000003, 3.834, 3.8360000000000003,
      3.838, 3.84, 3.842, 3.844, 3.846, 3.848, 3.85, 3.852, 3.854, 3.856, 3.858,
      3.86, 3.862, 3.864, 3.866, 3.868, 3.87, 3.872, 3.874, 3.876, 3.878, 3.88,
      3.882, 3.884, 3.886, 3.888, 3.89, 3.892, 3.894, 3.896, 3.898, 3.9, 3.902,
      3.904, 3.906, 3.908, 3.91, 3.912, 3.914, 3.916, 3.918, 3.92, 3.922, 3.924,
      3.926, 3.928, 3.93, 3.932, 3.934, 3.936, 3.938, 3.94, 3.942, 3.944, 3.946,
      3.948, 3.95, 3.952, 3.954, 3.956, 3.958, 3.96, 3.962, 3.964, 3.966, 3.968,
      3.97, 3.972, 3.974, 3.976, 3.978, 3.98, 3.982, 3.984, 3.986, 3.988, 3.99,
      3.992, 3.994, 3.996, 3.998, 4.0, 4.002, 4.0040000000000004, 4.006, 4.008,
      4.01, 4.0120000000000005, 4.014, 4.016, 4.018, 4.0200000000000005, 4.022,
      4.024, 4.026, 4.0280000000000005, 4.03, 4.032, 4.034, 4.0360000000000005,
      4.038, 4.04, 4.042, 4.0440000000000005, 4.046, 4.048, 4.05,
      4.0520000000000005, 4.054, 4.056, 4.058, 4.0600000000000005, 4.062, 4.064,
      4.066, 4.0680000000000005, 4.07, 4.072, 4.074, 4.0760000000000005, 4.078,
      4.08, 4.082, 4.0840000000000005, 4.086, 4.088, 4.09, 4.0920000000000005,
      4.094, 4.096, 4.098, 4.1, 4.102, 4.104, 4.106, 4.108, 4.11, 4.112, 4.114,
      4.116, 4.118, 4.12, 4.122, 4.124, 4.126, 4.128, 4.13, 4.132, 4.134, 4.136,
      4.138, 4.14, 4.142, 4.144, 4.146, 4.148, 4.15, 4.152, 4.154, 4.156, 4.158,
      4.16, 4.162, 4.164, 4.166, 4.168, 4.17, 4.172, 4.174, 4.176, 4.178, 4.18,
      4.182, 4.184, 4.186, 4.188, 4.19, 4.192, 4.194, 4.196, 4.198, 4.2, 4.202,
      4.204, 4.206, 4.208, 4.21, 4.212, 4.214, 4.216, 4.218, 4.22, 4.222, 4.224,
      4.226, 4.228, 4.23, 4.232, 4.234, 4.236, 4.238, 4.24, 4.242, 4.244, 4.246,
      4.248, 4.25, 4.252, 4.2540000000000004, 4.256, 4.258, 4.26,
      4.2620000000000005, 4.264, 4.266, 4.268, 4.2700000000000005, 4.272, 4.274,
      4.276, 4.2780000000000005, 4.28, 4.282, 4.284, 4.2860000000000005, 4.288,
      4.29, 4.292, 4.2940000000000005, 4.296, 4.298, 4.3, 4.3020000000000005,
      4.304, 4.306, 4.308, 4.3100000000000005, 4.312, 4.314, 4.316,
      4.3180000000000005, 4.32, 4.322, 4.324, 4.3260000000000005, 4.328, 4.33,
      4.332, 4.3340000000000005, 4.336, 4.338, 4.34, 4.3420000000000005, 4.344,
      4.346, 4.348, 4.3500000000000005, 4.352, 4.354, 4.356, 4.358, 4.36, 4.362,
      4.364, 4.366, 4.368, 4.37, 4.372, 4.374, 4.376, 4.378, 4.38, 4.382, 4.384,
      4.386, 4.388, 4.39, 4.392, 4.394, 4.396, 4.398, 4.4, 4.402, 4.404, 4.406,
      4.408, 4.41, 4.412, 4.414, 4.416, 4.418, 4.42, 4.422, 4.424, 4.426, 4.428,
      4.43, 4.432, 4.434, 4.436, 4.438, 4.44, 4.442, 4.444, 4.446, 4.448, 4.45,
      4.452, 4.454, 4.456, 4.458, 4.46, 4.462, 4.464, 4.466, 4.468, 4.47, 4.472,
      4.474, 4.476, 4.478, 4.48, 4.482, 4.484, 4.486, 4.488, 4.49, 4.492, 4.494,
      4.496, 4.498, 4.5, 4.502, 4.5040000000000004, 4.506, 4.508, 4.51,
      4.5120000000000005, 4.514, 4.516, 4.518, 4.5200000000000005, 4.522, 4.524,
      4.526, 4.5280000000000005, 4.53, 4.532, 4.534, 4.5360000000000005, 4.538,
      4.54, 4.542, 4.5440000000000005, 4.546, 4.548, 4.55, 4.5520000000000005,
      4.554, 4.556, 4.558, 4.5600000000000005, 4.562, 4.564, 4.566,
      4.5680000000000005, 4.57, 4.572, 4.574, 4.5760000000000005, 4.578, 4.58,
      4.582, 4.5840000000000005, 4.586, 4.588, 4.59, 4.5920000000000005, 4.594,
      4.596, 4.598, 4.6000000000000005, 4.602, 4.604, 4.606, 4.6080000000000005,
      4.61, 4.612, 4.614, 4.616, 4.618, 4.62, 4.622, 4.624, 4.626, 4.628, 4.63,
      4.632, 4.634, 4.636, 4.638, 4.64, 4.642, 4.644, 4.646, 4.648, 4.65, 4.652,
      4.654, 4.656, 4.658, 4.66, 4.662, 4.664, 4.666, 4.668, 4.67, 4.672, 4.674,
      4.676, 4.678, 4.68, 4.682, 4.684, 4.686, 4.688, 4.69, 4.692, 4.694, 4.696,
      4.698, 4.7, 4.702, 4.704, 4.706, 4.708, 4.71, 4.712, 4.714, 4.716, 4.718,
      4.72, 4.722, 4.724, 4.726, 4.728, 4.73, 4.732, 4.734, 4.736, 4.738, 4.74,
      4.742, 4.744, 4.746, 4.748, 4.75, 4.752, 4.7540000000000004, 4.756, 4.758,
      4.76, 4.7620000000000005, 4.764, 4.766, 4.768, 4.7700000000000005, 4.772,
      4.774, 4.776, 4.7780000000000005, 4.78, 4.782, 4.784, 4.7860000000000005,
      4.788, 4.79, 4.792, 4.7940000000000005, 4.796, 4.798, 4.8,
      4.8020000000000005, 4.804, 4.806, 4.808, 4.8100000000000005, 4.812, 4.814,
      4.816, 4.8180000000000005, 4.82, 4.822, 4.824, 4.8260000000000005, 4.828,
      4.83, 4.832, 4.8340000000000005, 4.836, 4.838, 4.84, 4.8420000000000005,
      4.844, 4.846, 4.848, 4.8500000000000005, 4.852, 4.854, 4.856,
      4.8580000000000005, 4.86, 4.862, 4.864, 4.866, 4.868, 4.87, 4.872, 4.874,
      4.876, 4.878, 4.88, 4.882, 4.884, 4.886, 4.888, 4.89, 4.892, 4.894, 4.896,
      4.898, 4.9, 4.902, 4.904, 4.906, 4.908, 4.91, 4.912, 4.914, 4.916, 4.918,
      4.92, 4.922, 4.924, 4.926, 4.928, 4.93, 4.932, 4.934, 4.936, 4.938, 4.94,
      4.942, 4.944, 4.946, 4.948, 4.95, 4.952, 4.954, 4.956, 4.958, 4.96, 4.962,
      4.964, 4.966, 4.968, 4.97, 4.972, 4.974, 4.976, 4.978, 4.98, 4.982, 4.984,
      4.986, 4.988, 4.99, 4.992, 4.994, 4.996, 4.998, 5.0, 5.002,
      5.0040000000000004, 5.006, 5.008, 5.01, 5.0120000000000005, 5.014, 5.016,
      5.018, 5.0200000000000005, 5.022, 5.024, 5.026, 5.0280000000000005, 5.03,
      5.032, 5.034, 5.0360000000000005, 5.038, 5.04, 5.042, 5.0440000000000005,
      5.046, 5.048, 5.05, 5.0520000000000005, 5.054, 5.056, 5.058,
      5.0600000000000005, 5.062, 5.064, 5.066, 5.0680000000000005, 5.07, 5.072,
      5.074, 5.0760000000000005, 5.078, 5.08, 5.082, 5.0840000000000005, 5.086,
      5.088, 5.09, 5.0920000000000005, 5.094, 5.096, 5.098, 5.1000000000000005,
      5.102, 5.104, 5.106, 5.1080000000000005, 5.11, 5.112, 5.114,
      5.1160000000000005, 5.118, 5.12, 5.122, 5.124, 5.126, 5.128, 5.13, 5.132,
      5.134, 5.136, 5.138, 5.14, 5.142, 5.144, 5.146, 5.148, 5.15, 5.152, 5.154,
      5.156, 5.158, 5.16, 5.162, 5.164, 5.166, 5.168, 5.17, 5.172, 5.174, 5.176,
      5.178, 5.18, 5.182, 5.184, 5.186, 5.188, 5.19, 5.192, 5.194, 5.196, 5.198,
      5.2, 5.202, 5.204, 5.206, 5.208, 5.21, 5.212, 5.214, 5.216, 5.218, 5.22,
      5.222, 5.224, 5.226, 5.228, 5.23, 5.232, 5.234, 5.236, 5.238, 5.24, 5.242,
      5.244, 5.246, 5.248, 5.25, 5.252, 5.2540000000000004, 5.256, 5.258, 5.26,
      5.2620000000000005, 5.264, 5.266, 5.268, 5.2700000000000005, 5.272, 5.274,
      5.276, 5.2780000000000005, 5.28, 5.282, 5.284, 5.2860000000000005, 5.288,
      5.29, 5.292, 5.2940000000000005, 5.296, 5.298, 5.3, 5.3020000000000005,
      5.304, 5.306, 5.308, 5.3100000000000005, 5.312, 5.314, 5.316,
      5.3180000000000005, 5.32, 5.322, 5.324, 5.3260000000000005, 5.328, 5.33,
      5.332, 5.3340000000000005, 5.336, 5.338, 5.34, 5.3420000000000005, 5.344,
      5.346, 5.348, 5.3500000000000005, 5.352, 5.354, 5.356, 5.3580000000000005,
      5.36, 5.362, 5.364, 5.3660000000000005, 5.368, 5.37, 5.372,
      5.3740000000000006, 5.376, 5.378, 5.38, 5.382, 5.384, 5.386, 5.388, 5.39,
      5.392, 5.394, 5.396, 5.398, 5.4, 5.402, 5.404, 5.406, 5.408, 5.41, 5.412,
      5.414, 5.416, 5.418, 5.42, 5.422, 5.424, 5.426, 5.428, 5.43, 5.432, 5.434,
      5.436, 5.438, 5.44, 5.442, 5.444, 5.446, 5.448, 5.45, 5.452, 5.454, 5.456,
      5.458, 5.46, 5.462, 5.464, 5.466, 5.468, 5.47, 5.472, 5.474, 5.476, 5.478,
      5.48, 5.482, 5.484, 5.486, 5.488, 5.49, 5.492, 5.494, 5.496, 5.498, 5.5,
      5.502, 5.5040000000000004, 5.506, 5.508, 5.51, 5.5120000000000005, 5.514,
      5.516, 5.518, 5.5200000000000005, 5.522, 5.524, 5.526, 5.5280000000000005,
      5.53, 5.532, 5.534, 5.5360000000000005, 5.538, 5.54, 5.542,
      5.5440000000000005, 5.546, 5.548, 5.55, 5.5520000000000005, 5.554, 5.556,
      5.558, 5.5600000000000005, 5.562, 5.564, 5.566, 5.5680000000000005, 5.57,
      5.572, 5.574, 5.5760000000000005, 5.578, 5.58, 5.582, 5.5840000000000005,
      5.586, 5.588, 5.59, 5.5920000000000005, 5.594, 5.596, 5.598,
      5.6000000000000005, 5.602, 5.604, 5.606, 5.6080000000000005, 5.61, 5.612,
      5.614, 5.6160000000000005, 5.618, 5.62, 5.622, 5.6240000000000006, 5.626,
      5.628, 5.63, 5.632, 5.634, 5.636, 5.638, 5.64, 5.642, 5.644, 5.646, 5.648,
      5.65, 5.652, 5.654, 5.656, 5.658, 5.66, 5.662, 5.664, 5.666, 5.668, 5.67,
      5.672, 5.674, 5.676, 5.678, 5.68, 5.682, 5.684, 5.686, 5.688, 5.69, 5.692,
      5.694, 5.696, 5.698, 5.7, 5.702, 5.704, 5.706, 5.708, 5.71, 5.712, 5.714,
      5.716, 5.718, 5.72, 5.722, 5.724, 5.726, 5.728, 5.73, 5.732, 5.734, 5.736,
      5.738, 5.74, 5.742, 5.744, 5.746, 5.748, 5.75, 5.752, 5.7540000000000004,
      5.756, 5.758, 5.76, 5.7620000000000005, 5.764, 5.766, 5.768,
      5.7700000000000005, 5.772, 5.774, 5.776, 5.7780000000000005, 5.78, 5.782,
      5.784, 5.7860000000000005, 5.788, 5.79, 5.792, 5.7940000000000005, 5.796,
      5.798, 5.8, 5.8020000000000005, 5.804, 5.806, 5.808, 5.8100000000000005,
      5.812, 5.814, 5.816, 5.8180000000000005, 5.82, 5.822, 5.824,
      5.8260000000000005, 5.828, 5.83, 5.832, 5.8340000000000005, 5.836, 5.838,
      5.84, 5.8420000000000005, 5.844, 5.846, 5.848, 5.8500000000000005, 5.852,
      5.854, 5.856, 5.8580000000000005, 5.86, 5.862, 5.864, 5.8660000000000005,
      5.868, 5.87, 5.872, 5.8740000000000006, 5.876, 5.878, 5.88,
      5.8820000000000006, 5.884, 5.886, 5.888, 5.89, 5.892, 5.894, 5.896, 5.898,
      5.9, 5.902, 5.904, 5.906, 5.908, 5.91, 5.912, 5.914, 5.916, 5.918, 5.92,
      5.922, 5.924, 5.926, 5.928, 5.93, 5.932, 5.934, 5.936, 5.938, 5.94, 5.942,
      5.944, 5.946, 5.948, 5.95, 5.952, 5.954, 5.956, 5.958, 5.96, 5.962, 5.964,
      5.966, 5.968, 5.97, 5.972, 5.974, 5.976, 5.978, 5.98, 5.982, 5.984, 5.986,
      5.988, 5.99, 5.992, 5.994, 5.996, 5.998, 6.0, 6.002, 6.0040000000000004,
      6.006, 6.008, 6.01, 6.0120000000000005, 6.014, 6.016, 6.018,
      6.0200000000000005, 6.022, 6.024, 6.026, 6.0280000000000005, 6.03, 6.032,
      6.034, 6.0360000000000005, 6.038, 6.04, 6.042, 6.0440000000000005, 6.046,
      6.048, 6.05, 6.0520000000000005, 6.054, 6.056, 6.058, 6.0600000000000005,
      6.062, 6.064, 6.066, 6.0680000000000005, 6.07, 6.072, 6.074,
      6.0760000000000005, 6.078, 6.08, 6.082, 6.0840000000000005, 6.086, 6.088,
      6.09, 6.0920000000000005, 6.094, 6.096, 6.098, 6.1000000000000005, 6.102,
      6.104, 6.106, 6.1080000000000005, 6.11, 6.112, 6.114, 6.1160000000000005,
      6.118, 6.12, 6.122, 6.1240000000000006, 6.126, 6.128, 6.13,
      6.1320000000000006, 6.134, 6.136, 6.138, 6.1400000000000006, 6.142, 6.144,
      6.146, 6.148, 6.15, 6.152, 6.154, 6.156, 6.158, 6.16, 6.162, 6.164, 6.166,
      6.168, 6.17, 6.172, 6.174, 6.176, 6.178, 6.18, 6.182, 6.184, 6.186, 6.188,
      6.19, 6.192, 6.194, 6.196, 6.198, 6.2, 6.202, 6.204, 6.206, 6.208, 6.21,
      6.212, 6.214, 6.216, 6.218, 6.22, 6.222, 6.224, 6.226, 6.228, 6.23, 6.232,
      6.234, 6.236, 6.238, 6.24, 6.242, 6.244, 6.246, 6.248, 6.25, 6.252,
      6.2540000000000004, 6.256, 6.258, 6.26, 6.2620000000000005, 6.264, 6.266,
      6.268, 6.2700000000000005, 6.272, 6.274, 6.276, 6.2780000000000005, 6.28,
      6.282, 6.284, 6.2860000000000005, 6.288, 6.29, 6.292, 6.2940000000000005,
      6.296, 6.298, 6.3, 6.3020000000000005, 6.304, 6.306, 6.308,
      6.3100000000000005, 6.312, 6.314, 6.316, 6.3180000000000005, 6.32, 6.322,
      6.324, 6.3260000000000005, 6.328, 6.33, 6.332, 6.3340000000000005, 6.336,
      6.338, 6.34, 6.3420000000000005, 6.344, 6.346, 6.348, 6.3500000000000005,
      6.352, 6.354, 6.356, 6.3580000000000005, 6.36, 6.362, 6.364,
      6.3660000000000005, 6.368, 6.37, 6.372, 6.3740000000000006, 6.376, 6.378,
      6.38, 6.3820000000000006, 6.384, 6.386, 6.388, 6.3900000000000006, 6.392,
      6.394, 6.396, 6.3980000000000006, 6.4, 6.402, 6.404, 6.406, 6.408, 6.41,
      6.412, 6.414, 6.416, 6.418, 6.42, 6.422, 6.424, 6.426, 6.428, 6.43, 6.432,
      6.434, 6.436, 6.438, 6.44, 6.442, 6.444, 6.446, 6.448, 6.45, 6.452, 6.454,
      6.456, 6.458, 6.46, 6.462, 6.464, 6.466, 6.468, 6.47, 6.472, 6.474, 6.476,
      6.478, 6.48, 6.482, 6.484, 6.486, 6.488, 6.49, 6.492, 6.494, 6.496, 6.498,
      6.5, 6.502, 6.5040000000000004, 6.506, 6.508, 6.51, 6.5120000000000005,
      6.514, 6.516, 6.518, 6.5200000000000005, 6.522, 6.524, 6.526,
      6.5280000000000005, 6.53, 6.532, 6.534, 6.5360000000000005, 6.538, 6.54,
      6.542, 6.5440000000000005, 6.546, 6.548, 6.55, 6.5520000000000005, 6.554,
      6.556, 6.558, 6.5600000000000005, 6.562, 6.564, 6.566, 6.5680000000000005,
      6.57, 6.572, 6.574, 6.5760000000000005, 6.578, 6.58, 6.582,
      6.5840000000000005, 6.586, 6.588, 6.59, 6.5920000000000005, 6.594, 6.596,
      6.598, 6.6000000000000005, 6.602, 6.604, 6.606, 6.6080000000000005, 6.61,
      6.612, 6.614, 6.6160000000000005, 6.618, 6.62, 6.622, 6.6240000000000006,
      6.626, 6.628, 6.63, 6.6320000000000006, 6.634, 6.636, 6.638,
      6.6400000000000006, 6.642, 6.644, 6.646, 6.6480000000000006, 6.65, 6.652,
      6.654, 6.6560000000000006, 6.658, 6.66, 6.662, 6.664, 6.666, 6.668, 6.67,
      6.672, 6.674, 6.676, 6.678, 6.68, 6.682, 6.684, 6.686, 6.688, 6.69, 6.692,
      6.694, 6.696, 6.698, 6.7, 6.702, 6.704, 6.706, 6.708, 6.71, 6.712, 6.714,
      6.716, 6.718, 6.72, 6.722, 6.724, 6.726, 6.728, 6.73, 6.732, 6.734, 6.736,
      6.738, 6.74, 6.742, 6.744, 6.746, 6.748, 6.75, 6.752, 6.7540000000000004,
      6.756, 6.758, 6.76, 6.7620000000000005, 6.764, 6.766, 6.768,
      6.7700000000000005, 6.772, 6.774, 6.776, 6.7780000000000005, 6.78, 6.782,
      6.784, 6.7860000000000005, 6.788, 6.79, 6.792, 6.7940000000000005, 6.796,
      6.798, 6.8, 6.8020000000000005, 6.804, 6.806, 6.808, 6.8100000000000005,
      6.812, 6.814, 6.816, 6.8180000000000005, 6.82, 6.822, 6.824,
      6.8260000000000005, 6.828, 6.83, 6.832, 6.8340000000000005, 6.836, 6.838,
      6.84, 6.8420000000000005, 6.844, 6.846, 6.848, 6.8500000000000005, 6.852,
      6.854, 6.856, 6.8580000000000005, 6.86, 6.862, 6.864, 6.8660000000000005,
      6.868, 6.87, 6.872, 6.8740000000000006, 6.876, 6.878, 6.88,
      6.8820000000000006, 6.884, 6.886, 6.888, 6.8900000000000006, 6.892, 6.894,
      6.896, 6.8980000000000006, 6.9, 6.902, 6.904, 6.9060000000000006, 6.908,
      6.91, 6.912, 6.914, 6.916, 6.918, 6.92, 6.922, 6.924, 6.926, 6.928, 6.93,
      6.932, 6.934, 6.936, 6.938, 6.94, 6.942, 6.944, 6.946, 6.948, 6.95, 6.952,
      6.954, 6.956, 6.958, 6.96, 6.962, 6.964, 6.966, 6.968, 6.97, 6.972, 6.974,
      6.976, 6.978, 6.98, 6.982, 6.984, 6.986, 6.988, 6.99, 6.992, 6.994, 6.996,
      6.998, 7.0, 7.002, 7.0040000000000004, 7.006, 7.008, 7.01,
      7.0120000000000005, 7.014, 7.016, 7.018, 7.0200000000000005, 7.022, 7.024,
      7.026, 7.0280000000000005, 7.03, 7.032, 7.034, 7.0360000000000005, 7.038,
      7.04, 7.042, 7.0440000000000005, 7.046, 7.048, 7.05, 7.0520000000000005,
      7.054, 7.056, 7.058, 7.0600000000000005, 7.062, 7.064, 7.066,
      7.0680000000000005, 7.07, 7.072, 7.074, 7.0760000000000005, 7.078, 7.08,
      7.082, 7.0840000000000005, 7.086, 7.088, 7.09, 7.0920000000000005, 7.094,
      7.096, 7.098, 7.1000000000000005, 7.102, 7.104, 7.106, 7.1080000000000005,
      7.11, 7.112, 7.114, 7.1160000000000005, 7.118, 7.12, 7.122,
      7.1240000000000006, 7.126, 7.128, 7.13, 7.1320000000000006, 7.134, 7.136,
      7.138, 7.1400000000000006, 7.142, 7.144, 7.146, 7.1480000000000006, 7.15,
      7.152, 7.154, 7.1560000000000006, 7.158, 7.16, 7.162, 7.1640000000000006,
      7.166, 7.168, 7.17, 7.172, 7.174, 7.176, 7.178, 7.18, 7.182, 7.184, 7.186,
      7.188, 7.19, 7.192, 7.194, 7.196, 7.198, 7.2, 7.202, 7.204, 7.206, 7.208,
      7.21, 7.212, 7.214, 7.216, 7.218, 7.22, 7.222, 7.224, 7.226, 7.228, 7.23,
      7.232, 7.234, 7.236, 7.238, 7.24, 7.242, 7.244, 7.246, 7.248, 7.25, 7.252,
      7.2540000000000004, 7.256, 7.258, 7.26, 7.2620000000000005, 7.264, 7.266,
      7.268, 7.2700000000000005, 7.272, 7.274, 7.276, 7.2780000000000005, 7.28,
      7.282, 7.284, 7.2860000000000005, 7.288, 7.29, 7.292, 7.2940000000000005,
      7.296, 7.298, 7.3, 7.3020000000000005, 7.304, 7.306, 7.308,
      7.3100000000000005, 7.312, 7.314, 7.316, 7.3180000000000005, 7.32, 7.322,
      7.324, 7.3260000000000005, 7.328, 7.33, 7.332, 7.3340000000000005, 7.336,
      7.338, 7.34, 7.3420000000000005, 7.344, 7.346, 7.348, 7.3500000000000005,
      7.352, 7.354, 7.356, 7.3580000000000005, 7.36, 7.362, 7.364,
      7.3660000000000005, 7.368, 7.37, 7.372, 7.3740000000000006, 7.376, 7.378,
      7.38, 7.3820000000000006, 7.384, 7.386, 7.388, 7.3900000000000006, 7.392,
      7.394, 7.396, 7.3980000000000006, 7.4, 7.402, 7.404, 7.4060000000000006,
      7.408, 7.41, 7.412, 7.4140000000000006, 7.416, 7.418, 7.42,
      7.4220000000000006, 7.424, 7.426, 7.428, 7.43, 7.432, 7.434, 7.436, 7.438,
      7.44, 7.442, 7.444, 7.446, 7.448, 7.45, 7.452, 7.454, 7.456, 7.458, 7.46,
      7.462, 7.464, 7.466, 7.468, 7.47, 7.472, 7.474, 7.476, 7.478, 7.48, 7.482,
      7.484, 7.486, 7.488, 7.49, 7.492, 7.494, 7.496, 7.498, 7.5, 7.502,
      7.5040000000000004, 7.506, 7.508, 7.51, 7.5120000000000005, 7.514, 7.516,
      7.518, 7.5200000000000005, 7.522, 7.524, 7.526, 7.5280000000000005, 7.53,
      7.532, 7.534, 7.5360000000000005, 7.538, 7.54, 7.542, 7.5440000000000005,
      7.546, 7.548, 7.55, 7.5520000000000005, 7.554, 7.556, 7.558,
      7.5600000000000005, 7.562, 7.564, 7.566, 7.5680000000000005, 7.57, 7.572,
      7.574, 7.5760000000000005, 7.578, 7.58, 7.582, 7.5840000000000005, 7.586,
      7.588, 7.59, 7.5920000000000005, 7.594, 7.596, 7.598, 7.6000000000000005,
      7.602, 7.604, 7.606, 7.6080000000000005, 7.61, 7.612, 7.614,
      7.6160000000000005, 7.618, 7.62, 7.622, 7.6240000000000006, 7.626, 7.628,
      7.63, 7.6320000000000006, 7.634, 7.636, 7.638, 7.6400000000000006, 7.642,
      7.644, 7.646, 7.6480000000000006, 7.65, 7.652, 7.654, 7.6560000000000006,
      7.658, 7.66, 7.662, 7.6640000000000006, 7.666, 7.668, 7.67,
      7.6720000000000006, 7.674, 7.676, 7.678, 7.68, 7.682, 7.684, 7.686, 7.688,
      7.69, 7.692, 7.694, 7.696, 7.698, 7.7, 7.702, 7.704, 7.706, 7.708, 7.71,
      7.712, 7.714, 7.716, 7.718, 7.72, 7.722, 7.724, 7.726, 7.728, 7.73, 7.732,
      7.734, 7.736, 7.738, 7.74, 7.742, 7.744, 7.746, 7.748, 7.75, 7.752,
      7.7540000000000004, 7.756, 7.758, 7.76, 7.7620000000000005, 7.764, 7.766,
      7.768, 7.7700000000000005, 7.772, 7.774, 7.776, 7.7780000000000005, 7.78,
      7.782, 7.784, 7.7860000000000005, 7.788, 7.79, 7.792, 7.7940000000000005,
      7.796, 7.798, 7.8, 7.8020000000000005, 7.804, 7.806, 7.808,
      7.8100000000000005, 7.812, 7.814, 7.816, 7.8180000000000005, 7.82, 7.822,
      7.824, 7.8260000000000005, 7.828, 7.83, 7.832, 7.8340000000000005, 7.836,
      7.838, 7.84, 7.8420000000000005, 7.844, 7.846, 7.848, 7.8500000000000005,
      7.852, 7.854, 7.856, 7.8580000000000005, 7.86, 7.862, 7.864,
      7.8660000000000005, 7.868, 7.87, 7.872, 7.8740000000000006, 7.876, 7.878,
      7.88, 7.8820000000000006, 7.884, 7.886, 7.888, 7.8900000000000006, 7.892,
      7.894, 7.896, 7.8980000000000006, 7.9, 7.902, 7.904, 7.9060000000000006,
      7.908, 7.91, 7.912, 7.9140000000000006, 7.916, 7.918, 7.92,
      7.9220000000000006, 7.924, 7.926, 7.928, 7.9300000000000006, 7.932, 7.934,
      7.936, 7.938, 7.94, 7.942, 7.944, 7.946, 7.948, 7.95, 7.952, 7.954, 7.956,
      7.958, 7.96, 7.962, 7.964, 7.966, 7.968, 7.97, 7.972, 7.974, 7.976, 7.978,
      7.98, 7.982, 7.984, 7.986, 7.988, 7.99, 7.992, 7.994, 7.996, 7.998, 8.0,
      8.002, 8.004, 8.006, 8.0080000000000009, 8.01, 8.012, 8.014, 8.016, 8.018,
      8.02, 8.022, 8.0240000000000009, 8.026, 8.028, 8.03, 8.032, 8.034, 8.036,
      8.038, 8.0400000000000009, 8.042, 8.044, 8.046, 8.048, 8.05, 8.052, 8.054,
      8.0560000000000009, 8.058, 8.06, 8.062, 8.064, 8.066, 8.068, 8.07,
      8.072000000000001, 8.074, 8.076, 8.078, 8.08, 8.082, 8.084, 8.086,
      8.088000000000001, 8.09, 8.092, 8.094, 8.096, 8.098, 8.1, 8.102,
      8.104000000000001, 8.106, 8.108, 8.11, 8.112, 8.114, 8.116, 8.118,
      8.120000000000001, 8.122, 8.124, 8.126, 8.128, 8.13, 8.132, 8.134,
      8.136000000000001, 8.138, 8.14, 8.142, 8.144, 8.146, 8.148, 8.15,
      8.152000000000001, 8.154, 8.156, 8.158, 8.16, 8.162, 8.164, 8.166,
      8.168000000000001, 8.17, 8.172, 8.174, 8.176, 8.178, 8.18, 8.182,
      8.1840000000000011, 8.186, 8.188, 8.19, 8.192, 8.194, 8.196, 8.198, 8.2,
      8.202, 8.204, 8.206, 8.208, 8.21, 8.212, 8.214, 8.216, 8.218, 8.22, 8.222,
      8.224, 8.226, 8.228, 8.23, 8.232, 8.234, 8.236, 8.238, 8.24, 8.242, 8.244,
      8.246, 8.248, 8.25, 8.252, 8.254, 8.256, 8.2580000000000009, 8.26, 8.262,
      8.264, 8.266, 8.268, 8.27, 8.272, 8.2740000000000009, 8.276, 8.278, 8.28,
      8.282, 8.284, 8.286, 8.288, 8.2900000000000009, 8.292, 8.294, 8.296, 8.298,
      8.3, 8.302, 8.304, 8.3060000000000009, 8.308, 8.31, 8.312, 8.314, 8.316,
      8.318, 8.32, 8.322000000000001, 8.324, 8.326, 8.328, 8.33, 8.332, 8.334,
      8.336, 8.338000000000001, 8.34, 8.342, 8.344, 8.346, 8.348, 8.35, 8.352,
      8.354000000000001, 8.356, 8.358, 8.36, 8.362, 8.364, 8.366, 8.368,
      8.370000000000001, 8.372, 8.374, 8.376, 8.378, 8.38, 8.382, 8.384,
      8.386000000000001, 8.388, 8.39, 8.392, 8.394, 8.396, 8.398, 8.4,
      8.402000000000001, 8.404, 8.406, 8.408, 8.41, 8.412, 8.414, 8.416,
      8.418000000000001, 8.42, 8.422, 8.424, 8.426, 8.428, 8.43, 8.432,
      8.4340000000000011, 8.436, 8.438, 8.44, 8.442, 8.444, 8.446, 8.448, 8.45,
      8.452, 8.454, 8.456, 8.458, 8.46, 8.462, 8.464, 8.466, 8.468, 8.47, 8.472,
      8.474, 8.476, 8.478, 8.48, 8.482, 8.484, 8.486, 8.488, 8.49, 8.492, 8.494,
      8.496, 8.498, 8.5, 8.502, 8.504, 8.506, 8.5080000000000009, 8.51, 8.512,
      8.514, 8.516, 8.518, 8.52, 8.522, 8.5240000000000009, 8.526, 8.528, 8.53,
      8.532, 8.534, 8.536, 8.538, 8.5400000000000009, 8.542, 8.544, 8.546, 8.548,
      8.55, 8.552, 8.554, 8.5560000000000009, 8.558, 8.56, 8.562, 8.564, 8.566,
      8.568, 8.57, 8.572000000000001, 8.574, 8.576, 8.578, 8.58, 8.582, 8.584,
      8.586, 8.588000000000001, 8.59, 8.592, 8.594, 8.596, 8.598, 8.6, 8.602,
      8.604000000000001, 8.606, 8.608, 8.61, 8.612, 8.614, 8.616, 8.618,
      8.620000000000001, 8.622, 8.624, 8.626, 8.628, 8.63, 8.632, 8.634,
      8.636000000000001, 8.638, 8.64, 8.642, 8.644, 8.646, 8.648, 8.65,
      8.652000000000001, 8.654, 8.656, 8.658, 8.66, 8.662, 8.664, 8.666,
      8.668000000000001, 8.67, 8.672, 8.674, 8.676, 8.678, 8.68, 8.682,
      8.6840000000000011, 8.686, 8.688, 8.69, 8.692, 8.694, 8.696, 8.698,
      8.7000000000000011, 8.702, 8.704, 8.706, 8.708, 8.71, 8.712, 8.714, 8.716,
      8.718, 8.72, 8.722, 8.724, 8.726, 8.728, 8.73, 8.732, 8.734, 8.736, 8.738,
      8.74, 8.742, 8.744, 8.746, 8.748, 8.75, 8.752, 8.754, 8.756,
      8.7580000000000009, 8.76, 8.762, 8.764, 8.766, 8.768, 8.77, 8.772,
      8.7740000000000009, 8.776, 8.778, 8.78, 8.782, 8.784, 8.786, 8.788,
      8.7900000000000009, 8.792, 8.794, 8.796, 8.798, 8.8, 8.802, 8.804,
      8.8060000000000009, 8.808, 8.81, 8.812, 8.814, 8.816, 8.818, 8.82,
      8.822000000000001, 8.824, 8.826, 8.828, 8.83, 8.832, 8.834, 8.836,
      8.838000000000001, 8.84, 8.842, 8.844, 8.846, 8.848, 8.85, 8.852,
      8.854000000000001, 8.856, 8.858, 8.86, 8.862, 8.864, 8.866, 8.868,
      8.870000000000001, 8.872, 8.874, 8.876, 8.878, 8.88, 8.882, 8.884,
      8.886000000000001, 8.888, 8.89, 8.892, 8.894, 8.896, 8.898, 8.9,
      8.902000000000001, 8.904, 8.906, 8.908, 8.91, 8.912, 8.914, 8.916,
      8.918000000000001, 8.92, 8.922, 8.924, 8.926, 8.928, 8.93, 8.932,
      8.9340000000000011, 8.936, 8.938, 8.94, 8.942, 8.944, 8.946, 8.948,
      8.9500000000000011, 8.952, 8.954, 8.956, 8.958, 8.96, 8.962, 8.964, 8.966,
      8.968, 8.97, 8.972, 8.974, 8.976, 8.978, 8.98, 8.982, 8.984, 8.986, 8.988,
      8.99, 8.992, 8.994, 8.996, 8.998, 9.0, 9.002, 9.004, 9.006,
      9.0080000000000009, 9.01, 9.012, 9.014, 9.016, 9.018, 9.02, 9.022,
      9.0240000000000009, 9.026, 9.028, 9.03, 9.032, 9.034, 9.036, 9.038,
      9.0400000000000009, 9.042, 9.044, 9.046, 9.048, 9.05, 9.052, 9.054,
      9.0560000000000009, 9.058, 9.06, 9.062, 9.064, 9.066, 9.068, 9.07,
      9.072000000000001, 9.074, 9.076, 9.078, 9.08, 9.082, 9.084, 9.086,
      9.088000000000001, 9.09, 9.092, 9.094, 9.096, 9.098, 9.1, 9.102,
      9.104000000000001, 9.106, 9.108, 9.11, 9.112, 9.114, 9.116, 9.118,
      9.120000000000001, 9.122, 9.124, 9.126, 9.128, 9.13, 9.132, 9.134,
      9.136000000000001, 9.138, 9.14, 9.142, 9.144, 9.146, 9.148, 9.15,
      9.152000000000001, 9.154, 9.156, 9.158, 9.16, 9.162, 9.164, 9.166,
      9.168000000000001, 9.17, 9.172, 9.174, 9.176, 9.178, 9.18, 9.182,
      9.1840000000000011, 9.186, 9.188, 9.19, 9.192, 9.194, 9.196, 9.198,
      9.2000000000000011, 9.202, 9.204, 9.206, 9.208, 9.21, 9.212, 9.214,
      9.2160000000000011, 9.218, 9.22, 9.222, 9.224, 9.226, 9.228, 9.23, 9.232,
      9.234, 9.236, 9.238, 9.24, 9.242, 9.244, 9.246, 9.248, 9.25, 9.252, 9.254,
      9.256, 9.2580000000000009, 9.26, 9.262, 9.264, 9.266, 9.268, 9.27, 9.272,
      9.2740000000000009, 9.276, 9.278, 9.28, 9.282, 9.284, 9.286, 9.288,
      9.2900000000000009, 9.292, 9.294, 9.296, 9.298, 9.3, 9.302, 9.304,
      9.3060000000000009, 9.308, 9.31, 9.312, 9.314, 9.316, 9.318, 9.32,
      9.322000000000001, 9.324, 9.326, 9.328, 9.33, 9.332, 9.334, 9.336,
      9.338000000000001, 9.34, 9.342, 9.344, 9.346, 9.348, 9.35, 9.352,
      9.354000000000001, 9.356, 9.358, 9.36, 9.362, 9.364, 9.366, 9.368,
      9.370000000000001, 9.372, 9.374, 9.376, 9.378, 9.38, 9.382, 9.384,
      9.386000000000001, 9.388, 9.39, 9.392, 9.394, 9.396, 9.398, 9.4,
      9.402000000000001, 9.404, 9.406, 9.408, 9.41, 9.412, 9.414, 9.416,
      9.418000000000001, 9.42, 9.422, 9.424, 9.426, 9.428, 9.43, 9.432,
      9.4340000000000011, 9.436, 9.438, 9.44, 9.442, 9.444, 9.446, 9.448,
      9.4500000000000011, 9.452, 9.454, 9.456, 9.458, 9.46, 9.462, 9.464,
      9.4660000000000011, 9.468, 9.47, 9.472, 9.474, 9.476, 9.478, 9.48, 9.482,
      9.484, 9.486, 9.488, 9.49, 9.492, 9.494, 9.496, 9.498, 9.5, 9.502, 9.504,
      9.506, 9.5080000000000009, 9.51, 9.512, 9.514, 9.516, 9.518, 9.52, 9.522,
      9.5240000000000009, 9.526, 9.528, 9.53, 9.532, 9.534, 9.536, 9.538,
      9.5400000000000009, 9.542, 9.544, 9.546, 9.548, 9.55, 9.552, 9.554,
      9.5560000000000009, 9.558, 9.56, 9.562, 9.564, 9.566, 9.568, 9.57,
      9.572000000000001, 9.574, 9.576, 9.578, 9.58, 9.582, 9.584, 9.586,
      9.588000000000001, 9.59, 9.592, 9.594, 9.596, 9.598, 9.6, 9.602,
      9.604000000000001, 9.606, 9.608, 9.61, 9.612, 9.614, 9.616, 9.618,
      9.620000000000001, 9.622, 9.624, 9.626, 9.628, 9.63, 9.632, 9.634,
      9.636000000000001, 9.638, 9.64, 9.642, 9.644, 9.646, 9.648, 9.65,
      9.652000000000001, 9.654, 9.656, 9.658, 9.66, 9.662, 9.664, 9.666,
      9.668000000000001, 9.67, 9.672, 9.674, 9.676, 9.678, 9.68, 9.682,
      9.6840000000000011, 9.686, 9.688, 9.69, 9.692, 9.694, 9.696, 9.698,
      9.7000000000000011, 9.702, 9.704, 9.706, 9.708, 9.71, 9.712, 9.714,
      9.7160000000000011, 9.718, 9.72, 9.722, 9.724, 9.726, 9.728, 9.73, 9.732,
      9.734, 9.736, 9.738, 9.74, 9.742, 9.744, 9.746, 9.748, 9.75, 9.752, 9.754,
      9.756, 9.7580000000000009, 9.76, 9.762, 9.764, 9.766, 9.768, 9.77, 9.772,
      9.7740000000000009, 9.776, 9.778, 9.78, 9.782, 9.784, 9.786, 9.788,
      9.7900000000000009, 9.792, 9.794, 9.796, 9.798, 9.8, 9.802, 9.804,
      9.8060000000000009, 9.808, 9.81, 9.812, 9.814, 9.816, 9.818, 9.82,
      9.822000000000001, 9.824, 9.826, 9.828, 9.83, 9.832, 9.834, 9.836,
      9.838000000000001, 9.84, 9.842, 9.844, 9.846, 9.848, 9.85, 9.852,
      9.854000000000001, 9.856, 9.858, 9.86, 9.862, 9.864, 9.866, 9.868,
      9.870000000000001, 9.872, 9.874, 9.876, 9.878, 9.88, 9.882, 9.884,
      9.886000000000001, 9.888, 9.89, 9.892, 9.894, 9.896, 9.898, 9.9,
      9.902000000000001, 9.904, 9.906, 9.908, 9.91, 9.912, 9.914, 9.916,
      9.918000000000001, 9.92, 9.922, 9.924, 9.926, 9.928, 9.93, 9.932,
      9.9340000000000011, 9.936, 9.938, 9.94, 9.942, 9.944, 9.946, 9.948,
      9.9500000000000011, 9.952, 9.954, 9.956, 9.958, 9.96, 9.962, 9.964,
      9.9660000000000011, 9.968, 9.97, 9.972, 9.974, 9.976, 9.978, 9.98,
      9.9820000000000011, 9.984, 9.986, 9.988, 9.99, 9.992, 9.994, 9.996, 9.998,
      10.0, 10.002, 10.004, 10.006, 10.008000000000001, 10.01, 10.012, 10.014,
      10.016, 10.018, 10.02, 10.022, 10.024000000000001, 10.026, 10.028, 10.03,
      10.032, 10.034, 10.036, 10.038, 10.040000000000001, 10.042, 10.044, 10.046,
      10.048, 10.05, 10.052, 10.054, 10.056000000000001, 10.058, 10.06, 10.062,
      10.064, 10.066, 10.068, 10.07, 10.072000000000001, 10.074, 10.076, 10.078,
      10.08, 10.082, 10.084, 10.086, 10.088000000000001, 10.09, 10.092, 10.094,
      10.096, 10.098, 10.1, 10.102, 10.104000000000001, 10.106, 10.108, 10.11,
      10.112, 10.114, 10.116, 10.118, 10.120000000000001, 10.122, 10.124, 10.126,
      10.128, 10.13, 10.132, 10.134, 10.136000000000001, 10.138, 10.14, 10.142,
      10.144, 10.146, 10.148, 10.15, 10.152000000000001, 10.154, 10.156, 10.158,
      10.16, 10.162, 10.164, 10.166, 10.168000000000001, 10.17, 10.172, 10.174,
      10.176, 10.178, 10.18, 10.182, 10.184000000000001, 10.186, 10.188, 10.19,
      10.192, 10.194, 10.196, 10.198, 10.200000000000001, 10.202, 10.204, 10.206,
      10.208, 10.21, 10.212, 10.214, 10.216000000000001, 10.218, 10.22, 10.222,
      10.224, 10.226, 10.228, 10.23, 10.232000000000001, 10.234, 10.236, 10.238,
      10.24, 10.242, 10.244, 10.246, 10.248, 10.25, 10.252, 10.254, 10.256,
      10.258000000000001, 10.26, 10.262, 10.264, 10.266, 10.268, 10.27, 10.272,
      10.274000000000001, 10.276, 10.278, 10.28, 10.282, 10.284, 10.286, 10.288,
      10.290000000000001, 10.292, 10.294, 10.296, 10.298, 10.3, 10.302, 10.304,
      10.306000000000001, 10.308, 10.31, 10.312, 10.314, 10.316, 10.318, 10.32,
      10.322000000000001, 10.324, 10.326, 10.328, 10.33, 10.332, 10.334, 10.336,
      10.338000000000001, 10.34, 10.342, 10.344, 10.346, 10.348, 10.35, 10.352,
      10.354000000000001, 10.356, 10.358, 10.36, 10.362, 10.364, 10.366, 10.368,
      10.370000000000001, 10.372, 10.374, 10.376, 10.378, 10.38, 10.382, 10.384,
      10.386000000000001, 10.388, 10.39, 10.392, 10.394, 10.396, 10.398, 10.4,
      10.402000000000001, 10.404, 10.406, 10.408, 10.41, 10.412, 10.414, 10.416,
      10.418000000000001, 10.42, 10.422, 10.424, 10.426, 10.428, 10.43, 10.432,
      10.434000000000001, 10.436, 10.438, 10.44, 10.442, 10.444, 10.446, 10.448,
      10.450000000000001, 10.452, 10.454, 10.456, 10.458, 10.46, 10.462, 10.464,
      10.466000000000001, 10.468, 10.47, 10.472, 10.474, 10.476, 10.478, 10.48,
      10.482000000000001, 10.484, 10.486, 10.488, 10.49, 10.492, 10.494, 10.496,
      10.498, 10.5, 10.502, 10.504, 10.506, 10.508000000000001, 10.51, 10.512,
      10.514, 10.516, 10.518, 10.52, 10.522, 10.524000000000001, 10.526, 10.528,
      10.53, 10.532, 10.534, 10.536, 10.538, 10.540000000000001, 10.542, 10.544,
      10.546, 10.548, 10.55, 10.552, 10.554, 10.556000000000001, 10.558, 10.56,
      10.562, 10.564, 10.566, 10.568, 10.57, 10.572000000000001, 10.574, 10.576,
      10.578, 10.58, 10.582, 10.584, 10.586, 10.588000000000001, 10.59, 10.592,
      10.594, 10.596, 10.598, 10.6, 10.602, 10.604000000000001, 10.606, 10.608,
      10.61, 10.612, 10.614, 10.616, 10.618, 10.620000000000001, 10.622, 10.624,
      10.626, 10.628, 10.63, 10.632, 10.634, 10.636000000000001, 10.638, 10.64,
      10.642, 10.644, 10.646, 10.648, 10.65, 10.652000000000001, 10.654, 10.656,
      10.658, 10.66, 10.662, 10.664, 10.666, 10.668000000000001, 10.67, 10.672,
      10.674, 10.676, 10.678, 10.68, 10.682, 10.684000000000001, 10.686, 10.688,
      10.69, 10.692, 10.694, 10.696, 10.698, 10.700000000000001, 10.702, 10.704,
      10.706, 10.708, 10.71, 10.712, 10.714, 10.716000000000001, 10.718, 10.72,
      10.722, 10.724, 10.726, 10.728, 10.73, 10.732000000000001, 10.734, 10.736,
      10.738, 10.74, 10.742, 10.744, 10.746, 10.748000000000001, 10.75, 10.752,
      10.754, 10.756, 10.758000000000001, 10.76, 10.762, 10.764, 10.766, 10.768,
      10.77, 10.772, 10.774000000000001, 10.776, 10.778, 10.78, 10.782, 10.784,
      10.786, 10.788, 10.790000000000001, 10.792, 10.794, 10.796, 10.798, 10.8,
      10.802, 10.804, 10.806000000000001, 10.808, 10.81, 10.812, 10.814, 10.816,
      10.818, 10.82, 10.822000000000001, 10.824, 10.826, 10.828, 10.83, 10.832,
      10.834, 10.836, 10.838000000000001, 10.84, 10.842, 10.844, 10.846, 10.848,
      10.85, 10.852, 10.854000000000001, 10.856, 10.858, 10.86, 10.862, 10.864,
      10.866, 10.868, 10.870000000000001, 10.872, 10.874, 10.876, 10.878, 10.88,
      10.882, 10.884, 10.886000000000001, 10.888, 10.89, 10.892, 10.894, 10.896,
      10.898, 10.9, 10.902000000000001, 10.904, 10.906, 10.908, 10.91, 10.912,
      10.914, 10.916, 10.918000000000001, 10.92, 10.922, 10.924, 10.926, 10.928,
      10.93, 10.932, 10.934000000000001, 10.936, 10.938, 10.94, 10.942, 10.944,
      10.946, 10.948, 10.950000000000001, 10.952, 10.954, 10.956, 10.958, 10.96,
      10.962, 10.964, 10.966000000000001, 10.968, 10.97, 10.972, 10.974, 10.976,
      10.978, 10.98, 10.982000000000001, 10.984, 10.986, 10.988, 10.99, 10.992,
      10.994, 10.996, 10.998000000000001, 11.0, 11.002, 11.004, 11.006,
      11.008000000000001, 11.01, 11.012, 11.014, 11.016, 11.018, 11.02, 11.022,
      11.024000000000001, 11.026, 11.028, 11.03, 11.032, 11.034, 11.036, 11.038,
      11.040000000000001, 11.042, 11.044, 11.046, 11.048, 11.05, 11.052, 11.054,
      11.056000000000001, 11.058, 11.06, 11.062, 11.064, 11.066, 11.068, 11.07,
      11.072000000000001, 11.074, 11.076, 11.078, 11.08, 11.082, 11.084, 11.086,
      11.088000000000001, 11.09, 11.092, 11.094, 11.096, 11.098, 11.1, 11.102,
      11.104000000000001, 11.106, 11.108, 11.11, 11.112, 11.114, 11.116, 11.118,
      11.120000000000001, 11.122, 11.124, 11.126, 11.128, 11.13, 11.132, 11.134,
      11.136000000000001, 11.138, 11.14, 11.142, 11.144, 11.146, 11.148, 11.15,
      11.152000000000001, 11.154, 11.156, 11.158, 11.16, 11.162, 11.164, 11.166,
      11.168000000000001, 11.17, 11.172, 11.174, 11.176, 11.178, 11.18, 11.182,
      11.184000000000001, 11.186, 11.188, 11.19, 11.192, 11.194, 11.196, 11.198,
      11.200000000000001, 11.202, 11.204, 11.206, 11.208, 11.21, 11.212, 11.214,
      11.216000000000001, 11.218, 11.22, 11.222, 11.224, 11.226, 11.228, 11.23,
      11.232000000000001, 11.234, 11.236, 11.238, 11.24, 11.242, 11.244, 11.246,
      11.248000000000001, 11.25, 11.252, 11.254, 11.256, 11.258000000000001,
      11.26, 11.262, 11.264, 11.266, 11.268, 11.27, 11.272, 11.274000000000001,
      11.276, 11.278, 11.28, 11.282, 11.284, 11.286, 11.288, 11.290000000000001,
      11.292, 11.294, 11.296, 11.298, 11.3, 11.302, 11.304, 11.306000000000001,
      11.308, 11.31, 11.312, 11.314, 11.316, 11.318, 11.32, 11.322000000000001,
      11.324, 11.326, 11.328, 11.33, 11.332, 11.334, 11.336, 11.338000000000001,
      11.34, 11.342, 11.344, 11.346, 11.348, 11.35, 11.352, 11.354000000000001,
      11.356, 11.358, 11.36, 11.362, 11.364, 11.366, 11.368, 11.370000000000001,
      11.372, 11.374, 11.376, 11.378, 11.38, 11.382, 11.384, 11.386000000000001,
      11.388, 11.39, 11.392, 11.394, 11.396, 11.398, 11.4, 11.402000000000001,
      11.404, 11.406, 11.408, 11.41, 11.412, 11.414, 11.416, 11.418000000000001,
      11.42, 11.422, 11.424, 11.426, 11.428, 11.43, 11.432, 11.434000000000001,
      11.436, 11.438, 11.44, 11.442, 11.444, 11.446, 11.448, 11.450000000000001,
      11.452, 11.454, 11.456, 11.458, 11.46, 11.462, 11.464, 11.466000000000001,
      11.468, 11.47, 11.472, 11.474, 11.476, 11.478, 11.48, 11.482000000000001,
      11.484, 11.486, 11.488, 11.49, 11.492, 11.494, 11.496, 11.498000000000001,
      11.5, 11.502, 11.504, 11.506, 11.508000000000001, 11.51, 11.512,
      11.514000000000001, 11.516, 11.518, 11.52, 11.522, 11.524000000000001,
      11.526, 11.528, 11.53, 11.532, 11.534, 11.536, 11.538, 11.540000000000001,
      11.542, 11.544, 11.546, 11.548, 11.55, 11.552, 11.554, 11.556000000000001,
      11.558, 11.56, 11.562, 11.564, 11.566, 11.568, 11.57, 11.572000000000001,
      11.574, 11.576, 11.578, 11.58, 11.582, 11.584, 11.586, 11.588000000000001,
      11.59, 11.592, 11.594, 11.596, 11.598, 11.6, 11.602, 11.604000000000001,
      11.606, 11.608, 11.61, 11.612, 11.614, 11.616, 11.618, 11.620000000000001,
      11.622, 11.624, 11.626, 11.628, 11.63, 11.632, 11.634, 11.636000000000001,
      11.638, 11.64, 11.642, 11.644, 11.646, 11.648, 11.65, 11.652000000000001,
      11.654, 11.656, 11.658, 11.66, 11.662, 11.664, 11.666, 11.668000000000001,
      11.67, 11.672, 11.674, 11.676, 11.678, 11.68, 11.682, 11.684000000000001,
      11.686, 11.688, 11.69, 11.692, 11.694, 11.696, 11.698, 11.700000000000001,
      11.702, 11.704, 11.706, 11.708, 11.71, 11.712, 11.714, 11.716000000000001,
      11.718, 11.72, 11.722, 11.724, 11.726, 11.728, 11.73, 11.732000000000001,
      11.734, 11.736, 11.738, 11.74, 11.742, 11.744, 11.746, 11.748000000000001,
      11.75, 11.752, 11.754, 11.756, 11.758000000000001, 11.76, 11.762,
      11.764000000000001, 11.766, 11.768, 11.77, 11.772, 11.774000000000001,
      11.776, 11.778, 11.78, 11.782, 11.784, 11.786, 11.788, 11.790000000000001,
      11.792, 11.794, 11.796, 11.798, 11.8, 11.802, 11.804, 11.806000000000001,
      11.808, 11.81, 11.812, 11.814, 11.816, 11.818, 11.82, 11.822000000000001,
      11.824, 11.826, 11.828, 11.83, 11.832, 11.834, 11.836, 11.838000000000001,
      11.84, 11.842, 11.844, 11.846, 11.848, 11.85, 11.852, 11.854000000000001,
      11.856, 11.858, 11.86, 11.862, 11.864, 11.866, 11.868, 11.870000000000001,
      11.872, 11.874, 11.876, 11.878, 11.88, 11.882, 11.884, 11.886000000000001,
      11.888, 11.89, 11.892, 11.894, 11.896, 11.898, 11.9, 11.902000000000001,
      11.904, 11.906, 11.908, 11.91, 11.912, 11.914, 11.916, 11.918000000000001,
      11.92, 11.922, 11.924, 11.926, 11.928, 11.93, 11.932, 11.934000000000001,
      11.936, 11.938, 11.94, 11.942, 11.944, 11.946, 11.948, 11.950000000000001,
      11.952, 11.954, 11.956, 11.958, 11.96, 11.962, 11.964, 11.966000000000001,
      11.968, 11.97, 11.972, 11.974, 11.976, 11.978, 11.98, 11.982000000000001,
      11.984, 11.986, 11.988, 11.99, 11.992, 11.994, 11.996, 11.998000000000001,
      12.0, 12.002, 12.004, 12.006, 12.008000000000001, 12.01, 12.012,
      12.014000000000001, 12.016, 12.018, 12.02, 12.022, 12.024000000000001,
      12.026, 12.028, 12.030000000000001, 12.032, 12.034, 12.036, 12.038,
      12.040000000000001, 12.042, 12.044, 12.046, 12.048, 12.05, 12.052, 12.054,
      12.056000000000001, 12.058, 12.06, 12.062, 12.064, 12.066, 12.068, 12.07,
      12.072000000000001, 12.074, 12.076, 12.078, 12.08, 12.082, 12.084, 12.086,
      12.088000000000001, 12.09, 12.092, 12.094, 12.096, 12.098, 12.1, 12.102,
      12.104000000000001, 12.106, 12.108, 12.11, 12.112, 12.114, 12.116, 12.118,
      12.120000000000001, 12.122, 12.124, 12.126, 12.128, 12.13, 12.132, 12.134,
      12.136000000000001, 12.138, 12.14, 12.142, 12.144, 12.146, 12.148, 12.15,
      12.152000000000001, 12.154, 12.156, 12.158, 12.16, 12.162, 12.164, 12.166,
      12.168000000000001, 12.17, 12.172, 12.174, 12.176, 12.178, 12.18, 12.182,
      12.184000000000001, 12.186, 12.188, 12.19, 12.192, 12.194, 12.196, 12.198,
      12.200000000000001, 12.202, 12.204, 12.206, 12.208, 12.21, 12.212, 12.214,
      12.216000000000001, 12.218, 12.22, 12.222, 12.224, 12.226, 12.228, 12.23,
      12.232000000000001, 12.234, 12.236, 12.238, 12.24, 12.242, 12.244, 12.246,
      12.248000000000001, 12.25, 12.252, 12.254, 12.256, 12.258000000000001,
      12.26, 12.262, 12.264000000000001, 12.266, 12.268, 12.27, 12.272,
      12.274000000000001, 12.276, 12.278, 12.280000000000001, 12.282, 12.284,
      12.286, 12.288, 12.290000000000001, 12.292, 12.294, 12.296, 12.298, 12.3,
      12.302, 12.304, 12.306000000000001, 12.308, 12.31, 12.312, 12.314, 12.316,
      12.318, 12.32, 12.322000000000001, 12.324, 12.326, 12.328, 12.33, 12.332,
      12.334, 12.336, 12.338000000000001, 12.34, 12.342, 12.344, 12.346, 12.348,
      12.35, 12.352, 12.354000000000001, 12.356, 12.358, 12.36, 12.362, 12.364,
      12.366, 12.368, 12.370000000000001, 12.372, 12.374, 12.376, 12.378, 12.38,
      12.382, 12.384, 12.386000000000001, 12.388, 12.39, 12.392, 12.394, 12.396,
      12.398, 12.4, 12.402000000000001, 12.404, 12.406, 12.408, 12.41, 12.412,
      12.414, 12.416, 12.418000000000001, 12.42, 12.422, 12.424, 12.426, 12.428,
      12.43, 12.432, 12.434000000000001, 12.436, 12.438, 12.44, 12.442, 12.444,
      12.446, 12.448, 12.450000000000001, 12.452, 12.454, 12.456, 12.458, 12.46,
      12.462, 12.464, 12.466000000000001, 12.468, 12.47, 12.472, 12.474, 12.476,
      12.478, 12.48, 12.482000000000001, 12.484, 12.486, 12.488, 12.49, 12.492,
      12.494, 12.496, 12.498000000000001, 12.5, 12.502, 12.504, 12.506,
      12.508000000000001, 12.51, 12.512, 12.514000000000001, 12.516, 12.518,
      12.52, 12.522, 12.524000000000001, 12.526, 12.528, 12.530000000000001,
      12.532, 12.534, 12.536, 12.538, 12.540000000000001, 12.542, 12.544, 12.546,
      12.548, 12.55, 12.552, 12.554, 12.556000000000001, 12.558, 12.56, 12.562,
      12.564, 12.566, 12.568, 12.57, 12.572000000000001, 12.574, 12.576, 12.578,
      12.58, 12.582, 12.584, 12.586, 12.588000000000001, 12.59, 12.592, 12.594,
      12.596, 12.598, 12.6, 12.602, 12.604000000000001, 12.606, 12.608, 12.61,
      12.612, 12.614, 12.616, 12.618, 12.620000000000001, 12.622, 12.624, 12.626,
      12.628, 12.63, 12.632, 12.634, 12.636000000000001, 12.638, 12.64, 12.642,
      12.644, 12.646, 12.648, 12.65, 12.652000000000001, 12.654, 12.656, 12.658,
      12.66, 12.662, 12.664, 12.666, 12.668000000000001, 12.67, 12.672, 12.674,
      12.676, 12.678, 12.68, 12.682, 12.684000000000001, 12.686, 12.688, 12.69,
      12.692, 12.694, 12.696, 12.698, 12.700000000000001, 12.702, 12.704, 12.706,
      12.708, 12.71, 12.712, 12.714, 12.716000000000001, 12.718, 12.72, 12.722,
      12.724, 12.726, 12.728, 12.73, 12.732000000000001, 12.734, 12.736, 12.738,
      12.74, 12.742, 12.744, 12.746, 12.748000000000001, 12.75, 12.752, 12.754,
      12.756, 12.758000000000001, 12.76, 12.762, 12.764000000000001, 12.766,
      12.768, 12.77, 12.772, 12.774000000000001, 12.776, 12.778,
      12.780000000000001, 12.782, 12.784, 12.786, 12.788, 12.790000000000001,
      12.792, 12.794, 12.796000000000001, 12.798, 12.8, 12.802, 12.804,
      12.806000000000001, 12.808, 12.81, 12.812, 12.814, 12.816, 12.818, 12.82,
      12.822000000000001, 12.824, 12.826, 12.828, 12.83, 12.832, 12.834, 12.836,
      12.838000000000001, 12.84, 12.842, 12.844, 12.846, 12.848, 12.85, 12.852,
      12.854000000000001, 12.856, 12.858, 12.86, 12.862, 12.864, 12.866, 12.868,
      12.870000000000001, 12.872, 12.874, 12.876, 12.878, 12.88, 12.882, 12.884,
      12.886000000000001, 12.888, 12.89, 12.892, 12.894, 12.896, 12.898, 12.9,
      12.902000000000001, 12.904, 12.906, 12.908, 12.91, 12.912, 12.914, 12.916,
      12.918000000000001, 12.92, 12.922, 12.924, 12.926, 12.928, 12.93, 12.932,
      12.934000000000001, 12.936, 12.938, 12.94, 12.942, 12.944, 12.946, 12.948,
      12.950000000000001, 12.952, 12.954, 12.956, 12.958, 12.96, 12.962, 12.964,
      12.966000000000001, 12.968, 12.97, 12.972, 12.974, 12.976, 12.978, 12.98,
      12.982000000000001, 12.984, 12.986, 12.988, 12.99, 12.992, 12.994, 12.996,
      12.998000000000001, 13.0, 13.002, 13.004, 13.006, 13.008000000000001,
      13.01, 13.012, 13.014000000000001, 13.016, 13.018, 13.02, 13.022,
      13.024000000000001, 13.026, 13.028, 13.030000000000001, 13.032, 13.034,
      13.036, 13.038, 13.040000000000001, 13.042, 13.044, 13.046000000000001,
      13.048, 13.05, 13.052, 13.054, 13.056000000000001, 13.058, 13.06, 13.062,
      13.064, 13.066, 13.068, 13.07, 13.072000000000001, 13.074, 13.076, 13.078,
      13.08, 13.082, 13.084, 13.086, 13.088000000000001, 13.09, 13.092, 13.094,
      13.096, 13.098, 13.1, 13.102, 13.104000000000001, 13.106, 13.108, 13.11,
      13.112, 13.114, 13.116, 13.118, 13.120000000000001, 13.122, 13.124, 13.126,
      13.128, 13.13, 13.132, 13.134, 13.136000000000001, 13.138, 13.14, 13.142,
      13.144, 13.146, 13.148, 13.15, 13.152000000000001, 13.154, 13.156, 13.158,
      13.16, 13.162, 13.164, 13.166, 13.168000000000001, 13.17, 13.172, 13.174,
      13.176, 13.178, 13.18, 13.182, 13.184000000000001, 13.186, 13.188, 13.19,
      13.192, 13.194, 13.196, 13.198, 13.200000000000001, 13.202, 13.204, 13.206,
      13.208, 13.21, 13.212, 13.214, 13.216000000000001, 13.218, 13.22, 13.222,
      13.224, 13.226, 13.228, 13.23, 13.232000000000001, 13.234, 13.236, 13.238,
      13.24, 13.242, 13.244, 13.246, 13.248000000000001, 13.25, 13.252, 13.254,
      13.256, 13.258000000000001, 13.26, 13.262, 13.264000000000001, 13.266,
      13.268, 13.27, 13.272, 13.274000000000001, 13.276, 13.278,
      13.280000000000001, 13.282, 13.284, 13.286, 13.288, 13.290000000000001,
      13.292, 13.294, 13.296000000000001, 13.298, 13.3, 13.302, 13.304,
      13.306000000000001, 13.308, 13.31, 13.312000000000001, 13.314, 13.316,
      13.318, 13.32, 13.322000000000001, 13.324, 13.326, 13.328, 13.33, 13.332,
      13.334, 13.336, 13.338000000000001, 13.34, 13.342, 13.344, 13.346, 13.348,
      13.35, 13.352, 13.354000000000001, 13.356, 13.358, 13.36, 13.362, 13.364,
      13.366, 13.368, 13.370000000000001, 13.372, 13.374, 13.376, 13.378, 13.38,
      13.382, 13.384, 13.386000000000001, 13.388, 13.39, 13.392, 13.394, 13.396,
      13.398, 13.4, 13.402000000000001, 13.404, 13.406, 13.408, 13.41, 13.412,
      13.414, 13.416, 13.418000000000001, 13.42, 13.422, 13.424, 13.426, 13.428,
      13.43, 13.432, 13.434000000000001, 13.436, 13.438, 13.44, 13.442, 13.444,
      13.446, 13.448, 13.450000000000001, 13.452, 13.454, 13.456, 13.458, 13.46,
      13.462, 13.464, 13.466000000000001, 13.468, 13.47, 13.472, 13.474, 13.476,
      13.478, 13.48, 13.482000000000001, 13.484, 13.486, 13.488, 13.49, 13.492,
      13.494, 13.496, 13.498000000000001, 13.5, 13.502, 13.504, 13.506,
      13.508000000000001, 13.51, 13.512, 13.514000000000001, 13.516, 13.518,
      13.52, 13.522, 13.524000000000001, 13.526, 13.528, 13.530000000000001,
      13.532, 13.534, 13.536, 13.538, 13.540000000000001, 13.542, 13.544,
      13.546000000000001, 13.548, 13.55, 13.552, 13.554, 13.556000000000001,
      13.558, 13.56, 13.562000000000001, 13.564, 13.566, 13.568, 13.57,
      13.572000000000001, 13.574, 13.576, 13.578, 13.58, 13.582, 13.584, 13.586,
      13.588000000000001, 13.59, 13.592, 13.594, 13.596, 13.598, 13.6, 13.602,
      13.604000000000001, 13.606, 13.608, 13.61, 13.612, 13.614, 13.616, 13.618,
      13.620000000000001, 13.622, 13.624, 13.626, 13.628, 13.63, 13.632, 13.634,
      13.636000000000001, 13.638, 13.64, 13.642, 13.644, 13.646, 13.648, 13.65,
      13.652000000000001, 13.654, 13.656, 13.658, 13.66, 13.662, 13.664, 13.666,
      13.668000000000001, 13.67, 13.672, 13.674, 13.676, 13.678, 13.68, 13.682,
      13.684000000000001, 13.686, 13.688, 13.69, 13.692, 13.694, 13.696, 13.698,
      13.700000000000001, 13.702, 13.704, 13.706, 13.708, 13.71, 13.712, 13.714,
      13.716000000000001, 13.718, 13.72, 13.722, 13.724, 13.726, 13.728, 13.73,
      13.732000000000001, 13.734, 13.736, 13.738, 13.74, 13.742, 13.744, 13.746,
      13.748000000000001, 13.75, 13.752, 13.754, 13.756, 13.758000000000001,
      13.76, 13.762, 13.764000000000001, 13.766, 13.768, 13.77, 13.772,
      13.774000000000001, 13.776, 13.778, 13.780000000000001, 13.782, 13.784,
      13.786, 13.788, 13.790000000000001, 13.792, 13.794, 13.796000000000001,
      13.798, 13.8, 13.802, 13.804, 13.806000000000001, 13.808, 13.81,
      13.812000000000001, 13.814, 13.816, 13.818, 13.82, 13.822000000000001,
      13.824, 13.826, 13.828, 13.83, 13.832, 13.834, 13.836, 13.838000000000001,
      13.84, 13.842, 13.844, 13.846, 13.848, 13.85, 13.852, 13.854000000000001,
      13.856, 13.858, 13.86, 13.862, 13.864, 13.866, 13.868, 13.870000000000001,
      13.872, 13.874, 13.876, 13.878, 13.88, 13.882, 13.884, 13.886000000000001,
      13.888, 13.89, 13.892, 13.894, 13.896, 13.898, 13.9, 13.902000000000001,
      13.904, 13.906, 13.908, 13.91, 13.912, 13.914, 13.916, 13.918000000000001,
      13.92, 13.922, 13.924, 13.926, 13.928, 13.93, 13.932, 13.934000000000001,
      13.936, 13.938, 13.94, 13.942, 13.944, 13.946, 13.948, 13.950000000000001,
      13.952, 13.954, 13.956, 13.958, 13.96, 13.962, 13.964, 13.966000000000001,
      13.968, 13.97, 13.972, 13.974, 13.976, 13.978, 13.98, 13.982000000000001,
      13.984, 13.986, 13.988, 13.99, 13.992, 13.994, 13.996, 13.998000000000001,
      14.0, 14.002, 14.004, 14.006, 14.008000000000001, 14.01, 14.012,
      14.014000000000001, 14.016, 14.018, 14.02, 14.022, 14.024000000000001,
      14.026, 14.028, 14.030000000000001, 14.032, 14.034, 14.036, 14.038,
      14.040000000000001, 14.042, 14.044, 14.046000000000001, 14.048, 14.05,
      14.052, 14.054, 14.056000000000001, 14.058, 14.06, 14.062000000000001,
      14.064, 14.066, 14.068, 14.07, 14.072000000000001, 14.074, 14.076,
      14.078000000000001, 14.08, 14.082, 14.084, 14.086, 14.088000000000001,
      14.09, 14.092, 14.094, 14.096, 14.098, 14.1, 14.102, 14.104000000000001,
      14.106, 14.108, 14.11, 14.112, 14.114, 14.116, 14.118, 14.120000000000001,
      14.122, 14.124, 14.126, 14.128, 14.13, 14.132, 14.134, 14.136000000000001,
      14.138, 14.14, 14.142, 14.144, 14.146, 14.148, 14.15, 14.152000000000001,
      14.154, 14.156, 14.158, 14.16, 14.162, 14.164, 14.166, 14.168000000000001,
      14.17, 14.172, 14.174, 14.176, 14.178, 14.18, 14.182, 14.184000000000001,
      14.186, 14.188, 14.19, 14.192, 14.194, 14.196, 14.198, 14.200000000000001,
      14.202, 14.204, 14.206, 14.208, 14.21, 14.212, 14.214, 14.216000000000001,
      14.218, 14.22, 14.222, 14.224, 14.226, 14.228, 14.23, 14.232000000000001,
      14.234, 14.236, 14.238, 14.24, 14.242, 14.244, 14.246, 14.248000000000001,
      14.25, 14.252, 14.254, 14.256, 14.258000000000001, 14.26, 14.262,
      14.264000000000001, 14.266, 14.268, 14.27, 14.272, 14.274000000000001,
      14.276, 14.278, 14.280000000000001, 14.282, 14.284, 14.286, 14.288,
      14.290000000000001, 14.292, 14.294, 14.296000000000001, 14.298, 14.3,
      14.302, 14.304, 14.306000000000001, 14.308, 14.31, 14.312000000000001,
      14.314, 14.316, 14.318, 14.32, 14.322000000000001, 14.324, 14.326,
      14.328000000000001, 14.33, 14.332, 14.334, 14.336, 14.338000000000001,
      14.34, 14.342, 14.344, 14.346, 14.348, 14.35, 14.352, 14.354000000000001,
      14.356, 14.358, 14.36, 14.362, 14.364, 14.366, 14.368, 14.370000000000001,
      14.372, 14.374, 14.376, 14.378, 14.38, 14.382, 14.384, 14.386000000000001,
      14.388, 14.39, 14.392, 14.394, 14.396, 14.398, 14.4, 14.402000000000001,
      14.404, 14.406, 14.408, 14.41, 14.412, 14.414, 14.416, 14.418000000000001,
      14.42, 14.422, 14.424, 14.426, 14.428, 14.43, 14.432, 14.434000000000001,
      14.436, 14.438, 14.44, 14.442, 14.444, 14.446, 14.448, 14.450000000000001,
      14.452, 14.454, 14.456, 14.458, 14.46, 14.462, 14.464, 14.466000000000001,
      14.468, 14.47, 14.472, 14.474, 14.476, 14.478, 14.48, 14.482000000000001,
      14.484, 14.486, 14.488, 14.49, 14.492, 14.494, 14.496, 14.498000000000001,
      14.5, 14.502, 14.504, 14.506, 14.508000000000001, 14.51, 14.512,
      14.514000000000001, 14.516, 14.518, 14.52, 14.522, 14.524000000000001,
      14.526, 14.528, 14.530000000000001, 14.532, 14.534, 14.536, 14.538,
      14.540000000000001, 14.542, 14.544, 14.546000000000001, 14.548, 14.55,
      14.552, 14.554, 14.556000000000001, 14.558, 14.56, 14.562000000000001,
      14.564, 14.566, 14.568, 14.57, 14.572000000000001, 14.574, 14.576,
      14.578000000000001, 14.58, 14.582, 14.584, 14.586, 14.588000000000001,
      14.59, 14.592, 14.594, 14.596, 14.598, 14.6, 14.602, 14.604000000000001,
      14.606, 14.608, 14.61, 14.612, 14.614, 14.616, 14.618, 14.620000000000001,
      14.622, 14.624, 14.626, 14.628, 14.63, 14.632, 14.634, 14.636000000000001,
      14.638, 14.64, 14.642, 14.644, 14.646, 14.648, 14.65, 14.652000000000001,
      14.654, 14.656, 14.658, 14.66, 14.662, 14.664, 14.666, 14.668000000000001,
      14.67, 14.672, 14.674, 14.676, 14.678, 14.68, 14.682, 14.684000000000001,
      14.686, 14.688, 14.69, 14.692, 14.694, 14.696, 14.698, 14.700000000000001,
      14.702, 14.704, 14.706, 14.708, 14.71, 14.712, 14.714, 14.716000000000001,
      14.718, 14.72, 14.722, 14.724, 14.726, 14.728, 14.73, 14.732000000000001,
      14.734, 14.736, 14.738, 14.74, 14.742, 14.744, 14.746, 14.748000000000001,
      14.75, 14.752, 14.754, 14.756, 14.758000000000001, 14.76, 14.762,
      14.764000000000001, 14.766, 14.768, 14.77, 14.772, 14.774000000000001,
      14.776, 14.778, 14.780000000000001, 14.782, 14.784, 14.786, 14.788,
      14.790000000000001, 14.792, 14.794, 14.796000000000001, 14.798, 14.8,
      14.802, 14.804, 14.806000000000001, 14.808, 14.81, 14.812000000000001,
      14.814, 14.816, 14.818, 14.82, 14.822000000000001, 14.824, 14.826,
      14.828000000000001, 14.83, 14.832, 14.834, 14.836, 14.838000000000001,
      14.84, 14.842, 14.844000000000001, 14.846, 14.848, 14.85, 14.852,
      14.854000000000001, 14.856, 14.858, 14.86, 14.862, 14.864, 14.866, 14.868,
      14.870000000000001, 14.872, 14.874, 14.876, 14.878, 14.88, 14.882, 14.884,
      14.886000000000001, 14.888, 14.89, 14.892, 14.894, 14.896, 14.898, 14.9,
      14.902000000000001, 14.904, 14.906, 14.908, 14.91, 14.912, 14.914, 14.916,
      14.918000000000001, 14.92, 14.922, 14.924, 14.926, 14.928, 14.93, 14.932,
      14.934000000000001, 14.936, 14.938, 14.94, 14.942, 14.944, 14.946, 14.948,
      14.950000000000001, 14.952, 14.954, 14.956, 14.958, 14.96, 14.962, 14.964,
      14.966000000000001, 14.968, 14.97, 14.972, 14.974, 14.976, 14.978, 14.98,
      14.982000000000001, 14.984, 14.986, 14.988, 14.99, 14.992, 14.994, 14.996,
      14.998000000000001, 15.0, 15.002, 15.004, 15.006, 15.008000000000001,
      15.01, 15.012, 15.014000000000001, 15.016, 15.018, 15.02, 15.022,
      15.024000000000001, 15.026, 15.028, 15.030000000000001, 15.032, 15.034,
      15.036, 15.038, 15.040000000000001, 15.042, 15.044, 15.046000000000001,
      15.048, 15.05, 15.052, 15.054, 15.056000000000001, 15.058, 15.06,
      15.062000000000001, 15.064, 15.066, 15.068, 15.07, 15.072000000000001,
      15.074, 15.076, 15.078000000000001, 15.08, 15.082, 15.084, 15.086,
      15.088000000000001, 15.09, 15.092, 15.094000000000001, 15.096, 15.098,
      15.1, 15.102, 15.104000000000001, 15.106, 15.108, 15.11, 15.112, 15.114,
      15.116, 15.118, 15.120000000000001, 15.122, 15.124, 15.126, 15.128, 15.13,
      15.132, 15.134, 15.136000000000001, 15.138, 15.14, 15.142, 15.144, 15.146,
      15.148, 15.15, 15.152000000000001, 15.154, 15.156, 15.158, 15.16, 15.162,
      15.164, 15.166, 15.168000000000001, 15.17, 15.172, 15.174, 15.176, 15.178,
      15.18, 15.182, 15.184000000000001, 15.186, 15.188, 15.19, 15.192, 15.194,
      15.196, 15.198, 15.200000000000001, 15.202, 15.204, 15.206, 15.208, 15.21,
      15.212, 15.214, 15.216000000000001, 15.218, 15.22, 15.222, 15.224, 15.226,
      15.228, 15.23, 15.232000000000001, 15.234, 15.236, 15.238, 15.24, 15.242,
      15.244, 15.246, 15.248000000000001, 15.25, 15.252, 15.254, 15.256,
      15.258000000000001, 15.26, 15.262, 15.264000000000001, 15.266, 15.268,
      15.27, 15.272, 15.274000000000001, 15.276, 15.278, 15.280000000000001,
      15.282, 15.284, 15.286, 15.288, 15.290000000000001, 15.292, 15.294,
      15.296000000000001, 15.298, 15.3, 15.302, 15.304, 15.306000000000001,
      15.308, 15.31, 15.312000000000001, 15.314, 15.316, 15.318, 15.32,
      15.322000000000001, 15.324, 15.326, 15.328000000000001, 15.33, 15.332,
      15.334, 15.336, 15.338000000000001, 15.34, 15.342, 15.344000000000001,
      15.346, 15.348, 15.35, 15.352, 15.354000000000001, 15.356, 15.358, 15.36,
      15.362, 15.364, 15.366, 15.368, 15.370000000000001, 15.372, 15.374, 15.376,
      15.378, 15.38, 15.382, 15.384, 15.386000000000001, 15.388, 15.39, 15.392,
      15.394, 15.396, 15.398, 15.4, 15.402000000000001, 15.404, 15.406, 15.408,
      15.41, 15.412, 15.414, 15.416, 15.418000000000001, 15.42, 15.422, 15.424,
      15.426, 15.428, 15.43, 15.432, 15.434000000000001, 15.436, 15.438, 15.44,
      15.442, 15.444, 15.446, 15.448, 15.450000000000001, 15.452, 15.454, 15.456,
      15.458, 15.46, 15.462, 15.464, 15.466000000000001, 15.468, 15.47, 15.472,
      15.474, 15.476, 15.478, 15.48, 15.482000000000001, 15.484, 15.486, 15.488,
      15.49, 15.492, 15.494, 15.496, 15.498000000000001, 15.5, 15.502, 15.504,
      15.506, 15.508000000000001, 15.51, 15.512, 15.514000000000001, 15.516,
      15.518, 15.52, 15.522, 15.524000000000001, 15.526, 15.528,
      15.530000000000001, 15.532, 15.534, 15.536, 15.538, 15.540000000000001,
      15.542, 15.544, 15.546000000000001, 15.548, 15.55, 15.552, 15.554,
      15.556000000000001, 15.558, 15.56, 15.562000000000001, 15.564, 15.566,
      15.568, 15.57, 15.572000000000001, 15.574, 15.576, 15.578000000000001,
      15.58, 15.582, 15.584, 15.586, 15.588000000000001, 15.59, 15.592,
      15.594000000000001, 15.596, 15.598, 15.6, 15.602, 15.604000000000001,
      15.606, 15.608, 15.610000000000001, 15.612, 15.614, 15.616, 15.618,
      15.620000000000001, 15.622, 15.624, 15.626, 15.628, 15.63, 15.632, 15.634,
      15.636000000000001, 15.638, 15.64, 15.642, 15.644, 15.646, 15.648, 15.65,
      15.652000000000001, 15.654, 15.656, 15.658, 15.66, 15.662, 15.664, 15.666,
      15.668000000000001, 15.67, 15.672, 15.674, 15.676, 15.678, 15.68, 15.682,
      15.684000000000001, 15.686, 15.688, 15.69, 15.692, 15.694, 15.696, 15.698,
      15.700000000000001, 15.702, 15.704, 15.706, 15.708, 15.71, 15.712, 15.714,
      15.716000000000001, 15.718, 15.72, 15.722, 15.724, 15.726, 15.728, 15.73,
      15.732000000000001, 15.734, 15.736, 15.738, 15.74, 15.742, 15.744, 15.746,
      15.748000000000001, 15.75, 15.752, 15.754, 15.756, 15.758000000000001,
      15.76, 15.762, 15.764000000000001, 15.766, 15.768, 15.77, 15.772,
      15.774000000000001, 15.776, 15.778, 15.780000000000001, 15.782, 15.784,
      15.786, 15.788, 15.790000000000001, 15.792, 15.794, 15.796000000000001,
      15.798, 15.8, 15.802, 15.804, 15.806000000000001, 15.808, 15.81,
      15.812000000000001, 15.814, 15.816, 15.818, 15.82, 15.822000000000001,
      15.824, 15.826, 15.828000000000001, 15.83, 15.832, 15.834, 15.836,
      15.838000000000001, 15.84, 15.842, 15.844000000000001, 15.846, 15.848,
      15.85, 15.852, 15.854000000000001, 15.856, 15.858, 15.860000000000001,
      15.862, 15.864, 15.866, 15.868, 15.870000000000001, 15.872, 15.874, 15.876,
      15.878, 15.88, 15.882, 15.884, 15.886000000000001, 15.888, 15.89, 15.892,
      15.894, 15.896, 15.898, 15.9, 15.902000000000001, 15.904, 15.906, 15.908,
      15.91, 15.912, 15.914, 15.916, 15.918000000000001, 15.92, 15.922, 15.924,
      15.926, 15.928, 15.93, 15.932, 15.934000000000001, 15.936, 15.938, 15.94,
      15.942, 15.944, 15.946, 15.948, 15.950000000000001, 15.952, 15.954, 15.956,
      15.958, 15.96, 15.962, 15.964, 15.966000000000001, 15.968, 15.97, 15.972,
      15.974, 15.976, 15.978, 15.98, 15.982000000000001, 15.984, 15.986, 15.988,
      15.99, 15.992, 15.994, 15.996, 15.998000000000001, 16.0, 16.002, 16.004,
      16.006, 16.008, 16.01, 16.012, 16.014, 16.016000000000002, 16.018, 16.02,
      16.022000000000002, 16.024, 16.026, 16.028, 16.03, 16.032, 16.034, 16.036,
      16.038, 16.04, 16.042, 16.044, 16.046, 16.048000000000002, 16.05, 16.052,
      16.054000000000002, 16.056, 16.058, 16.06, 16.062, 16.064, 16.066, 16.068,
      16.07, 16.072, 16.074, 16.076, 16.078, 16.080000000000002, 16.082, 16.084,
      16.086000000000002, 16.088, 16.09, 16.092, 16.094, 16.096, 16.098, 16.1,
      16.102, 16.104, 16.106, 16.108, 16.11, 16.112000000000002, 16.114, 16.116,
      16.118000000000002, 16.12, 16.122, 16.124, 16.126, 16.128, 16.13, 16.132,
      16.134, 16.136, 16.138, 16.14, 16.142, 16.144000000000002, 16.146, 16.148,
      16.15, 16.152, 16.154, 16.156, 16.158, 16.16, 16.162, 16.164, 16.166,
      16.168, 16.17, 16.172, 16.174, 16.176000000000002, 16.178, 16.18, 16.182,
      16.184, 16.186, 16.188, 16.19, 16.192, 16.194, 16.196, 16.198, 16.2,
      16.202, 16.204, 16.206, 16.208000000000002, 16.21, 16.212, 16.214, 16.216,
      16.218, 16.22, 16.222, 16.224, 16.226, 16.228, 16.23, 16.232, 16.234,
      16.236, 16.238, 16.240000000000002, 16.242, 16.244, 16.246, 16.248, 16.25,
      16.252, 16.254, 16.256, 16.258, 16.26, 16.262, 16.264, 16.266000000000002,
      16.268, 16.27, 16.272000000000002, 16.274, 16.276, 16.278, 16.28, 16.282,
      16.284, 16.286, 16.288, 16.29, 16.292, 16.294, 16.296, 16.298000000000002,
      16.3, 16.302, 16.304000000000002, 16.306, 16.308, 16.31, 16.312, 16.314,
      16.316, 16.318, 16.32, 16.322, 16.324, 16.326, 16.328, 16.330000000000002,
      16.332, 16.334, 16.336000000000002, 16.338, 16.34, 16.342, 16.344, 16.346,
      16.348, 16.35, 16.352, 16.354, 16.356, 16.358, 16.36, 16.362000000000002,
      16.364, 16.366, 16.368000000000002, 16.37, 16.372, 16.374, 16.376, 16.378,
      16.38, 16.382, 16.384, 16.386, 16.388, 16.39, 16.392, 16.394000000000002,
      16.396, 16.398, 16.4, 16.402, 16.404, 16.406, 16.408, 16.41, 16.412,
      16.414, 16.416, 16.418, 16.42, 16.422, 16.424, 16.426000000000002, 16.428,
      16.43, 16.432, 16.434, 16.436, 16.438, 16.44, 16.442, 16.444, 16.446,
      16.448, 16.45, 16.452, 16.454, 16.456, 16.458000000000002, 16.46, 16.462,
      16.464, 16.466, 16.468, 16.47, 16.472, 16.474, 16.476, 16.478, 16.48,
      16.482, 16.484, 16.486, 16.488, 16.490000000000002, 16.492, 16.494, 16.496,
      16.498, 16.5, 16.502, 16.504, 16.506, 16.508, 16.51, 16.512, 16.514,
      16.516000000000002, 16.518, 16.52, 16.522000000000002, 16.524, 16.526,
      16.528, 16.53, 16.532, 16.534, 16.536, 16.538, 16.54, 16.542, 16.544,
      16.546, 16.548000000000002, 16.55, 16.552, 16.554000000000002, 16.556,
      16.558, 16.56, 16.562, 16.564, 16.566, 16.568, 16.57, 16.572, 16.574,
      16.576, 16.578, 16.580000000000002, 16.582, 16.584, 16.586000000000002,
      16.588, 16.59, 16.592, 16.594, 16.596, 16.598, 16.6, 16.602, 16.604,
      16.606, 16.608, 16.61, 16.612000000000002, 16.614, 16.616,
      16.618000000000002, 16.62, 16.622, 16.624, 16.626, 16.628, 16.63, 16.632,
      16.634, 16.636, 16.638, 16.64, 16.642, 16.644000000000002, 16.646, 16.648,
      16.65, 16.652, 16.654, 16.656, 16.658, 16.66, 16.662, 16.664, 16.666,
      16.668, 16.67, 16.672, 16.674, 16.676000000000002, 16.678, 16.68, 16.682,
      16.684, 16.686, 16.688, 16.69, 16.692, 16.694, 16.696, 16.698, 16.7,
      16.702, 16.704, 16.706, 16.708000000000002, 16.71, 16.712, 16.714, 16.716,
      16.718, 16.72, 16.722, 16.724, 16.726, 16.728, 16.73, 16.732, 16.734,
      16.736, 16.738, 16.740000000000002, 16.742, 16.744, 16.746, 16.748, 16.75,
      16.752, 16.754, 16.756, 16.758, 16.76, 16.762, 16.764, 16.766000000000002,
      16.768, 16.77, 16.772000000000002, 16.774, 16.776, 16.778, 16.78, 16.782,
      16.784, 16.786, 16.788, 16.79, 16.792, 16.794, 16.796, 16.798000000000002,
      16.8, 16.802, 16.804000000000002, 16.806, 16.808, 16.81, 16.812, 16.814,
      16.816, 16.818, 16.82, 16.822, 16.824, 16.826, 16.828, 16.830000000000002,
      16.832, 16.834, 16.836000000000002, 16.838, 16.84, 16.842, 16.844, 16.846,
      16.848, 16.85, 16.852, 16.854, 16.856, 16.858, 16.86, 16.862000000000002,
      16.864, 16.866, 16.868000000000002, 16.87, 16.872, 16.874, 16.876, 16.878,
      16.88, 16.882, 16.884, 16.886, 16.888, 16.89, 16.892, 16.894000000000002,
      16.896, 16.898, 16.9, 16.902, 16.904, 16.906, 16.908, 16.91, 16.912,
      16.914, 16.916, 16.918, 16.92, 16.922, 16.924, 16.926000000000002, 16.928,
      16.93, 16.932, 16.934, 16.936, 16.938, 16.94, 16.942, 16.944, 16.946,
      16.948, 16.95, 16.952, 16.954, 16.956, 16.958000000000002, 16.96, 16.962,
      16.964, 16.966, 16.968, 16.97, 16.972, 16.974, 16.976, 16.978, 16.98,
      16.982, 16.984, 16.986, 16.988, 16.990000000000002, 16.992, 16.994, 16.996,
      16.998, 17.0, 17.002, 17.004, 17.006, 17.008, 17.01, 17.012, 17.014,
      17.016000000000002, 17.018, 17.02, 17.022000000000002, 17.024, 17.026,
      17.028, 17.03, 17.032, 17.034, 17.036, 17.038, 17.04, 17.042, 17.044,
      17.046, 17.048000000000002, 17.05, 17.052, 17.054000000000002, 17.056,
      17.058, 17.06, 17.062, 17.064, 17.066, 17.068, 17.07, 17.072, 17.074,
      17.076, 17.078, 17.080000000000002, 17.082, 17.084, 17.086000000000002,
      17.088, 17.09, 17.092, 17.094, 17.096, 17.098, 17.1, 17.102, 17.104,
      17.106, 17.108, 17.11, 17.112000000000002, 17.114, 17.116,
      17.118000000000002, 17.12, 17.122, 17.124, 17.126, 17.128, 17.13, 17.132,
      17.134, 17.136, 17.138, 17.14, 17.142, 17.144000000000002, 17.146, 17.148,
      17.150000000000002, 17.152, 17.154, 17.156, 17.158, 17.16, 17.162, 17.164,
      17.166, 17.168, 17.17, 17.172, 17.174, 17.176000000000002, 17.178, 17.18,
      17.182, 17.184, 17.186, 17.188, 17.19, 17.192, 17.194, 17.196, 17.198,
      17.2, 17.202, 17.204, 17.206, 17.208000000000002, 17.21, 17.212, 17.214,
      17.216, 17.218, 17.22, 17.222, 17.224, 17.226, 17.228, 17.23, 17.232,
      17.234, 17.236, 17.238, 17.240000000000002, 17.242, 17.244, 17.246, 17.248,
      17.25, 17.252, 17.254, 17.256, 17.258, 17.26, 17.262, 17.264,
      17.266000000000002, 17.268, 17.27, 17.272000000000002, 17.274, 17.276,
      17.278, 17.28, 17.282, 17.284, 17.286, 17.288, 17.29, 17.292, 17.294,
      17.296, 17.298000000000002, 17.3, 17.302, 17.304000000000002, 17.306,
      17.308, 17.31, 17.312, 17.314, 17.316, 17.318, 17.32, 17.322, 17.324,
      17.326, 17.328, 17.330000000000002, 17.332, 17.334, 17.336000000000002,
      17.338, 17.34, 17.342, 17.344, 17.346, 17.348, 17.35, 17.352, 17.354,
      17.356, 17.358, 17.36, 17.362000000000002, 17.364, 17.366,
      17.368000000000002, 17.37, 17.372, 17.374, 17.376, 17.378, 17.38, 17.382,
      17.384, 17.386, 17.388, 17.39, 17.392, 17.394000000000002, 17.396, 17.398,
      17.400000000000002, 17.402, 17.404, 17.406, 17.408, 17.41, 17.412, 17.414,
      17.416, 17.418, 17.42, 17.422, 17.424, 17.426000000000002, 17.428, 17.43,
      17.432, 17.434, 17.436, 17.438, 17.44, 17.442, 17.444, 17.446, 17.448,
      17.45, 17.452, 17.454, 17.456, 17.458000000000002, 17.46, 17.462, 17.464,
      17.466, 17.468, 17.47, 17.472, 17.474, 17.476, 17.478, 17.48, 17.482,
      17.484, 17.486, 17.488, 17.490000000000002, 17.492, 17.494, 17.496, 17.498,
      17.5, 17.502, 17.504, 17.506, 17.508, 17.51, 17.512, 17.514,
      17.516000000000002, 17.518, 17.52, 17.522000000000002, 17.524, 17.526,
      17.528, 17.53, 17.532, 17.534, 17.536, 17.538, 17.54, 17.542, 17.544,
      17.546, 17.548000000000002, 17.55, 17.552, 17.554000000000002, 17.556,
      17.558, 17.56, 17.562, 17.564, 17.566, 17.568, 17.57, 17.572, 17.574,
      17.576, 17.578, 17.580000000000002, 17.582, 17.584, 17.586000000000002,
      17.588, 17.59, 17.592, 17.594, 17.596, 17.598, 17.6, 17.602, 17.604,
      17.606, 17.608, 17.61, 17.612000000000002, 17.614, 17.616,
      17.618000000000002, 17.62, 17.622, 17.624, 17.626, 17.628, 17.63, 17.632,
      17.634, 17.636, 17.638, 17.64, 17.642, 17.644000000000002, 17.646, 17.648,
      17.650000000000002, 17.652, 17.654, 17.656, 17.658, 17.66, 17.662, 17.664,
      17.666, 17.668, 17.67, 17.672, 17.674, 17.676000000000002, 17.678, 17.68,
      17.682, 17.684, 17.686, 17.688, 17.69, 17.692, 17.694, 17.696, 17.698,
      17.7, 17.702, 17.704, 17.706, 17.708000000000002, 17.71, 17.712, 17.714,
      17.716, 17.718, 17.72, 17.722, 17.724, 17.726, 17.728, 17.73, 17.732,
      17.734, 17.736, 17.738, 17.740000000000002, 17.742, 17.744, 17.746, 17.748,
      17.75, 17.752, 17.754, 17.756, 17.758, 17.76, 17.762, 17.764,
      17.766000000000002, 17.768, 17.77, 17.772000000000002, 17.774, 17.776,
      17.778, 17.78, 17.782, 17.784, 17.786, 17.788, 17.79, 17.792, 17.794,
      17.796, 17.798000000000002, 17.8, 17.802, 17.804000000000002, 17.806,
      17.808, 17.81, 17.812, 17.814, 17.816, 17.818, 17.82, 17.822, 17.824,
      17.826, 17.828, 17.830000000000002, 17.832, 17.834, 17.836000000000002,
      17.838, 17.84, 17.842, 17.844, 17.846, 17.848, 17.85, 17.852, 17.854,
      17.856, 17.858, 17.86, 17.862000000000002, 17.864, 17.866,
      17.868000000000002, 17.87, 17.872, 17.874, 17.876, 17.878, 17.88, 17.882,
      17.884, 17.886, 17.888, 17.89, 17.892, 17.894000000000002, 17.896, 17.898,
      17.900000000000002, 17.902, 17.904, 17.906, 17.908, 17.91, 17.912, 17.914,
      17.916, 17.918, 17.92, 17.922, 17.924, 17.926000000000002, 17.928, 17.93,
      17.932, 17.934, 17.936, 17.938, 17.94, 17.942, 17.944, 17.946, 17.948,
      17.95, 17.952, 17.954, 17.956, 17.958000000000002, 17.96, 17.962, 17.964,
      17.966, 17.968, 17.97, 17.972, 17.974, 17.976, 17.978, 17.98, 17.982,
      17.984, 17.986, 17.988, 17.990000000000002, 17.992, 17.994, 17.996, 17.998,
      18.0, 18.002, 18.004, 18.006, 18.008, 18.01, 18.012, 18.014,
      18.016000000000002, 18.018, 18.02, 18.022000000000002, 18.024, 18.026,
      18.028, 18.03, 18.032, 18.034, 18.036, 18.038, 18.04, 18.042, 18.044,
      18.046, 18.048000000000002, 18.05, 18.052, 18.054000000000002, 18.056,
      18.058, 18.06, 18.062, 18.064, 18.066, 18.068, 18.07, 18.072, 18.074,
      18.076, 18.078, 18.080000000000002, 18.082, 18.084, 18.086000000000002,
      18.088, 18.09, 18.092, 18.094, 18.096, 18.098, 18.1, 18.102, 18.104,
      18.106, 18.108, 18.11, 18.112000000000002, 18.114, 18.116,
      18.118000000000002, 18.12, 18.122, 18.124, 18.126, 18.128, 18.13, 18.132,
      18.134, 18.136, 18.138, 18.14, 18.142, 18.144000000000002, 18.146, 18.148,
      18.150000000000002, 18.152, 18.154, 18.156, 18.158, 18.16, 18.162, 18.164,
      18.166, 18.168, 18.17, 18.172, 18.174, 18.176000000000002, 18.178, 18.18,
      18.182, 18.184, 18.186, 18.188, 18.19, 18.192, 18.194, 18.196, 18.198,
      18.2, 18.202, 18.204, 18.206, 18.208000000000002, 18.21, 18.212, 18.214,
      18.216, 18.218, 18.22, 18.222, 18.224, 18.226, 18.228, 18.23, 18.232,
      18.234, 18.236, 18.238, 18.240000000000002, 18.242, 18.244, 18.246, 18.248,
      18.25, 18.252, 18.254, 18.256, 18.258, 18.26, 18.262, 18.264,
      18.266000000000002, 18.268, 18.27, 18.272000000000002, 18.274, 18.276,
      18.278, 18.28, 18.282, 18.284, 18.286, 18.288, 18.29, 18.292, 18.294,
      18.296, 18.298000000000002, 18.3, 18.302, 18.304000000000002, 18.306,
      18.308, 18.31, 18.312, 18.314, 18.316, 18.318, 18.32, 18.322, 18.324,
      18.326, 18.328, 18.330000000000002, 18.332, 18.334, 18.336000000000002,
      18.338, 18.34, 18.342, 18.344, 18.346, 18.348, 18.35, 18.352, 18.354,
      18.356, 18.358, 18.36, 18.362000000000002, 18.364, 18.366,
      18.368000000000002, 18.37, 18.372, 18.374, 18.376, 18.378, 18.38, 18.382,
      18.384, 18.386, 18.388, 18.39, 18.392, 18.394000000000002, 18.396, 18.398,
      18.400000000000002, 18.402, 18.404, 18.406, 18.408, 18.41, 18.412, 18.414,
      18.416, 18.418, 18.42, 18.422, 18.424, 18.426000000000002, 18.428, 18.43,
      18.432000000000002, 18.434, 18.436, 18.438, 18.44, 18.442, 18.444, 18.446,
      18.448, 18.45, 18.452, 18.454, 18.456, 18.458000000000002, 18.46, 18.462,
      18.464, 18.466, 18.468, 18.47, 18.472, 18.474, 18.476, 18.478, 18.48,
      18.482, 18.484, 18.486, 18.488, 18.490000000000002, 18.492, 18.494, 18.496,
      18.498, 18.5, 18.502, 18.504, 18.506, 18.508, 18.51, 18.512, 18.514,
      18.516000000000002, 18.518, 18.52, 18.522000000000002, 18.524, 18.526,
      18.528, 18.53, 18.532, 18.534, 18.536, 18.538, 18.54, 18.542, 18.544,
      18.546, 18.548000000000002, 18.55, 18.552, 18.554000000000002, 18.556,
      18.558, 18.56, 18.562, 18.564, 18.566, 18.568, 18.57, 18.572, 18.574,
      18.576, 18.578, 18.580000000000002, 18.582, 18.584, 18.586000000000002,
      18.588, 18.59, 18.592, 18.594, 18.596, 18.598, 18.6, 18.602, 18.604,
      18.606, 18.608, 18.61, 18.612000000000002, 18.614, 18.616,
      18.618000000000002, 18.62, 18.622, 18.624, 18.626, 18.628, 18.63, 18.632,
      18.634, 18.636, 18.638, 18.64, 18.642, 18.644000000000002, 18.646, 18.648,
      18.650000000000002, 18.652, 18.654, 18.656, 18.658, 18.66, 18.662, 18.664,
      18.666, 18.668, 18.67, 18.672, 18.674, 18.676000000000002, 18.678, 18.68,
      18.682000000000002, 18.684, 18.686, 18.688, 18.69, 18.692, 18.694, 18.696,
      18.698, 18.7, 18.702, 18.704, 18.706, 18.708000000000002, 18.71, 18.712,
      18.714, 18.716, 18.718, 18.72, 18.722, 18.724, 18.726, 18.728, 18.73,
      18.732, 18.734, 18.736, 18.738, 18.740000000000002, 18.742, 18.744, 18.746,
      18.748, 18.75, 18.752, 18.754, 18.756, 18.758, 18.76, 18.762, 18.764,
      18.766000000000002, 18.768, 18.77, 18.772000000000002, 18.774, 18.776,
      18.778, 18.78, 18.782, 18.784, 18.786, 18.788, 18.79, 18.792, 18.794,
      18.796, 18.798000000000002, 18.8, 18.802, 18.804000000000002, 18.806,
      18.808, 18.81, 18.812, 18.814, 18.816, 18.818, 18.82, 18.822, 18.824,
      18.826, 18.828, 18.830000000000002, 18.832, 18.834, 18.836000000000002,
      18.838, 18.84, 18.842, 18.844, 18.846, 18.848, 18.85, 18.852, 18.854,
      18.856, 18.858, 18.86, 18.862000000000002, 18.864, 18.866,
      18.868000000000002, 18.87, 18.872, 18.874, 18.876, 18.878, 18.88, 18.882,
      18.884, 18.886, 18.888, 18.89, 18.892, 18.894000000000002, 18.896, 18.898,
      18.900000000000002, 18.902, 18.904, 18.906, 18.908, 18.91, 18.912, 18.914,
      18.916, 18.918, 18.92, 18.922, 18.924, 18.926000000000002, 18.928, 18.93,
      18.932000000000002, 18.934, 18.936, 18.938, 18.94, 18.942, 18.944, 18.946,
      18.948, 18.95, 18.952, 18.954, 18.956, 18.958000000000002, 18.96, 18.962,
      18.964, 18.966, 18.968, 18.97, 18.972, 18.974, 18.976, 18.978, 18.98,
      18.982, 18.984, 18.986, 18.988, 18.990000000000002, 18.992, 18.994, 18.996,
      18.998, 19.0, 19.002, 19.004, 19.006, 19.008, 19.01, 19.012, 19.014,
      19.016000000000002, 19.018, 19.02, 19.022000000000002, 19.024, 19.026,
      19.028, 19.03, 19.032, 19.034, 19.036, 19.038, 19.04, 19.042, 19.044,
      19.046, 19.048000000000002, 19.05, 19.052, 19.054000000000002, 19.056,
      19.058, 19.06, 19.062, 19.064, 19.066, 19.068, 19.07, 19.072, 19.074,
      19.076, 19.078, 19.080000000000002, 19.082, 19.084, 19.086000000000002,
      19.088, 19.09, 19.092, 19.094, 19.096, 19.098, 19.1, 19.102, 19.104,
      19.106, 19.108, 19.11, 19.112000000000002, 19.114, 19.116,
      19.118000000000002, 19.12, 19.122, 19.124, 19.126, 19.128, 19.13, 19.132,
      19.134, 19.136, 19.138, 19.14, 19.142, 19.144000000000002, 19.146, 19.148,
      19.150000000000002, 19.152, 19.154, 19.156, 19.158, 19.16, 19.162, 19.164,
      19.166, 19.168, 19.17, 19.172, 19.174, 19.176000000000002, 19.178, 19.18,
      19.182000000000002, 19.184, 19.186, 19.188, 19.19, 19.192, 19.194, 19.196,
      19.198, 19.2, 19.202, 19.204, 19.206, 19.208000000000002, 19.21, 19.212,
      19.214, 19.216, 19.218, 19.22, 19.222, 19.224, 19.226, 19.228, 19.23,
      19.232, 19.234, 19.236, 19.238, 19.240000000000002, 19.242, 19.244, 19.246,
      19.248, 19.25, 19.252, 19.254, 19.256, 19.258, 19.26, 19.262, 19.264,
      19.266000000000002, 19.268, 19.27, 19.272000000000002, 19.274, 19.276,
      19.278, 19.28, 19.282, 19.284, 19.286, 19.288, 19.29, 19.292, 19.294,
      19.296, 19.298000000000002, 19.3, 19.302, 19.304000000000002, 19.306,
      19.308, 19.31, 19.312, 19.314, 19.316, 19.318, 19.32, 19.322, 19.324,
      19.326, 19.328, 19.330000000000002, 19.332, 19.334, 19.336000000000002,
      19.338, 19.34, 19.342, 19.344, 19.346, 19.348, 19.35, 19.352, 19.354,
      19.356, 19.358, 19.36, 19.362000000000002, 19.364, 19.366,
      19.368000000000002, 19.37, 19.372, 19.374, 19.376, 19.378, 19.38, 19.382,
      19.384, 19.386, 19.388, 19.39, 19.392, 19.394000000000002, 19.396, 19.398,
      19.400000000000002, 19.402, 19.404, 19.406, 19.408, 19.41, 19.412, 19.414,
      19.416, 19.418, 19.42, 19.422, 19.424, 19.426000000000002, 19.428, 19.43,
      19.432000000000002, 19.434, 19.436, 19.438, 19.44, 19.442, 19.444, 19.446,
      19.448, 19.45, 19.452, 19.454, 19.456, 19.458000000000002, 19.46, 19.462,
      19.464, 19.466, 19.468, 19.47, 19.472, 19.474, 19.476, 19.478, 19.48,
      19.482, 19.484, 19.486, 19.488, 19.490000000000002, 19.492, 19.494, 19.496,
      19.498, 19.5, 19.502, 19.504, 19.506, 19.508, 19.51, 19.512, 19.514,
      19.516000000000002, 19.518, 19.52, 19.522000000000002, 19.524, 19.526,
      19.528, 19.53, 19.532, 19.534, 19.536, 19.538, 19.54, 19.542, 19.544,
      19.546, 19.548000000000002, 19.55, 19.552, 19.554000000000002, 19.556,
      19.558, 19.56, 19.562, 19.564, 19.566, 19.568, 19.57, 19.572, 19.574,
      19.576, 19.578, 19.580000000000002, 19.582, 19.584, 19.586000000000002,
      19.588, 19.59, 19.592, 19.594, 19.596, 19.598, 19.6, 19.602, 19.604,
      19.606, 19.608, 19.61, 19.612000000000002, 19.614, 19.616,
      19.618000000000002, 19.62, 19.622, 19.624, 19.626, 19.628, 19.63, 19.632,
      19.634, 19.636, 19.638, 19.64, 19.642, 19.644000000000002, 19.646, 19.648,
      19.650000000000002, 19.652, 19.654, 19.656, 19.658, 19.66, 19.662, 19.664,
      19.666, 19.668, 19.67, 19.672, 19.674, 19.676000000000002, 19.678, 19.68,
      19.682000000000002, 19.684, 19.686, 19.688, 19.69, 19.692, 19.694, 19.696,
      19.698, 19.7, 19.702, 19.704, 19.706, 19.708000000000002, 19.71, 19.712,
      19.714, 19.716, 19.718, 19.72, 19.722, 19.724, 19.726, 19.728, 19.73,
      19.732, 19.734, 19.736, 19.738, 19.740000000000002, 19.742, 19.744, 19.746,
      19.748, 19.75, 19.752, 19.754, 19.756, 19.758, 19.76, 19.762, 19.764,
      19.766000000000002, 19.768, 19.77, 19.772000000000002, 19.774, 19.776,
      19.778, 19.78, 19.782, 19.784, 19.786, 19.788, 19.79, 19.792, 19.794,
      19.796, 19.798000000000002, 19.8, 19.802, 19.804000000000002, 19.806,
      19.808, 19.81, 19.812, 19.814, 19.816, 19.818, 19.82, 19.822, 19.824,
      19.826, 19.828, 19.830000000000002, 19.832, 19.834, 19.836000000000002,
      19.838, 19.84, 19.842, 19.844, 19.846, 19.848, 19.85, 19.852, 19.854,
      19.856, 19.858, 19.86, 19.862000000000002, 19.864, 19.866,
      19.868000000000002, 19.87, 19.872, 19.874, 19.876, 19.878, 19.88, 19.882,
      19.884, 19.886, 19.888, 19.89, 19.892, 19.894000000000002, 19.896, 19.898,
      19.900000000000002, 19.902, 19.904, 19.906, 19.908, 19.91, 19.912, 19.914,
      19.916, 19.918, 19.92, 19.922, 19.924, 19.926000000000002, 19.928, 19.93,
      19.932000000000002, 19.934, 19.936, 19.938, 19.94, 19.942, 19.944, 19.946,
      19.948, 19.95, 19.952, 19.954, 19.956, 19.958000000000002, 19.96, 19.962,
      19.964000000000002, 19.966, 19.968, 19.97, 19.972, 19.974, 19.976, 19.978,
      19.98, 19.982, 19.984, 19.986, 19.988, 19.990000000000002, 19.992, 19.994,
      19.996, 19.998, 20.0, 20.002, 20.004, 20.006, 20.008, 20.01, 20.012,
      20.014, 20.016000000000002, 20.018, 20.02, 20.022000000000002, 20.024,
      20.026, 20.028, 20.03, 20.032, 20.034, 20.036, 20.038, 20.04, 20.042,
      20.044, 20.046, 20.048000000000002, 20.05, 20.052, 20.054000000000002,
      20.056, 20.058, 20.06, 20.062, 20.064, 20.066, 20.068, 20.07, 20.072,
      20.074, 20.076, 20.078, 20.080000000000002, 20.082, 20.084,
      20.086000000000002, 20.088, 20.09, 20.092, 20.094, 20.096, 20.098, 20.1,
      20.102, 20.104, 20.106, 20.108, 20.11, 20.112000000000002, 20.114, 20.116,
      20.118000000000002, 20.12, 20.122, 20.124, 20.126, 20.128, 20.13, 20.132,
      20.134, 20.136, 20.138, 20.14, 20.142, 20.144000000000002, 20.146, 20.148,
      20.150000000000002, 20.152, 20.154, 20.156, 20.158, 20.16, 20.162, 20.164,
      20.166, 20.168, 20.17, 20.172, 20.174, 20.176000000000002, 20.178, 20.18,
      20.182000000000002, 20.184, 20.186, 20.188, 20.19, 20.192, 20.194, 20.196,
      20.198, 20.2, 20.202, 20.204, 20.206, 20.208000000000002, 20.21, 20.212,
      20.214000000000002, 20.216, 20.218, 20.22, 20.222, 20.224, 20.226, 20.228,
      20.23, 20.232, 20.234, 20.236, 20.238, 20.240000000000002, 20.242, 20.244,
      20.246, 20.248, 20.25, 20.252, 20.254, 20.256, 20.258, 20.26, 20.262,
      20.264, 20.266000000000002, 20.268, 20.27, 20.272000000000002, 20.274,
      20.276, 20.278, 20.28, 20.282, 20.284, 20.286, 20.288, 20.29, 20.292,
      20.294, 20.296, 20.298000000000002, 20.3, 20.302, 20.304000000000002,
      20.306, 20.308, 20.31, 20.312, 20.314, 20.316, 20.318, 20.32, 20.322,
      20.324, 20.326, 20.328, 20.330000000000002, 20.332, 20.334,
      20.336000000000002, 20.338, 20.34, 20.342, 20.344, 20.346, 20.348, 20.35,
      20.352, 20.354, 20.356, 20.358, 20.36, 20.362000000000002, 20.364, 20.366,
      20.368000000000002, 20.37, 20.372, 20.374, 20.376, 20.378, 20.38, 20.382,
      20.384, 20.386, 20.388, 20.39, 20.392, 20.394000000000002, 20.396, 20.398,
      20.400000000000002, 20.402, 20.404, 20.406, 20.408, 20.41, 20.412, 20.414,
      20.416, 20.418, 20.42, 20.422, 20.424, 20.426000000000002, 20.428, 20.43,
      20.432000000000002, 20.434, 20.436, 20.438, 20.44, 20.442, 20.444, 20.446,
      20.448, 20.45, 20.452, 20.454, 20.456, 20.458000000000002, 20.46, 20.462,
      20.464000000000002, 20.466, 20.468, 20.47, 20.472, 20.474, 20.476, 20.478,
      20.48, 20.482, 20.484, 20.486, 20.488, 20.490000000000002, 20.492, 20.494,
      20.496, 20.498, 20.5, 20.502, 20.504, 20.506, 20.508, 20.51, 20.512,
      20.514, 20.516000000000002, 20.518, 20.52, 20.522000000000002, 20.524,
      20.526, 20.528, 20.53, 20.532, 20.534, 20.536, 20.538, 20.54, 20.542,
      20.544, 20.546, 20.548000000000002, 20.55, 20.552, 20.554000000000002,
      20.556, 20.558, 20.56, 20.562, 20.564, 20.566, 20.568, 20.57, 20.572,
      20.574, 20.576, 20.578, 20.580000000000002, 20.582, 20.584,
      20.586000000000002, 20.588, 20.59, 20.592, 20.594, 20.596, 20.598, 20.6,
      20.602, 20.604, 20.606, 20.608, 20.61, 20.612000000000002, 20.614, 20.616,
      20.618000000000002, 20.62, 20.622, 20.624, 20.626, 20.628, 20.63, 20.632,
      20.634, 20.636, 20.638, 20.64, 20.642, 20.644000000000002, 20.646, 20.648,
      20.650000000000002, 20.652, 20.654, 20.656, 20.658, 20.66, 20.662, 20.664,
      20.666, 20.668, 20.67, 20.672, 20.674, 20.676000000000002, 20.678, 20.68,
      20.682000000000002, 20.684, 20.686, 20.688, 20.69, 20.692, 20.694, 20.696,
      20.698, 20.7, 20.702, 20.704, 20.706, 20.708000000000002, 20.71, 20.712,
      20.714000000000002, 20.716, 20.718, 20.72, 20.722, 20.724, 20.726, 20.728,
      20.73, 20.732, 20.734, 20.736, 20.738, 20.740000000000002, 20.742, 20.744,
      20.746, 20.748, 20.75, 20.752, 20.754, 20.756, 20.758, 20.76, 20.762,
      20.764, 20.766000000000002, 20.768, 20.77, 20.772000000000002, 20.774,
      20.776, 20.778, 20.78, 20.782, 20.784, 20.786, 20.788, 20.79, 20.792,
      20.794, 20.796, 20.798000000000002, 20.8, 20.802, 20.804000000000002,
      20.806, 20.808, 20.81, 20.812, 20.814, 20.816, 20.818, 20.82, 20.822,
      20.824, 20.826, 20.828, 20.830000000000002, 20.832, 20.834,
      20.836000000000002, 20.838, 20.84, 20.842, 20.844, 20.846, 20.848, 20.85,
      20.852, 20.854, 20.856, 20.858, 20.86, 20.862000000000002, 20.864, 20.866,
      20.868000000000002, 20.87, 20.872, 20.874, 20.876, 20.878, 20.88, 20.882,
      20.884, 20.886, 20.888, 20.89, 20.892, 20.894000000000002, 20.896, 20.898,
      20.900000000000002, 20.902, 20.904, 20.906, 20.908, 20.91, 20.912, 20.914,
      20.916, 20.918, 20.92, 20.922, 20.924, 20.926000000000002, 20.928, 20.93,
      20.932000000000002, 20.934, 20.936, 20.938, 20.94, 20.942, 20.944, 20.946,
      20.948, 20.95, 20.952, 20.954, 20.956, 20.958000000000002, 20.96, 20.962,
      20.964000000000002, 20.966, 20.968, 20.97, 20.972, 20.974, 20.976, 20.978,
      20.98, 20.982, 20.984, 20.986, 20.988, 20.990000000000002, 20.992, 20.994,
      20.996, 20.998, 21.0, 21.002, 21.004, 21.006, 21.008, 21.01, 21.012,
      21.014, 21.016000000000002, 21.018, 21.02, 21.022000000000002, 21.024,
      21.026, 21.028, 21.03, 21.032, 21.034, 21.036, 21.038, 21.04, 21.042,
      21.044, 21.046, 21.048000000000002, 21.05, 21.052, 21.054000000000002,
      21.056, 21.058, 21.06, 21.062, 21.064, 21.066, 21.068, 21.07, 21.072,
      21.074, 21.076, 21.078, 21.080000000000002, 21.082, 21.084,
      21.086000000000002, 21.088, 21.09, 21.092, 21.094, 21.096, 21.098, 21.1,
      21.102, 21.104, 21.106, 21.108, 21.11, 21.112000000000002, 21.114, 21.116,
      21.118000000000002, 21.12, 21.122, 21.124, 21.126, 21.128, 21.13, 21.132,
      21.134, 21.136, 21.138, 21.14, 21.142, 21.144000000000002, 21.146, 21.148,
      21.150000000000002, 21.152, 21.154, 21.156, 21.158, 21.16, 21.162, 21.164,
      21.166, 21.168, 21.17, 21.172, 21.174, 21.176000000000002, 21.178, 21.18,
      21.182000000000002, 21.184, 21.186, 21.188, 21.19, 21.192, 21.194, 21.196,
      21.198, 21.2, 21.202, 21.204, 21.206, 21.208000000000002, 21.21, 21.212,
      21.214000000000002, 21.216, 21.218, 21.22, 21.222, 21.224, 21.226, 21.228,
      21.23, 21.232, 21.234, 21.236, 21.238, 21.240000000000002, 21.242, 21.244,
      21.246000000000002, 21.248, 21.25, 21.252, 21.254, 21.256, 21.258, 21.26,
      21.262, 21.264, 21.266000000000002, 21.268, 21.27, 21.272000000000002,
      21.274, 21.276, 21.278, 21.28, 21.282, 21.284, 21.286, 21.288, 21.29,
      21.292, 21.294, 21.296, 21.298000000000002, 21.3, 21.302,
      21.304000000000002, 21.306, 21.308, 21.31, 21.312, 21.314, 21.316, 21.318,
      21.32, 21.322, 21.324, 21.326, 21.328, 21.330000000000002, 21.332, 21.334,
      21.336000000000002, 21.338, 21.34, 21.342, 21.344, 21.346, 21.348, 21.35,
      21.352, 21.354, 21.356, 21.358, 21.36, 21.362000000000002, 21.364, 21.366,
      21.368000000000002, 21.37, 21.372, 21.374, 21.376, 21.378, 21.38, 21.382,
      21.384, 21.386, 21.388, 21.39, 21.392, 21.394000000000002, 21.396, 21.398,
      21.400000000000002, 21.402, 21.404, 21.406, 21.408, 21.41, 21.412, 21.414,
      21.416, 21.418, 21.42, 21.422, 21.424, 21.426000000000002, 21.428, 21.43,
      21.432000000000002, 21.434, 21.436, 21.438, 21.44, 21.442, 21.444, 21.446,
      21.448, 21.45, 21.452, 21.454, 21.456, 21.458000000000002, 21.46, 21.462,
      21.464000000000002, 21.466, 21.468, 21.47, 21.472, 21.474, 21.476, 21.478,
      21.48, 21.482, 21.484, 21.486, 21.488, 21.490000000000002, 21.492, 21.494,
      21.496000000000002, 21.498, 21.5, 21.502, 21.504, 21.506, 21.508, 21.51,
      21.512, 21.514, 21.516000000000002, 21.518, 21.52, 21.522000000000002,
      21.524, 21.526, 21.528, 21.53, 21.532, 21.534, 21.536, 21.538, 21.54,
      21.542, 21.544, 21.546, 21.548000000000002, 21.55, 21.552,
      21.554000000000002, 21.556, 21.558, 21.56, 21.562, 21.564, 21.566, 21.568,
      21.57, 21.572, 21.574, 21.576, 21.578, 21.580000000000002, 21.582, 21.584,
      21.586000000000002, 21.588, 21.59, 21.592, 21.594, 21.596, 21.598, 21.6,
      21.602, 21.604, 21.606, 21.608, 21.61, 21.612000000000002, 21.614, 21.616,
      21.618000000000002, 21.62, 21.622, 21.624, 21.626, 21.628, 21.63, 21.632,
      21.634, 21.636, 21.638, 21.64, 21.642, 21.644000000000002, 21.646, 21.648,
      21.650000000000002, 21.652, 21.654, 21.656, 21.658, 21.66, 21.662, 21.664,
      21.666, 21.668, 21.67, 21.672, 21.674, 21.676000000000002, 21.678, 21.68,
      21.682000000000002, 21.684, 21.686, 21.688, 21.69, 21.692, 21.694, 21.696,
      21.698, 21.7, 21.702, 21.704, 21.706, 21.708000000000002, 21.71, 21.712,
      21.714000000000002, 21.716, 21.718, 21.72, 21.722, 21.724, 21.726, 21.728,
      21.73, 21.732, 21.734, 21.736, 21.738, 21.740000000000002, 21.742, 21.744,
      21.746000000000002, 21.748, 21.75, 21.752, 21.754, 21.756, 21.758, 21.76,
      21.762, 21.764, 21.766000000000002, 21.768, 21.77, 21.772000000000002,
      21.774, 21.776, 21.778, 21.78, 21.782, 21.784, 21.786, 21.788, 21.79,
      21.792, 21.794, 21.796, 21.798000000000002, 21.8, 21.802,
      21.804000000000002, 21.806, 21.808, 21.81, 21.812, 21.814, 21.816, 21.818,
      21.82, 21.822, 21.824, 21.826, 21.828, 21.830000000000002, 21.832, 21.834,
      21.836000000000002, 21.838, 21.84, 21.842, 21.844, 21.846, 21.848, 21.85,
      21.852, 21.854, 21.856, 21.858, 21.86, 21.862000000000002, 21.864, 21.866,
      21.868000000000002, 21.87, 21.872, 21.874, 21.876, 21.878, 21.88, 21.882,
      21.884, 21.886, 21.888, 21.89, 21.892, 21.894000000000002, 21.896, 21.898,
      21.900000000000002, 21.902, 21.904, 21.906, 21.908, 21.91, 21.912, 21.914,
      21.916, 21.918, 21.92, 21.922, 21.924, 21.926000000000002, 21.928, 21.93,
      21.932000000000002, 21.934, 21.936, 21.938, 21.94, 21.942, 21.944, 21.946,
      21.948, 21.95, 21.952, 21.954, 21.956, 21.958000000000002, 21.96, 21.962,
      21.964000000000002, 21.966, 21.968, 21.97, 21.972, 21.974, 21.976, 21.978,
      21.98, 21.982, 21.984, 21.986, 21.988, 21.990000000000002, 21.992, 21.994,
      21.996000000000002, 21.998, 22.0, 22.002, 22.004, 22.006, 22.008, 22.01,
      22.012, 22.014, 22.016000000000002, 22.018, 22.02, 22.022000000000002,
      22.024, 22.026, 22.028, 22.03, 22.032, 22.034, 22.036, 22.038, 22.04,
      22.042, 22.044, 22.046, 22.048000000000002, 22.05, 22.052,
      22.054000000000002, 22.056, 22.058, 22.06, 22.062, 22.064, 22.066, 22.068,
      22.07, 22.072, 22.074, 22.076, 22.078, 22.080000000000002, 22.082, 22.084,
      22.086000000000002, 22.088, 22.09, 22.092, 22.094, 22.096, 22.098, 22.1,
      22.102, 22.104, 22.106, 22.108, 22.11, 22.112000000000002, 22.114, 22.116,
      22.118000000000002, 22.12, 22.122, 22.124, 22.126, 22.128, 22.13, 22.132,
      22.134, 22.136, 22.138, 22.14, 22.142, 22.144000000000002, 22.146, 22.148,
      22.150000000000002, 22.152, 22.154, 22.156, 22.158, 22.16, 22.162, 22.164,
      22.166, 22.168, 22.17, 22.172, 22.174, 22.176000000000002, 22.178, 22.18,
      22.182000000000002, 22.184, 22.186, 22.188, 22.19, 22.192, 22.194, 22.196,
      22.198, 22.2, 22.202, 22.204, 22.206, 22.208000000000002, 22.21, 22.212,
      22.214000000000002, 22.216, 22.218, 22.22, 22.222, 22.224, 22.226, 22.228,
      22.23, 22.232, 22.234, 22.236, 22.238, 22.240000000000002, 22.242, 22.244,
      22.246000000000002, 22.248, 22.25, 22.252, 22.254, 22.256, 22.258, 22.26,
      22.262, 22.264, 22.266000000000002, 22.268, 22.27, 22.272000000000002,
      22.274, 22.276, 22.278, 22.28, 22.282, 22.284, 22.286, 22.288, 22.29,
      22.292, 22.294, 22.296, 22.298000000000002, 22.3, 22.302,
      22.304000000000002, 22.306, 22.308, 22.31, 22.312, 22.314, 22.316, 22.318,
      22.32, 22.322, 22.324, 22.326, 22.328, 22.330000000000002, 22.332, 22.334,
      22.336000000000002, 22.338, 22.34, 22.342, 22.344, 22.346, 22.348, 22.35,
      22.352, 22.354, 22.356, 22.358, 22.36, 22.362000000000002, 22.364, 22.366,
      22.368000000000002, 22.37, 22.372, 22.374, 22.376, 22.378, 22.38, 22.382,
      22.384, 22.386, 22.388, 22.39, 22.392, 22.394000000000002, 22.396, 22.398,
      22.400000000000002, 22.402, 22.404, 22.406, 22.408, 22.41, 22.412, 22.414,
      22.416, 22.418, 22.42, 22.422, 22.424, 22.426000000000002, 22.428, 22.43,
      22.432000000000002, 22.434, 22.436, 22.438, 22.44, 22.442, 22.444, 22.446,
      22.448, 22.45, 22.452, 22.454, 22.456, 22.458000000000002, 22.46, 22.462,
      22.464000000000002, 22.466, 22.468, 22.47, 22.472, 22.474, 22.476, 22.478,
      22.48, 22.482, 22.484, 22.486, 22.488, 22.490000000000002, 22.492, 22.494,
      22.496000000000002, 22.498, 22.5, 22.502, 22.503999999999998, 22.506,
      22.508, 22.509999999999998, 22.512, 22.514, 22.516, 22.518, 22.52, 22.522,
      22.524, 22.526, 22.528, 22.53, 22.532, 22.534, 22.535999999999998, 22.538,
      22.54, 22.541999999999998, 22.544, 22.546, 22.548, 22.55, 22.552, 22.554,
      22.556, 22.558, 22.56, 22.562, 22.564, 22.566, 22.567999999999998, 22.57,
      22.572, 22.573999999999998, 22.576, 22.578, 22.58, 22.582, 22.584, 22.586,
      22.588, 22.59, 22.592, 22.594, 22.596, 22.598, 22.599999999999998, 22.602,
      22.604, 22.605999999999998, 22.608, 22.61, 22.612, 22.614, 22.616, 22.618,
      22.62, 22.622, 22.624, 22.626, 22.628, 22.63, 22.631999999999998, 22.634,
      22.636, 22.637999999999998, 22.64, 22.642, 22.644, 22.646, 22.648, 22.65,
      22.652, 22.654, 22.656, 22.658, 22.66, 22.662, 22.663999999999998, 22.666,
      22.668, 22.669999999999998, 22.672, 22.674, 22.676, 22.678, 22.68, 22.682,
      22.684, 22.686, 22.688, 22.69, 22.692, 22.694, 22.695999999999998, 22.698,
      22.7, 22.701999999999998, 22.704, 22.706, 22.708, 22.71, 22.712, 22.714,
      22.716, 22.718, 22.72, 22.722, 22.724, 22.726, 22.727999999999998, 22.73,
      22.732, 22.733999999999998, 22.736, 22.738, 22.74, 22.742, 22.744, 22.746,
      22.748, 22.75, 22.752, 22.753999999999998, 22.756, 22.758,
      22.759999999999998, 22.762, 22.764, 22.766, 22.768, 22.77, 22.772, 22.774,
      22.776, 22.778, 22.78, 22.782, 22.784, 22.785999999999998, 22.788, 22.79,
      22.791999999999998, 22.794, 22.796, 22.798, 22.8, 22.802, 22.804, 22.806,
      22.808, 22.81, 22.812, 22.814, 22.816, 22.817999999999998, 22.82, 22.822,
      22.823999999999998, 22.826, 22.828, 22.83, 22.832, 22.834, 22.836, 22.838,
      22.84, 22.842, 22.844, 22.846, 22.848, 22.849999999999998, 22.852, 22.854,
      22.855999999999998, 22.858, 22.86, 22.862, 22.864, 22.866, 22.868, 22.87,
      22.872, 22.874, 22.876, 22.878, 22.88, 22.881999999999998, 22.884, 22.886,
      22.887999999999998, 22.89, 22.892, 22.894, 22.896, 22.898, 22.9, 22.902,
      22.904, 22.906, 22.908, 22.91, 22.912, 22.913999999999998, 22.916, 22.918,
      22.919999999999998, 22.922, 22.924, 22.926, 22.928, 22.93, 22.932, 22.934,
      22.936, 22.938, 22.94, 22.942, 22.944, 22.945999999999998, 22.948, 22.95,
      22.951999999999998, 22.954, 22.956, 22.958, 22.96, 22.962, 22.964, 22.966,
      22.968, 22.97, 22.972, 22.974, 22.976, 22.977999999999998, 22.98, 22.982,
      22.983999999999998, 22.986, 22.988, 22.99, 22.992, 22.994, 22.996, 22.998,
      23.0, 23.002, 23.003999999999998, 23.006, 23.008, 23.009999999999998,
      23.012, 23.014, 23.016, 23.018, 23.02, 23.022, 23.024, 23.026, 23.028,
      23.03, 23.032, 23.034, 23.035999999999998, 23.038, 23.04,
      23.041999999999998, 23.044, 23.046, 23.048, 23.05, 23.052, 23.054, 23.056,
      23.058, 23.06, 23.062, 23.064, 23.066, 23.067999999999998, 23.07, 23.072,
      23.073999999999998, 23.076, 23.078, 23.08, 23.082, 23.084, 23.086, 23.088,
      23.09, 23.092, 23.094, 23.096, 23.098, 23.099999999999998, 23.102, 23.104,
      23.105999999999998, 23.108, 23.11, 23.112, 23.114, 23.116, 23.118, 23.12,
      23.122, 23.124, 23.126, 23.128, 23.13, 23.131999999999998, 23.134, 23.136,
      23.137999999999998, 23.14, 23.142, 23.144, 23.146, 23.148, 23.15, 23.152,
      23.154, 23.156, 23.158, 23.16, 23.162, 23.163999999999998, 23.166, 23.168,
      23.169999999999998, 23.172, 23.174, 23.176, 23.178, 23.18, 23.182, 23.184,
      23.186, 23.188, 23.19, 23.192, 23.194, 23.195999999999998, 23.198, 23.2,
      23.201999999999998, 23.204, 23.206, 23.208, 23.21, 23.212, 23.214, 23.216,
      23.218, 23.22, 23.222, 23.224, 23.226, 23.227999999999998, 23.23, 23.232,
      23.233999999999998, 23.236, 23.238, 23.24, 23.242, 23.244, 23.246, 23.248,
      23.25, 23.252, 23.253999999999998, 23.256, 23.258, 23.259999999999998,
      23.262, 23.264, 23.266, 23.268, 23.27, 23.272, 23.274, 23.276, 23.278,
      23.28, 23.282, 23.284, 23.285999999999998, 23.288, 23.29,
      23.291999999999998, 23.294, 23.296, 23.298, 23.3, 23.302, 23.304, 23.306,
      23.308, 23.31, 23.312, 23.314, 23.316, 23.317999999999998, 23.32, 23.322,
      23.323999999999998, 23.326, 23.328, 23.33, 23.332, 23.334, 23.336, 23.338,
      23.34, 23.342, 23.344, 23.346, 23.348, 23.349999999999998, 23.352, 23.354,
      23.355999999999998, 23.358, 23.36, 23.362, 23.364, 23.366, 23.368, 23.37,
      23.372, 23.374, 23.376, 23.378, 23.38, 23.381999999999998, 23.384, 23.386,
      23.387999999999998, 23.39, 23.392, 23.394, 23.396, 23.398, 23.4, 23.402,
      23.404, 23.406, 23.408, 23.41, 23.412, 23.413999999999998, 23.416, 23.418,
      23.419999999999998, 23.422, 23.424, 23.426, 23.428, 23.43, 23.432, 23.434,
      23.436, 23.438, 23.44, 23.442, 23.444, 23.445999999999998, 23.448, 23.45,
      23.451999999999998, 23.454, 23.456, 23.458, 23.46, 23.462, 23.464, 23.466,
      23.468, 23.47, 23.472, 23.474, 23.476, 23.477999999999998, 23.48, 23.482,
      23.483999999999998, 23.486, 23.488, 23.49, 23.492, 23.494, 23.496, 23.498,
      23.5, 23.502, 23.503999999999998, 23.506, 23.508, 23.509999999999998,
      23.512, 23.514, 23.516, 23.518, 23.52, 23.522, 23.524, 23.526, 23.528,
      23.53, 23.532, 23.534, 23.535999999999998, 23.538, 23.54,
      23.541999999999998, 23.544, 23.546, 23.548, 23.55, 23.552, 23.554, 23.556,
      23.558, 23.56, 23.562, 23.564, 23.566, 23.567999999999998, 23.57, 23.572,
      23.573999999999998, 23.576, 23.578, 23.58, 23.582, 23.584, 23.586, 23.588,
      23.59, 23.592, 23.594, 23.596, 23.598, 23.599999999999998, 23.602, 23.604,
      23.605999999999998, 23.608, 23.61, 23.612, 23.614, 23.616, 23.618, 23.62,
      23.622, 23.624, 23.626, 23.628, 23.63, 23.631999999999998, 23.634, 23.636,
      23.637999999999998, 23.64, 23.642, 23.644, 23.646, 23.648, 23.65, 23.652,
      23.654, 23.656, 23.658, 23.66, 23.662, 23.663999999999998, 23.666, 23.668,
      23.669999999999998, 23.672, 23.674, 23.676, 23.678, 23.68, 23.682, 23.684,
      23.686, 23.688, 23.69, 23.692, 23.694, 23.695999999999998, 23.698, 23.7,
      23.701999999999998, 23.704, 23.706, 23.708, 23.71, 23.712, 23.714, 23.716,
      23.718, 23.72, 23.722, 23.724, 23.726, 23.727999999999998, 23.73, 23.732,
      23.733999999999998, 23.736, 23.738, 23.74, 23.742, 23.744, 23.746, 23.748,
      23.75, 23.752, 23.753999999999998, 23.756, 23.758, 23.759999999999998,
      23.762, 23.764, 23.766, 23.768, 23.77, 23.772, 23.774, 23.776, 23.778,
      23.78, 23.782, 23.784, 23.785999999999998, 23.788, 23.79,
      23.791999999999998, 23.794, 23.796, 23.798, 23.8, 23.802, 23.804, 23.806,
      23.808, 23.81, 23.812, 23.814, 23.816, 23.817999999999998, 23.82, 23.822,
      23.823999999999998, 23.826, 23.828, 23.83, 23.832, 23.834, 23.836, 23.838,
      23.84, 23.842, 23.844, 23.846, 23.848, 23.849999999999998, 23.852, 23.854,
      23.855999999999998, 23.858, 23.86, 23.862, 23.864, 23.866, 23.868, 23.87,
      23.872, 23.874, 23.876, 23.878, 23.88, 23.881999999999998, 23.884, 23.886,
      23.887999999999998, 23.89, 23.892, 23.894, 23.896, 23.898, 23.9, 23.902,
      23.904, 23.906, 23.908, 23.91, 23.912, 23.913999999999998, 23.916, 23.918,
      23.919999999999998, 23.922, 23.924, 23.926, 23.928, 23.93, 23.932, 23.934,
      23.936, 23.938, 23.94, 23.942, 23.944, 23.945999999999998, 23.948, 23.95,
      23.951999999999998, 23.954, 23.956, 23.958, 23.96, 23.962, 23.964, 23.966,
      23.968, 23.97, 23.972, 23.974, 23.976, 23.977999999999998, 23.98, 23.982,
      23.983999999999998, 23.986, 23.988, 23.99, 23.992, 23.994, 23.996, 23.998,
      24.0, 24.002, 24.004, 24.006, 24.008, 24.009999999999998, 24.012, 24.014,
      24.016, 24.018, 24.02, 24.022, 24.024, 24.026, 24.028, 24.03, 24.032,
      24.034, 24.035999999999998, 24.038, 24.04, 24.041999999999998, 24.044,
      24.046, 24.048, 24.05, 24.052, 24.054, 24.056, 24.058, 24.06, 24.062,
      24.064, 24.066, 24.067999999999998, 24.07, 24.072, 24.073999999999998,
      24.076, 24.078, 24.08, 24.082, 24.084, 24.086, 24.088, 24.09, 24.092,
      24.094, 24.096, 24.098, 24.099999999999998, 24.102, 24.104,
      24.105999999999998, 24.108, 24.11, 24.112, 24.114, 24.116, 24.118, 24.12,
      24.122, 24.124, 24.126, 24.128, 24.13, 24.131999999999998, 24.134, 24.136,
      24.137999999999998, 24.14, 24.142, 24.144, 24.146, 24.148, 24.15, 24.152,
      24.154, 24.156, 24.158, 24.16, 24.162, 24.163999999999998, 24.166, 24.168,
      24.169999999999998, 24.172, 24.174, 24.176, 24.178, 24.18, 24.182, 24.184,
      24.186, 24.188, 24.19, 24.192, 24.194, 24.195999999999998, 24.198, 24.2,
      24.201999999999998, 24.204, 24.206, 24.208, 24.21, 24.212, 24.214, 24.216,
      24.218, 24.22, 24.222, 24.224, 24.226, 24.227999999999998, 24.23, 24.232,
      24.233999999999998, 24.236, 24.238, 24.24, 24.242, 24.244, 24.246, 24.248,
      24.25, 24.252, 24.254, 24.256, 24.258, 24.259999999999998, 24.262, 24.264,
      24.266, 24.268, 24.27, 24.272, 24.274, 24.276, 24.278, 24.28, 24.282,
      24.284, 24.285999999999998, 24.288, 24.29, 24.291999999999998, 24.294,
      24.296, 24.298, 24.3, 24.302, 24.304, 24.306, 24.308, 24.31, 24.312,
      24.314, 24.316, 24.317999999999998, 24.32, 24.322, 24.323999999999998,
      24.326, 24.328, 24.33, 24.332, 24.334, 24.336, 24.338, 24.34, 24.342,
      24.344, 24.346, 24.348, 24.349999999999998, 24.352, 24.354,
      24.355999999999998, 24.358, 24.36, 24.362, 24.364, 24.366, 24.368, 24.37,
      24.372, 24.374, 24.376, 24.378, 24.38, 24.381999999999998, 24.384, 24.386,
      24.387999999999998, 24.39, 24.392, 24.394, 24.396, 24.398, 24.4, 24.402,
      24.404, 24.406, 24.408, 24.41, 24.412, 24.413999999999998, 24.416, 24.418,
      24.419999999999998, 24.422, 24.424, 24.426, 24.428, 24.43, 24.432, 24.434,
      24.436, 24.438, 24.44, 24.442, 24.444, 24.445999999999998, 24.448, 24.45,
      24.451999999999998, 24.454, 24.456, 24.458, 24.46, 24.462, 24.464, 24.466,
      24.468, 24.47, 24.472, 24.474, 24.476, 24.477999999999998, 24.48, 24.482,
      24.483999999999998, 24.486, 24.488, 24.49, 24.492, 24.494, 24.496, 24.498,
      24.5, 24.502, 24.504, 24.506, 24.508, 24.509999999999998, 24.512, 24.514,
      24.516, 24.518, 24.52, 24.522, 24.524, 24.526, 24.528, 24.53, 24.532,
      24.534, 24.535999999999998, 24.538, 24.54, 24.541999999999998, 24.544,
      24.546, 24.548, 24.55, 24.552, 24.554, 24.556, 24.558, 24.56, 24.562,
      24.564, 24.566, 24.567999999999998, 24.57, 24.572, 24.573999999999998,
      24.576, 24.578, 24.58, 24.582, 24.584, 24.586, 24.588, 24.59, 24.592,
      24.594, 24.596, 24.598, 24.599999999999998, 24.602, 24.604,
      24.605999999999998, 24.608, 24.61, 24.612, 24.614, 24.616, 24.618, 24.62,
      24.622, 24.624, 24.626, 24.628, 24.63, 24.631999999999998, 24.634, 24.636,
      24.637999999999998, 24.64, 24.642, 24.644, 24.646, 24.648, 24.65, 24.652,
      24.654, 24.656, 24.658, 24.66, 24.662, 24.663999999999998, 24.666, 24.668,
      24.669999999999998, 24.672, 24.674, 24.676, 24.678, 24.68, 24.682, 24.684,
      24.686, 24.688, 24.69, 24.692, 24.694, 24.695999999999998, 24.698, 24.7,
      24.701999999999998, 24.704, 24.706, 24.708, 24.71, 24.712, 24.714, 24.716,
      24.718, 24.72, 24.722, 24.724, 24.726, 24.727999999999998, 24.73, 24.732,
      24.733999999999998, 24.736, 24.738, 24.74, 24.742, 24.744, 24.746, 24.748,
      24.75, 24.752, 24.754, 24.756, 24.758, 24.759999999999998, 24.762, 24.764,
      24.766, 24.768, 24.77, 24.772, 24.774, 24.776, 24.778, 24.78, 24.782,
      24.784, 24.785999999999998, 24.788, 24.79, 24.791999999999998, 24.794,
      24.796, 24.798, 24.8, 24.802, 24.804, 24.806, 24.808, 24.81, 24.812,
      24.814, 24.816, 24.817999999999998, 24.82, 24.822, 24.823999999999998,
      24.826, 24.828, 24.83, 24.832, 24.834, 24.836, 24.838, 24.84, 24.842,
      24.844, 24.846, 24.848, 24.849999999999998, 24.852, 24.854,
      24.855999999999998, 24.858, 24.86, 24.862, 24.864, 24.866, 24.868, 24.87,
      24.872, 24.874, 24.876, 24.878, 24.88, 24.881999999999998, 24.884, 24.886,
      24.887999999999998, 24.89, 24.892, 24.894, 24.896, 24.898, 24.9, 24.902,
      24.904, 24.906, 24.908, 24.91, 24.912, 24.913999999999998, 24.916, 24.918,
      24.919999999999998, 24.922, 24.924, 24.926, 24.928, 24.93, 24.932, 24.934,
      24.936, 24.938, 24.94, 24.942, 24.944, 24.945999999999998, 24.948, 24.95,
      24.951999999999998, 24.954, 24.956, 24.958, 24.96, 24.962, 24.964, 24.966,
      24.968, 24.97, 24.972, 24.974, 24.976, 24.977999999999998, 24.98, 24.982,
      24.983999999999998, 24.986, 24.988, 24.99, 24.992, 24.994, 24.996, 24.998,
      25.0, 25.002, 25.004, 25.006, 25.008, 25.009999999999998, 25.012, 25.014,
      25.016, 25.018, 25.02, 25.022, 25.024, 25.026, 25.028, 25.03, 25.032,
      25.034, 25.035999999999998, 25.038, 25.04, 25.041999999999998, 25.044,
      25.046, 25.048, 25.05, 25.052, 25.054, 25.056, 25.058, 25.06, 25.062,
      25.064, 25.066, 25.067999999999998, 25.07, 25.072, 25.073999999999998,
      25.076, 25.078, 25.08, 25.082, 25.084, 25.086, 25.088, 25.09, 25.092,
      25.094, 25.096, 25.098, 25.099999999999998, 25.102, 25.104,
      25.105999999999998, 25.108, 25.11, 25.112, 25.114, 25.116, 25.118, 25.12,
      25.122, 25.124, 25.126, 25.128, 25.13, 25.131999999999998, 25.134, 25.136,
      25.137999999999998, 25.14, 25.142, 25.144, 25.146, 25.148, 25.15, 25.152,
      25.154, 25.156, 25.158, 25.16, 25.162, 25.163999999999998, 25.166, 25.168,
      25.169999999999998, 25.172, 25.174, 25.176, 25.178, 25.18, 25.182, 25.184,
      25.186, 25.188, 25.19, 25.192, 25.194, 25.195999999999998, 25.198, 25.2,
      25.201999999999998, 25.204, 25.206, 25.208, 25.21, 25.212, 25.214, 25.216,
      25.218, 25.22, 25.222, 25.224, 25.226, 25.227999999999998, 25.23, 25.232,
      25.233999999999998, 25.236, 25.238, 25.24, 25.242, 25.244, 25.246, 25.248,
      25.25, 25.252, 25.254, 25.256, 25.258, 25.259999999999998, 25.262, 25.264,
      25.266, 25.268, 25.27, 25.272, 25.274, 25.276, 25.278, 25.28, 25.282,
      25.284, 25.286, 25.288, 25.29, 25.291999999999998, 25.294, 25.296, 25.298,
      25.3, 25.302, 25.304, 25.306, 25.308, 25.31, 25.312, 25.314, 25.316,
      25.317999999999998, 25.32, 25.322, 25.323999999999998, 25.326, 25.328,
      25.33, 25.332, 25.334, 25.336, 25.338, 25.34, 25.342, 25.344, 25.346,
      25.348, 25.349999999999998, 25.352, 25.354, 25.355999999999998, 25.358,
      25.36, 25.362, 25.364, 25.366, 25.368, 25.37, 25.372, 25.374, 25.376,
      25.378, 25.38, 25.381999999999998, 25.384, 25.386, 25.387999999999998,
      25.39, 25.392, 25.394, 25.396, 25.398, 25.4, 25.402, 25.404, 25.406,
      25.408, 25.41, 25.412, 25.413999999999998, 25.416, 25.418,
      25.419999999999998, 25.422, 25.424, 25.426, 25.428, 25.43, 25.432, 25.434,
      25.436, 25.438, 25.44, 25.442, 25.444, 25.445999999999998, 25.448, 25.45,
      25.451999999999998, 25.454, 25.456, 25.458, 25.46, 25.462, 25.464, 25.466,
      25.468, 25.47, 25.472, 25.474, 25.476, 25.477999999999998, 25.48, 25.482,
      25.483999999999998, 25.486, 25.488, 25.49, 25.492, 25.494, 25.496, 25.498,
      25.5, 25.502, 25.504, 25.506, 25.508, 25.509999999999998, 25.512, 25.514,
      25.516, 25.518, 25.52, 25.522, 25.524, 25.526, 25.528, 25.53, 25.532,
      25.534, 25.536, 25.538, 25.54, 25.541999999999998, 25.544, 25.546, 25.548,
      25.55, 25.552, 25.554, 25.556, 25.558, 25.56, 25.562, 25.564, 25.566,
      25.567999999999998, 25.57, 25.572, 25.573999999999998, 25.576, 25.578,
      25.58, 25.582, 25.584, 25.586, 25.588, 25.59, 25.592, 25.594, 25.596,
      25.598, 25.599999999999998, 25.602, 25.604, 25.605999999999998, 25.608,
      25.61, 25.612, 25.614, 25.616, 25.618, 25.62, 25.622, 25.624, 25.626,
      25.628, 25.63, 25.631999999999998, 25.634, 25.636, 25.637999999999998,
      25.64, 25.642, 25.644, 25.646, 25.648, 25.65, 25.652, 25.654, 25.656,
      25.658, 25.66, 25.662, 25.663999999999998, 25.666, 25.668,
      25.669999999999998, 25.672, 25.674, 25.676, 25.678, 25.68, 25.682, 25.684,
      25.686, 25.688, 25.69, 25.692, 25.694, 25.695999999999998, 25.698, 25.7,
      25.701999999999998, 25.704, 25.706, 25.708, 25.71, 25.712, 25.714, 25.716,
      25.718, 25.72, 25.722, 25.724, 25.726, 25.727999999999998, 25.73, 25.732,
      25.733999999999998, 25.736, 25.738, 25.74, 25.742, 25.744, 25.746, 25.748,
      25.75, 25.752, 25.754, 25.756, 25.758, 25.759999999999998, 25.762, 25.764,
      25.766, 25.768, 25.77, 25.772, 25.774, 25.776, 25.778, 25.78, 25.782,
      25.784, 25.786, 25.788, 25.79, 25.791999999999998, 25.794, 25.796, 25.798,
      25.8, 25.802, 25.804, 25.806, 25.808, 25.81, 25.812, 25.814, 25.816,
      25.817999999999998, 25.82, 25.822, 25.823999999999998, 25.826, 25.828,
      25.83, 25.832, 25.834, 25.836, 25.838, 25.84, 25.842, 25.844, 25.846,
      25.848, 25.849999999999998, 25.852, 25.854, 25.855999999999998, 25.858,
      25.86, 25.862, 25.864, 25.866, 25.868, 25.87, 25.872, 25.874, 25.876,
      25.878, 25.88, 25.881999999999998, 25.884, 25.886, 25.887999999999998,
      25.89, 25.892, 25.894, 25.896, 25.898, 25.9, 25.902, 25.904, 25.906,
      25.908, 25.91, 25.912, 25.913999999999998, 25.916, 25.918,
      25.919999999999998, 25.922, 25.924, 25.926, 25.928, 25.93, 25.932, 25.934,
      25.936, 25.938, 25.94, 25.942, 25.944, 25.945999999999998, 25.948, 25.95,
      25.951999999999998, 25.954, 25.956, 25.958, 25.96, 25.962, 25.964, 25.966,
      25.968, 25.97, 25.972, 25.974, 25.976, 25.977999999999998, 25.98, 25.982,
      25.983999999999998, 25.986, 25.988, 25.99, 25.992, 25.994, 25.996, 25.998,
      26.0, 26.002, 26.004, 26.006, 26.008, 26.009999999999998, 26.012, 26.014,
      26.016, 26.018, 26.02, 26.022, 26.024, 26.026, 26.028, 26.03, 26.032,
      26.034, 26.036, 26.038, 26.04, 26.041999999999998, 26.044, 26.046, 26.048,
      26.05, 26.052, 26.054, 26.056, 26.058, 26.06, 26.062, 26.064, 26.066,
      26.067999999999998, 26.07, 26.072, 26.073999999999998, 26.076, 26.078,
      26.08, 26.082, 26.084, 26.086, 26.088, 26.09, 26.092, 26.094, 26.096,
      26.098, 26.099999999999998, 26.102, 26.104, 26.105999999999998, 26.108,
      26.11, 26.112, 26.114, 26.116, 26.118, 26.12, 26.122, 26.124, 26.126,
      26.128, 26.13, 26.131999999999998, 26.134, 26.136, 26.137999999999998,
      26.14, 26.142, 26.144, 26.146, 26.148, 26.15, 26.152, 26.154, 26.156,
      26.158, 26.16, 26.162, 26.163999999999998, 26.166, 26.168,
      26.169999999999998, 26.172, 26.174, 26.176, 26.178, 26.18, 26.182, 26.184,
      26.186, 26.188, 26.19, 26.192, 26.194, 26.195999999999998, 26.198, 26.2,
      26.201999999999998, 26.204, 26.206, 26.208, 26.21, 26.212, 26.214, 26.216,
      26.218, 26.22, 26.222, 26.224, 26.226, 26.227999999999998, 26.23, 26.232,
      26.233999999999998, 26.236, 26.238, 26.24, 26.242, 26.244, 26.246, 26.248,
      26.25, 26.252, 26.254, 26.256, 26.258, 26.259999999999998, 26.262, 26.264,
      26.266, 26.268, 26.27, 26.272, 26.274, 26.276, 26.278, 26.28, 26.282,
      26.284, 26.286, 26.288, 26.29, 26.291999999999998, 26.294, 26.296, 26.298,
      26.3, 26.302, 26.304, 26.306, 26.308, 26.31, 26.312, 26.314, 26.316,
      26.317999999999998, 26.32, 26.322, 26.323999999999998, 26.326, 26.328,
      26.33, 26.332, 26.334, 26.336, 26.338, 26.34, 26.342, 26.344, 26.346,
      26.348, 26.349999999999998, 26.352, 26.354, 26.355999999999998, 26.358,
      26.36, 26.362, 26.364, 26.366, 26.368, 26.37, 26.372, 26.374, 26.376,
      26.378, 26.38, 26.381999999999998, 26.384, 26.386, 26.387999999999998,
      26.39, 26.392, 26.394, 26.396, 26.398, 26.4, 26.402, 26.404, 26.406,
      26.408, 26.41, 26.412, 26.413999999999998, 26.416, 26.418,
      26.419999999999998, 26.422, 26.424, 26.426, 26.428, 26.43, 26.432, 26.434,
      26.436, 26.438, 26.44, 26.442, 26.444, 26.445999999999998, 26.448, 26.45,
      26.451999999999998, 26.454, 26.456, 26.458, 26.46, 26.462, 26.464, 26.466,
      26.468, 26.47, 26.472, 26.474, 26.476, 26.477999999999998, 26.48, 26.482,
      26.483999999999998, 26.486, 26.488, 26.49, 26.492, 26.494, 26.496, 26.498,
      26.5, 26.502, 26.504, 26.506, 26.508, 26.509999999999998, 26.512, 26.514,
      26.516, 26.518, 26.52, 26.522, 26.524, 26.526, 26.528, 26.53, 26.532,
      26.534, 26.536, 26.538, 26.54, 26.541999999999998, 26.544, 26.546, 26.548,
      26.55, 26.552, 26.554, 26.556, 26.558, 26.56, 26.562, 26.564, 26.566,
      26.567999999999998, 26.57, 26.572, 26.573999999999998, 26.576, 26.578,
      26.58, 26.582, 26.584, 26.586, 26.588, 26.59, 26.592, 26.594, 26.596,
      26.598, 26.599999999999998, 26.602, 26.604, 26.605999999999998, 26.608,
      26.61, 26.612, 26.614, 26.616, 26.618, 26.62, 26.622, 26.624, 26.626,
      26.628, 26.63, 26.631999999999998, 26.634, 26.636, 26.637999999999998,
      26.64, 26.642, 26.644, 26.646, 26.648, 26.65, 26.652, 26.654, 26.656,
      26.658, 26.66, 26.662, 26.663999999999998, 26.666, 26.668,
      26.669999999999998, 26.672, 26.674, 26.676, 26.678, 26.68, 26.682, 26.684,
      26.686, 26.688, 26.69, 26.692, 26.694, 26.695999999999998, 26.698, 26.7,
      26.701999999999998, 26.704, 26.706, 26.708, 26.71, 26.712, 26.714, 26.716,
      26.718, 26.72, 26.722, 26.724, 26.726, 26.727999999999998, 26.73, 26.732,
      26.733999999999998, 26.736, 26.738, 26.74, 26.742, 26.744, 26.746, 26.748,
      26.75, 26.752, 26.754, 26.756, 26.758, 26.759999999999998, 26.762, 26.764,
      26.766, 26.768, 26.77, 26.772, 26.774, 26.776, 26.778, 26.78, 26.782,
      26.784, 26.786, 26.788, 26.79, 26.791999999999998, 26.794, 26.796, 26.798,
      26.8, 26.802, 26.804, 26.806, 26.808, 26.81, 26.812, 26.814, 26.816,
      26.818, 26.82, 26.822, 26.823999999999998, 26.826, 26.828, 26.83, 26.832,
      26.834, 26.836, 26.838, 26.84, 26.842, 26.844, 26.846, 26.848,
      26.849999999999998, 26.852, 26.854, 26.855999999999998, 26.858, 26.86,
      26.862, 26.864, 26.866, 26.868, 26.87, 26.872, 26.874, 26.876, 26.878,
      26.88, 26.881999999999998, 26.884, 26.886, 26.887999999999998, 26.89,
      26.892, 26.894, 26.896, 26.898, 26.9, 26.902, 26.904, 26.906, 26.908,
      26.91, 26.912, 26.913999999999998, 26.916, 26.918, 26.919999999999998,
      26.922, 26.924, 26.926, 26.928, 26.93, 26.932, 26.934, 26.936, 26.938,
      26.94, 26.942, 26.944, 26.945999999999998, 26.948, 26.95,
      26.951999999999998, 26.954, 26.956, 26.958, 26.96, 26.962, 26.964, 26.966,
      26.968, 26.97, 26.972, 26.974, 26.976, 26.977999999999998, 26.98, 26.982,
      26.983999999999998, 26.986, 26.988, 26.99, 26.992, 26.994, 26.996, 26.998,
      27.0, 27.002, 27.004, 27.006, 27.008, 27.009999999999998, 27.012, 27.014,
      27.016, 27.018, 27.02, 27.022, 27.024, 27.026, 27.028, 27.03, 27.032,
      27.034, 27.036, 27.038, 27.04, 27.041999999999998, 27.044, 27.046, 27.048,
      27.05, 27.052, 27.054, 27.056, 27.058, 27.06, 27.062, 27.064, 27.066,
      27.068, 27.07, 27.072, 27.073999999999998, 27.076, 27.078, 27.08, 27.082,
      27.084, 27.086, 27.088, 27.09, 27.092, 27.094, 27.096, 27.098,
      27.099999999999998, 27.102, 27.104, 27.105999999999998, 27.108, 27.11,
      27.112, 27.114, 27.116, 27.118, 27.12, 27.122, 27.124, 27.126, 27.128,
      27.13, 27.131999999999998, 27.134, 27.136, 27.137999999999998, 27.14,
      27.142, 27.144, 27.146, 27.148, 27.15, 27.152, 27.154, 27.156, 27.158,
      27.16, 27.162, 27.163999999999998, 27.166, 27.168, 27.169999999999998,
      27.172, 27.174, 27.176, 27.178, 27.18, 27.182, 27.184, 27.186, 27.188,
      27.19, 27.192, 27.194, 27.195999999999998, 27.198, 27.2,
      27.201999999999998, 27.204, 27.206, 27.208, 27.21, 27.212, 27.214, 27.216,
      27.218, 27.22, 27.222, 27.224, 27.226, 27.227999999999998, 27.23, 27.232,
      27.233999999999998, 27.236, 27.238, 27.24, 27.242, 27.244, 27.246, 27.248,
      27.25, 27.252, 27.254, 27.256, 27.258, 27.259999999999998, 27.262, 27.264,
      27.266, 27.268, 27.27, 27.272, 27.274, 27.276, 27.278, 27.28, 27.282,
      27.284, 27.286, 27.288, 27.29, 27.291999999999998, 27.294, 27.296, 27.298,
      27.3, 27.302, 27.304, 27.306, 27.308, 27.31, 27.312, 27.314, 27.316,
      27.318, 27.32, 27.322, 27.323999999999998, 27.326, 27.328, 27.33, 27.332,
      27.334, 27.336, 27.338, 27.34, 27.342, 27.344, 27.346, 27.348,
      27.349999999999998, 27.352, 27.354, 27.355999999999998, 27.358, 27.36,
      27.362, 27.364, 27.366, 27.368, 27.37, 27.372, 27.374, 27.376, 27.378,
      27.38, 27.381999999999998, 27.384, 27.386, 27.387999999999998, 27.39,
      27.392, 27.394, 27.396, 27.398, 27.4, 27.402, 27.404, 27.406, 27.408,
      27.41, 27.412, 27.413999999999998, 27.416, 27.418, 27.419999999999998,
      27.422, 27.424, 27.426, 27.428, 27.43, 27.432, 27.434, 27.436, 27.438,
      27.44, 27.442, 27.444, 27.445999999999998, 27.448, 27.45,
      27.451999999999998, 27.454, 27.456, 27.458, 27.46, 27.462, 27.464, 27.466,
      27.468, 27.47, 27.472, 27.474, 27.476, 27.477999999999998, 27.48, 27.482,
      27.483999999999998, 27.486, 27.488, 27.49, 27.492, 27.494, 27.496, 27.498,
      27.5, 27.502, 27.504, 27.506, 27.508, 27.509999999999998, 27.512, 27.514,
      27.516, 27.518, 27.52, 27.522, 27.524, 27.526, 27.528, 27.53, 27.532,
      27.534, 27.536, 27.538, 27.54, 27.541999999999998, 27.544, 27.546, 27.548,
      27.55, 27.552, 27.554, 27.556, 27.558, 27.56, 27.562, 27.564, 27.566,
      27.568, 27.57, 27.572, 27.573999999999998, 27.576, 27.578, 27.58, 27.582,
      27.584, 27.586, 27.588, 27.59, 27.592, 27.594, 27.596, 27.598,
      27.599999999999998, 27.602, 27.604, 27.605999999999998, 27.608, 27.61,
      27.612, 27.614, 27.616, 27.618, 27.62, 27.622, 27.624, 27.626, 27.628,
      27.63, 27.631999999999998, 27.634, 27.636, 27.637999999999998, 27.64,
      27.642, 27.644, 27.646, 27.648, 27.65, 27.652, 27.654, 27.656, 27.658,
      27.66, 27.662, 27.663999999999998, 27.666, 27.668, 27.669999999999998,
      27.672, 27.674, 27.676, 27.678, 27.68, 27.682, 27.684, 27.686, 27.688,
      27.69, 27.692, 27.694, 27.695999999999998, 27.698, 27.7,
      27.701999999999998, 27.704, 27.706, 27.708, 27.71, 27.712, 27.714, 27.716,
      27.718, 27.72, 27.722, 27.724, 27.726, 27.727999999999998, 27.73, 27.732,
      27.733999999999998, 27.736, 27.738, 27.74, 27.742, 27.744, 27.746, 27.748,
      27.75, 27.752, 27.754, 27.756, 27.758, 27.759999999999998, 27.762, 27.764,
      27.766, 27.768, 27.77, 27.772, 27.774, 27.776, 27.778, 27.78, 27.782,
      27.784, 27.786, 27.788, 27.79, 27.791999999999998, 27.794, 27.796, 27.798,
      27.8, 27.802, 27.804, 27.806, 27.808, 27.81, 27.812, 27.814, 27.816,
      27.818, 27.82, 27.822, 27.823999999999998, 27.826, 27.828, 27.83, 27.832,
      27.834, 27.836, 27.838, 27.84, 27.842, 27.844, 27.846, 27.848,
      27.849999999999998, 27.852, 27.854, 27.855999999999998, 27.858, 27.86,
      27.862, 27.864, 27.866, 27.868, 27.87, 27.872, 27.874, 27.876, 27.878,
      27.88, 27.881999999999998, 27.884, 27.886, 27.887999999999998, 27.89,
      27.892, 27.894, 27.896, 27.898, 27.9, 27.902, 27.904, 27.906, 27.908,
      27.91, 27.912, 27.913999999999998, 27.916, 27.918, 27.919999999999998,
      27.922, 27.924, 27.926, 27.928, 27.93, 27.932, 27.934, 27.936, 27.938,
      27.94, 27.942, 27.944, 27.945999999999998, 27.948, 27.95,
      27.951999999999998, 27.954, 27.956, 27.958, 27.96, 27.962, 27.964, 27.966,
      27.968, 27.97, 27.972, 27.974, 27.976, 27.977999999999998, 27.98, 27.982,
      27.983999999999998, 27.986, 27.988, 27.99, 27.992, 27.994, 27.996, 27.998,
      28.0, 28.002, 28.004, 28.006, 28.008, 28.009999999999998, 28.012, 28.014,
      28.016, 28.018, 28.02, 28.022, 28.024, 28.026, 28.028, 28.03, 28.032,
      28.034, 28.036, 28.038, 28.04, 28.041999999999998, 28.044, 28.046, 28.048,
      28.05, 28.052, 28.054, 28.056, 28.058, 28.06, 28.062, 28.064, 28.066,
      28.068, 28.07, 28.072, 28.073999999999998, 28.076, 28.078, 28.08, 28.082,
      28.084, 28.086, 28.088, 28.09, 28.092, 28.094, 28.096, 28.098, 28.1,
      28.102, 28.104, 28.105999999999998, 28.108, 28.11, 28.112, 28.114, 28.116,
      28.118, 28.12, 28.122, 28.124, 28.126, 28.128, 28.13, 28.131999999999998,
      28.134, 28.136, 28.137999999999998, 28.14, 28.142, 28.144, 28.146, 28.148,
      28.15, 28.152, 28.154, 28.156, 28.158, 28.16, 28.162, 28.163999999999998,
      28.166, 28.168, 28.169999999999998, 28.172, 28.174, 28.176, 28.178, 28.18,
      28.182, 28.184, 28.186, 28.188, 28.19, 28.192, 28.194, 28.195999999999998,
      28.198, 28.2, 28.201999999999998, 28.204, 28.206, 28.208, 28.21, 28.212,
      28.214, 28.216, 28.218, 28.22, 28.222, 28.224, 28.226, 28.227999999999998,
      28.23, 28.232, 28.233999999999998, 28.236, 28.238, 28.24, 28.242, 28.244,
      28.246, 28.248, 28.25, 28.252, 28.254, 28.256, 28.258, 28.259999999999998,
      28.262, 28.264, 28.266, 28.268, 28.27, 28.272, 28.274, 28.276, 28.278,
      28.28, 28.282, 28.284, 28.286, 28.288, 28.29, 28.291999999999998, 28.294,
      28.296, 28.298, 28.3, 28.302, 28.304, 28.306, 28.308, 28.31, 28.312,
      28.314, 28.316, 28.318, 28.32, 28.322, 28.323999999999998, 28.326, 28.328,
      28.33, 28.332, 28.334, 28.336, 28.338, 28.34, 28.342, 28.344, 28.346,
      28.348, 28.35, 28.352, 28.354, 28.355999999999998, 28.358, 28.36, 28.362,
      28.364, 28.366, 28.368, 28.37, 28.372, 28.374, 28.376, 28.378, 28.38,
      28.381999999999998, 28.384, 28.386, 28.387999999999998, 28.39, 28.392,
      28.394, 28.396, 28.398, 28.4, 28.402, 28.404, 28.406, 28.408, 28.41,
      28.412, 28.413999999999998, 28.416, 28.418, 28.419999999999998, 28.422,
      28.424, 28.426, 28.428, 28.43, 28.432, 28.434, 28.436, 28.438, 28.44,
      28.442, 28.444, 28.445999999999998, 28.448, 28.45, 28.451999999999998,
      28.454, 28.456, 28.458, 28.46, 28.462, 28.464, 28.466, 28.468, 28.47,
      28.472, 28.474, 28.476, 28.477999999999998, 28.48, 28.482,
      28.483999999999998, 28.486, 28.488, 28.49, 28.492, 28.494, 28.496, 28.498,
      28.5, 28.502, 28.504, 28.506, 28.508, 28.509999999999998, 28.512, 28.514,
      28.516, 28.518, 28.52, 28.522, 28.524, 28.526, 28.528, 28.53, 28.532,
      28.534, 28.536, 28.538, 28.54, 28.541999999999998, 28.544, 28.546, 28.548,
      28.55, 28.552, 28.554, 28.556, 28.558, 28.56, 28.562, 28.564, 28.566,
      28.568, 28.57, 28.572, 28.573999999999998, 28.576, 28.578, 28.58, 28.582,
      28.584, 28.586, 28.588, 28.59, 28.592, 28.594, 28.596, 28.598, 28.6,
      28.602, 28.604, 28.605999999999998, 28.608, 28.61, 28.612, 28.614, 28.616,
      28.618, 28.62, 28.622, 28.624, 28.626, 28.628, 28.63, 28.631999999999998,
      28.634, 28.636, 28.637999999999998, 28.64, 28.642, 28.644, 28.646, 28.648,
      28.65, 28.652, 28.654, 28.656, 28.658, 28.66, 28.662, 28.663999999999998,
      28.666, 28.668, 28.669999999999998, 28.672, 28.674, 28.676, 28.678, 28.68,
      28.682, 28.684, 28.686, 28.688, 28.69, 28.692, 28.694, 28.695999999999998,
      28.698, 28.7, 28.701999999999998, 28.704, 28.706, 28.708, 28.71, 28.712,
      28.714, 28.716, 28.718, 28.72, 28.722, 28.724, 28.726, 28.727999999999998,
      28.73, 28.732, 28.733999999999998, 28.736, 28.738, 28.74, 28.742, 28.744,
      28.746, 28.748, 28.75, 28.752, 28.754, 28.756, 28.758, 28.759999999999998,
      28.762, 28.764, 28.766, 28.768, 28.77, 28.772, 28.774, 28.776, 28.778,
      28.78, 28.782, 28.784, 28.786, 28.788, 28.79, 28.791999999999998, 28.794,
      28.796, 28.798, 28.8, 28.802, 28.804, 28.806, 28.808, 28.81, 28.812,
      28.814, 28.816, 28.818, 28.82, 28.822, 28.823999999999998, 28.826, 28.828,
      28.83, 28.832, 28.834, 28.836, 28.838, 28.84, 28.842, 28.844, 28.846,
      28.848, 28.85, 28.852, 28.854, 28.855999999999998, 28.858, 28.86, 28.862,
      28.864, 28.866, 28.868, 28.87, 28.872, 28.874, 28.876, 28.878, 28.88,
      28.881999999999998, 28.884, 28.886, 28.887999999999998, 28.89, 28.892,
      28.894, 28.896, 28.898, 28.9, 28.902, 28.904, 28.906, 28.908, 28.91,
      28.912, 28.913999999999998, 28.916, 28.918, 28.919999999999998, 28.922,
      28.924, 28.926, 28.928, 28.93, 28.932, 28.934, 28.936, 28.938, 28.94,
      28.942, 28.944, 28.945999999999998, 28.948, 28.95, 28.951999999999998,
      28.954, 28.956, 28.958, 28.96, 28.962, 28.964, 28.966, 28.968, 28.97,
      28.972, 28.974, 28.976, 28.977999999999998, 28.98, 28.982,
      28.983999999999998, 28.986, 28.988, 28.99, 28.992, 28.994, 28.996, 28.998,
      29.0, 29.002, 29.003999999999998, 29.006, 29.008, 29.009999999999998,
      29.012, 29.014, 29.016, 29.018, 29.02, 29.022, 29.024, 29.026, 29.028,
      29.03, 29.032, 29.034, 29.036, 29.038, 29.04, 29.042, 29.044, 29.046,
      29.048000000000002, 29.049999999999997, 29.052, 29.054000000000002,
      29.055999999999997, 29.058, 29.060000000000002, 29.061999999999998, 29.064,
      29.066, 29.067999999999998, 29.07, 29.072, 29.073999999999998, 29.076,
      29.078, 29.08, 29.082, 29.084, 29.086, 29.088, 29.09, 29.092, 29.094,
      29.096, 29.098, 29.1, 29.102, 29.104, 29.106, 29.108, 29.11,
      29.112000000000002, 29.113999999999997, 29.116, 29.118000000000002,
      29.119999999999997, 29.122, 29.124000000000002, 29.125999999999998, 29.128,
      29.13, 29.131999999999998, 29.134, 29.136, 29.137999999999998, 29.14,
      29.142, 29.144, 29.146, 29.148, 29.15, 29.152, 29.154, 29.156, 29.158,
      29.16, 29.162, 29.164, 29.166, 29.168, 29.17, 29.171999999999997, 29.174,
      29.176000000000002, 29.177999999999997, 29.18, 29.182000000000002,
      29.183999999999997, 29.186, 29.188, 29.189999999999998, 29.192, 29.194,
      29.195999999999998, 29.198, 29.2, 29.201999999999998, 29.204, 29.206,
      29.208, 29.21, 29.212, 29.214, 29.216, 29.218, 29.22, 29.222, 29.224,
      29.226, 29.228, 29.23, 29.232, 29.234, 29.235999999999997, 29.238,
      29.240000000000002, 29.241999999999997, 29.244, 29.246000000000002,
      29.247999999999998, 29.25, 29.252, 29.253999999999998, 29.256, 29.258,
      29.259999999999998, 29.262, 29.264, 29.266, 29.268, 29.27, 29.272, 29.274,
      29.276, 29.278, 29.28, 29.282, 29.284, 29.286, 29.288, 29.29, 29.292,
      29.294, 29.296, 29.298000000000002, 29.299999999999997, 29.302,
      29.304000000000002, 29.305999999999997, 29.308, 29.310000000000002,
      29.311999999999998, 29.314, 29.316, 29.317999999999998, 29.32, 29.322,
      29.323999999999998, 29.326, 29.328, 29.33, 29.332, 29.334, 29.336, 29.338,
      29.34, 29.342, 29.344, 29.346, 29.348, 29.35, 29.352, 29.354, 29.356,
      29.358, 29.36, 29.362000000000002, 29.363999999999997, 29.366,
      29.368000000000002, 29.369999999999997, 29.372, 29.374000000000002,
      29.375999999999998, 29.378, 29.38, 29.381999999999998, 29.384, 29.386,
      29.387999999999998, 29.39, 29.392, 29.394, 29.396, 29.398, 29.4, 29.402,
      29.404, 29.406, 29.408, 29.41, 29.412, 29.414, 29.416, 29.418, 29.42,
      29.421999999999997, 29.424, 29.426000000000002, 29.427999999999997, 29.43,
      29.432000000000002, 29.433999999999997, 29.436, 29.438, 29.439999999999998,
      29.442, 29.444, 29.445999999999998, 29.448, 29.45, 29.451999999999998,
      29.454, 29.456, 29.458, 29.46, 29.462, 29.464, 29.466, 29.468, 29.47,
      29.472, 29.474, 29.476, 29.478, 29.48, 29.482, 29.484, 29.485999999999997,
      29.488, 29.490000000000002, 29.491999999999997, 29.494, 29.496000000000002,
      29.497999999999998, 29.5, 29.502, 29.503999999999998, 29.506, 29.508,
      29.509999999999998, 29.512, 29.514, 29.516, 29.518, 29.52, 29.522, 29.524,
      29.526, 29.528, 29.53, 29.532, 29.534, 29.536, 29.538, 29.54, 29.542,
      29.544, 29.546, 29.548000000000002, 29.549999999999997, 29.552,
      29.554000000000002, 29.555999999999997, 29.558, 29.560000000000002,
      29.561999999999998, 29.564, 29.566, 29.567999999999998, 29.57, 29.572,
      29.573999999999998, 29.576, 29.578, 29.58, 29.582, 29.584, 29.586, 29.588,
      29.59, 29.592, 29.594, 29.596, 29.598, 29.6, 29.602, 29.604, 29.606,
      29.608, 29.61, 29.612000000000002, 29.613999999999997, 29.616,
      29.618000000000002, 29.619999999999997, 29.622, 29.624000000000002,
      29.625999999999998, 29.628, 29.63, 29.631999999999998, 29.634, 29.636,
      29.637999999999998, 29.64, 29.642, 29.644, 29.646, 29.648, 29.65, 29.652,
      29.654, 29.656, 29.658, 29.66, 29.662, 29.664, 29.666, 29.668, 29.67,
      29.671999999999997, 29.674, 29.676000000000002, 29.677999999999997, 29.68,
      29.682000000000002, 29.683999999999997, 29.686, 29.688, 29.689999999999998,
      29.692, 29.694, 29.695999999999998, 29.698, 29.7, 29.701999999999998,
      29.704, 29.706, 29.708, 29.71, 29.712, 29.714, 29.716, 29.718, 29.72,
      29.722, 29.724, 29.726, 29.728, 29.73, 29.732, 29.734, 29.735999999999997,
      29.738, 29.740000000000002, 29.741999999999997, 29.744, 29.746000000000002,
      29.747999999999998, 29.75, 29.752, 29.753999999999998, 29.756, 29.758,
      29.759999999999998, 29.762, 29.764, 29.766, 29.768, 29.77, 29.772, 29.774,
      29.776, 29.778, 29.78, 29.782, 29.784, 29.786, 29.788, 29.79, 29.792,
      29.794, 29.796, 29.798000000000002, 29.799999999999997, 29.802,
      29.804000000000002, 29.805999999999997, 29.808, 29.810000000000002,
      29.811999999999998, 29.814, 29.816, 29.817999999999998, 29.82, 29.822,
      29.823999999999998, 29.826, 29.828, 29.83, 29.832, 29.834, 29.836, 29.838,
      29.84, 29.842, 29.844, 29.846, 29.848, 29.85, 29.852, 29.854, 29.856,
      29.858, 29.86, 29.862000000000002, 29.863999999999997, 29.866,
      29.868000000000002, 29.869999999999997, 29.872, 29.874000000000002,
      29.875999999999998, 29.878, 29.88, 29.881999999999998, 29.884, 29.886,
      29.887999999999998, 29.89, 29.892, 29.894, 29.896, 29.898, 29.9, 29.902,
      29.904, 29.906, 29.908, 29.91, 29.912, 29.914, 29.916, 29.918, 29.92,
      29.921999999999997, 29.924, 29.926000000000002, 29.927999999999997, 29.93,
      29.932000000000002, 29.933999999999997, 29.936, 29.938, 29.939999999999998,
      29.942, 29.944, 29.945999999999998, 29.948, 29.95, 29.951999999999998,
      29.954, 29.956, 29.958, 29.96, 29.962, 29.964, 29.966, 29.968, 29.97,
      29.972, 29.974, 29.976, 29.978, 29.98, 29.982, 29.984, 29.985999999999997,
      29.988, 29.990000000000002, 29.991999999999997, 29.994, 29.996000000000002,
      29.997999999999998, 30.0, 30.002, 30.003999999999998, 30.006, 30.008,
      30.009999999999998, 30.012, 30.014, 30.016, 30.018, 30.02, 30.022, 30.024,
      30.026, 30.028, 30.03, 30.032, 30.034, 30.036, 30.038, 30.04, 30.042,
      30.044, 30.046, 30.048000000000002, 30.049999999999997, 30.052,
      30.054000000000002, 30.055999999999997, 30.058, 30.060000000000002,
      30.061999999999998, 30.064, 30.066, 30.067999999999998, 30.07, 30.072,
      30.073999999999998, 30.076, 30.078, 30.08, 30.082, 30.084, 30.086, 30.088,
      30.09, 30.092, 30.094, 30.096, 30.098, 30.1, 30.102, 30.104, 30.106,
      30.108, 30.11, 30.112000000000002, 30.113999999999997, 30.116,
      30.118000000000002, 30.119999999999997, 30.122, 30.124000000000002,
      30.125999999999998, 30.128, 30.13, 30.131999999999998, 30.134, 30.136,
      30.137999999999998, 30.14, 30.142, 30.144, 30.146, 30.148, 30.15, 30.152,
      30.154, 30.156, 30.158, 30.16, 30.162, 30.164, 30.166, 30.168, 30.17,
      30.171999999999997, 30.174, 30.176000000000002, 30.177999999999997, 30.18,
      30.182000000000002, 30.183999999999997, 30.186, 30.188, 30.189999999999998,
      30.192, 30.194, 30.195999999999998, 30.198, 30.2, 30.201999999999998,
      30.204, 30.206, 30.208, 30.21, 30.212, 30.214, 30.216, 30.218, 30.22,
      30.222, 30.224, 30.226, 30.228, 30.23, 30.232, 30.234, 30.235999999999997,
      30.238, 30.240000000000002, 30.241999999999997, 30.244, 30.246000000000002,
      30.247999999999998, 30.25, 30.252, 30.253999999999998, 30.256, 30.258,
      30.259999999999998, 30.262, 30.264, 30.266, 30.268, 30.27, 30.272, 30.274,
      30.276, 30.278, 30.28, 30.282, 30.284, 30.286, 30.288, 30.29, 30.292,
      30.294, 30.296, 30.298000000000002, 30.299999999999997, 30.302,
      30.304000000000002, 30.305999999999997, 30.308, 30.310000000000002,
      30.311999999999998, 30.314, 30.316, 30.317999999999998, 30.32, 30.322,
      30.323999999999998, 30.326, 30.328, 30.33, 30.332, 30.334, 30.336, 30.338,
      30.34, 30.342, 30.344, 30.346, 30.348, 30.35, 30.352, 30.354, 30.356,
      30.358, 30.36, 30.362000000000002, 30.363999999999997, 30.366,
      30.368000000000002, 30.369999999999997, 30.372, 30.374000000000002,
      30.375999999999998, 30.378, 30.38, 30.381999999999998, 30.384, 30.386,
      30.387999999999998, 30.39, 30.392, 30.394, 30.396, 30.398, 30.4, 30.402,
      30.404, 30.406, 30.408, 30.41, 30.412, 30.414, 30.416, 30.418, 30.42,
      30.421999999999997, 30.424, 30.426000000000002, 30.427999999999997, 30.43,
      30.432000000000002, 30.433999999999997, 30.436, 30.438, 30.439999999999998,
      30.442, 30.444, 30.445999999999998, 30.448, 30.45, 30.451999999999998,
      30.454, 30.456, 30.458, 30.46, 30.462, 30.464, 30.466, 30.468, 30.47,
      30.472, 30.474, 30.476, 30.478, 30.48, 30.482, 30.484, 30.485999999999997,
      30.488, 30.490000000000002, 30.491999999999997, 30.494, 30.496000000000002,
      30.497999999999998, 30.5, 30.502, 30.503999999999998, 30.506, 30.508,
      30.509999999999998, 30.512, 30.514, 30.516, 30.518, 30.52, 30.522, 30.524,
      30.526, 30.528, 30.53, 30.532, 30.534, 30.536, 30.538, 30.54, 30.542,
      30.544, 30.546, 30.548000000000002, 30.549999999999997, 30.552,
      30.554000000000002, 30.555999999999997, 30.558, 30.560000000000002,
      30.561999999999998, 30.564, 30.566, 30.567999999999998, 30.57, 30.572,
      30.573999999999998, 30.576, 30.578, 30.58, 30.582, 30.584, 30.586, 30.588,
      30.59, 30.592, 30.594, 30.596, 30.598, 30.6, 30.602, 30.604, 30.606,
      30.608, 30.61, 30.612000000000002, 30.613999999999997, 30.616,
      30.618000000000002, 30.619999999999997, 30.622, 30.624000000000002,
      30.625999999999998, 30.628, 30.63, 30.631999999999998, 30.634, 30.636,
      30.637999999999998, 30.64, 30.642, 30.644, 30.646, 30.648, 30.65, 30.652,
      30.654, 30.656, 30.658, 30.66, 30.662, 30.664, 30.666, 30.668, 30.67,
      30.671999999999997, 30.674, 30.676000000000002, 30.677999999999997, 30.68,
      30.682000000000002, 30.683999999999997, 30.686, 30.688, 30.689999999999998,
      30.692, 30.694, 30.695999999999998, 30.698, 30.7, 30.701999999999998,
      30.704, 30.706, 30.708, 30.71, 30.712, 30.714, 30.716, 30.718, 30.72,
      30.722, 30.724, 30.726, 30.728, 30.73, 30.732, 30.734, 30.735999999999997,
      30.738, 30.740000000000002, 30.741999999999997, 30.744, 30.746000000000002,
      30.747999999999998, 30.75, 30.752, 30.753999999999998, 30.756, 30.758,
      30.759999999999998, 30.762, 30.764, 30.766, 30.768, 30.77, 30.772, 30.774,
      30.776, 30.778, 30.78, 30.782, 30.784, 30.786, 30.788, 30.79, 30.792,
      30.794, 30.796, 30.798000000000002, 30.799999999999997, 30.802,
      30.804000000000002, 30.805999999999997, 30.808, 30.810000000000002,
      30.811999999999998, 30.814, 30.816, 30.817999999999998, 30.82, 30.822,
      30.823999999999998, 30.826, 30.828, 30.83, 30.832, 30.834, 30.836, 30.838,
      30.84, 30.842, 30.844, 30.846, 30.848, 30.85, 30.852, 30.854, 30.856,
      30.858, 30.86, 30.862000000000002, 30.863999999999997, 30.866,
      30.868000000000002, 30.869999999999997, 30.872, 30.874000000000002,
      30.875999999999998, 30.878, 30.88, 30.881999999999998, 30.884, 30.886,
      30.887999999999998, 30.89, 30.892, 30.894, 30.896, 30.898, 30.9, 30.902,
      30.904, 30.906, 30.908, 30.91, 30.912, 30.914, 30.916, 30.918, 30.92,
      30.921999999999997, 30.924, 30.926000000000002, 30.927999999999997, 30.93,
      30.932000000000002, 30.933999999999997, 30.936, 30.938, 30.939999999999998,
      30.942, 30.944, 30.945999999999998, 30.948, 30.95, 30.951999999999998,
      30.954, 30.956, 30.958, 30.96, 30.962, 30.964, 30.966, 30.968, 30.97,
      30.972, 30.974, 30.976, 30.978, 30.98, 30.982, 30.984, 30.985999999999997,
      30.988, 30.990000000000002, 30.991999999999997, 30.994, 30.996000000000002,
      30.997999999999998, 31.0, 31.002, 31.003999999999998, 31.006, 31.008,
      31.009999999999998, 31.012, 31.014, 31.016, 31.018, 31.02, 31.022, 31.024,
      31.026, 31.028, 31.03, 31.032, 31.034, 31.036, 31.038, 31.04, 31.042,
      31.044, 31.046, 31.048000000000002, 31.049999999999997, 31.052,
      31.054000000000002, 31.055999999999997, 31.058, 31.060000000000002,
      31.061999999999998, 31.064, 31.066, 31.067999999999998, 31.07, 31.072,
      31.073999999999998, 31.076, 31.078, 31.08, 31.082, 31.084, 31.086, 31.088,
      31.09, 31.092, 31.094, 31.096, 31.098, 31.1, 31.102, 31.104, 31.106,
      31.108, 31.11, 31.112000000000002, 31.113999999999997, 31.116,
      31.118000000000002, 31.119999999999997, 31.122, 31.124000000000002,
      31.125999999999998, 31.128, 31.13, 31.131999999999998, 31.134, 31.136,
      31.137999999999998, 31.14, 31.142, 31.144, 31.146, 31.148, 31.15, 31.152,
      31.154, 31.156, 31.158, 31.16, 31.162, 31.164, 31.166, 31.168, 31.17,
      31.172, 31.174, 31.176000000000002, 31.177999999999997, 31.18,
      31.182000000000002, 31.183999999999997, 31.186, 31.188, 31.189999999999998,
      31.192, 31.194, 31.195999999999998, 31.198, 31.2, 31.201999999999998,
      31.204, 31.206, 31.208, 31.21, 31.212, 31.214, 31.216, 31.218, 31.22,
      31.222, 31.224, 31.226, 31.228, 31.23, 31.232, 31.234, 31.235999999999997,
      31.238, 31.240000000000002, 31.241999999999997, 31.244, 31.246000000000002,
      31.247999999999998, 31.25, 31.252, 31.253999999999998, 31.256, 31.258,
      31.259999999999998, 31.262, 31.264, 31.266, 31.268, 31.27, 31.272, 31.274,
      31.276, 31.278, 31.28, 31.282, 31.284, 31.286, 31.288, 31.29, 31.292,
      31.294, 31.296, 31.298000000000002, 31.299999999999997, 31.302,
      31.304000000000002, 31.305999999999997, 31.308, 31.310000000000002,
      31.311999999999998, 31.314, 31.316, 31.317999999999998, 31.32, 31.322,
      31.323999999999998, 31.326, 31.328, 31.33, 31.332, 31.334, 31.336, 31.338,
      31.34, 31.342, 31.344, 31.346, 31.348, 31.35, 31.352, 31.354, 31.356,
      31.358, 31.36, 31.362000000000002, 31.363999999999997, 31.366,
      31.368000000000002, 31.369999999999997, 31.372, 31.374000000000002,
      31.375999999999998, 31.378, 31.38, 31.381999999999998, 31.384, 31.386,
      31.387999999999998, 31.39, 31.392, 31.394, 31.396, 31.398, 31.4, 31.402,
      31.404, 31.406, 31.408, 31.41, 31.412, 31.414, 31.416, 31.418, 31.42,
      31.422, 31.424, 31.426000000000002, 31.427999999999997, 31.43,
      31.432000000000002, 31.433999999999997, 31.436, 31.438, 31.439999999999998,
      31.442, 31.444, 31.445999999999998, 31.448, 31.45, 31.451999999999998,
      31.454, 31.456, 31.458, 31.46, 31.462, 31.464, 31.466, 31.468, 31.47,
      31.472, 31.474, 31.476, 31.478, 31.48, 31.482, 31.484, 31.485999999999997,
      31.488, 31.490000000000002, 31.491999999999997, 31.494, 31.496000000000002,
      31.497999999999998, 31.5, 31.502, 31.503999999999998, 31.506, 31.508,
      31.509999999999998, 31.512, 31.514, 31.516, 31.518, 31.52, 31.522, 31.524,
      31.526, 31.528, 31.53, 31.532, 31.534, 31.536, 31.538, 31.54, 31.542,
      31.544, 31.546, 31.548000000000002, 31.549999999999997, 31.552,
      31.554000000000002, 31.555999999999997, 31.558, 31.560000000000002,
      31.561999999999998, 31.564, 31.566, 31.567999999999998, 31.57, 31.572,
      31.573999999999998, 31.576, 31.578, 31.58, 31.582, 31.584, 31.586, 31.588,
      31.59, 31.592, 31.594, 31.596, 31.598, 31.6, 31.602, 31.604, 31.606,
      31.608, 31.61, 31.612000000000002, 31.613999999999997, 31.616,
      31.618000000000002, 31.619999999999997, 31.622, 31.624000000000002,
      31.625999999999998, 31.628, 31.63, 31.631999999999998, 31.634, 31.636,
      31.637999999999998, 31.64, 31.642, 31.644, 31.646, 31.648, 31.65, 31.652,
      31.654, 31.656, 31.658, 31.66, 31.662, 31.664, 31.666, 31.668, 31.67,
      31.672, 31.674, 31.676000000000002, 31.677999999999997, 31.68,
      31.682000000000002, 31.683999999999997, 31.686, 31.688, 31.689999999999998,
      31.692, 31.694, 31.695999999999998, 31.698, 31.7, 31.701999999999998,
      31.704, 31.706, 31.708, 31.71, 31.712, 31.714, 31.716, 31.718, 31.72,
      31.722, 31.724, 31.726, 31.728, 31.73, 31.732, 31.734, 31.735999999999997,
      31.738, 31.740000000000002, 31.741999999999997, 31.744, 31.746000000000002,
      31.747999999999998, 31.75, 31.752, 31.753999999999998, 31.756, 31.758,
      31.759999999999998, 31.762, 31.764, 31.766, 31.768, 31.77, 31.772, 31.774,
      31.776, 31.778, 31.78, 31.782, 31.784, 31.786, 31.788, 31.79, 31.792,
      31.794, 31.796, 31.798000000000002, 31.799999999999997, 31.802,
      31.804000000000002, 31.805999999999997, 31.808, 31.810000000000002,
      31.811999999999998, 31.814, 31.816, 31.817999999999998, 31.82, 31.822,
      31.823999999999998, 31.826, 31.828, 31.83, 31.832, 31.834, 31.836, 31.838,
      31.84, 31.842, 31.844, 31.846, 31.848, 31.85, 31.852, 31.854, 31.856,
      31.858, 31.86, 31.862000000000002, 31.863999999999997, 31.866,
      31.868000000000002, 31.869999999999997, 31.872, 31.874000000000002,
      31.875999999999998, 31.878, 31.88, 31.881999999999998, 31.884, 31.886,
      31.887999999999998, 31.89, 31.892, 31.894, 31.896, 31.898, 31.9, 31.902,
      31.904, 31.906, 31.908, 31.91, 31.912, 31.914, 31.916, 31.918, 31.92,
      31.922, 31.924, 31.926000000000002, 31.927999999999997, 31.93,
      31.932000000000002, 31.933999999999997, 31.936, 31.938000000000002,
      31.939999999999998, 31.942, 31.944, 31.945999999999998, 31.948, 31.95,
      31.951999999999998, 31.954, 31.956, 31.958, 31.96, 31.962, 31.964, 31.966,
      31.968, 31.97, 31.972, 31.974, 31.976, 31.978, 31.98, 31.982, 31.984,
      31.985999999999997, 31.988, 31.990000000000002, 31.991999999999997, 31.994,
      31.996000000000002, 31.997999999999998, 32.0, 32.001999999999995, 32.004,
      32.006, 32.007999999999996, 32.01, 32.012, 32.013999999999996, 32.016,
      32.018, 32.019999999999996, 32.022, 32.024, 32.025999999999996, 32.028,
      32.03, 32.032, 32.034, 32.036, 32.038, 32.04, 32.042, 32.044, 32.046,
      32.048, 32.05, 32.052, 32.054, 32.056, 32.058, 32.06, 32.062, 32.064,
      32.066, 32.068, 32.07, 32.072, 32.074, 32.076, 32.078, 32.08, 32.082,
      32.084, 32.086, 32.088, 32.09, 32.092, 32.094, 32.096000000000004, 32.098,
      32.1, 32.102000000000004, 32.104, 32.106, 32.108000000000004, 32.11,
      32.112, 32.114, 32.116, 32.118, 32.12, 32.122, 32.124, 32.126, 32.128,
      32.129999999999995, 32.132, 32.134, 32.135999999999996, 32.138, 32.14,
      32.141999999999996, 32.144, 32.146, 32.147999999999996, 32.15, 32.152,
      32.153999999999996, 32.156, 32.158, 32.16, 32.162, 32.164, 32.166, 32.168,
      32.17, 32.172, 32.174, 32.176, 32.178, 32.18, 32.182, 32.184, 32.186,
      32.188, 32.19, 32.192, 32.194, 32.196, 32.198, 32.2, 32.202, 32.204,
      32.206, 32.208, 32.21, 32.212, 32.214, 32.216, 32.218, 32.22, 32.222,
      32.224000000000004, 32.226, 32.228, 32.230000000000004, 32.232, 32.234,
      32.236, 32.238, 32.24, 32.242, 32.244, 32.246, 32.248, 32.25,
      32.251999999999995, 32.254, 32.256, 32.257999999999996, 32.26, 32.262,
      32.263999999999996, 32.266, 32.268, 32.269999999999996, 32.272, 32.274,
      32.275999999999996, 32.278, 32.28, 32.282, 32.284, 32.286, 32.288, 32.29,
      32.292, 32.294, 32.296, 32.298, 32.3, 32.302, 32.304, 32.306, 32.308,
      32.31, 32.312, 32.314, 32.316, 32.318, 32.32, 32.322, 32.324, 32.326,
      32.328, 32.33, 32.332, 32.334, 32.336, 32.338, 32.34, 32.342, 32.344,
      32.346000000000004, 32.348, 32.35, 32.352000000000004, 32.354, 32.356,
      32.358000000000004, 32.36, 32.362, 32.364, 32.366, 32.368, 32.37, 32.372,
      32.374, 32.376, 32.378, 32.379999999999995, 32.382, 32.384,
      32.385999999999996, 32.388, 32.39, 32.391999999999996, 32.394, 32.396,
      32.397999999999996, 32.4, 32.402, 32.403999999999996, 32.406, 32.408,
      32.41, 32.412, 32.414, 32.416, 32.418, 32.42, 32.422, 32.424, 32.426,
      32.428, 32.43, 32.432, 32.434, 32.436, 32.438, 32.44, 32.442, 32.444,
      32.446, 32.448, 32.45, 32.452, 32.454, 32.456, 32.458, 32.46, 32.462,
      32.464, 32.466, 32.468, 32.47, 32.472, 32.474000000000004, 32.476, 32.478,
      32.480000000000004, 32.482, 32.484, 32.486, 32.488, 32.49, 32.492, 32.494,
      32.496, 32.498, 32.5, 32.501999999999995, 32.504, 32.506,
      32.507999999999996, 32.51, 32.512, 32.513999999999996, 32.516, 32.518,
      32.519999999999996, 32.522, 32.524, 32.525999999999996, 32.528, 32.53,
      32.532, 32.534, 32.536, 32.538, 32.54, 32.542, 32.544, 32.546, 32.548,
      32.55, 32.552, 32.554, 32.556, 32.558, 32.56, 32.562, 32.564, 32.566,
      32.568, 32.57, 32.572, 32.574, 32.576, 32.578, 32.58, 32.582, 32.584,
      32.586, 32.588, 32.59, 32.592, 32.594, 32.596000000000004, 32.598, 32.6,
      32.602000000000004, 32.604, 32.606, 32.608000000000004, 32.61, 32.612,
      32.614, 32.616, 32.618, 32.62, 32.622, 32.624, 32.626, 32.628,
      32.629999999999995, 32.632, 32.634, 32.635999999999996, 32.638, 32.64,
      32.641999999999996, 32.644, 32.646, 32.647999999999996, 32.65, 32.652,
      32.653999999999996, 32.656, 32.658, 32.66, 32.662, 32.664, 32.666, 32.668,
      32.67, 32.672, 32.674, 32.676, 32.678, 32.68, 32.682, 32.684, 32.686,
      32.688, 32.69, 32.692, 32.694, 32.696, 32.698, 32.7, 32.702, 32.704,
      32.706, 32.708, 32.71, 32.712, 32.714, 32.716, 32.718, 32.72, 32.722,
      32.724000000000004, 32.726, 32.728, 32.730000000000004, 32.732, 32.734,
      32.736, 32.738, 32.74, 32.742, 32.744, 32.746, 32.748, 32.75,
      32.751999999999995, 32.754, 32.756, 32.757999999999996, 32.76, 32.762,
      32.763999999999996, 32.766, 32.768, 32.769999999999996, 32.772, 32.774,
      32.775999999999996, 32.778, 32.78, 32.782, 32.784, 32.786, 32.788, 32.79,
      32.792, 32.794, 32.796, 32.798, 32.8, 32.802, 32.804, 32.806, 32.808,
      32.81, 32.812, 32.814, 32.816, 32.818, 32.82, 32.822, 32.824, 32.826,
      32.828, 32.83, 32.832, 32.834, 32.836, 32.838, 32.84, 32.842, 32.844,
      32.846000000000004, 32.848, 32.85, 32.852000000000004, 32.854, 32.856,
      32.858000000000004, 32.86, 32.862, 32.864, 32.866, 32.868, 32.87, 32.872,
      32.874, 32.876, 32.878, 32.879999999999995, 32.882, 32.884,
      32.885999999999996, 32.888, 32.89, 32.891999999999996, 32.894, 32.896,
      32.897999999999996, 32.9, 32.902, 32.903999999999996, 32.906, 32.908,
      32.91, 32.912, 32.914, 32.916, 32.918, 32.92, 32.922, 32.924, 32.926,
      32.928, 32.93, 32.932, 32.934, 32.936, 32.938, 32.94, 32.942, 32.944,
      32.946, 32.948, 32.95, 32.952, 32.954, 32.956, 32.958, 32.96, 32.962,
      32.964, 32.966, 32.968, 32.97, 32.972, 32.974000000000004, 32.976, 32.978,
      32.980000000000004, 32.982, 32.984, 32.986, 32.988, 32.99, 32.992, 32.994,
      32.996, 32.998, 33.0, 33.001999999999995, 33.004, 33.006,
      33.007999999999996, 33.01, 33.012, 33.013999999999996, 33.016, 33.018,
      33.019999999999996, 33.022, 33.024, 33.025999999999996, 33.028, 33.03,
      33.032, 33.034, 33.036, 33.038, 33.04, 33.042, 33.044, 33.046, 33.048,
      33.05, 33.052, 33.054, 33.056, 33.058, 33.06, 33.062, 33.064, 33.066,
      33.068, 33.07, 33.072, 33.074, 33.076, 33.078, 33.08, 33.082, 33.084,
      33.086, 33.088, 33.09, 33.092, 33.094, 33.096000000000004, 33.098, 33.1,
      33.102000000000004, 33.104, 33.106, 33.108000000000004, 33.11, 33.112,
      33.114, 33.116, 33.118, 33.12, 33.122, 33.124, 33.126, 33.128,
      33.129999999999995, 33.132, 33.134, 33.135999999999996, 33.138, 33.14,
      33.141999999999996, 33.144, 33.146, 33.147999999999996, 33.15, 33.152,
      33.153999999999996, 33.156, 33.158, 33.16, 33.162, 33.164, 33.166, 33.168,
      33.17, 33.172, 33.174, 33.176, 33.178, 33.18, 33.182, 33.184, 33.186,
      33.188, 33.19, 33.192, 33.194, 33.196, 33.198, 33.2, 33.202, 33.204,
      33.206, 33.208, 33.21, 33.212, 33.214, 33.216, 33.218, 33.22, 33.222,
      33.224000000000004, 33.226, 33.228, 33.230000000000004, 33.232, 33.234,
      33.236, 33.238, 33.24, 33.242, 33.244, 33.246, 33.248, 33.25,
      33.251999999999995, 33.254, 33.256, 33.257999999999996, 33.26, 33.262,
      33.263999999999996, 33.266, 33.268, 33.269999999999996, 33.272, 33.274,
      33.275999999999996, 33.278, 33.28, 33.282, 33.284, 33.286, 33.288, 33.29,
      33.292, 33.294, 33.296, 33.298, 33.3, 33.302, 33.304, 33.306, 33.308,
      33.31, 33.312, 33.314, 33.316, 33.318, 33.32, 33.322, 33.324, 33.326,
      33.328, 33.33, 33.332, 33.334, 33.336, 33.338, 33.34, 33.342, 33.344,
      33.346000000000004, 33.348, 33.35, 33.352000000000004, 33.354, 33.356,
      33.358000000000004, 33.36, 33.362, 33.364, 33.366, 33.368, 33.37, 33.372,
      33.374, 33.376, 33.378, 33.379999999999995, 33.382, 33.384,
      33.385999999999996, 33.388, 33.39, 33.391999999999996, 33.394, 33.396,
      33.397999999999996, 33.4, 33.402, 33.403999999999996, 33.406, 33.408,
      33.41, 33.412, 33.414, 33.416, 33.418, 33.42, 33.422, 33.424, 33.426,
      33.428, 33.43, 33.432, 33.434, 33.436, 33.438, 33.44, 33.442, 33.444,
      33.446, 33.448, 33.45, 33.452, 33.454, 33.456, 33.458, 33.46, 33.462,
      33.464, 33.466, 33.468, 33.47, 33.472, 33.474000000000004, 33.476, 33.478,
      33.480000000000004, 33.482, 33.484, 33.486, 33.488, 33.49, 33.492, 33.494,
      33.496, 33.498, 33.5, 33.501999999999995, 33.504, 33.506,
      33.507999999999996, 33.51, 33.512, 33.513999999999996, 33.516, 33.518,
      33.519999999999996, 33.522, 33.524, 33.525999999999996, 33.528, 33.53,
      33.532, 33.534, 33.536, 33.538, 33.54, 33.542, 33.544, 33.546, 33.548,
      33.55, 33.552, 33.554, 33.556, 33.558, 33.56, 33.562, 33.564, 33.566,
      33.568, 33.57, 33.572, 33.574, 33.576, 33.578, 33.58, 33.582, 33.584,
      33.586, 33.588, 33.59, 33.592, 33.594, 33.596000000000004, 33.598, 33.6,
      33.602000000000004, 33.604, 33.606, 33.608000000000004, 33.61, 33.612,
      33.614, 33.616, 33.618, 33.62, 33.622, 33.624, 33.626, 33.628,
      33.629999999999995, 33.632, 33.634, 33.635999999999996, 33.638, 33.64,
      33.641999999999996, 33.644, 33.646, 33.647999999999996, 33.65, 33.652,
      33.653999999999996, 33.656, 33.658, 33.66, 33.662, 33.664, 33.666, 33.668,
      33.67, 33.672, 33.674, 33.676, 33.678, 33.68, 33.682, 33.684, 33.686,
      33.688, 33.69, 33.692, 33.694, 33.696, 33.698, 33.7, 33.702, 33.704,
      33.706, 33.708, 33.71, 33.712, 33.714, 33.716, 33.718, 33.72, 33.722,
      33.724000000000004, 33.726, 33.728, 33.730000000000004, 33.732, 33.734,
      33.736000000000004, 33.738, 33.74, 33.742, 33.744, 33.746, 33.748, 33.75,
      33.751999999999995, 33.754, 33.756, 33.757999999999996, 33.76, 33.762,
      33.763999999999996, 33.766, 33.768, 33.769999999999996, 33.772, 33.774,
      33.775999999999996, 33.778, 33.78, 33.782, 33.784, 33.786, 33.788, 33.79,
      33.792, 33.794, 33.796, 33.798, 33.8, 33.802, 33.804, 33.806, 33.808,
      33.81, 33.812, 33.814, 33.816, 33.818, 33.82, 33.822, 33.824, 33.826,
      33.828, 33.83, 33.832, 33.834, 33.836, 33.838, 33.84, 33.842, 33.844,
      33.846000000000004, 33.848, 33.85, 33.852000000000004, 33.854, 33.856,
      33.858000000000004, 33.86, 33.862, 33.864, 33.866, 33.868, 33.87, 33.872,
      33.874, 33.876, 33.878, 33.879999999999995, 33.882, 33.884,
      33.885999999999996, 33.888, 33.89, 33.891999999999996, 33.894, 33.896,
      33.897999999999996, 33.9, 33.902, 33.903999999999996, 33.906, 33.908,
      33.91, 33.912, 33.914, 33.916, 33.918, 33.92, 33.922, 33.924, 33.926,
      33.928, 33.93, 33.932, 33.934, 33.936, 33.938, 33.94, 33.942, 33.944,
      33.946, 33.948, 33.95, 33.952, 33.954, 33.956, 33.958, 33.96, 33.962,
      33.964, 33.966, 33.968, 33.97, 33.972, 33.974000000000004, 33.976, 33.978,
      33.980000000000004, 33.982, 33.984, 33.986000000000004, 33.988, 33.99,
      33.992, 33.994, 33.996, 33.998, 34.0, 34.001999999999995, 34.004, 34.006,
      34.007999999999996, 34.01, 34.012, 34.013999999999996, 34.016, 34.018,
      34.019999999999996, 34.022, 34.024, 34.025999999999996, 34.028, 34.03,
      34.032, 34.034, 34.036, 34.038, 34.04, 34.042, 34.044, 34.046, 34.048,
      34.05, 34.052, 34.054, 34.056, 34.058, 34.06, 34.062, 34.064, 34.066,
      34.068, 34.07, 34.072, 34.074, 34.076, 34.078, 34.08, 34.082, 34.084,
      34.086, 34.088, 34.09, 34.092, 34.094, 34.096000000000004, 34.098, 34.1,
      34.102000000000004, 34.104, 34.106, 34.108000000000004, 34.11, 34.112,
      34.114, 34.116, 34.118, 34.12, 34.122, 34.124, 34.126, 34.128,
      34.129999999999995, 34.132, 34.134, 34.135999999999996, 34.138, 34.14,
      34.141999999999996, 34.144, 34.146, 34.147999999999996, 34.15, 34.152,
      34.153999999999996, 34.156, 34.158, 34.16, 34.162, 34.164, 34.166, 34.168,
      34.17, 34.172, 34.174, 34.176, 34.178, 34.18, 34.182, 34.184, 34.186,
      34.188, 34.19, 34.192, 34.194, 34.196, 34.198, 34.2, 34.202, 34.204,
      34.206, 34.208, 34.21, 34.212, 34.214, 34.216, 34.218, 34.22, 34.222,
      34.224000000000004, 34.226, 34.228, 34.230000000000004, 34.232, 34.234,
      34.236000000000004, 34.238, 34.24, 34.242, 34.244, 34.246, 34.248, 34.25,
      34.251999999999995, 34.254, 34.256, 34.257999999999996, 34.26, 34.262,
      34.263999999999996, 34.266, 34.268, 34.269999999999996, 34.272, 34.274,
      34.275999999999996, 34.278, 34.28, 34.282, 34.284, 34.286, 34.288, 34.29,
      34.292, 34.294, 34.296, 34.298, 34.3, 34.302, 34.304, 34.306, 34.308,
      34.31, 34.312, 34.314, 34.316, 34.318, 34.32, 34.322, 34.324, 34.326,
      34.328, 34.33, 34.332, 34.334, 34.336, 34.338, 34.34, 34.342, 34.344,
      34.346000000000004, 34.348, 34.35, 34.352000000000004, 34.354, 34.356,
      34.358000000000004, 34.36, 34.362, 34.364, 34.366, 34.368, 34.37, 34.372,
      34.374, 34.376, 34.378, 34.379999999999995, 34.382, 34.384,
      34.385999999999996, 34.388, 34.39, 34.391999999999996, 34.394, 34.396,
      34.397999999999996, 34.4, 34.402, 34.403999999999996, 34.406, 34.408,
      34.41, 34.412, 34.414, 34.416, 34.418, 34.42, 34.422, 34.424, 34.426,
      34.428, 34.43, 34.432, 34.434, 34.436, 34.438, 34.44, 34.442, 34.444,
      34.446, 34.448, 34.45, 34.452, 34.454, 34.456, 34.458, 34.46, 34.462,
      34.464, 34.466, 34.468, 34.47, 34.472, 34.474000000000004, 34.476, 34.478,
      34.480000000000004, 34.482, 34.484, 34.486000000000004, 34.488, 34.49,
      34.492, 34.494, 34.496, 34.498, 34.5, 34.502, 34.504, 34.506,
      34.507999999999996, 34.51, 34.512, 34.513999999999996, 34.516, 34.518,
      34.519999999999996, 34.522, 34.524, 34.525999999999996, 34.528, 34.53,
      34.532, 34.534, 34.536, 34.538, 34.54, 34.542, 34.544, 34.546, 34.548,
      34.55, 34.552, 34.554, 34.556, 34.558, 34.56, 34.562, 34.564, 34.566,
      34.568, 34.57, 34.572, 34.574, 34.576, 34.578, 34.58, 34.582, 34.584,
      34.586, 34.588, 34.59, 34.592, 34.594, 34.596000000000004, 34.598, 34.6,
      34.602000000000004, 34.604, 34.606, 34.608000000000004, 34.61, 34.612,
      34.614, 34.616, 34.618, 34.62, 34.622, 34.624, 34.626, 34.628,
      34.629999999999995, 34.632, 34.634, 34.635999999999996, 34.638, 34.64,
      34.641999999999996, 34.644, 34.646, 34.647999999999996, 34.65, 34.652,
      34.653999999999996, 34.656, 34.658, 34.66, 34.662, 34.664, 34.666, 34.668,
      34.67, 34.672, 34.674, 34.676, 34.678, 34.68, 34.682, 34.684, 34.686,
      34.688, 34.69, 34.692, 34.694, 34.696, 34.698, 34.7, 34.702, 34.704,
      34.706, 34.708, 34.71, 34.712, 34.714, 34.716, 34.718, 34.72, 34.722,
      34.724000000000004, 34.726, 34.728, 34.730000000000004, 34.732, 34.734,
      34.736000000000004, 34.738, 34.74, 34.742, 34.744, 34.746, 34.748, 34.75,
      34.752, 34.754, 34.756, 34.757999999999996, 34.76, 34.762,
      34.763999999999996, 34.766, 34.768, 34.769999999999996, 34.772, 34.774,
      34.775999999999996, 34.778, 34.78, 34.782, 34.784, 34.786, 34.788, 34.79,
      34.792, 34.794, 34.796, 34.798, 34.8, 34.802, 34.804, 34.806, 34.808,
      34.81, 34.812, 34.814, 34.816, 34.818, 34.82, 34.822, 34.824, 34.826,
      34.828, 34.83, 34.832, 34.834, 34.836, 34.838, 34.84, 34.842, 34.844,
      34.846000000000004, 34.848, 34.85, 34.852000000000004, 34.854, 34.856,
      34.858000000000004, 34.86, 34.862, 34.864, 34.866, 34.868, 34.87, 34.872,
      34.874, 34.876, 34.878, 34.879999999999995, 34.882, 34.884,
      34.885999999999996, 34.888, 34.89, 34.891999999999996, 34.894, 34.896,
      34.897999999999996, 34.9, 34.902, 34.903999999999996, 34.906, 34.908,
      34.91, 34.912, 34.914, 34.916, 34.918, 34.92, 34.922, 34.924, 34.926,
      34.928, 34.93, 34.932, 34.934, 34.936, 34.938, 34.94, 34.942, 34.944,
      34.946, 34.948, 34.95, 34.952, 34.954, 34.956, 34.958, 34.96, 34.962,
      34.964, 34.966, 34.968, 34.97, 34.972, 34.974000000000004, 34.976, 34.978,
      34.980000000000004, 34.982, 34.984, 34.986000000000004, 34.988, 34.99,
      34.992, 34.994, 34.996, 34.998, 35.0, 35.002, 35.004, 35.006,
      35.007999999999996, 35.01, 35.012, 35.013999999999996, 35.016, 35.018,
      35.019999999999996, 35.022, 35.024, 35.025999999999996, 35.028, 35.03,
      35.032, 35.034, 35.036, 35.038, 35.04, 35.042, 35.044, 35.046, 35.048,
      35.05, 35.052, 35.054, 35.056, 35.058, 35.06, 35.062, 35.064, 35.066,
      35.068, 35.07, 35.072, 35.074, 35.076, 35.078, 35.08, 35.082, 35.084,
      35.086, 35.088, 35.09, 35.092, 35.094, 35.096000000000004, 35.098, 35.1,
      35.102000000000004, 35.104, 35.106, 35.108000000000004, 35.11, 35.112,
      35.114, 35.116, 35.118, 35.12, 35.122, 35.124, 35.126, 35.128,
      35.129999999999995, 35.132, 35.134, 35.135999999999996, 35.138, 35.14,
      35.141999999999996, 35.144, 35.146, 35.147999999999996, 35.15, 35.152,
      35.153999999999996, 35.156, 35.158, 35.16, 35.162, 35.164, 35.166, 35.168,
      35.17, 35.172, 35.174, 35.176, 35.178, 35.18, 35.182, 35.184, 35.186,
      35.188, 35.19, 35.192, 35.194, 35.196, 35.198, 35.2, 35.202, 35.204,
      35.206, 35.208, 35.21, 35.212, 35.214, 35.216, 35.218, 35.22, 35.222,
      35.224000000000004, 35.226, 35.228, 35.230000000000004, 35.232, 35.234,
      35.236000000000004, 35.238, 35.24, 35.242, 35.244, 35.246, 35.248, 35.25,
      35.252, 35.254, 35.256, 35.257999999999996, 35.26, 35.262,
      35.263999999999996, 35.266, 35.268, 35.269999999999996, 35.272, 35.274,
      35.275999999999996, 35.278, 35.28, 35.282, 35.284, 35.286, 35.288, 35.29,
      35.292, 35.294, 35.296, 35.298, 35.3, 35.302, 35.304, 35.306, 35.308,
      35.31, 35.312, 35.314, 35.316, 35.318, 35.32, 35.322, 35.324, 35.326,
      35.328, 35.33, 35.332, 35.334, 35.336, 35.338, 35.34, 35.342, 35.344,
      35.346000000000004, 35.348, 35.35, 35.352000000000004, 35.354, 35.356,
      35.358000000000004, 35.36, 35.362, 35.364, 35.366, 35.368, 35.37, 35.372,
      35.374, 35.376, 35.378, 35.379999999999995, 35.382, 35.384,
      35.385999999999996, 35.388, 35.39, 35.391999999999996, 35.394, 35.396,
      35.397999999999996, 35.4, 35.402, 35.403999999999996, 35.406, 35.408,
      35.41, 35.412, 35.414, 35.416, 35.418, 35.42, 35.422, 35.424, 35.426,
      35.428, 35.43, 35.432, 35.434, 35.436, 35.438, 35.44, 35.442, 35.444,
      35.446, 35.448, 35.45, 35.452, 35.454, 35.456, 35.458, 35.46, 35.462,
      35.464, 35.466, 35.468, 35.47, 35.472, 35.474000000000004, 35.476, 35.478,
      35.480000000000004, 35.482, 35.484, 35.486000000000004, 35.488, 35.49,
      35.492, 35.494, 35.496, 35.498, 35.5, 35.502, 35.504, 35.506,
      35.507999999999996, 35.51, 35.512, 35.513999999999996, 35.516, 35.518,
      35.519999999999996, 35.522, 35.524, 35.525999999999996, 35.528, 35.53,
      35.532, 35.534, 35.536, 35.538, 35.54, 35.542, 35.544, 35.546, 35.548,
      35.55, 35.552, 35.554, 35.556, 35.558, 35.56, 35.562, 35.564, 35.566,
      35.568, 35.57, 35.572, 35.574, 35.576, 35.578, 35.58, 35.582, 35.584,
      35.586, 35.588, 35.59, 35.592, 35.594, 35.596000000000004, 35.598, 35.6,
      35.602000000000004, 35.604, 35.606, 35.608000000000004, 35.61, 35.612,
      35.614, 35.616, 35.618, 35.62, 35.622, 35.624, 35.626, 35.628,
      35.629999999999995, 35.632, 35.634, 35.635999999999996, 35.638, 35.64,
      35.641999999999996, 35.644, 35.646, 35.647999999999996, 35.65, 35.652,
      35.653999999999996, 35.656, 35.658, 35.66, 35.662, 35.664, 35.666, 35.668,
      35.67, 35.672, 35.674, 35.676, 35.678, 35.68, 35.682, 35.684, 35.686,
      35.688, 35.69, 35.692, 35.694, 35.696, 35.698, 35.7, 35.702, 35.704,
      35.706, 35.708, 35.71, 35.712, 35.714, 35.716, 35.718, 35.72, 35.722,
      35.724000000000004, 35.726, 35.728, 35.730000000000004, 35.732, 35.734,
      35.736000000000004, 35.738, 35.74, 35.742, 35.744, 35.746, 35.748, 35.75,
      35.752, 35.754, 35.756, 35.757999999999996, 35.76, 35.762,
      35.763999999999996, 35.766, 35.768, 35.769999999999996, 35.772, 35.774,
      35.775999999999996, 35.778, 35.78, 35.782, 35.784, 35.786, 35.788, 35.79,
      35.792, 35.794, 35.796, 35.798, 35.8, 35.802, 35.804, 35.806, 35.808,
      35.81, 35.812, 35.814, 35.816, 35.818, 35.82, 35.822, 35.824, 35.826,
      35.828, 35.83, 35.832, 35.834, 35.836, 35.838, 35.84, 35.842, 35.844,
      35.846000000000004, 35.848, 35.85, 35.852000000000004, 35.854, 35.856,
      35.858000000000004, 35.86, 35.862, 35.864, 35.866, 35.868, 35.87, 35.872,
      35.874, 35.876, 35.878, 35.879999999999995, 35.882, 35.884,
      35.885999999999996, 35.888, 35.89, 35.891999999999996, 35.894, 35.896,
      35.897999999999996, 35.9, 35.902, 35.903999999999996, 35.906, 35.908,
      35.91, 35.912, 35.914, 35.916, 35.918, 35.92, 35.922, 35.924, 35.926,
      35.928, 35.93, 35.932, 35.934, 35.936, 35.938, 35.94, 35.942, 35.944,
      35.946, 35.948, 35.95, 35.952, 35.954, 35.956, 35.958, 35.96, 35.962,
      35.964, 35.966, 35.968, 35.97, 35.972, 35.974000000000004, 35.976, 35.978,
      35.980000000000004, 35.982, 35.984, 35.986000000000004, 35.988, 35.99,
      35.992, 35.994, 35.996, 35.998, 36.0, 36.002, 36.004, 36.006,
      36.007999999999996, 36.01, 36.012, 36.013999999999996, 36.016, 36.018,
      36.019999999999996, 36.022, 36.024, 36.025999999999996, 36.028, 36.03,
      36.032, 36.034, 36.036, 36.038, 36.04, 36.042, 36.044, 36.046, 36.048,
      36.05, 36.052, 36.054, 36.056, 36.058, 36.06, 36.062, 36.064, 36.066,
      36.068, 36.07, 36.072, 36.074, 36.076, 36.078, 36.08, 36.082, 36.084,
      36.086, 36.088, 36.09, 36.092, 36.094, 36.096000000000004, 36.098, 36.1,
      36.102000000000004, 36.104, 36.106, 36.108000000000004, 36.11, 36.112,
      36.114, 36.116, 36.118, 36.12, 36.122, 36.124, 36.126, 36.128,
      36.129999999999995, 36.132, 36.134, 36.135999999999996, 36.138, 36.14,
      36.141999999999996, 36.144, 36.146, 36.147999999999996, 36.15, 36.152,
      36.153999999999996, 36.156, 36.158, 36.16, 36.162, 36.164, 36.166, 36.168,
      36.17, 36.172, 36.174, 36.176, 36.178, 36.18, 36.182, 36.184, 36.186,
      36.188, 36.19, 36.192, 36.194, 36.196, 36.198, 36.2, 36.202, 36.204,
      36.206, 36.208, 36.21, 36.212, 36.214, 36.216, 36.218, 36.22, 36.222,
      36.224000000000004, 36.226, 36.228, 36.230000000000004, 36.232, 36.234,
      36.236000000000004, 36.238, 36.24, 36.242, 36.244, 36.246, 36.248, 36.25,
      36.252, 36.254, 36.256, 36.257999999999996, 36.26, 36.262,
      36.263999999999996, 36.266, 36.268, 36.269999999999996, 36.272, 36.274,
      36.275999999999996, 36.278, 36.28, 36.282, 36.284, 36.286, 36.288, 36.29,
      36.292, 36.294, 36.296, 36.298, 36.3, 36.302, 36.304, 36.306, 36.308,
      36.31, 36.312, 36.314, 36.316, 36.318, 36.32, 36.322, 36.324, 36.326,
      36.328, 36.33, 36.332, 36.334, 36.336, 36.338, 36.34, 36.342, 36.344,
      36.346000000000004, 36.348, 36.35, 36.352000000000004, 36.354, 36.356,
      36.358000000000004, 36.36, 36.362, 36.364, 36.366, 36.368, 36.37, 36.372,
      36.374, 36.376, 36.378, 36.379999999999995, 36.382, 36.384,
      36.385999999999996, 36.388, 36.39, 36.391999999999996, 36.394, 36.396,
      36.397999999999996, 36.4, 36.402, 36.403999999999996, 36.406, 36.408,
      36.41, 36.412, 36.414, 36.416, 36.418, 36.42, 36.422, 36.424, 36.426,
      36.428, 36.43, 36.432, 36.434, 36.436, 36.438, 36.44, 36.442, 36.444,
      36.446, 36.448, 36.45, 36.452, 36.454, 36.456, 36.458, 36.46, 36.462,
      36.464, 36.466, 36.468, 36.47, 36.472, 36.474000000000004, 36.476, 36.478,
      36.480000000000004, 36.482, 36.484, 36.486000000000004, 36.488, 36.49,
      36.492, 36.494, 36.496, 36.498, 36.5, 36.502, 36.504, 36.506,
      36.507999999999996, 36.51, 36.512, 36.513999999999996, 36.516, 36.518,
      36.519999999999996, 36.522, 36.524, 36.525999999999996, 36.528, 36.53,
      36.532, 36.534, 36.536, 36.538, 36.54, 36.542, 36.544, 36.546, 36.548,
      36.55, 36.552, 36.554, 36.556, 36.558, 36.56, 36.562, 36.564, 36.566,
      36.568, 36.57, 36.572, 36.574, 36.576, 36.578, 36.58, 36.582, 36.584,
      36.586, 36.588, 36.59, 36.592, 36.594, 36.596000000000004, 36.598, 36.6,
      36.602000000000004, 36.604, 36.606, 36.608000000000004, 36.61, 36.612,
      36.614, 36.616, 36.618, 36.62, 36.622, 36.624, 36.626, 36.628,
      36.629999999999995, 36.632, 36.634, 36.635999999999996, 36.638, 36.64,
      36.641999999999996, 36.644, 36.646, 36.647999999999996, 36.65, 36.652,
      36.653999999999996, 36.656, 36.658, 36.66, 36.662, 36.664, 36.666, 36.668,
      36.67, 36.672, 36.674, 36.676, 36.678, 36.68, 36.682, 36.684, 36.686,
      36.688, 36.69, 36.692, 36.694, 36.696, 36.698, 36.7, 36.702, 36.704,
      36.706, 36.708, 36.71, 36.712, 36.714, 36.716, 36.718, 36.72, 36.722,
      36.724000000000004, 36.726, 36.728, 36.730000000000004, 36.732, 36.734,
      36.736000000000004, 36.738, 36.74, 36.742, 36.744, 36.746, 36.748, 36.75,
      36.752, 36.754, 36.756, 36.757999999999996, 36.76, 36.762,
      36.763999999999996, 36.766, 36.768, 36.769999999999996, 36.772, 36.774,
      36.775999999999996, 36.778, 36.78, 36.782, 36.784, 36.786, 36.788, 36.79,
      36.792, 36.794, 36.796, 36.798, 36.8, 36.802, 36.804, 36.806, 36.808,
      36.81, 36.812, 36.814, 36.816, 36.818, 36.82, 36.822, 36.824, 36.826,
      36.828, 36.83, 36.832, 36.834, 36.836, 36.838, 36.84, 36.842, 36.844,
      36.846000000000004, 36.848, 36.85, 36.852000000000004, 36.854, 36.856,
      36.858000000000004, 36.86, 36.862, 36.864, 36.866, 36.868, 36.87, 36.872,
      36.874, 36.876, 36.878, 36.879999999999995, 36.882, 36.884,
      36.885999999999996, 36.888, 36.89, 36.891999999999996, 36.894, 36.896,
      36.897999999999996, 36.9, 36.902, 36.903999999999996, 36.906, 36.908,
      36.91, 36.912, 36.914, 36.916, 36.918, 36.92, 36.922, 36.924, 36.926,
      36.928, 36.93, 36.932, 36.934, 36.936, 36.938, 36.94, 36.942, 36.944,
      36.946, 36.948, 36.95, 36.952, 36.954, 36.956, 36.958, 36.96, 36.962,
      36.964, 36.966, 36.968, 36.97, 36.972, 36.974000000000004, 36.976, 36.978,
      36.980000000000004, 36.982, 36.984, 36.986000000000004, 36.988, 36.99,
      36.992, 36.994, 36.996, 36.998, 37.0, 37.002, 37.004, 37.006, 37.008,
      37.01, 37.012, 37.014, 37.016, 37.018, 37.019999999999996, 37.022, 37.024,
      37.025999999999996, 37.028, 37.03, 37.032, 37.034, 37.036, 37.038, 37.04,
      37.042, 37.044, 37.046, 37.048, 37.05, 37.052, 37.054, 37.056, 37.058,
      37.06, 37.062, 37.064, 37.066, 37.068, 37.07, 37.072, 37.074, 37.076,
      37.078, 37.08, 37.082, 37.084, 37.086, 37.088, 37.09, 37.092, 37.094,
      37.096000000000004, 37.098, 37.1, 37.102, 37.104, 37.106, 37.108, 37.11,
      37.112, 37.114, 37.116, 37.118, 37.12, 37.122, 37.124, 37.126, 37.128,
      37.13, 37.132, 37.134, 37.136, 37.138, 37.14, 37.141999999999996, 37.144,
      37.146, 37.147999999999996, 37.15, 37.152, 37.153999999999996, 37.156,
      37.158, 37.16, 37.162, 37.164, 37.166, 37.168, 37.17, 37.172, 37.174,
      37.176, 37.178, 37.18, 37.182, 37.184, 37.186, 37.188, 37.19, 37.192,
      37.194, 37.196, 37.198, 37.2, 37.202, 37.204, 37.206, 37.208, 37.21,
      37.212, 37.214, 37.216, 37.218, 37.22, 37.222, 37.224000000000004, 37.226,
      37.228, 37.23, 37.232, 37.234, 37.236, 37.238, 37.24, 37.242, 37.244,
      37.246, 37.248, 37.25, 37.252, 37.254, 37.256, 37.258, 37.26, 37.262,
      37.264, 37.266, 37.268, 37.269999999999996, 37.272, 37.274,
      37.275999999999996, 37.278, 37.28, 37.282, 37.284, 37.286, 37.288, 37.29,
      37.292, 37.294, 37.296, 37.298, 37.3, 37.302, 37.304, 37.306, 37.308,
      37.31, 37.312, 37.314, 37.316, 37.318, 37.32, 37.322, 37.324, 37.326,
      37.328, 37.33, 37.332, 37.334, 37.336, 37.338, 37.34, 37.342, 37.344,
      37.346000000000004, 37.348, 37.35, 37.352, 37.354, 37.356, 37.358, 37.36,
      37.362, 37.364, 37.366, 37.368, 37.37, 37.372, 37.374, 37.376, 37.378,
      37.38, 37.382, 37.384, 37.386, 37.388, 37.39, 37.391999999999996, 37.394,
      37.396, 37.397999999999996, 37.4, 37.402, 37.403999999999996, 37.406,
      37.408, 37.41, 37.412, 37.414, 37.416, 37.418, 37.42, 37.422, 37.424,
      37.426, 37.428, 37.43, 37.432, 37.434, 37.436, 37.438, 37.44, 37.442,
      37.444, 37.446, 37.448, 37.45, 37.452, 37.454, 37.456, 37.458, 37.46,
      37.462, 37.464, 37.466, 37.468, 37.47, 37.472, 37.474000000000004, 37.476,
      37.478, 37.48, 37.482, 37.484, 37.486, 37.488, 37.49, 37.492, 37.494,
      37.496, 37.498, 37.5, 37.502, 37.504, 37.506, 37.508, 37.51, 37.512,
      37.514, 37.516, 37.518, 37.519999999999996, 37.522, 37.524,
      37.525999999999996, 37.528, 37.53, 37.532, 37.534, 37.536, 37.538, 37.54,
      37.542, 37.544, 37.546, 37.548, 37.55, 37.552, 37.554, 37.556, 37.558,
      37.56, 37.562, 37.564, 37.566, 37.568, 37.57, 37.572, 37.574, 37.576,
      37.578, 37.58, 37.582, 37.584, 37.586, 37.588, 37.59, 37.592, 37.594,
      37.596000000000004, 37.598, 37.6, 37.602, 37.604, 37.606, 37.608, 37.61,
      37.612, 37.614, 37.616, 37.618, 37.62, 37.622, 37.624, 37.626, 37.628,
      37.63, 37.632, 37.634, 37.636, 37.638, 37.64, 37.641999999999996, 37.644,
      37.646, 37.647999999999996, 37.65, 37.652, 37.653999999999996, 37.656,
      37.658, 37.66, 37.662, 37.664, 37.666, 37.668, 37.67, 37.672, 37.674,
      37.676, 37.678, 37.68, 37.682, 37.684, 37.686, 37.688, 37.69, 37.692,
      37.694, 37.696, 37.698, 37.7, 37.702, 37.704, 37.706, 37.708, 37.71,
      37.712, 37.714, 37.716, 37.718, 37.72, 37.722, 37.724000000000004, 37.726,
      37.728, 37.73, 37.732, 37.734, 37.736, 37.738, 37.74, 37.742, 37.744,
      37.746, 37.748, 37.75, 37.752, 37.754, 37.756, 37.758, 37.76, 37.762,
      37.764, 37.766, 37.768, 37.769999999999996, 37.772, 37.774,
      37.775999999999996, 37.778, 37.78, 37.782, 37.784, 37.786, 37.788, 37.79,
      37.792, 37.794, 37.796, 37.798, 37.8, 37.802, 37.804, 37.806, 37.808,
      37.81, 37.812, 37.814, 37.816, 37.818, 37.82, 37.822, 37.824, 37.826,
      37.828, 37.83, 37.832, 37.834, 37.836, 37.838, 37.84, 37.842, 37.844,
      37.846000000000004, 37.848, 37.85, 37.852, 37.854, 37.856, 37.858, 37.86,
      37.862, 37.864, 37.866, 37.868, 37.87, 37.872, 37.874, 37.876, 37.878,
      37.88, 37.882, 37.884, 37.886, 37.888, 37.89, 37.891999999999996, 37.894,
      37.896, 37.897999999999996, 37.9, 37.902, 37.903999999999996, 37.906,
      37.908, 37.91, 37.912, 37.914, 37.916, 37.918, 37.92, 37.922, 37.924,
      37.926, 37.928, 37.93, 37.932, 37.934, 37.936, 37.938, 37.94, 37.942,
      37.944, 37.946, 37.948, 37.95, 37.952, 37.954, 37.956, 37.958, 37.96,
      37.962, 37.964, 37.966, 37.968, 37.97, 37.972, 37.974000000000004, 37.976,
      37.978, 37.98, 37.982, 37.984, 37.986, 37.988, 37.99, 37.992, 37.994,
      37.996, 37.998, 38.0, 38.002, 38.004, 38.006, 38.008, 38.01, 38.012,
      38.014, 38.016, 38.018, 38.019999999999996, 38.022, 38.024,
      38.025999999999996, 38.028, 38.03, 38.032, 38.034, 38.036, 38.038, 38.04,
      38.042, 38.044, 38.046, 38.048, 38.05, 38.052, 38.054, 38.056, 38.058,
      38.06, 38.062, 38.064, 38.066, 38.068, 38.07, 38.072, 38.074, 38.076,
      38.078, 38.08, 38.082, 38.084, 38.086, 38.088, 38.09, 38.092, 38.094,
      38.096000000000004, 38.098, 38.1, 38.102, 38.104, 38.106, 38.108, 38.11,
      38.112, 38.114, 38.116, 38.118, 38.12, 38.122, 38.124, 38.126, 38.128,
      38.13, 38.132, 38.134, 38.136, 38.138, 38.14, 38.141999999999996, 38.144,
      38.146, 38.147999999999996, 38.15, 38.152, 38.153999999999996, 38.156,
      38.158, 38.16, 38.162, 38.164, 38.166, 38.168, 38.17, 38.172, 38.174,
      38.176, 38.178, 38.18, 38.182, 38.184, 38.186, 38.188, 38.19, 38.192,
      38.194, 38.196, 38.198, 38.2, 38.202, 38.204, 38.206, 38.208, 38.21,
      38.212, 38.214, 38.216, 38.218, 38.22, 38.222, 38.224000000000004, 38.226,
      38.228, 38.23, 38.232, 38.234, 38.236, 38.238, 38.24, 38.242, 38.244,
      38.246, 38.248, 38.25, 38.252, 38.254, 38.256, 38.258, 38.26, 38.262,
      38.264, 38.266, 38.268, 38.269999999999996, 38.272, 38.274,
      38.275999999999996, 38.278, 38.28, 38.282, 38.284, 38.286, 38.288, 38.29,
      38.292, 38.294, 38.296, 38.298, 38.3, 38.302, 38.304, 38.306, 38.308,
      38.31, 38.312, 38.314, 38.316, 38.318, 38.32, 38.322, 38.324, 38.326,
      38.328, 38.33, 38.332, 38.334, 38.336, 38.338, 38.34, 38.342, 38.344,
      38.346000000000004, 38.348, 38.35, 38.352, 38.354, 38.356, 38.358, 38.36,
      38.362, 38.364, 38.366, 38.368, 38.37, 38.372, 38.374, 38.376, 38.378,
      38.38, 38.382, 38.384, 38.386, 38.388, 38.39, 38.391999999999996, 38.394,
      38.396, 38.397999999999996, 38.4, 38.402, 38.403999999999996, 38.406,
      38.408, 38.41, 38.412, 38.414, 38.416, 38.418, 38.42, 38.422, 38.424,
      38.426, 38.428, 38.43, 38.432, 38.434, 38.436, 38.438, 38.44, 38.442,
      38.444, 38.446, 38.448, 38.45, 38.452, 38.454, 38.456, 38.458, 38.46,
      38.462, 38.464, 38.466, 38.468, 38.47, 38.472, 38.474000000000004, 38.476,
      38.478, 38.48, 38.482, 38.484, 38.486, 38.488, 38.49, 38.492, 38.494,
      38.496, 38.498, 38.5, 38.502, 38.504, 38.506, 38.508, 38.51, 38.512,
      38.514, 38.516, 38.518, 38.519999999999996, 38.522, 38.524,
      38.525999999999996, 38.528, 38.53, 38.532, 38.534, 38.536, 38.538, 38.54,
      38.542, 38.544, 38.546, 38.548, 38.55, 38.552, 38.554, 38.556, 38.558,
      38.56, 38.562, 38.564, 38.566, 38.568, 38.57, 38.572, 38.574, 38.576,
      38.578, 38.58, 38.582, 38.584, 38.586, 38.588, 38.59, 38.592, 38.594,
      38.596000000000004, 38.598, 38.6, 38.602, 38.604, 38.606, 38.608, 38.61,
      38.612, 38.614, 38.616, 38.618, 38.62, 38.622, 38.624, 38.626, 38.628,
      38.63, 38.632, 38.634, 38.636, 38.638, 38.64, 38.641999999999996, 38.644,
      38.646, 38.647999999999996, 38.65, 38.652, 38.653999999999996, 38.656,
      38.658, 38.66, 38.662, 38.664, 38.666, 38.668, 38.67, 38.672, 38.674,
      38.676, 38.678, 38.68, 38.682, 38.684, 38.686, 38.688, 38.69, 38.692,
      38.694, 38.696, 38.698, 38.7, 38.702, 38.704, 38.706, 38.708, 38.71,
      38.712, 38.714, 38.716, 38.718, 38.72, 38.722, 38.724000000000004, 38.726,
      38.728, 38.73, 38.732, 38.734, 38.736, 38.738, 38.74, 38.742, 38.744,
      38.746, 38.748, 38.75, 38.752, 38.754, 38.756, 38.758, 38.76, 38.762,
      38.764, 38.766, 38.768, 38.769999999999996, 38.772, 38.774,
      38.775999999999996, 38.778, 38.78, 38.782, 38.784, 38.786, 38.788, 38.79,
      38.792, 38.794, 38.796, 38.798, 38.8, 38.802, 38.804, 38.806, 38.808,
      38.81, 38.812, 38.814, 38.816, 38.818, 38.82, 38.822, 38.824, 38.826,
      38.828, 38.83, 38.832, 38.834, 38.836, 38.838, 38.84, 38.842, 38.844,
      38.846000000000004, 38.848, 38.85, 38.852000000000004, 38.854, 38.856,
      38.858, 38.86, 38.862, 38.864, 38.866, 38.868, 38.87, 38.872, 38.874,
      38.876, 38.878, 38.88, 38.882, 38.884, 38.886, 38.888, 38.89,
      38.891999999999996, 38.894, 38.896, 38.897999999999996, 38.9, 38.902,
      38.903999999999996, 38.906, 38.908, 38.91, 38.912, 38.914, 38.916, 38.918,
      38.92, 38.922, 38.924, 38.926, 38.928, 38.93, 38.932, 38.934, 38.936,
      38.938, 38.94, 38.942, 38.944, 38.946, 38.948, 38.95, 38.952, 38.954,
      38.956, 38.958, 38.96, 38.962, 38.964, 38.966, 38.968, 38.97, 38.972,
      38.974000000000004, 38.976, 38.978, 38.98, 38.982, 38.984, 38.986, 38.988,
      38.99, 38.992, 38.994, 38.996, 38.998, 39.0, 39.002, 39.004, 39.006,
      39.008, 39.01, 39.012, 39.014, 39.016, 39.018, 39.019999999999996, 39.022,
      39.024, 39.025999999999996, 39.028, 39.03, 39.032, 39.034, 39.036, 39.038,
      39.04, 39.042, 39.044, 39.046, 39.048, 39.05, 39.052, 39.054, 39.056,
      39.058, 39.06, 39.062, 39.064, 39.066, 39.068, 39.07, 39.072, 39.074,
      39.076, 39.078, 39.08, 39.082, 39.084, 39.086, 39.088, 39.09, 39.092,
      39.094, 39.096000000000004, 39.098, 39.1, 39.102000000000004, 39.104,
      39.106, 39.108, 39.11, 39.112, 39.114, 39.116, 39.118, 39.12, 39.122,
      39.124, 39.126, 39.128, 39.13, 39.132, 39.134, 39.136, 39.138, 39.14,
      39.141999999999996, 39.144, 39.146, 39.147999999999996, 39.15, 39.152,
      39.153999999999996, 39.156, 39.158, 39.16, 39.162, 39.164, 39.166, 39.168,
      39.17, 39.172, 39.174, 39.176, 39.178, 39.18, 39.182, 39.184, 39.186,
      39.188, 39.19, 39.192, 39.194, 39.196, 39.198, 39.2, 39.202, 39.204,
      39.206, 39.208, 39.21, 39.212, 39.214, 39.216, 39.218, 39.22, 39.222,
      39.224000000000004, 39.226, 39.228, 39.23, 39.232, 39.234, 39.236, 39.238,
      39.24, 39.242, 39.244, 39.246, 39.248, 39.25, 39.252, 39.254, 39.256,
      39.258, 39.26, 39.262, 39.264, 39.266, 39.268, 39.269999999999996, 39.272,
      39.274, 39.275999999999996, 39.278, 39.28, 39.282, 39.284, 39.286, 39.288,
      39.29, 39.292, 39.294, 39.296, 39.298, 39.3, 39.302, 39.304, 39.306,
      39.308, 39.31, 39.312, 39.314, 39.316, 39.318, 39.32, 39.322, 39.324,
      39.326, 39.328, 39.33, 39.332, 39.334, 39.336, 39.338, 39.34, 39.342,
      39.344, 39.346000000000004, 39.348, 39.35, 39.352000000000004, 39.354,
      39.356, 39.358, 39.36, 39.362, 39.364, 39.366, 39.368, 39.37, 39.372,
      39.374, 39.376, 39.378, 39.38, 39.382, 39.384, 39.386, 39.388, 39.39,
      39.391999999999996, 39.394, 39.396, 39.397999999999996, 39.4, 39.402,
      39.403999999999996, 39.406, 39.408, 39.41, 39.412, 39.414, 39.416, 39.418,
      39.42, 39.422, 39.424, 39.426, 39.428, 39.43, 39.432, 39.434, 39.436,
      39.438, 39.44, 39.442, 39.444, 39.446, 39.448, 39.45, 39.452, 39.454,
      39.456, 39.458, 39.46, 39.462, 39.464, 39.466, 39.468, 39.47, 39.472,
      39.474000000000004, 39.476, 39.478, 39.48, 39.482, 39.484, 39.486, 39.488,
      39.49, 39.492, 39.494, 39.496, 39.498, 39.5, 39.502, 39.504, 39.506,
      39.508, 39.51, 39.512, 39.514, 39.516, 39.518, 39.519999999999996, 39.522,
      39.524, 39.525999999999996, 39.528, 39.53, 39.532, 39.534, 39.536, 39.538,
      39.54, 39.542, 39.544, 39.546, 39.548, 39.55, 39.552, 39.554, 39.556,
      39.558, 39.56, 39.562, 39.564, 39.566, 39.568, 39.57, 39.572, 39.574,
      39.576, 39.578, 39.58, 39.582, 39.584, 39.586, 39.588, 39.59, 39.592,
      39.594, 39.596000000000004, 39.598, 39.6, 39.602000000000004, 39.604,
      39.606, 39.608, 39.61, 39.612, 39.614, 39.616, 39.618, 39.62, 39.622,
      39.624, 39.626, 39.628, 39.63, 39.632, 39.634, 39.636, 39.638, 39.64,
      39.641999999999996, 39.644, 39.646, 39.647999999999996, 39.65, 39.652,
      39.653999999999996, 39.656, 39.658, 39.66, 39.662, 39.664, 39.666, 39.668,
      39.67, 39.672, 39.674, 39.676, 39.678, 39.68, 39.682, 39.684, 39.686,
      39.688, 39.69, 39.692, 39.694, 39.696, 39.698, 39.7, 39.702, 39.704,
      39.706, 39.708, 39.71, 39.712, 39.714, 39.716, 39.718, 39.72, 39.722,
      39.724000000000004, 39.726, 39.728, 39.73, 39.732, 39.734, 39.736, 39.738,
      39.74, 39.742, 39.744, 39.746, 39.748, 39.75, 39.752, 39.754, 39.756,
      39.758, 39.76, 39.762, 39.764, 39.766, 39.768, 39.769999999999996, 39.772,
      39.774, 39.775999999999996, 39.778, 39.78, 39.782, 39.784, 39.786, 39.788,
      39.79, 39.792, 39.794, 39.796, 39.798, 39.8, 39.802, 39.804, 39.806,
      39.808, 39.81, 39.812, 39.814, 39.816, 39.818, 39.82, 39.822, 39.824,
      39.826, 39.828, 39.83, 39.832, 39.834, 39.836, 39.838, 39.84, 39.842,
      39.844, 39.846000000000004, 39.848, 39.85, 39.852000000000004, 39.854,
      39.856, 39.858, 39.86, 39.862, 39.864, 39.866, 39.868, 39.87, 39.872,
      39.874, 39.876, 39.878, 39.88, 39.882, 39.884, 39.886, 39.888, 39.89,
      39.891999999999996, 39.894, 39.896, 39.897999999999996, 39.9, 39.902,
      39.903999999999996, 39.906, 39.908, 39.91, 39.912, 39.914, 39.916, 39.918,
      39.92, 39.922, 39.924, 39.926, 39.928, 39.93, 39.932, 39.934, 39.936,
      39.938, 39.94, 39.942, 39.944, 39.946, 39.948, 39.95, 39.952, 39.954,
      39.956, 39.958, 39.96, 39.962, 39.964, 39.966, 39.968, 39.97, 39.972,
      39.974000000000004, 39.976, 39.978, 39.98, 39.982, 39.984, 39.986, 39.988,
      39.99, 39.992, 39.994, 39.996, 39.998, 40.0, 40.002, 40.004, 40.006,
      40.008, 40.01, 40.012, 40.014, 40.016, 40.018, 40.019999999999996, 40.022,
      40.024, 40.025999999999996, 40.028, 40.03, 40.032, 40.034, 40.036, 40.038,
      40.04, 40.042, 40.044, 40.046, 40.048, 40.05, 40.052, 40.054, 40.056,
      40.058, 40.06, 40.062, 40.064, 40.066, 40.068, 40.07, 40.072, 40.074,
      40.076, 40.078, 40.08, 40.082, 40.084, 40.086, 40.088, 40.09, 40.092,
      40.094, 40.096000000000004, 40.098, 40.1, 40.102000000000004, 40.104,
      40.106, 40.108, 40.11, 40.112, 40.114, 40.116, 40.118, 40.12, 40.122,
      40.124, 40.126, 40.128, 40.13, 40.132, 40.134, 40.136, 40.138, 40.14,
      40.141999999999996, 40.144, 40.146, 40.147999999999996, 40.15, 40.152,
      40.153999999999996, 40.156, 40.158, 40.16, 40.162, 40.164, 40.166, 40.168,
      40.17, 40.172, 40.174, 40.176, 40.178, 40.18, 40.182, 40.184, 40.186,
      40.188, 40.19, 40.192, 40.194, 40.196, 40.198, 40.2, 40.202, 40.204,
      40.206, 40.208, 40.21, 40.212, 40.214, 40.216, 40.218, 40.22, 40.222,
      40.224000000000004, 40.226, 40.228, 40.23, 40.232, 40.234, 40.236, 40.238,
      40.24, 40.242, 40.244, 40.246, 40.248, 40.25, 40.252, 40.254, 40.256,
      40.258, 40.26, 40.262, 40.264, 40.266, 40.268, 40.269999999999996, 40.272,
      40.274, 40.275999999999996, 40.278, 40.28, 40.282, 40.284, 40.286, 40.288,
      40.29, 40.292, 40.294, 40.296, 40.298, 40.3, 40.302, 40.304, 40.306,
      40.308, 40.31, 40.312, 40.314, 40.316, 40.318, 40.32, 40.322, 40.324,
      40.326, 40.328, 40.33, 40.332, 40.334, 40.336, 40.338, 40.34, 40.342,
      40.344, 40.346000000000004, 40.348, 40.35, 40.352000000000004, 40.354,
      40.356, 40.358, 40.36, 40.362, 40.364, 40.366, 40.368, 40.37, 40.372,
      40.374, 40.376, 40.378, 40.38, 40.382, 40.384, 40.386, 40.388, 40.39,
      40.391999999999996, 40.394, 40.396, 40.397999999999996, 40.4, 40.402,
      40.403999999999996, 40.406, 40.408, 40.41, 40.412, 40.414, 40.416, 40.418,
      40.42, 40.422, 40.424, 40.426, 40.428, 40.43, 40.432, 40.434, 40.436,
      40.438, 40.44, 40.442, 40.444, 40.446, 40.448, 40.45, 40.452, 40.454,
      40.456, 40.458, 40.46, 40.462, 40.464, 40.466, 40.468, 40.47, 40.472,
      40.474000000000004, 40.476, 40.478, 40.48, 40.482, 40.484, 40.486, 40.488,
      40.49, 40.492, 40.494, 40.496, 40.498, 40.5, 40.502, 40.504, 40.506,
      40.508, 40.51, 40.512, 40.514, 40.516, 40.518, 40.519999999999996, 40.522,
      40.524, 40.525999999999996, 40.528, 40.53, 40.532, 40.534, 40.536, 40.538,
      40.54, 40.542, 40.544, 40.546, 40.548, 40.55, 40.552, 40.554, 40.556,
      40.558, 40.56, 40.562, 40.564, 40.566, 40.568, 40.57, 40.572, 40.574,
      40.576, 40.578, 40.58, 40.582, 40.584, 40.586, 40.588, 40.59, 40.592,
      40.594, 40.596000000000004, 40.598, 40.6, 40.602000000000004, 40.604,
      40.606, 40.608, 40.61, 40.612, 40.614, 40.616, 40.618, 40.62, 40.622,
      40.624, 40.626, 40.628, 40.63, 40.632, 40.634, 40.636, 40.638, 40.64,
      40.642, 40.644, 40.646, 40.647999999999996, 40.65, 40.652,
      40.653999999999996, 40.656, 40.658, 40.66, 40.662, 40.664, 40.666, 40.668,
      40.67, 40.672, 40.674, 40.676, 40.678, 40.68, 40.682, 40.684, 40.686,
      40.688, 40.69, 40.692, 40.694, 40.696, 40.698, 40.7, 40.702, 40.704,
      40.706, 40.708, 40.71, 40.712, 40.714, 40.716, 40.718, 40.72, 40.722,
      40.724000000000004, 40.726, 40.728, 40.73, 40.732, 40.734, 40.736, 40.738,
      40.74, 40.742, 40.744, 40.746, 40.748, 40.75, 40.752, 40.754, 40.756,
      40.758, 40.76, 40.762, 40.764, 40.766, 40.768, 40.769999999999996, 40.772,
      40.774, 40.775999999999996, 40.778, 40.78, 40.782, 40.784, 40.786, 40.788,
      40.79, 40.792, 40.794, 40.796, 40.798, 40.8, 40.802, 40.804, 40.806,
      40.808, 40.81, 40.812, 40.814, 40.816, 40.818, 40.82, 40.822, 40.824,
      40.826, 40.828, 40.83, 40.832, 40.834, 40.836, 40.838, 40.84, 40.842,
      40.844, 40.846000000000004, 40.848, 40.85, 40.852000000000004, 40.854,
      40.856, 40.858, 40.86, 40.862, 40.864, 40.866, 40.868, 40.87, 40.872,
      40.874, 40.876, 40.878, 40.88, 40.882, 40.884, 40.886, 40.888, 40.89,
      40.892, 40.894, 40.896, 40.897999999999996, 40.9, 40.902,
      40.903999999999996, 40.906, 40.908, 40.91, 40.912, 40.914, 40.916, 40.918,
      40.92, 40.922, 40.924, 40.926, 40.928, 40.93, 40.932, 40.934, 40.936,
      40.938, 40.94, 40.942, 40.944, 40.946, 40.948, 40.95, 40.952, 40.954,
      40.956, 40.958, 40.96, 40.962, 40.964, 40.966, 40.968, 40.97, 40.972,
      40.974000000000004, 40.976, 40.978, 40.98, 40.982, 40.984, 40.986, 40.988,
      40.99, 40.992, 40.994, 40.996, 40.998, 41.0, 41.002, 41.004, 41.006,
      41.008, 41.01, 41.012, 41.014, 41.016, 41.018, 41.02, 41.022, 41.024,
      41.025999999999996, 41.028, 41.03, 41.032, 41.034, 41.036, 41.038, 41.04,
      41.042, 41.044, 41.046, 41.048, 41.05, 41.052, 41.054, 41.056, 41.058,
      41.06, 41.062, 41.064, 41.066, 41.068, 41.07, 41.072, 41.074, 41.076,
      41.078, 41.08, 41.082, 41.084, 41.086, 41.088, 41.09, 41.092, 41.094,
      41.096000000000004, 41.098, 41.1, 41.102, 41.104, 41.106, 41.108, 41.11,
      41.112, 41.114, 41.116, 41.118, 41.12, 41.122, 41.124, 41.126, 41.128,
      41.13, 41.132, 41.134, 41.136, 41.138, 41.14, 41.142, 41.144, 41.146,
      41.148, 41.15, 41.152, 41.153999999999996, 41.156, 41.158, 41.16, 41.162,
      41.164, 41.166, 41.168, 41.17, 41.172, 41.174, 41.176, 41.178, 41.18,
      41.182, 41.184, 41.186, 41.188, 41.19, 41.192, 41.194, 41.196, 41.198,
      41.2, 41.202, 41.204, 41.206, 41.208, 41.21, 41.212, 41.214, 41.216,
      41.218, 41.22, 41.222, 41.224, 41.226, 41.228, 41.23, 41.232, 41.234,
      41.236, 41.238, 41.24, 41.242, 41.244, 41.246, 41.248, 41.25, 41.252,
      41.254, 41.256, 41.258, 41.26, 41.262, 41.264, 41.266, 41.268, 41.27,
      41.272, 41.274, 41.275999999999996, 41.278, 41.28, 41.282, 41.284, 41.286,
      41.288, 41.29, 41.292, 41.294, 41.296, 41.298, 41.3, 41.302, 41.304,
      41.306, 41.308, 41.31, 41.312, 41.314, 41.316, 41.318, 41.32, 41.322,
      41.324, 41.326, 41.328, 41.33, 41.332, 41.334, 41.336, 41.338, 41.34,
      41.342, 41.344, 41.346000000000004, 41.348, 41.35, 41.352, 41.354, 41.356,
      41.358, 41.36, 41.362, 41.364, 41.366, 41.368, 41.37, 41.372, 41.374,
      41.376, 41.378, 41.38, 41.382, 41.384, 41.386, 41.388, 41.39, 41.392,
      41.394, 41.396, 41.398, 41.4, 41.402, 41.403999999999996, 41.406, 41.408,
      41.41, 41.412, 41.414, 41.416, 41.418, 41.42, 41.422, 41.424, 41.426,
      41.428, 41.43, 41.432, 41.434, 41.436, 41.438, 41.44, 41.442, 41.444,
      41.446, 41.448, 41.45, 41.452, 41.454, 41.456, 41.458, 41.46, 41.462,
      41.464, 41.466, 41.468, 41.47, 41.472, 41.474, 41.476, 41.478, 41.48,
      41.482, 41.484, 41.486, 41.488, 41.49, 41.492, 41.494, 41.496, 41.498,
      41.5, 41.502, 41.504, 41.506, 41.508, 41.51, 41.512, 41.514, 41.516,
      41.518, 41.52, 41.522, 41.524, 41.525999999999996, 41.528, 41.53, 41.532,
      41.534, 41.536, 41.538, 41.54, 41.542, 41.544, 41.546, 41.548, 41.55,
      41.552, 41.554, 41.556, 41.558, 41.56, 41.562, 41.564, 41.566, 41.568,
      41.57, 41.572, 41.574, 41.576, 41.578, 41.58, 41.582, 41.584, 41.586,
      41.588, 41.59, 41.592, 41.594, 41.596000000000004, 41.598, 41.6, 41.602,
      41.604, 41.606, 41.608, 41.61, 41.612, 41.614, 41.616, 41.618, 41.62,
      41.622, 41.624, 41.626, 41.628, 41.63, 41.632, 41.634, 41.636, 41.638,
      41.64, 41.642, 41.644, 41.646, 41.648, 41.65, 41.652, 41.653999999999996,
      41.656, 41.658, 41.66, 41.662, 41.664, 41.666, 41.668, 41.67, 41.672,
      41.674, 41.676, 41.678, 41.68, 41.682, 41.684, 41.686, 41.688, 41.69,
      41.692, 41.694, 41.696, 41.698, 41.7, 41.702, 41.704, 41.706, 41.708,
      41.71, 41.712, 41.714, 41.716, 41.718, 41.72, 41.722, 41.724, 41.726,
      41.728, 41.73, 41.732, 41.734, 41.736, 41.738, 41.74, 41.742, 41.744,
      41.746, 41.748, 41.75, 41.752, 41.754, 41.756, 41.758, 41.76, 41.762,
      41.764, 41.766, 41.768, 41.77, 41.772, 41.774, 41.775999999999996, 41.778,
      41.78, 41.782, 41.784, 41.786, 41.788, 41.79, 41.792, 41.794, 41.796,
      41.798, 41.8, 41.802, 41.804, 41.806, 41.808, 41.81, 41.812, 41.814,
      41.816, 41.818, 41.82, 41.822, 41.824, 41.826, 41.828, 41.83, 41.832,
      41.834, 41.836, 41.838, 41.84, 41.842, 41.844, 41.846000000000004, 41.848,
      41.85, 41.852, 41.854, 41.856, 41.858, 41.86, 41.862, 41.864, 41.866,
      41.868, 41.87, 41.872, 41.874, 41.876, 41.878, 41.88, 41.882, 41.884,
      41.886, 41.888, 41.89, 41.892, 41.894, 41.896, 41.898, 41.9, 41.902,
      41.903999999999996, 41.906, 41.908, 41.91, 41.912, 41.914, 41.916, 41.918,
      41.92, 41.922, 41.924, 41.926, 41.928, 41.93, 41.932, 41.934, 41.936,
      41.938, 41.94, 41.942, 41.944, 41.946, 41.948, 41.95, 41.952, 41.954,
      41.956, 41.958, 41.96, 41.962, 41.964, 41.966, 41.968, 41.97, 41.972,
      41.974, 41.976, 41.978, 41.98, 41.982, 41.984, 41.986, 41.988, 41.99,
      41.992, 41.994, 41.996, 41.998, 42.0, 42.002, 42.004, 42.006, 42.008,
      42.01, 42.012, 42.014, 42.016, 42.018, 42.02, 42.022, 42.024,
      42.025999999999996, 42.028, 42.03, 42.032, 42.034, 42.036, 42.038, 42.04,
      42.042, 42.044, 42.046, 42.048, 42.05, 42.052, 42.054, 42.056, 42.058,
      42.06, 42.062, 42.064, 42.066, 42.068, 42.07, 42.072, 42.074, 42.076,
      42.078, 42.08, 42.082, 42.084, 42.086, 42.088, 42.09, 42.092, 42.094,
      42.096000000000004, 42.098, 42.1, 42.102, 42.104, 42.106, 42.108, 42.11,
      42.112, 42.114, 42.116, 42.118, 42.12, 42.122, 42.124, 42.126, 42.128,
      42.13, 42.132, 42.134, 42.136, 42.138, 42.14, 42.142, 42.144, 42.146,
      42.148, 42.15, 42.152, 42.153999999999996, 42.156, 42.158, 42.16, 42.162,
      42.164, 42.166, 42.168, 42.17, 42.172, 42.174, 42.176, 42.178, 42.18,
      42.182, 42.184, 42.186, 42.188, 42.19, 42.192, 42.194, 42.196, 42.198,
      42.2, 42.202, 42.204, 42.206, 42.208, 42.21, 42.212, 42.214, 42.216,
      42.218, 42.22, 42.222, 42.224, 42.226, 42.228, 42.23, 42.232, 42.234,
      42.236, 42.238, 42.24, 42.242, 42.244, 42.246, 42.248, 42.25, 42.252,
      42.254, 42.256, 42.258, 42.26, 42.262, 42.264, 42.266, 42.268, 42.27,
      42.272, 42.274, 42.275999999999996, 42.278, 42.28, 42.282, 42.284, 42.286,
      42.288, 42.29, 42.292, 42.294, 42.296, 42.298, 42.3, 42.302, 42.304,
      42.306, 42.308, 42.31, 42.312, 42.314, 42.316, 42.318, 42.32, 42.322,
      42.324, 42.326, 42.328, 42.33, 42.332, 42.334, 42.336, 42.338, 42.34,
      42.342, 42.344, 42.346000000000004, 42.348, 42.35, 42.352, 42.354, 42.356,
      42.358, 42.36, 42.362, 42.364, 42.366, 42.368, 42.37, 42.372, 42.374,
      42.376, 42.378, 42.38, 42.382, 42.384, 42.386, 42.388, 42.39, 42.392,
      42.394, 42.396, 42.398, 42.4, 42.402, 42.403999999999996, 42.406, 42.408,
      42.41, 42.412, 42.414, 42.416, 42.418, 42.42, 42.422, 42.424, 42.426,
      42.428, 42.43, 42.432, 42.434, 42.436, 42.438, 42.44, 42.442, 42.444,
      42.446, 42.448, 42.45, 42.452, 42.454, 42.456, 42.458, 42.46, 42.462,
      42.464, 42.466, 42.468, 42.47, 42.472, 42.474, 42.476, 42.478, 42.48,
      42.482, 42.484, 42.486, 42.488, 42.49, 42.492, 42.494, 42.496, 42.498,
      42.5, 42.502, 42.504, 42.506, 42.508, 42.51, 42.512, 42.514, 42.516,
      42.518, 42.52, 42.522, 42.524, 42.525999999999996, 42.528, 42.53, 42.532,
      42.534, 42.536, 42.538, 42.54, 42.542, 42.544, 42.546, 42.548, 42.55,
      42.552, 42.554, 42.556, 42.558, 42.56, 42.562, 42.564, 42.566, 42.568,
      42.57, 42.572, 42.574, 42.576, 42.578, 42.58, 42.582, 42.584, 42.586,
      42.588, 42.59, 42.592, 42.594, 42.596000000000004, 42.598, 42.6, 42.602,
      42.604, 42.606, 42.608, 42.61, 42.612, 42.614, 42.616, 42.618, 42.62,
      42.622, 42.624, 42.626, 42.628, 42.63, 42.632, 42.634, 42.636, 42.638,
      42.64, 42.642, 42.644, 42.646, 42.648, 42.65, 42.652, 42.653999999999996,
      42.656, 42.658, 42.66, 42.662, 42.664, 42.666, 42.668, 42.67, 42.672,
      42.674, 42.676, 42.678, 42.68, 42.682, 42.684, 42.686, 42.688, 42.69,
      42.692, 42.694, 42.696, 42.698, 42.7, 42.702, 42.704, 42.706, 42.708,
      42.71, 42.712, 42.714, 42.716, 42.718, 42.72, 42.722, 42.724, 42.726,
      42.728, 42.73, 42.732, 42.734, 42.736, 42.738, 42.74, 42.742, 42.744,
      42.746, 42.748, 42.75, 42.752, 42.754, 42.756, 42.758, 42.76, 42.762,
      42.764, 42.766, 42.768, 42.77, 42.772, 42.774, 42.775999999999996, 42.778,
      42.78, 42.782, 42.784, 42.786, 42.788, 42.79, 42.792, 42.794, 42.796,
      42.798, 42.8, 42.802, 42.804, 42.806, 42.808, 42.81, 42.812, 42.814,
      42.816, 42.818, 42.82, 42.822, 42.824, 42.826, 42.828, 42.83, 42.832,
      42.834, 42.836, 42.838, 42.84, 42.842, 42.844, 42.846000000000004, 42.848,
      42.85, 42.852, 42.854, 42.856, 42.858, 42.86, 42.862, 42.864, 42.866,
      42.868, 42.87, 42.872, 42.874, 42.876, 42.878, 42.88, 42.882, 42.884,
      42.886, 42.888, 42.89, 42.892, 42.894, 42.896, 42.898, 42.9, 42.902,
      42.903999999999996, 42.906, 42.908, 42.91, 42.912, 42.914, 42.916, 42.918,
      42.92, 42.922, 42.924, 42.926, 42.928, 42.93, 42.932, 42.934, 42.936,
      42.938, 42.94, 42.942, 42.944, 42.946, 42.948, 42.95, 42.952, 42.954,
      42.956, 42.958, 42.96, 42.962, 42.964, 42.966, 42.968, 42.97, 42.972,
      42.974, 42.976, 42.978, 42.98, 42.982, 42.984, 42.986, 42.988, 42.99,
      42.992, 42.994, 42.996, 42.998, 43.0, 43.002, 43.004, 43.006, 43.008,
      43.01, 43.012, 43.014, 43.016, 43.018, 43.02, 43.022, 43.024, 43.026,
      43.028, 43.03, 43.032, 43.034, 43.036, 43.038, 43.04, 43.042, 43.044,
      43.046, 43.048, 43.05, 43.052, 43.054, 43.056, 43.058, 43.06, 43.062,
      43.064, 43.066, 43.068, 43.07, 43.072, 43.074, 43.076, 43.078, 43.08,
      43.082, 43.084, 43.086, 43.088, 43.09, 43.092, 43.094, 43.096, 43.098,
      43.1, 43.102, 43.104, 43.106, 43.108, 43.11, 43.112, 43.114, 43.116,
      43.118, 43.12, 43.122, 43.124, 43.126, 43.128, 43.13, 43.132, 43.134,
      43.136, 43.138, 43.14, 43.142, 43.144, 43.146, 43.148, 43.15, 43.152,
      43.153999999999996, 43.156, 43.158, 43.16, 43.162, 43.164, 43.166, 43.168,
      43.17, 43.172, 43.174, 43.176, 43.178, 43.18, 43.182, 43.184, 43.186,
      43.188, 43.19, 43.192, 43.194, 43.196, 43.198, 43.2, 43.202, 43.204,
      43.206, 43.208, 43.21, 43.212, 43.214, 43.216, 43.218, 43.22, 43.222,
      43.224, 43.226, 43.228, 43.23, 43.232, 43.234, 43.236, 43.238, 43.24,
      43.242, 43.244, 43.246, 43.248, 43.25, 43.252, 43.254, 43.256, 43.258,
      43.26, 43.262, 43.264, 43.266, 43.268, 43.27, 43.272, 43.274, 43.276,
      43.278, 43.28, 43.282, 43.284, 43.286, 43.288, 43.29, 43.292, 43.294,
      43.296, 43.298, 43.3, 43.302, 43.304, 43.306, 43.308, 43.31, 43.312,
      43.314, 43.316, 43.318, 43.32, 43.322, 43.324, 43.326, 43.328, 43.33,
      43.332, 43.334, 43.336, 43.338, 43.34, 43.342, 43.344, 43.346, 43.348,
      43.35, 43.352, 43.354, 43.356, 43.358, 43.36, 43.362, 43.364, 43.366,
      43.368, 43.37, 43.372, 43.374, 43.376, 43.378, 43.38, 43.382, 43.384,
      43.386, 43.388, 43.39, 43.392, 43.394, 43.396, 43.398, 43.4, 43.402,
      43.403999999999996, 43.406, 43.408, 43.41, 43.412, 43.414, 43.416, 43.418,
      43.42, 43.422, 43.424, 43.426, 43.428, 43.43, 43.432, 43.434, 43.436,
      43.438, 43.44, 43.442, 43.444, 43.446, 43.448, 43.45, 43.452, 43.454,
      43.456, 43.458, 43.46, 43.462, 43.464, 43.466, 43.468, 43.47, 43.472,
      43.474, 43.476, 43.478, 43.48, 43.482, 43.484, 43.486, 43.488, 43.49,
      43.492, 43.494, 43.496, 43.498, 43.5, 43.502, 43.504, 43.506, 43.508,
      43.51, 43.512, 43.514, 43.516, 43.518, 43.52, 43.522, 43.524, 43.526,
      43.528, 43.53, 43.532, 43.534, 43.536, 43.538, 43.54, 43.542, 43.544,
      43.546, 43.548, 43.55, 43.552, 43.554, 43.556, 43.558, 43.56, 43.562,
      43.564, 43.566, 43.568, 43.57, 43.572, 43.574, 43.576, 43.578, 43.58,
      43.582, 43.584, 43.586, 43.588, 43.59, 43.592, 43.594, 43.596, 43.598,
      43.6, 43.602, 43.604, 43.606, 43.608, 43.61, 43.612, 43.614, 43.616,
      43.618, 43.62, 43.622, 43.624, 43.626, 43.628, 43.63, 43.632, 43.634,
      43.636, 43.638, 43.64, 43.642, 43.644, 43.646, 43.648, 43.65, 43.652,
      43.653999999999996, 43.656, 43.658, 43.66, 43.662, 43.664, 43.666, 43.668,
      43.67, 43.672, 43.674, 43.676, 43.678, 43.68, 43.682, 43.684, 43.686,
      43.688, 43.69, 43.692, 43.694, 43.696, 43.698, 43.7, 43.702, 43.704,
      43.706, 43.708, 43.71, 43.712, 43.714, 43.716, 43.718, 43.72, 43.722,
      43.724, 43.726, 43.728, 43.73, 43.732, 43.734, 43.736, 43.738, 43.74,
      43.742, 43.744, 43.746, 43.748, 43.75, 43.752, 43.754, 43.756, 43.758,
      43.76, 43.762, 43.764, 43.766, 43.768, 43.77, 43.772, 43.774, 43.776,
      43.778, 43.78, 43.782, 43.784, 43.786, 43.788, 43.79, 43.792, 43.794,
      43.796, 43.798, 43.8, 43.802, 43.804, 43.806, 43.808, 43.81, 43.812,
      43.814, 43.816, 43.818, 43.82, 43.822, 43.824, 43.826, 43.828, 43.83,
      43.832, 43.834, 43.836, 43.838, 43.84, 43.842, 43.844, 43.846000000000004,
      43.848, 43.85, 43.852, 43.854, 43.856, 43.858, 43.86, 43.862, 43.864,
      43.866, 43.868, 43.87, 43.872, 43.874, 43.876, 43.878, 43.88, 43.882,
      43.884, 43.886, 43.888, 43.89, 43.892, 43.894, 43.896, 43.898, 43.9,
      43.902, 43.903999999999996, 43.906, 43.908, 43.91, 43.912, 43.914, 43.916,
      43.918, 43.92, 43.922, 43.924, 43.926, 43.928, 43.93, 43.932, 43.934,
      43.936, 43.938, 43.94, 43.942, 43.944, 43.946, 43.948, 43.95, 43.952,
      43.954, 43.956, 43.958, 43.96, 43.962, 43.964, 43.966, 43.968, 43.97,
      43.972, 43.974, 43.976, 43.978, 43.98, 43.982, 43.984, 43.986, 43.988,
      43.99, 43.992, 43.994, 43.996, 43.998, 44.0, 44.002, 44.004, 44.006,
      44.008, 44.01, 44.012, 44.014, 44.016, 44.018, 44.02, 44.022, 44.024,
      44.026, 44.028, 44.03, 44.032, 44.034, 44.036, 44.038, 44.04, 44.042,
      44.044, 44.046, 44.048, 44.05, 44.052, 44.054, 44.056, 44.058, 44.06,
      44.062, 44.064, 44.066, 44.068, 44.07, 44.072, 44.074, 44.076, 44.078,
      44.08, 44.082, 44.084, 44.086, 44.088, 44.09, 44.092, 44.094, 44.096,
      44.098, 44.1, 44.102, 44.104, 44.106, 44.108, 44.11, 44.112, 44.114,
      44.116, 44.118, 44.12, 44.122, 44.124, 44.126, 44.128, 44.13, 44.132,
      44.134, 44.136, 44.138, 44.14, 44.142, 44.144, 44.146, 44.148, 44.15,
      44.152, 44.154, 44.156, 44.158, 44.16, 44.162, 44.164, 44.166, 44.168,
      44.17, 44.172, 44.174, 44.176, 44.178, 44.18, 44.182, 44.184, 44.186,
      44.188, 44.19, 44.192, 44.194, 44.196, 44.198, 44.2, 44.202, 44.204,
      44.206, 44.208, 44.21, 44.212, 44.214, 44.216, 44.218, 44.22, 44.222,
      44.224, 44.226, 44.228, 44.23, 44.232, 44.234, 44.236, 44.238, 44.24,
      44.242, 44.244, 44.246, 44.248, 44.25, 44.252, 44.254, 44.256, 44.258,
      44.26, 44.262, 44.264, 44.266, 44.268, 44.27, 44.272, 44.274, 44.276,
      44.278, 44.28, 44.282, 44.284, 44.286, 44.288, 44.29, 44.292, 44.294,
      44.296, 44.298, 44.3, 44.302, 44.304, 44.306, 44.308, 44.31, 44.312,
      44.314, 44.316, 44.318, 44.32, 44.322, 44.324, 44.326, 44.328, 44.33,
      44.332, 44.334, 44.336, 44.338, 44.34, 44.342, 44.344, 44.346, 44.348,
      44.35, 44.352, 44.354, 44.356, 44.358, 44.36, 44.362, 44.364, 44.366,
      44.368, 44.37, 44.372, 44.374, 44.376, 44.378, 44.38, 44.382, 44.384,
      44.386, 44.388, 44.39, 44.392, 44.394, 44.396, 44.398, 44.4, 44.402,
      44.404, 44.406, 44.408, 44.41, 44.412, 44.414, 44.416, 44.418, 44.42,
      44.422, 44.424, 44.426, 44.428, 44.43, 44.432, 44.434, 44.436, 44.438,
      44.44, 44.442, 44.444, 44.446, 44.448, 44.45, 44.452, 44.454, 44.456,
      44.458, 44.46, 44.462, 44.464, 44.466, 44.468, 44.47, 44.472, 44.474,
      44.476, 44.478, 44.48, 44.482, 44.484, 44.486, 44.488, 44.49, 44.492,
      44.494, 44.496, 44.498, 44.5, 44.502, 44.504, 44.506, 44.508, 44.51,
      44.512, 44.514, 44.516, 44.518, 44.52, 44.522, 44.524, 44.526, 44.528,
      44.53, 44.532, 44.534, 44.536, 44.538, 44.54, 44.542, 44.544, 44.546,
      44.548, 44.55, 44.552, 44.554, 44.556, 44.558, 44.56, 44.562, 44.564,
      44.566, 44.568, 44.57, 44.572, 44.574, 44.576, 44.578, 44.58, 44.582,
      44.584, 44.586, 44.588, 44.59, 44.592, 44.594, 44.596, 44.598, 44.6,
      44.602, 44.604, 44.606, 44.608, 44.61, 44.612, 44.614, 44.616, 44.618,
      44.62, 44.622, 44.624, 44.626, 44.628, 44.63, 44.632, 44.634, 44.636,
      44.638, 44.64, 44.642, 44.644, 44.646, 44.648, 44.65, 44.652, 44.654,
      44.656, 44.658, 44.66, 44.662, 44.664, 44.666, 44.668, 44.67, 44.672,
      44.674, 44.676, 44.678, 44.68, 44.682, 44.684, 44.686, 44.688, 44.69,
      44.692, 44.694, 44.696, 44.698, 44.7, 44.702, 44.704, 44.706, 44.708,
      44.71, 44.712, 44.714, 44.716, 44.718, 44.72, 44.722, 44.724, 44.726,
      44.728, 44.73, 44.732, 44.734, 44.736, 44.738, 44.74, 44.742, 44.744,
      44.746, 44.748, 44.75, 44.752, 44.754, 44.756, 44.758, 44.76, 44.762,
      44.764, 44.766, 44.768, 44.77, 44.772, 44.774, 44.776, 44.778, 44.78,
      44.782, 44.784, 44.786, 44.788, 44.79, 44.792, 44.794, 44.796, 44.798,
      44.8, 44.802, 44.804, 44.806, 44.808, 44.81, 44.812, 44.814, 44.816,
      44.818, 44.82, 44.822, 44.824, 44.826, 44.828, 44.83, 44.832, 44.834,
      44.836, 44.838, 44.84, 44.842, 44.844, 44.846, 44.848, 44.85, 44.852,
      44.854, 44.856, 44.858, 44.86, 44.862, 44.864, 44.866, 44.868, 44.87,
      44.872, 44.874, 44.876, 44.878, 44.88, 44.882, 44.884, 44.886, 44.888,
      44.89, 44.892, 44.894, 44.896, 44.898, 44.9, 44.902, 44.904, 44.906,
      44.908, 44.91, 44.912, 44.914, 44.916, 44.918, 44.92, 44.922, 44.924,
      44.926, 44.928, 44.93, 44.932, 44.934, 44.936, 44.938, 44.94, 44.942,
      44.944, 44.946, 44.948, 44.95, 44.952, 44.954, 44.956, 44.958, 44.96,
      44.962, 44.964, 44.966, 44.968, 44.97, 44.972, 44.974, 44.976, 44.978,
      44.98, 44.982, 44.984, 44.986, 44.988, 44.99, 44.992, 44.994, 44.996,
      44.998, 45.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3,
      -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, -0.3, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.00075398045090086484, 0.0015079501860705826, 0.00226189848993164,
      0.0030158146472070921, 0.003769687943080885, 0.0045235076633461224,
      0.0052772630945533174, 0.0060309435241706873, 0.006784538240732392,
      0.0075380365339867477, 0.00829142769505647, 0.0090447010165868643,
      0.0097978457928939843, 0.010550851320124802, 0.011303706896405334,
      0.012056401821988715, 0.012808925399415295, 0.013561266933660663,
      0.014313415732283633, 0.015065361105586223, 0.015817092366761584,
      0.016568598832041859, 0.01731986982085805, 0.0180708946559878,
      0.018821662663701798, 0.019572163173930162, 0.020322385520396738,
      0.021072319040778695, 0.02182195307686606, 0.022571276974697189,
      0.02332028008471821, 0.02406895176194232, 0.024817281366083813,
      0.025565258261723914, 0.02631287181845661, 0.027060111411035755,
      0.027806966419534049, 0.028553426229489982, 0.029299480232054698,
      0.030045117824150775, 0.030790328408618863, 0.031535101394364391,
      0.032279426196515991, 0.033023292236571973, 0.033766688942546724,
      0.034509605749128855, 0.035252032097827415, 0.035993957437117995,
      0.036735371222600573, 0.037476262917145453, 0.038216621991039063,
      0.038956437922141485, 0.039695700196032059, 0.040434398306154896,
      0.041172521753976059, 0.041910060049128804, 0.042647002709557492,
      0.043383339261680934, 0.044119059240524214, 0.0448541521898753,
      0.045588607662441473, 0.046322415219982149, 0.047055564433465022,
      0.047788044883222164, 0.048519846159081122, 0.049250957860527224,
      0.049981369596846174, 0.050711070987267827, 0.051440051661121526,
      0.052168301257979589, 0.052895809427800679, 0.05362256583108465,
      0.0543485601390156, 0.055073782033604871, 0.055798221207845333,
      0.056521867365854073, 0.057244710223014784, 0.057966739506131772,
      0.05868794495357197, 0.059408316315407043, 0.060127843353566628,
      0.060846515841980135, 0.061564323566718183, 0.062281256326145375,
      0.062997303931061566, 0.063712456204841492, 0.064426702983593417,
      0.065140034116287118, 0.065852439464905654, 0.066563908904597222,
      0.067274432323803687, 0.067983999624412, 0.068692600721905223,
      0.0694002255454895, 0.070106864038250991, 0.070812506157293856,
      0.071517141873879114, 0.072220761173574774, 0.072923354056394371,
      0.073624910536935345, 0.074325420644528462, 0.075024874423375756,
      0.075723261932688288, 0.076420573246834919, 0.0771167984554796,
      0.077811927663718569, 0.0785059509922283, 0.079198858577402345,
      0.079890640571487689, 0.080581287142732147, 0.081270788475520425,
      0.081959134770509923, 0.082646316244777362, 0.0833323231319541,
      0.0840171456823614, 0.084700774163156148, 0.085383198858465653,
      0.086064410069520772, 0.08674439811480722, 0.087423153330187242,
      0.088100666069044459, 0.088776926702427927, 0.089451925619174755,
      0.090125653226053842, 0.090798099947909355, 0.091469256227781348,
      0.092139112527054673, 0.09280765932558975, 0.093474887121854366,
      0.094140786433065851, 0.094805347795322181, 0.095468561763732987,
      0.09613041891256098, 0.096790909835352212, 0.09745002514506633,
      0.09810775547421699, 0.098764091475001481, 0.099419023819430088,
      0.10007254319946574, 0.10072464032715255, 0.10137530593474463,
      0.10202453077484459, 0.10267230562053156, 0.10331862126548885,
      0.10396346852414162, 0.10460683823178413, 0.10524872124470641,
      0.10588910844033124, 0.10652799071734015, 0.10716535899579843,
      0.10780120421729655, 0.10843551734506421, 0.10906828936410554,
      0.10969951128133403, 0.11032917412568677, 0.11095726894825873,
      0.11158378682243666, 0.11220871884401143, 0.11283205613131686,
      0.1134537898253514, 0.11407391108990082, 0.1146924111116705,
      0.11530928110040711, 0.11592451228902048, 0.1165380959337147,
      0.11715002331410909, 0.11776028573335891, 0.11836887451828544,
      0.11897578101949605, 0.11958099661150375, 0.12018451269285642,
      0.12078632068625575, 0.12138641203867589, 0.12198477822149152,
      0.12258141073059572, 0.12317630108651777, 0.12376944083454999,
      0.12436082154486472, 0.12495043481263089, 0.12553827225813993,
      0.1261243255269216, 0.12670858628985857, 0.12729104624331633,
      0.12787169710924756, 0.12845053063531614, 0.1290275385950205,
      0.12960271278779831, 0.13017604503914906, 0.13074752720075647,
      0.131317151150591, 0.13188490879303646, 0.13245079205900109,
      0.133014792906029, 0.13357690331842073, 0.13413711530734415,
      0.13469542091094486, 0.13525181219446539, 0.13580628125035502,
      0.13635882019837917, 0.13690942118573732, 0.1374580763871717,
      0.13800477800507546, 0.13854951826960946, 0.13909228943880972,
      0.13963308379869457, 0.14017189366338009, 0.14070871137518634,
      0.14124352930474357, 0.14177633985110602, 0.14230713544185752,
      0.1428359085332149, 0.14336265161014583, 0.14388735718646339,
      0.14441001780493809, 0.14493062603740925, 0.14544917448487973,
      0.14596565577762644, 0.14648006257531063, 0.14699238756707028,
      0.1475026234716342, 0.14801076303742167, 0.14851679904264287,
      0.14902072429540691, 0.14952253163382148, 0.15002221392609175,
      0.15051976407062714, 0.15101517499613967, 0.15150843966174177,
      0.15199955105705149, 0.15248850220228979, 0.15297528614837683,
      0.15345989597703608, 0.15394232480089004, 0.15442256576355562,
      0.1549006120397465, 0.15537645683536783, 0.15585009338761008,
      0.15632151496505028, 0.15679071486774518, 0.15725768642732388,
      0.15772242300708775, 0.1581849180021021, 0.15864516483928681,
      0.15910315697751889, 0.15955888790771466, 0.1600123511529272,
      0.16046354026844326, 0.16091244884186523, 0.161359070493207,
      0.16180339887498951, 0.16224542767232053, 0.16268515060299316,
      0.16312256141757212, 0.1635576538994799, 0.16399042186509005,
      0.16442085916381258, 0.16484895967817917, 0.16527471732393473,
      0.16569812605012138, 0.16611917983916247, 0.16653787270695231,
      0.16695419870293929, 0.16736815191020796, 0.16777972644556771,
      0.16818891645963407, 0.16859571613690974, 0.16900011969587161,
      0.16940212138905067, 0.1698017155031116, 0.1701988963589382,
      0.17059365831171214, 0.17098599575099074, 0.17137590310079137,
      0.17176337481966814, 0.17214840540078818, 0.17253098937201747,
      0.17291112129598951, 0.17328879577018694, 0.17366400742702212,
      0.17403675093390558, 0.17440702099332567, 0.17477481234292788,
      0.17514011975558108, 0.175502938039459, 0.17586326203811131,
      0.17622108663053515, 0.17657640673125172, 0.17692921729037642,
      0.17727951329368904, 0.17762728976270861, 0.17797254175476235,
      0.17831526436305398, 0.17865545271673719, 0.17899310198098314,
      0.17932820735704713, 0.17966076408234069, 0.17999076743049716,
      0.18031821271143733, 0.1806430952714396, 0.18096541049320414,
      0.18128515379591714, 0.18160232063531903, 0.18191690650376757,
      0.18222890693030008, 0.18253831748070048, 0.18284513375756051,
      0.18314935140034005, 0.18345096608543524, 0.18374997352623268,
      0.18404636947317371, 0.18434014971381796, 0.18463131007289688,
      0.18491984641237624, 0.18520575463151803, 0.18548903066693212,
      0.18576967049263948, 0.18604767012012749, 0.18632302559840508,
      0.18659573301406196, 0.18686578849132252, 0.1871331881920997,
      0.1873979283160524, 0.18766000510063788, 0.187919414821164,
      0.18817615379084493, 0.188430218360852, 0.18868160492036445,
      0.18893030989662324, 0.18917632975498058, 0.18941966099894889,
      0.18966030017025298, 0.189898243848878, 0.19013348865311672,
      0.1903660312396202, 0.19059586830344397, 0.19082299657809337,
      0.1910474128355745, 0.19126911388643475, 0.19148809657981072,
      0.19170435780347517, 0.19191789448387658, 0.19212870358618536,
      0.19233678211433902, 0.19254212711108, 0.19274473565800174,
      0.19294460487558859, 0.19314173192325593, 0.19333611399939241,
      0.19352774834139877, 0.19371663222572616, 0.19390276296791686,
      0.19408613792264129, 0.19426675448373484, 0.19444461008423669,
      0.19461970219642541, 0.19479202833185383, 0.19496158604138647,
      0.1951283729152333, 0.19529238658298298, 0.19545362471363861,
      0.19561208501564972, 0.19576776523694406, 0.19592066316496143,
      0.19607077662668404, 0.19621810348866686, 0.19636264165706929,
      0.19650438907768425, 0.19664334373596645, 0.19677950365706354,
      0.1969128669058412, 0.197043431586912, 0.19717119584466375,
      0.19729615786328303, 0.19741831586678255, 0.19753766811902757,
      0.19765421292375771, 0.19776794862461355, 0.19787887360515927,
      0.1979869862889049, 0.19809228513933014, 0.19819476865990543,
      0.19829443539411271, 0.19839128392546723, 0.19848531287753721,
      0.19857652091396272, 0.19866490673847589, 0.19875046909491864,
      0.19883320676726016, 0.19891311857961519, 0.19899020339626008,
      0.19906446012164872, 0.19913588770042878, 0.19920448511745645,
      0.19927025139781027, 0.19933318560680596, 0.19939328685000923,
      0.19945055427324818, 0.19950498706262604, 0.1995565844445325,
      0.19960534568565425, 0.1996512700929865, 0.19969435701384161,
      0.19973460583585886, 0.19977201598701372, 0.199806586935625,
      0.19983831819036285, 0.19986720930025617, 0.19989325985469816,
      0.19991646948345282, 0.19993683785666, 0.19995436468483996,
      0.19996904971889773, 0.19998089275012643, 0.19998989361021036,
      0.19999605217122743, 0.19999936834565082, 0.19999984208635035,
      0.19999747338659316, 0.19999226228004366, 0.19998420884076323,
      0.1999733131832091, 0.19995957546223259, 0.19994299587307723,
      0.19992357465137564, 0.19990131207314632, 0.19987620845478984,
      0.19984826415308421, 0.19981747956517973, 0.19978385512859362,
      0.19974739132120353, 0.19970808866124079, 0.19966594770728338,
      0.19962096905824731, 0.1995731533533788, 0.19952250127224513,
      0.19946901353472404, 0.19941269090099495, 0.19935353417152729,
      0.19929154418706874, 0.19922672182863455, 0.19915906801749372,
      0.19908858371515664, 0.19901526992336144, 0.19893912768405927,
      0.19886015807939977, 0.19877836223171608, 0.19869374130350814,
      0.19860629649742648, 0.19851602905625565, 0.19842294026289564,
      0.19832703144034414, 0.19822830395167806, 0.19812675920003345,
      0.19802239862858581, 0.19791522372053019, 0.19780523599905914,
      0.19769243702734141, 0.19757682840850044, 0.19745841178559043,
      0.19733718884157353, 0.1972131612992967, 0.197086330921465,
      0.19695669951061923, 0.1968242689091092, 0.19668904099906595,
      0.19655101770237787, 0.19641020098066203, 0.19626659283523473,
      0.19612019530708635, 0.19597101047684956, 0.19581904046477075,
      0.19566428743068076, 0.19550675357396241, 0.19534644113352029,
      0.19518335238774953, 0.19501748965450202, 0.19484885529105392,
      0.19467745169407349, 0.19450328129958494, 0.19432634658293471,
      0.1941466500587575, 0.19396419428093831, 0.1937789818425773,
      0.19359101537595383, 0.19340029755248711, 0.19320683108269929,
      0.19301061871617778, 0.19281166324153429, 0.19260996748636611,
      0.19240553431721716, 0.19219836663953488, 0.19198846739763017,
      0.19177583957463704, 0.19156048619246593, 0.19134241031176591,
      0.19112161503187866, 0.19089810349079234, 0.19067187886510145,
      0.19044294436995945, 0.19021130325903074, 0.18997695882444934,
      0.18973991439676807, 0.18950017334491254, 0.18925773907613452,
      0.18901261503596123, 0.18876480470814741, 0.18851431161462726,
      0.18826113931546162, 0.18800529140878885, 0.1877467715307749,
      0.187485583355559, 0.18722173059520286, 0.18695521699963913,
      0.18668604635661548, 0.18641422249164208, 0.18613974926793864,
      0.18586263058637684, 0.18558287038542598, 0.18530047264109875,
      0.18501544136689174, 0.18472778061372974, 0.18443749446990981,
      0.18414458706104009, 0.18384906254998271, 0.18355092513679669,
      0.18325017905867244, 0.18294682858987854, 0.18264087804169768,
      0.18233233176236219, 0.1820211941369988, 0.18170746958756295,
      0.18139116257277271, 0.18107227758805255, 0.18075081916546346,
      0.18042679187364052, 0.18010020031773002, 0.17977104913932021,
      0.17943934301637743, 0.17910508666318103, 0.17876828483025306,
      0.17842894230429254, 0.17808706390810902, 0.1777426545005508,
      0.17739571897643713, 0.17704626226649109, 0.17669428933726539,
      0.17633980519107384, 0.17598281486592207, 0.17562332343543219,
      0.17526133600877247, 0.17489685773058683, 0.17452989378091774,
      0.17416044937513445, 0.17378852976386119, 0.17341414023289814,
      0.17303728610314861, 0.17265797273054595, 0.17227620550597006,
      0.17189198985517967, 0.17150533123873096, 0.17111623515189606,
      0.17072470712459289, 0.17033075272130291, 0.16993437754098725,
      0.16953558721701686, 0.16913438741708417, 0.16873078384312573,
      0.16832478223124314, 0.16791638835161718, 0.16750560800842826,
      0.16709244703977566, 0.16667691131759069, 0.16625900674755487,
      0.16583873926901876, 0.16541611485491267, 0.16499113951166433,
      0.16456381927911556, 0.16413416023043187, 0.16370216847201877,
      0.16326785014343678, 0.16283121141731005, 0.16239225849924052,
      0.16195099762772239, 0.16150743507404858, 0.16106157714222402,
      0.16061343016887841, 0.16016300052317145, 0.15971029460670461,
      0.15925531885343336, 0.15879807972956717, 0.15833858373348758,
      0.1578768373956515, 0.15741284727849317, 0.15694661997634171,
      0.15647816211531815, 0.15600748035324491, 0.15553458137955334,
      0.15505947191518366, 0.15458215871249231, 0.154102648555158,
      0.15362094825808081, 0.15313706466728716, 0.15265100465983578,
      0.15216277514371435, 0.15167238305774419, 0.15117983537148405,
      0.15068513908512582, 0.15018830122939805, 0.149689328865468,
      0.14918822908483673, 0.14868500900924028, 0.14817967579055175,
      0.14767223661067364, 0.14716269868143916, 0.14665106924451188,
      0.14613735557127777, 0.14562156496274428, 0.14510370474944032,
      0.14458378229130228, 0.14406180497758087, 0.14353778022673105,
      0.14301171548630068, 0.14248361823283609, 0.14195349597177007,
      0.14142135623730953, 0.14088720659234094, 0.14035105462831204,
      0.13981290796512816, 0.13927277425104639, 0.13873066116256158,
      0.13818657640429952, 0.13764052770891111, 0.13709252283695583,
      0.13654256957679514, 0.135990675744484, 0.1354368491836544,
      0.13488109776540683, 0.13432342938820088, 0.13376385197773777,
      0.13320237348685002, 0.13263900189539188, 0.13207374521011966,
      0.13150661146458112, 0.13093760871900403, 0.130366745060176,
      0.12979402860133221, 0.12921946748204313, 0.12864306986809326,
      0.12806484395136736, 0.1274847979497388, 0.126902940106941,
      0.12631927869246398, 0.12573382200143043, 0.12514657835447165,
      0.1245575560976219, 0.12396676360219319, 0.12337420926465059,
      0.12277990150650585, 0.12218384877418682, 0.12158605953892099,
      0.12098654229661886, 0.12038530556774625, 0.11978235789720704,
      0.11917770785422428, 0.11857136403221238, 0.11796333504865822,
      0.11735362954500156, 0.11674225618650627, 0.11612922366213979,
      0.1155145406844536, 0.11489821598945214, 0.11428025833647266,
      0.11366067650806329, 0.11303947930985231, 0.11241667557042573,
      0.11179227414120543, 0.11116628389631687, 0.11053871373246578,
      0.10990957256881573, 0.10927886934685399, 0.10864661303026842,
      0.10801281260482409, 0.10737747707822339, 0.10674061547999286,
      0.10610223686134763, 0.10546235029505656, 0.10482096487532624,
      0.10417808971766565, 0.10353373395874904, 0.10288790675630165,
      0.10224061728895624, 0.10159187475612792, 0.10094168837788633,
      0.10029006739481786, 0.099637021067898027, 0.098982558678362836,
      0.098326689527570482, 0.097669422936872044, 0.097010768247483142,
      0.096350734820343509, 0.095689332035988131, 0.095026569294416857,
      0.094362456014954021, 0.0936970016361183, 0.093030215615491629,
      0.092362107429578275, 0.091692686573673077, 0.09102196256173066,
      0.090349944926222586, 0.0896766432180059, 0.0890020670061905,
      0.088326225877996462, 0.087649129438620937, 0.086970787311106593,
      0.08629120913619194, 0.085610404572189339, 0.084928383294841162,
      0.084245154997174457, 0.083560729389379432, 0.082875116198657589,
      0.082188325169088916, 0.081500366061496521, 0.080811248653300832,
      0.0801209827383845, 0.079429578126956377, 0.07873704464540536,
      0.078043392136163764, 0.07734863045757176, 0.076652769483729274,
      0.075955819104359945, 0.0752577892246738, 0.074558689765219149,
      0.073858530661745733, 0.07315732186506653, 0.072455073340909587,
      0.071751795069779453, 0.071047497046819716, 0.070342189281662859,
      0.069635881798292346, 0.068928584634903242, 0.068220307843752784,
      0.067511061491020583, 0.066800855656670946, 0.066089700434295948,
      0.065377605930987792, 0.064664582267188284, 0.063950639576536766,
      0.063235788005741853, 0.062520037714429169, 0.061803398874989507,
      0.061085881672451041, 0.060367496304319992, 0.059648252980441512,
      0.058928161922857637, 0.058207233365655121, 0.057485477554823111,
      0.056762904748112, 0.056039525214879329, 0.055315349235948386,
      0.054590387103465268, 0.053864649120745206, 0.053138145602130253,
      0.052410886872845931, 0.051682883268847457, 0.050954145136676024,
      0.0502246828333163, 0.049494506726040832, 0.048763627192267227,
      0.048032054619413879, 0.047299799404745269, 0.046566871955227462,
      0.045833282687384375, 0.045099042027142162, 0.0443641604096844,
      0.043628648279309595, 0.042892516089267807, 0.042155774301629673,
      0.041418433387129278, 0.040680503825007847, 0.039941996102880628,
      0.0392029207165795, 0.038463288169996591, 0.037723108974951319,
      0.03698239365102729, 0.036241152725427363, 0.03549939673282862,
      0.034757136215224117, 0.034014381721777669, 0.033271143808677246,
      0.032527433038977364, 0.031783259982453134, 0.031038635215453358,
      0.030293569320743081, 0.029548072887356371, 0.028802156510450524,
      0.028055830791146846, 0.02730910633638467, 0.026561993758773834,
      0.025814503676436659, 0.02506664671286038, 0.024318433496750391,
      0.02356987466187152, 0.022820980846900249, 0.022071762695278194,
      0.02132223085505219, 0.020572395978727624, 0.019822268723121747,
      0.019071859749197877, 0.018321179721931397, 0.017570239310149605,
      0.016819049186372833, 0.01606762002667798, 0.015315962510539528,
      0.014564087320669095, 0.013812005142881568, 0.013059726665927925,
      0.012307262581349343, 0.011554623583328621, 0.01080182036853047,
      0.010048863635953755, 0.0092957640867828012, 0.00854253242422804,
      0.0077891793533771715, 0.0070357155810477209, 0.0062821518156261809,
      0.0055284987669205216, 0.004774767146011355, 0.0040209676650919826,
      0.0032671110373204133, 0.0025132079766704788, 0.0017592691977722855,
      0.0010053054157632194, 0.00025132734614036737, -0.00050265429540047649,
      -0.0012566287931123981, -0.0020105854313463719, -0.0027645134947108358,
      -0.0035184022682206067, -0.0042722410374435686, -0.005026019088667337,
      -0.0057797257090348225, -0.0065333501867037777, -0.0072868818110077274,
      -0.00804030987259017, -0.0087936236635721438, -0.0095468124776983687,
      -0.010299865610486033, -0.011052772359384656, -0.011805522023923922,
      -0.012558103905862403, -0.013310507309346862, -0.014062721541060997,
      -0.014814735910372707, -0.015566539729494719, -0.016318122313631802,
      -0.017069472981129229, -0.017820581053632312, -0.018571435856233911,
      -0.019322026717622787, -0.020072342970242504, -0.020822373950439794,
      -0.021572108998611398, -0.022321537459364243, -0.023070648681662188,
      -0.023819432018974126, -0.024567876829432546, -0.02531597247598142,
      -0.026063708326521814, -0.026811073754077288, -0.02755805813692835,
      -0.028304650858770649, -0.029050841308874482, -0.029796618882219034,
      -0.030541972979651662, -0.03128689300804615, -0.032031368380435889,
      -0.032775388516179428, -0.033518942841104876, -0.034262020787656979,
      -0.03500461179505443, -0.035746705309436785, -0.036488290784009766,
      -0.037229357679203774, -0.037969895462819, -0.038709893610171832,
      -0.039449341604251995, -0.040188228935867848, -0.040926545103792455,
      -0.041664279614919919, -0.042401421984411346, -0.043137961735839211,
      -0.043873888401344791, -0.044609191521782325, -0.04534386064686443,
      -0.046077885335317786, -0.046811255155028181, -0.047543959683184651,
      -0.048275988506435136, -0.04900733122103116, -0.049737977432969885,
      -0.050467916758156678, -0.051197138822535251, -0.051925633262243434,
      -0.052653389723767964, -0.053380397864075869, -0.054106647350769858,
      -0.054832127862242119, -0.055556829087805064, -0.056280740727851247,
      -0.057003852493995338, -0.057726154109215791, -0.058447635308009283,
      -0.0591682858365321, -0.059888095452742589, -0.060607053926554168,
      -0.0613251510399766, -0.062042376587258023, -0.062758720375036922,
      -0.0634741722224839, -0.0641887219614418, -0.064902359436578669,
      -0.0656150745055274, -0.0663268570390269, -0.067037696921072962,
      -0.067747584049058715, -0.06845650833391434, -0.069164459700257613,
      -0.069871428086533974, -0.070577403445155132, -0.07128237574264995,
      -0.071986334959802709, -0.072689271091791074, -0.073391174148341717,
      -0.07409203415385586, -0.074791841147559185, -0.075490585183650052,
      -0.076188256331426729, -0.0768848446754353, -0.077580340315618557,
      -0.078274733367440119, -0.078968013962039063, -0.079660172246364652,
      -0.080351198383313172, -0.081041082551874963, -0.081729814947269955,
      -0.08241738578108404, -0.083103785281414766, -0.083789003693007263,
      -0.084473031277388588, -0.08515585831301406, -0.085837475095401072,
      -0.086517871937264068, -0.087197039168659174, -0.087874967137117677,
      -0.088551646207780346, -0.0892270667635408, -0.089901219205179211,
      -0.090574093951494627, -0.091245681439448847, -0.091915972124298112,
      -0.092584956479725908, -0.093252624997984743, -0.09391896819002836,
      -0.0945839765856416, -0.095247640733587685, -0.095909951201727864,
      -0.09657089857716189, -0.097230473466369316, -0.097888666495328569,
      -0.098545468309657588, -0.099200869574753256, -0.099854860975909454,
      -0.100507433218462, -0.10115857702791585, -0.10180828315007402,
      -0.10245654235117539, -0.10310334541802305, -0.10374868315811132,
      -0.10439254639976372, -0.10503492599225939, -0.10567581280596022,
      -0.10631519773244716, -0.10695307168464614, -0.10758942559695424,
      -0.10822425042537476, -0.108857537147643, -0.10948927676335043,
      -0.11011946029408004, -0.11074807878352991, -0.11137512329763775,
      -0.11200058492471404, -0.11262445477556578, -0.11324672398361819,
      -0.1138673837050527, -0.11448642511891878, -0.11510383942726538,
      -0.11571961785527296, -0.11633375165136479, -0.11694623208733812,
      -0.11755705045849461, -0.11816619808374872, -0.11877366630576876,
      -0.11937944649108437, -0.11998353003021628, -0.12058590833780432,
      -0.12118657285271739, -0.12178551503818094, -0.12238272638190509,
      -0.12297819839619246, -0.12357192261806565, -0.12416389060939348,
      -0.12475409395699827, -0.12534252427278206, -0.12592917319385161,
      -0.12651403238262524, -0.12709709352695708, -0.12767834834026198,
      -0.12825778856162018, -0.12883540595590157, -0.12941119231388862,
      -0.12998513945238041, -0.13055723921431586, -0.13112748346889488,
      -0.13169586411168252, -0.13226237306472954, -0.13282700227669395,
      -0.13338974372294263, -0.13395058940567214, -0.13450953135402788,
      -0.13506656162420547, -0.13562167229956992, -0.13617485549077363,
      -0.13672610333585708, -0.13727540800036619, -0.13782276167746976,
      -0.13836815658805843, -0.13891158498086148, -0.13945303913256227,
      -0.139992511347897, -0.14052999395976937, -0.14106547932936558,
      -0.1415989598462514, -0.14213042792848579, -0.14265987602273481,
      -0.1431872966043671, -0.14371268217756702, -0.14423602527544618,
      -0.14475731846013903, -0.14527655432291359, -0.14579372548428263,
      -0.14630882459409741, -0.14682184433165749, -0.14733277740582054,
      -0.14784161655509473, -0.14834835454774772, -0.14885298418191445,
      -0.14935549828568728, -0.14985588971723218, -0.15035415136487729,
      -0.15085027614722013, -0.15134425701323273, -0.15183608694235187,
      -0.15232575894458381, -0.15281326606060902, -0.1532986013618689,
      -0.15378175795067781, -0.15426272896030946, -0.15474150755509952,
      -0.15521808693054781, -0.15569246031340486, -0.15616462096177297,
      -0.15663456216520766, -0.15710227724480255, -0.15756775955328955,
      -0.15803100247513777, -0.15849199942663833, -0.15895074385600255,
      -0.15940722924345987, -0.159861449101341, -0.16031339697417454,
      -0.16076306643878413, -0.16121045110436971, -0.16165554461260345,
      -0.1620983406377243, -0.16253883288661916, -0.16297701509891657,
      -0.16341288104708049, -0.16384642453648957, -0.16427763940552942,
      -0.16470651952568538, -0.16513305880162019, -0.16555725117126507,
      -0.1659790906059104, -0.16639857111028258, -0.16681568672263372,
      -0.16723043151483072, -0.16764279959243031, -0.168052785094768,
      -0.16846038219504525, -0.16886558510040353, -0.16926838805201136,
      -0.16966878532514984, -0.17006677122928604, -0.170462340108158,
      -0.17085548633985925, -0.17124620433690996, -0.17163448854634128,
      -0.17202033344977791, -0.17240373356350827, -0.17278468343856687,
      -0.17316317766081524, -0.17353921085101146, -0.17391277766489022,
      -0.17428387279324287, -0.17465249096198476, -0.17501862693223461,
      -0.17538227550039237, -0.1757434314982044, -0.17610208979284717,
      -0.17645824528699103, -0.17681189291887681, -0.17716302766239142,
      -0.17751164452713172, -0.177857738558479, -0.17820130483767357,
      -0.17854233848187565, -0.1788808346442447, -0.17921678851399983,
      -0.17955019531649163, -0.17988105031327387, -0.18020934880216347,
      -0.18053508611731117, -0.18085825762927088, -0.18117885874505893,
      -0.18149688490822274, -0.18181233159890881, -0.18212519433392038,
      -0.18243546866678417, -0.18274315018781748, -0.18304823452418365,
      -0.183350717339958, -0.18365059433619219, -0.18394786125096929,
      -0.18424251385946738, -0.1845345479740228, -0.18482395944418339,
      -0.18511074415677037, -0.18539489803594028, -0.18567641704323654,
      -0.18595529717764991, -0.18623153447567831, -0.18650512501137728,
      -0.18677606489641885, -0.18704435028014935, -0.18730997734963878,
      -0.18757294232973745, -0.18783324148313285, -0.18809087111039691,
      -0.18834582755004148, -0.18859810717857295, -0.18884770641053847,
      -0.18909462169857963, -0.18933884953348545, -0.1895803864442368,
      -0.1898192289980587, -0.19005537380047155, -0.19028881749533411,
      -0.190519556764894, -0.19074758832983696, -0.19097290894932897,
      -0.19119551542106447, -0.19141540458131437, -0.19163257330496614,
      -0.19184701850557073, -0.19205873713538876, -0.19226772618542903,
      -0.19247398268549393, -0.19267750370422332, -0.19287828634913243,
      -0.1930763277666547, -0.19327162514218468, -0.1934641757001129,
      -0.19365397670387113, -0.19384102545596626, -0.19402531929802092,
      -0.19420685561081297, -0.19438563181430879, -0.19456164536770235,
      -0.19473489376945258, -0.19490537455731505, -0.19507308530838158,
      -0.19523802363911058, -0.19540018720536267, -0.19555957370243579,
      -0.19571618086509446, -0.19587000646760369, -0.19602104832376227,
      -0.1961693042869305, -0.19631477225006255, -0.19645745014573765,
      -0.19659733594618656, -0.19673442766332191, -0.19686872334876798,
      -0.19700022109388532, -0.1971289190297994, -0.19725481532742861,
      -0.19737790819750745, -0.19749819589061335, -0.19761567669719271,
      -0.1977303489475829, -0.19784221101203694, -0.19795126130074814,
      -0.19805749826387009, -0.19816092039154, -0.19826152621390131,
      -0.19835931430112214, -0.19845428326341705, -0.19854643175106748,
      -0.19863575845443915, -0.19872226210400157, -0.19880594147034705,
      -0.19888679536420623, -0.19896482263646598, -0.1990400221781867,
      -0.19911239292061611, -0.19918193383520555, -0.19924864393362515,
      -0.19931252226777652, -0.19937356792980693, -0.19943178005212281,
      -0.19948715780740087, -0.19953970040860042, -0.19958940710897513,
      -0.19963627720208266, -0.19968031002179498, -0.19972150494230867,
      -0.19975986137815249, -0.19979537878419651, -0.19982805665565997,
      -0.19985789452811792, -0.199884891977508, -0.19990904862013692,
      -0.19993036411268514, -0.19994883815221245, -0.19996447047616184,
      -0.19997726086236325, -0.19998720912903717, -0.1999943151347966,
      -0.19999857877864946, -0.2, -0.19999857877864949, -0.1999943151347966,
      -0.19998720912903717, -0.19997726086236331, -0.19996447047616184,
      -0.19994883815221245, -0.19993036411268519, -0.19990904862013692,
      -0.19988489197750803, -0.19985789452811792, -0.19982805665565997,
      -0.19979537878419651, -0.19975986137815249, -0.19972150494230867,
      -0.19968031002179498, -0.19963627720208266, -0.19958940710897513,
      -0.19953970040860042, -0.19948715780740089, -0.19943178005212281,
      -0.19937356792980693, -0.19931252226777652, -0.19924864393362515,
      -0.19918193383520555, -0.19911239292061611, -0.19904002217818673,
      -0.198964822636466, -0.19888679536420623, -0.19880594147034708,
      -0.1987222621040016, -0.19863575845443915, -0.19854643175106748,
      -0.19845428326341705, -0.19835931430112214, -0.19826152621390131,
      -0.19816092039154004, -0.19805749826387012, -0.19795126130074814,
      -0.19784221101203697, -0.1977303489475829, -0.19761567669719274,
      -0.19749819589061335, -0.19737790819750745, -0.19725481532742861,
      -0.19712891902979943, -0.19700022109388535, -0.19686872334876798,
      -0.19673442766332194, -0.19659733594618656, -0.19645745014573768,
      -0.19631477225006258, -0.19616930428693052, -0.19602104832376227,
      -0.19587000646760372, -0.19571618086509449, -0.19555957370243582,
      -0.19540018720536323, -0.19523802363911058, -0.19507308530838161,
      -0.19490537455731569, -0.1947348937694526, -0.19456164536770235,
      -0.19438563181430882, -0.19420685561081297, -0.19402531929802158,
      -0.19384102545596629, -0.19365397670387116, -0.19346417570011359,
      -0.19327162514218471, -0.19307632776665473, -0.19287828634913246,
      -0.19267750370422335, -0.19247398268549393, -0.19226772618542906,
      -0.19205873713538879, -0.19184701850557076, -0.19163257330496616,
      -0.1914154045813144, -0.1911955154210645, -0.190972908949329,
      -0.190747588329837, -0.19051955676489402, -0.19028881749533413,
      -0.19005537380047158, -0.18981922899805873, -0.1895803864442368,
      -0.18933884953348548, -0.18909462169857966, -0.1888477064105385,
      -0.18859810717857295, -0.18834582755004151, -0.18809087111039691,
      -0.18783324148313288, -0.18757294232973748, -0.18730997734963881,
      -0.18704435028014937, -0.18677606489641885, -0.18650512501137731,
      -0.18623153447567831, -0.18595529717764994, -0.18567641704323656,
      -0.18539489803594031, -0.1851107441567704, -0.18482395944418339,
      -0.18453454797402283, -0.18424251385946741, -0.18394786125096929,
      -0.18365059433619224, -0.18335071733995803, -0.1830482345241837,
      -0.1827431501878175, -0.1824354686667842, -0.18212519433392038,
      -0.18181233159890883, -0.18149688490822277, -0.18117885874505896,
      -0.18085825762927091, -0.18053508611731237, -0.18020934880216352,
      -0.17988105031327389, -0.17955019531649286, -0.17921678851399989,
      -0.17888083464424473, -0.17854233848187687, -0.1782013048376736,
      -0.17785773855848028, -0.17751164452713175, -0.17716302766239145,
      -0.17681189291887808, -0.17645824528699106, -0.17610208979284722,
      -0.1757434314982057, -0.17538227550039243, -0.17501862693223466,
      -0.17465249096198482, -0.17428387279324289, -0.17391277766489022,
      -0.17353921085101151, -0.17316317766081529, -0.1727846834385669,
      -0.17240373356350833, -0.17202033344977796, -0.17163448854634134,
      -0.17124620433690999, -0.17085548633985928, -0.17046234010815806,
      -0.1700667712292861, -0.16966878532514984, -0.16926838805201139,
      -0.16886558510040359, -0.16846038219504531, -0.16805278509476806,
      -0.16764279959243034, -0.16723043151483075, -0.16681568672263378,
      -0.16639857111028264, -0.16597909060591043, -0.16555725117126513,
      -0.16513305880162021, -0.16470651952568544, -0.16427763940552945,
      -0.16384642453648959, -0.16341288104708052, -0.1629770150989166,
      -0.16253883288661919, -0.16209834063772433, -0.16165554461260348,
      -0.16121045110436974, -0.16076306643878416, -0.1603133969741746,
      -0.15986144910134104, -0.15940722924345993, -0.15895074385600261,
      -0.15849199942663839, -0.15803100247513779, -0.15756775955328961,
      -0.15710227724480261, -0.15663456216520771, -0.156164620961773,
      -0.15569246031340489, -0.15521808693054784, -0.15474150755510127,
      -0.15426272896030951, -0.15378175795067783, -0.15329860136187068,
      -0.15281326606060908, -0.15232575894458386, -0.15183608694235193,
      -0.15134425701323281, -0.15085027614722188, -0.15035415136487737,
      -0.14985588971723224, -0.1493554982856892, -0.14885298418191456,
      -0.1483483545477477, -0.14784161655509476, -0.1473327774058206,
      -0.14682184433165757, -0.14630882459409741, -0.14579372548428268,
      -0.14527655432291361, -0.14475731846013909, -0.14423602527544629,
      -0.143712682177567, -0.14318729660436716, -0.14265987602273486,
      -0.1421304279284859, -0.14159895984625137, -0.14106547932936561,
      -0.14052999395976942, -0.13999251134789706, -0.13945303913256241,
      -0.13891158498086148, -0.13836815658805848, -0.13782276167746985,
      -0.13727540800036631, -0.13672610333585708, -0.13617485549077366,
      -0.13562167229956998, -0.13506656162420558, -0.13450953135402788,
      -0.13395058940567217, -0.13338974372294268, -0.13282700227669397,
      -0.13226237306472965, -0.13169586411168252, -0.13112748346889494,
      -0.13055723921431592, -0.12998513945238055, -0.12941119231388859,
      -0.12883540595590165, -0.12825778856162023, -0.127678348340262,
      -0.12709709352695722, -0.12651403238262521, -0.12592917319385163,
      -0.12534252427278211, -0.12475409395699839, -0.12416389060939347,
      -0.1235719226180657, -0.12297819839619253, -0.12238272638190516,
      -0.12178551503818319, -0.12118657285271738, -0.12058590833780436,
      -0.11998353003021844, -0.11937944649108451, -0.11877366630576874,
      -0.11816619808375091, -0.11755705045849468, -0.11694623208734041,
      -0.11633375165136493, -0.11571961785527296, -0.11510383942726761,
      -0.11448642511891885, -0.11386738370505284, -0.11324672398362037,
      -0.11262445477556585, -0.1120005849247141, -0.11137512329763891,
      -0.11074807878353005, -0.11011946029408003, -0.10948927676335161,
      -0.10885753714764307, -0.1082242504253749, -0.10758942559695535,
      -0.10695307168464621, -0.10631519773244723, -0.10567581280596149,
      -0.10503492599225953, -0.1043925463997637, -0.10374868315811253,
      -0.10310334541802312, -0.10245654235117552, -0.10180828315007516,
      -0.10115857702791592, -0.10050743321846206, -0.099854860975910745,
      -0.099200869574753381, -0.098545468309657575, -0.097888666495328625,
      -0.097230473466369385, -0.096570898577162015, -0.09590995120172785,
      -0.095247640733587755, -0.09458397658564166, -0.0939189681900285,
      -0.093252624997984729, -0.0925849564797247, -0.091915972124298181,
      -0.091245681439448917, -0.090574093951493587, -0.0899012192051792,
      -0.089227066763540863, -0.088551646207779222, -0.087874967137117829,
      -0.087197039168659146, -0.086517871937262944, -0.085837475095401142,
      -0.085155858313014129, -0.084473031277387534, -0.08378900369300725,
      -0.083103785281414821, -0.082417385781082875, -0.081729814947270107,
      -0.081041082551874949, -0.080351198383314462, -0.079660172246364722,
      -0.078968013962039132, -0.078274733367441493, -0.077580340315618529,
      -0.076884844675435368, -0.0761882563314268, -0.0754905851836502,
      -0.074791841147561641, -0.074092034153855929, -0.073391174148341773,
      -0.072689271091793711, -0.071986334959802875, -0.071282375742649937,
      -0.070577403445156436, -0.069871428086534057, -0.069164459700257766,
      -0.068456508333915575, -0.067747584049058784, -0.067037696921073017,
      -0.066326857039028228, -0.065615074505527546, -0.064902359436578655,
      -0.064188721961443138, -0.063474172222483957, -0.062758720375037089,
      -0.062042376587259279, -0.061325151039976669, -0.060607053926554237,
      -0.059888095452744018, -0.059168285836532254, -0.058447635308009276,
      -0.057726154109217137, -0.0570038524939954, -0.0562807407278514,
      -0.055556829087806327, -0.0548321278622422, -0.054106647350769935,
      -0.053380397864076029, -0.052653389723767957, -0.051925633262243504,
      -0.051197138822535321, -0.050467916758156754, -0.049737977432970037,
      -0.049007331221031153, -0.048275988506435205, -0.04754395968318343,
      -0.04681125515502834, -0.046077885335317773, -0.045343860646863118,
      -0.044609191521782394, -0.043873888401344867, -0.043137961735838073,
      -0.042401421984411332, -0.041664279614919995, -0.04092654510379122,
      -0.040188228935868008, -0.039449341604251981, -0.0387098936101706,
      -0.037969895462819071, -0.037229357679203844, -0.036488290784011237,
      -0.035746705309436765, -0.035004611795054506, -0.034262020787658359,
      -0.033518942841105036, -0.032775388516179414, -0.032031368380437276,
      -0.031286893008046227, -0.030541972979654455, -0.02979661888221919,
      -0.029050841308874465, -0.028304650858773362, -0.027558058136928423,
      -0.026811073754077448, -0.026063708326524437, -0.025315972475981493,
      -0.024567876829432622, -0.023819432018975521, -0.023070648681662351,
      -0.02232153745936423, -0.021572108998612796, -0.020822373950439867,
      -0.020072342970242667, -0.019322026717624095, -0.018571435856233984,
      -0.017820581053632385, -0.017069472981130717, -0.016318122313631965,
      -0.015566539729494705, -0.014814735910374108, -0.014062721541061069,
      -0.013310507309347026, -0.012558103905863717, -0.011805522023923995,
      -0.011052772359384729, -0.010299865610487527, -0.00954681247769853,
      -0.0087936236635721282, -0.0080403098725915743, -0.0072868818110078011,
      -0.0065333501867039408, -0.0057797257090348069, -0.00502601908866741,
      -0.0042722410374436423, -0.0035184022682207688, -0.0027645134947108206,
      -0.002010585431345024, -0.0012566287931124716, -0.00050265429540054989,
      0.00025132734614153734, 0.0010053054157632348, 0.001759269197772212,
      0.0025132079766717373, 0.0032671110373202507, 0.0040209676650919983,
      0.0047747671460126135, 0.0055284987669204479, 0.0062821518156261072,
      0.0070357155810488892, 0.0077891793533771863, 0.0085425324242279672,
      0.0092957640867840589, 0.010048863635953593, 0.010801820368530488,
      0.011554623583327218, 0.01230726258134927, 0.013059726665927852,
      0.013812005142880078, 0.014564087320669109, 0.015315962510539455,
      0.016067620026677904, 0.01681904918637267, 0.017570239310146965,
      0.018321179721931324, 0.019071859749197805, 0.019822268723118933,
      0.020572395978727464, 0.021322230855052204, 0.022071762695276796,
      0.022820980846900176, 0.023569874661871357, 0.024318433496749083,
      0.02506664671286031, 0.025814503676436586, 0.02656199375877244,
      0.02730910633638451, 0.028055830791146864, 0.028802156510449137,
      0.029548072887356298, 0.030293569320742921, 0.031038635215452061,
      0.031783259982453065, 0.032527433038977295, 0.033271143808675775,
      0.0340143817217775, 0.034757136215224131, 0.035499396732827239,
      0.036241152725427293, 0.03698239365102713, 0.037723108974950022,
      0.038463288169996522, 0.03920292071657943, 0.039941996102880475,
      0.04068050382500786, 0.041418433387129208, 0.042155774301629596,
      0.042892516089267738, 0.043628648279309436, 0.044364160409684411,
      0.045099042027142093, 0.045833282687385596, 0.04656687195522731,
      0.047299799404745282, 0.048032054619415183, 0.04876362719226715,
      0.049494506726040756, 0.050224682833317429, 0.050954145136676038,
      0.051682883268847381, 0.052410886872847146, 0.053138145602130094,
      0.053864649120745227, 0.054590387103466476, 0.055315349235948323,
      0.05603952521487926, 0.056762904748110569, 0.057485477554823132,
      0.058207233365655059, 0.0589281619228563, 0.059648252980441352,
      0.060367496304320013, 0.061085881672449695, 0.061803398874989438,
      0.062520037714426477, 0.0632357880057417, 0.06395063957653678,
      0.064664582267185688, 0.065377605930987723, 0.0660897004342958,
      0.066800855656668448, 0.067511061491020527, 0.0682203078437527,
      0.068928584634901924, 0.069635881798292193, 0.070342189281662887,
      0.0710474970468184, 0.071751795069779384, 0.072455073340909434,
      0.0731573218650653, 0.073858530661745678, 0.07455868976521908,
      0.075257789224672411, 0.0759558191043598, 0.076652769483729288,
      0.077348630457570455, 0.0780433921361637, 0.078737044645405208,
      0.079429578126955169, 0.08012098273838443, 0.080811248653300763,
      0.081500366061495161, 0.082188325169088777, 0.082875116198657617,
      0.083560729389378155, 0.084245154997174387, 0.084928383294841023,
      0.085610404572189353, 0.086291209136191871, 0.086970787311106523,
      0.0876491294386208, 0.088326225877996475, 0.0890020670061917,
      0.089676643218005836, 0.090349944926222517, 0.0910219625617317,
      0.091692686573673077, 0.0923621074295782, 0.09303021561549274,
      0.09369700163611816, 0.094362456014954021, 0.095026569294417967,
      0.095689332035988076, 0.096350734820343453, 0.097010768247484169,
      0.097669422936872058, 0.098326689527570413, 0.098982558678363919,
      0.0996370210678979, 0.10029006739481788, 0.10094168837788514,
      0.10159187475612785, 0.10224061728895617, 0.10288790675630036,
      0.10353373395874906, 0.10417808971766558, 0.10482096487532618,
      0.10546235029505642, 0.1061022368613454, 0.10674061547999281,
      0.10737747707822332, 0.10801281260482171, 0.10864661303026829,
      0.109278869346854, 0.10990957256881456, 0.11053871373246574,
      0.11116628389631673, 0.11179227414120435, 0.11241667557042567,
      0.11303947930985224, 0.11366067650806214, 0.11428025833647254,
      0.11489821598945216, 0.11551454068445244, 0.11612922366213974,
      0.11674225618650613, 0.11735362954500049, 0.11796333504865815,
      0.11857136403221231, 0.11917770785422309, 0.11978235789720691,
      0.12038530556774628, 0.12098654229661775, 0.12158605953892093,
      0.1221838487741867, 0.12277990150650482, 0.12337420926465054,
      0.12396676360219312, 0.12455755609762176, 0.12514657835447165,
      0.12573382200143041, 0.12631927869246393, 0.12690294010694092,
      0.12748479794973866, 0.12806484395136739, 0.12864306986809321,
      0.1292194674820441, 0.12979402860133207, 0.13036674506017604,
      0.13093760871900503, 0.13150661146458106, 0.13207374521011961,
      0.13263900189539277, 0.13320237348685002, 0.13376385197773771,
      0.13432342938820183, 0.13488109776540669, 0.13543684918365442,
      0.13599067574448495, 0.13654256957679509, 0.1370925228369558,
      0.13764052770891197, 0.13818657640429954, 0.13873066116256152,
      0.13927277425104539, 0.13981290796512805, 0.14035105462831204,
      0.14088720659233994, 0.14142135623730948, 0.14195349597176807,
      0.14248361823283598, 0.14301171548630071, 0.14353778022672914,
      0.14406180497758081, 0.14458378229130217, 0.14510370474943851,
      0.14562156496274423, 0.14613735557127772, 0.14665106924451093,
      0.14716269868143905, 0.14767223661067364, 0.14817967579055077,
      0.14868500900924025, 0.14918822908483664, 0.14968932886546713,
      0.150188301229398, 0.15068513908512579, 0.15117983537148305,
      0.15167238305774408, 0.15216277514371435, 0.15265100465983489,
      0.1531370646672871, 0.1536209482580807, 0.15410264855515721,
      0.15458215871249226, 0.1550594719151836, 0.15553458137955237,
      0.15600748035324483, 0.15647816211531818, 0.15694661997634085,
      0.15741284727849314, 0.15787683739565142, 0.15833858373348758,
      0.15879807972956714, 0.1592553188534333, 0.15971029460670449,
      0.16016300052317145, 0.16061343016887919, 0.161061577142224,
      0.16150743507404852, 0.16195099762772311, 0.16239225849924052,
      0.16283121141731, 0.1632678501434375, 0.16370216847201868,
      0.16413416023043187, 0.16456381927911626, 0.1649911395116643,
      0.16541611485491262, 0.1658387392690194, 0.16625900674755489,
      0.16667691131759066, 0.16709244703977635, 0.16750560800842818,
      0.16791638835161718, 0.16832478223124236, 0.1687307838431257,
      0.16913438741708411, 0.16953558721701609, 0.16993437754098728,
      0.17033075272130285, 0.17072470712459287, 0.17111623515189597,
      0.17150533123872957, 0.17189198985517964, 0.17227620550597,
      0.17265797273054451, 0.1730372861031485, 0.17341414023289814,
      0.1737885297638605, 0.17416044937513442, 0.17452989378091766,
      0.17489685773058616, 0.17526133600877247, 0.17562332343543216,
      0.17598281486592141, 0.17633980519107378, 0.17669428933726539,
      0.17704626226649045, 0.17739571897643708, 0.17774265450055071,
      0.17808706390810844, 0.17842894230429251, 0.17876828483025303,
      0.17910508666318037, 0.17943934301637735, 0.17977104913932021,
      0.18010020031772941, 0.1804267918736405, 0.1807508191654634,
      0.181072277588052, 0.18139116257277269, 0.1817074695875629,
      0.18202119413699874, 0.18233233176236219, 0.18264087804169765,
      0.18294682858987851, 0.18325017905867239, 0.18355092513679661,
      0.18384906254998271, 0.18414458706104009, 0.18443749446991031,
      0.18472778061372971, 0.18501544136689174, 0.18530047264109925,
      0.18558287038542595, 0.18586263058637678, 0.18613974926793908,
      0.18641422249164205, 0.18668604635661545, 0.18695521699963957,
      0.18722173059520281, 0.187485583355559, 0.18774677153077535,
      0.18800529140878883, 0.1882611393154616, 0.18851431161462764,
      0.18876480470814741, 0.18901261503596123, 0.18925773907613405,
      0.18950017334491248, 0.1897399143967681, 0.18997695882444893,
      0.19021130325903071, 0.19044294436995862, 0.1906718788651014,
      0.19089810349079234, 0.19112161503187786, 0.19134241031176588,
      0.19156048619246591, 0.19177583957463629, 0.19198846739763017,
      0.19219836663953485, 0.19240553431721674, 0.19260996748636605,
      0.19281166324153426, 0.19301061871617742, 0.19320683108269926,
      0.19340029755248711, 0.1935910153759535, 0.1937789818425773,
      0.19396419428093831, 0.19414665005875717, 0.19432634658293468,
      0.19450328129958491, 0.19467745169407316, 0.19484885529105389,
      0.19501748965450197, 0.19518335238774925, 0.19534644113352029,
      0.19550675357396241, 0.19566428743068046, 0.19581904046477072,
      0.19597101047684956, 0.19612019530708608, 0.1962665928352347,
      0.196410200980662, 0.1965510177023779, 0.19668904099906595,
      0.1968242689091092, 0.19695669951061923, 0.197086330921465,
      0.19721316129929667, 0.1973371888415735, 0.19745841178559043,
      0.19757682840850063, 0.19769243702734141, 0.19780523599905914,
      0.19791522372053039, 0.19802239862858578, 0.19812675920003345,
      0.19822830395167823, 0.19832703144034411, 0.19842294026289564,
      0.19851602905625579, 0.19860629649742645, 0.19869374130350814,
      0.19877836223171622, 0.19886015807939975, 0.19893912768405927,
      0.1990152699233613, 0.19908858371515661, 0.19915906801749372,
      0.19922672182863441, 0.19929154418706874, 0.19935353417152729,
      0.19941269090099495, 0.19946901353472404, 0.19952250127224494,
      0.1995731533533788, 0.19962096905824731, 0.19966594770728321,
      0.19970808866124076, 0.19974739132120353, 0.19978385512859353,
      0.19981747956517973, 0.19984826415308421, 0.19987620845478982,
      0.19990131207314632, 0.19992357465137564, 0.19994299587307718,
      0.19995957546223259, 0.1999733131832091, 0.19998420884076321,
      0.19999226228004366, 0.19999747338659316, 0.19999984208635035,
      0.19999936834565082, 0.19999605217122743, 0.19998989361021038,
      0.19998089275012643, 0.19996904971889773, 0.19995436468483999,
      0.19993683785666003, 0.19991646948345285, 0.19989325985469819,
      0.19986720930025617, 0.19983831819036288, 0.199806586935625,
      0.19977201598701372, 0.19973460583585886, 0.19969435701384161,
      0.19965127009298653, 0.19960534568565425, 0.1995565844445325,
      0.19950498706262604, 0.19945055427324809, 0.19939328685000923,
      0.19933318560680596, 0.19927025139781016, 0.19920448511745645,
      0.19913588770042881, 0.19906446012164861, 0.19899020339626008,
      0.19891311857961519, 0.19883320676726002, 0.19875046909491864,
      0.19866490673847589, 0.19857652091396258, 0.19848531287753721,
      0.19839128392546723, 0.19829443539411254, 0.19819476865990543,
      0.19809228513933017, 0.1979869862889051, 0.19787887360515929,
      0.19776794862461355, 0.19765421292375795, 0.19753766811902759,
      0.197418315866783, 0.19729615786328306, 0.19717119584466378,
      0.19704343158691248, 0.19691286690584123, 0.19677950365706356,
      0.19664334373596692, 0.19650438907768428, 0.19636264165706929,
      0.19621810348866708, 0.19607077662668404, 0.19592066316496143,
      0.19576776523694439, 0.19561208501564969, 0.19545362471363859,
      0.19529238658298331, 0.19512837291523333, 0.19496158604138647,
      0.19479202833185416, 0.19461970219642544, 0.19444461008423675,
      0.19426675448373518, 0.19408613792264132, 0.19390276296791689,
      0.19371663222572649, 0.19352774834139877, 0.19333611399939243,
      0.19314173192325626, 0.19294460487558859, 0.19274473565800174,
      0.19254212711108043, 0.19233678211433902, 0.19212870358618536,
      0.19191789448387664, 0.19170435780347522, 0.1914880965798107,
      0.19126911388643481, 0.19104741283557455, 0.19082299657809343,
      0.190595868303444, 0.19036603123962023, 0.19013348865311633,
      0.189898243848878, 0.18966030017025298, 0.18941966099894847,
      0.18917632975498055, 0.18893030989662321, 0.188681604920364,
      0.18843021836085208, 0.1881761537908449, 0.18791941482116356,
      0.18766000510063796, 0.18739792831605248, 0.1871331881920992,
      0.18686578849132254, 0.186595733014062, 0.18632302559840558,
      0.18604767012012752, 0.18576967049263954, 0.18548903066693262,
      0.18520575463151806, 0.18491984641237624, 0.18463131007289682,
      0.18434014971381793, 0.18404636947317482, 0.18374997352623276,
      0.18345096608543521, 0.18314935140034116, 0.18284513375756056,
      0.18253831748070057, 0.18222890693030067, 0.1819169065037676,
      0.18160232063531909, 0.1812851537959177, 0.18096541049320414,
      0.18064309527143962, 0.18031821271143789, 0.17999076743049716,
      0.17966076408234072, 0.17932820735704785, 0.17899310198098309,
      0.17865545271673719, 0.17831526436305464, 0.17797254175476243,
      0.17762728976270858, 0.17727951329368971, 0.17692921729037647,
      0.1765764067312518, 0.17622108663053582, 0.17586326203811137,
      0.17550293803945904, 0.17514011975558175, 0.17477481234292791,
      0.1744070209933257, 0.17403675093390553, 0.17366400742702212,
      0.17328879577018697, 0.17291112129598962, 0.17253098937201744,
      0.17214840540078818, 0.17176337481966819, 0.17137590310079145,
      0.17098599575099002, 0.17059365831171217, 0.17019889635893828,
      0.169801715503111, 0.16940212138905072, 0.1690001196958717,
      0.1685957161369091, 0.16818891645963407, 0.16777972644556771,
      0.16736815191020726, 0.16695419870293926, 0.16653787270695231,
      0.16611917983916172, 0.16569812605012152, 0.1652747173239347,
      0.16484895967817842, 0.16442085916381266, 0.16399042186509016,
      0.16355765389948074, 0.1631225614175722, 0.16268515060299327,
      0.16224542767232131, 0.16180339887498951, 0.16135907049320708,
      0.1609124488418652, 0.16046354026844328, 0.16001235115292892,
      0.15955888790771461, 0.15910315697751887, 0.15864516483928856,
      0.15818491800210221, 0.15772242300708769, 0.15725768642732477,
      0.15679071486774526, 0.15632151496505042, 0.15585009338761094,
      0.15537645683536788, 0.15490061203974659, 0.15442256576355645,
      0.15394232480089007, 0.15345989597703613, 0.15297528614837763,
      0.15248850220228977, 0.15199955105705151, 0.15150843966174277,
      0.15101517499613962, 0.15051976407062712, 0.15002221392609272,
      0.14952253163382165, 0.14902072429540689, 0.14851679904264381,
      0.14801076303742175, 0.14750262347163434, 0.14699238756707123,
      0.14648006257531068, 0.14596565577762652, 0.14544917448487973,
      0.1449306260374093, 0.14441001780493812, 0.14388735718646337,
      0.14336265161014583, 0.1428359085332149, 0.14230713544185769,
      0.14177633985110602, 0.1412435293047426, 0.14070871137518648,
      0.14017189366338023, 0.13963308379869355, 0.1390922894388098,
      0.13854951826960957, 0.13800477800507466, 0.13745807638717175,
      0.13690942118573743, 0.13635882019837831, 0.13580628125035504,
      0.13525181219446544, 0.13469542091094394, 0.13413711530734415,
      0.13357690331842073, 0.13301479290603013, 0.13245079205900126,
      0.13188490879303644, 0.13131715115059214, 0.13074752720075661,
      0.13017604503914923, 0.12960271278779836, 0.12902753859502061,
      0.12845053063531817, 0.12787169710924759, 0.12729104624331639,
      0.12670858628986059, 0.12612432552692157, 0.12553827225813993,
      0.12495043481263211, 0.12436082154486466, 0.12376944083454998,
      0.12317630108651896, 0.1225814107305959, 0.12198477822149144,
      0.12138641203867705, 0.12078632068625589, 0.12018451269285657,
      0.11958099661150486, 0.11897578101949612, 0.11836887451828558,
      0.11776028573336, 0.11715002331410912, 0.11653809593371477,
      0.11592451228902151, 0.11530928110040709, 0.11469241111167053,
      0.11407391108990213, 0.11345378982535133, 0.11283205613131682,
      0.11220871884401269, 0.11158378682243685, 0.11095726894825864,
      0.11032917412568687, 0.10969951128133418, 0.10906828936410572,
      0.10843551734506425, 0.10780120421729662, 0.10716535899579856,
      0.10652799071734015, 0.10588910844033128, 0.10524872124470537,
      0.10460683823178407, 0.10396346852414161, 0.10331862126548773,
      0.10267230562053178, 0.10202453077484455, 0.10137530593474345,
      0.1007246403271527, 0.10007254319946593, 0.099419023819428867,
      0.098764091475001592, 0.098107755474217129, 0.097450025145065344,
      0.096790909835352268, 0.096130418912561078, 0.09546856176373196,
      0.094805347795322181, 0.094140786433065893, 0.093474887121855477,
      0.092807659325589709, 0.092139112527054659, 0.091469256227782736,
      0.090798099947909272, 0.090125653226053787, 0.0894519256191749,
      0.0887769267024281, 0.0881006660690469, 0.087423153330187339,
      0.086744398114807331, 0.086064410069523187, 0.085383198858465681,
      0.084700774163156217, 0.084017145682362557, 0.083332323131954086,
      0.082646316244777362, 0.081959134770511352, 0.081270788475520342,
      0.0805812871427321, 0.079890640571489077, 0.079198858577402553,
      0.078505950992228235, 0.077811927663719915, 0.077116798455479751,
      0.0764205732468351, 0.075723261932689578, 0.075024874423375854,
      0.0743254206445286, 0.07362491053693658, 0.072923354056394413,
      0.072220761173574857, 0.071517141873880308, 0.070812506157293842,
      0.070106864038251032, 0.069400225545490968, 0.068692600721905153,
      0.06798399962441197, 0.067274432323803854, 0.066563908904597444,
      0.065852439464905585, 0.065140034116287229, 0.064426702983593584,
      0.0637124562048417, 0.062997303931061635, 0.062281256326145486,
      0.061564323566717052, 0.060846515841980142, 0.060127843353566669,
      0.059408316315405843, 0.058687944953571929, 0.057966739506131772,
      0.057244710223013542, 0.056521867365854295, 0.055798221207845271,
      0.055073782033603559, 0.054348560139015782, 0.053622565831084858,
      0.052895809427799312, 0.052168301257979721, 0.0514400516611217,
      0.050711070987269152, 0.049981369596846244, 0.049250957860527335,
      0.048519846159082392, 0.047788044883222178, 0.047055564433465077,
      0.046322415219982059, 0.045588607662441438, 0.044854152189878066,
      0.044119059240524415, 0.043383339261680837, 0.042647002709560212,
      0.04191006004912895, 0.041172521753976246, 0.040434398306156263,
      0.039695700196032156, 0.038956437922141623, 0.038216621991040367,
      0.037476262917145488, 0.036735371222600649, 0.035993957437119244,
      0.035252032097827395, 0.034509605749128876, 0.033766688942548272,
      0.03302329223657189, 0.032279426196515949, 0.031535101394365876,
      0.030790328408619078, 0.030045117824150681, 0.029299480232056141,
      0.028553426229490139, 0.027806966419534247, 0.027060111411037136,
      0.026312871818456707, 0.025565258261724056, 0.024817281366085145,
      0.024068951761942365, 0.023320280084718297, 0.02257127697469713,
      0.021821953076866046, 0.021072319040778723, 0.020322385520396974,
      0.019572163173930089, 0.01882166266370177, 0.01807089465598798,
      0.017319869820858275, 0.01656859883204044, 0.015817092366761706,
      0.015065361105586393, 0.014313415732282508, 0.013561266933660729,
      0.012808925399415406, 0.012056401821987531, 0.011303706896405341,
      0.010550851320124854, 0.009797845792892744, 0.0090447010165868157,
      0.0082914276950564643, 0.0075380365339854476, 0.0067845382407326392,
      0.006030943524170624, 0.0052772630945519582, 0.0045235076633463114,
      0.0037696879430811191, 0.003015814647208518, 0.0022618984899317714,
      0.0015079501860707587, 0.000753980450902233, 7.347880794884119E-17,
      -0.00075398045090208608, -0.0015079501860706117, -0.0022618984899316244,
      -0.0030158146472055291, -0.0037696879430809717, -0.0045235076633461649,
      -0.0052772630945518116, -0.0060309435241704765, -0.0067845382407324926,
      -0.0075380365339853, -0.0082914276950563186, -0.0090447010165866683,
      -0.0097978457928925965, -0.010550851320124708, -0.011303706896405193,
      -0.012056401821987384, -0.012808925399415258, -0.013561266933660582,
      -0.014313415732282363, -0.015065361105586246, -0.01581709236676156,
      -0.016568598832040295, -0.01731986982085813, -0.018070894655987834,
      -0.018821662663701624, -0.019572163173929943, -0.020322385520396828,
      -0.021072319040778581, -0.021821953076865897, -0.022571276974696984,
      -0.023320280084718148, -0.024068951761942219, -0.024817281366084996,
      -0.025565258261723914, -0.026312871818456565, -0.027060111411036987,
      -0.027806966419534104, -0.028553426229489989, -0.029299480232055992,
      -0.030045117824150536, -0.030790328408618936, -0.031535101394365737,
      -0.032279426196515804, -0.033023292236571744, -0.033766688942548126,
      -0.03450960574912873, -0.035252032097827256, -0.0359939574371191,
      -0.0367353712226005, -0.037476262917145342, -0.038216621991040228,
      -0.038956437922141478, -0.03969570019603201, -0.040434398306156118,
      -0.0411725217539761, -0.041910060049128811, -0.042647002709557291,
      -0.043383339261680691, -0.044119059240524269, -0.044854152189875152,
      -0.045588607662441293, -0.046322415219981913, -0.047055564433464939,
      -0.047788044883222032, -0.048519846159079838, -0.049250957860527196,
      -0.0499813695968461, -0.0507110709872666, -0.051440051661121561,
      -0.052168301257979582, -0.052895809427799173, -0.053622565831084726,
      -0.054348560139015636, -0.055073782033603427, -0.055798221207845139,
      -0.056521867365854163, -0.0572447102230134, -0.057966739506131626,
      -0.0586879449535718, -0.059408316315405711, -0.060127843353566537,
      -0.06084651584198, -0.061564323566716907, -0.06228125632614534,
      -0.0629973039310615, -0.063712456204841547, -0.064426702983593445,
      -0.065140034116287091, -0.065852439464905446, -0.0665639089045973,
      -0.067274432323803715, -0.067983999624411831, -0.068692600721905014,
      -0.069400225545490843, -0.07010686403825088, -0.070812506157293717,
      -0.071517141873880183, -0.072220761173574718, -0.07292335405639426,
      -0.073624910536936455, -0.074325420644528448, -0.0750248744233757,
      -0.07572326193268944, -0.076420573246834975, -0.077116798455479613,
      -0.077811927663719763, -0.078505950992228082, -0.079198858577402415,
      -0.079890640571488925, -0.08058128714273198, -0.081270788475520217,
      -0.081959134770511213, -0.082646316244777238, -0.083332323131953948,
      -0.084017145682362418, -0.084700774163156078, -0.085383198858465542,
      -0.086064410069523048, -0.0867443981148072, -0.0874231533301872,
      -0.088100666069044542, -0.088776926702427969, -0.089451925619174755,
      -0.090125653226053648, -0.090798099947909133, -0.0914692562277826,
      -0.092139112527054534, -0.09280765932558957, -0.093474887121853145,
      -0.094140786433065782, -0.094805347795322042, -0.095468561763731821,
      -0.096130418912560966, -0.096790909835352157, -0.097450025145065219,
      -0.098107755474217, -0.098764091475001453, -0.099419023819428742,
      -0.10007254319946579, -0.10072464032715256, -0.10137530593474331,
      -0.10202453077484441, -0.10267230562053165, -0.10331862126548762,
      -0.1039634685241415, -0.10460683823178396, -0.10524872124470525,
      -0.10588910844033116, -0.10652799071734001, -0.10716535899579843,
      -0.10780120421729651, -0.10843551734506413, -0.10906828936410561,
      -0.10969951128133404, -0.11032917412568675, -0.11095726894825853,
      -0.11158378682243673, -0.11220871884401257, -0.11283205613131671,
      -0.1134537898253512, -0.11407391108990202, -0.11469241111167039,
      -0.11530928110040697, -0.1159245122890214, -0.11653809593371463,
      -0.11715002331410901, -0.11776028573335987, -0.11836887451828544,
      -0.118975781019496, -0.11958099661150473, -0.12018451269285646,
      -0.12078632068625575, -0.12138641203867694, -0.12198477822149133,
      -0.12258141073059577, -0.12317630108651885, -0.12376944083454987,
      -0.12436082154486455, -0.124950434812632, -0.12553827225813982,
      -0.12612432552692146, -0.12670858628985857, -0.12729104624331627,
      -0.12787169710924748, -0.12845053063531617, -0.1290275385950205,
      -0.12960271278779825, -0.13017604503914912, -0.13074752720075652,
      -0.13131715115058987, -0.13188490879303633, -0.13245079205900115,
      -0.13301479290602791, -0.13357690331842062, -0.13413711530734404,
      -0.13469542091094386, -0.13525181219446533, -0.13580628125035493,
      -0.13635882019837819, -0.13690942118573732, -0.13745807638717164,
      -0.13800477800507455, -0.13854951826960948, -0.13909228943880972,
      -0.13963308379869344, -0.14017189366338015, -0.14070871137518637,
      -0.14124352930474249, -0.14177633985110591, -0.14230713544185758,
      -0.14283590853321479, -0.14336265161014572, -0.14388735718646326,
      -0.14441001780493803, -0.14493062603740919, -0.14544917448487965,
      -0.14596565577762641, -0.14648006257531057, -0.14699238756707111,
      -0.14750262347163423, -0.14801076303742167, -0.14851679904264373,
      -0.14902072429540678, -0.14952253163382154, -0.15002221392609263,
      -0.150519764070627, -0.15101517499613951, -0.15150843966174268,
      -0.15199955105705143, -0.15248850220228968, -0.15297528614837752,
      -0.15345989597703602, -0.15394232480088998, -0.15442256576355637,
      -0.15490061203974648, -0.1553764568353678, -0.15585009338761086,
      -0.15632151496505031, -0.15679071486774518, -0.15725768642732468,
      -0.15772242300708761, -0.1581849180021021, -0.15864516483928845,
      -0.15910315697751878, -0.15955888790771453, -0.16001235115292714,
      -0.1604635402684432, -0.16091244884186512, -0.16135907049320697,
      -0.16180339887498946, -0.16224542767232122, -0.16268515060299321,
      -0.16312256141757212, -0.16355765389947902, -0.16399042186509008,
      -0.1644208591638126, -0.16484895967817834, -0.16527471732393462,
      -0.16569812605012146, -0.16611917983916163, -0.16653787270695222,
      -0.16695419870293918, -0.16736815191020718, -0.16777972644556763,
      -0.16818891645963396, -0.16859571613690905, -0.16900011969587159,
      -0.16940212138905064, -0.16980171550311091, -0.17019889635893823,
      -0.17059365831171211, -0.17098599575098994, -0.1713759031007914,
      -0.17176337481966814, -0.1721484054007881, -0.17253098937201738,
      -0.17291112129598957, -0.17328879577018685, -0.17366400742702204,
      -0.17403675093390547, -0.17440702099332561, -0.17477481234292783,
      -0.17514011975558166, -0.175502938039459, -0.17586326203811128,
      -0.17622108663053576, -0.17657640673125174, -0.17692921729037642,
      -0.17727951329368963, -0.1776272897627085, -0.17797254175476238,
      -0.17831526436305456, -0.17865545271673711, -0.17899310198098303,
      -0.1793282073570478, -0.17966076408234066, -0.17999076743049711,
      -0.18031821271143783, -0.18064309527143954, -0.18096541049320411,
      -0.18128515379591761, -0.181602320635319, -0.18191690650376754,
      -0.18222890693030058, -0.18253831748070048, -0.18284513375756051,
      -0.18314935140033997, -0.18345096608543515, -0.18374997352623268,
      -0.18404636947317365, -0.18434014971381787, -0.18463131007289679,
      -0.18491984641237622, -0.185205754631518, -0.18548903066693165,
      -0.18576967049263948, -0.18604767012012746, -0.18632302559840463,
      -0.18659573301406196, -0.18686578849132249, -0.18713318819209915,
      -0.18739792831605243, -0.18766000510063791, -0.18791941482116351,
      -0.18817615379084485, -0.18843021836085205, -0.18868160492036395,
      -0.18893030989662318, -0.18917632975498053, -0.18941966099894844,
      -0.18966030017025293, -0.18989824384887793, -0.1901334886531163,
      -0.19036603123962018, -0.19059586830344394, -0.1908229965780934,
      -0.1910474128355745, -0.19126911388643475, -0.19148809657981067,
      -0.19170435780347517, -0.19191789448387658, -0.19212870358618531,
      -0.19233678211433897, -0.1925421271110804, -0.19274473565800168,
      -0.19294460487558857, -0.19314173192325623, -0.19333611399939238,
      -0.19352774834139874, -0.19371663222572647, -0.19390276296791686,
      -0.19408613792264129, -0.19426675448373515, -0.19444461008423672,
      -0.19461970219642541, -0.19479202833185413, -0.19496158604138644,
      -0.1951283729152333, -0.19529238658298329, -0.19545362471363859,
      -0.19561208501564964, -0.19576776523694436, -0.1959206631649614,
      -0.19607077662668404, -0.19621810348866708, -0.19636264165706926,
      -0.19650438907768422, -0.1966433437359669, -0.19677950365706354,
      -0.1969128669058412, -0.19704343158691204, -0.19717119584466375,
      -0.19729615786328303, -0.19741831586678252, -0.19753766811902757,
      -0.19765421292375793, -0.19776794862461355, -0.19787887360515924,
      -0.19798698628890471, -0.19809228513933014, -0.1981947686599054,
      -0.19829443539411251, -0.19839128392546723, -0.19848531287753718,
      -0.19857652091396258, -0.19866490673847589, -0.19875046909491861,
      -0.19883320676726, -0.19891311857961519, -0.19899020339626008,
      -0.19906446012164858, -0.19913588770042878, -0.19920448511745645,
      -0.19927025139781013, -0.19933318560680593, -0.19939328685000923,
      -0.19945055427324809, -0.19950498706262604, -0.19955658444453248,
      -0.19960534568565425, -0.1996512700929865, -0.19969435701384158,
      -0.19973460583585886, -0.19977201598701372, -0.199806586935625,
      -0.19983831819036285, -0.19986720930025617, -0.19989325985469819,
      -0.19991646948345282, -0.19993683785666, -0.19995436468483999,
      -0.19996904971889773, -0.19998089275012643, -0.19998989361021038,
      -0.19999605217122743, -0.19999936834565082, -0.19999984208635035,
      -0.19999747338659316, -0.19999226228004366, -0.19998420884076321,
      -0.1999733131832091, -0.19995957546223259, -0.19994299587307718,
      -0.19992357465137564, -0.19990131207314632, -0.19987620845478982,
      -0.19984826415308421, -0.19981747956517973, -0.19978385512859353,
      -0.19974739132120353, -0.19970808866124079, -0.19966594770728338,
      -0.19962096905824731, -0.1995731533533788, -0.19952250127224513,
      -0.19946901353472407, -0.19941269090099495, -0.19935353417152729,
      -0.19929154418706874, -0.19922672182863466, -0.19915906801749375,
      -0.19908858371515661, -0.19901526992336158, -0.1989391276840593,
      -0.1988601580793998, -0.19877836223171624, -0.19869374130350814,
      -0.19860629649742648, -0.19851602905625579, -0.19842294026289564,
      -0.19832703144034414, -0.19822830395167823, -0.19812675920003345,
      -0.19802239862858581, -0.19791522372053041, -0.19780523599905911,
      -0.19769243702734141, -0.19757682840850066, -0.19745841178559048,
      -0.1973371888415735, -0.1972131612992967, -0.197086330921465,
      -0.19695669951061928, -0.19682426890910923, -0.19668904099906598,
      -0.19655101770237793, -0.19641020098066203, -0.19626659283523473,
      -0.1961201953070861, -0.19597101047684953, -0.19581904046477075,
      -0.19566428743068048, -0.19550675357396247, -0.19534644113352029,
      -0.19518335238774925, -0.19501748965450205, -0.194848855291054,
      -0.19467745169407316, -0.19450328129958494, -0.19432634658293477,
      -0.19414665005875723, -0.19396419428093833, -0.19377898184257733,
      -0.19359101537595352, -0.19340029755248714, -0.19320683108269932,
      -0.19301061871617745, -0.19281166324153426, -0.19260996748636611,
      -0.1924055343172168, -0.19219836663953493, -0.19198846739763017,
      -0.19177583957463629, -0.191560486192466, -0.19134241031176596,
      -0.19112161503187869, -0.19089810349079239, -0.19067187886510151,
      -0.19044294436995948, -0.19021130325903077, -0.18997695882444898,
      -0.18973991439676807, -0.18950017334491254, -0.18925773907613502,
      -0.1890126150359612, -0.18876480470814741, -0.18851431161462776,
      -0.18826113931546171, -0.1880052914087888, -0.18774677153077537,
      -0.18748558335555907, -0.18722173059520295, -0.18695521699963963,
      -0.18668604635661551, -0.18641422249164211, -0.18613974926793914,
      -0.18586263058637684, -0.18558287038542598, -0.18530047264109925,
      -0.18501544136689174, -0.18472778061372974, -0.18443749446991042,
      -0.18414458706104009, -0.18384906254998268, -0.18355092513679674,
      -0.18325017905867252, -0.18294682858987849, -0.18264087804169771,
      -0.18233233176236227, -0.18202119413699888, -0.18170746958756298,
      -0.18139116257277277, -0.18107227758805206, -0.18075081916546346,
      -0.18042679187364055, -0.18010020031772947, -0.17977104913932021,
      -0.17943934301637743, -0.17910508666318042, -0.17876828483025317,
      -0.17842894230429251, -0.17808706390810844, -0.17774265450055085,
      -0.17739571897643724, -0.17704626226649042, -0.17669428933726547,
      -0.17633980519107395, -0.17598281486592157, -0.17562332343543222,
      -0.17526133600877253, -0.17489685773058627, -0.17452989378091771,
      -0.1741604493751345, -0.17378852976386058, -0.17341414023289811,
      -0.17303728610314859, -0.17265797273054603, -0.1722762055059702,
      -0.17189198985517962, -0.17150533123873105, -0.17111623515189614,
      -0.17072470712459303, -0.17033075272130294, -0.16993437754098734,
      -0.16953558721701756, -0.1691343874170842, -0.16873078384312579,
      -0.16832478223124381, -0.16791638835161715, -0.16750560800842826,
      -0.16709244703977655, -0.16667691131759063, -0.16625900674755487,
      -0.1658387392690196, -0.16541611485491281, -0.16499113951166428,
      -0.16456381927911634, -0.16413416023043195, -0.16370216847201885,
      -0.16326785014343759, -0.16283121141731008, -0.1623922584992406,
      -0.16195099762772316, -0.16150743507404863, -0.16106157714222408,
      -0.16061343016887919, -0.16016300052317142, -0.15971029460670458,
      -0.1592553188534335, -0.15879807972956711, -0.15833858373348755,
      -0.15787683739565161, -0.15741284727849333, -0.15694661997634082,
      -0.15647816211531826, -0.15600748035324502, -0.15553458137955259,
      -0.15505947191518368, -0.15458215871249237, -0.15410264855515729,
      -0.15362094825808081, -0.15313706466728719, -0.15265100465983497,
      -0.15216277514371435, -0.15167238305774416, -0.15117983537148316,
      -0.15068513908512599, -0.15018830122939797, -0.14968932886546713,
      -0.14918822908483684, -0.14868500900924048, -0.14817967579055077,
      -0.14767223661067375, -0.14716269868143927, -0.14665106924451116,
      -0.14613735557127783, -0.14562156496274434, -0.14510370474943859,
      -0.14458378229130228, -0.14406180497758092, -0.143537780226731,
      -0.14301171548630065, -0.14248361823283609, -0.14195349597177018,
      -0.1414213562373097, -0.14088720659233991, -0.14035105462831216,
      -0.1398129079651283, -0.13927277425104742, -0.13873066116256161,
      -0.13818657640429965, -0.13764052770891208, -0.13709252283695592,
      -0.1365425695767952, -0.13599067574448492, -0.1354368491836544,
      -0.1348810977654068, -0.13432342938820205, -0.13376385197773769,
      -0.13320237348685002, -0.13263900189539302, -0.13207374521011986,
      -0.13150661146458106, -0.13093760871900514, -0.13036674506017615,
      -0.12979402860133232, -0.12921946748204421, -0.12864306986809332,
      -0.1280648439513675, -0.12748479794973877, -0.12690294010694103,
      -0.12631927869246404, -0.12573382200143038, -0.12514657835447163,
      -0.12455755609762187, -0.12396676360219337, -0.12337420926465051,
      -0.12277990150650481, -0.12218384877418696, -0.1215860595389212,
      -0.12098654229661771, -0.12038530556774639, -0.11978235789720718,
      -0.11917770785422335, -0.11857136403221243, -0.11796333504865829,
      -0.11735362954500062, -0.11674225618650624, -0.11612922366213985,
      -0.11551454068445258, -0.11489821598945214, -0.11428025833647266,
      -0.11366067650806225, -0.1130394793098525, -0.11241667557042563,
      -0.1117922741412043, -0.111166283896317, -0.110538713732466,
      -0.10990957256881453, -0.10927886934685412, -0.10864661303026857,
      -0.10801281260482408, -0.10737747707822345, -0.10674061547999292,
      -0.10610223686134762, -0.10546235029505656, -0.10482096487532631,
      -0.10417808971766557, -0.10353373395874904, -0.10288790675630294,
      -0.10224061728895645, -0.10159187475612784, -0.10094168837788756,
      -0.10029006739481801, -0.099637021067898179, -0.098982558678364058,
      -0.098326689527570538, -0.0976694229368722, -0.0970107682474843,
      -0.096350734820343578, -0.0956893320359882, -0.09502656929441794,
      -0.094362456014954008, -0.093697001636118285, -0.093030215615493031,
      -0.092362107429578177, -0.091692686573673049, -0.091021962561731992,
      -0.090349944926222808, -0.089676643218005822, -0.089002067006191843,
      -0.0883262258779966, -0.087649129438621076, -0.086970787311106662,
      -0.08629120913619201, -0.085610404572189491, -0.084928383294841148,
      -0.084245154997174526, -0.0835607293893783, -0.082875116198657575,
      -0.082188325169088916, -0.0815003660614953, -0.080811248653301054,
      -0.0801209827383844, -0.079429578126955142, -0.078737044645405513,
      -0.078043392136164, -0.077348630457570441, -0.076652769483729413,
      -0.075955819104360112, -0.0752577892246727, -0.074558689765219219,
      -0.0738585306617458, -0.073157321865065447, -0.072455073340909559,
      -0.071751795069779509, -0.07104749704681855, -0.070342189281662845,
      -0.069635881798292332, -0.068928584634902063, -0.06822030784375302,
      -0.067511061491020485, -0.06680085565666842, -0.0660897004342961,
      -0.065377605930988028, -0.064664582267188353, -0.0639506395765369,
      -0.063235788005742019, -0.062520037714429141, -0.061803398874989583,
      -0.06108588167244984, -0.060367496304319979, -0.0596482529804415,
      -0.05892816192285915, -0.058207233365655024, -0.0574854775548231,
      -0.056762904748113435, -0.056039525214879572, -0.055315349235948288,
      -0.054590387103466621, -0.053864649120745359, -0.053138145602130406,
      -0.052410886872847284, -0.051682883268847526, -0.050954145136676177,
      -0.050224682833317574, -0.0494945067260409, -0.048763627192267296,
      -0.048032054619415156, -0.047299799404745255, -0.046566871955227455,
      -0.045833282687385915, -0.045099042027142065, -0.044364160409684383,
      -0.043628648279309755, -0.042892516089268057, -0.042155774301629562,
      -0.041418433387129354, -0.040680503825008006, -0.039941996102880795,
      -0.039202920716579576, -0.038463288169996668, -0.037723108974950167,
      -0.036982393651027276, -0.036241152725427432, -0.035499396732827385,
      -0.0347571362152241, -0.034014381721777655, -0.033271143808675921,
      -0.032527433038977614, -0.03178325998245303, -0.031038635215452026,
      -0.030293569320743244, -0.02954807288735662, -0.028802156510449102,
      -0.028055830791147009, -0.027309106336384833, -0.026561993758772762,
      -0.025814503676436729, -0.025066646712860453, -0.024318433496749229,
      -0.023569874661871503, -0.022820980846900322, -0.022071762695276942,
      -0.021322230855052172, -0.02057239597872761, -0.01982226872312191,
      -0.019071859749198127, -0.018321179721931292, -0.017570239310149765,
      -0.016819049186372996, -0.01606762002667823, -0.015315962510539603,
      -0.014564087320669257, -0.013812005142882881, -0.013059726665928,
      -0.012307262581349418, -0.011554623583329848, -0.010801820368530455,
      -0.010048863635953739, -0.0092957640867843833, -0.008542532424227936,
      -0.0077891793533771559, -0.0070357155810492136, -0.0062821518156264316,
      -0.0055284987669204175, -0.00477476714601276, -0.0040209676650921448,
      -0.0032671110373205751, -0.0025132079766718844, -0.0017592691977723592,
      -0.0010053054157633816, -0.0002513273461416843, 0.000502654295400403,
      0.0012566287931123248, 0.0020105854313450552, 0.002764513494710851,
      0.0035184022682206218, 0.004272241037443318, 0.0050260190886674411,
      0.0057797257090348372, 0.0065333501867036155, 0.0072868818110074758,
      0.0080403098725916038, 0.00879362366357198, 0.0095468124776982057,
      0.0102998656104872, 0.011052772359384582, 0.01180552202392385,
      0.012558103905863569, 0.013310507309346879, 0.014062721541060922,
      0.014814735910373961, 0.015566539729494736, 0.016318122313631816,
      0.017069472981130571, 0.017820581053632063, 0.018571435856234015,
      0.019322026717624126, 0.020072342970242345, 0.020822373950439545,
      0.021572108998612824, 0.022321537459364084, 0.023070648681662025,
      0.023819432018975198, 0.024567876829432473, 0.025315972475981347,
      0.026063708326524295, 0.026811073754077305, 0.027558058136928278,
      0.028304650858770753, 0.0290508413088745, 0.029796618882219045,
      0.0305419729796515, 0.031286893008046254, 0.032031368380437304,
      0.032775388516179269, 0.033518942841104717, 0.034262020787655591,
      0.035004611795054361, 0.035746705309436626, 0.036488290784008469,
      0.037229357679203705, 0.037969895462818926, 0.038709893610170631,
      0.039449341604252008, 0.040188228935867862, 0.0409265451037909,
      0.041664279614920023, 0.04240142198441136, 0.043137961735837754,
      0.043873888401344548, 0.044609191521782422, 0.045343860646862973,
      0.046077885335317627, 0.046811255155028021, 0.047543959683183284,
      0.048275988506435066, 0.049007331221031007, 0.0497379774329699,
      0.050467916758156608, 0.051197138822535175, 0.051925633262243531,
      0.052653389723767978, 0.05338039786407589, 0.054106647350769622,
      0.054832127862242223, 0.055556829087806361, 0.056280740727851088,
      0.057003852493995089, 0.057726154109217165, 0.05844763530800913,
      0.059168285836531942, 0.059888095452743706, 0.060607053926554105,
      0.061325151039976523, 0.062042376587259133, 0.062758720375036936,
      0.063474172222483818, 0.064188721961443, 0.064902359436578683,
      0.065615074505527407, 0.066326857039028089, 0.067037696921072726,
      0.067747584049058826, 0.068456508333915617, 0.069164459700257461,
      0.069871428086533738, 0.070577403445156478, 0.0712823757426498,
      0.071986334959802556, 0.0726892710917911, 0.073391174148341648,
      0.07409203415385579, 0.0747918411475592, 0.075490585183650066,
      0.076188256331426674, 0.076884844675435382, 0.077580340315618557,
      0.078274733367438731, 0.078968013962038841, 0.079660172246364749,
      0.0803511983833119, 0.08104108255187481, 0.0817298149472698,
      0.08241738578108275, 0.0831037852814147, 0.083789003693007125,
      0.084473031277387409, 0.085155858313013991, 0.085837475095401017,
      0.086517871937262972, 0.087197039168659174, 0.08787496713711769,
      0.088551646207778931, 0.089227066763540877, 0.089901219205179225,
      0.0905740939514933, 0.091245681439448625, 0.091915972124298209,
      0.092584956479724576, 0.09325262499798459, 0.093918968190028207,
      0.094583976585641535, 0.095247640733587616, 0.095909951201727725,
      0.09657089857716189, 0.09723047346636926, 0.097888666495328513,
      0.0985454683096576, 0.09920086957475327, 0.09985486097591062,
      0.10050743321846178, 0.10115857702791593, 0.10180828315007517,
      0.10245654235117525, 0.10310334541802285, 0.10374868315811255,
      0.10439254639976359, 0.10503492599225926, 0.10567581280596122,
      0.10631519773244712, 0.10695307168464607, 0.10758942559695522,
      0.10822425042537479, 0.10885753714764293, 0.10948927676335148,
      0.11011946029408004, 0.11074807878352991, 0.1113751232976388,
      0.11200058492471383, 0.11262445477556587, 0.1132467239836204,
      0.11386738370505256, 0.11448642511891859, 0.11510383942726531,
      0.11571961785527284, 0.11633375165136467, 0.11694623208733812,
      0.11755705045849454, 0.1181661980837508, 0.11877366630576876,
      0.1193794464910844, 0.11998353003021833, 0.12058590833780439,
      0.12118657285271742, 0.12178551503818308, 0.12238272638190489,
      0.12297819839619256, 0.12357192261806559, 0.12416389060939335,
      0.12475409395699813, 0.125342524272782, 0.12592917319385152,
      0.1265140323826251, 0.12709709352695711, 0.1276783483402619,
      0.12825778856162012, 0.12883540595590168, 0.12941119231388862,
      0.12998513945238044, 0.1305572392143157, 0.131127483468895,
      0.13169586411168252, 0.1322623730647294, 0.13282700227669375,
      0.13338974372294271, 0.13395058940567206, 0.13450953135402777,
      0.13506656162420536, 0.13562167229956987, 0.13617485549077357,
      0.13672610333585697, 0.13727540800036619, 0.13782276167746974,
      0.1383681565880584, 0.13891158498086151, 0.1394530391325623,
      0.13999251134789698, 0.1405299939597692, 0.14106547932936564,
      0.1415989598462514, 0.14213042792848568, 0.14265987602273464,
      0.14318729660436716, 0.14371268217756691, 0.14423602527544607,
      0.14475731846013887, 0.14527655432291353, 0.14579372548428257,
      0.14630882459409561, 0.14682184433165749, 0.14733277740582049,
      0.14784161655509298, 0.14834835454774772, 0.14885298418191445,
      0.1493554982856872, 0.14985588971723202, 0.15035415136487737,
      0.15085027614722002, 0.15134425701323262, 0.15183608694235171,
      0.15232575894458378, 0.15281326606060897, 0.15329860136187046,
      0.15378175795067775, 0.15426272896030943, 0.15474150755510119,
      0.15521808693054787, 0.15569246031340481, 0.1561646209617728,
      0.15663456216520774, 0.15710227724480264, 0.15756775955328939,
      0.1580310024751376, 0.15849199942663839, 0.1589507438560025,
      0.15940722924345985, 0.15986144910134087, 0.16031339697417452,
      0.1607630664387841, 0.16121045110436968, 0.1616555446126034,
      0.16209834063772424, 0.16253883288661911, 0.16297701509891663,
      0.16341288104708054, 0.16384642453648951, 0.16427763940552928,
      0.16470651952568546, 0.16513305880162024, 0.16555725117126496,
      0.16597909060591026, 0.16639857111028267, 0.16681568672263369,
      0.16723043151483055, 0.16764279959243017, 0.16805278509476795,
      0.16846038219504522, 0.1688655851004035, 0.16926838805201133,
      0.16966878532514978, 0.170066771229286, 0.17046234010815808,
      0.1708554863398592, 0.17124620433690993, 0.17163448854634117,
      0.17202033344977796, 0.17240373356350833, 0.17278468343856676,
      0.17316317766081513, 0.17353921085101154, 0.17391277766489016,
      0.17428387279324276, 0.17465249096198343, 0.17501862693223458,
      0.17538227550039232, 0.17574343149820446, 0.17610208979284714,
      0.17645824528699097, 0.17681189291887686, 0.17716302766239145,
      0.17751164452713167, 0.17785773855847889, 0.17820130483767346,
      0.17854233848187689, 0.17888083464424465, 0.17921678851399972,
      0.17955019531649272, 0.17988105031327384, 0.18020934880216344,
      0.18053508611731223, 0.18085825762927085, 0.1811788587450589,
      0.1814968849082228, 0.18181233159890886, 0.18212519433392033,
      0.18243546866678409, 0.1827431501878175, 0.1830482345241837,
      0.18335071733995792, 0.1836505943361921, 0.18394786125096932,
      0.18424251385946736, 0.1845345479740228, 0.18482395944418328,
      0.18511074415677034, 0.18539489803594025, 0.18567641704323648,
      0.18595529717764989, 0.18623153447567828, 0.18650512501137728,
      0.18677606489641888, 0.1870443502801494, 0.18730997734963875,
      0.18757294232973737, 0.18783324148313288, 0.18809087111039693,
      0.18834582755004139, 0.18859810717857284, 0.1888477064105385,
      0.1890946216985796, 0.18933884953348537, 0.18958038644423669,
      0.1898192289980587, 0.19005537380047155, 0.19028881749533411,
      0.19051955676489396, 0.19074758832983696, 0.19097290894932895,
      0.1911955154210645, 0.19141540458131434, 0.19163257330496611,
      0.19184701850557068, 0.19205873713538879, 0.19226772618542828,
      0.19247398268549384, 0.19267750370422326, 0.19287828634913173,
      0.1930763277666547, 0.19327162514218463, 0.19346417570011287,
      0.19365397670387111, 0.19384102545596626, 0.19402531929802094,
      0.19420685561081294, 0.19438563181430879, 0.19456164536770237,
      0.1947348937694526, 0.19490537455731566, 0.19507308530838152,
      0.19523802363911058, 0.19540018720536323, 0.19555957370243576,
      0.19571618086509443, 0.19587000646760366, 0.19602104832376224,
      0.1961693042869305, 0.19631477225006255, 0.19645745014573765,
      0.19659733594618653, 0.19673442766332194, 0.196868723348768,
      0.19700022109388529, 0.19712891902979934, 0.19725481532742861,
      0.19737790819750745, 0.19749819589061329, 0.19761567669719271,
      0.1977303489475829, 0.19784221101203694, 0.19795126130074814,
      0.19805749826387009, 0.19816092039154, 0.19826152621390128,
      0.19835931430112211, 0.19845428326341705, 0.19854643175106745,
      0.19863575845443915, 0.1987222621040016, 0.19880594147034705,
      0.1988867953642062, 0.19896482263646598, 0.19904002217818673,
      0.19911239292061611, 0.19918193383520552, 0.19924864393362512,
      0.19931252226777652, 0.1993735679298069, 0.19943178005212281,
      0.19948715780740087, 0.19953970040860039, 0.19958940710897513,
      0.19963627720208266, 0.19968031002179498, 0.19972150494230867,
      0.19975986137815249, 0.19979537878419651, 0.19982805665565997,
      0.19985789452811781, 0.199884891977508, 0.19990904862013692,
      0.19993036411268514, 0.19994883815221245, 0.19996447047616184,
      0.19997726086236325, 0.19998720912903717, 0.1999943151347966,
      0.19999857877864946, 0.2, 0.19999857877864946, 0.1999943151347966,
      0.19998720912903717, 0.19997726086236325, 0.19996447047616184,
      0.19994883815221245, 0.19993036411268514, 0.19990904862013692,
      0.199884891977508, 0.19985789452811792, 0.19982805665565997,
      0.19979537878419651, 0.19975986137815249, 0.19972150494230867,
      0.199680310021795, 0.19963627720208266, 0.19958940710897516,
      0.19953970040860042, 0.19948715780740087, 0.19943178005212281,
      0.19937356792980693, 0.19931252226777654, 0.19924864393362515,
      0.19918193383520555, 0.19911239292061614, 0.19904002217818673,
      0.19896482263646598, 0.19888679536420623, 0.19880594147034708,
      0.19872226210400162, 0.19863575845443918, 0.19854643175106751,
      0.19845428326341708, 0.19835931430112216, 0.19826152621390133,
      0.19816092039154004, 0.19805749826387009, 0.19795126130074817,
      0.19784221101203697, 0.19773034894758296, 0.19761567669719271,
      0.19749819589061335, 0.1973779081975075, 0.19725481532742867,
      0.1971289190297994, 0.19700022109388535, 0.19686872334876804,
      0.19673442766332197, 0.19659733594618656, 0.19645745014573768,
      0.19631477225006308, 0.19616930428693055, 0.1960210483237623,
      0.19587000646760422, 0.19571618086509446, 0.19555957370243582,
      0.19540018720536328, 0.19523802363911064, 0.19507308530838158,
      0.19490537455731571, 0.19473489376945263, 0.1945616453677024,
      0.19438563181430885, 0.19420685561081297, 0.194025319298021,
      0.19384102545596632, 0.19365397670387116, 0.19346417570011296,
      0.19327162514218468, 0.19307632776665473, 0.19287828634913251,
      0.19267750370422332, 0.1924739826854939, 0.19226772618542912,
      0.19205873713538885, 0.19184701850557073, 0.19163257330496619,
      0.19141540458131442, 0.19119551542106455, 0.190972908949329,
      0.19074758832983701, 0.19051955676489404, 0.19028881749533416,
      0.19005537380047161, 0.18981922899805875, 0.18958038644423678,
      0.18933884953348545, 0.18909462169857968, 0.18884770641053858,
      0.18859810717857295, 0.18834582755004148, 0.18809087111039702,
      0.18783324148313296, 0.18757294232973745, 0.18730997734963883,
      0.18704435028014946, 0.18677606489641896, 0.18650512501137734,
      0.18623153447567836, 0.18595529717764997, 0.18567641704323656,
      0.18539489803594034, 0.18511074415677042, 0.18482395944418339,
      0.18453454797402286, 0.18424251385946744, 0.1839478612509694,
      0.18365059433619219, 0.183350717339958, 0.18304823452418378,
      0.18274315018781762, 0.18243546866678417, 0.18212519433392044,
      0.18181233159890894, 0.18149688490822391, 0.181178858745059,
      0.18085825762927094, 0.18053508611731231, 0.18020934880216355,
      0.17988105031327395, 0.1795501953164928, 0.17921678851399983,
      0.17888083464424476, 0.178542338481877, 0.17820130483767355,
      0.177857738558479, 0.17751164452713178, 0.17716302766239156,
      0.17681189291887697, 0.17645824528699108, 0.17610208979284725,
      0.17574343149820457, 0.17538227550039243, 0.17501862693223469,
      0.17465249096198476, 0.17428387279324287, 0.17391277766489027,
      0.17353921085101162, 0.17316317766081524, 0.17278468343856687,
      0.17240373356350844, 0.17202033344977807, 0.17163448854634128,
      0.17124620433691004, 0.17085548633985931, 0.17046234010815819,
      0.17006677122928615, 0.1696687853251499, 0.16926838805201144,
      0.16886558510040361, 0.16846038219504533, 0.16805278509476809,
      0.16764279959243028, 0.16723043151483069, 0.1668156867226338,
      0.16639857111028278, 0.16597909060591037, 0.16555725117126507,
      0.16513305880162035, 0.1647065195256856, 0.16427763940552939,
      0.16384642453648965, 0.16341288104708068, 0.16297701509891677,
      0.16253883288661924, 0.16209834063772438, 0.16165554461260354,
      0.1612104511043698, 0.16076306643878421, 0.16031339697417463,
      0.159861449101341, 0.15940722924345996, 0.15895074385600264,
      0.15849199942663852, 0.15803100247513774, 0.15756775955329128,
      0.15710227724480275, 0.15663456216520788, 0.15616462096177472,
      0.15569246031340495, 0.155218086930548, 0.15474150755510133,
      0.15426272896030957, 0.15378175795067789, 0.1532986013618706,
      0.1528132660606091, 0.15232575894458389, 0.15183608694235184,
      0.15134425701323276, 0.15085027614722016, 0.15035415136487751,
      0.14985588971723215, 0.14935549828568734, 0.14885298418191459,
      0.14834835454774786, 0.14784161655509481, 0.14733277740582063,
      0.14682184433165765, 0.14630882459409744, 0.14579372548428274,
      0.1452765543229137, 0.14475731846013903, 0.14423602527544621,
      0.14371268217756702, 0.14318729660436733, 0.14265987602273481,
      0.14213042792848582, 0.14159895984625157, 0.14106547932936581,
      0.14052999395976937, 0.13999251134789711, 0.13945303913256243,
      0.13891158498086165, 0.13836815658805854, 0.13782276167746987,
      0.13727540800036639, 0.13672610333585714, 0.13617485549077374,
      0.13562167229957003, 0.13506656162420552, 0.13450953135402793,
      0.13395058940567225, 0.13338974372294285, 0.13282700227669392,
      0.1322623730647296, 0.13169586411168269, 0.13112748346889513,
      0.13055723921431583, 0.1299851394523806, 0.12941119231388878,
      0.12883540595590182, 0.12825778856162029, 0.12767834834026209,
      0.12709709352695728, 0.12651403238262526, 0.12592917319385172,
      0.12534252427278217, 0.12475409395699831, 0.12416389060939353,
      0.123571922618068, 0.12297819839619273, 0.12238272638190506,
      0.12178551503818323, 0.12118657285271757, 0.12058590833780457,
      0.11998353003021851, 0.11937944649108456, 0.11877366630576894,
      0.11816619808375098, 0.11755705045849472, 0.1169462320873383,
      0.11633375165136484, 0.11571961785527302, 0.11510383942726549,
      0.11448642511891877, 0.11386738370505277, 0.11324672398361824,
      0.11262445477556604, 0.11200058492471401, 0.11137512329763898,
      0.11074807878353009, 0.11011946029408025, 0.10948927676335166,
      0.10885753714764312, 0.10822425042537497, 0.10758942559695542,
      0.10695307168464628, 0.1063151977324473, 0.10567581280596139,
      0.10503492599225944, 0.10439254639976377, 0.10374868315811273,
      0.10310334541802302, 0.10245654235117543, 0.10180828315007538,
      0.10115857702791614, 0.10050743321846196, 0.099854860975910814,
      0.09920086957475345, 0.0985454683096578, 0.0978886664953287,
      0.097230473466369455, 0.096570898577162084, 0.095909951201727919,
      0.095247640733587824, 0.094583976585641716, 0.093918968190028415,
      0.0932526249979848, 0.09258495647972477, 0.0919159721242984,
      0.09124568143944882, 0.0905740939514935, 0.08990121920517942,
      0.089227066763541085, 0.088551646207779125, 0.0878749671371179,
      0.087197039168659382, 0.086517871937263166, 0.085837475095401211,
      0.0851558583130142, 0.084473031277389865, 0.083789003693007319,
      0.083103785281414891, 0.08241738578108522, 0.08172981494727001,
      0.081041082551875018, 0.0803511983833147, 0.079660172246364958,
      0.078968013962039049, 0.078274733367441562, 0.077580340315618765,
      0.0768848446754356, 0.076188256331426868, 0.075490585183650274,
      0.0747918411475594, 0.074092034153856, 0.073391174148341842,
      0.0726892710917913, 0.071986334959802764, 0.071282375742649992,
      0.070577403445156672, 0.069871428086533946, 0.069164459700257669,
      0.068456508333915811, 0.067747584049059034, 0.06703769692107292,
      0.0663268570390283, 0.065615074505527615, 0.064902359436578891,
      0.064188721961443207, 0.063474172222484027, 0.062758720375037144,
      0.062042376587259342, 0.061325151039976739, 0.060607053926554313,
      0.059888095452743921, 0.059168285836532157, 0.058447635308009338,
      0.05772615410921738, 0.057003852493995304, 0.0562807407278513,
      0.05555682908780657, 0.054832127862242432, 0.054106647350769838,
      0.053380397864076105, 0.052653389723768186, 0.051925633262243746,
      0.051197138822535383, 0.050467916758156817, 0.049737977432970114,
      0.049007331221031215, 0.048275988506435275, 0.047543959683183507,
      0.046811255155028236, 0.046077885335317842, 0.045343860646863188,
      0.044609191521782637, 0.043873888401344763, 0.043137961735837969,
      0.042401421984411575, 0.041664279614920238, 0.040926545103791123,
      0.040188228935868077, 0.039449341604252224, 0.038709893610173282,
      0.037969895462819148, 0.03722935767920392, 0.036488290784011133,
      0.035746705309436841, 0.035004611795054576, 0.034262020787658262,
      0.033518942841104939, 0.032775388516179484, 0.032031368380437526,
      0.031286893008046469, 0.030541972979651718, 0.029796618882219267,
      0.029050841308874715, 0.028304650858770972, 0.027558058136928493,
      0.02681107375407752, 0.026063708326522047, 0.025315972475981566,
      0.024567876829432692, 0.02381943201897542, 0.023070648681662243,
      0.022321537459364302, 0.021572108998613046, 0.020822373950439763,
      0.020072342970242563, 0.019322026717624344, 0.018571435856234234,
      0.017820581053632281, 0.01706947298113079, 0.016318122313632038,
      0.015566539729494955, 0.014814735910374181, 0.014062721541061144,
      0.013310507309347097, 0.012558103905863791, 0.01180552202392407,
      0.011052772359384802, 0.010299865610487423, 0.009546812477698426,
      0.0087936236635722028, 0.0080403098725918259, 0.007286881811007697,
      0.0065333501867038367, 0.0057797257090350584, 0.0050260190886676605,
      0.0042722410374435383, 0.0035184022682208426, 0.0027645134947110717,
      0.0020105854313452755, 0.0012566287931125451, 0.0005026542954006234,
      -0.00025132734614146388, -0.0010053054157631613, -0.0017592691977721384,
      -0.0025132079766716636, -0.0032671110373203548, -0.0040209676650919245,
      -0.00477476714601254, -0.0055284987669201972, -0.0062821518156262112,
      -0.0070357155810461527, -0.0077891793533769356, -0.0085425324242277157,
      -0.0092957640867813232, -0.010048863635953519, -0.010801820368530236,
      -0.011554623583327144, -0.012307262581349197, -0.013059726665927777,
      -0.01381200514288018, -0.014564087320669036, -0.015315962510539384,
      -0.016067620026678008, -0.016819049186372774, -0.017570239310149546,
      -0.018321179721931074, -0.019071859749197909, -0.019822268723121688,
      -0.020572395978727391, -0.021322230855051954, -0.022071762695276723,
      -0.022820980846900103, -0.023569874661871285, -0.02431843349674901,
      -0.025066646712860238, -0.025814503676436514, -0.026561993758772547,
      -0.027309106336384614, -0.028055830791146791, -0.028802156510448887,
      -0.029548072887356405, -0.030293569320743022, -0.031038635215451811,
      -0.031783259982452815, -0.0325274330389774, -0.033271143808675706,
      -0.034014381721777433, -0.034757136215223881, -0.03549939673282717,
      -0.036241152725427217, -0.036982393651027061, -0.037723108974949952,
      -0.038463288169996446, -0.039202920716579354, -0.039941996102880573,
      -0.040680503825007791, -0.041418433387129139, -0.042155774301629353,
      -0.042892516089267835, -0.04362864827930954, -0.044364160409684168,
      -0.04509904202714185, -0.0458332826873857, -0.04656687195522724,
      -0.04729979940474504, -0.048032054619414941, -0.048763627192267081,
      -0.049494506726040693, -0.050224682833317359, -0.050954145136675968,
      -0.051682883268847318, -0.052410886872847076, -0.0531381456021302,
      -0.053864649120745151, -0.054590387103463672, -0.05531534923594808,
      -0.056039525214879364, -0.056762904748110493, -0.057485477554822889,
      -0.058207233365654809, -0.058928161922856215, -0.059648252980441623,
      -0.06036749630431977, -0.061085881672449632, -0.061803398874989028,
      -0.062520037714428947, -0.0632357880057418, -0.063950639576536364,
      -0.064664582267188145, -0.06537760593098782, -0.066089700434295559,
      -0.066800855656670891, -0.067511061491020624, -0.068220307843752478,
      -0.068928584634901854, -0.069635881798292457, -0.070342189281662637,
      -0.071047497046818328, -0.071751795069779634, -0.072455073340909365,
      -0.073157321865065225, -0.073858530661745275, -0.074558689765219011,
      -0.075257789224672508, -0.07595581910435957, -0.076652769483729219,
      -0.077348630457570566, -0.078043392136163459, -0.078737044645405319,
      -0.079429578126955266, -0.0801209827383842, -0.08081124865330086,
      -0.081500366061495425, -0.082188325169088708, -0.0828751161986577,
      -0.083560729389377766, -0.084245154997174332, -0.084928383294841273,
      -0.085610404572188964, -0.086291209136191815, -0.086970787311106787,
      -0.087649129438620563, -0.0883262258779964, -0.089002067006191316,
      -0.089676643218005614, -0.090349944926222614, -0.091021962561731479,
      -0.091692686573672855, -0.0923621074295783, -0.093030215615492518,
      -0.0936970016361181, -0.094362456014954119, -0.095026569294417745,
      -0.095689332035988, -0.096350734820343689, -0.097010768247481616,
      -0.097669422936872, -0.098326689527570038, -0.0989825586783614,
      -0.099637021067897985, -0.10029006739481749, -0.10094168837788492,
      -0.10159187475612795, -0.10224061728895595, -0.10288790675630029,
      -0.10353373395874915, -0.10417808971766536, -0.10482096487532613,
      -0.10546235029505667, -0.10610223686134744, -0.10674061547999275,
      -0.10737747707822357, -0.1080128126048239, -0.10864661303026837,
      -0.10927886934685366, -0.10990957256881435, -0.11053871373246582,
      -0.11116628389631651, -0.11179227414120413, -0.11241667557042574,
      -0.11303947930985203, -0.11366067650806207, -0.11428025833647278,
      -0.11489821598945196, -0.1155145406844524, -0.11612922366213996,
      -0.11674225618650608, -0.11735362954500045, -0.11796333504865782,
      -0.11857136403221225, -0.11917770785422317, -0.1197823578972067,
      -0.12038530556774621, -0.12098654229661782, -0.12158605953892072,
      -0.12218384877418678, -0.12277990150650489, -0.12337420926465033,
      -0.12396676360219322, -0.12455755609762198, -0.12514657835447146,
      -0.12573382200143046, -0.12631927869246359, -0.12690294010694086,
      -0.12748479794973888, -0.12806484395136705, -0.12864306986809315,
      -0.12921946748204433, -0.12979402860133191, -0.13036674506017595,
      -0.1309376087190047, -0.13150661146458087, -0.13207374521011969,
      -0.13263900189539257, -0.13320237348684982, -0.1337638519777378,
      -0.1343234293882016, -0.13488109776540666, -0.13543684918365448,
      -0.13599067574448265, -0.13654256957679503, -0.137092522836956,
      -0.13764052770890986, -0.13818657640429952, -0.13873066116256122,
      -0.1392727742510452, -0.1398129079651281, -0.14035105462831174,
      -0.14088720659233975, -0.14142135623730953, -0.14195349597176976,
      -0.14248361823283592, -0.14301171548630073, -0.14353778022673083,
      -0.14406180497758075, -0.14458378229130237, -0.14510370474944015,
      -0.14562156496274417, -0.14613735557127791, -0.14665106924451074,
      -0.14716269868143914, -0.14767223661067336, -0.14817967579055064,
      -0.14868500900924034, -0.14918822908483648, -0.14968932886546696,
      -0.15018830122939805, -0.1506851390851256, -0.151179835371483,
      -0.15167238305774428, -0.15216277514371418, -0.15265100465983483,
      -0.15313706466728727, -0.15362094825808068, -0.15410264855515715,
      -0.15458215871249198, -0.15505947191518354, -0.15553458137955245,
      -0.15600748035324466, -0.15647816211531812, -0.15694661997634091,
      -0.15741284727849297, -0.1578768373956515, -0.15833858373348764,
      -0.15879807972956697, -0.15925531885343336, -0.15971029460670466,
      -0.16016300052317128, -0.16061343016887927, -0.16106157714222374,
      -0.16150743507404849, -0.16195099762772325, -0.16239225849924027,
      -0.16283121141730997, -0.16326785014343767, -0.16370216847201852,
      -0.16413416023043181, -0.164563819279116, -0.16499113951166416,
      -0.1654161148549127, -0.16583873926901926, -0.16625900674755473,
      -0.16667691131759069, -0.16709244703977505, -0.16750560800842815,
      -0.16791638835161726, -0.16832478223124214, -0.16873078384312568,
      -0.16913438741708428, -0.16953558721701595, -0.16993437754098722,
      -0.17033075272130263, -0.17072470712459273, -0.171116235151896,
      -0.17150533123873074, -0.17189198985517951, -0.17227620550597009,
      -0.17265797273054573, -0.17303728610314847, -0.17341414023289817,
      -0.17378852976386028, -0.17416044937513439, -0.17452989378091777,
      -0.17489685773058597, -0.17526133600877242, -0.1756233234354323,
      -0.17598281486592127, -0.17633980519107384, -0.17669428933726519,
      -0.17704626226649034, -0.17739571897643713, -0.1777426545005506,
      -0.17808706390810833, -0.17842894230429254, -0.17876828483025292,
      -0.17910508666318034, -0.17943934301637748, -0.1797710491393201,
      -0.18010020031772936, -0.18042679187364064, -0.18075081916546337,
      -0.18107227758805197, -0.18139116257277252, -0.1817074695875629,
      -0.1820211941369988, -0.18233233176236202, -0.18264087804169762,
      -0.18294682858987854, -0.18325017905867227, -0.18355092513679666,
      -0.18384906254998276, -0.18414458706103998, -0.18443749446991034,
      -0.1847277806137298, -0.18501544136689166, -0.18530047264109928,
      -0.18558287038542579, -0.18586263058637675, -0.18613974926793919,
      -0.18641422249164188, -0.18668604635661543, -0.18695521699963968,
      -0.18722173059520272, -0.18748558335555898, -0.18774677153077446,
      -0.18800529140878874, -0.18826113931546162, -0.18851431161462684,
      -0.18876480470814733, -0.18901261503596123, -0.18925773907613413,
      -0.18950017334491245, -0.18973991439676813, -0.18997695882444879,
      -0.19021130325903068, -0.19044294436995954, -0.19067187886510131,
      -0.19089810349079231, -0.19112161503187852, -0.1913424103117658,
      -0.19156048619246593, -0.19177583957463692, -0.19198846739763009,
      -0.19219836663953488, -0.19240553431721683, -0.19260996748636605,
      -0.19281166324153429, -0.19301061871617731, -0.19320683108269926,
      -0.19340029755248717, -0.19359101537595338, -0.19377898184257727,
      -0.19396419428093836, -0.19414665005875709, -0.19432634658293471,
      -0.19450328129958483, -0.19467745169407313, -0.19484885529105392,
      -0.19501748965450194, -0.1951833523877492, -0.19534644113352029,
      -0.19550675357396236, -0.19566428743068043, -0.19581904046477078,
      -0.19597101047684951, -0.19612019530708605, -0.19626659283523476,
      -0.19641020098066198, -0.19655101770237787, -0.19668904099906589,
      -0.1968242689091092, -0.19695669951061923, -0.19708633092146491,
      -0.19721316129929667, -0.19733718884157353, -0.1974584117855904,
      -0.19757682840850063, -0.19769243702734141, -0.19780523599905908,
      -0.19791522372053039, -0.19802239862858584, -0.19812675920003342,
      -0.19822830395167823, -0.19832703144034405, -0.19842294026289564,
      -0.19851602905625582, -0.19860629649742642, -0.19869374130350814,
      -0.19877836223171594, -0.19886015807939972, -0.19893912768405927,
      -0.1990152699233613, -0.19908858371515659, -0.19915906801749372,
      -0.19922672182863443, -0.19929154418706874, -0.19935353417152729,
      -0.19941269090099498, -0.19946901353472404, -0.19952250127224513,
      -0.19957315335337877, -0.19962096905824728, -0.19966594770728341,
      -0.19970808866124076, -0.19974739132120353, -0.19978385512859356,
      -0.1998174795651797, -0.19984826415308421, -0.19987620845478982,
      -0.19990131207314629, -0.19992357465137564, -0.19994299587307718,
      -0.19995957546223259, -0.1999733131832091, -0.19998420884076321,
      -0.19999226228004366, -0.19999747338659316, -0.19999984208635035,
      -0.19999936834565082, -0.19999605217122743, -0.19998989361021038,
      -0.19998089275012643, -0.19996904971889773, -0.19995436468483999,
      -0.19993683785666, -0.19991646948345285, -0.19989325985469822,
      -0.19986720930025617, -0.19983831819036288, -0.199806586935625,
      -0.19977201598701372, -0.19973460583585889, -0.19969435701384161,
      -0.1996512700929865, -0.19960534568565427, -0.1995565844445325,
      -0.19950498706262609, -0.19945055427324809, -0.19939328685000923,
      -0.199333185606806, -0.19927025139781016, -0.19920448511745645,
      -0.19913588770042884, -0.19906446012164858, -0.19899020339626006,
      -0.19891311857961522, -0.19883320676726002, -0.19875046909491861,
      -0.19866490673847592, -0.19857652091396288, -0.19848531287753726,
      -0.19839128392546723, -0.19829443539411287, -0.19819476865990548,
      -0.19809228513933017, -0.1979869862889051, -0.19787887360515932,
      -0.19776794862461355, -0.1976542129237579, -0.19753766811902762,
      -0.19741831586678255, -0.197296157863283, -0.1971711958446638,
      -0.197043431586912, -0.1969128669058412, -0.19677950365706359,
      -0.19664334373596642, -0.19650438907768433, -0.19636264165706929,
      -0.19621810348866711, -0.19607077662668415, -0.19592066316496146,
      -0.19576776523694434, -0.19561208501564978, -0.19545362471363861,
      -0.19529238658298326, -0.19512837291523333, -0.19496158604138647,
      -0.19479202833185408, -0.19461970219642544, -0.19444461008423669,
      -0.19426675448373529, -0.19408613792264134, -0.19390276296791681,
      -0.1937166322257266, -0.1935277483413988, -0.19333611399939235,
      -0.19314173192325637, -0.19294460487558862, -0.19274473565800185,
      -0.19254212711108046, -0.19233678211433902, -0.19212870358618547,
      -0.19191789448387664, -0.19170435780347514, -0.19148809657981081,
      -0.19126911388643483, -0.19104741283557447, -0.19082299657809346,
      -0.190595868303444, -0.19036603123962015, -0.19013348865311636,
      -0.189898243848878, -0.18966030017025312, -0.1894196609989485,
      -0.18917632975498058, -0.18893030989662338, -0.188681604920364,
      -0.188430218360852, -0.18817615379084504, -0.18791941482116359,
      -0.18766000510063785, -0.18739792831605251, -0.18713318819210023,
      -0.18686578849132243, -0.18659573301406202, -0.18632302559840561,
      -0.18604767012012768, -0.18576967049263957, -0.18548903066693265,
      -0.18520575463151823, -0.18491984641237627, -0.18463131007289685,
      -0.1843401497138181, -0.18404636947317374, -0.18374997352623265,
      -0.18345096608543537, -0.18314935140034005, -0.18284513375756045,
      -0.1825383174807006, -0.18222890693030069, -0.18191690650376746,
      -0.18160232063531911, -0.1812851537959177, -0.18096541049320436,
      -0.18064309527143965, -0.18031821271143791, -0.17999076743049736,
      -0.17966076408234075, -0.17932820735704771, -0.17899310198098328,
      -0.17865545271673722, -0.1783152643630545, -0.17797254175476249,
      -0.17762728976270861, -0.17727951329368957, -0.17692921729037653,
      -0.17657640673125166, -0.17622108663053604, -0.1758632620381114,
      -0.17550293803945893, -0.17514011975558194, -0.17477481234292791,
      -0.17440702099332556, -0.17403675093390575, -0.17366400742702215,
      -0.17328879577018716, -0.17291112129598968, -0.1725309893720175,
      -0.17214840540078841, -0.17176337481966825, -0.17137590310079132,
      -0.17098599575099022, -0.17059365831171222, -0.17019889635893815,
      -0.16980171550311104, -0.16940212138905075, -0.16900011969587153,
      -0.16859571613690916, -0.16818891645963407, -0.16777972644556793,
      -0.16736815191020732, -0.16695419870293929, -0.16653787270695253,
      -0.16611917983916336, -0.16569812605012135, -0.16527471732393495,
      -0.16484895967818006, -0.16442085916381252, -0.16399042186509022,
      -0.16355765389948076, -0.16312256141757206, -0.16268515060299332,
      -0.16224542767232134, -0.16180339887498937, -0.16135907049320711,
      -0.16091244884186526, -0.16046354026844353, -0.16001235115292728,
      -0.15955888790771466, -0.15910315697751914, -0.15864516483928687,
      -0.15818491800210202, -0.15772242300708794, -0.15725768642732482,
      -0.1567907148677451, -0.15632151496505045, -0.155850093387611,
      -0.15537645683536772, -0.15490061203974662, -0.15442256576355651,
      -0.15394232480089035, -0.15345989597703616, -0.15297528614837769,
      -0.15248850220229004, -0.15199955105705154, -0.15150843966174257,
      -0.15101517499613989, -0.15051976407062717, -0.15002221392609255,
      -0.14952253163382168, -0.14902072429540691, -0.14851679904264364,
      -0.14801076303742183, -0.14750262347163415, -0.14699238756707153,
      -0.14648006257531074, -0.14596565577762632, -0.14544917448488,
      -0.14493062603740933, -0.14441001780493795, -0.14388735718646367,
      -0.14336265161014589, -0.14283590853321521, -0.14230713544185775,
      -0.14177633985110605, -0.1412435293047429, -0.14070871137518653,
      -0.14017189366338004, -0.13963308379869385, -0.13909228943880989,
      -0.13854951826960937, -0.13800477800507469, -0.13745807638717181,
      -0.13690942118573721, -0.13635882019837836, -0.13580628125035507,
      -0.13525181219446575, -0.13469542091094611, -0.13413711530734418,
      -0.13357690331842106, -0.13301479290603019, -0.13245079205900107,
      -0.13188490879303677, -0.13131715115059217, -0.13074752720075641,
      -0.13017604503914929, -0.12960271278779842, -0.12902753859502039,
      -0.12845053063531633, -0.12787169710924765, -0.12729104624331619,
      -0.12670858628985873, -0.12612432552692163, -0.12553827225814027,
      -0.12495043481263218, -0.12436082154486471, -0.12376944083455031,
      -0.12317630108651903, -0.12258141073059568, -0.12198477822149179,
      -0.12138641203867712, -0.12078632068625564, -0.12018451269285664,
      -0.1195809966115049, -0.11897578101949589, -0.11836887451828562,
      -0.11776028573336005, -0.11715002331410947, -0.11653809593371484,
      -0.11592451228902156, -0.11530928110040745, -0.1146924111116706,
      -0.11407391108990191, -0.11345378982535169, -0.11283205613131689,
      -0.11220871884401246, -0.11158378682243691, -0.11095726894825871,
      -0.11032917412568662, -0.10969951128133422, -0.10906828936410547,
      -0.10843551734506461, -0.10780120421729669, -0.10716535899579832,
      -0.1065279907173405, -0.10588910844033134, -0.10524872124470513,
      -0.10460683823178446, -0.10396346852414168, -0.1033186212654881,
      -0.10267230562053185, -0.10202453077484459, -0.10137530593474382,
      -0.10072464032715277, -0.10007254319946568, -0.099419023819429242,
      -0.098764091475001647, -0.098107755474216879, -0.0974500251450679,
      -0.096790909835352337, -0.096130418912560842, -0.095468561763734514,
      -0.094805347795322237, -0.094140786433066281, -0.093474887121855865,
      -0.092807659325589764, -0.092139112527055048, -0.091469256227782791,
      -0.090798099947909328, -0.090125653226054175, -0.089451925619174963,
      -0.088776926702427858, -0.088100666069044736, -0.087423153330187409,
      -0.086744398114807081, -0.086064410069521008, -0.085383198858465736,
      -0.084700774163155967, -0.084017145682362945, -0.083332323131954156,
      -0.082646316244777751, -0.081959134770511421, -0.081270788475520411,
      -0.0805812871427325, -0.079890640571489147, -0.07919885857740229,
      -0.078505950992228624, -0.077811927663719971, -0.077116798455479488,
      -0.076420573246835169, -0.075723261932689648, -0.075024874423375576,
      -0.07432542064452867, -0.07362491053693665, -0.072923354056394815,
      -0.072220761173574927, -0.071517141873880377, -0.070812506157294244,
      -0.0701068640382511, -0.0694002255454907, -0.068692600721905556,
      -0.067983999624412039, -0.06727443232380359, -0.0665639089045975,
      -0.06585243946490564, -0.065140034116286966, -0.064426702983593653,
      -0.063712456204841422, -0.062997303931062038, -0.062281256326145555,
      -0.061564323566716789, -0.060846515841980559, -0.060127843353566739,
      -0.059408316315405579, -0.058687944953572338, -0.057966739506131841,
      -0.057244710223013952, -0.056521867365854378, -0.055798221207845347,
      -0.055073782033603969, -0.054348560139015845, -0.053622565831084594,
      -0.052895809427801782, -0.052168301257979791, -0.051440051661121422,
      -0.050711070987269562, -0.04998136959684632, -0.049250957860527064,
      -0.048519846159082808, -0.047788044883222247, -0.047055564433465494,
      -0.046322415219982475, -0.0455886076624415, -0.044854152189875714,
      -0.044119059240524484, -0.043383339261680906, -0.042647002709557853,
      -0.041910060049129019, -0.041172521753975976, -0.04043439830615668,
      -0.039695700196032226, -0.038956437922141346, -0.038216621991040783,
      -0.037476262917145557, -0.036735371222600371, -0.03599395743711966,
      -0.035252032097827471, -0.0345096057491293, -0.033766688942548341,
      -0.033023292236571959, -0.032279426196516373, -0.031535101394365959,
      -0.0307903284086188, -0.030045117824151108, -0.029299480232056214,
      -0.028553426229489854, -0.027806966419534319, -0.027060111411037209,
      -0.026312871818456429, -0.025565258261724136, -0.024817281366085214,
      -0.024068951761942792, -0.02332028008471837, -0.022571276974697203,
      -0.02182195307686647, -0.0210723190407788, -0.020322385520396696,
      -0.019572163173930516, -0.018821662663701843, -0.0180708946559877,
      -0.017319869820858352, -0.016568598832040513, -0.015817092366761428,
      -0.015065361105586464, -0.014313415732282226, -0.013561266933661158,
      -0.012808925399415479, -0.01205640182198725, -0.011303706896405769,
      -0.010550851320124927, -0.0097978457928924612, -0.0090447010165872442,
      -0.0082914276950565372, -0.0075380365339880063, -0.006784538240732713,
      -0.0060309435241706968, -0.0052772630945545178, -0.0045235076633463852,
      -0.0037696879430808372, -0.0030158146472082361, -0.0022618984899318447,
      -0.0015079501860704768, -0.00075398045090266179, -1.4695761589768238E-16,
      0.00075398045090236787, 0.001507950186070183, 0.0022618984899315511,
      0.0030158146472079421, 0.0037696879430805436, 0.0045235076633460911,
      0.0052772630945542246, 0.0060309435241704028, 0.0067845382407324189,
      0.007538036533985582, 0.008291427695056244, 0.00904470101658695,
      0.0097978457928921681, 0.010550851320124635, 0.011303706896405474,
      0.012056401821986957, 0.012808925399415187, 0.013561266933660863,
      0.014313415732281934, 0.015065361105586171, 0.015817092366761133,
      0.016568598832040218, 0.017319869820858057, 0.018070894655987404,
      0.018821662663701551, 0.019572163173930224, 0.0203223855203964,
      0.021072319040778505, 0.021821953076866178, 0.022571276974696911,
      0.023320280084718079, 0.0240689517619425, 0.024817281366084923,
      0.025565258261723841, 0.026312871818456138, 0.027060111411036914,
      0.027806966419534031, 0.028553426229489566, 0.029299480232055919,
      0.030045117824150813, 0.030790328408618513, 0.031535101394365661,
      0.032279426196516081, 0.033023292236571675, 0.03376668894254805,
      0.034509605749129008, 0.03525203209782718, 0.035993957437119375,
      0.036735371222600087, 0.037476262917145273, 0.0382166219910405,
      0.038956437922141054, 0.039695700196031941, 0.040434398306153613,
      0.041172521753975684, 0.041910060049128735, 0.042647002709557569,
      0.043383339261680615, 0.0441190592405242, 0.044854152189875429,
      0.045588607662441216, 0.046322415219982191, 0.047055564433465209,
      0.047788044883221963, 0.048519846159082523, 0.04925095786052678,
      0.049981369596846029, 0.050711070987269284, 0.051440051661121138,
      0.0521683012579795, 0.052895809427799437, 0.053622565831084316,
      0.054348560139015567, 0.055073782033603691, 0.055798221207845056,
      0.056521867365854087, 0.057244710223013674, 0.057966739506131564,
      0.05868794495357206, 0.0594083163154053, 0.060127843353566461,
      0.060846515841980281, 0.0615643235667165, 0.062281256326145278,
      0.06299730393106176, 0.063712456204841145, 0.064426702983593362,
      0.065140034116286688, 0.065852439464905363, 0.066563908904597222,
      0.067274432323803313, 0.067983999624411762, 0.068692600721905278,
      0.069400225545490427, 0.070106864038250824, 0.070812506157293967,
      0.0715171418738801, 0.072220761173574649, 0.072923354056394538,
      0.073624910536936372, 0.074325420644528392, 0.075024874423375312,
      0.07572326193268937, 0.0764205732468349, 0.077116798455479224,
      0.0778119276637197, 0.078505950992228346, 0.079198858577402026,
      0.079890640571488869, 0.08058128714273223, 0.081270788475520148,
      0.081959134770511144, 0.082646316244777487, 0.083332323131953878,
      0.084017145682360087, 0.08470077416315569, 0.085383198858465473,
      0.086064410069520744, 0.086744398114806831, 0.087423153330187131,
      0.088100666069044473, 0.0887769267024276, 0.0894519256191747,
      0.090125653226053912, 0.090798099947909064, 0.091469256227782528,
      0.092139112527054784, 0.092807659325589514, 0.0934748871218556,
      0.094140786433066018, 0.094805347795321987, 0.09546856176373425,
      0.096130418912560578, 0.096790909835352087, 0.09745002514506515,
      0.098107755474216629, 0.098764091475001384, 0.099419023819428978,
      0.10007254319946542, 0.10072464032715252, 0.10137530593474356,
      0.10202453077484436, 0.1026723056205316, 0.10331862126548784,
      0.10396346852414143, 0.10460683823178418, 0.10524872124470488,
      0.10588910844033109, 0.10652799071734026, 0.10716535899579807,
      0.10780120421729644, 0.10843551734506436, 0.10906828936410523,
      0.10969951128133398, 0.11032917412568638, 0.11095726894825847,
      0.11158378682243666, 0.11220871884401223, 0.11283205613131664,
      0.11345378982535144, 0.11407391108990167, 0.11469241111167035,
      0.1153092811004072, 0.11592451228902133, 0.11653809593371459,
      0.11715002331410923, 0.11776028573335982, 0.1183688745182854,
      0.11897578101949564, 0.11958099661150468, 0.1201845126928564,
      0.12078632068625542, 0.12138641203867687, 0.12198477822149155,
      0.12258141073059543, 0.12317630108651881, 0.12376944083455009,
      0.12436082154486448, 0.12495043481262971, 0.12553827225814004,
      0.1261243255269214, 0.12670858628985851, 0.12729104624331597,
      0.12787169710924742, 0.12845053063531611, 0.12902753859502017,
      0.1296027127877982, 0.13017604503914906, 0.13074752720075619,
      0.13131715115059195, 0.13188490879303655, 0.13245079205900084,
      0.13301479290603, 0.13357690331842084, 0.13413711530734396,
      0.13469542091094378, 0.13525181219446553, 0.13580628125035485,
      0.13635882019837817, 0.13690942118573698, 0.13745807638717161,
      0.13800477800507449, 0.13854951826960918, 0.13909228943880966,
      0.13963308379869366, 0.14017189366337984, 0.14070871137518634,
      0.14124352930474268, 0.14177633985110585, 0.14230713544185755,
      0.142835908533215, 0.14336265161014566, 0.14388735718646348,
      0.14441001780493776, 0.14493062603740914, 0.14544917448487982,
      0.14596565577762613, 0.14648006257531052, 0.14699238756707131,
      0.14750262347163395, 0.14801076303742164, 0.14851679904264345,
      0.14902072429540672, 0.14952253163382148, 0.15002221392609236,
      0.15051976407062695, 0.1510151749961397, 0.15150843966174241,
      0.15199955105705137, 0.15248850220228985, 0.15297528614837749,
      0.15345989597703596, 0.15394232480089015, 0.15442256576355631,
      0.15490061203974645, 0.15537645683536752, 0.1558500933876108,
      0.15632151496505028, 0.1567907148677449, 0.15725768642732288,
      0.15772242300708778, 0.15818491800210185, 0.1586451648392867,
      0.15910315697751895, 0.15955888790771447, 0.16001235115292711,
      0.16046354026844334, 0.16091244884186506, 0.16135907049320694,
      0.16180339887498918, 0.1622454276723212, 0.16268515060299316,
      0.16312256141757187, 0.1635576538994806, 0.16399042186509005,
      0.16442085916381236, 0.16484895967817992, 0.16527471732393476,
      0.16569812605012121, 0.16611917983916158, 0.16653787270695239,
      0.16695419870293915, 0.16736815191020715, 0.1677797264455678,
      0.16818891645963394, 0.168595716136909, 0.16900011969587136,
      0.16940212138905059, 0.16980171550311088, 0.170198896358938,
      0.17059365831171205, 0.17098599575099008, 0.17137590310079118,
      0.17176337481966808, 0.17214840540078824, 0.17253098937201733,
      0.17291112129598951, 0.17328879577018702, 0.173664007427022,
      0.17403675093390558, 0.17440702099332539, 0.1747748123429278,
      0.1751401197555818, 0.17550293803945879, 0.17586326203811126,
      0.1762210866305359, 0.17657640673125152, 0.17692921729037636,
      0.17727951329368943, 0.17762728976270847, 0.17797254175476235,
      0.17831526436305437, 0.17865545271673708, 0.17899310198098317,
      0.17932820735704758, 0.17966076408234061, 0.17999076743049722,
      0.1803182127114378, 0.18064309527143951, 0.18096541049320422,
      0.18128515379591759, 0.181602320635319, 0.18191690650376735,
      0.18222890693029939, 0.18253831748070048, 0.18284513375756031,
      0.18314935140033994, 0.18345096608543526, 0.18374997352623254,
      0.18404636947317363, 0.18434014971381799, 0.18463131007289674,
      0.18491984641237616, 0.18520575463151812, 0.18548903066693254,
      0.18576967049263945, 0.18604767012012757, 0.18632302559840552,
      0.18659573301406193, 0.18686578849132232, 0.18713318819210012,
      0.1873979283160524, 0.18766000510063774, 0.18791941482116348,
      0.18817615379084496, 0.18843021836085189, 0.18868160492036393,
      0.18893030989662327, 0.1891763297549805, 0.18941966099894841,
      0.18966030017025304, 0.18989824384887791, 0.19013348865311627,
      0.19036603123962004, 0.19059586830344391, 0.19082299657809337,
      0.19104741283557436, 0.19126911388643475, 0.19148809657981075,
      0.19170435780347506, 0.19191789448387656, 0.19212870358618539,
      0.19233678211433897, 0.19254212711108037, 0.19274473565800176,
      0.19294460487558854, 0.19314173192325632, 0.19333611399939227,
      0.19352774834139874, 0.19371663222572655, 0.19390276296791675,
      0.19408613792264129, 0.1942667544837352, 0.19444461008423664,
      0.19461970219642538, 0.19479202833185402, 0.19496158604138641,
      0.1951283729152333, 0.1952923865829832, 0.19545362471363856,
      0.19561208501564972, 0.19576776523694428, 0.19592066316496137,
      0.19607077662668407, 0.19621810348866653, 0.19636264165706926,
      0.1965043890776843, 0.19664334373596637, 0.19677950365706354,
      0.19691286690584112, 0.19704343158691195, 0.19717119584466372,
      0.19729615786328294, 0.19741831586678249, 0.19753766811902757,
      0.19765421292375784, 0.19776794862461353, 0.19787887360515929,
      0.19798698628890507, 0.19809228513933014, 0.19819476865990546,
      0.19829443539411284, 0.19839128392546723, 0.19848531287753723,
      0.19857652091396252, 0.19866490673847589, 0.19875046909491856,
      0.19883320676726, 0.19891311857961519, 0.19899020339626006,
      0.19906446012164858, 0.19913588770042881, 0.19920448511745642,
      0.19927025139781013, 0.19933318560680596, 0.19939328685000923,
      0.19945055427324807, 0.19950498706262607, 0.19955658444453248,
      0.19960534568565425, 0.19965127009298647, 0.19969435701384158,
      0.19973460583585886, 0.19977201598701369, 0.199806586935625,
      0.19983831819036285, 0.19986720930025614, 0.19989325985469819,
      0.19991646948345285, 0.19993683785666, 0.19995436468483999,
      0.19996904971889773, 0.19998089275012643, 0.19998989361021038,
      0.19999605217122743, 0.19999936834565082, 0.19999984208635035,
      0.19999747338659316, 0.19999226228004366, 0.19998420884076321,
      0.1999733131832091, 0.19995957546223259, 0.19994299587307721,
      0.19992357465137564, 0.19990131207314632, 0.19987620845478982,
      0.19984826415308421, 0.19981747956517973, 0.19978385512859367,
      0.19974739132120353, 0.19970808866124076, 0.19966594770728341,
      0.19962096905824731, 0.1995731533533788, 0.19952250127224513,
      0.19946901353472407, 0.199412690900995, 0.19935353417152735,
      0.19929154418706874, 0.19922672182863446, 0.19915906801749375,
      0.19908858371515664, 0.19901526992336133, 0.1989391276840593,
      0.19886015807939975, 0.19877836223171597, 0.19869374130350814,
      0.19860629649742645, 0.19851602905625587, 0.19842294026289564,
      0.19832703144034408, 0.19822830395167829, 0.19812675920003345,
      0.19802239862858587, 0.19791522372053044, 0.19780523599905914,
      0.19769243702734146, 0.19757682840850066, 0.19745841178559043,
      0.19733718884157359, 0.19721316129929672, 0.19708633092146496,
      0.19695669951061928, 0.19682426890910923, 0.19668904099906592,
      0.19655101770237793, 0.19641020098066206, 0.19626659283523482,
      0.1961201953070861, 0.19597101047684956, 0.19581904046477083,
      0.19566428743068051, 0.19550675357396241, 0.19534644113352037,
      0.19518335238774928, 0.19501748965450197, 0.194848855291054,
      0.19467745169407319, 0.19450328129958488, 0.19432634658293479,
      0.19414665005875717, 0.19396419428093845, 0.19377898184257736,
      0.19359101537595347, 0.19340029755248725, 0.19320683108269932,
      0.19301061871617736, 0.19281166324153437, 0.19260996748636613,
      0.19240553431721749, 0.19219836663953496, 0.1919884673976302,
      0.19177583957463698, 0.19156048619246602, 0.19134241031176588,
      0.19112161503187861, 0.19089810349079239, 0.1906718788651014,
      0.19044294436995962, 0.1902113032590308, 0.18997695882444887,
      0.18973991439676821, 0.18950017334491254, 0.18925773907613425,
      0.18901261503596134, 0.18876480470814744, 0.18851431161462695,
      0.18826113931546173, 0.18800529140878883, 0.18774677153077457,
      0.18748558335555909, 0.18722173059520283, 0.18695521699963977,
      0.18668604635661554, 0.186414222491642, 0.1861397492679393,
      0.18586263058637686, 0.18558287038542587, 0.18530047264109939,
      0.18501544136689177, 0.18472778061372994, 0.18443749446991045,
      0.18414458706104009, 0.18384906254998287, 0.18355092513679677,
      0.18325017905867241, 0.18294682858987865, 0.18264087804169774,
      0.18233233176236216, 0.18202119413699891, 0.181707469587563,
      0.18139116257277263, 0.18107227758805211, 0.18075081916546348,
      0.18042679187364075, 0.1801002003177295, 0.17977104913932024,
      0.17943934301637762, 0.17910508666318048, 0.17876828483025303,
      0.17842894230429268, 0.17808706390810847, 0.17774265450055071,
      0.17739571897643727, 0.17704626226649045, 0.17669428933726533,
      0.17633980519107395, 0.17598281486592143, 0.17562332343543241,
      0.17526133600877258, 0.1748968577305875, 0.17452989378091793,
      0.17416044937513453, 0.17378852976386183, 0.17341414023289833,
      0.17303728610314861, 0.17265797273054587, 0.17227620550597023,
      0.17189198985517967, 0.17150533123873091, 0.17111623515189617,
      0.17072470712459287, 0.17033075272130277, 0.16993437754098739,
      0.16953558721701611, 0.16913438741708442, 0.16873078384312581,
      0.16832478223124231, 0.1679163883516174, 0.16750560800842829,
      0.16709244703977522, 0.16667691131759088, 0.16625900674755489,
      0.16583873926901826, 0.16541611485491284, 0.16499113951166433,
      0.16456381927911617, 0.164134160230432, 0.16370216847201868,
      0.16326785014343784, 0.16283121141731013, 0.16239225849924044,
      0.16195099762772344, 0.16150743507404866, 0.16106157714222391,
      0.16061343016887944, 0.16016300052317145, 0.15971029460670483,
      0.15925531885343355, 0.15879807972956717, 0.15833858373348783,
      0.15787683739565167, 0.15741284727849314, 0.15694661997634107,
      0.15647816211531829, 0.15600748035324485, 0.15553458137955264,
      0.15505947191518374, 0.15458215871249217, 0.15410264855515732,
      0.15362094825808084, 0.15313706466728749, 0.15265100465983503,
      0.15216277514371437, 0.15167238305774444, 0.15117983537148319,
      0.15068513908512582, 0.15018830122939825, 0.14968932886546715,
      0.14918822908483667, 0.1486850090092405, 0.14817967579055275,
      0.14767223661067355, 0.14716269868143936, 0.14665106924451288,
      0.14613735557127813, 0.14562156496274437, 0.14510370474944034,
      0.14458378229130259, 0.14406180497758098, 0.14353778022673103,
      0.14301171548630096, 0.14248361823283615, 0.14195349597176998,
      0.14142135623730975, 0.14088720659233997, 0.14035105462831196,
      0.13981290796512832, 0.13927277425104542, 0.13873066116256141,
      0.13818657640429971, 0.13764052770891005, 0.13709252283695622,
      0.13654256957679523, 0.13599067574448287, 0.1354368491836547,
      0.13488109776540688, 0.13432342938820183, 0.13376385197773802,
      0.13320237348685005, 0.13263900189539279, 0.13207374521011991,
      0.13150661146458109, 0.13093760871900492, 0.13036674506017618,
      0.12979402860133213, 0.12921946748204455, 0.12864306986809337,
      0.12806484395136727, 0.1274847979497391, 0.12690294010694111,
      0.12631927869246382, 0.12573382200143071, 0.12514657835447171,
      0.1245575560976222, 0.12396676360219344, 0.12337420926465055,
      0.12277990150650514, 0.122183848774187, 0.12158605953892097,
      0.12098654229661805, 0.12038530556774646, 0.11978235789720695,
      0.11917770785422342, 0.1185713640322125, 0.11796333504865807,
      0.11735362954500067, 0.11674225618650631, 0.11612922366214021,
      0.11551454068445262, 0.11489821598945221, 0.114280258336473,
      0.11366067650806232, 0.11303947930985228, 0.11241667557042599,
      0.11179227414120672, 0.11116628389631676, 0.11053871373246607,
      0.10990957256881698, 0.10927886934685389, 0.10864661303026862,
      0.10801281260482415, 0.10737747707822382, 0.10674061547999299,
      0.10610223686134768, 0.10546235029505691, 0.10482096487532638,
      0.10417808971766561, 0.10353373395874939, 0.10288790675630055,
      0.1022406172889562, 0.10159187475612821, 0.10094168837788516,
      0.10029006739481777, 0.099637021067898235, 0.098982558678361643,
      0.098326689527570288, 0.097669422936872252, 0.097010768247481879,
      0.096350734820343953, 0.09568933203598827, 0.095026569294418,
      0.094362456014954382, 0.093697001636118354, 0.0930302156154928,
      0.092362107429578566, 0.091692686573673118, 0.091021962561731742,
      0.090349944926222878, 0.089676643218005891, 0.089002067006191579,
      0.08832622587799667, 0.087649129438620826, 0.086970787311107037,
      0.086291209136192079, 0.085610404572189228, 0.084928383294841536,
      0.0842451549971746, 0.08356072938937803, 0.082875116198657964,
      0.082188325169088972, 0.081500366061495688, 0.080811248653301124,
      0.080120982738384472, 0.07942957812695553, 0.078737044645405582,
      0.078043392136163736, 0.07734863045757083, 0.076652769483729483,
      0.075955819104359834, 0.075257789224672772, 0.074558689765219288,
      0.073858530661745539, 0.0731573218650655, 0.072455073340909643,
      0.071751795069779911, 0.07104749704682127, 0.070342189281662915,
      0.069635881798292734, 0.0689285846349048, 0.068220307843752756,
      0.0675110614910209, 0.066800855656671168, 0.066089700434295837,
      0.0653776059309881, 0.064664582267188422, 0.063950639576536641,
      0.063235788005742075, 0.062520037714429225, 0.061803398874989313,
      0.06108588167244991, 0.060367496304320048, 0.059648252980441907,
      0.058928161922856506, 0.0582072333656551, 0.057485477554823507,
      0.056762904748110778, 0.056039525214879309, 0.0553153492359487,
      0.054590387103463957, 0.053864649120745095, 0.053138145602130482,
      0.052410886872847368, 0.051682883268847263, 0.050954145136676246,
      0.050224682833317651, 0.049494506726041318, 0.048763627192267373,
      0.048032054619415232, 0.047299799404745671, 0.046566871955227525,
      0.045833282687385637, 0.045099042027142482, 0.04436416040968446,
      0.043628648279309477, 0.042892516089268126, 0.042155774301629638,
      0.041418433387129076, 0.040680503825008076, 0.039941996102880517,
      0.039202920716579992, 0.038463288169996737, 0.03772310897494989,
      0.0369823936510277, 0.036241152725427508, 0.035499396732827107,
      0.034757136215224527, 0.034014381721777724, 0.033271143808676344,
      0.032527433038977691, 0.0317832599824531, 0.031038635215452449,
      0.030293569320743313, 0.029548072887356343, 0.028802156510449529,
      0.028055830791147082, 0.027309106336384555, 0.026561993758772835,
      0.0258145036764368, 0.025066646712860175, 0.024318433496752122,
      0.023569874661871576, 0.022820980846900749, 0.022071762695279842,
      0.021322230855052245, 0.020572395978728036, 0.019822268723121983,
      0.019071859749197846, 0.018321179721931719, 0.017570239310149838,
      0.016819049186372712, 0.0160676200266783, 0.015315962510539675,
      0.014564087320668976, 0.013812005142880474, 0.01305972666592807,
      0.012307262581349135, 0.011554623583327438, 0.010801820368530529,
      0.010048863635954169, 0.0092957640867816181, 0.00854253242422801,
      0.0077891793533775844, 0.0070357155810464467, 0.00628215181562615,
      0.005528498766920846, 0.0047747671460128338, 0.004020967665091863,
      0.0032671110373206484, 0.0025132079766719577, 0.0017592691977720771,
      0.0010053054157634551, 0.00025132734614175775, -0.00050265429539997429,
      -0.0012566287931122513, -0.0020105854313449815, -0.0027645134947104225,
      -0.0035184022682205485, -0.0042722410374436, -0.0050260190886670117,
      -0.0057797257090347644, -0.0065333501867038974, -0.0072868818110074021,
      -0.008040309872591531, -0.0087936236635722635, -0.0095468124776981328,
      -0.010299865610487484, -0.011052772359384155, -0.011805522023923777,
      -0.012558103905863852, -0.01331050730934645, -0.014062721541060849,
      -0.014814735910374242, -0.015566539729494309, -0.016318122313631743,
      -0.017069472981130145, -0.017820581053631986, -0.018571435856233942,
      -0.019322026717623703, -0.020072342970242268, -0.020822373950439826,
      -0.021572108998610281, -0.022321537459364008, -0.023070648681662306,
      -0.023819432018972304, -0.0245678768294324, -0.025315972475981625,
      -0.0260637083265214, -0.026811073754077232, -0.027558058136927851,
      -0.028304650858770333, -0.02905084130887442, -0.029796618882218625,
      -0.03054197297965143, -0.031286893008046178, -0.032031368380436881,
      -0.032775388516179192, -0.033518942841104994, -0.034262020787657964,
      -0.035004611795054284, -0.0357467053094369, -0.036488290784010849,
      -0.037229357679203628, -0.0379698954628192, -0.038709893610172991,
      -0.039449341604251932, -0.040188228935867445, -0.040926545103790832,
      -0.041664279614919947, -0.042401421984410943, -0.043137961735837678,
      -0.043873888401344825, -0.044609191521782006, -0.0453438606468629,
      -0.046077885335317904, -0.046811255155027952, -0.047543959683183215,
      -0.048275988506435337, -0.049007331221030931, -0.049737977432969829,
      -0.050467916758156185, -0.051197138822535106, -0.051925633262243469,
      -0.052653389723767569, -0.053380397864075814, -0.054106647350769893,
      -0.054832127862241814, -0.055556829087806285, -0.056280740727851365,
      -0.057003852493995026, -0.057726154109217089, -0.058447635308009407,
      -0.05916828583653188, -0.059888095452743977, -0.060607053926553689,
      -0.061325151039976461, -0.0620423765872594, -0.062758720375036534,
      -0.063474172222483749, -0.064188721961443262, -0.06490235943657828,
      -0.065615074505527338, -0.066326857039027687, -0.067037696921072656,
      -0.067747584049058757, -0.0684565083339132, -0.069164459700257391,
      -0.069871428086534, -0.070577403445154077, -0.071282375742649728,
      -0.07198633495980282, -0.0726892710917907, -0.073391174148341579,
      -0.074092034153856054, -0.07479184114755881, -0.07549058518365,
      -0.076188256331426271, -0.076884844675435, -0.0775803403156185,
      -0.078274733367440952, -0.078968013962038772, -0.07966017224636468,
      -0.080351198383314115, -0.081041082551874755, -0.081729814947270066,
      -0.082417385781084943, -0.083103785281414627, -0.083789003693007374,
      -0.084473031277389588, -0.085155858313013921, -0.085837475095401267,
      -0.086517871937262583, -0.087197039168659118, -0.0878749671371173,
      -0.088551646207778861, -0.089227066763540808, -0.089901219205178851,
      -0.09057409395149324, -0.091245681439448875, -0.091915972124297821,
      -0.0925849564797245, -0.093252624997984854, -0.093918968190028151,
      -0.094583976585641466, -0.095247640733587879, -0.09590995120172767,
      -0.096570898577161834, -0.097230473466368886, -0.097888666495328444,
      -0.098545468309657547, -0.0992008695747529, -0.099854860975910564,
      -0.10050743321846203, -0.10115857702791559, -0.10180828315007512,
      -0.1024565423511755, -0.10310334541802278, -0.10374868315811248,
      -0.10439254639976381, -0.10503492599225919, -0.10567581280596144,
      -0.10631519773244674, -0.10695307168464602, -0.10758942559695546,
      -0.10822425042537442, -0.10885753714764289, -0.10948927676334935,
      -0.11011946029407969, -0.11074807878352984, -0.11137512329763666,
      -0.11200058492471376, -0.1126244547755658, -0.11324672398361829,
      -0.11386738370505252, -0.11448642511891881, -0.11510383942726553,
      -0.11571961785527279, -0.11633375165136489, -0.11694623208733779, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15, 0.15,
      0.15, 0.15, 0.15, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1,
      0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, 0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1,
      -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, -0.1, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    Lab3_IMU_LQRI_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    Lab3_IMU_LQRI_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    Lab3_IMU_LQRI_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "p3Run.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error creating .mat file p3Run.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 27 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                        "Error writing mat file header to file p3Run.mat");
      return;
    }

    Lab3_IMU_LQRI_DW.ToFile_IWORK.Count = 0;
    Lab3_IMU_LQRI_DW.ToFile_IWORK.Decimation = -1;
    Lab3_IMU_LQRI_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for ToFile: '<S5>/p2Run' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "p2Run.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error creating .mat file p2Run.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                        "Error writing mat file header to file p2Run.mat");
      return;
    }

    Lab3_IMU_LQRI_DW.p2Run_IWORK.Count = 0;
    Lab3_IMU_LQRI_DW.p2Run_IWORK.Decimation = -1;
    Lab3_IMU_LQRI_DW.p2Run_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S4>/Rate Transition: x' */
  Lab3_IMU_LQRI_B.RateTransitionx =
    Lab3_IMU_LQRI_P.RateTransitionx_InitialConditio;

  /* Start for RateTransition: '<S4>/Rate Transition: y' */
  Lab3_IMU_LQRI_B.RateTransitiony =
    Lab3_IMU_LQRI_P.RateTransitiony_InitialConditio;

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab3_IMU_LQRI/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab3_IMU_LQRI_P.GameController_Enabled) {
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
        (Lab3_IMU_LQRI_P.GameController_ControllerNumber,
         Lab3_IMU_LQRI_P.GameController_BufferSize, deadzone, saturation,
         Lab3_IMU_LQRI_P.GameController_AutoCenter, 0, 1.0,
         &Lab3_IMU_LQRI_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
      }
    }
  }

  Lab3_IMU_LQRI_PrevZCX.Integrator_Reset_ZCE = UNINITIALIZED_ZCSIG;

  {
    int32_T i;

    /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
    Lab3_IMU_LQRI_X.TravelTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
    Lab3_IMU_LQRI_X.PitchTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
    Lab3_IMU_LQRI_X.ElevationTransferFcn_CSTATE = 0.0;

    /* InitializeConditions for Memory: '<S9>/Memory' */
    memcpy(&Lab3_IMU_LQRI_DW.Memory_PreviousInput[0],
           &Lab3_IMU_LQRI_P.Memory_InitialCondition[0], 10U * sizeof(real_T));

    /* InitializeConditions for Integrator: '<S6>/Integrator' */
    for (i = 0; i < 5; i++) {
      Lab3_IMU_LQRI_X.Integrator_CSTATE[i] = Lab3_IMU_LQRI_P.Integrator_IC;
    }

    /* End of InitializeConditions for Integrator: '<S6>/Integrator' */

    /* InitializeConditions for Integrator: '<S5>/Integrator' */
    Lab3_IMU_LQRI_X.Integrator_CSTATE_i[0] = Lab3_IMU_LQRI_P.Integrator_IC_c;
    Lab3_IMU_LQRI_X.Integrator_CSTATE_i[1] = Lab3_IMU_LQRI_P.Integrator_IC_c;

    /* InitializeConditions for RateTransition: '<S4>/Rate Transition: x' */
    Lab3_IMU_LQRI_DW.RateTransitionx_Buffer0 =
      Lab3_IMU_LQRI_P.RateTransitionx_InitialConditio;

    /* InitializeConditions for RateTransition: '<S4>/Rate Transition: y' */
    Lab3_IMU_LQRI_DW.RateTransitiony_Buffer0 =
      Lab3_IMU_LQRI_P.RateTransitiony_InitialConditio;
  }
}

/* Model terminate function */
void Lab3_IMU_LQRI_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab3_IMU_LQRI/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab3_IMU_LQRI_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab3_IMU_LQRI_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab3_IMU_LQRI_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_IMU_LQRI_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab3_IMU_LQRI_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab3_IMU_LQRI_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_LQRI_P.HILInitialize_POFinal;
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
      result = hil_write(Lab3_IMU_LQRI_DW.HILInitialize_Card
                         , Lab3_IMU_LQRI_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab3_IMU_LQRI_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0]
                         , &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab3_IMU_LQRI_DW.HILInitialize_Card,
            Lab3_IMU_LQRI_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab3_IMU_LQRI_DW.HILInitialize_Card,
            Lab3_IMU_LQRI_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab3_IMU_LQRI_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_IMU_LQRI_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab3_IMU_LQRI_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab3_IMU_LQRI_DW.HILInitialize_Card);
    hil_close(Lab3_IMU_LQRI_DW.HILInitialize_Card);
    Lab3_IMU_LQRI_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (stream_call_block): '<S9>/Stream Call1' incorporates:
   *  Constant: '<S9>/Constant'
   *  S-Function (string_constant_block): '<S9>/String Constant'
   */

  /* S-Function Block: Lab3_IMU_LQRI/IMU/IMU/Stream Call1 (stream_call_block) */
  {
    if (Lab3_IMU_LQRI_DW.StreamCall1_Stream != NULL) {
      stream_close(Lab3_IMU_LQRI_DW.StreamCall1_Stream);
      Lab3_IMU_LQRI_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) Lab3_IMU_LQRI_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "p3Run.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error closing MAT-file p3Run.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error reopening MAT-file p3Run.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 27 + 1, Lab3_IMU_LQRI_DW.ToFile_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                          "Error writing header for ans to MAT-file p3Run.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error closing MAT-file p3Run.mat");
        return;
      }

      Lab3_IMU_LQRI_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<S5>/p2Run' */
  {
    FILE *fp = (FILE *) Lab3_IMU_LQRI_DW.p2Run_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "p2Run.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error closing MAT-file p2Run.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error reopening MAT-file p2Run.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1, Lab3_IMU_LQRI_DW.p2Run_IWORK.Count,
           "ans")) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M,
                          "Error writing header for ans to MAT-file p2Run.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_IMU_LQRI_M, "Error closing MAT-file p2Run.mat");
        return;
      }

      Lab3_IMU_LQRI_DW.p2Run_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab3_IMU_LQRI/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab3_IMU_LQRI_P.GameController_Enabled) {
      game_controller_close(Lab3_IMU_LQRI_DW.GameController_Controller);
      Lab3_IMU_LQRI_DW.GameController_Controller = NULL;
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
  Lab3_IMU_LQRI_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  Lab3_IMU_LQRI_update(tid);
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
  Lab3_IMU_LQRI_initialize();
}

void MdlTerminate(void)
{
  Lab3_IMU_LQRI_terminate();
}

/* Registration function */
RT_MODEL_Lab3_IMU_LQRI_T *Lab3_IMU_LQRI(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Lab3_IMU_LQRI_M, 0,
                sizeof(RT_MODEL_Lab3_IMU_LQRI_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Lab3_IMU_LQRI_M->solverInfo,
                          &Lab3_IMU_LQRI_M->Timing.simTimeStep);
    rtsiSetTPtr(&Lab3_IMU_LQRI_M->solverInfo, &rtmGetTPtr(Lab3_IMU_LQRI_M));
    rtsiSetStepSizePtr(&Lab3_IMU_LQRI_M->solverInfo,
                       &Lab3_IMU_LQRI_M->Timing.stepSize0);
    rtsiSetdXPtr(&Lab3_IMU_LQRI_M->solverInfo, &Lab3_IMU_LQRI_M->derivs);
    rtsiSetContStatesPtr(&Lab3_IMU_LQRI_M->solverInfo, (real_T **)
                         &Lab3_IMU_LQRI_M->contStates);
    rtsiSetNumContStatesPtr(&Lab3_IMU_LQRI_M->solverInfo,
      &Lab3_IMU_LQRI_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Lab3_IMU_LQRI_M->solverInfo,
      &Lab3_IMU_LQRI_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Lab3_IMU_LQRI_M->solverInfo,
      &Lab3_IMU_LQRI_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Lab3_IMU_LQRI_M->solverInfo,
      &Lab3_IMU_LQRI_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Lab3_IMU_LQRI_M->solverInfo, (&rtmGetErrorStatus
      (Lab3_IMU_LQRI_M)));
    rtsiSetRTModelPtr(&Lab3_IMU_LQRI_M->solverInfo, Lab3_IMU_LQRI_M);
  }

  rtsiSetSimTimeStep(&Lab3_IMU_LQRI_M->solverInfo, MAJOR_TIME_STEP);
  Lab3_IMU_LQRI_M->intgData.f[0] = Lab3_IMU_LQRI_M->odeF[0];
  Lab3_IMU_LQRI_M->contStates = ((real_T *) &Lab3_IMU_LQRI_X);
  rtsiSetSolverData(&Lab3_IMU_LQRI_M->solverInfo, (void *)
                    &Lab3_IMU_LQRI_M->intgData);
  rtsiSetSolverName(&Lab3_IMU_LQRI_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab3_IMU_LQRI_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    Lab3_IMU_LQRI_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab3_IMU_LQRI_M->Timing.sampleTimes =
      (&Lab3_IMU_LQRI_M->Timing.sampleTimesArray[0]);
    Lab3_IMU_LQRI_M->Timing.offsetTimes =
      (&Lab3_IMU_LQRI_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab3_IMU_LQRI_M->Timing.sampleTimes[0] = (0.0);
    Lab3_IMU_LQRI_M->Timing.sampleTimes[1] = (0.002);
    Lab3_IMU_LQRI_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    Lab3_IMU_LQRI_M->Timing.offsetTimes[0] = (0.0);
    Lab3_IMU_LQRI_M->Timing.offsetTimes[1] = (0.0);
    Lab3_IMU_LQRI_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(Lab3_IMU_LQRI_M, &Lab3_IMU_LQRI_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab3_IMU_LQRI_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits = Lab3_IMU_LQRI_M->Timing.perTaskSampleHitsArray;
    Lab3_IMU_LQRI_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    Lab3_IMU_LQRI_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab3_IMU_LQRI_M, 45.0);
  Lab3_IMU_LQRI_M->Timing.stepSize0 = 0.002;
  Lab3_IMU_LQRI_M->Timing.stepSize1 = 0.002;
  Lab3_IMU_LQRI_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  Lab3_IMU_LQRI_M->Sizes.checksums[0] = (4051030798U);
  Lab3_IMU_LQRI_M->Sizes.checksums[1] = (757590525U);
  Lab3_IMU_LQRI_M->Sizes.checksums[2] = (2546377221U);
  Lab3_IMU_LQRI_M->Sizes.checksums[3] = (2966019969U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[6];
    Lab3_IMU_LQRI_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab3_IMU_LQRI_M->extModeInfo,
      &Lab3_IMU_LQRI_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab3_IMU_LQRI_M->extModeInfo,
                        Lab3_IMU_LQRI_M->Sizes.checksums);
    rteiSetTPtr(Lab3_IMU_LQRI_M->extModeInfo, rtmGetTPtr(Lab3_IMU_LQRI_M));
  }

  Lab3_IMU_LQRI_M->solverInfoPtr = (&Lab3_IMU_LQRI_M->solverInfo);
  Lab3_IMU_LQRI_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Lab3_IMU_LQRI_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Lab3_IMU_LQRI_M->solverInfo, SOLVER_MODE_MULTITASKING);

  /* block I/O */
  Lab3_IMU_LQRI_M->blockIO = ((void *) &Lab3_IMU_LQRI_B);
  (void) memset(((void *) &Lab3_IMU_LQRI_B), 0,
                sizeof(B_Lab3_IMU_LQRI_T));

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      Lab3_IMU_LQRI_B.Switch[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      Lab3_IMU_LQRI_B.Integrator[i] = 0.0;
    }

    for (i = 0; i < 27; i++) {
      Lab3_IMU_LQRI_B.TmpSignalConversionAtToFileInpo[i] = 0.0;
    }

    for (i = 0; i < 5; i++) {
      Lab3_IMU_LQRI_B.Sum1[i] = 0.0;
    }

    Lab3_IMU_LQRI_B.TravelCounttorad = 0.0;
    Lab3_IMU_LQRI_B.TravelTransferFcn = 0.0;
    Lab3_IMU_LQRI_B.PitchCounttorad = 0.0;
    Lab3_IMU_LQRI_B.PitchTransferFcn = 0.0;
    Lab3_IMU_LQRI_B.ElevationCounttorad = 0.0;
    Lab3_IMU_LQRI_B.ElevationTransferFcn = 0.0;
    Lab3_IMU_LQRI_B.Gain1[0] = 0.0;
    Lab3_IMU_LQRI_B.Gain1[1] = 0.0;
    Lab3_IMU_LQRI_B.Gain1[2] = 0.0;
    Lab3_IMU_LQRI_B.Gain2[0] = 0.0;
    Lab3_IMU_LQRI_B.Gain2[1] = 0.0;
    Lab3_IMU_LQRI_B.Gain2[2] = 0.0;
    Lab3_IMU_LQRI_B.DataTypeConversion = 0.0;
    Lab3_IMU_LQRI_B.FromWorkspace[0] = 0.0;
    Lab3_IMU_LQRI_B.FromWorkspace[1] = 0.0;
    Lab3_IMU_LQRI_B.Fr[0] = 0.0;
    Lab3_IMU_LQRI_B.Fr[1] = 0.0;
    Lab3_IMU_LQRI_B.ManualSwitch = 0.0;
    Lab3_IMU_LQRI_B.Integrator_m[0] = 0.0;
    Lab3_IMU_LQRI_B.Integrator_m[1] = 0.0;
    Lab3_IMU_LQRI_B.u[0] = 0.0;
    Lab3_IMU_LQRI_B.u[1] = 0.0;
    Lab3_IMU_LQRI_B.Sum = 0.0;
    Lab3_IMU_LQRI_B.FrontmotorSaturation = 0.0;
    Lab3_IMU_LQRI_B.BackmotorSaturation = 0.0;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator[0] = 0.0;
    Lab3_IMU_LQRI_B.TmpSignalConversionAtIntegrator[1] = 0.0;
    Lab3_IMU_LQRI_B.RateTransitionx = 0.0;
    Lab3_IMU_LQRI_B.Joystick_gain_x = 0.0;
    Lab3_IMU_LQRI_B.RateTransitiony = 0.0;
    Lab3_IMU_LQRI_B.Joystick_gain_y = 0.0;
    Lab3_IMU_LQRI_B.euler_rates[0] = 0.0;
    Lab3_IMU_LQRI_B.euler_rates[1] = 0.0;
    Lab3_IMU_LQRI_B.euler_rates[2] = 0.0;
    Lab3_IMU_LQRI_B.angles[0] = 0.0;
    Lab3_IMU_LQRI_B.angles[1] = 0.0;
  }

  /* parameters */
  Lab3_IMU_LQRI_M->defaultParam = ((real_T *)&Lab3_IMU_LQRI_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Lab3_IMU_LQRI_X;
    Lab3_IMU_LQRI_M->contStates = (x);
    (void) memset((void *)&Lab3_IMU_LQRI_X, 0,
                  sizeof(X_Lab3_IMU_LQRI_T));
  }

  /* states (dwork) */
  Lab3_IMU_LQRI_M->dwork = ((void *) &Lab3_IMU_LQRI_DW);
  (void) memset((void *)&Lab3_IMU_LQRI_DW, 0,
                sizeof(DW_Lab3_IMU_LQRI_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_LQRI_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      Lab3_IMU_LQRI_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  Lab3_IMU_LQRI_DW.HILWriteAnalog_Buffer[0] = 0.0;
  Lab3_IMU_LQRI_DW.HILWriteAnalog_Buffer[1] = 0.0;
  Lab3_IMU_LQRI_DW.RateTransitionx_Buffer0 = 0.0;
  Lab3_IMU_LQRI_DW.RateTransitiony_Buffer0 = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab3_IMU_LQRI_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab3_IMU_LQRI_M->Sizes.numContStates = (10);/* Number of continuous states */
  Lab3_IMU_LQRI_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Lab3_IMU_LQRI_M->Sizes.numY = (0);   /* Number of model outputs */
  Lab3_IMU_LQRI_M->Sizes.numU = (0);   /* Number of model inputs */
  Lab3_IMU_LQRI_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab3_IMU_LQRI_M->Sizes.numSampTimes = (3);/* Number of sample times */
  Lab3_IMU_LQRI_M->Sizes.numBlocks = (88);/* Number of blocks */
  Lab3_IMU_LQRI_M->Sizes.numBlockIO = (29);/* Number of block outputs */
  Lab3_IMU_LQRI_M->Sizes.numBlockPrms = (533);/* Sum of parameter "widths" */
  return Lab3_IMU_LQRI_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
