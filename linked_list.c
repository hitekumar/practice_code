#include <stdio.h>
#include <stdlib.h>
struct list
{
    int data;
    struct list* next;
};

static int add_node(struct list **head, struct list *new_node)
{
    struct list *end = *head;
    if (*head == NULL)
        *head = new_node;
    else
    {
        while (end->next != NULL)
        {
            end = end->next;
        }
        end->next = new_node;
    }
    return 0;
}

static void delete_node(struct list **head, int i)
{
    struct list *cur = *head;
    struct list *prev = cur;
    // Head is the node to delete
    if ((cur != NULL) && (cur->data == i))
    {
       *head = cur->next; 
       free(cur);
       return;
    }
    while ((cur != NULL) && (cur->data != i))
    {
        prev = cur;
        cur = cur->next;
    }
    if (cur == NULL)
        return;
    prev->next = cur->next;
    free(cur);
    return;
}

static void reverse_recursive(struct list **head, struct list* prev, struct list *cur)
{
    if (cur)
    {
        reverse_recursive(head, cur, cur->next);
        cur->next = prev;
    }
    else
    {
        *head = prev;
    }

}

static void reverse(struct list **head)
{
    struct list *p, *c, *n;
    if ((*head)->next == NULL)
    {   
        return;
    }
    p=NULL;
    c=*head;

    while(c!=NULL)
    {
        n = c->next;
        c->next = p;
        p = c;
        c = n;
    }
    *head = p;
}

static void print_list(struct list **head)
{
    struct list * tmp = *head;
    while (tmp)
    {
        printf("%d->", tmp->data);
        tmp = tmp->next;
    }
    printf("\\0\n");

}

struct list * get_node(int i)
{
    struct list *tmp = malloc(sizeof(struct list));
    tmp->data = i;
    tmp->next = NULL;
    return tmp;
}

int main()
{
    struct list *head = NULL;
    int i;
    for (i = 0; i < 10; i++)
    {
        add_node(&head, get_node(i));
        print_list(&head);
    }
    delete_node(&head, 4);
    print_list(&head);
    delete_node(&head, 6);
    print_list(&head);
    delete_node(&head, 11);
    print_list(&head);
    delete_node(&head, 0);
    print_list(&head);

    reverse(&head);
    print_list(&head);
    reverse_recursive(&head, NULL, head );
    print_list(&head);

}
