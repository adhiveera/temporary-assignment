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

// Function to find the vertex with the maximal distance from the current vertex
int findMaxDistanceVertex(int current, int n, int *visited, Vertex *vertices) {
    int maxIndex = -1;
    double maxDistance = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            double dist = distance(vertices[current], vertices[i]);
            if (dist > maxDistance) {
                maxDistance = dist;
                maxIndex = i;
            }
        }
    }

    return maxIndex;
}

// Function to find the vertex vk for Furthest Insertion
int findFurthestVertex(int n, int *tour, Vertex *vertices) {
    int furthestVertex = -1;
    double minIncrease = INF;

    for (int vk = 0; vk < n; vk++) {
        if (tour[vk] == -1) {
            for (int i = 0; i < n; i++) {
                if (tour[i] != -1) {
                    int vn = tour[i];
                    int vn1 = tour[(i + 1) % n];

                    double increase = distance(vertices[vn], vertices[vk]) + distance(vertices[vn1], vertices[vk]) -
                                      distance(vertices[vn], vertices[vn1]);

                    if (increase < minIncrease) {
                        minIncrease = increase;
                        furthestVertex = vk;
                    }
                }
            }
        }
    }

    return furthestVertex;
}

// Function to perform the Furthest Insertion Algorithm
void furthestInsertion(int n, Vertex *vertices) {
    int *tour = (int *)malloc(n * sizeof(int));
    int current = 0;

    for (int i = 0; i < n; i++) {
        tour[i] = -1;
    }

    tour[0] = current;

    // STEP #2
    int next = findMaxDistanceVertex(current, n, tour, vertices);
    tour[1] = next;
    tour[n - 1] = 0; // Complete the tour by returning to the starting point

    // STEP #3 and #4
    for (int i = 2; i < n - 1; i++) {
        int vk = findFurthestVertex(n, tour, vertices);
        int position = 0;
        double minIncrease = INF;

        for (int j = 0; j < n; j++) {
            if (tour[j] != -1) {
                int vn = tour[j];
                int vn1 = tour[(j + 1) % n];

                double increase = distance(vertices[vn], vertices[vk]) + distance(vertices[vn1], vertices[vk]) -
                                  distance(vertices[vn], vertices[vn1]);

                if (increase < minIncrease) {
                    minIncrease = increase;
                    position = j;
                }
            }
        }

        // Insert vk between two connected vertices in the partial tour
        for (int j = n - 1; j > position; j--) {
            tour[j] = tour[j - 1];
        }
        tour[position + 1] = vk;
    }

    // Print the tour
    printf("Tour: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", tour[i]);
    }
    printf("\n");

    free(tour);
}

int main() {
    int n = readNumOfCoords("9_coords.coord"); // Number of vertices
    Vertex vertices[n];
    double **coordinates = readCoords("9_coords.coord", 9);

    for (int i = 0; i < n; i++) {
        vertices[i].x = coordinates[i][0];
        vertices[i].y = coordinates[i][1];
    }

    furthestInsertion(n, vertices);

    return 0;
}