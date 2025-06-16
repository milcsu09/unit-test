#include "unit-test.h"

int
main (void)
{
  ut_case ("main")
    {
      ut_case ("integer-math")
        {
          ut_case ("1 + 1")
            assert_eq (1 + 1, 3);
        }

      ut_case ("float-math")
        {
          assert_eqf (0.1 + 0.2, 0.3, 1e-6);
          assert_eqf (0.2 + 0.4, 0.6, 1e-6);
          assert_eqf (0.3 + 0.8, 1.1, 1e-6);
        }
    }

  return 0;
}

