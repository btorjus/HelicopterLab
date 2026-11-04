/*
 * heli_p4_kalman_kf_r2020b_private.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "heli_p4_kalman_kf_r2020b".
 *
 * Model version              : 11.0
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Wed Nov  4 16:27:22 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_heli_p4_kalman_kf_r2020b_private_h_
#define RTW_HEADER_heli_p4_kalman_kf_r2020b_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"
#include "heli_p4_kalman_kf_r2020b.h"

/* Used by FromWorkspace Block: '<Root>/From Workspace' */
#ifndef rtInterpolate
# define rtInterpolate(v1,v2,f1,f2)    (((v1)==(v2))?((double)(v1)): (((f1)*((double)(v1)))+((f2)*((double)(v2)))))
#endif

#ifndef rtRound
# define rtRound(v)                    ( ((v) >= 0) ? floor((v) + 0.5) : ceil((v) - 0.5) )
#endif

extern t_stream heli_p4_kalman_kf_r2020b_rtZt_stream;

/* A global buffer for storing error messages (defined in quanser_common library) */
EXTERN char _rt_error_message[512];
extern real_T rt_atan2d_snf(real_T u0, real_T u1);
int_T rt_WriteMat4FileHeader(FILE *fp,
  int32_T m,
  int32_T n,
  const char_T *name);
void heli_p4_kalman_kf_r2020b_output0(void);
void heli_p4_kalman_kf_r2020b_update0(void);
void heli_p4_kalman_kf_r2020b_output2(void);
void heli_p4_kalman_kf_r2020b_update2(void);/* private model entry point functions */
extern void heli_p4_kalman_kf_r2020b_derivatives(void);

#endif                      /* RTW_HEADER_heli_p4_kalman_kf_r2020b_private_h_ */
