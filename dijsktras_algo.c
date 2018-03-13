/*
 * This file contains the explanation and implementation
 * of Dijsktra's algorithm.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define INFINITE 2222
/*
 * Datastructures used:
 * We have a graph represented by a 2d array. The graph has V vertices and E edges
 * between them and each edge has some weight. The value at graph[i][j] represents
 * the weight of edge between i and j vertex. If its 0 then it means there is no
 * edge between i and j vertices. We are given a source vertice and we
 * are supposed to find minimum weight from this source to all the rest vertices.
 *
 * We maintain a binary array of length V to keep track of if the particular vertex
 * is visited or not.
 *
 * We maintain a integer array of length V to keep track of distances from source
 * vertex to all other vertices. In this array, the distance of source vertex is 0.
 * The other values are initialized to infinity at the start and then we keep on
 * updating it later.
 *
 * Algorithm working:
 * Inside the loop that runs for the number of vertices, we get the vertex with
 * minimum distance from the distance array. For the first iteration, this vertex
 * will be the source vertex as we initialized distance array for this vertex as 0
 * and infinity for rest all the vertices.
 * Once we get the minimum distance vertex, we then mark this vertex as visited in
 * the binary array and from the graph array, we get all the adjascent vertices of
 * this vertex. For each of these adjascent vertices, we update their weights in the
 * distance array such that their updated weight = weight of present vertex + weight
 * of the edge from the edge array. We update these weights only if this particular
 * vertex is not visited earlier and its current weight in weight array is greater
 * than the new calculated weight.
 * We continue doing this for all the vertices till our loop ends.
 * In the end, we have our distance array with minimum distance to each vertex from
 * the source vertex.
 */

int get_minimum(int *distance, int no_of_vertices, bool *visited_vertices) {
    int min_index, min_val=INFINITE;
    for(int i=0;i<no_of_vertices;i++) {
        if(!(visited_vertices[i]) && distance[i] <= min_val) {
            min_val = distance[i];
            min_index = i;
        }
    }
    return min_index;
}

int* dijsktras(int** graph, int source, int no_of_vertices) {
    bool visited_vertices[no_of_vertices]; /*to maintain visited database*/
    int *distance;                         /*to maintain distances from src vertex*/
    distance = (int *)malloc(sizeof(int)*no_of_vertices);

    /* Initialize visited_vertices and distance arrays */
    for(int i=0;i<no_of_vertices;i++) {
        visited_vertices[i] = false;
        distance[i] = INFINITE;
    }

   /* Mark the distance of source vertex as 0 */
   distance[source] = 0;

  /* Start the loop to calculate and update the min distances */
  for(int i=0;i<no_of_vertices-1;i++) {
      int min_val;
      
      /* Get the min val vertex from distance array */
      int min_vertex = get_minimum(distance, no_of_vertices, visited_vertices);

      /* Mark the vertex as visited */
      visited_vertices[min_vertex] = true;

      /* Update the distance array with distances to all the adjascent
       * vertices of min_vertex
       */
      for(int j=0;j<no_of_vertices;j++) {
          if((graph[min_vertex][j]) && (!visited_vertices[j])) {
              int new_distance = distance[min_vertex] + graph[min_vertex][j];
              if(distance[j] > new_distance) {
                  distance[j] = new_distance;
              }
          }
      }
  }
  return distance;
}

int main(void) {
    int **graph;
    graph = (int **)malloc(sizeof(int*)*9);
    for(int i=0;i<9;i++) {
        graph[i] = (int*)malloc(sizeof(int)*9);
    }

    printf("Enter the values of edges for graph.\n");
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    int *distance = (int *)malloc(sizeof(int)*9);

    distance = dijsktras(graph, 0, 9);

    printf("The array you entered is: \n");
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }

    printf("The minimum distances from source node 0 are: \n");
    for(int i=0;i<9;i++) {
        printf("%d\n", distance[i]);
    }

    return 0;
}
