#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10
#define ERROR_MALLOC 101
#define ERROR_REALLOC 102

int main(int argc, char *argv[])
{
  int capacity = LENGTH;
  int load = 0;
  int count = 0;

  // allocate memory for 10 numbers
  int *arr_line = malloc(sizeof(int) * capacity);

  if (arr_line == NULL) /*error malloc, for sure*/
  {
    fprintf(stderr, "Error malloc\n");
    return ERROR_MALLOC;
  }
  // malloc ok ---> continue scanning numbers
  else
  {
    while (scanf("%d", &arr_line[load]) == 1)
    {
      count++;
      if (load == capacity) /*array is full*/
      {
        capacity *= 2; /*double size array*/
        int *tmp = realloc(arr_line, capacity);
        if (tmp == NULL) /*error realloc, for sure*/
        {
          fprintf(stderr, "Error realloc\n");
          free(arr_line);
          arr_line = NULL;
          return ERROR_REALLOC;
        }
        arr_line = tmp;
      }
      load++;
    }
  }
  free(arr_line);
  printf("%d", *arr_line);
  return 0;
}
