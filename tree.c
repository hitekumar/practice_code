#include <stdio.h>
#include <stdlib.h>

#define MAX_Q_SIZE  100

struct node 
{
    int data;
    struct node *left;
    struct node *right;
};

// Helper queue function used in bft
struct node ** create_queue(int *front, int *rear)
{
    struct node ** queue = (struct node **) malloc (sizeof (struct node*) * MAX_Q_SIZE);
    *front = *rear = 0;
    return queue; 
}

void enqueue(struct node ** queue, int *rear, struct node * n_ptr)
{
    queue[*rear] = n_ptr;
    (*rear)++;
    if (*rear >= MAX_Q_SIZE)
    {
        *rear = 0;
    }
}

struct node * dequeue(struct node ** queue, int * front)
{
    struct node * n_ptr =  queue[*front];
    queue[*front] = NULL;
    (*front)++;
    if (*front >= MAX_Q_SIZE)
    {
        *front = 0;
    }
    return n_ptr;
}

// retuen 1 if empty
int is_queue_empty(int *front, int *rear)
{
    if (*front == *rear)
        return 1;
    return 0;
}

// retruns 1 if full
int is_queue_full(int * front, int *rear)
{
    if ((*rear) + 1 == *front)
    {
        return 1;
    }
    if (((*rear) + 1 >= MAX_Q_SIZE) && (*front == 0))
    {
        return 1;
    }
    return 0;    
}
// End helper function

struct node * get_new_node(int data)
{
    struct node * ptr = malloc(sizeof(struct node));
    if (ptr != NULL)
    {
        ptr->data = data;
        ptr->left = NULL;
        ptr->right = NULL;
    }
    return ptr;
}

void add_node(struct node * root, struct node * n_ptr)
{
    if (root->left == NULL)
    {
        root->left = n_ptr;
    }
    else if (root->right == NULL)
    {
        root->right = n_ptr;
    }
    else if (root->left->right == NULL)
    {
        add_node(root->left, n_ptr);
    }
    else
    {
        add_node(root->right, n_ptr);
    }
    return;
}


// Bredth first traverse, using queue algo
void print_tree_bft(struct node * root)
{
    int front, rear;
    struct node * tmp;
    struct node ** queue = create_queue(&front, &rear);
    if (root == NULL)
    {
        return;
    }
    tmp = root;

    while(tmp != NULL)
    {
        printf("%d ", tmp->data);
        if (tmp->left != NULL)
        {
            enqueue(queue,&rear, tmp->left);
        }
        if (tmp->right != NULL)
        {
            enqueue(queue,&rear, tmp->right);
        }
        tmp = dequeue(queue, &front);
    }
}


// Depth first traverse
void print_tree_dft(struct node * root)
{
    if (root == NULL)
    {
        return;
    }
    
    printf("%d ", root->data);
    print_tree_dft(root->left);
    print_tree_dft(root->right);
}

struct node * create_tree(void)
{
    struct node *root = get_new_node(1);
    add_node(root, get_new_node(2));
    add_node(root, get_new_node(3));
    add_node(root, get_new_node(4));
    add_node(root, get_new_node(5));
    add_node(root, get_new_node(6));
    add_node(root, get_new_node(7));
    add_node(root, get_new_node(8));
    add_node(root, get_new_node(9));
    add_node(root, get_new_node(10));
    add_node(root, get_new_node(11));
    
    return root;
}

int main()
{
    struct node * tree = create_tree();
    printf("DFT ");
    print_tree_dft(tree);
    printf("\n");

    
    printf("BFT ");
    print_tree_bft(tree);
    printf("\n");
}
