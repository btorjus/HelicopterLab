/*
 * Lab3_IMU_LQRI_private.h
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

#ifndef RTW_HEADER_Lab3_IMU_LQRI_private_h_
#define RTW_HEADER_Lab3_IMU_LQRI_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "Lab3_IMU_LQRI.h"

/* Used by FromWorkspace Block: '<Root>/From Workspace' */
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? floor((v) + 0.5) : ceil((v) - 0.5) )
#endif

extern t_stream Lab3_IMU_LQRI_rtZt_stream;

/* A global buffer for storing error messages (defined in quanser_common library) */
EXTERN char _rt_error_message[512];
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
int_T rt_WriteMat4FileHeader(FILE *fp,
  int32_T m,
  int32_T n,
  const char_T *name);
void Lab3_IMU_LQRI_output0(void);
void Lab3_IMU_LQRI_update0(void);
void Lab3_IMU_LQRI_output2(void);
void Lab3_IMU_LQRI_update2(void);      /* private model entry point functions */
extern void Lab3_IMU_LQRI_derivatives(void);

#endif                                 /* RTW_HEADER_Lab3_IMU_LQRI_private_h_ */
