/*************************************************************
* Write a program that prints the distinct words in its input sorted into
* decreasing order of frequency of occurrence. Precede each word by its count.
*
* By Faisal Saadatmand
*

* NOTE: I included a definition for sorttree and copytree for academic
* purposes. They are not used in the code
**************************************************************/

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

struct tnode *add_tree_linear(struct tnode *p, char *w, int case_sensitive);

void printtree(struct tnode *);

void freetree(struct tnode *);

struct tnode *sorttree(struct tnode *p, struct tnode *root, int sort_arg);

struct tnode *copyTree(struct tnode *p, struct tnode *root);

struct tnode *copy_tree_alpha(struct tnode *p, struct tnode *root);

/* globals */
int buf[BUFSIZE];         /* buffer from ungetch */
int bufp = 0;             /* next free position in buf */

char *lower_case(char *word) {
    char *temp = strDup(word); // make a copy

    // adjust copy to lowercase
    unsigned char *tptr = (unsigned char *)temp;
    while(*tptr) {
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
    }
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

int main(void) {
    struct tnode *root = NULL;                /* root node */
    struct tnode *sorted = NULL;                /* root node */
    char word[MAXWORD];                /* currently read word */
    int case_sensitive_arg = 1;
    int sort_arg = 1;

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            root = add_tree_linear(root, word, case_sensitive_arg); /* build tree */
    printf("\nOriginal order -c %d, -s %d\n", case_sensitive_arg, sort_arg);
    printtree(root);

    printf("\nIncreasing count -c %d, -s %d\n", case_sensitive_arg, sort_arg);
    sorted = sorttree(sorted, root, sort_arg);
    printtree(sorted);
    freetree(sorted);
    sorted = NULL;

    sort_arg = 2;
    printf("\nAlphabet order -c %d, -s %d\n", case_sensitive_arg, sort_arg);
    sorted = sorttree(sorted, root, sort_arg);
    printtree(sorted);
    freetree(root);
    freetree(sorted);
    root = NULL;
    sorted = NULL;
    return 0;
}
