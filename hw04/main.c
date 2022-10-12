#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_INPUT 100

int main(int argc, char *argv[])
{
  int count_in = 0, count_enc = 0, counter = 0;
  char ch, tmp;
  while (((ch = getchar()) != EOF && ch != '\n'))
  {
    count_in++;

    // only once
    if (count_in == 1)
      tmp = ch;

    if (ch == tmp)
      counter++;
    if (ch != tmp && counter > 2)
    {
      printf("%c%d", tmp, counter);
      count_enc++;
      counter = 1;
    }

    if (ch != tmp && counter == 1)
    {
      printf("%c", tmp);
      counter = 1;
    }

    if (ch != tmp && counter == 2)
    {
      printf("%c%c", tmp, tmp);
      counter = 1;
    }

    tmp = ch;
    if (ch < 'A' || ch > 'Z')
    {
      fprintf(stderr, "Error: Neplatny symbol!\n");
      printf("\n");
      return ERROR_INPUT;
    }
  }
  switch (counter)
  {
  case 1:
    printf("%c", tmp);
    break;
  case 2:
    printf("%c%c", tmp, tmp);
    break;
  default:
    printf("%c%d", tmp, counter);
    break;
  }

  printf("\n");
  fprintf(stderr, "Pocet vstupnich symbolu: %d\n", count_in);
  fprintf(stderr, "Pocet zakodovanych symbolu: %d\n", counter);
  fprintf(stderr, "Kompresni pomer: \n");
  return 0;
}
