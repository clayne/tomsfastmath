/* TomsFastMath, a fast ISO C bignum library. -- Tom St Denis */
/* SPDX-License-Identifier: Unlicense */
#ifndef TFM_PRE_GEN_MPI_C
#define TFM_DEFINES
#include "fp_mul_comba.c"
#endif

#if defined(TFM_MUL8) && FP_SIZE >= 16
void fp_mul_comba8(const fp_int *A, const fp_int *B, fp_int *C)
{
   fp_digit c0, c1, c2, at[16];

   memcpy(at, A->dp, 8 * sizeof(fp_digit));
   memcpy(at+8, B->dp, 8 * sizeof(fp_digit));
   COMBA_START;

   COMBA_CLEAR;
   /* 0 */
   MULADD(at[0], at[8]);
   COMBA_STORE(C->dp[0]);
   /* 1 */
   COMBA_FORWARD;
   MULADD(at[0], at[9]);   MULADD(at[1], at[8]);
   COMBA_STORE(C->dp[1]);
   /* 2 */
   COMBA_FORWARD;
   MULADD(at[0], at[10]);   MULADD(at[1], at[9]);   MULADD(at[2], at[8]);
   COMBA_STORE(C->dp[2]);
   /* 3 */
   COMBA_FORWARD;
   MULADD(at[0], at[11]);   MULADD(at[1], at[10]);   MULADD(at[2], at[9]);   MULADD(at[3], at[8]);
   COMBA_STORE(C->dp[3]);
   /* 4 */
   COMBA_FORWARD;
   MULADD(at[0], at[12]);   MULADD(at[1], at[11]);   MULADD(at[2], at[10]);   MULADD(at[3], at[9]);   MULADD(at[4], at[8]);
   COMBA_STORE(C->dp[4]);
   /* 5 */
   COMBA_FORWARD;
   MULADD(at[0], at[13]);   MULADD(at[1], at[12]);   MULADD(at[2], at[11]);   MULADD(at[3], at[10]);   MULADD(at[4], at[9]);   MULADD(at[5], at[8]);
   COMBA_STORE(C->dp[5]);
   /* 6 */
   COMBA_FORWARD;
   MULADD(at[0], at[14]);   MULADD(at[1], at[13]);   MULADD(at[2], at[12]);   MULADD(at[3], at[11]);   MULADD(at[4], at[10]);   MULADD(at[5], at[9]);   MULADD(at[6], at[8]);
   COMBA_STORE(C->dp[6]);
   /* 7 */
   COMBA_FORWARD;
   MULADD(at[0], at[15]);   MULADD(at[1], at[14]);   MULADD(at[2], at[13]);   MULADD(at[3], at[12]);   MULADD(at[4], at[11]);   MULADD(at[5], at[10]);   MULADD(at[6], at[9]);   MULADD(at[7], at[8]);
   COMBA_STORE(C->dp[7]);
   /* 8 */
   COMBA_FORWARD;
   MULADD(at[1], at[15]);   MULADD(at[2], at[14]);   MULADD(at[3], at[13]);   MULADD(at[4], at[12]);   MULADD(at[5], at[11]);   MULADD(at[6], at[10]);   MULADD(at[7], at[9]);
   COMBA_STORE(C->dp[8]);
   /* 9 */
   COMBA_FORWARD;
   MULADD(at[2], at[15]);   MULADD(at[3], at[14]);   MULADD(at[4], at[13]);   MULADD(at[5], at[12]);   MULADD(at[6], at[11]);   MULADD(at[7], at[10]);
   COMBA_STORE(C->dp[9]);
   /* 10 */
   COMBA_FORWARD;
   MULADD(at[3], at[15]);   MULADD(at[4], at[14]);   MULADD(at[5], at[13]);   MULADD(at[6], at[12]);   MULADD(at[7], at[11]);
   COMBA_STORE(C->dp[10]);
   /* 11 */
   COMBA_FORWARD;
   MULADD(at[4], at[15]);   MULADD(at[5], at[14]);   MULADD(at[6], at[13]);   MULADD(at[7], at[12]);
   COMBA_STORE(C->dp[11]);
   /* 12 */
   COMBA_FORWARD;
   MULADD(at[5], at[15]);   MULADD(at[6], at[14]);   MULADD(at[7], at[13]);
   COMBA_STORE(C->dp[12]);
   /* 13 */
   COMBA_FORWARD;
   MULADD(at[6], at[15]);   MULADD(at[7], at[14]);
   COMBA_STORE(C->dp[13]);
   /* 14 */
   COMBA_FORWARD;
   MULADD(at[7], at[15]);
   COMBA_STORE(C->dp[14]);
   COMBA_STORE2(C->dp[15]);
   C->used = 16;
   C->sign = A->sign ^ B->sign;
   fp_clamp(C);
   COMBA_FINI;
}
#endif
