#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 20
enum {
    ERROR_MALLOC = -1, ERROR_REALLOC = -2
};

/* functions */
char *load_input();

int main(void) {

    char *input = NULL;
    input = load_input();

    for(int i = 0; i < strlen(input); i ++){
        if (ispunct(input[i])){
            // copy rest of string behind punctuation symbol and paste it in actual position
            strcpy(input + i, input + i + 1);
            // check again same symbol, because of possible existence punctuation
            i --;
        }
    }

    printf("%lu\n", strlen(input));
    printf("%s\n", input);
    return 0;
}

char *load_input() {
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
            fgets(input + capacity - 1, (int) capacity + 1, stdin);
            capacity *= 2;
        }
    }
    // Add null character at the end of the string
    input[strlen(input)] = '\0';
    return input;
}
