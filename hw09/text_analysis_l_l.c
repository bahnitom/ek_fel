#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
 * @return head of new linked list
 */
node *add_to_unique_list(node **head, char *word, int case_sensitive) {
    if (case_sensitive == 0)
        word = lower_case(word);
    node *current = *head;
    if (*head == NULL) {                                 /* a new word has arrived */
        *head = create_node(1, word);
    } else if (strcmp(word, current->word) == 0)
        ++current->count;                                /* repeated word increase count*/
    else
        current->next = add_to_unique_list(&current->next, word, case_sensitive);
    return *head;
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


void build_linked_list(char word[MAXWORD], node **head, int case_sensitive) {
    while (get_word(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            append(head, 1, word, case_sensitive); /* build tree */
}


void print_list(node *head) {
    node *current = head;
    while (current != NULL) {
        printf("%-20s %d\n", current->word, current->count);
        current = current->next;
    }
}

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

int main() {
    char word[MAXWORD];
    int case_sensitive = 1;
    node *head = NULL;
    while (get_word(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            head = add_to_unique_list(&head, word, case_sensitive); /* build tree */
    printf("Original list:\n");
    print_list(head);
    printf("Sorting by count:\n");
    bubble_sort(head, compare_count);
    print_list(head);
    printf("Sorting by word:\n");
    bubble_sort(head, compare_word);
    print_list(head);
    return 0;
}
