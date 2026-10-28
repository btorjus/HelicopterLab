/*
 * Lab3_IMU_Encoder_comp.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab3_IMU_Encoder_comp".
 *
 * Model version              : 11.15
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Oct 14 17:44:55 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab3_IMU_Encoder_comp.h"
#include "Lab3_IMU_Encoder_comp_private.h"
#include "Lab3_IMU_Encoder_comp_dt.h"

t_stream Lab3_IMU_Encoder_comp_rtZt_stream = NULL;

/* Block signals (default storage) */
B_Lab3_IMU_Encoder_comp_T Lab3_IMU_Encoder_comp_B;

/* Continuous states */
X_Lab3_IMU_Encoder_comp_T Lab3_IMU_Encoder_comp_X;

/* Block states (default storage) */
DW_Lab3_IMU_Encoder_comp_T Lab3_IMU_Encoder_comp_DW;

/* Real-time model */
static RT_MODEL_Lab3_IMU_Encoder_com_T Lab3_IMU_Encoder_comp_M_;
RT_MODEL_Lab3_IMU_Encoder_com_T *const Lab3_IMU_Encoder_comp_M =
  &Lab3_IMU_Encoder_comp_M_;
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
  rtmSampleHitPtr[1] = rtmStepTask(Lab3_IMU_Encoder_comp_M, 1);
  rtmSampleHitPtr[2] = rtmStepTask(Lab3_IMU_Encoder_comp_M, 2);
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
  if (Lab3_IMU_Encoder_comp_M->Timing.TaskCounters.TID[1] == 0) {
    Lab3_IMU_Encoder_comp_M->Timing.RateInteraction.TID1_2 =
      (Lab3_IMU_Encoder_comp_M->Timing.TaskCounters.TID[2] == 0);

    /* update PerTaskSampleHits matrix for non-inline sfcn */
    Lab3_IMU_Encoder_comp_M->Timing.perTaskSampleHits[5] =
      Lab3_IMU_Encoder_comp_M->Timing.RateInteraction.TID1_2;
  }

  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (Lab3_IMU_Encoder_comp_M->Timing.TaskCounters.TID[2])++;
  if ((Lab3_IMU_Encoder_comp_M->Timing.TaskCounters.TID[2]) > 4) {/* Sample time: [0.01s, 0.0s] */
    Lab3_IMU_Encoder_comp_M->Timing.TaskCounters.TID[2] = 0;
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
  Lab3_IMU_Encoder_comp_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function for TID0 */
void Lab3_IMU_Encoder_comp_output0(void) /* Sample time: [0.0s, 0.0s] */
{
  /* local block i/o variables */
  t_stream_ptr rtb_StreamCall1_o1;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_BackmotorSaturation;
  real_T rtb_DeadZoney;
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  boolean_T rtb_StreamRead1_o3;
  real_T tmp[9];
  real_T euler_rates_tmp;
  real_T euler_rates_tmp_0;
  real_T euler_rates_tmp_1;
  real_T euler_rates_tmp_2;
  int32_T i;
  if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    /* set solver stop time */
    if (!(Lab3_IMU_Encoder_comp_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Lab3_IMU_Encoder_comp_M->solverInfo,
                            ((Lab3_IMU_Encoder_comp_M->Timing.clockTickH0 + 1) *
        Lab3_IMU_Encoder_comp_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Lab3_IMU_Encoder_comp_M->solverInfo,
                            ((Lab3_IMU_Encoder_comp_M->Timing.clockTick0 + 1) *
        Lab3_IMU_Encoder_comp_M->Timing.stepSize0 +
        Lab3_IMU_Encoder_comp_M->Timing.clockTickH0 *
        Lab3_IMU_Encoder_comp_M->Timing.stepSize0 * 4294967296.0));
    }

    {                                  /* Sample time: [0.0s, 0.0s] */
      rate_monotonic_scheduler();
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    Lab3_IMU_Encoder_comp_M->Timing.t[0] = rtsiGetT
      (&Lab3_IMU_Encoder_comp_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

    /* S-Function Block: Lab3_IMU_Encoder_comp/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Task, 1,
         &Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_BackmotorSaturation =
          Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_DeadZoney = Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S2>/Travel: Count to rad' */
    Lab3_IMU_Encoder_comp_B.TravelCounttorad =
      Lab3_IMU_Encoder_comp_P.TravelCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S2>/Pitch: Count to rad' */
    Lab3_IMU_Encoder_comp_B.PitchCounttorad =
      Lab3_IMU_Encoder_comp_P.PitchCounttorad_Gain * rtb_BackmotorSaturation;
  }

  /* TransferFcn: '<S2>/Travel: Transfer Fcn' */
  Lab3_IMU_Encoder_comp_B.TravelTransferFcn = 0.0;
  Lab3_IMU_Encoder_comp_B.TravelTransferFcn +=
    Lab3_IMU_Encoder_comp_P.TravelTransferFcn_C *
    Lab3_IMU_Encoder_comp_X.TravelTransferFcn_CSTATE;
  Lab3_IMU_Encoder_comp_B.TravelTransferFcn +=
    Lab3_IMU_Encoder_comp_P.TravelTransferFcn_D *
    Lab3_IMU_Encoder_comp_B.TravelCounttorad;

  /* TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  Lab3_IMU_Encoder_comp_B.PitchTransferFcn = 0.0;
  Lab3_IMU_Encoder_comp_B.PitchTransferFcn +=
    Lab3_IMU_Encoder_comp_P.PitchTransferFcn_C *
    Lab3_IMU_Encoder_comp_X.PitchTransferFcn_CSTATE;
  Lab3_IMU_Encoder_comp_B.PitchTransferFcn +=
    Lab3_IMU_Encoder_comp_P.PitchTransferFcn_D *
    Lab3_IMU_Encoder_comp_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    /* Gain: '<S2>/Elevation: Count to rad' */
    Lab3_IMU_Encoder_comp_B.ElevationCounttorad =
      Lab3_IMU_Encoder_comp_P.ElevationCounttorad_Gain * rtb_DeadZoney;
  }

  /* TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  Lab3_IMU_Encoder_comp_B.ElevationTransferFcn = 0.0;
  Lab3_IMU_Encoder_comp_B.ElevationTransferFcn +=
    Lab3_IMU_Encoder_comp_P.ElevationTransferFcn_C *
    Lab3_IMU_Encoder_comp_X.ElevationTransferFcn_CSTATE;
  Lab3_IMU_Encoder_comp_B.ElevationTransferFcn +=
    Lab3_IMU_Encoder_comp_P.ElevationTransferFcn_D *
    Lab3_IMU_Encoder_comp_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    /* S-Function (stream_call_block): '<S7>/Stream Call1' incorporates:
     *  Constant: '<S7>/Constant'
     *  S-Function (string_constant_block): '<S7>/String Constant'
     */

    /* S-Function Block: Lab3_IMU_Encoder_comp/IMU/IMU/Stream Call1 (stream_call_block) */
    {
      t_error result = 0;
      t_boolean close_flag = (Lab3_IMU_Encoder_comp_P.Constant_Value != 0);
      rtb_StreamCall1_o1 = NULL;
      switch (Lab3_IMU_Encoder_comp_DW.StreamCall1_State) {
       case STREAM_CALL_STATE_NOT_CONNECTED:
        {
          if (!close_flag) {
            /* Make sure URI is null-terminated */
            if (string_length((char *)
                              Lab3_IMU_Encoder_comp_P.StringConstant_Value, 255)
                == 255) {
              rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                                "URI passed to Stream Call block is not null-terminated!");
              result = -QERR_STRING_NOT_TERMINATED;
            } else {
              result = stream_connect((char *)
                Lab3_IMU_Encoder_comp_P.StringConstant_Value,
                Lab3_IMU_Encoder_comp_P.StreamCall1_NonBlocking != 0,
                Lab3_IMU_Encoder_comp_P.StreamCall1_SendBufferSize,
                Lab3_IMU_Encoder_comp_P.StreamCall1_ReceiveBufferSize,
                &Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream);
              if (result == 0) {
                Lab3_IMU_Encoder_comp_DW.StreamCall1_State =
                  STREAM_CALL_STATE_CONNECTED;
                stream_set_byte_order
                  (Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream,
                   (t_stream_byte_order)
                   Lab3_IMU_Encoder_comp_P.StreamCall1_Endian);
                rtb_StreamCall1_o1 =
                  &Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream;
              } else if (result == -QERR_WOULD_BLOCK) {
                Lab3_IMU_Encoder_comp_DW.StreamCall1_State =
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

            result = stream_poll(Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream,
                                 &timeout, STREAM_POLL_CONNECT);
            if (result > 0) {
              Lab3_IMU_Encoder_comp_DW.StreamCall1_State =
                STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    Lab3_IMU_Encoder_comp_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream;
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
          rtb_StreamCall1_o1 = &Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream;
          if (!close_flag) {
            break;
          }

          /* Fall through deliberately */
        }

       default:
        {
          t_error close_result = stream_close
            (Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream);
          if (close_result == 0) {
            Lab3_IMU_Encoder_comp_DW.StreamCall1_State =
              STREAM_CALL_STATE_NOT_CONNECTED;
            Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream = NULL;
            rtb_StreamCall1_o1 = NULL;
          } else if (result == 0) {
            result = close_result;
          }
          break;
        }
      }

      Lab3_IMU_Encoder_comp_B.StreamCall1_o2 =
        Lab3_IMU_Encoder_comp_DW.StreamCall1_State;
      rtb_StreamCall1_o3 = (int32_T) result;
    }

    /* S-Function (stream_formatted_write_block): '<S7>/Stream Formatted Write' incorporates:
     *  Constant: '<S7>/Constant1'
     */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          Lab3_IMU_Encoder_comp_P.StreamFormattedWrite_MaxUnits,
          &rtb_StreamFormattedWrite_o2, "%c\n"
          , (char) Lab3_IMU_Encoder_comp_P.Constant1_Value
          );
        if (result > 0) {
          result = stream_flush(*rtb_StreamCall1_o1);
        }

        if (result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      }
    }

    /* S-Function (stream_read_block): '<S7>/Stream Read1' incorporates:
     *  Constant: '<S7>/Constant1'
     *  S-Function (stream_call_block): '<S7>/Stream Call1'
     *  S-Function (stream_formatted_write_block): '<S7>/Stream Formatted Write'
     */

    /* S-Function Block: Lab3_IMU_Encoder_comp/IMU/IMU/Stream Read1 (stream_read_block) */
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
      /* Switch: '<S7>/Switch' */
      if (rtb_StreamRead1_o3) {
        /* Switch: '<S7>/Switch' incorporates:
         *  DataTypeConversion: '<S7>/Data Type Conversion'
         */
        Lab3_IMU_Encoder_comp_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        /* Switch: '<S7>/Switch' incorporates:
         *  Memory: '<S7>/Memory'
         */
        Lab3_IMU_Encoder_comp_B.Switch[i] =
          Lab3_IMU_Encoder_comp_DW.Memory_PreviousInput[i];
      }

      /* End of Switch: '<S7>/Switch' */
    }

    for (i = 0; i < 3; i++) {
      /* Gain: '<S7>/Gain1' */
      Lab3_IMU_Encoder_comp_B.Gain1[i] = 0.0;

      /* Gain: '<S7>/Gain2' */
      Lab3_IMU_Encoder_comp_B.Gain2[i] = 0.0;

      /* Gain: '<S7>/Gain1' */
      Lab3_IMU_Encoder_comp_B.Gain1[i] += Lab3_IMU_Encoder_comp_P.Gain1_Gain[i] *
        Lab3_IMU_Encoder_comp_B.Switch[3];

      /* Gain: '<S7>/Gain2' */
      Lab3_IMU_Encoder_comp_B.Gain2[i] += Lab3_IMU_Encoder_comp_P.Gain2_Gain[i] *
        Lab3_IMU_Encoder_comp_B.Switch[0];

      /* Gain: '<S7>/Gain1' */
      Lab3_IMU_Encoder_comp_B.Gain1[i] += Lab3_IMU_Encoder_comp_P.Gain1_Gain[i +
        3] * Lab3_IMU_Encoder_comp_B.Switch[4];

      /* Gain: '<S7>/Gain2' */
      Lab3_IMU_Encoder_comp_B.Gain2[i] += Lab3_IMU_Encoder_comp_P.Gain2_Gain[i +
        3] * Lab3_IMU_Encoder_comp_B.Switch[1];

      /* Gain: '<S7>/Gain1' */
      Lab3_IMU_Encoder_comp_B.Gain1[i] += Lab3_IMU_Encoder_comp_P.Gain1_Gain[i +
        6] * Lab3_IMU_Encoder_comp_B.Switch[5];

      /* Gain: '<S7>/Gain2' */
      Lab3_IMU_Encoder_comp_B.Gain2[i] += Lab3_IMU_Encoder_comp_P.Gain2_Gain[i +
        6] * Lab3_IMU_Encoder_comp_B.Switch[2];
    }

    /* DataTypeConversion: '<Root>/Data Type Conversion' */
    Lab3_IMU_Encoder_comp_B.DataTypeConversion = rtb_StreamRead1_o3;

    /* MATLAB Function: '<S3>/Gyro vector to [pitch rate, elevation rate, travle rate]' incorporates:
     *  SignalConversion generated from: '<S6>/ SFunction '
     */
    /* MATLAB Function 'IMU/Gyro vector to [pitch rate, elevation rate, travle rate]': '<S6>:1' */
    /* '<S6>:1:3' */
    /* '<S6>:1:4' */
    /* '<S6>:1:10' */
    /* '<S6>:1:14' */
    euler_rates_tmp = tan(Lab3_IMU_Encoder_comp_B.ElevationCounttorad);
    euler_rates_tmp_0 = sin(Lab3_IMU_Encoder_comp_B.PitchCounttorad);
    euler_rates_tmp_1 = cos(Lab3_IMU_Encoder_comp_B.PitchCounttorad);
    euler_rates_tmp_2 = cos(Lab3_IMU_Encoder_comp_B.ElevationCounttorad);
    tmp[0] = 1.0;
    tmp[3] = euler_rates_tmp_0 * euler_rates_tmp;
    tmp[6] = euler_rates_tmp_1 * euler_rates_tmp;
    tmp[1] = 0.0;
    tmp[4] = euler_rates_tmp_1;
    tmp[7] = -euler_rates_tmp_0;
    tmp[2] = 0.0;
    tmp[5] = euler_rates_tmp_0 / euler_rates_tmp_2;
    tmp[8] = euler_rates_tmp_1 / euler_rates_tmp_2;

    /* SignalConversion generated from: '<Root>/To File' */
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[0] =
      Lab3_IMU_Encoder_comp_B.TravelCounttorad;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[1] =
      Lab3_IMU_Encoder_comp_B.TravelTransferFcn;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[2] =
      Lab3_IMU_Encoder_comp_B.PitchCounttorad;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[3] =
      Lab3_IMU_Encoder_comp_B.PitchTransferFcn;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[4] =
      Lab3_IMU_Encoder_comp_B.ElevationCounttorad;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[5] =
      Lab3_IMU_Encoder_comp_B.ElevationTransferFcn;
    for (i = 0; i < 3; i++) {
      /* MATLAB Function: '<S3>/Gyro vector to [pitch rate, elevation rate, travle rate]' */
      Lab3_IMU_Encoder_comp_B.euler_rates[i] = 0.0;
      Lab3_IMU_Encoder_comp_B.euler_rates[i] += tmp[i] *
        Lab3_IMU_Encoder_comp_B.Gain1[0];
      Lab3_IMU_Encoder_comp_B.euler_rates[i] += tmp[i + 3] *
        Lab3_IMU_Encoder_comp_B.Gain1[1];
      Lab3_IMU_Encoder_comp_B.euler_rates[i] += tmp[i + 6] *
        Lab3_IMU_Encoder_comp_B.Gain1[2];

      /* SignalConversion generated from: '<Root>/To File' */
      Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[i + 6] =
        Lab3_IMU_Encoder_comp_B.Gain1[i];
      Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[i + 9] =
        Lab3_IMU_Encoder_comp_B.Gain2[i];
    }

    /* SignalConversion generated from: '<Root>/To File' */
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[12] =
      Lab3_IMU_Encoder_comp_B.DataTypeConversion;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[13] =
      Lab3_IMU_Encoder_comp_B.PitchCounttorad;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[14] =
      Lab3_IMU_Encoder_comp_B.euler_rates[0];
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[15] =
      Lab3_IMU_Encoder_comp_B.ElevationCounttorad;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[16] =
      Lab3_IMU_Encoder_comp_B.euler_rates[1];
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[17] =
      Lab3_IMU_Encoder_comp_B.euler_rates[2];
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[18] = 0.0;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[19] = 0.0;
    Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[20] = 0.0;

    /* ToFile: '<Root>/To File' */
    if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
      if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M) ) {
        {
          if (!(++Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Decimation % 1) &&
              (Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Count * (21 + 1)) + 1 <
              100000000 ) {
            FILE *fp = (FILE *) Lab3_IMU_Encoder_comp_DW.ToFile_PWORK.FilePtr;
            if (fp != (NULL)) {
              real_T u[21 + 1];
              Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Decimation = 0;
              u[0] = Lab3_IMU_Encoder_comp_M->Timing.t[1];
              u[1] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[0];
              u[2] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[1];
              u[3] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[2];
              u[4] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[3];
              u[5] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[4];
              u[6] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[5];
              u[7] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[6];
              u[8] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[7];
              u[9] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[8];
              u[10] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[9];
              u[11] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[10];
              u[12] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[11];
              u[13] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[12];
              u[14] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[13];
              u[15] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[14];
              u[16] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[15];
              u[17] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[16];
              u[18] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[17];
              u[19] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[18];
              u[20] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[19];
              u[21] = Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[20];
              if (fwrite(u, sizeof(real_T), 21 + 1, fp) != 21 + 1) {
                rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                                  "Error writing to MAT-file p3Run.mat");
                return;
              }

              if (((++Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Count) * (21 + 1))+1
                  >= 100000000) {
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

    /* DeadZone: '<S4>/Dead Zone: y' incorporates:
     *  Sum: '<S1>/Add'
     */
    rtb_DeadZoney = 0.0;

    /* Saturate: '<S2>/Back motor: Saturation' incorporates:
     *  Gain: '<S1>/Back gain'
     *  Sum: '<S1>/Subtract'
     */
    rtb_BackmotorSaturation = 0.0;
    rtb_BackmotorSaturation *= Lab3_IMU_Encoder_comp_P.Backgain_Gain;

    /* DeadZone: '<S4>/Dead Zone: y' incorporates:
     *  Gain: '<S1>/Front gain'
     */
    rtb_DeadZoney *= Lab3_IMU_Encoder_comp_P.Frontgain_Gain;

    /* Saturate: '<S2>/Front motor: Saturation' */
    if (rtb_DeadZoney > Lab3_IMU_Encoder_comp_P.FrontmotorSaturation_UpperSat) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_Encoder_comp_P.FrontmotorSaturation_UpperSat;
    } else {
      if (rtb_DeadZoney < Lab3_IMU_Encoder_comp_P.FrontmotorSaturation_LowerSat)
      {
        /* DeadZone: '<S4>/Dead Zone: y' */
        rtb_DeadZoney = Lab3_IMU_Encoder_comp_P.FrontmotorSaturation_LowerSat;
      }
    }

    /* End of Saturate: '<S2>/Front motor: Saturation' */

    /* Saturate: '<S2>/Back motor: Saturation' */
    if (rtb_BackmotorSaturation >
        Lab3_IMU_Encoder_comp_P.BackmotorSaturation_UpperSat) {
      /* Saturate: '<S2>/Back motor: Saturation' */
      rtb_BackmotorSaturation =
        Lab3_IMU_Encoder_comp_P.BackmotorSaturation_UpperSat;
    } else {
      if (rtb_BackmotorSaturation <
          Lab3_IMU_Encoder_comp_P.BackmotorSaturation_LowerSat) {
        /* Saturate: '<S2>/Back motor: Saturation' */
        rtb_BackmotorSaturation =
          Lab3_IMU_Encoder_comp_P.BackmotorSaturation_LowerSat;
      }
    }

    /* End of Saturate: '<S2>/Back motor: Saturation' */

    /* S-Function (hil_write_analog_block): '<S2>/HIL Write Analog' */

    /* S-Function Block: Lab3_IMU_Encoder_comp/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_Buffer[0] = rtb_DeadZoney;
      Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_Buffer[1] =
        rtb_BackmotorSaturation;
      result = hil_write_analog(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
        Lab3_IMU_Encoder_comp_P.HILWriteAnalog_channels, 2,
        &Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
      }
    }

    /* Scope: '<S7>/Connected' */
    /* MATLAB Function 'IMU/Acc til ang': '<S5>:1' */
    /* '<S5>:1:2' */
    /* '<S5>:1:3' */
    /* '<S5>:1:4' */
    /* '<S5>:1:5' */

    /* S-Function (stop_with_error_block): '<S7>/Stop with Call Error' */

    /* S-Function Block: Lab3_IMU_Encoder_comp/IMU/IMU/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    /* RateTransition: '<S4>/Rate Transition: x' */
    if (Lab3_IMU_Encoder_comp_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S4>/Rate Transition: x' */
      Lab3_IMU_Encoder_comp_B.RateTransitionx =
        Lab3_IMU_Encoder_comp_DW.RateTransitionx_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: x' */

    /* DeadZone: '<S4>/Dead Zone: x' */
    if (Lab3_IMU_Encoder_comp_B.RateTransitionx >
        Lab3_IMU_Encoder_comp_P.DeadZonex_End) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_Encoder_comp_B.RateTransitionx -
        Lab3_IMU_Encoder_comp_P.DeadZonex_End;
    } else if (Lab3_IMU_Encoder_comp_B.RateTransitionx >=
               Lab3_IMU_Encoder_comp_P.DeadZonex_Start) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = 0.0;
    } else {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_Encoder_comp_B.RateTransitionx -
        Lab3_IMU_Encoder_comp_P.DeadZonex_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: x' */

    /* Gain: '<S4>/Joystick_gain_x' incorporates:
     *  Gain: '<S4>/Gain: x'
     */
    Lab3_IMU_Encoder_comp_B.Joystick_gain_x = Lab3_IMU_Encoder_comp_P.Gainx_Gain
      * rtb_DeadZoney * Lab3_IMU_Encoder_comp_P.Joystick_gain_x;

    /* RateTransition: '<S4>/Rate Transition: y' */
    if (Lab3_IMU_Encoder_comp_M->Timing.RateInteraction.TID1_2) {
      /* RateTransition: '<S4>/Rate Transition: y' */
      Lab3_IMU_Encoder_comp_B.RateTransitiony =
        Lab3_IMU_Encoder_comp_DW.RateTransitiony_Buffer0;
    }

    /* End of RateTransition: '<S4>/Rate Transition: y' */

    /* DeadZone: '<S4>/Dead Zone: y' */
    if (Lab3_IMU_Encoder_comp_B.RateTransitiony >
        Lab3_IMU_Encoder_comp_P.DeadZoney_End) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_Encoder_comp_B.RateTransitiony -
        Lab3_IMU_Encoder_comp_P.DeadZoney_End;
    } else if (Lab3_IMU_Encoder_comp_B.RateTransitiony >=
               Lab3_IMU_Encoder_comp_P.DeadZoney_Start) {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = 0.0;
    } else {
      /* DeadZone: '<S4>/Dead Zone: y' */
      rtb_DeadZoney = Lab3_IMU_Encoder_comp_B.RateTransitiony -
        Lab3_IMU_Encoder_comp_P.DeadZoney_Start;
    }

    /* End of DeadZone: '<S4>/Dead Zone: y' */

    /* Gain: '<S4>/Joystick_gain_y' incorporates:
     *  Gain: '<S4>/Gain: y'
     */
    Lab3_IMU_Encoder_comp_B.Joystick_gain_y = Lab3_IMU_Encoder_comp_P.Gainy_Gain
      * rtb_DeadZoney * Lab3_IMU_Encoder_comp_P.Joystick_gain_y;
  }
}

/* Model update function for TID0 */
void Lab3_IMU_Encoder_comp_update0(void) /* Sample time: [0.0s, 0.0s] */
{
  if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    /* Update for Memory: '<S7>/Memory' */
    memcpy(&Lab3_IMU_Encoder_comp_DW.Memory_PreviousInput[0],
           &Lab3_IMU_Encoder_comp_B.Switch[0], 10U * sizeof(real_T));
  }

  if (rtmIsMajorTimeStep(Lab3_IMU_Encoder_comp_M)) {
    rt_ertODEUpdateContinuousStates(&Lab3_IMU_Encoder_comp_M->solverInfo);
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
  if (!(++Lab3_IMU_Encoder_comp_M->Timing.clockTick0)) {
    ++Lab3_IMU_Encoder_comp_M->Timing.clockTickH0;
  }

  Lab3_IMU_Encoder_comp_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Lab3_IMU_Encoder_comp_M->solverInfo);

  /* Update absolute time */
  /* The "clockTick1" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick1"
   * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick1 and the high bits
   * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab3_IMU_Encoder_comp_M->Timing.clockTick1)) {
    ++Lab3_IMU_Encoder_comp_M->Timing.clockTickH1;
  }

  Lab3_IMU_Encoder_comp_M->Timing.t[1] =
    Lab3_IMU_Encoder_comp_M->Timing.clockTick1 *
    Lab3_IMU_Encoder_comp_M->Timing.stepSize1 +
    Lab3_IMU_Encoder_comp_M->Timing.clockTickH1 *
    Lab3_IMU_Encoder_comp_M->Timing.stepSize1 * 4294967296.0;
}

/* Derivatives for root system: '<Root>' */
void Lab3_IMU_Encoder_comp_derivatives(void)
{
  XDot_Lab3_IMU_Encoder_comp_T *_rtXdot;
  _rtXdot = ((XDot_Lab3_IMU_Encoder_comp_T *) Lab3_IMU_Encoder_comp_M->derivs);

  /* Derivatives for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE +=
    Lab3_IMU_Encoder_comp_P.TravelTransferFcn_A *
    Lab3_IMU_Encoder_comp_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += Lab3_IMU_Encoder_comp_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += Lab3_IMU_Encoder_comp_P.PitchTransferFcn_A
    * Lab3_IMU_Encoder_comp_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += Lab3_IMU_Encoder_comp_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    Lab3_IMU_Encoder_comp_P.ElevationTransferFcn_A *
    Lab3_IMU_Encoder_comp_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    Lab3_IMU_Encoder_comp_B.ElevationCounttorad;
}

/* Model output function for TID2 */
void Lab3_IMU_Encoder_comp_output2(void) /* Sample time: [0.01s, 0.0s] */
{
  /* local block i/o variables */
  real_T rtb_GameController_o4;
  real_T rtb_GameController_o5;

  /* S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab3_IMU_Encoder_comp/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab3_IMU_Encoder_comp_P.GameController_Enabled) {
      t_game_controller_states state;
      t_boolean new_data;
      t_error result;
      result = game_controller_poll
        (Lab3_IMU_Encoder_comp_DW.GameController_Controller, &state, &new_data);
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
  Lab3_IMU_Encoder_comp_DW.RateTransitionx_Buffer0 = rtb_GameController_o4;

  /* RateTransition: '<S4>/Rate Transition: y' */
  Lab3_IMU_Encoder_comp_DW.RateTransitiony_Buffer0 = rtb_GameController_o5;
}

/* Model update function for TID2 */
void Lab3_IMU_Encoder_comp_update2(void) /* Sample time: [0.01s, 0.0s] */
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
  if (!(++Lab3_IMU_Encoder_comp_M->Timing.clockTick2)) {
    ++Lab3_IMU_Encoder_comp_M->Timing.clockTickH2;
  }

  Lab3_IMU_Encoder_comp_M->Timing.t[2] =
    Lab3_IMU_Encoder_comp_M->Timing.clockTick2 *
    Lab3_IMU_Encoder_comp_M->Timing.stepSize2 +
    Lab3_IMU_Encoder_comp_M->Timing.clockTickH2 *
    Lab3_IMU_Encoder_comp_M->Timing.stepSize2 * 4294967296.0;
}

/* Model output wrapper function for compatibility with a static main program */
void Lab3_IMU_Encoder_comp_output(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab3_IMU_Encoder_comp_output0();
    break;

   case 2 :
    Lab3_IMU_Encoder_comp_output2();
    break;

   default :
    break;
  }
}

