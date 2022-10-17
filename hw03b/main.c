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

    if (x != tmp && counter != 1)
    {
      printf("%dx %d\n", counter, tmp);
      counter = 1;
    }
    tmp = x;
    // check if input is out of interval
    if (x < BORDER_LEFT || x > BORDER_RIGHT)
    {
      printf("Error: Vstup je mimo interval!\n");
      return ERROR_INPUT;
    }
  }
  if (counter != 1)
    printf("%dx %d\n", counter, tmp);
  return ret;
}
