#include <stdio.h>
#include <limits.h>

#define V 8 // Number of vertices

// Function to find the vertex with minimum distance value, from
// the set of vertices not yet included in the shortest path tree
int minDistance(int dist[], int sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Function that implements Dijkstra's single source shortest path algorithm
// for a graph represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src) {
    int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i
    int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest path tree or shortest distance from src to i is finalized

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = 0;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        // u is always equal to src in the first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++)
            // Update dist[v] only if is not in sptSet, there is an edge from
            // u to v, and total weight of path from src to v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // print the constructed distance array
    printSolution(dist);
}

int main() {
    /* Let us create the example graph discussed above */
    int graph[V][V] = {{0, 0, 0, 0, 0, 0, 0, 0},
                       {300, 0, 0, 0, 0, 0, 0, 0},
                       {1000, 800, 0, 0, 0, 0, 0, 0},
                       {0, 0, 1200, 0, 0, 0, 0, 0},
                       {0, 0, 0, 1500, 0, 250, 0, 0},
                       {0, 0, 0, 1000, 0, 0, 900, 1400},
                       {0, 0, 0, 0, 0, 0, 0, 1000},
                       {1700, 0, 0, 0, 0, 0, 0, 0}};
                       
    dijkstra(graph, 4); // 4 is Boston, the source vertex in this example
    return 0;
}