/* Model update wrapper function for compatibility with a static main program */
void Lab3_IMU_Encoder_comp_update(int_T tid)
{
  switch (tid) {
   case 0 :
    Lab3_IMU_Encoder_comp_update0();
    break;

   case 2 :
    Lab3_IMU_Encoder_comp_update2();
    break;

   default :
    break;
  }
}

/* Model initialize function */
void Lab3_IMU_Encoder_comp_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab3_IMU_Encoder_comp/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0",
                      &Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
       "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
      return;
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab3_IMU_Encoder_comp_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_AIChannels, 8U,
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMinimums[0],
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab3_IMU_Encoder_comp_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_AOChannels, 8U,
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMinimums[0],
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_AOStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
        Lab3_IMU_Encoder_comp_P.HILInitialize_AOChannels, 8U,
        &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if (Lab3_IMU_Encoder_comp_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_AOChannels, 8U,
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] =
            Lab3_IMU_Encoder_comp_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_EIStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] =
            Lab3_IMU_Encoder_comp_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_EIChannels, 8U,
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_POPStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
        Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab3_IMU_Encoder_comp_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = Lab3_IMU_Encoder_comp_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              Lab3_IMU_Encoder_comp_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency
          (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
           &Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedChans[0],
           num_duty_cycle_modes,
           &Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle
          (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
           &Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
           num_frequency_modes,
           &Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] =
            Lab3_IMU_Encoder_comp_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] =
            Lab3_IMU_Encoder_comp_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] =
            Lab3_IMU_Encoder_comp_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels, 8U,
         (t_pwm_configuration *)
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_POModeValues[0],
         (t_pwm_alignment *)
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_POAlignValues[0],
         (t_pwm_polarity *)
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
        Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels, 8U,
        &Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[0],
        &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_POStart && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
        Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels, 8U,
        &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }

    if (Lab3_IMU_Encoder_comp_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
         Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels, 8U,
         &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S2>/HIL Read Encoder Timebase' */

  /* S-Function Block: Lab3_IMU_Encoder_comp/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
       Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_SamplesI,
       Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_Channels, 3,
       &Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Lab3_IMU_Encoder_comp_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (Lab3_IMU_Encoder_comp_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
    }
  }

  /* Start for S-Function (stream_call_block): '<S7>/Stream Call1' incorporates:
   *  Constant: '<S7>/Constant'
   *  S-Function (string_constant_block): '<S7>/String Constant'
   */

  /* S-Function Block: Lab3_IMU_Encoder_comp/IMU/IMU/Stream Call1 (stream_call_block) */
  {
    Lab3_IMU_Encoder_comp_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream = NULL;
  }

  /* Start for ToFile: '<Root>/To File' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "p3Run.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                        "Error creating .mat file p3Run.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 21 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                        "Error writing mat file header to file p3Run.mat");
      return;
    }

    Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Count = 0;
    Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Decimation = -1;
    Lab3_IMU_Encoder_comp_DW.ToFile_PWORK.FilePtr = fp;
  }

  /* Start for RateTransition: '<S4>/Rate Transition: x' */
  Lab3_IMU_Encoder_comp_B.RateTransitionx =
    Lab3_IMU_Encoder_comp_P.RateTransitionx_InitialConditio;

  /* Start for RateTransition: '<S4>/Rate Transition: y' */
  Lab3_IMU_Encoder_comp_B.RateTransitiony =
    Lab3_IMU_Encoder_comp_P.RateTransitiony_InitialConditio;

  /* Start for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab3_IMU_Encoder_comp/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab3_IMU_Encoder_comp_P.GameController_Enabled) {
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
        (Lab3_IMU_Encoder_comp_P.GameController_ControllerNumber,
         Lab3_IMU_Encoder_comp_P.GameController_BufferSize, deadzone, saturation,
         Lab3_IMU_Encoder_comp_P.GameController_AutoCenter, 0, 1.0,
         &Lab3_IMU_Encoder_comp_DW.GameController_Controller);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<S2>/Travel: Transfer Fcn' */
  Lab3_IMU_Encoder_comp_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Pitch: Transfer Fcn' */
  Lab3_IMU_Encoder_comp_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S2>/Elevation: Transfer Fcn' */
  Lab3_IMU_Encoder_comp_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S7>/Memory' */
  memcpy(&Lab3_IMU_Encoder_comp_DW.Memory_PreviousInput[0],
         &Lab3_IMU_Encoder_comp_P.Memory_InitialCondition[0], 10U * sizeof
         (real_T));

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: x' */
  Lab3_IMU_Encoder_comp_DW.RateTransitionx_Buffer0 =
    Lab3_IMU_Encoder_comp_P.RateTransitionx_InitialConditio;

  /* InitializeConditions for RateTransition: '<S4>/Rate Transition: y' */
  Lab3_IMU_Encoder_comp_DW.RateTransitiony_Buffer0 =
    Lab3_IMU_Encoder_comp_P.RateTransitiony_InitialConditio;
}

