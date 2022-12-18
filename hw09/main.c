#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20
#define TOKEN " "
enum {
    ERROR_MALLOC = -1, ERROR_REALLOC = -2
};

// List of punctuation characters to remove
const char PUNCTUATIONS[] = "!#$%&'()*+,-./:;<=>?@[]^_`{|}~";

/* functions */
char *load_input();

void remove_punctuations(char *input);

int count_words_in_string(const char *input);

char *copy_strings(const char *input);


int main(void) {

    char *input = NULL;
    input = load_input();
    remove_punctuations(input);
    int word_count = count_words_in_string(input);
    char *input_copy = copy_strings(input);

    /*maybe function*/
//    char *word;
//    int cnt = 0;
//    word = strtok(input_copy, TOKEN);
//    while (word != NULL) {
//        printf("%s\n", word);
//        word = strtok(NULL, TOKEN);
//        cnt++;
//    }


//    char *word = "Jak";
//    if (strstr(input, word) != NULL) {
//        printf("slovo %s je v retezci\n", word);
//    } else {
//        printf("slovo %s neni v retezci\n", word);
//    }


    struct word_count {
        char *word;
        int count;
    } words[word_count];

    int word_num = 0, count = 0;
    char *word;
    char *tmp = input;
    word = strtok(input_copy, TOKEN);
    //get first word from string
    while (word != NULL) {
        // word == NULL --> in string is not any more words
        words[word_num].count = 0; //start from zero
        unsigned long word_len = strlen(word);
        while ((tmp = strstr(tmp, word)) != NULL) { // word exist in string
            //we don't need to check same word
            tmp += word_len + 1;
            count++;
        }
        // if while not true, tmp set to NULL
        if(tmp == NULL){
            tmp = input;
        }
        //set values to actual word
        words[word_num].word = word;
        words[word_num].count = count;
        word_num++;
        count = 0;
        // get another word from string
        word = strtok(NULL, TOKEN);
    }
    //print
    for (int i = 0; i < word_num; i++) {
        printf("%s %d\n", words[i].word, words[i].count);
    }

//    printf("%d\n", word_count);
//    printf("%s\n", input);
    free(input);
    free(input_copy);

    return 0;
}

char *copy_strings(const char *input) {
    //need use malloc, because of valgrind
    char *input_copy = malloc(strlen(input) + 1);
    if (input_copy == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
    } else {
        strcpy(input_copy, input);
    }
    return input_copy;
}

int count_words_in_string(const char *input) {
    int count = 0;
    // read text to end + 1, because to find '\0'character
    for (int i = 0; i < strlen(input) + 1; i++) {
        if (input[i] == 32 || input[i] == '\0') {
            count++;
        }
    }
    return count;
}

void remove_punctuations(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (strchr(PUNCTUATIONS, input[i]) != NULL) {
            // Shift the rest of the string one character to the left
            memmove(input + i, input + i + 1, strlen(input + i + 1) + 1);
            // check again same symbol, because of possible existence punctuation
            i--;
        }
    }
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
