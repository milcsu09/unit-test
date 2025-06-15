#ifndef UNIT_TEST_H
#define UNIT_TEST_H


#include <math.h>


#define UT_CHECK_TYPE(type, x) (void)sizeof((type)(x))


#define assert_eq(a, b)                                                        \
  do                                                                           \
    {                                                                          \
      UT_CHECK_TYPE (int, a);                                                  \
      UT_CHECK_TYPE (int, b);                                                  \
      if (a != b)                                                              \
        ut_failed (__FILE__, __LINE__,                                         \
                   "expected `%s` to be `%d`, but was `%d`", #a, b, a);        \
      else                                                                     \
        ut_passed (__FILE__, __LINE__);                                        \
    }                                                                          \
  while (0)


#define assert_eqf(a, b, epsilon)                                              \
  do                                                                           \
    {                                                                          \
      UT_CHECK_TYPE (double, a);                                               \
      UT_CHECK_TYPE (double, b);                                               \
      if (fabs ((a) - (b)) > (epsilon))                                        \
        ut_failed (__FILE__, __LINE__,                                         \
                   "expected `%s` to be `%f`, but was `%f`", #a, b, a);        \
      else                                                                     \
        ut_passed (__FILE__, __LINE__);                                        \
    }                                                                          \
  while (0)


#define assert_true(a)                                                         \
  do                                                                           \
    {                                                                          \
      UT_CHECK_TYPE (int, a);                                                  \
      if (!(a))                                                                \
        ut_failed (__FILE__, __LINE__, "expected `%s` to be `true`", #a);      \
      else                                                                     \
        ut_passed (__FILE__, __LINE__);                                        \
    }                                                                          \
  while (0)


void ut_init ();

void ut_set_color_allowed (int);

void ut_push_case (const char *);

void ut_pop_case ();

void ut_passed (const char *, int);

void ut_failed (const char *, int, const char *, ...);

void ut_failed_expect_int (const char *, int, int, int);

void ut_failed_assertion (const char *, int, const char *);


#endif // UNIT_TEST_H

