#include "unit-test.h"

int
main (void)
{
  ut_push_case ("main");
    ut_push_case ("integer-math");
      ut_push_case ("integer-math-1-2");
        assert_eq (1, 2);
      ut_pop_case ();
      ut_push_case ("integer-math-2-4");
        assert_eq (2, 4);
      ut_pop_case ();
      ut_push_case ("integer-math-3-6");
        assert_eq (3, 6);
      ut_pop_case ();
      ut_push_case ("integer-math-4-8");
        assert_eq (4, 8);
      ut_pop_case ();
    ut_pop_case ();

    ut_push_case ("float-math");
      assert_eqf (0.1 + 0.2, 0.3, 1e-6);
      assert_eqf (0.2 + 0.4, 0.6, 1e-6);
      assert_eqf (0.3 + 0.8, 1.1, 1e-6);
    ut_pop_case ();
  ut_pop_case ();

  return 0;
}

