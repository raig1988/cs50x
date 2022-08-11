#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int value;
    struct node *next;
} node;

void printlist(node *head)
{
    node *tmp = head;
    while (tmp != NULL)
    {
        printf("%i -", tmp->value);
        tmp = tmp->next;
    }
    printf("/n");
}

int main()
{
    node *n1, *n2, *n3;
    node *head;

    n1 = malloc(sizeof(node));
    n2 = malloc(sizeof(node));
    n3 = malloc(sizeof(node));

    n1->value = 1;
    n2->value = 2;
    n3->value = 3;

    head = n1;
    n1->next = n2;
    n2->next = n3;
    n3->next = NULL;

    node *n4;
    n4 = malloc(sizeof(node));
    n4->value = 4;
    n4->next = n3;
    n2->next = n4;

    printlist(head);
    return 0;

}