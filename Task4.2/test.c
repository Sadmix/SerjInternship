#include <stdio.h>
#include "atof.h"

int main() {
  char* nums[] = {
    "123.321e-1",
    "123.321e-2",
    "123.321e-25",
    "123.321e+1",
    "123.321e+2",
    "123.321e+25",
    "-123.321e-1",
    "-123.321e-2",
    "-123.321e-25"
  };

  double exp[] = {
    123.321e-1,
    123.321e-2,
    123.321e-25,
    123.321e+1,
    123.321e+2,
    123.321e+25,
    -123.321e-1,
    -123.321e-2,
    -123.321e-25
  };

  for (int i = 0; i < sizeof(exp)/sizeof(double); i++) {
    double res = atof(nums[i]);
    printf("\nString: %s\nResult: %.32f\nExpected: %.32f\n", nums[i], res, exp[i]);
  }
  return 0;
}