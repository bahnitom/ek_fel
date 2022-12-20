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

char *remove_duplicates(char *input);


int main(void) {

    char *input = NULL;
    input = load_input();
    remove_punctuations(input);
    int word_count = count_words_in_string(input);
    char *input_copy = remove_duplicates(input);

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
        if (tmp == NULL) {
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
//    printf("%s\n", input_copy);
    free(input);
    free(input_copy);

    return 0;
}

char *remove_duplicates(char *input) {

    unsigned long len = strlen(input);
    char *word = NULL;
    char *resentence;
    //allocate memory
    resentence = malloc(len + 1);
    if (resentence == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
    } else {
        // get first word
        *resentence = 0;
//        strcpy(resentence,input);
        word = strtok(input, TOKEN);
        /*z nejakeho duvoud strtok okrouhne i input string,ktery pak pouzivam --> spatne
         * pokud input prekopiruju do resentence a pote ho vynulu tak podle debugu vse
         * sedi a melo by fungovat ale ze zahadneho duvodu program pri vypisu preskoci jedno slovo --> spatne*/


        if (word != NULL){// && strstr(temp1, temp) == NULL)
            strcpy(resentence, word);
            while ((word = strtok(NULL, TOKEN)) != NULL){
                if (strstr(resentence, word) == NULL){
                    strcat(resentence, TOKEN);
                    strcat(resentence, word);
                }
            }
        }
        puts(resentence);
    }
    return resentence;
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
