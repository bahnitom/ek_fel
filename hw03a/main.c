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
void print_output(int count, int even, int possitive, int negativ, float avg, int max, int min);

/* The main program */
int main(int argc, char *argv[])
{
  int x;
  int ret = EXIT_SUCCESS;
  int count = 0, even = 0, possitive = 0, negative = 0, max = 0, min = 0;
  float avg = 0;
  while (scanf("%d", &x) != EOF)
  {
    // counters
    count += 1;
    avg += x;
    if (x > 0)
      possitive += 1;
    if (x < 0)
      negative += 1;
    if (x % 2 == 0)
      even += 1;

    // set max / min to first scaned value
    if (count == 1)
    {
      max = x;
      min = x;
    }
    // find max/min
    if (x > max)
      max = x;
    if (x < min)
      min = x;

    // check if input is out of interval
    if (x < BORDER_LEFT || x > BORDER_RIGHT)
    {
      printf("\n");
      printf("Error: Vstup je mimo interval!\n");
      return ERROR_INPUT;
    }
    else
    {
      if (count != 1)
        printf(", ");
    }
    printf("%d", x);
  };
  print_output(count, even, possitive, negative, avg, max, min);
  return ret;
}

// function that print outputs
void print_output(int count, int even, int possitive, int negativ, float avg, int max, int min)
{
  int odd = count - even;
  float per_possitiv = (100.00 / count) * possitive;
  float per_negativ = (100.00 / count) * negativ;
  float per_even = (100.00 / count) * even;
  float per_odd = (100.00 / count) * odd;
  float avg_res = avg / count;

  printf("\n");
  printf("Pocet cisel: %d\n", count);
  printf("Pocet kladnych: %d\n", possitive);
  printf("Pocet zapornych: %d\n", negativ);
  printf("Procento kladnych: %.2f\n", per_possitiv);
  printf("Procento zapornych: %.2f\n", per_negativ);
  printf("Pocet sudych: %d\n", even);
  printf("Pocet lichych: %d\n", odd);
  printf("Procento sudych: %.2f\n", per_even);
  printf("Procento lichych: %.2f\n", per_odd);
  printf("Prumer: %.2f\n", avg_res);
  printf("Maximum: %d\n", max);
  printf("Minimum: %d\n", min);
}
