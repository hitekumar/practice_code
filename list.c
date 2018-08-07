#include <stdio.h>
#include <stdlib.h>

struct my_list
{
    int data;
    struct my_list *next;
};

void populate_list(void **head, int count)
{
    struct my_list *my_head = (struct my_list *) *head;
    struct my_list *tmp, *last;
    int i;
    my_head = malloc(sizeof(struct my_list));
    my_head->data = 0;
    my_head->next = NULL;
    last = my_head;
    for (i =1; i < count; i++)
    {
        tmp =  malloc(sizeof(struct my_list));
        tmp->data = i;
        tmp->next = NULL;
        last->next = tmp;
        last = last->next;

        printf("%s -- data = %d\n", __func__, last->data);
    }
    printf("%p %p %p\n", (void *)my_head, (void *)&my_head, (void *)*head);
 
}

void print_list(void ** head)
{
    struct my_list * my_head = (struct my_list*) *head;
    struct my_list *tmp = my_head;

    while (tmp != NULL)
    {
        printf("data = %d\n", tmp->data);
        tmp = tmp->next;
    }
}

int main()
{
    struct my_list *list_head=NULL;
    printf("add ress of list head %p\n", &list_head);
    populate_list((void **)&list_head, 10);
    print_list((void **)&list_head);
}
