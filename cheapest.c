#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include "coordReader.c"

#define INF 999999

// Define a structure to represent a vertex
typedef struct {
    double x, y;  // Coordinates of the vertex
} Vertex;

// Function to calculate the Euclidean distance between two vertices
double distance(Vertex v1, Vertex v2) {
    return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

// Function to find the vertex with the minimal distance from the current vertex
int findMinDistanceVertex(int current, int n, int *visited, Vertex *vertices) {
    int minIndex = -1;
    double minDistance = INF;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && i != current) {
            double dist = distance(vertices[current], vertices[i]);
            if (dist < minDistance) {
                minDistance = dist;
                minIndex = i;
            }
        }
    }

    return minIndex;
}

int *findVk(int current, int n, int *visited, Vertex *vertices, int nex, int *tour) {
    int Vk = -1;
    double minDistance = INF;

    for (int i = 0; i < n; i++) {
        if (visited[i]) {
            for (int j = 1; j < n; j++) {
                if (visited[j]) {
                    double dist1 = distance(vertices[tour[i]], vertices[current]);
                    double dist2 = distance(vertices[current], vertices[next]);
                    double dist3 = distance(vertices[next], vertices[tour[j]]);
                    double increase = dist1 + dist2 + dist3 - distance(vertices[tour[i]], vertices[tour[j]]);

                    if (increase < minDistance) {
                        minIncrease = increase;
                        Vk = i;
                    }
                }
            }
        }
    }

    static int arr[2];
    arr[0] = tour[Vk];
    arr[1] = next;
    return arr;
}

// Function to perform the Cheapest Insertion Algorithm
void cheapestInsertion(int n, Vertex *vertices) {
    int *visited = (int *)malloc(n * sizeof(int));
    int *tour = (int *)malloc((n + 1) * sizeof(int)); // +1 for returning to the starting point
    int current = 0;                                   // Start with the first vertex
    int next;

    for (int i = 0; i < n; ++i) {
        visited[i] = 0;
    }

    visited[current] = 1; // updating that vertex has been visited
    tour[0] = current;

    // STEP #2
    next = findMinDistanceVertex(current, n, visited, vertices);
    visited[next] = 1; // updating that vertex has been visited

    tour[1] = next;

    // STEP #3
    for (int i = 2; i < n; ++i) {
        int *newVerts = findVk(current, n, visited, vertices, next, tour);
        tour[i] = newVerts[1];
        // insert the new vertex
        current = newVerts[0];
        next = newVerts[1];
        visited[next] = 1;
    }

    // Complete the tour by returning to the starting point
    tour[n] = tour[0];

    // Print the tour
    printf("Tour: ");
    for (int i = 0; i <= n; ++i) {
        printf("%d ", tour[i]);
    }
    printf("\n");

    free(visited);
    free(tour); 
}

int main() {
    int n = readNumOfCoords("9_coords.coord"); // Number of vertices
    Vertex vertices[n];
    double **coordinates = readCoords("9_coords.coord", n);

    for (int i = 0; i < n; i++) {
        vertices[i].x = coordinates[i][0];
        vertices[i].y = coordinates[i][1];
    }

    cheapestInsertion(n, vertices);

    return 0;
}
