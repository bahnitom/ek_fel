#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WORD 100
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */


/* Case-sensitive unique words in order in which they appear in the text */
struct key {
    char word[MAX_WORD];
    int count;
} unique_words_counts[] = {
        "Ahoj", 0,
        "jak", 0,
        "se", 0,
        "mas", 0,
        "Mam", 0,
        "dobre", 0,
        "Jak", 0,
        "ty", 0,
        "Ja", 0,
        "mam", 0,
        "taky", 0,
};

#define NKEYS (sizeof unique_words_counts/sizeof unique_words_counts[0])

void to_lower_case(char str[MAX_WORD]) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}


void case_insensitive(struct key table[]) {
    struct key ret[NKEYS];
    int n;
    for (n = 0; n < NKEYS; n++) {
        to_lower_case(table[n].word);
    }
}


int get_word(char *, int);

int binsearch(char *, struct key *, int);

int simple_search(char *word, struct key table[], int n);

int getch(void) /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


/* count C keywords */
int main() {
    int n;
    char word[MAX_WORD];
    bool lower_case = true;
    if (lower_case)  case_insensitive(unique_words_counts);

    while (get_word(word, MAX_WORD) != EOF)
        if (isalpha(word[0])) {
            if (lower_case) to_lower_case(word);
            if ((n = simple_search(word, unique_words_counts, NKEYS)) >= 0)
                unique_words_counts[n].count++;
        }
    for (n = 0; n < NKEYS; n++)
        if (unique_words_counts[n].count > 0)
            printf("%-20s %d\n", unique_words_counts[n].word, unique_words_counts[n].count);
    printf("%-20s %lu\n", "Pocet slov:", NKEYS);
    printf("%-20s %lu\n", "Nejcastejsi:", NKEYS);
    printf("%-20s %lu\n", "Nejmene caste:", NKEYS);
    return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int simple_search(char *word, struct key table[], int n) {
    for (int i = 0; i < n; ++i) {
        if ((strcmp(word, table[i].word)) == 0)
            return i;
    }
    return -1;
}

/* get_word: get next word or character from input */
int get_word(char *word, int lim) {
    int c;
    char *w = word;
    while (isspace(c = getch()));
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
