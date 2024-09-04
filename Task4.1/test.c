#include <stdio.h>
#include "strindex.h"

int main() {
    char s[] = "Hello, world! Hello!";
    char t[] = "Hello";

    char* strings[2] = {
      "Apple, banana, pineapple",
      "One, two, three, twenty, ten",
    };

    char* patterns[10] = {
      "Apple",
      "apple",
      "banana",
      "ban",
      "two",
      "ten",
      "three",
      " two, ",
      "one",
      "ent"
    };

    int results[2][10] = {
      {0, 19, 7, 7, -1, -1, -1, -1, -1, -1},
      {-1, -1, -1, -1, 5, 25, 10, 4, -1, 19}
    };

    for (int str_i = 0; str_i < 2; str_i++) {
      for (int pat_i = 0; pat_i < 10; pat_i++)
      {
        int pos = strindex(strings[str_i], patterns[pat_i]);
        int exp = results[str_i][pat_i];
        if (pos != exp)
          printf("Error!\nString: %s\nPattern: %s\nResult: %d\nExpected: %d\n", strings[str_i], patterns[pat_i], pos, exp);
      }
    }
    printf("Success!\n");
}