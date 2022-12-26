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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>

typedef struct node {
    int count;
    char *word;
    struct node *next;
} node;

char *to_lower_case(char *string) {
    int length = strlen(string);
    char *lower_case = (char *) malloc((length + 1) * sizeof(char));
    for (int i = 0; i < length; i++) {
        lower_case[i] = tolower(string[i]);
    }
    lower_case[length] = '\0';
    return lower_case;
}

char *strDup(char *s) {
    char *p;
    p = malloc(strlen(s) + 1); /* +1 for '\0'*/
    if (p)
        strcpy(p, s);
    return p;
}

char *lower_case(char *word) {
    char *temp = strDup(word); // make a copy
    // adjust copy to lowercase
    unsigned char *tptr = (unsigned char *) temp;
    while (*tptr) {
        *tptr = tolower(*tptr);
        tptr++;
    }
    return temp;
}

node *create_node(int count, char *word) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->count = count;
    new_node->word = strDup(word);
    new_node->next = NULL;
    return new_node;
}

void append(node **head, int count, char *word, int case_sensitive) {
    /* sample use of indirection operator precedence
     * parentheses are necessary around (*head) similar to (*ip)++
     * pp->x is shorthand for (*pp).y)
     *     printf("append '%s', count %d,  after '%s', count %d.\n",
           word, count, (*head)->word, (*head)->count);
           printf("2nd append '%s', count %d,  after '%s', count %d.\n",
           word, count, (**head).word, (*head)->count);
     */
    if (case_sensitive == 0) {
        word = lower_case(word);
    }
    node *new_node = create_node(count, word);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

/******************************
 * Add new word or increase count of already added word
 * @param head of linked list
 * @param word word to add
 * @param case_sensitive 0 = insensitive, 1 = sensitive
 * @return pointer to head node of new linked list
 */
node *add_to_unique_list(node *head, char *word, int case_sensitive) {
    if (case_sensitive == 0)
        word = lower_case(word);
    if (head == NULL) {                                 /* a new word has arrived */
        head = create_node(1, word);
    } else if (strcmp(word, head->word) == 0)
        ++head->count;                                /* repeated word increase count*/
    else
        head->next = add_to_unique_list(head->next, word, case_sensitive);
    return head;
}

int MAX_COUNT = 1000000;
int MIN_COUNT = 0;

/***********
 * argument is node, head is pointer to node
 * when `*` is applied to a pointer, it accesses the object the pointer points to
 * @param head  pointer to node
 * @return
 */
int max_count(node *head) {
    if (head) {
        int curr = head->count;
        int next = max_count(head->next);
        return curr > next ? curr : next;
    } else {
        return MIN_COUNT;
    }
}

int min_count(node *head) {
    if (head) {
        int curr = head->count;
        int next = min_count(head->next);
        return curr < next ? curr : next;
    } else {
        return MAX_COUNT;
    }
}

/* Counts no. of nodes in linked list */
int words_count(node *head) {
    int count = 0; // Initialize count
    node *current = head; // Initialize current
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

void words_with_count(node *p, int count) {
    if (p) {
        if (p->count == count) {
            printf(" %s", p->word);
        }
        words_with_count(p->next, count);
    }
}

void free_list(struct node *p) {
    if (!p)
        return;
    free_list(p->next);
    free(p->word);
    free(p);
}

#define MAXWORD 100
#define BUF_SIZE 100

int buf[BUF_SIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */

/* get a (possibly pushed back) character */
int get_ch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void un_get_ch(int c) {
    if (bufp >= BUF_SIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


int get_word(char *word, int lim) {
    int c;
    char *w = word;

    while (isblank(c = get_ch()));
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = get_ch())) {
            un_get_ch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

void print_list(node *, int);

int compare_count(node *a, node *b) {
    return a->count - b->count;
}

int compare_word(node *a, node *b) {
    return strcmp(a->word, b->word);
}

void bubble_sort(node *head, int (*compare)(node *, node *)) {
    int swapped;
    node *current;
    node *last = NULL;
    do {
        swapped = 0;
        current = head;
        while (current->next != last) {
            if (compare(current, current->next) > 0) {
                int temp_count = current->count;
                current->count = current->next->count;
                current->next->count = temp_count;
                char *temp_word = current->word;
                current->word = current->next->word;
                current->next->word = temp_word;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

/****
 * * without -s argument
 *    order as in the text
 * -s sort output
 *    1 = sort by increasing frequency
 *    2 = sort alphabetically
 * @return
 */
int main(int argc, char *argv[]) {
    char word[MAXWORD];
    node *head = NULL;
    bool case_sensitive_arg = false;
    int sort_arg = 0;
    int word_length_arg = -1;
    int max_cnt = 0;
    int min_cnt = 0;
    int word_cnt = 0;
    int opt;


    while ((opt = getopt(argc, argv, "s:l:c")) != -1) {
        switch (opt) {
            case 's':
                sort_arg = atoi(optarg);
                if (sort_arg < 1 || sort_arg > 2) {
                    fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
                    exit(0);
                }
                break;
            case 'c':
                case_sensitive_arg = true;
                break;
            case 'l':
                word_length_arg = atoi(optarg);
                if (word_length_arg < 0) {
                    fprintf(stderr, "Warning: Chybna hodnota parametru -l!\n");
                    exit(0);
                }
                break;
            default:
                printf("Invalid option %d\n", opt);
                exit(0);
        }
    }
//    printf("case_sensitive=%d, sort_ord=%d, word_length_arg=%d\n",
//           case_sensitive_arg, sort_arg, word_length_arg);
    while (get_word(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            head = add_to_unique_list(head, word, case_sensitive_arg); /* build liked list */

    max_cnt = max_count(head);
    min_cnt = min_count(head);
    word_cnt = words_count(head);
    switch (sort_arg) {
        case 0:
            print_list(head, word_length_arg);
            break;
        case 1:
            bubble_sort(head, compare_count);
            print_list(head, word_length_arg);
            break;
        case 2:
            bubble_sort(head, compare_word);
            print_list(head, word_length_arg);
            break;
        default:
            fprintf(stderr, "Warning: Chybna hodnota parametru -s!\n");
            exit(0);
    }
    printf("%-20s %d", "Pocet slov:", word_cnt);
    printf("\n%-20s", "Nejcastejsi:");
    words_with_count(head, max_cnt);
    printf("\n%-20s", "Nejmene caste:");
    words_with_count(head, min_cnt);
    printf("\n");
    free_list(head);
    head = NULL;
    return 0;
}

void print_list(node *head, int word_len) {
    node *current = head;
    bool header = true;
    if (word_len >= 0) {
        while (current != NULL) {
            if (strlen(current->word) == word_len) {
                if (header)
                    printf("Seznam slov:\n");
                header = false;
                printf("%-20s %d\n", current->word, current->count);
            }
            current = current->next;
        }
    } else {
        while (current != NULL) {
            if (header)
                printf("Seznam slov:\n");
            header = false;
            printf("%-20s %d\n", current->word, current->count);
            current = current->next;
        }
    }
}
