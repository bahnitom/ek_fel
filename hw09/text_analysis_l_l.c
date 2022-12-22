/*************************************************************
 * This code defines a linked list node with an integer count and char ^word
 * count field and a pointer to the next node in the list.
 * It also defines functions for creating a new node, appending a new node to the end of the list,
 * printing the list, and sorting the list using bubble sort.
 * To use bubble sort to sort the list, the function repeatedly iterates through the list,
 * swapping adjacent elements that are in the wrong order until the list is sorted.
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int count;
    char *word;
    struct node *next;
} node;

node *create_node(int data) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->count = data;
    new_node->next = NULL;
    return new_node;
}

void append(node **head, int data) {
    node *new_node = create_node(data);
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
        printf("%d ", current->count);
        current = current->next;
    }
    printf("\n");
}

void bubble_sort(node *head) {
    int swapped;
    node *current;
    node *last = NULL;
    do {
        swapped = 0;
        current = head;
        while (current->next != last) {
            if (current->count > current->next->count) {
                int temp = current->count;
                current->count = current->next->count;
                current->next->count = temp;
                swapped = 1;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

int main() {
    node *head = NULL;
    append(&head, 5);
    append(&head, 2);
    append(&head, 3);
    append(&head, 1);
    append(&head, 4);
    printf("Original list: ");
    print_list(head);
    bubble_sort(head);
    printf("Sorted list: ");
    print_list(head);
    return 0;
}//
