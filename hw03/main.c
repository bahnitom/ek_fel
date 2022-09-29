#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_INPUT 100
enum
{
  BORDER_LEFT = -10000,
  BORDER_RIGHT = 10000
};

/* The main program */
int main(int argc, char *argv[])
{
  int x;
  int ret = EXIT_SUCCESS;
  int sc;
  while ((sc = scanf("%d", &x)) != EOF)
  {
    if (x < BORDER_LEFT || x > BORDER_RIGHT)
    {
      // sc = false;
      printf("\n");
      printf("Vstup je mimo interval!\n");
      return ERROR_INPUT;
    }
    else
    {
      printf("%d", x);
      if (sc != EOF) //while cyclus does not reach last value + 1 ---> that value giv us EOS
        printf(", ");
      else
        printf("\n");
    }
  };

  // printing rows
  /* printf("Desitkova soustava: %d %d\n", x, y);
  printf("Sestnactkova soustava: %x %x\n", x, y);
  printf("Soucet: %d + %d = %d\n", x, y, x + y);
  printf("Rozdil: %d - %d = %d\n", x, y, x - y);
  printf("Soucin: %d * %d = %d\n", x, y, x * y);
  if (y == 0) {
    printf("Nedefinovany vysledek!\n");
  } else
    printf("Podil: %d / %d = %d\n", x, y, x / y);
  printf("Prumer: %.1f\n", avg);
   */

  return ret;
}

int read_numbers(int x)
{

  return x;
};
