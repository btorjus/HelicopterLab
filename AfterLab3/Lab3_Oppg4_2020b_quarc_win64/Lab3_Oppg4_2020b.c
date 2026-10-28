/*
 * Lab3_Oppg4_2020b.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Lab3_Oppg4_2020b".
 *
 * Model version              : 11.1
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Oct 14 16:07:03 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Lab3_Oppg4_2020b.h"
#include "Lab3_Oppg4_2020b_private.h"
#include "Lab3_Oppg4_2020b_dt.h"

t_stream Lab3_Oppg4_2020b_rtZt_stream = NULL;

/* Block signals (default storage) */
B_Lab3_Oppg4_2020b_T Lab3_Oppg4_2020b_B;

/* Continuous states */
X_Lab3_Oppg4_2020b_T Lab3_Oppg4_2020b_X;

/* Block states (default storage) */
DW_Lab3_Oppg4_2020b_T Lab3_Oppg4_2020b_DW;

/* Real-time model */
static RT_MODEL_Lab3_Oppg4_2020b_T Lab3_Oppg4_2020b_M_;
RT_MODEL_Lab3_Oppg4_2020b_T *const Lab3_Oppg4_2020b_M = &Lab3_Oppg4_2020b_M_;

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
  Lab3_Oppg4_2020b_derivatives();
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

