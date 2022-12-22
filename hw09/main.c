/*************************************************************
 * read a file from std in
 * cmd line arguments
 * split text to words and remove punctuation
 * list of all unique word and their counts
 * 20 chars for each word <space> word_count
 * count all words, number is considered as word
 * find most and least frequent words. if more than one keep the order as in text
 * Arguments
 * -c : case sensitive
 * without -s argument
 *    order as in the text
 * -s sort output
 *    1 = sort by increasing frequency
 *    2 = sort alphabetically
 *    other values ignored with warning "Warning: Chybna hodnota parametru -s!\n"
 * exit code is always 0
 * output ends by \n
 * check the value of arg -l (positive int)
**************************************************************/


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define MAXWORD 100
#define BUFSIZE 100

/* types */
struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

/* functions */
int getword(char *, int);

struct tnode *talloc(void);        /* allocate memory to new tree node */

char *strDup(char *);              /* copy string into safe place */

<<<<<<< HEAD:hw09/main_pantom.c
char *copy_strings(const char *input);

char *remove_duplicates(char *input);
=======
struct tnode *add_tree_linear(struct tnode *p, char *w, int case_sensitive);

void printtree(struct tnode *);

void freetree(struct tnode *);

struct tnode *sorttree(struct tnode *p, struct tnode *root, int sort_arg);
>>>>>>> hw09_tmp:hw09/main.c

struct tnode *copyTree(struct tnode *p, struct tnode *root);

struct tnode *copy_tree_alpha(struct tnode *p, struct tnode *root);

<<<<<<< HEAD:hw09/main_pantom.c
    char *input = NULL;
    input = load_input();
    remove_punctuations(input);
    int word_count = count_words_in_string(input);
    char *resentance = remove_duplicates(input);

    struct word_count {
        char *word;
        int count;
    } words[word_count];

    int word_num = 0, count = 0;
    char *word;
    char *tmp = input;
    word = strtok(resentance, TOKEN);
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
        printf("%-20s %d\n", words[i].word, words[i].count);
=======
void remove_last_space(char *BUFFER);

/* globals */
int buf[BUFSIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */

char *lower_case(char *word) {
    char *temp = strDup(word); // make a copy

    // adjust copy to lowercase
    unsigned char *tptr = (unsigned char *) temp;
    while (*tptr) {
        *tptr = tolower(*tptr);
        tptr++;
    }
//    free(temp);
    return temp;
}


/*strDup: make a duplicate of s */
char *strDup(char *s) {
    char *p;

    p = malloc(strlen(s) + 1); /* +1 for '\0'*/
    if (p)
        strcpy(p, s);

    return p;
}

/*************************
 * linear search:  nodes are added only to left
 * Keeps the original order
**************************/
struct tnode *add_tree_linear(struct tnode *p, char *w, int case_sensitive) {
    if (case_sensitive == 0)
        w = lower_case(w);
    if (!p) {                          /* a new word has arrived */
        p = talloc();                  /* make a new node */
        p->word = strDup(w);           /* copy data to it */
        p->count = 1;
        p->left = p->right = NULL;
    } else if (strcmp(w, p->word) == 0)
        ++p->count;                    /* repeated word */
    else
        /* in correlation with printtree corresponds to original order*/
        p->left = add_tree_linear(p->left, w, case_sensitive);
    return p;
}


/* print: in-order print of tree p - decreasing order version */
void printtree(struct tnode *p) {
    if (p) {
        printtree(p->right);
        printf("%-20s %d\n", p->word, p->count);
        printtree(p->left);
>>>>>>> hw09_tmp:hw09/main.c
    }
}

<<<<<<< HEAD:hw09/main_pantom.c
    free(input);
    free(resentance);
    return 0;
}

char *remove_duplicates(char *input) {

    unsigned long len = strlen(input);
    char *word = NULL, *resentence = NULL, *input_copy = NULL;
    //allocate memory
    resentence = malloc(len + 1);
    if (resentence == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
    } else {
        input_copy = copy_strings(input);
        // get first word
        word = strtok(input_copy, TOKEN);

        if (word != NULL){// && strstr(resentence, word) == NULL)
            strcpy(resentence, word);
            while ((word = strtok(NULL, TOKEN)) != NULL){
                if (strstr(resentence, word) == NULL){ /*z nejakeho duvodu vyhodnoti ze slovo Ja se uz v retezci vyskytuje*/
                    strcat(resentence, TOKEN); // add space to string
                    strcat(resentence, word);  // add word to string
                }
            }
        }
    }
    free(input_copy);
    return resentence;
}

