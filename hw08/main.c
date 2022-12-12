#include <stdio.h>
#include <stdlib.h>


// macros
#define LENGTH 10
#define ERROR_HISTOGRAM 100
#define ERROR_MALLOC 101
#define ERROR_REALLOC 102
#define EPSILON 0.001

// functions
int *read_input(int *load);

int check_first_numb(int first_numb);

int *sort_array(int *array, int load);

int put_in_bin(int x, int min_num, float interval_size);

int array_max(const int *array, int array_size);

int array_min(const int *array, int array_size);

int simple_floor(double num);

double simple_median(const int *array, int array_size);

int main(int argc, char *argv[])
{

    int load = 0;
    int n_intervals;
    int *arr_line = NULL;
    int *arr_line_sort = NULL;

    // read n_intervals
    scanf("%d", &n_intervals);
    check_first_numb(n_intervals);
    arr_line = read_input(&load);

    // sort from lowest to highest number
    arr_line_sort = sort_array(arr_line, load);

    // print A solution
    int med_pos = load / 2;
    int numbers = load;
    int min_val = arr_line_sort[0];
    int max_val = arr_line_sort[load - 1];
    double median = simple_median(arr_line_sort, numbers);
    printf("Median %.2f\n", median);
    printf("Pocet cisel: %d\n", numbers);
    printf("Min. hodnota: %d\n", min_val);
    printf("Max. hodnota: %d\n", max_val);

    /* HISTOGRAM */
    float interval_size = (float)(max_val - min_val) / (float)n_intervals;
    float borders[n_intervals];
    int priority[n_intervals];
    int priority_sort[n_intervals];
    float k_i;

    // START calculation with bins
    int bins[n_intervals];
    // init bins to 0
    for (int i = 0; i < n_intervals; ++i)
    {
        bins[i] = 0;
    }

    //  assign number to bins
    for (int i = 0; i < numbers; i++)
    {
        int x = arr_line[i];
        int bin_number = put_in_bin(x, min_val, interval_size);
        // increase count of items in the bin with bin_number
        bins[bin_number] += 1;
    }

    //  calculate intervals from bins. bin size = number of '='
    int bin_max = array_max(bins, n_intervals);
    double scale_by = 25.0 / bin_max;
    printf("Histogram:\n");
    for (int bin_number = 0; bin_number < n_intervals; ++bin_number) {
        int n_of_signs = simple_floor(scale_by * bins[bin_number]);
        float lower_bound = ((float)min_val + (float)bin_number * interval_size);
        float upper_bound = ((float)min_val + ((float )bin_number + 1) * interval_size);
        printf("bin %d : %.1f-%.1f, bin size: %d | ", bin_number, lower_bound, upper_bound, n_of_signs);
        for (int i = 0; i < n_of_signs; ++i) {
            printf("=");
        }
        printf("\n");

    }
    // END calculation with bins


    // count borders values
    for (int i = 0; i < n_intervals + 1; ++i)
    {
        k_i = (float)min_val + (float)i * interval_size;
        borders[i] = k_i;
    }

    // count how many numbers are in which interval - TODO function
    int int_val = 0;
    for (int x = 0; x < n_intervals; ++x)
    {
        for (int y = 0; y < load; ++y)
        {
            if ((borders[x] <= arr_line[y]) && (borders[x + 1] >= arr_line[y]))
            {
                int_val++;
            }
        }
        priority[x] = int_val;
        int_val = 0;
    }

    // find interval with most bins and count multiplier of char '=' - TODO function
    double most_bins;
    double max_bin;
    for (int i = 0; i < n_intervals; i++)
    {
        priority_sort[i] = priority[i];
    }
    *priority_sort = *sort_array(priority_sort, n_intervals);
    most_bins = priority_sort[n_intervals - 1];

    max_bin = 25.000 / most_bins;

    // print histogram
    int count = 0;
    printf("Histogram:\n");
    for (int y = 0; y < n_intervals; ++y)
    {
        if (count < n_intervals)
        {
            printf("%5.1f", borders[count]);
            count++;
            printf(" -");
            printf("%6.1f", borders[count]);
            printf(" |");
            for (int x = 0; x <= priority[y] * max_bin - 1; ++x)
            {
                printf("=");
            }
            priority[y] = 0;
        }
        printf("\n");
    }
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

int *sort_array(int *array, int load)
{
    // sort from lowest to highest number
    for (int i = 0; i < load; ++i)
    {
        for (int j = i + 1; j < load; ++j)
        {
            if (array[i] > array[j])
            {
                int x = array[i];
                array[i] = array[j];
                array[j] = x;
            }
        }
    }
    return array;
}

int put_in_bin(int x, int min_num, float interval_size) {
    if (x == min_num) {
        return 0;
    } else {
        double ret = (x - EPSILON - min_num) / interval_size;
        return simple_floor(ret);
    }
}

int array_max(const int *array, int array_size) {
    int ret = 0;
    for (unsigned int i = 0; i < array_size; i++) {
        if (array[i] > ret) {
            ret = array[i];
        }
    }
    return ret;
}

int array_min(const int *array, int array_size) {
    int ret = 0;
    for (unsigned int i = 0; i < array_size; i++) {
        if (array[i] < ret) {
            ret = array[i];
        }
    }
    return ret;
}

/* Largest integer not greater than X.  */
int simple_floor(double num) {
    if (num < 0)
        return (int) num - 1;
    else
        return (int) num;
}


double simple_median(const int *array, int array_size) {
    double median = 0;
    int l_index = (array_size - 1) / 2;;
    int r_index = array_size / 2;
    // if number of elements are even
    if (array_size % 2 == 0) {
        median = (array[l_index] + array[r_index]) / 2.0;
    } else
        // if number of elements are odd
        median = array[r_index];
    return median;
}
