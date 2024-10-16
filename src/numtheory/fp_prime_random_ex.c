/* TomsFastMath, a fast ISO C bignum library. -- Tom St Denis */
/* SPDX-License-Identifier: Unlicense */
#include <tfm_private.h>

#define fp_on_bitnum(a, bitnum) \
    a->dp[(bitnum) >> DIGIT_SHIFT] |= (fp_digit)1 << ((bitnum) & (DIGIT_BIT-1))

#define fp_off_bitnum(a, bitnum) \
    a->dp[(bitnum) >> DIGIT_SHIFT] &= ~((fp_digit)1 << ((bitnum) & (DIGIT_BIT-1)))

/* This is possibly the mother of all prime generation functions, muahahahahaha! */
int fp_prime_random_ex(fp_int *a, int t, int size, int flags, tfm_prime_callback cb, void *dat)
{
   fp_digit maskAND_msb, maskOR_lsb;
   int res, bsize, dsize;
   unsigned char buf[FP_SIZE * sizeof(fp_digit)];

   /* sanity check the input */
   if (size <= 1 || cb == NULL || t <= 0 || t > FP_PRIME_SIZE) {
      return FP_VAL;
   }

   /* TFM_PRIME_SAFE implies TFM_PRIME_BBS */
   if (flags & TFM_PRIME_SAFE) {
      flags |= TFM_PRIME_BBS;
   }

   /* calc the size in fp_digit */
   dsize = (size + DIGIT_BIT - 1) >> DIGIT_SHIFT;
   /* calc the size in bytes */
   bsize = (size + 7) >> 3;

   /* calc the maskAND value for the MSbyte */
   maskAND_msb = FP_MASK >> ((DIGIT_BIT - size) & (DIGIT_BIT-1));

   /* get the maskOR_lsb */
   maskOR_lsb         = 1;
   if (flags & TFM_PRIME_BBS) {
      maskOR_lsb     |= 3;
   }

   do {
      /* read the bytes */
      if (cb(buf, bsize, dat) != bsize) {
         return FP_VAL;
      }
      fp_read_unsigned_bin(a, buf, bsize);

      /* make sure the MSbyte has the required number of bits */
      a->dp[dsize-1]    &= maskAND_msb;

      /* Force a->used as well, it could be smaller if the highest bits were
         generated as 0 by the callback. */
      a->used           = dsize;

      /* modify the LSbyte as requested */
      a->dp[0]          |= maskOR_lsb;

      /* turn on the MSbit to force the requested magnitude */
      fp_on_bitnum(a, size-1);

      /* modify the 2nd MSBit */
      if (flags & TFM_PRIME_2MSB_ON) {
          fp_on_bitnum(a, size-2);
      } else if (flags & TFM_PRIME_2MSB_OFF) {
          fp_off_bitnum(a, size-2);
      }

      /* is it prime? */
      res = fp_isprime_ex(a, t);
      if (res == FP_NO) continue;

      if (flags & TFM_PRIME_SAFE) {
         /* see if (a-1)/2 is prime */
         fp_sub_d(a, 1, a);
         fp_div_2(a, a);

         /* is it prime? */
         res = fp_isprime_ex(a, t);
      }
   } while (res == FP_NO);

   if (flags & TFM_PRIME_SAFE) {
      /* restore a to the original value */
      fp_mul_2(a, a);
      fp_add_d(a, 1, a);
   }

   return FP_OKAY;
}
