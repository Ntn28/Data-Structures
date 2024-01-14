#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define get_list(x) &(x.self)

struct linked_list
{
    struct linked_list* next;
    unsigned int count;
};

int length(struct linked_list* pointer)
{
    return pointer ? pointer->count : 0;
}

struct linked_list* get_tail(struct linked_list** pointer)
{
    
    struct linked_list* current_pointer = *pointer;
    struct linked_list* last_pointer = NULL;

    while(current_pointer)
    {
        last_pointer = current_pointer;
        current_pointer = current_pointer->next;
    }

    return last_pointer;
}

int append(struct linked_list** pointer,struct linked_list* item)
{
    
    struct linked_list* tail = get_tail(pointer);

    if (!tail)
    {
        *pointer = item;
        item->next = NULL;
        (*pointer)->count = 1;
        return 0;
    }
   
    printf("Successfully item added\n");
    tail->next = item;
    item->next = NULL;
    
    (*pointer)->count++;
    return 0;
}

int remove_item(struct linked_list** pointer, struct linked_list* item)
{
    
    int pointer_length = length(*pointer);

    if (pointer_length == 0)
    {
        printf("Cannot remove cause list is empty\n");
        return -1;
    }

    struct linked_list* current_pointer = *pointer;
    struct linked_list* prev_pointer = current_pointer;
    
    for (int i = 0; i < pointer_length; i++)
    {
        if (current_pointer == item)
        {
            if (i== 0)
            {
                *pointer = current_pointer->next;
            }
            else
            {
                prev_pointer->next = current_pointer->next;
            }
            item = NULL;
            printf("Successfullyu removed!!\n");
            (*pointer)->count = pointer_length - 1;
            return 0;
        }
        prev_pointer = current_pointer;
        current_pointer = current_pointer->next;
    }

    printf("Item not found!!\n");
    return -1;
};