/* Model output function */
void Lab3_Oppg4_2020b_output(void)
{
  /* local block i/o variables */
  t_stream_ptr rtb_StreamCall1_o1;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_TmpSignalConversionAtHeli3D[6];
  real_T rtb_BackmotorSaturation;
  real_T rtb_FrontmotorSaturation;
  real32_T rtb_StreamRead1_o2[10];
  int32_T rtb_StreamFormattedWrite_o2;
  int32_T rtb_StreamCall1_o3;
  boolean_T rtb_StreamRead1_o3;
  real_T tmp[9];
  real_T rtb_Gain2[3];
  real_T euler_rates_tmp;
  real_T euler_rates_tmp_0;
  real_T euler_rates_tmp_1;
  real_T euler_rates_tmp_2;
  int32_T i;
  if (rtmIsMajorTimeStep(Lab3_Oppg4_2020b_M)) {
    /* set solver stop time */
    if (!(Lab3_Oppg4_2020b_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Lab3_Oppg4_2020b_M->solverInfo,
                            ((Lab3_Oppg4_2020b_M->Timing.clockTickH0 + 1) *
        Lab3_Oppg4_2020b_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Lab3_Oppg4_2020b_M->solverInfo,
                            ((Lab3_Oppg4_2020b_M->Timing.clockTick0 + 1) *
        Lab3_Oppg4_2020b_M->Timing.stepSize0 +
        Lab3_Oppg4_2020b_M->Timing.clockTickH0 *
        Lab3_Oppg4_2020b_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Lab3_Oppg4_2020b_M)) {
    Lab3_Oppg4_2020b_M->Timing.t[0] = rtsiGetT(&Lab3_Oppg4_2020b_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(Lab3_Oppg4_2020b_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

    /* S-Function Block: Lab3_Oppg4_2020b/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Task, 1,
         &Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_BackmotorSaturation =
          Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_FrontmotorSaturation =
          Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S3>/Travel: Count to rad' */
    Lab3_Oppg4_2020b_B.TravelCounttorad =
      Lab3_Oppg4_2020b_P.TravelCounttorad_Gain * rtb_HILReadEncoderTimebase_o1;

    /* Gain: '<S3>/Pitch: Count to rad' */
    Lab3_Oppg4_2020b_B.PitchCounttorad = Lab3_Oppg4_2020b_P.PitchCounttorad_Gain
      * rtb_BackmotorSaturation;
  }

  /* TransferFcn: '<S3>/Travel: Transfer Fcn' */
  Lab3_Oppg4_2020b_B.TravelTransferFcn = 0.0;
  Lab3_Oppg4_2020b_B.TravelTransferFcn += Lab3_Oppg4_2020b_P.TravelTransferFcn_C
    * Lab3_Oppg4_2020b_X.TravelTransferFcn_CSTATE;
  Lab3_Oppg4_2020b_B.TravelTransferFcn += Lab3_Oppg4_2020b_P.TravelTransferFcn_D
    * Lab3_Oppg4_2020b_B.TravelCounttorad;

  /* TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  Lab3_Oppg4_2020b_B.PitchTransferFcn = 0.0;
  Lab3_Oppg4_2020b_B.PitchTransferFcn += Lab3_Oppg4_2020b_P.PitchTransferFcn_C *
    Lab3_Oppg4_2020b_X.PitchTransferFcn_CSTATE;
  Lab3_Oppg4_2020b_B.PitchTransferFcn += Lab3_Oppg4_2020b_P.PitchTransferFcn_D *
    Lab3_Oppg4_2020b_B.PitchCounttorad;
  if (rtmIsMajorTimeStep(Lab3_Oppg4_2020b_M)) {
    /* Gain: '<S3>/Elevation: Count to rad' */
    Lab3_Oppg4_2020b_B.ElevationCounttorad =
      Lab3_Oppg4_2020b_P.ElevationCounttorad_Gain * rtb_FrontmotorSaturation;
  }

  /* TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  Lab3_Oppg4_2020b_B.ElevationTransferFcn = 0.0;
  Lab3_Oppg4_2020b_B.ElevationTransferFcn +=
    Lab3_Oppg4_2020b_P.ElevationTransferFcn_C *
    Lab3_Oppg4_2020b_X.ElevationTransferFcn_CSTATE;
  Lab3_Oppg4_2020b_B.ElevationTransferFcn +=
    Lab3_Oppg4_2020b_P.ElevationTransferFcn_D *
    Lab3_Oppg4_2020b_B.ElevationCounttorad;
  if (rtmIsMajorTimeStep(Lab3_Oppg4_2020b_M)) {
    /* SignalConversion generated from: '<Root>/Heli3DLog' */
    rtb_TmpSignalConversionAtHeli3D[0] = Lab3_Oppg4_2020b_B.TravelCounttorad;
    rtb_TmpSignalConversionAtHeli3D[1] = Lab3_Oppg4_2020b_B.TravelTransferFcn;
    rtb_TmpSignalConversionAtHeli3D[2] = Lab3_Oppg4_2020b_B.PitchCounttorad;
    rtb_TmpSignalConversionAtHeli3D[3] = Lab3_Oppg4_2020b_B.PitchTransferFcn;
    rtb_TmpSignalConversionAtHeli3D[4] = Lab3_Oppg4_2020b_B.ElevationCounttorad;
    rtb_TmpSignalConversionAtHeli3D[5] = Lab3_Oppg4_2020b_B.ElevationTransferFcn;

    /* ToFile: '<Root>/Heli3DLog' */
    {
      if (!(++Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Decimation % 1) &&
          (Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Count * (6 + 1)) + 1 < 100000000 )
      {
        FILE *fp = (FILE *) Lab3_Oppg4_2020b_DW.Heli3DLog_PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Decimation = 0;
          u[0] = Lab3_Oppg4_2020b_M->Timing.t[1];
          u[1] = rtb_TmpSignalConversionAtHeli3D[0];
          u[2] = rtb_TmpSignalConversionAtHeli3D[1];
          u[3] = rtb_TmpSignalConversionAtHeli3D[2];
          u[4] = rtb_TmpSignalConversionAtHeli3D[3];
          u[5] = rtb_TmpSignalConversionAtHeli3D[4];
          u[6] = rtb_TmpSignalConversionAtHeli3D[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                              "Error writing to MAT-file Heli3D.mat");
            return;
          }

          if (((++Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Count) * (6 + 1))+1 >=
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

    /* S-Function (stream_call_block): '<S4>/Stream Call1' incorporates:
     *  Constant: '<S4>/Constant'
     *  S-Function (string_constant_block): '<S4>/String Constant'
     */

    /* S-Function Block: Lab3_Oppg4_2020b/IMU/Stream Call1 (stream_call_block) */
    {
      t_error result = 0;
      t_boolean close_flag = (Lab3_Oppg4_2020b_P.Constant_Value != 0);
      rtb_StreamCall1_o1 = NULL;
      switch (Lab3_Oppg4_2020b_DW.StreamCall1_State) {
       case STREAM_CALL_STATE_NOT_CONNECTED:
        {
          if (!close_flag) {
            /* Make sure URI is null-terminated */
            if (string_length((char *) Lab3_Oppg4_2020b_P.StringConstant_Value,
                              255) == 255) {
              rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                                "URI passed to Stream Call block is not null-terminated!");
              result = -QERR_STRING_NOT_TERMINATED;
            } else {
              result = stream_connect((char *)
                Lab3_Oppg4_2020b_P.StringConstant_Value,
                Lab3_Oppg4_2020b_P.StreamCall1_NonBlocking != 0,
                Lab3_Oppg4_2020b_P.StreamCall1_SendBufferSize,
                Lab3_Oppg4_2020b_P.StreamCall1_ReceiveBufferSize,
                &Lab3_Oppg4_2020b_DW.StreamCall1_Stream);
              if (result == 0) {
                Lab3_Oppg4_2020b_DW.StreamCall1_State =
                  STREAM_CALL_STATE_CONNECTED;
                stream_set_byte_order(Lab3_Oppg4_2020b_DW.StreamCall1_Stream,
                                      (t_stream_byte_order)
                                      Lab3_Oppg4_2020b_P.StreamCall1_Endian);
                rtb_StreamCall1_o1 = &Lab3_Oppg4_2020b_DW.StreamCall1_Stream;
              } else if (result == -QERR_WOULD_BLOCK) {
                Lab3_Oppg4_2020b_DW.StreamCall1_State =
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

            result = stream_poll(Lab3_Oppg4_2020b_DW.StreamCall1_Stream,
                                 &timeout, STREAM_POLL_CONNECT);
            if (result > 0) {
              Lab3_Oppg4_2020b_DW.StreamCall1_State =
                STREAM_CALL_STATE_CONNECTED;
              stream_set_byte_order(Lab3_Oppg4_2020b_DW.StreamCall1_Stream,
                                    (t_stream_byte_order)
                                    Lab3_Oppg4_2020b_P.StreamCall1_Endian);
              rtb_StreamCall1_o1 = &Lab3_Oppg4_2020b_DW.StreamCall1_Stream;
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
          rtb_StreamCall1_o1 = &Lab3_Oppg4_2020b_DW.StreamCall1_Stream;
          if (!close_flag) {
            break;
          }

          /* Fall through deliberately */
        }

       default:
        {
          t_error close_result = stream_close
            (Lab3_Oppg4_2020b_DW.StreamCall1_Stream);
          if (close_result == 0) {
            Lab3_Oppg4_2020b_DW.StreamCall1_State =
              STREAM_CALL_STATE_NOT_CONNECTED;
            Lab3_Oppg4_2020b_DW.StreamCall1_Stream = NULL;
            rtb_StreamCall1_o1 = NULL;
          } else if (result == 0) {
            result = close_result;
          }
          break;
        }
      }

      Lab3_Oppg4_2020b_B.StreamCall1_o2 = Lab3_Oppg4_2020b_DW.StreamCall1_State;
      rtb_StreamCall1_o3 = (int32_T) result;
    }

    /* S-Function (stream_formatted_write_block): '<S4>/Stream Formatted Write' incorporates:
     *  Constant: '<S4>/Constant1'
     */
    {
      t_error result;
      if (rtb_StreamCall1_o1 != NULL) {
        result = stream_print_utf8_char_array(*rtb_StreamCall1_o1,
          Lab3_Oppg4_2020b_P.StreamFormattedWrite_MaxUnits,
          &rtb_StreamFormattedWrite_o2, "%c\n"
          , (char) Lab3_Oppg4_2020b_P.Constant1_Value
          );
        if (result > 0) {
          result = stream_flush(*rtb_StreamCall1_o1);
        }

        if (result == -QERR_WOULD_BLOCK) {
          result = 0;
        }
      }
    }

    /* S-Function (stream_read_block): '<S4>/Stream Read1' incorporates:
     *  Constant: '<S4>/Constant1'
     *  S-Function (stream_call_block): '<S4>/Stream Call1'
     *  S-Function (stream_formatted_write_block): '<S4>/Stream Formatted Write'
     */

    /* S-Function Block: Lab3_Oppg4_2020b/IMU/Stream Read1 (stream_read_block) */
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
      /* Switch: '<S4>/Switch' */
      if (rtb_StreamRead1_o3) {
        /* Switch: '<S4>/Switch' incorporates:
         *  DataTypeConversion: '<S4>/Data Type Conversion'
         */
        Lab3_Oppg4_2020b_B.Switch[i] = rtb_StreamRead1_o2[i];
      } else {
        /* Switch: '<S4>/Switch' incorporates:
         *  Memory: '<S4>/Memory'
         */
        Lab3_Oppg4_2020b_B.Switch[i] =
          Lab3_Oppg4_2020b_DW.Memory_PreviousInput[i];
      }

      /* End of Switch: '<S4>/Switch' */
    }

    /* Gain: '<S4>/Gain2' */
    for (i = 0; i < 3; i++) {
      rtb_Gain2[i] = Lab3_Oppg4_2020b_P.Gain2_Gain[i + 6] *
        Lab3_Oppg4_2020b_B.Switch[2] + (Lab3_Oppg4_2020b_P.Gain2_Gain[i + 3] *
        Lab3_Oppg4_2020b_B.Switch[1] + Lab3_Oppg4_2020b_P.Gain2_Gain[i] *
        Lab3_Oppg4_2020b_B.Switch[0]);
    }

    /* End of Gain: '<S4>/Gain2' */

    /* MATLAB Function: '<Root>/Acc til ang' */
    /* MATLAB Function 'Acc til ang': '<S1>:1' */
    /* '<S1>:1:2' */
    /* '<S1>:1:3' */
    /* '<S1>:1:4' */
    /* '<S1>:1:5' */
    Lab3_Oppg4_2020b_B.angles[0] = rt_atan2d_snf(rtb_Gain2[1], rtb_Gain2[2]);
    Lab3_Oppg4_2020b_B.angles[1] = rt_atan2d_snf(rtb_Gain2[0], sqrt(rtb_Gain2[1]
      * rtb_Gain2[1] + rtb_Gain2[2] * rtb_Gain2[2]));

    /* MATLAB Function: '<Root>/Gyro vector to [pitch rate, elevation rate, travle rate]' */
    /* MATLAB Function 'Gyro vector to [pitch rate, elevation rate, travle rate]': '<S2>:1' */
    /* '<S2>:1:3' */
    /* '<S2>:1:4' */
    /* '<S2>:1:10' */
    /* '<S2>:1:14' */
    euler_rates_tmp = tan(Lab3_Oppg4_2020b_B.angles[1]);
    euler_rates_tmp_0 = sin(Lab3_Oppg4_2020b_B.angles[0]);
    euler_rates_tmp_1 = cos(Lab3_Oppg4_2020b_B.angles[0]);
    euler_rates_tmp_2 = cos(Lab3_Oppg4_2020b_B.angles[1]);
    tmp[0] = 1.0;
    tmp[3] = euler_rates_tmp_0 * euler_rates_tmp;
    tmp[6] = euler_rates_tmp_1 * euler_rates_tmp;
    tmp[1] = 0.0;
    tmp[4] = euler_rates_tmp_1;
    tmp[7] = -euler_rates_tmp_0;
    tmp[2] = 0.0;
    tmp[5] = euler_rates_tmp_0 / euler_rates_tmp_2;
    tmp[8] = euler_rates_tmp_1 / euler_rates_tmp_2;

    /* Gain: '<S4>/Gain1' */
    for (i = 0; i < 3; i++) {
      rtb_Gain2[i] = Lab3_Oppg4_2020b_P.Gain1_Gain[i + 6] *
        Lab3_Oppg4_2020b_B.Switch[5] + (Lab3_Oppg4_2020b_P.Gain1_Gain[i + 3] *
        Lab3_Oppg4_2020b_B.Switch[4] + Lab3_Oppg4_2020b_P.Gain1_Gain[i] *
        Lab3_Oppg4_2020b_B.Switch[3]);
    }

    /* End of Gain: '<S4>/Gain1' */

    /* MATLAB Function: '<Root>/Gyro vector to [pitch rate, elevation rate, travle rate]' */
    for (i = 0; i < 3; i++) {
      Lab3_Oppg4_2020b_B.euler_rates[i] = 0.0;
      Lab3_Oppg4_2020b_B.euler_rates[i] += tmp[i] * rtb_Gain2[0];
      Lab3_Oppg4_2020b_B.euler_rates[i] += tmp[i + 3] * rtb_Gain2[1];
      Lab3_Oppg4_2020b_B.euler_rates[i] += tmp[i + 6] * rtb_Gain2[2];
    }

    /* Saturate: '<S3>/Front motor: Saturation' */
    if (0.0 > Lab3_Oppg4_2020b_P.FrontmotorSaturation_UpperSat) {
      /* Saturate: '<S3>/Front motor: Saturation' */
      rtb_FrontmotorSaturation =
        Lab3_Oppg4_2020b_P.FrontmotorSaturation_UpperSat;
    } else if (0.0 < Lab3_Oppg4_2020b_P.FrontmotorSaturation_LowerSat) {
      /* Saturate: '<S3>/Front motor: Saturation' */
      rtb_FrontmotorSaturation =
        Lab3_Oppg4_2020b_P.FrontmotorSaturation_LowerSat;
    } else {
      /* Saturate: '<S3>/Front motor: Saturation' */
      rtb_FrontmotorSaturation = 0.0;
    }

    /* End of Saturate: '<S3>/Front motor: Saturation' */

    /* Saturate: '<S3>/Back motor: Saturation' */
    if (0.0 > Lab3_Oppg4_2020b_P.BackmotorSaturation_UpperSat) {
      /* Saturate: '<S3>/Back motor: Saturation' */
      rtb_BackmotorSaturation = Lab3_Oppg4_2020b_P.BackmotorSaturation_UpperSat;
    } else if (0.0 < Lab3_Oppg4_2020b_P.BackmotorSaturation_LowerSat) {
      /* Saturate: '<S3>/Back motor: Saturation' */
      rtb_BackmotorSaturation = Lab3_Oppg4_2020b_P.BackmotorSaturation_LowerSat;
    } else {
      /* Saturate: '<S3>/Back motor: Saturation' */
      rtb_BackmotorSaturation = 0.0;
    }

    /* End of Saturate: '<S3>/Back motor: Saturation' */

    /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

    /* S-Function Block: Lab3_Oppg4_2020b/Heli 3D/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      Lab3_Oppg4_2020b_DW.HILWriteAnalog_Buffer[0] = rtb_FrontmotorSaturation;
      Lab3_Oppg4_2020b_DW.HILWriteAnalog_Buffer[1] = rtb_BackmotorSaturation;
      result = hil_write_analog(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILWriteAnalog_channels, 2,
        &Lab3_Oppg4_2020b_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
      }
    }

    /* S-Function (stop_with_error_block): '<S4>/Stop with Call Error' */

    /* S-Function Block: Lab3_Oppg4_2020b/IMU/Stop with Call Error (stop_with_error_block) */
    {
      if (rtb_StreamCall1_o3 < 0) {
        msg_get_error_messageA(NULL, rtb_StreamCall1_o3, _rt_error_message,
          sizeof(_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }
  }
}

/* Model update function */
void Lab3_Oppg4_2020b_update(void)
{
  if (rtmIsMajorTimeStep(Lab3_Oppg4_2020b_M)) {
    /* Update for Memory: '<S4>/Memory' */
    memcpy(&Lab3_Oppg4_2020b_DW.Memory_PreviousInput[0],
           &Lab3_Oppg4_2020b_B.Switch[0], 10U * sizeof(real_T));
  }

  if (rtmIsMajorTimeStep(Lab3_Oppg4_2020b_M)) {
    rt_ertODEUpdateContinuousStates(&Lab3_Oppg4_2020b_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++Lab3_Oppg4_2020b_M->Timing.clockTick0)) {
    ++Lab3_Oppg4_2020b_M->Timing.clockTickH0;
  }

  Lab3_Oppg4_2020b_M->Timing.t[0] = rtsiGetSolverStopTime
    (&Lab3_Oppg4_2020b_M->solverInfo);

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
    if (!(++Lab3_Oppg4_2020b_M->Timing.clockTick1)) {
      ++Lab3_Oppg4_2020b_M->Timing.clockTickH1;
    }

    Lab3_Oppg4_2020b_M->Timing.t[1] = Lab3_Oppg4_2020b_M->Timing.clockTick1 *
      Lab3_Oppg4_2020b_M->Timing.stepSize1 +
      Lab3_Oppg4_2020b_M->Timing.clockTickH1 *
      Lab3_Oppg4_2020b_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void Lab3_Oppg4_2020b_derivatives(void)
{
  XDot_Lab3_Oppg4_2020b_T *_rtXdot;
  _rtXdot = ((XDot_Lab3_Oppg4_2020b_T *) Lab3_Oppg4_2020b_M->derivs);

  /* Derivatives for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += Lab3_Oppg4_2020b_P.TravelTransferFcn_A *
    Lab3_Oppg4_2020b_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += Lab3_Oppg4_2020b_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += Lab3_Oppg4_2020b_P.PitchTransferFcn_A *
    Lab3_Oppg4_2020b_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += Lab3_Oppg4_2020b_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE +=
    Lab3_Oppg4_2020b_P.ElevationTransferFcn_A *
    Lab3_Oppg4_2020b_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += Lab3_Oppg4_2020b_B.ElevationCounttorad;
}

/* Model initialize function */
void Lab3_Oppg4_2020b_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab3_Oppg4_2020b/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (Lab3_Oppg4_2020b_DW.HILInitialize_Card, "update_rate=normal;decimation=1",
       32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
      return;
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_AIPStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &Lab3_Oppg4_2020b_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (Lab3_Oppg4_2020b_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &Lab3_Oppg4_2020b_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = Lab3_Oppg4_2020b_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges
        (Lab3_Oppg4_2020b_DW.HILInitialize_Card,
         Lab3_Oppg4_2020b_P.HILInitialize_AIChannels, 8U,
         &Lab3_Oppg4_2020b_DW.HILInitialize_AIMinimums[0],
         &Lab3_Oppg4_2020b_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_AOPStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &Lab3_Oppg4_2020b_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (Lab3_Oppg4_2020b_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &Lab3_Oppg4_2020b_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = Lab3_Oppg4_2020b_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges
        (Lab3_Oppg4_2020b_DW.HILInitialize_Card,
         Lab3_Oppg4_2020b_P.HILInitialize_AOChannels, 8U,
         &Lab3_Oppg4_2020b_DW.HILInitialize_AOMinimums[0],
         &Lab3_Oppg4_2020b_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_AOStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_Oppg4_2020b_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILInitialize_AOChannels, 8U,
        &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if (Lab3_Oppg4_2020b_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_Oppg4_2020b_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (Lab3_Oppg4_2020b_DW.HILInitialize_Card,
         Lab3_Oppg4_2020b_P.HILInitialize_AOChannels, 8U,
         &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_EIPStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &Lab3_Oppg4_2020b_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = Lab3_Oppg4_2020b_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (Lab3_Oppg4_2020b_DW.HILInitialize_Card,
         Lab3_Oppg4_2020b_P.HILInitialize_EIChannels, 8U,
         (t_encoder_quadrature_mode *)
         &Lab3_Oppg4_2020b_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_EIStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &Lab3_Oppg4_2020b_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = Lab3_Oppg4_2020b_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILInitialize_EIChannels, 8U,
        &Lab3_Oppg4_2020b_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_POPStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab3_Oppg4_2020b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &Lab3_Oppg4_2020b_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          Lab3_Oppg4_2020b_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues =
          &Lab3_Oppg4_2020b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            Lab3_Oppg4_2020b_DW.HILInitialize_POSortedChans[num_duty_cycle_modes]
              = (p_HILInitialize_POChannels[i1]);
            Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]
              = Lab3_Oppg4_2020b_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            Lab3_Oppg4_2020b_DW.HILInitialize_POSortedChans[7U -
              num_frequency_modes] = (p_HILInitialize_POChannels[i1]);
            Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[7U -
              num_frequency_modes] =
              Lab3_Oppg4_2020b_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
          &Lab3_Oppg4_2020b_DW.HILInitialize_POSortedChans[0],
          num_duty_cycle_modes,
          &Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
          &Lab3_Oppg4_2020b_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues =
          &Lab3_Oppg4_2020b_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &Lab3_Oppg4_2020b_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &Lab3_Oppg4_2020b_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &Lab3_Oppg4_2020b_DW.HILInitialize_POModeValues
        [0],
        (t_pwm_alignment *) &Lab3_Oppg4_2020b_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &Lab3_Oppg4_2020b_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs =
          &Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILInitialize_POChannels, 8U,
        &Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[0],
        &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_POStart && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
        Lab3_Oppg4_2020b_P.HILInitialize_POChannels, 8U,
        &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }

    if (Lab3_Oppg4_2020b_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (Lab3_Oppg4_2020b_DW.HILInitialize_Card,
         Lab3_Oppg4_2020b_P.HILInitialize_POChannels, 8U,
         &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: Lab3_Oppg4_2020b/Heli 3D/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (Lab3_Oppg4_2020b_DW.HILInitialize_Card,
       Lab3_Oppg4_2020b_P.HILReadEncoderTimebase_SamplesI,
       Lab3_Oppg4_2020b_P.HILReadEncoderTimebase_Channels, 3,
       &Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Lab3_Oppg4_2020b_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (Lab3_Oppg4_2020b_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
    }
  }

  /* Start for ToFile: '<Root>/Heli3DLog' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "Heli3D.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                        "Error creating .mat file Heli3D.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                        "Error writing mat file header to file Heli3D.mat");
      return;
    }

    Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Count = 0;
    Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Decimation = -1;
    Lab3_Oppg4_2020b_DW.Heli3DLog_PWORK.FilePtr = fp;
  }

  /* Start for S-Function (stream_call_block): '<S4>/Stream Call1' incorporates:
   *  Constant: '<S4>/Constant'
   *  S-Function (string_constant_block): '<S4>/String Constant'
   */

  /* S-Function Block: Lab3_Oppg4_2020b/IMU/Stream Call1 (stream_call_block) */
  {
    Lab3_Oppg4_2020b_DW.StreamCall1_State = STREAM_CALL_STATE_NOT_CONNECTED;
    Lab3_Oppg4_2020b_DW.StreamCall1_Stream = NULL;
  }

  /* InitializeConditions for TransferFcn: '<S3>/Travel: Transfer Fcn' */
  Lab3_Oppg4_2020b_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Pitch: Transfer Fcn' */
  Lab3_Oppg4_2020b_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S3>/Elevation: Transfer Fcn' */
  Lab3_Oppg4_2020b_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S4>/Memory' */
  memcpy(&Lab3_Oppg4_2020b_DW.Memory_PreviousInput[0],
         &Lab3_Oppg4_2020b_P.Memory_InitialCondition[0], 10U * sizeof(real_T));
}

/* Model terminate function */
void Lab3_Oppg4_2020b_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Lab3_Oppg4_2020b/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    hil_monitor_stop_all(Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    is_switching = false;
    if ((Lab3_Oppg4_2020b_P.HILInitialize_AOTerminate && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = Lab3_Oppg4_2020b_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Lab3_Oppg4_2020b_P.HILInitialize_POTerminate && !is_switching) ||
        (Lab3_Oppg4_2020b_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = Lab3_Oppg4_2020b_P.HILInitialize_POFinal;
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
      result = hil_write(Lab3_Oppg4_2020b_DW.HILInitialize_Card
                         , Lab3_Oppg4_2020b_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , Lab3_Oppg4_2020b_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0]
                         , &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
            Lab3_Oppg4_2020b_P.HILInitialize_AOChannels,
            num_final_analog_outputs,
            &Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(Lab3_Oppg4_2020b_DW.HILInitialize_Card,
            Lab3_Oppg4_2020b_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &Lab3_Oppg4_2020b_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Lab3_Oppg4_2020b_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    hil_monitor_delete_all(Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    hil_close(Lab3_Oppg4_2020b_DW.HILInitialize_Card);
    Lab3_Oppg4_2020b_DW.HILInitialize_Card = NULL;
  }

  /* Terminate for ToFile: '<Root>/Heli3DLog' */
  {
    FILE *fp = (FILE *) Lab3_Oppg4_2020b_DW.Heli3DLog_PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "Heli3D.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                          "Error closing MAT-file Heli3D.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                          "Error reopening MAT-file Heli3D.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1,
           Lab3_Oppg4_2020b_DW.Heli3DLog_IWORK.Count, "ans")) {
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                          "Error writing header for ans to MAT-file Heli3D.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(Lab3_Oppg4_2020b_M,
                          "Error closing MAT-file Heli3D.mat");
        return;
      }

      Lab3_Oppg4_2020b_DW.Heli3DLog_PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for S-Function (stream_call_block): '<S4>/Stream Call1' incorporates:
   *  Constant: '<S4>/Constant'
   *  S-Function (string_constant_block): '<S4>/String Constant'
   */

  /* S-Function Block: Lab3_Oppg4_2020b/IMU/Stream Call1 (stream_call_block) */
  {
    if (Lab3_Oppg4_2020b_DW.StreamCall1_Stream != NULL) {
      stream_close(Lab3_Oppg4_2020b_DW.StreamCall1_Stream);
      Lab3_Oppg4_2020b_DW.StreamCall1_Stream = NULL;
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
  Lab3_Oppg4_2020b_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Lab3_Oppg4_2020b_update();
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
  Lab3_Oppg4_2020b_initialize();
}

void MdlTerminate(void)
{
  Lab3_Oppg4_2020b_terminate();
}

/* Registration function */
RT_MODEL_Lab3_Oppg4_2020b_T *Lab3_Oppg4_2020b(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)Lab3_Oppg4_2020b_M, 0,
                sizeof(RT_MODEL_Lab3_Oppg4_2020b_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Lab3_Oppg4_2020b_M->solverInfo,
                          &Lab3_Oppg4_2020b_M->Timing.simTimeStep);
    rtsiSetTPtr(&Lab3_Oppg4_2020b_M->solverInfo, &rtmGetTPtr(Lab3_Oppg4_2020b_M));
    rtsiSetStepSizePtr(&Lab3_Oppg4_2020b_M->solverInfo,
                       &Lab3_Oppg4_2020b_M->Timing.stepSize0);
    rtsiSetdXPtr(&Lab3_Oppg4_2020b_M->solverInfo, &Lab3_Oppg4_2020b_M->derivs);
    rtsiSetContStatesPtr(&Lab3_Oppg4_2020b_M->solverInfo, (real_T **)
                         &Lab3_Oppg4_2020b_M->contStates);
    rtsiSetNumContStatesPtr(&Lab3_Oppg4_2020b_M->solverInfo,
      &Lab3_Oppg4_2020b_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Lab3_Oppg4_2020b_M->solverInfo,
      &Lab3_Oppg4_2020b_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Lab3_Oppg4_2020b_M->solverInfo,
      &Lab3_Oppg4_2020b_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Lab3_Oppg4_2020b_M->solverInfo,
      &Lab3_Oppg4_2020b_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Lab3_Oppg4_2020b_M->solverInfo, (&rtmGetErrorStatus
      (Lab3_Oppg4_2020b_M)));
    rtsiSetRTModelPtr(&Lab3_Oppg4_2020b_M->solverInfo, Lab3_Oppg4_2020b_M);
  }

  rtsiSetSimTimeStep(&Lab3_Oppg4_2020b_M->solverInfo, MAJOR_TIME_STEP);
  Lab3_Oppg4_2020b_M->intgData.f[0] = Lab3_Oppg4_2020b_M->odeF[0];
  Lab3_Oppg4_2020b_M->contStates = ((real_T *) &Lab3_Oppg4_2020b_X);
  rtsiSetSolverData(&Lab3_Oppg4_2020b_M->solverInfo, (void *)
                    &Lab3_Oppg4_2020b_M->intgData);
  rtsiSetSolverName(&Lab3_Oppg4_2020b_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Lab3_Oppg4_2020b_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    Lab3_Oppg4_2020b_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Lab3_Oppg4_2020b_M->Timing.sampleTimes =
      (&Lab3_Oppg4_2020b_M->Timing.sampleTimesArray[0]);
    Lab3_Oppg4_2020b_M->Timing.offsetTimes =
      (&Lab3_Oppg4_2020b_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Lab3_Oppg4_2020b_M->Timing.sampleTimes[0] = (0.0);
    Lab3_Oppg4_2020b_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    Lab3_Oppg4_2020b_M->Timing.offsetTimes[0] = (0.0);
    Lab3_Oppg4_2020b_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Lab3_Oppg4_2020b_M, &Lab3_Oppg4_2020b_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Lab3_Oppg4_2020b_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Lab3_Oppg4_2020b_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Lab3_Oppg4_2020b_M, -1);
  Lab3_Oppg4_2020b_M->Timing.stepSize0 = 0.002;
  Lab3_Oppg4_2020b_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  Lab3_Oppg4_2020b_M->Sizes.checksums[0] = (2122836360U);
  Lab3_Oppg4_2020b_M->Sizes.checksums[1] = (1768717047U);
  Lab3_Oppg4_2020b_M->Sizes.checksums[2] = (3459314575U);
  Lab3_Oppg4_2020b_M->Sizes.checksums[3] = (2602144071U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[4];
    Lab3_Oppg4_2020b_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Lab3_Oppg4_2020b_M->extModeInfo,
      &Lab3_Oppg4_2020b_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Lab3_Oppg4_2020b_M->extModeInfo,
                        Lab3_Oppg4_2020b_M->Sizes.checksums);
    rteiSetTPtr(Lab3_Oppg4_2020b_M->extModeInfo, rtmGetTPtr(Lab3_Oppg4_2020b_M));
  }

  Lab3_Oppg4_2020b_M->solverInfoPtr = (&Lab3_Oppg4_2020b_M->solverInfo);
  Lab3_Oppg4_2020b_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Lab3_Oppg4_2020b_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Lab3_Oppg4_2020b_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Lab3_Oppg4_2020b_M->blockIO = ((void *) &Lab3_Oppg4_2020b_B);
  (void) memset(((void *) &Lab3_Oppg4_2020b_B), 0,
                sizeof(B_Lab3_Oppg4_2020b_T));

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      Lab3_Oppg4_2020b_B.Switch[i] = 0.0;
    }

    Lab3_Oppg4_2020b_B.TravelCounttorad = 0.0;
    Lab3_Oppg4_2020b_B.TravelTransferFcn = 0.0;
    Lab3_Oppg4_2020b_B.PitchCounttorad = 0.0;
    Lab3_Oppg4_2020b_B.PitchTransferFcn = 0.0;
    Lab3_Oppg4_2020b_B.ElevationCounttorad = 0.0;
    Lab3_Oppg4_2020b_B.ElevationTransferFcn = 0.0;
    Lab3_Oppg4_2020b_B.euler_rates[0] = 0.0;
    Lab3_Oppg4_2020b_B.euler_rates[1] = 0.0;
    Lab3_Oppg4_2020b_B.euler_rates[2] = 0.0;
    Lab3_Oppg4_2020b_B.angles[0] = 0.0;
    Lab3_Oppg4_2020b_B.angles[1] = 0.0;
  }

  /* parameters */
  Lab3_Oppg4_2020b_M->defaultParam = ((real_T *)&Lab3_Oppg4_2020b_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Lab3_Oppg4_2020b_X;
    Lab3_Oppg4_2020b_M->contStates = (x);
    (void) memset((void *)&Lab3_Oppg4_2020b_X, 0,
                  sizeof(X_Lab3_Oppg4_2020b_T));
  }

  /* states (dwork) */
  Lab3_Oppg4_2020b_M->dwork = ((void *) &Lab3_Oppg4_2020b_DW);
  (void) memset((void *)&Lab3_Oppg4_2020b_DW, 0,
                sizeof(DW_Lab3_Oppg4_2020b_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      Lab3_Oppg4_2020b_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 10; i++) {
      Lab3_Oppg4_2020b_DW.Memory_PreviousInput[i] = 0.0;
    }
  }

  Lab3_Oppg4_2020b_DW.HILWriteAnalog_Buffer[0] = 0.0;
  Lab3_Oppg4_2020b_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Lab3_Oppg4_2020b_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 24;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Lab3_Oppg4_2020b_M->Sizes.numContStates = (3);/* Number of continuous states */
  Lab3_Oppg4_2020b_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Lab3_Oppg4_2020b_M->Sizes.numY = (0);/* Number of model outputs */
  Lab3_Oppg4_2020b_M->Sizes.numU = (0);/* Number of model inputs */
  Lab3_Oppg4_2020b_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Lab3_Oppg4_2020b_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Lab3_Oppg4_2020b_M->Sizes.numBlocks = (42);/* Number of blocks */
  Lab3_Oppg4_2020b_M->Sizes.numBlockIO = (10);/* Number of block outputs */
  Lab3_Oppg4_2020b_M->Sizes.numBlockPrms = (412);/* Sum of parameter "widths" */
  return Lab3_Oppg4_2020b_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
