#include <stddef.h>
#include <stdio.h>

#define get_list(x) &(x.self)

struct linked_list{

    struct linked_list* next;
    unsigned int count;
};

int length(struct linked_list* pointer){
    return pointer ? pointer->count : 0;
}

struct linked_list* get_tail(struct linked_list** pointer){
    
    struct linked_list* current_pointer = *pointer;
    struct linked_list* last_pointer = NULL;

    while(current_pointer){
        last_pointer = current_pointer;
        current_pointer = current_pointer->next;
    }

    return last_pointer;
}

int append(struct linked_list** pointer,struct linked_list* item){
    
    struct linked_list* tail = get_tail(pointer);

    if (!tail)
    {
        *pointer = item;
        item->next = NULL;
        (*pointer)->count = 1;
        printf("List was empty\n");
        return 0;
    }
   
    printf("Successfully item added\n");
    tail->next = item;
    item->next = NULL;
    
    (*pointer)->count++;
    return 0;
}

int remove_item(struct linked_list** pointer, struct linked_list* item){
    
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
            else{
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

void reverse_list(struct linked_list** pointer) {
   struct linked_list* current = *pointer;
   struct linked_list* prev = NULL;
   struct linked_list* next = NULL;

  int count = length(*pointer);
   while (current != NULL)
   {
        next = current->next; 
        current->next = prev;
        prev = current;
        current = next;
   }
     (*pointer) = prev;
     (*pointer)->count = count;
}


int remove_at_index(struct linked_list** pointer, const int index){
    
    int pointer_length = length(*pointer);

    if (pointer_length == 0 || index > pointer_length - 1)
    {
        printf("Cannot remove cause list is empty or index greater than length\n");
        return -1;
    }

    struct linked_list* current_pointer = *pointer;
    struct linked_list* prev_pointer = current_pointer;
    
    for (int i = 0; i < pointer_length; i++)
    {
        if (i == index)
        {
            if (i== 0)
            {
                *pointer = current_pointer->next;
            }
            else{
                prev_pointer->next = current_pointer->next;
            }
            current_pointer = NULL;
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

struct int_list{
    struct linked_list self;
    int value;
};

void print_value(struct linked_list** pointer){
    struct linked_list* current_pointer = *pointer;
    while (current_pointer)
    {
        printf("Value: %d\n",((struct int_list*)current_pointer)->value);
       current_pointer = current_pointer->next;
    }
}

int main()
{ 
    struct linked_list* test_list = NULL;
    printf("Initial list\n");
    printf("Length : %d\n",length(test_list));
    struct int_list item0;
    item0.value = 10;
    struct int_list item1;
    item1.value = 2;
     struct int_list item2;
    item2.value = 5;
    struct int_list item3;
    item3.value = 7;

  
    printf("--------APPEND--------\n");
    printf("Try to add item0\n");
    append(&test_list,get_list(item0));
    printf("Length : %d\n",length(test_list));
    printf("Try to add item1\n");
    append(&test_list,get_list(item1));
    printf("Length : %d\n",length(test_list));
    printf("Try to add item2\n");
    append(&test_list,get_list(item2));
    printf("Length : %d\n",length(test_list));
    printf("Try to add item3\n");
    append(&test_list,get_list(item3));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);

    printf("--------REVERSING---------\n");
    printf("Try to reversing the list\n");
    reverse_list(&test_list);
    print_value(&test_list);
    printf("Length : %d\n",length(test_list));


    printf("---------REMOVE---------\n");
    printf("Try to remove item0\n");
    remove_item(&test_list,get_list(item0));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");

    printf("Try to remove item3\n");
    remove_item(&test_list,get_list(item3));
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);

    printf("------REMOVE AT INDEX------\n");
    printf("Try to remove at index 0\n");
    remove_at_index(&test_list,0);
    printf("Length : %d\n",length(test_list));
    print_value(&test_list);
    printf("------------------------------\n");
    
   


    return 0;
}