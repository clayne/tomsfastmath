/* TomsFastMath, a fast ISO C bignum library. -- Tom St Denis */
/* SPDX-License-Identifier: Unlicense */
#ifndef TFM_PRE_GEN_MPI_C
#define TFM_DEFINES
#include "fp_sqr_comba.c"
#endif

#if defined(TFM_SQR3) && FP_SIZE >= 6
void fp_sqr_comba3(const fp_int *A, fp_int *B)
{
   const fp_digit *a;
   fp_digit b[6], c0, c1, c2;
#ifdef TFM_ISO
   fp_word tt;
#endif

   a = A->dp;
   COMBA_START;

   /* clear carries */
   CLEAR_CARRY;

   /* output 0 */
   SQRADD(a[0],a[0]);
   COMBA_STORE(b[0]);

   /* output 1 */
   CARRY_FORWARD;
   SQRADD2(a[0], a[1]);
   COMBA_STORE(b[1]);

   /* output 2 */
   CARRY_FORWARD;
   SQRADD2(a[0], a[2]); SQRADD(a[1], a[1]);
   COMBA_STORE(b[2]);

   /* output 3 */
   CARRY_FORWARD;
   SQRADD2(a[1], a[2]);
   COMBA_STORE(b[3]);

   /* output 4 */
   CARRY_FORWARD;
   SQRADD(a[2], a[2]);
   COMBA_STORE(b[4]);
   COMBA_STORE2(b[5]);
   COMBA_FINI;

   B->used = 6;
   B->sign = FP_ZPOS;
   memcpy(B->dp, b, 6 * sizeof(fp_digit));
   fp_clamp(B);
}
#endif
