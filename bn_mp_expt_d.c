/* LibTomMath, multiple-precision integer library -- Tom St Denis
 *
 * LibTomMath is library that provides for multiple-precision
 * integer arithmetic as well as number theoretic functionality.
 *
 * The library is designed directly after the MPI library by
 * Michael Fromberger but has been written from scratch with
 * additional optimizations in place.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@iahu.ca, http://libtommath.iahu.ca
 */
#include <tommath.h>

int
mp_expt_d (mp_int * a, mp_digit b, mp_int * c)
{
  int     res, x;
  mp_int  g;


  if ((res = mp_init_copy (&g, a)) != MP_OKAY) {
    return res;
  }

  /* set initial result */
  mp_set (c, 1);

  for (x = 0; x < (int) DIGIT_BIT; x++) {
    if ((res = mp_sqr (c, c)) != MP_OKAY) {
      mp_clear (&g);
      return res;
    }

    if ((b & (mp_digit) (1 << (DIGIT_BIT - 1))) != 0) {
      if ((res = mp_mul (c, &g, c)) != MP_OKAY) {
	mp_clear (&g);
	return res;
      }
    }

    b <<= 1;
  }

  mp_clear (&g);
  return MP_OKAY;
}
