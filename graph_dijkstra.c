
#include <stdio.h>

#define V   9
#define INT_MAX     10000

int get_vertex_with_minimum_distance(int dist[], int visited[])
{
    // Initialize min value
    int min = INT_MAX;
    int min_idx, i;
    for (i = 0; i < V; i++)
    {
        if (visited[i] == 0 && dist[i] <= min)
        {
            min = dist[i];
            min_idx = i;
        }
    }
    printf("Returning min_idx = %d\n", min_idx);
    return min_idx;
}

void print_distance(int dist[], int src)
{
    int i;
    for (i = 0; i < V; i++)
    {
        printf("Distance from %c to %c is %d\n", 97+src, 97+i, dist[i]);
    }

}

// Function to find shortest path from single source
void dijkstra(int graph[V][V], int src)
{
    int dist[V];    // Distance of each vertex from given source
    int visited[V]; // Mark if given vertex is visited
    int min,i,j;

    // Initialize all distance with Infinite
    for (i = 0; i < V; i++)
    {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    
    // Distance of source to source is 0
    dist[src] = 0;

    // find shortest path to all vertices
    for (i = 0; i < V-1; i++)
    {
        min = get_vertex_with_minimum_distance(dist, visited);
        visited[min] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (j = 0; j < V; j++)
        {
            // If the given vertex in not visited 
            // There is a path exist from source(min) to j
            // Distance from source(min) is not infinite
            // Distance from source(min) + distance to J is less than earlier distance from source to j
            if (!visited[j] && graph[min][j] && dist[min] != INT_MAX && dist[min] + graph[min][j] < dist[j])
            {
                // Update distance of j from source
                dist[j] = dist[min] + graph[min][j];
            }
        }
        
    }
    print_distance(dist, src);
}

int main()
{
//   a, b, c, d, e, f, g, h, i
    int graph[V][V] = {
    {0, 4, 8, 0, 0, 0, 0, 0, 0 },
    {4, 0,11, 8, 0, 0, 0, 0, 0 },
    {8,11, 0, 0, 7, 1, 0, 0, 0 },
    {0, 8, 8, 0, 2, 0, 7, 4, 0 },
    {0, 0, 7, 2, 0, 6, 0, 0, 0 },
    {0, 0, 1, 0, 6, 0, 0, 2, 9 },
    {0, 0, 0, 7, 0, 0, 0, 14, 9},
    {0, 0, 0, 4, 0, 2,14, 10,10},
    {0, 0, 0, 0, 0, 0, 9, 10,0 },
};

    dijkstra(graph, 0);

    
}


