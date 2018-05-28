/*
 * This file contains the function to see if there exists a
 * path in the given graph whose total weight is greater than
 * or equal to the given weight.
 *
 * We are using backtracking here. What backtracking essentially does is,
 * It does a depth first search. For each neighbor node, it goes to its
 * neighbor and then to its neighbor till it reaches the depth. If it finds
 * the weight of this path greater than given value, then it returns true.
 *
 * Another way to do is Breadth First search. Here, we first check all our
 * neighbors and only then go to next level where we check all of their
 * neighbors and so on.
 *
 * In this case, doing Depth First search is better because we need to find
 * the particular path whose depth is greater than given value. So, if say we
 * have 10 neighbors and the path going through 4th neighbor has this depth,
 * then using DFS, we would have to traverse all neighbors of our first 4
 * neighbors only. But in the case of BFS, we will traverse all 10 neighbors
 * then all neighbors of these 10 neighbors and so on, till we go to the
 * level whose depth is equal to given depth. So more computations are
 * required.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Define size of graph */
#define SIZE 9

int path_index = 0;

/*
 * Visited array to maintain a list of already
 * visited vertexes.
 */
bool visited[SIZE] = {false};

/* Array to have the path. */
int path[SIZE] = {0};

/* Recursive function which uses backtracking algorithm
 * to find the path with given weight.
 */
bool isPath(int graph[SIZE][SIZE], int x, int weight) {
    
    /* Base cases */
    /* If weight is less than 0 that means
     * we have found the path. return true.
     */
    if(weight <= 0) {
        path[path_index] = x;
        path_index++;
        return true;
    }

    /*
     * If weight is not less than zero but current
     * vertex is already visited, then return false
     * to avoid cycles.
     */
    if(visited[x]) {
        return false;
    }

    visited[x] = true;
    path[path_index] = x;
    path_index++;

    /* The idea is to check all the neighboring nodes of
     * given source node one by one for the path
     */
    for(int i=0; i<SIZE; i++) {
        /* Check if edge exists */
        if(graph[x][i] != 0) {
            /* Take this neighbor into consideration
             * for probable solution and recurse for
             * its neighbors.
             */
            weight = weight - graph[x][i];
            if(!isPath(graph, i, weight)) {
                /* If no solution, backtrack */
                weight = weight + graph[x][i];
            } else {
                return true;
            }
        }
    }
    /* If we come here, that means no neighbors satisfy
     * the condition. So return false.
     */
    visited[x] = false;
    path_index--;
    return false;
}

int main(void) {
    int graph[SIZE][SIZE] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                             {4, 0, 8, 0, 0, 0, 0, 11, 0},
                             {0, 8, 0, 7, 0, 4, 0, 0, 2},
                             {0, 0, 7, 0, 9, 14, 0, 0, 0},
                             {0, 0, 0, 9, 0, 10, 0, 0, 0},
                             {0, 0, 4, 14, 10, 0, 2, 0, 0},
                             {0, 0, 0, 0, 0, 2, 0, 1, 6},
                             {8, 11, 0, 0, 0, 0, 1, 0, 7},
                             {0, 0, 2, 0, 0, 0, 6, 7, 0}};
    int weight = 65;
    if(isPath(graph, 0, weight)) {
        printf("Path with weight %d exists.\n", weight);
        for(int i=0; i<path_index; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        printf("Path with weight %d does not exist\n", weight);
    }
    return 0;
}

