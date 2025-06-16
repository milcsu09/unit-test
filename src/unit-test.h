#ifndef UNIT_TEST_H
#define UNIT_TEST_H


#include <math.h>
#include <string.h>


#define UT_INDENT 4


#define assert_eq(a, b)                                                        \
  do                                                                           \
    {                                                                          \
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
      if (fabs ((a) - (b)) > (epsilon))                                        \
        ut_failed (__FILE__, __LINE__,                                         \
                   "expected `%s` to be `%f`, but was `%f`", #a, b, a);        \
      else                                                                     \
        ut_passed (__FILE__, __LINE__);                                        \
    }                                                                          \
  while (0)


#define assert_eqs(a, b)                                                       \
  do                                                                           \
    {                                                                          \
      if (strcmp(a, b) != 0)                                                   \
        ut_failed (__FILE__, __LINE__,                                         \
                   "expected `%s` to be \"%s\", but was \"%s\"", #a, b, a);    \
      else                                                                     \
        ut_passed (__FILE__, __LINE__);                                        \
    }                                                                          \
  while (0)


#define assert_true(a)                                                         \
  do                                                                           \
    {                                                                          \
      if (!(a))                                                                \
        ut_failed (__FILE__, __LINE__, "expected `%s` to be `true`", #a);      \
      else                                                                     \
        ut_passed (__FILE__, __LINE__);                                        \
    }                                                                          \
  while (0)


#define ut_case(name)                                                          \
  for (int __i = (ut_push_case (name), 1); __i; __i = (ut_pop_case (), 0))


void ut_init ();

void ut_set_color_allowed (int);

void ut_push_case (const char *);

void ut_pop_case ();

void ut_passed (const char *, int);

void ut_failed (const char *, int, const char *, ...);


#endif // UNIT_TEST_H

