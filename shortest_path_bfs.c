#include <stdio.h>
#include <stdlib.h>

// Queue operations

#define MAX_Q_SIZE  100
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

////////////////////////Graph///////////////////////////

struct graph {
    int vertex_count;
    struct adj_list *arr;
};

struct adj_list {
    struct adj_list_node *head;
};

struct adj_list_node {
    int v;
    struct adj_list_node* next;
};

struct graph* create_graph(int v_count) {
    int i;

    struct graph *g = (struct graph *) malloc(sizeof (struct graph));

    g->arr = (struct adj_list *) malloc(v_count * sizeof (struct adj_list));
    
    // Initialize each adjacency list as empty by making head as NULL
    for(i = 0; i< v_count;i++) {
	    g->arr[i].head = NULL;
    }
    return g;
}

struct adj_list_node* get_new_list_node(int v) {
    struct adj_list_node* n = malloc(sizeof(struct adj_list_node));
    n->v = v;
    n->next = NULL;
    return n;
}


void add_edge(struct graph *g, int src, int dst) {
    // Add and edge from src to dst.
    // The node is added at the begining of the list.
    struct adj_list_node *n = get_new_list_node(dst);
    n->next = g->arr[src].head;
    g->arr[src].head = n;

    // Since the graph is undirected, 
    // add an edge from dst to src as well
    n = get_new_list_node(src);
    n->next = g->arr[dst].head;
    g->arr[dst].head = n;
}

int main(int argc, char **argv) {
    struct graph *G  = create_graph(5);
    add_edge(G,0,1);
    add_edge(G,0,4);
    add_edge(G,1,2);
    add_edge(G,1,3);
    add_edge(G,1,4);
    add_edge(G,2,3);
    add_edge(G,3,4);
}
