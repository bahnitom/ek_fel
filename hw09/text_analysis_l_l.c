#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int count;
    char *word;
    struct node *next;
} node;

node *create_node(int count, char *word) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->count = count;
    new_node->word = strdup(word);
    new_node->next = NULL;
    return new_node;
}

void append(node **head, int count, char *word) {
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

void print_list(node *head) {
    node *current = head;
    while (current != NULL) {
        printf("%d %s\n", current->count, current->word);
        current = current->next;
    }
}

int compare_count(node *a, node *b) {
    return a->count - b->count;
}

int compare_word(node *a, node *b) {
    return strcmp(a->word, b->word);
}

void bubble_sort(node *head, int (*compare)(node*, node*)) {
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
    node *head = NULL;
    append(&head, 5, "apple");
    append(&head, 2, "banana");
    append(&head, 3, "cherry");
    append(&head, 1, "date");
    append(&head, 4, "elderberry");
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
