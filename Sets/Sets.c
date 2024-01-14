#include "Sets.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


size_t djb33x_hash(const char *str, size_t length) 
{
    size_t hash = 5381;
    for (size_t i = 0; i < length; i++) {
        hash = (hash << 5) + hash + str[i];
    }
    return hash;
}

struct set_node 
{
    struct linked_list self;
    const char *key;
    size_t key_len;
    struct set_node *next;
};

struct set_table 
{
    struct linked_list **nodes;
    size_t hashmap_size;
};

struct set_table *set_table_new(const size_t hashmap_size) 
{
    struct set_table *table = malloc(sizeof(struct set_table));

    if (!table) 
    {
        return NULL;
    }

    table->hashmap_size = hashmap_size;
    table->nodes = calloc(hashmap_size, sizeof(struct linked_list));

    if (!table->nodes) 
    {
        free(table);
        return NULL;
    }

    return table;
}

struct set_node *set_insert(struct set_table *table, const char *key, const size_t key_len) 
{
    struct set_node *new_node = malloc(sizeof(struct set_node));
    if (!new_node) 
    {
        return NULL;
    }

    new_node->self.next = NULL;
    new_node->self.count = 1;
    new_node->key = _strdup(key);
    new_node->key_len = key_len;

    size_t hash = djb33x_hash(key, key_len) % table->hashmap_size;
    append(&table->nodes[hash], &new_node->self);

    return new_node;
}

struct set_node *set_search(const struct set_table *table, const char *key, const size_t key_len) 
{
    struct linked_list *current;

    size_t hash = djb33x_hash(key, key_len) % table->hashmap_size;
    current = table->nodes[hash];
    while (current) 
    {
        struct set_node *current_node = (struct set_node *)current;
        if (current_node->key_len == key_len && strcmp(current_node->key, key) == 0)
        {
            return current_node; //Found the key
        }
        current = current->next;
    }

    return NULL;
}

int set_remove(struct set_table *table, const char *key, const size_t key_len) 
{
    size_t hash = djb33x_hash(key, key_len) % table->hashmap_size;
    struct linked_list *current = table->nodes[hash];
    struct linked_list *prev = NULL;

    while (current) {
        struct set_node *current_node = (struct set_node *)current;
        if (current_node->key_len == key_len && strncmp(current_node->key, key, key_len) == 0) 
        {
            if (prev) 
            {
                prev->next = current->next;
            } 
            else 
            {
                table->nodes[hash] = current->next;
            }

            free((void *)current_node->key);
            free(current_node); 

            return 0; //Removal successful
        }

        prev = current;
        current = current->next;
    }

    return -1; //Key not found
}

void print_set_contents(const struct set_table *table) {
    printf("Set Contents:\n");

    for (size_t i = 0; i < table->hashmap_size; ++i) 
    {
        struct linked_list *current = table->nodes[i];
        while (current)
        {
            struct set_node *current_node = (struct set_node *)current;
            printf("%s, ", current_node->key);
            current = current->next;
        }
    }

    printf("\n");
}

void set_free(struct set_table *table) {
    while (length(*table->nodes) > 0) 
    {
        struct linked_list *current = get_tail(table->nodes);
        struct set_node *current_node = (struct set_node *)current;

        free((void *)current_node->key); 
        free(current_node); 
    }

    free(table->nodes);
    free(table);
}

int main() {
    struct set_table *my_set = set_table_new(10);

   printf("--------APPEND--------\n");
    struct set_node *inserted_node_1 = set_insert(my_set, "apple", strlen("apple"));
    struct set_node *inserted_node_2 = set_insert(my_set, "orange", strlen("orange"));
    struct set_node *inserted_node_3 = set_insert(my_set, "banana", strlen("banana"));

    print_set_contents(my_set);

    printf("------SEARCH KEY------\n");
    struct set_node *result = set_search(my_set, "banana", strlen("banana"));

    if (result) {
        printf("Key found: %s\n", result->key);
    }
     else 
    {
        printf("Key not found\n");
    }

    printf("--------REMOVE--------\n");
    set_remove(my_set, "apple", strlen("apple"));
    print_set_contents(my_set);

  free(my_set);
    return 0;
}