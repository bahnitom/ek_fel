#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100

enum
{
  BORDER_LEFT = 0,
  BORDER_RIGHT = 100
};

int main()
{
  int x, tmp;
  int ret = EXIT_SUCCESS;
  int count_in = 0, counter = 0;
  while (scanf("%d", &x) != EOF)
  {
    // only once
    if (count_in == 0)
      tmp = x;

    // counters
    if (x == tmp)
      counter++;
    count_in++;

    if (x != tmp)
      printf("%dx %d\n", counter, x);

    x = tmp;
  }
  printf("\n");

  return ret;
}
