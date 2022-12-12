#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macros
#define LENGTH 10
#define ERROR_HISTOGRAM 100
#define ERROR_MALLOC 101
#define ERROR_REALLOC 102

// functions
int *read_input(int *load);

int check_first_numb(int first_numb);

int *sort_array(int *array, int load);

int main() {

    int load = 0;
    int cols;
    int *arr_line = NULL;
    int *arr_line_sort = NULL;

    // read cols
    scanf("%d", &cols);
    check_first_numb(cols);
    arr_line = read_input(&load);

    // sort from lowest to highest number
    arr_line_sort = sort_array(arr_line, load);

    // print A solution
    int med_pos = load / 2;
    int numbers = load;
    int min_val = arr_line_sort[0];
    int max_val = arr_line_sort[load - 1];
    float med;
    if (numbers % 2 != 0) {
        med = (float) arr_line_sort[med_pos];
    } else {
        med = (float) (arr_line[med_pos - 1] + arr_line[med_pos]) / 2;
    }

    printf("Median %.2f\n", med);
    printf("Pocet cisel: %d\n", numbers);
    printf("Min. hodnota: %d\n", min_val);
    printf("Max. hodnota: %d\n", max_val);

    /* HISTOGRAM */
    float SIZE = (float) (max_val - min_val) / (float) cols;
    float borders[cols];
    int priority[cols];
    memset(priority, 0, sizeof(priority));
    int priority_sort[cols];
    float k_i;

    // count borders values
    for (int i = 0; i < cols + 1; ++i) {
        k_i = (float) min_val + (float) i * SIZE;
        borders[i] = k_i;
    }

    // count how many numbers are in which interval
    int cnt_num = 0;
    int cnt_int = 1;
    while (cnt_num < load) {
        if (arr_line_sort[cnt_num] <= borders[cnt_int]) {
            priority[cnt_int - 1]++;
            cnt_num++;
        } else {
            cnt_int++;
        }
    }

    // find interval with most bins and count multiplier of char '='
    float max_bin;
    for (int i = 0; i < cols; i++) {
        priority_sort[i] = priority[i];
    }
    *priority_sort = *sort_array(priority_sort, cols);
    max_bin = 25.01 / priority_sort[cols - 1];

    for (int i = 0; i < cols; i++) {
        priority[i] = priority[i] * max_bin;
    }

    // print histogram
    int count = 0;
    printf("Histogram:\n");
    for (int y = 0; y < cols; ++y) {
        if (count < cols) {
            printf("%5.1f", borders[count]);
            count++;
            printf(" -");
            printf("%6.1f", borders[count]);
            printf(" |");
            for (int x = 0; x < priority[y]; ++x) {
                printf("=");
            }
            // clear unused array (valgrind)
            priority[y] = 0;
        }
        printf("\n");
    }
    free(arr_line);
    return 0;
}

int check_first_numb(int first_numb) {
    if (first_numb <= 0) {
        fprintf(stderr, "Error: Chyba histogramu!\n");
        exit(ERROR_HISTOGRAM);
    } else
        return 0;
}

int *read_input(int *load) {
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
    else {
        while (scanf("%d", &numb) == 1) {
            if (count >= capacity) /*array is full*/
            {
                int *tmp = realloc(arr_line, (capacity * 2) * sizeof(int));
                if (tmp == NULL) /*error realloc, for sure*/
                {
                    fprintf(stderr, "Error realloc\n");
                    free(arr_line);
                    arr_line = NULL;
                    exit(ERROR_REALLOC);
                }
                capacity *= 2; /*double size array*/
                arr_line = tmp;
            }
            arr_line[count] = numb;
            if (load == 0) {
                check_first_numb(arr_line[0]);
            }
            count++;
        }
    }
    *load = count;
    return arr_line;
}

int *sort_array(int *array, int load) {
    // sort from lowest to highest number
    for (int i = 0; i < load; ++i) {
        for (int j = i + 1; j < load; ++j) {
            if (array[i] > array[j]) {
                int x = array[i];
                array[i] = array[j];
                array[j] = x;
            }
        }
    }
    return array;
}
