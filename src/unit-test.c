#include "unit-test.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>


#define RESET "\033[0m"
#define BOLD "\033[1m"

#define BGREEN "\033[1;32m"
#define BRED "\033[1;31m"
#define GRAY "\033[90m"
#define BGRAY "\033[1;90m"
#define BYELLOW "\033[1;33m"


#define C(code) color_allowed ? code : ""


#define CASE_STACK_SIZE 1024


struct stack_item
{
  const char *name;
  int pass;
  int fail;
};


static struct stack_item case_stack[CASE_STACK_SIZE];
static size_t case_stack_depth = 0;
static size_t case_stack_previous_depth = -1;


static int ut_initalized = 0;
static int color_allowed = 1;


void
ut_init ()
{
  if (ut_initalized)
    return;

  ut_initalized = 1;

  if (color_allowed == 1)
    color_allowed = isatty (fileno (stderr));
}


void
ut_set_color_allowed (int a)
{
  color_allowed = a;
}


void
ut_push_case (const char *name)
{
  ut_init ();

  if (case_stack_depth == case_stack_previous_depth)
    fprintf (stderr, "\n");

  fprintf (stderr, "%*.s", (int)case_stack_depth * 2, "");
  fprintf (stderr, "%s%s%s\n", C (BGRAY), name, C (RESET));

  struct stack_item item;

  item.pass = 0;
  item.fail = 0;
  item.name = name;

  case_stack[case_stack_depth++] = item;
}


void
ut_pop_case ()
{
  ut_init ();

  struct stack_item item;

  item = case_stack[--case_stack_depth];

  case_stack_previous_depth = case_stack_depth;

  int pass = item.pass;
  int fail = item.fail;

  int total = pass + fail;

  fprintf (stderr, "%*.s", (int)case_stack_depth * 2, "");

  if (pass == total)
    fprintf (stderr, "%sPASSED%s (%s%d%s)%s\n", C (BGREEN), C (GRAY),
             C (BGREEN), pass, C (GRAY), C (RESET));

  else if (fail == total)
    fprintf (stderr, "%sFAILED%s (%s%d%s)%s\n", C (BRED), C (GRAY), C (BRED),
             fail, C (GRAY), C (RESET));

  else
    fprintf (stderr, "%sPARTIAL%s (%s%d%s passed %s%d%s failed) %s\n",
             C (BYELLOW), C (GRAY), C (BGREEN), pass, C (GRAY), C (BRED), fail,
             C (GRAY), C (RESET));

  case_stack[case_stack_depth - 1].pass += pass;
  case_stack[case_stack_depth - 1].fail += fail;
}


void
ut_passed (const char *file, int line)
{
  ut_init ();

  case_stack[case_stack_depth - 1].pass++;

  fprintf (stderr, "%*.s", (int)case_stack_depth * 2, "");
  fprintf (stderr, "%s:%d: %sPASSED%s\n", file, line, C (BGREEN), C (RESET));
}


void
ut_failed (const char *file, int line, const char *format, ...)
{
  ut_init ();

  case_stack[case_stack_depth - 1].fail++;

  fprintf (stderr, "%*.s", (int)case_stack_depth * 2, "");
  fprintf (stderr, "%s:%d: %sFAILED%s: %s", file, line, C (BRED), C (RESET),
           C (BOLD));

  va_list args;
  va_start (args, format);

  vfprintf (stderr, format, args);

  va_end (args);

  fprintf (stderr, "%s\n", C (RESET));
}


void
ut_failed_expect_int (const char *file, int line, int a, int b)
{
  ut_failed (file, line, "expected `%d`, got `%d`", a, b);
}


void
ut_failed_assertion (const char *file, int line, const char *a)
{
  ut_failed (file, line, "expected `%s` to be `true`, got `false`", a);
}

