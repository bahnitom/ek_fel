#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100

// function
int print_output(int count_enc, int counter, int digits, char tmp);

int main(int argc, char *argv[])
{
  int ret = EXIT_SUCCESS;
  int count_in = 0, count_enc = 0, counter = 0, digits = 0;
  char ch, tmp;
  while (((ch = getchar()) != EOF && ch != '\n'))
  {
    // only once
    if (count_in == 0)
      tmp = ch;

    // counters
    if (ch == tmp)
      counter++;
    count_in++;

    if (ch != tmp || counter == 255)
    {
      count_enc = print_output(count_enc, counter, digits, tmp);
      if (counter == 255)
        counter = 0;
      else
        counter = 1;
    }
    digits = 0;
    tmp = ch;

    // check if input is in correct interval
    if (ch < 'A' || ch > 'Z')
    {
      fprintf(stderr, "Error: Neplatny symbol!\n");
      ret = ERROR_INPUT;
      return ret;
    }
  }
  count_enc = print_output(count_enc, counter, digits, tmp);
  float rate = (float)count_enc / count_in;
  printf("\n");
  fprintf(stderr, "Pocet vstupnich symbolu: %d\n", count_in);
  fprintf(stderr, "Pocet zakodovanych symbolu: %d\n", count_enc);
  fprintf(stderr, "Kompresni pomer: %0.2f\n", rate);
  return 0;
}

int print_output(int count_enc, int counter, int digits, char tmp)
{
  /*counting number digits*/
  int count_tmp = counter;
  do
  {
    count_tmp /= 10;
    ++digits;
  } while (count_tmp != 0);

  /*switch*/
  switch (counter)
  {
  case 1:
    printf("%c", tmp);
    count_enc++;
    break;
  case 2:
    printf("%c%c", tmp, tmp);
    count_enc += 2;
    break;
  default:
    printf("%c%d", tmp, counter);
    count_enc += digits + 1;
    break;
  }
  return count_enc;
}
