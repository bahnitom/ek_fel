#include <stdio.h>
#include <stdlib.h>

/*Příklad implementace spojového seznamu*/

typedef struct node_t
{
    int value;
    struct node_t *next;

} node_t;

typedef struct list_t
{
    node_t *head;
    node_t *tail;
    int size;

}list_t;

enum nodetype_t {INT, DOUBLE, FLOAT, VOIDPTR, LISTPTR};

typedef struct varnode_t
{
    /*bud ukazatel na *void value*/
    /*nebo ...*/
    union
    {
        int i;
        double d;
        float f;
        void *v;
        list_t *list;
    }value;
    enum nodetype_t type;
    struct varnode_t *next;
}varnode_t;

// functions
node_t *list_add(node_t **head, int value);
void list_print(node_t *head);
node_t *list_pop(node_t **head);

int main(void)
{
    node_t *head = NULL, *node;
    head = list_add(&head, 2); /*hlavicka je NULL, proto ji musime nastavit*/
    if (head != NULL)
    {
        list_add(&head, 3); /*zde uz hlavicku nechceme posouvat*/
        list_add(&head, 5);
        list_add(&head, 8);
        list_print(head);

        node = list_pop(&head);
        printf("popped: %d\n", node->value);
        list_print(head);
        /*DODELAT FREE !!!*/
    }
    return 0;
}

/*@return Address of the newly created node*/
node_t *list_add(node_t **head, int value) /* dvojity pointer abychom mohli ukladat hodnoty do hlavicky*/
{
    node_t *ret;
    if (*head == NULL)
    {
        *head = malloc(sizeof(node_t));
        if (*head == NULL)
        {
            fprintf(stderr, "Error malloc\n");
            return NULL;
        }
        (*head)->value = value;
        (*head)->next = NULL;
        ret = *head;
    }
    else
    {
        /*nejdrive  musime dojit na konec seznamu*/
        node_t *tail;
        tail = *head; /*prochazi seznam od zacatku*/
        while (tail->next != NULL)
        {
            tail = tail->next;
        }

        ret = malloc(sizeof(node_t));
        if (ret == NULL)
        {
            fprintf(stderr, "Error malloc\n");
            return NULL;
        }
        ret->value = value;
        ret->next = NULL;
        tail->next = ret;
    }
    return ret;
}

void list_print(node_t *head)
{
    node_t *cursor;
    cursor = head;      /*nastavime cursor na zacatek*/
    if (cursor == NULL) // prazdny seznam
    {
        return;
    }
    do
    {
        printf("%d, ", cursor->value);
        cursor = cursor->next; /*bez na dalsi polozku seznamu*/
    } while (cursor != NULL);
    printf("\n");
}

node_t *list_pop(node_t **head)
{
    /*FIFO pop, odebrat hlavicku, posunout dal a vratit popped node*/
    if (*head == NULL)
    {
        return NULL;
    }
    node_t *ret;
    ret = *head; /*ulozi soucasnou hlavicku, kterou vyhodime*/
    *head = (*head)->next;
    return ret;
}
