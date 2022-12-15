#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
enum {
    ERROR_MALLOC = -1, ERROR_REALLOC = -2
};


int main(void) {
    size_t capacity = SIZE;
    char *input = malloc(capacity * sizeof(char));
    if (input == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
    } else {
        fgets(input, (int) capacity, stdin);
        while (capacity - 1 == strlen(input) && input[capacity - 2] != '\n') {
            char *tmp = realloc(input, 2 * capacity * sizeof(char));
            if (tmp == NULL) {
                fprintf(stderr, "Error realloc\n");
                free(input);
                input = NULL;
                exit(ERROR_REALLOC);
            }
            input = tmp;
            // read missing part of sentence
            fgets(input + capacity - 1, (int) capacity + 1, stdin); //TODOs
            capacity *= 2;
        }
    }
    printf("%lu\n", strlen(input));
    printf("%s", input);
    return 0;
}
