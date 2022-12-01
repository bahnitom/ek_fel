#include <stdio.h>
#include <stdlib.h>

// macros
#define LENGTH 10
#define ERROR_HISTOGRAM 100
#define ERROR_MALLOC 101
#define ERROR_REALLOC 102

// functions
int *read_input(int *load);
int check_first_numb(int first_numb);

int main(int argc, char *argv[])
{

    int load = 0;
    int cols;
    int *arr_line = NULL;

    arr_line = read_input(&load);
    // only if reading array goes wrong
    if (arr_line == NULL)
    {
        return -1;
    }

    // check if number of collums is set right
    check_first_numb(arr_line[0]);
    cols = arr_line[0];

    // sort from lowest to highest number
    for (int i = 0; i < load; ++i)
    {
        for (int j = i + 1; j < load; ++j)
        {
            if (arr_line[i] > arr_line[j])
            {
                int x = arr_line[i];
                arr_line[i] = arr_line[j];
                arr_line[j] = x;
            }
        }
    }
    int med_pos = load / 2;
    int numbers = load - 1;
    int min_val = arr_line[0];
    int max_val = arr_line[load - 1];
    printf("Median %.2f\n", (float)arr_line[med_pos]);
    printf("Pocet cisel: %d\n", numbers);
    printf("Min. hodnota: %d\n", min_val);
    printf("Max. hodnota: %d\n", max_val);

    // HISTOGRAM

    float SIZE = (max_val - min_val) / (float)cols;
    float borders[cols], BIN[load];
    char equals[cols];
    float k_i;
    // count bordes values
    for (int i = 0; i < cols; ++i)
    {
        k_i = min_val + i * SIZE;
        borders[i] = k_i;
    }
    // find values for each input
    for (int j = 0; j < load; ++j)
    {
        BIN[j] = (arr_line[j] - min_val) / SIZE;
    }

    // chose in which bordes imput number belong to
    for (int x = 0; x < load; ++x)
    {
        for (int y = 0; y < cols; ++y)
        {
            if ((BIN[x] >= borders[y]) && BIN[x] <= borders[y + 1])
            {
                equals[y] = '=';
            }
        }
    }
    printf("%c ", equals[0]);
    printf("\n");

    // only printing array
    /* for (int i = 0; i < load; i++)
    {
        printf("%d ", arr_line[i]);
    }
    printf("\n");
 */
    /* for (int i = 0; i < cols; i++)
    {
        printf("%c ", equals[i]);
    }
    printf("\n"); */

    free(arr_line);
    return 0;
}

int check_first_numb(int first_numb)
{
    if (first_numb <= 0)
    {
        fprintf(stderr, "Error: Chyba histogramu!\n");
        exit(ERROR_HISTOGRAM);
    }
    else
        return 0;
}

int *read_input(int *load)
{
    int capacity = LENGTH;
    int numb, count = 0;
    // allocate memory for 10 int numbers
    int *arr_line = calloc(capacity, sizeof(int));

    if (arr_line == NULL) /*error malloc, for sure*/
    {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
    }
    // malloc ok ---> continue scanning numbers
    else
    {
        while (scanf("%d", &numb) == 1)
        {
            if (count >= capacity) /*array is full*/
            {
                int *tmp = realloc(arr_line, (capacity * 2) * sizeof(int));
                if (tmp == NULL) /*error realloc, for sure*/
                {
                    fprintf(stderr, "Error realloc\n");
                    free(arr_line);
                    arr_line = NULL;
                    load = 0;
                    exit(ERROR_REALLOC);
                }
                capacity *= 2; /*double size array*/
                arr_line = tmp;
            }
            arr_line[count] = numb;
            if (load == 0)
            {
                check_first_numb(arr_line[0]);
            }
            count++;
        }
    }
    *load = count;
    return arr_line;
}
