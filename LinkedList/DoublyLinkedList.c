#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define get_list(x) &(x.self)

struct doubly_linked_list {
    struct doubly_linked_list* next;
    struct doubly_linked_list* prev;
    unsigned int count;
};

int length(struct doubly_linked_list* pointer) {
    return pointer ? pointer->count : 0;
}

struct doubly_linked_list* get_tail(struct doubly_linked_list** pointer) {
    struct doubly_linked_list* current_pointer = *pointer;
    struct doubly_linked_list* last_pointer = NULL;

    while (current_pointer) {
        last_pointer = current_pointer;
        current_pointer = current_pointer->next;
    }

    return last_pointer;
}

int append(struct doubly_linked_list** pointer, struct doubly_linked_list* item) {
    struct doubly_linked_list* tail = get_tail(pointer);

    if (!tail) {
        *pointer = item;
        item->next = NULL;
        item->prev = NULL;
        (*pointer)->count = 1;
        printf("List was empty\n");
        return 0;
    }

    printf("Successfully item added\n");
    tail->next = item;
    item->prev = tail;
    item->next = NULL;

    (*pointer)->count++;
    return 0;
}

int remove_item(struct doubly_linked_list** pointer, struct doubly_linked_list* item) {
    if (!item || !*pointer)
        return -1;

    struct doubly_linked_list* current_pointer = *pointer;

    for (int i = 0; i < (*pointer)->count; i++) {
        if (current_pointer == item) {
            if (i == 0) {
                int count = (*pointer)->count - 1;
                *pointer = current_pointer->next;
                if (current_pointer->next)
                    current_pointer->next->prev = NULL;
                
                (*pointer)->count = count;
                return 0;
            } else {
                (*pointer)->count--;

                if (current_pointer->prev)
                    current_pointer->prev->next = current_pointer->next;

                if (current_pointer->next)
                    current_pointer->next->prev = current_pointer->prev;

                
                return 0;
            }
        }
        current_pointer = current_pointer->next;
    }

    printf("Item not found!!\n");
    return -1;
}

struct int_doubly_list {
    struct doubly_linked_list self;
    int value;
};

void shuffle_list(struct doubly_linked_list** pointer) {
    struct doubly_linked_list* current_pointer = *pointer;

    int count = length(current_pointer);
    int i, j, temp;

    for (i = count - 1; i > 0; i--) {
        j = rand() % (i + 1);

        if (i != j) {
            struct doubly_linked_list* node_i = current_pointer;
            struct doubly_linked_list* node_j = current_pointer;

            while (i--)
                node_i = node_i->next;

            while (j--)
                node_j = node_j->next;

            temp = ((struct int_doubly_list*)node_i)->value;
            ((struct int_doubly_list*)node_i)->value = ((struct int_doubly_list*)node_j)->value;
            ((struct int_doubly_list*)node_j)->value = temp;
        }
    }
}

void insert_after(struct doubly_linked_list** pointer, struct doubly_linked_list* target, struct doubly_linked_list* new_node) {
    if (!target || !new_node || !*pointer)
        return;

    struct doubly_linked_list* current_pointer = *pointer;

    while (current_pointer) {
        if (current_pointer == target) {
            new_node->next = current_pointer->next;
            new_node->prev = current_pointer;

            if (current_pointer->next)
            {
                current_pointer->next->prev = new_node;
            }

            current_pointer->next = new_node;

            (*pointer)->count++;
            return;
        }

        current_pointer = current_pointer->next;
    }

    printf("Target node not found!!\n");
}

void insert_before(struct doubly_linked_list** pointer, struct doubly_linked_list* target, struct doubly_linked_list* new_node) {
    if (!target || !new_node || !*pointer)
        return;

    struct doubly_linked_list* current_pointer = *pointer;


    while (current_pointer) {
        if (current_pointer == target) {
            new_node->prev = current_pointer->prev;
            new_node->next = current_pointer;

            if (current_pointer->prev)
            {
                current_pointer->prev->next = new_node;
            }

            current_pointer->prev = new_node;

            if (*pointer == current_pointer)
            {
                *pointer = new_node;
            }

            int count = length(current_pointer);
            
            if (new_node->prev == NULL)
            {
                *pointer = new_node;
                (*pointer)->count = count;
                
            }
            (*pointer)->count++;

            return;
        }

        current_pointer = current_pointer->next;
    }

    printf("Target node not found!!\n");
}

void print_value(struct doubly_linked_list** pointer) {
    struct doubly_linked_list* current_pointer = *pointer;
    while (current_pointer) {
        printf("Value: %d\n", ((struct int_doubly_list*)current_pointer)->value);
        current_pointer = current_pointer->next;
    }
}

int main() {
    struct doubly_linked_list* test_list = NULL;
    printf("Initial list\n");
    printf("Length : %d\n", length(test_list));
    printf("------------------------------\n");

    struct int_doubly_list item0;
    item0.value = 0;
    struct int_doubly_list item1;
    item1.value = 1;
    struct int_doubly_list item2;
    item2.value = 2;
    struct int_doubly_list item3;
    item3.value = 3;
    struct int_doubly_list item4;
    item4.value = 4;
    struct int_doubly_list item5;
    item5.value = 5;
    struct int_doubly_list item6;
    item6.value = 6;
    struct int_doubly_list item7;
    item7.value = 7;



    printf("--------APPEND--------\n");

    printf("Try to add item0\n");
    append(&test_list,get_list(item0));
    printf("Length : %d\n",length(test_list));
    printf("------------------------------\n");
    printf("Try to add item1\n");
    append(&test_list,get_list(item1));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");
    printf("Try to add item2\n");
    append(&test_list,get_list(item2));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");
    printf("Try to add item3\n");
    append(&test_list,get_list(item3));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");
    printf("Try to add item4\n");
    append(&test_list,get_list(item4));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");
    printf("Try to add item5\n");
    append(&test_list,get_list(item5));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");


    printf("---------REMOVE---------\n");
    printf("Try to remove item5\n");
    remove_item(&test_list,get_list(item5));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");


    printf("-------INSERT_AFTER--------\n");
    printf("insert_after\n");
    insert_after(&test_list, get_list(item0), get_list(item6));
    print_value(&test_list);
    printf("Length : %d\n", length(test_list));


    printf("-------INSERT_BEFORE-------\n");
    printf("insert_before\n");
    insert_before(&test_list, get_list(item0), get_list(item7));
    print_value(&test_list);
    printf("Length : %d\n", length(test_list));

    printf("---------SHUFFLE----------\n");

    printf("Shuffling the list\n"); 
    shuffle_list(&test_list);
    print_value(&test_list);
    printf("Length : %d\n", length(test_list));
    
    printf("------------------------------\n");

    return 0;
}