char *copy_strings(const char *input) {
    //need use malloc, because of valgrind
    char *input_copy = malloc(strlen(input) + 1);
    if (input_copy == NULL) {
        fprintf(stderr, "Error malloc\n");
        exit(ERROR_MALLOC);
=======
int MAX_COUNT = 1000000;
int MIN_COUNT = 0;

int max_count(struct tnode *p) {
    if (p) {
        int curr = p->count;
        //  p->right is NULL
        int next = max_count(p->left);
        return curr > next ? curr : next;
    } else {
        return MIN_COUNT;
    }
}


int min_count(struct tnode *p) {
    if (p) {
        int curr = p->count;
        int next = min_count(p->left);
        return curr < next ? curr : next;
    } else {
        return MAX_COUNT;
>>>>>>> hw09_tmp:hw09/main.c
    }
}

void words_with_count(struct tnode *p, int count) {
    if (p) {
        if (p->count == count) {
            printf(" %s", p->word);
        }
        words_with_count(p->left, count);
    }
}

/* Counts no. of nodes in linked list */
int words_count(struct tnode *p) {
    int count = 0; // Initialize count
    struct tnode *current = p; // Initialize current
    while (current != NULL) {
        count++;
        current = current->left;
    }
    return count;
}

/* copyTree: copy nodes in root into p according to frequency of occurrence. */
struct tnode *copyTree(struct tnode *p, struct tnode *root) {
    if (!p) {
        p = talloc();
        p->word = strDup(root->word);
        p->count = root->count;
        p->left = p->right = NULL;
    } else if (root->count >= p->count)
        p->left = copyTree(p->left, root);
    else
        p->right = copyTree(p->right, root);
    return p;
}

struct tnode *copy_tree_alpha(struct tnode *p, struct tnode *root) {
    if (!p) {
        p = talloc();
        p->word = strDup(root->word);
        p->count = root->count;
        p->left = p->right = NULL;
    } else if (strcmp(root->word, p->word) >= 0)
        p->left = copy_tree_alpha(p->left, root);
    else
        p->right = copy_tree_alpha(p->right, root);
    return p;
}


/* sorttree: performs inorder traversal on root and creates a BST p according
 * to frequency of occurrence */
struct tnode *sorttree(struct tnode *p, struct tnode *root, int sort_arg) {

    if (root) {
        p = sorttree(p, root->left, sort_arg);
        if (sort_arg == 1)
            p = copyTree(p, root);
        if (sort_arg == 2)
            p = copy_tree_alpha(p, root);
        p = sorttree(p, root->right, sort_arg);
    }
    return p;
}


/* talloc: make a tnode */
struct tnode *talloc(void) {
    return malloc(sizeof(struct tnode));
}


/* freetree: free allocated heap memory of node tree */
void freetree(struct tnode *node) {
    if (!node)
        return;
    freetree(node->left);
    freetree(node->right);
    free(node->word);
    free(node);
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isblank(c = getch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

/* get a (possibly pushed back) character */
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

int main(int argc, char *argv[]) {
    struct tnode *root = NULL;                /* root node */
    struct tnode *sorted = NULL;                /* root node */
    char word[MAXWORD];                /* currently read word */
    int case_sensitive_arg = 0;
    int sort_arg = 0;
    int max_cnt = 0;
    int min_cnt = 0;
    int opt;
    int s_value;

    while ((opt = getopt(argc, argv, "s:c")) != -1) {
        switch (opt) {
            case 's':
                s_value = atoi(optarg);
                // Handle the -s option
                if (s_value == 1) {
                    // Do something for -s 1
                    sort_arg = 1;
                } else if (s_value == 2) {
                    // Do something for -s 2
                    sort_arg = 2;
                } else {
                    // do mandatory
                    sort_arg = 0;
                    fprintf(stderr, "Invalid value for -s option: %d\n", s_value);
                    return 1;
                }
                break;
            case 'c':
                // Do something for -c
                case_sensitive_arg = 1;
                break;
//            case 's': //both of them
//            case 'c':
//                s_value = atoi(optarg);
//                // Handle the -s option
//                if (s_value == 1) {
//                    // Do something for -s 1
//                    sort_arg = 1;
//                } else if (s_value == 2) {
//                    // Do something for -s 2
//                    sort_arg = 2;
//                }
//                case_sensitive_arg = 1;
//                break;
            case '?':
                // Handle invalid options
                fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
                exit(0);
        }
    }
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = add_tree_linear(root, word, case_sensitive_arg); /* build tree */
    //printf("\nOriginal order -c %d, -s %d\n", case_sensitive_arg, sort_arg);
    max_cnt = max_count(root);
    min_cnt = min_count(root);
    printf("Seznam slov:\n");
    if (sort_arg == 0) {
        printtree(root);
    }
    if (sort_arg == 1) {
        //printf("Increasing count -c %d, -s %d\n", case_sensitive_arg, sort_arg);
        sorted = sorttree(sorted, root, sort_arg);
        printtree(sorted);
        freetree(sorted);
        sorted = NULL;
    }
    if (sort_arg == 2) {
        //printf("Alphabet order -c %d, -s %d\n", case_sensitive_arg, sort_arg);
        sorted = sorttree(sorted, root, sort_arg);
        printtree(sorted);
        //freetree(root);
        freetree(sorted);
        //root = NULL;
        sorted = NULL;
    }
    printf("%-20s %d", "Pocet slov:", words_count(root));
    printf("\n%-20s", "Nejcastejsi:");
    words_with_count(root, max_cnt);
    printf("\n%-20s", "Nejmene caste:");
    words_with_count(root, min_cnt);
    printf("\n");
    freetree(root);
    root = NULL;
    return 0;
}
