/* TomsFastMath, a fast ISO C bignum library. -- Tom St Denis */
/* SPDX-License-Identifier: Unlicense */
#include <tfm_private.h>

/* unsigned addition */
void s_fp_add(const fp_int *a, const fp_int *b, fp_int *c)
{
  int      x, y, oldused;
  register fp_word  t;

  y       = MAX(a->used, b->used);
  oldused = MIN(c->used, FP_SIZE);
  c->used = y;

  t = 0;
  for (x = 0; x < y; x++) {
      t         += ((fp_word)a->dp[x]) + ((fp_word)b->dp[x]);
      c->dp[x]   = (fp_digit)t;
      t        >>= DIGIT_BIT;
  }
  if (t != 0 && x < FP_SIZE) {
     c->dp[c->used++] = (fp_digit)t;
     ++x;
  }

  c->used = x;
  for (; x < oldused; x++) {
     c->dp[x] = 0;
  }
  fp_clamp(c);
}
