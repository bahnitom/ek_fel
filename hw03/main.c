#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// error
#define ERROR_INPUT 100

// borders
enum
{
  BORDER_LEFT = -10000,
  BORDER_RIGHT = 10000
};

// functions
int read_numbers(void);

/* The main program */
int main(int argc, char *argv[])
{
  int x;
  int ret = EXIT_SUCCESS;
  int count = 0;
   while (scanf("%d", &x) != EOF)
  {
    count += 1;
    // check if input is out of interval
    if (x < BORDER_LEFT || x > BORDER_RIGHT)
    {
      printf("\n");
      fprintf(stderr, "Vstup je mimo interval!\n");
      return ERROR_INPUT;
    }
    else
    {
      if (count != 1)
        printf(", ");
    }
    printf("%d", x);
  };
  printf("\n");
  printf("pocet: %d\n", count);

  return ret;
};
