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
        printf("%d -", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}

node* create_new_node(int value)
{
    node *result = malloc(sizeof(node));
    result->value = value;
    result->next = NULL;
    return result;
}

node* insert_at_head(node **head, node *node_to_insert)
{
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
}

void insert_after_node(node *node_to_insert_after, node* newnode)
{
    newnode->next = node_to_insert_after->next;
    node_to_insert_after->next = newnode;
}

node* find_node(node *head, int value)
{
    node *tmp = head;
    while (tmp != NULL)
    {
        if (tmp->value == value)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

int main ()
{
    node *head = NULL;
    node *tmp;

    for (int i = 0; i < 25; i++)
    {
        tmp = create_new_node(i);
        insert_at_head(&head, tmp);
    }

    tmp = find_node(head, 13);
    printf("found node with value %i\n", tmp->value);

    insert_after_node(tmp, create_new_node(75));

    printlist(head);
    return 0;

}