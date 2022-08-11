#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct
{
    char name[MAX_NAME];
    int age;
} person;

person *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strlen(name);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value *= name[i];
    }
    return hash_value % TABLE_SIZE;
}

void init_hash_table()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }
    // table is empty
}

void print_table()
{
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t%s\n",i, hash_table[i]->name);
        }
    }
    printf("End\n");
}

bool hash_table_insert(person *p)
{
    if (p == NULL)
    {
        return false;
    }
    unsigned int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL)
        {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

// find a person in the table by their name
person* hash_table_lookup(char* name)
{
    unsigned int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] != NULL && strcmp(hash_table[try]->name, name) == 0)
        {
            return hash_table[try];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name)
{
    unsigned int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] != NULL && strcmp(hash_table[try]->name, name) == 0)
        {
            person *tmp = hash_table[try];
            hash_table[try] = NULL;
            return tmp;
        }
    }
    return NULL;
}

int main()
{
    init_hash_table();
    print_table();

    person jacob = {.name = "Jacob", .age=256};
    person kate = {.name = "Kate", .age=27};
    person mpho = {.name = "Mpho", .age=14};
    person sarah = {.name = "Sarah", .age=54};
    person edna = {.name = "Edna", .age=15};
    person maren = {.name = "Maren", .age=25};
    person eliza = {.name = "Eliza", .age=34};
    person robert = {.name = "Robert", .age=1};
    person jane = {.name = "Jane", .age=75};

    hash_table_insert(&jacob);
    hash_table_insert(&kate);
    hash_table_insert(&mpho);
    hash_table_insert(&sarah);
    hash_table_insert(&edna);
    hash_table_insert(&maren);
    hash_table_insert(&eliza);
    hash_table_insert(&robert);
    hash_table_insert(&jane);
    print_table();

    person *tmp = hash_table_lookup("Mpho");
    if (tmp == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found %s.\n", tmp->name);
    }
    tmp = hash_table_lookup("Rod");
    if (tmp == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found %s.\n", tmp->name);
    }

    hash_table_delete("Mpho");
    tmp = hash_table_lookup("Mpho");
    if (tmp == NULL)
    {
        printf("Not found!\n");
    }
    else
    {
        printf("Found %s.\n", tmp->name);
    }

    print_table();

    /*printf("Jacob => %u\n", hash("Jacob"));
    printf("Rod => %u\n", hash("Rod"));
    printf("Maria => %u\n", hash("Maria"));
    printf("July => %u\n", hash("July"));*/

    return 0;
}