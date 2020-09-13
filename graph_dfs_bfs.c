#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct vertex {
    char name;
    int visited;
    struct list_node *head;
} vertex_t;

typedef struct list_node {
    vertex_t *v;
    struct list_node * next;
} list_node_t;

//----------------------Queue operations
#define QUEUE_SIZE  32

typedef struct queue {
    int front;
    int rear;
    vertex_t * arr[QUEUE_SIZE];
} queue_t;

vertex_t * peek(queue_t *q) {
    return q->arr[q->front];
}

bool is_empty(queue_t *q) {
    if (q->front == q->rear) {
	    return 1;
    }
    return 0;
}

bool is_full(queue_t * q) {
    if ((q->rear +1 >= QUEUE_SIZE) && (q->front == 0)) {
    	return 1;
    }

    if (q->rear + 1 == q->front) {
    	return 1;
    }

    return 0;
}

void enqueue(queue_t *q, vertex_t *element) {
//    printf("Enqueue %c \n", element->name);
    if (!is_full(q)) {
    	q->arr[q->rear] = element;
	    q->rear++;
    	if(q->rear >= QUEUE_SIZE) {
	        q->rear = 0;
	    }
    }
    else {
    	printf("Queue is full\n");
    }
}

vertex_t* dequeue(queue_t *q) {
    vertex_t * element = NULL;
    if (!is_empty(q)) {
    	element = q->arr[q->front];
	    q->front++;
    	if (q->front >= QUEUE_SIZE) {
	        q->front = 0;
    	}
    }
    else {
	    printf("Queue is empty\n");
    }
//    printf("Dequeue %c \n", element->name);
    return element;
}

//---------------------Graph operations------------

// Allocate new vertex
vertex_t *get_new_vertex(char name) {
    vertex_t * v;
    v = malloc(sizeof(vertex_t));
    v->name = name;
    v->visited = 0;
    v->head = NULL;

    return v;
}

// Connect a vertex A to B by adding a list node
void connect_vertex(vertex_t *a, vertex_t * b) {
    list_node_t *tmp;
    list_node_t * l_node = malloc(sizeof(list_node_t));
    l_node->v = b;
    l_node->next = NULL;
    tmp = a->head;
    // Add it in a's adjuncy list
    if (tmp == NULL) {
        a->head = l_node;
    }
    else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = l_node;
   }
   return;    
}

void graph_bfs(vertex_t ** G, int size) {
    vertex_t * vertex;
    list_node_t *list;
    vertex = G[0];
    int i;
    queue_t *q = malloc(sizeof(queue_t));
 
    // Mark all vertex unvisited
    for (i = 0; i < size;i++) {
        G[i]->visited = 0;
    }

   
    if (q==NULL) {
	printf("No mem\n");
	    return ;
    }

    q->front = 0;
    q->rear = 0;

    enqueue(q, G[0]);
    while (!is_empty(q)) {
        vertex = dequeue(q);
        if (vertex->visited) {
            //printf("%c is already visited\n", vertex->name);
            continue;
        }
        printf("%c->", vertex->name);
        vertex->visited = 1;
        list = vertex->head;
        while (list != NULL) {
            if (!list->v->visited) {
                enqueue(q,list->v);
            }
            list = list->next;
        }
        
    }
    printf("null\n");
}


void dfs(vertex_t * v) {
    list_node_t * tmp = v->head;
    // Visit vertex
    printf("%c->", v->name);
    v->visited = 1;
    while (tmp != NULL) {
        if (!tmp->v->visited) {
            dfs(tmp->v);
        }
        tmp = tmp->next;
    }
    printf("null\n");
}

void graph_dfs(vertex_t **G, int size) {
    int i;
    // Mark all vertex unvisited
    for (i = 0; i < size;i++) {
        G[i]->visited = 0;
    }

    // traverse each vertex list
    for (i = 0; i < size;i++) {
        if (G[i]->visited == 0) {
            dfs(G[i]);
        }
    }

}

/*
 *     A---B
 *     |  / \
 *     | /   E
 *     |/   /
 *     C---D
 *
 */

int main(int argc, char** argv) {
    vertex_t *graph[5];
    // Add vertices to graph
    graph[0] = get_new_vertex('A');
    graph[1] = get_new_vertex('B');
    graph[2] = get_new_vertex('C');
    graph[3] = get_new_vertex('D');
    graph[4] = get_new_vertex('E');

    // Add edges, for undirected graphs add both ways
    // A---B
    connect_vertex(graph[0],graph[1]);
    connect_vertex(graph[1],graph[0]);

    // A--C
    connect_vertex(graph[0],graph[2]);
    connect_vertex(graph[2],graph[0]);

    // C--D
    connect_vertex(graph[2],graph[3]);
    connect_vertex(graph[3],graph[2]);

    // B--C, B--D, B--E
    connect_vertex(graph[1],graph[2]);
    connect_vertex(graph[2],graph[1]);

    connect_vertex(graph[1],graph[4]);
    connect_vertex(graph[4],graph[1]);

    // D--E
    connect_vertex(graph[3],graph[4]);
    connect_vertex(graph[4],graph[3]);
    
    printf("DFS\n");
    graph_dfs(graph,5);
    printf("BFS\n");
    graph_bfs(graph,5);
    return 0;

}