/* Model terminate function */
void Lab3_IMU_Encoder_comp_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab3_IMU_Encoder_comp/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages =
          &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab3_IMU_Encoder_comp_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab3_IMU_Encoder_comp_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_IMU_Encoder_comp_P.HILInitialize_POFinal;
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
      result = hil_write(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card
                         , Lab3_IMU_Encoder_comp_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0]
                         , &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
             Lab3_IMU_Encoder_comp_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm
            (Lab3_IMU_Encoder_comp_DW.HILInitialize_Card,
             Lab3_IMU_Encoder_comp_P.HILInitialize_POChannels,
             num_final_pwm_outputs,
             &Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    hil_close(Lab3_IMU_Encoder_comp_DW.HILInitialize_Card);
    Lab3_IMU_Encoder_comp_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for S-Function (stream_call_block): '<S7>/Stream Call1' incorporates:
   *  Constant: '<S7>/Constant'
   *  S-Function (string_constant_block): '<S7>/String Constant'
   */

  /* S-Function Block: Lab3_IMU_Encoder_comp/IMU/IMU/Stream Call1 (stream_call_block) */
  {
    if (Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream != NULL) {
      stream_close(Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream);
      Lab3_IMU_Encoder_comp_DW.StreamCall1_Stream = NULL;
    }
  }

  /* Terminate for ToFile: '<Root>/To File' */
  {
    FILE *fp = (FILE *) Lab3_IMU_Encoder_comp_DW.ToFile_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "p3Run.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                          "Error closing MAT-file p3Run.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                          "Error reopening MAT-file p3Run.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 21 + 1,
           Lab3_IMU_Encoder_comp_DW.ToFile_IWORK.Count, "ans")) {
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                          "Error writing header for ans to MAT-file p3Run.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_IMU_Encoder_comp_M,
                          "Error closing MAT-file p3Run.mat");
        return;
      }

      Lab3_IMU_Encoder_comp_DW.ToFile_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (game_controller_block): '<S4>/Game Controller' */

  /* S-Function Block: Lab3_IMU_Encoder_comp/Joystick/Game Controller (game_controller_block) */
  {
    if (Lab3_IMU_Encoder_comp_P.GameController_Enabled) {
      game_controller_close(Lab3_IMU_Encoder_comp_DW.GameController_Controller);
      Lab3_IMU_Encoder_comp_DW.GameController_Controller = NULL;
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
  Lab3_IMU_Encoder_comp_output(tid);
}

void MdlUpdate(int_T tid)
{
  if (tid == 1)
    tid = 0;
  Lab3_IMU_Encoder_comp_update(tid);
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
  Lab3_IMU_Encoder_comp_initialize();
}

void MdlTerminate(void)
{
  Lab3_IMU_Encoder_comp_terminate();
}

/* Registration function */
RT_MODEL_Lab3_IMU_Encoder_com_T *Lab3_IMU_Encoder_comp(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Lab3_IMU_Encoder_comp_M, 0,
                sizeof(RT_MODEL_Lab3_IMU_Encoder_com_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
                          &Lab3_IMU_Encoder_comp_M->Timing.simTimeStep);
    rtsiSetTPtr(&Lab3_IMU_Encoder_comp_M->solverInfo, &rtmGetTPtr
                (Lab3_IMU_Encoder_comp_M));
    rtsiSetStepSizePtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
                       &Lab3_IMU_Encoder_comp_M->Timing.stepSize0);
    rtsiSetdXPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
                 &Lab3_IMU_Encoder_comp_M->derivs);
    rtsiSetContStatesPtr(&Lab3_IMU_Encoder_comp_M->solverInfo, (real_T **)
                         &Lab3_IMU_Encoder_comp_M->contStates);
    rtsiSetNumContStatesPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
      &Lab3_IMU_Encoder_comp_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
      &Lab3_IMU_Encoder_comp_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
      &Lab3_IMU_Encoder_comp_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
      &Lab3_IMU_Encoder_comp_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
                          (&rtmGetErrorStatus(Lab3_IMU_Encoder_comp_M)));
    rtsiSetRTModelPtr(&Lab3_IMU_Encoder_comp_M->solverInfo,
                      Lab3_IMU_Encoder_comp_M);
  }

  rtsiSetSimTimeStep(&Lab3_IMU_Encoder_comp_M->solverInfo, MAJOR_TIME_STEP);
  Lab3_IMU_Encoder_comp_M->intgData.f[0] = Lab3_IMU_Encoder_comp_M->odeF[0];
  Lab3_IMU_Encoder_comp_M->contStates = ((real_T *) &Lab3_IMU_Encoder_comp_X);
  rtsiSetSolverData(&Lab3_IMU_Encoder_comp_M->solverInfo, (void *)
                    &Lab3_IMU_Encoder_comp_M->intgData);
  rtsiSetSolverName(&Lab3_IMU_Encoder_comp_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab3_IMU_Encoder_comp_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    Lab3_IMU_Encoder_comp_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab3_IMU_Encoder_comp_M->Timing.sampleTimes =
      (&Lab3_IMU_Encoder_comp_M->Timing.sampleTimesArray[0]);
    Lab3_IMU_Encoder_comp_M->Timing.offsetTimes =
      (&Lab3_IMU_Encoder_comp_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab3_IMU_Encoder_comp_M->Timing.sampleTimes[0] = (0.0);
    Lab3_IMU_Encoder_comp_M->Timing.sampleTimes[1] = (0.002);
    Lab3_IMU_Encoder_comp_M->Timing.sampleTimes[2] = (0.01);

    /* task offsets */
    Lab3_IMU_Encoder_comp_M->Timing.offsetTimes[0] = (0.0);
    Lab3_IMU_Encoder_comp_M->Timing.offsetTimes[1] = (0.0);
    Lab3_IMU_Encoder_comp_M->Timing.offsetTimes[2] = (0.0);
  }

  rtmSetTPtr(Lab3_IMU_Encoder_comp_M, &Lab3_IMU_Encoder_comp_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab3_IMU_Encoder_comp_M->Timing.sampleHitArray;
    int_T *mdlPerTaskSampleHits =
      Lab3_IMU_Encoder_comp_M->Timing.perTaskSampleHitsArray;
    Lab3_IMU_Encoder_comp_M->Timing.perTaskSampleHits = (&mdlPerTaskSampleHits[0]);
    mdlSampleHits[0] = 1;
    Lab3_IMU_Encoder_comp_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab3_IMU_Encoder_comp_M, -1);
  Lab3_IMU_Encoder_comp_M->Timing.stepSize0 = 0.002;
  Lab3_IMU_Encoder_comp_M->Timing.stepSize1 = 0.002;
  Lab3_IMU_Encoder_comp_M->Timing.stepSize2 = 0.01;

  /* External mode info */
  Lab3_IMU_Encoder_comp_M->Sizes.checksums[0] = (241584936U);
  Lab3_IMU_Encoder_comp_M->Sizes.checksums[1] = (2377646479U);
  Lab3_IMU_Encoder_comp_M->Sizes.checksums[2] = (1291162109U);
  Lab3_IMU_Encoder_comp_M->Sizes.checksums[3] = (2421960728U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    Lab3_IMU_Encoder_comp_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab3_IMU_Encoder_comp_M->extModeInfo,
      &Lab3_IMU_Encoder_comp_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab3_IMU_Encoder_comp_M->extModeInfo,
                        Lab3_IMU_Encoder_comp_M->Sizes.checksums);
    rteiSetTPtr(Lab3_IMU_Encoder_comp_M->extModeInfo, rtmGetTPtr
                (Lab3_IMU_Encoder_comp_M));
  }

  Lab3_IMU_Encoder_comp_M->solverInfoPtr = (&Lab3_IMU_Encoder_comp_M->solverInfo);
  Lab3_IMU_Encoder_comp_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Lab3_IMU_Encoder_comp_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Lab3_IMU_Encoder_comp_M->solverInfo,
                    SOLVER_MODE_MULTITASKING);

  /* block I/O */
  Lab3_IMU_Encoder_comp_M->blockIO = ((void *) &Lab3_IMU_Encoder_comp_B);
  (void) memset(((void *) &Lab3_IMU_Encoder_comp_B), 0,
                sizeof(B_Lab3_IMU_Encoder_comp_T));

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      Lab3_IMU_Encoder_comp_B.Switch[i] = 0.0;
    }

    for (i = 0; i < 21; i++) {
      Lab3_IMU_Encoder_comp_B.TmpSignalConversionAtToFileInpo[i] = 0.0;
    }

    Lab3_IMU_Encoder_comp_B.TravelCounttorad = 0.0;
    Lab3_IMU_Encoder_comp_B.TravelTransferFcn = 0.0;
    Lab3_IMU_Encoder_comp_B.PitchCounttorad = 0.0;
    Lab3_IMU_Encoder_comp_B.PitchTransferFcn = 0.0;
    Lab3_IMU_Encoder_comp_B.ElevationCounttorad = 0.0;
    Lab3_IMU_Encoder_comp_B.ElevationTransferFcn = 0.0;
    Lab3_IMU_Encoder_comp_B.Gain1[0] = 0.0;
    Lab3_IMU_Encoder_comp_B.Gain1[1] = 0.0;
    Lab3_IMU_Encoder_comp_B.Gain1[2] = 0.0;
    Lab3_IMU_Encoder_comp_B.Gain2[0] = 0.0;
    Lab3_IMU_Encoder_comp_B.Gain2[1] = 0.0;
    Lab3_IMU_Encoder_comp_B.Gain2[2] = 0.0;
    Lab3_IMU_Encoder_comp_B.DataTypeConversion = 0.0;
    Lab3_IMU_Encoder_comp_B.RateTransitionx = 0.0;
    Lab3_IMU_Encoder_comp_B.Joystick_gain_x = 0.0;
    Lab3_IMU_Encoder_comp_B.RateTransitiony = 0.0;
    Lab3_IMU_Encoder_comp_B.Joystick_gain_y = 0.0;
    Lab3_IMU_Encoder_comp_B.euler_rates[0] = 0.0;
    Lab3_IMU_Encoder_comp_B.euler_rates[1] = 0.0;
    Lab3_IMU_Encoder_comp_B.euler_rates[2] = 0.0;
  }

  /* parameters */
  Lab3_IMU_Encoder_comp_M->defaultParam = ((real_T *)&Lab3_IMU_Encoder_comp_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Lab3_IMU_Encoder_comp_X;
    Lab3_IMU_Encoder_comp_M->contStates = (x);
    (void) memset((void *)&Lab3_IMU_Encoder_comp_X, 0,
                  sizeof(X_Lab3_IMU_Encoder_comp_T));
  }

  /* states (dwork) */
  Lab3_IMU_Encoder_comp_M->dwork = ((void *) &Lab3_IMU_Encoder_comp_DW);
  (void) memset((void *)&Lab3_IMU_Encoder_comp_DW, 0,
                sizeof(DW_Lab3_IMU_Encoder_comp_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_IMU_Encoder_comp_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      Lab3_IMU_Encoder_comp_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_Buffer[0] = 0.0;
  Lab3_IMU_Encoder_comp_DW.HILWriteAnalog_Buffer[1] = 0.0;
  Lab3_IMU_Encoder_comp_DW.RateTransitionx_Buffer0 = 0.0;
  Lab3_IMU_Encoder_comp_DW.RateTransitiony_Buffer0 = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab3_IMU_Encoder_comp_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 25;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab3_IMU_Encoder_comp_M->Sizes.numContStates = (3);/* Number of continuous states */
  Lab3_IMU_Encoder_comp_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Lab3_IMU_Encoder_comp_M->Sizes.numY = (0);/* Number of model outputs */
  Lab3_IMU_Encoder_comp_M->Sizes.numU = (0);/* Number of model inputs */
  Lab3_IMU_Encoder_comp_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab3_IMU_Encoder_comp_M->Sizes.numSampTimes = (3);/* Number of sample times */
  Lab3_IMU_Encoder_comp_M->Sizes.numBlocks = (60);/* Number of blocks */
  Lab3_IMU_Encoder_comp_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  Lab3_IMU_Encoder_comp_M->Sizes.numBlockPrms = (428);/* Sum of parameter "widths" */
  return Lab3_IMU_Encoder_comp_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
