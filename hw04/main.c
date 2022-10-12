#include <stdio.h>
#include <stdlib.h>

#define ERROR_INPUT 100

int main(int argc, char *argv[])
{
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

    if (ch != tmp)
    {
      while (counter != 0)  // problem here
        {
          counter = counter / 10;
          digits ++;
        }
      switch (counter) // switch_1
      {
      case 1:
        printf("%c", tmp);
        count_enc++;
        break;
      case 2:
        printf("%c%c", tmp, tmp);
        count_enc += 2;
        counter = 1;
        break;
      default:
        printf("%c%d", tmp, counter);
        count_enc += digits;
        counter = 1;
        break;
      }
    }
    tmp = ch;

    // check if input is in correct interval
    if (ch < 'A' || ch > 'Z')
    {
      fprintf(stderr, "Error: Neplatny symbol!\n");
      return ERROR_INPUT;
    }
  }
  switch (counter) //switch_2
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
    count_enc += 2;
    break;
  }

  float rate = (float)count_enc / count_in;
  printf("\n");
  fprintf(stderr, "Pocet vstupnich symbolu: %d\n", count_in);
  fprintf(stderr, "Pocet zakodovanych symbolu: %d\n", count_enc);
  fprintf(stderr, "Kompresni pomer: %0.2f\n", rate);
  return 0;
}
