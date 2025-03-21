/* Boost test/pi.cpp
 * test if the pi constant is correctly defined
 *
 * Copyright Guillaume Melquiond, Sylvain Pion 2002-2003
 * Permission to use, copy, modify, sell, and distribute this software
 * is hereby granted without fee provided that the above copyright notice
 * appears in all copies and that both that copyright notice and this
 * permission notice appear in supporting documentation.
 *
 * None of the above authors nor Polytechnic University make any
 * representation about the suitability of this software for any
 * purpose. It is provided "as is" without express or implied warranty.
 *
 * $Id: pi.cpp,v 1.4 2003/06/03 22:00:00 hervebronnimann Exp $
 */

#include <boost/numeric/interval.hpp>
#include <boost/limits.hpp>
#include <boost/test/minimal.hpp>
#include "bugs.hpp"

#define PI 3.14159265358979323846

typedef boost::numeric::interval<int>         I_i;
typedef boost::numeric::interval<float>       I_f;
typedef boost::numeric::interval<double>      I_d;
typedef boost::numeric::interval<long double> I_ld;

using boost::numeric::interval_lib::pi;
using boost::numeric::interval_lib::pi_half;
using boost::numeric::interval_lib::pi_twice;

int test_main(int, char *[]) {
  I_i  pi_i  = pi<I_i>();
  I_f  pi_f  = pi<I_f>();
  I_d  pi_d  = pi<I_d>();
  I_ld pi_ld = pi<I_ld>();

  BOOST_TEST(in((int)   PI, pi_i));
  BOOST_TEST(in((float) PI, pi_f));
  BOOST_TEST(in((double)PI, pi_d));
  BOOST_TEST(subset(pi_i, widen(I_i((int)   PI), 1)));
  BOOST_TEST(subset(pi_f, widen(I_f((float) PI), std::numeric_limits<float> ::min())));
  BOOST_TEST(subset(pi_d, widen(I_d((double)PI), std::numeric_limits<double>::min())));

  // We can't test the following equalities for interval<int>.
  I_f pi_f_half = pi_half<I_f>();
  I_f pi_f_twice = pi_twice<I_f>();

  I_d pi_d_half = pi_half<I_d>();
  I_d pi_d_twice = pi_twice<I_d>();

  I_ld pi_ld_half = pi_half<I_ld>();
  I_ld pi_ld_twice = pi_twice<I_ld>();

  BOOST_TEST(equal(2.0f * pi_f_half, pi_f));
  BOOST_TEST(equal(2.0  * pi_d_half, pi_d));
  BOOST_TEST(equal(2.0l * pi_ld_half, pi_ld));

  BOOST_TEST(equal(2.0f * pi_f, pi_f_twice));
  BOOST_TEST(equal(2.0  * pi_d, pi_d_twice));
  BOOST_TEST(equal(2.0l * pi_ld, pi_ld_twice));

  return 0;
}
