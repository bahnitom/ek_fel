#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_WORD 100
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */


/* Arrays of Structures */
struct key {
    char *word;
    int count;
} word_counts[] = {
        "ahoj", 0,
        "jak", 0,
        "se", 0,
        "mas", 0
};

#define NKEYS (sizeof word_counts/sizeof word_counts[0])

int get_word(char *, int);

int binsearch(char *, struct key *, int);

//int getch(void);
//
//void ungetch(int);

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
    while (get_word(word, MAX_WORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, word_counts, NKEYS)) >= 0)
                word_counts[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (word_counts[n].count > 0)
            printf("%4d %s\n",
                   word_counts[n].count, word_counts[n].word);
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
