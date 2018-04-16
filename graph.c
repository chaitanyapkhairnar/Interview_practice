/*
 * This file contains verious representations of the graph and some
 * graph algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Say we have 10 vertices in the graph
#define V 10

/* Adjacency matrix representation
 * In this representation, we have a 2D array
 * of V*V size where V is the number of vertices.
 * The value at array[i][j] represents the edge between
 * i and j vertices. If it is 0 then it means no vertex present.
 * If its non zero then it represents the weight or cost of vertex.
 */
int graph_arr[V][V];

/* Structure representation
 * In this representation, we define a Graph structure which has 2
 * integer members to represent number of vertices and number of edges.
 * Then we have an array of edge structure which represents each edge.
 * The edge structure has 3 integer members to represent src vertex, dst
 * vertex and the cost/weight of the edge.
 */
typedef struct Edge {
    int src;
    int dst;
    int cost;
}Edge;

typedef struct Graph {
    int v;
    int e;
    Edge edges[e];
}

/* Adjacency list representation
 * In this representation, We have a array of size V and this array
 * holds pointers to the head of linked lists at each of its indices.
 * Each of the V lists represent the edges. For e.g. the list whose
 * head pointer is in array[0] represents all the edges from vertex 0.
 * say there are 3 vertices from 0: 0-1, 0-2, 0-3. Then the list will
 * have 3 nodes, each node representing an edge. The node struct of linked
 * list will have 2 integer members to represent dst vertex and cost of edge.
 */
typedef struct ll_edge_node {
    int dst;
    int cost;
    struct ll_edge_node *next;
}ll_edge_node;

ll_edge_node* graph_list[V];

/******************************************************************************************/

/* Disjoint Set and finding cycles in the graph:
 * Disjoint set is a data structure that maintains a set of elements and the subsets
 * they belong to. This is basically an array of integers. If the value of array[i] is -1
 * then it means that i belongs to its own subset. if array[i] = j, then it means that
 * i belongs to subset j. Now we see array[j], say it is k and array[k] is -1 then it means
 * that k belongs to its own subset, j belongs to subset of k and i belongs to subset of j
 * and so it also belongs to subset of k.
 * Union find algorithm does two operations, find the parent set of given index and make union.
 * For making union for two vertices, we first find the parent of these two vertices. If they are
 * different, then we can either make vertex 1 as parent of vertex 2 or vice versa. Here parent
 * means find the subset of given vertex.
 *
 * Time complexity is O(n) to find the parent and O(n) to make the union. Thus its O(n) to
 * find the cycle in the graph.
 */

// We initialize parent array of size V with -1 which means initially each vertex belongs to its
// own subset.
int parent_array[V] = {-1};

// find function to get the parent set of given vertex
int find(int parent[], int vertex) {
    if(parent[vertex] == -1) {
        return vertex;
    } else {
        return find(parent, parent[vertex]);
    }
}

// union function to make union of given vertices
void union(int parent[], int src, int dst) {
    int src_set, dst_set;
    src_set = find(parent, src);
    dst_set = find(parent, dst);
    parent[src_set] = dst_set;
}

/* Now we can use above to find cycle in the graph. For each edge in the graph,
 * we find the parent for both the vertices for that edge. If the parent is same, that means
 * both the vertices belong to same set. So there is a cycle. If they are not same, we call
 * the union function to update the parents of both these vertices and continue for next edge.
 * We use the struct representation of graph here as in this, we have a list of edges and this
 * is what we need to traverse.
 */
bool Graph_has_cycle(Graph *graph) {
    int i;
    for(i=0; i<graph->e; i++) {
        int src = graph->edges[i].src;
        int dst = graph->edges[i].dst;
        int x = find(parent, src);
        int y = find(parent, dst);
        if(x == y) {
            // src and dst belong to same parent. so cycle present
            return true;
        }
        union(parent, x, y);
    }
    return false;
}

/******************************************************************************************/

/* Spanning Trees:
 * Given a connected and undirected graph, Spanning tree of this graph is a tree that connects
 * all the vertices of the graph together. A graph can have multiple spanning trees. Minimum
 * spanning tree is the tree that has minimum weight edges in it as compared to all other
 * possible spanning trees. The basic idea is to traverse the graph and add the edges traversed
 * so far in the tree making sure that the edge does not introduce the cycle in the tree.
 */

/*
 * Kruskal's Minimum Spanning Tree Algorithm:
 * The idea here is to first get the list of edges of the graph.
 * Then sort the edges in ascending order of their cost.
 * Then get the minimum cost edge, see if any cycle is formed if we add this edge to the spanning
 * tree created so far. We check this using the union find algorithm discussed above. If cycle is not
 * formed, we add this edge to our tree and proceed by taking next graph edge from the list.
 * We stop when all the count of edges included in the tree reach V-1 where V is total vertices.
 */

/*
 * Prim's Minimum Spanning Tree Algorithm:
 * This algorithm is very much similar to Dijkstras Algorithm. We maintain a boolean visited array
 * to mark the vertex as visited and part of our MST. We maintain a distance array to store the
 * edge weights and we use this to select the minimum weight edge in each run. We also maintain
 * a array to add the vertex in the order we visit them and another parent array to add the parent
 * vertex of the current vertex being visited. We need these to print the MST.
 * We first initialize the distance array to all infinite and only the src vertex as 0 so that it
 * is picked for the first time. We also mark the parent array of this index as -1 as this is the root.
 * Now we start a for loop from 0 to number of vertices. For each iteration, we get the vertex from the
 * distance array whose edge weight is minimum and it is not yet visited. Then we start another for loop
 * to get all the neighbors of this vertex such that they are not visited before. For each of these neighbors,
 * we update the distance array with new distance equal to the weight of edge from current vertex to it.
 * While updating we check that the vertex should not be visited and its current weight should be more than the
 * weight that we are adding. (This is the only difference as compared to dijkstras algo. In Dijkstras algo,
 * we update the weight by adding our current weight to the weight of edge connecting the neighbor, but here,
 * we do not consider our current weight. We only consider the weight of the edge.). Along with updating the
 * weight of neighbors, we also update the parent vertex of these neighbors as our current vertex.
 * Once the weight for all neighbors are updated, we continue the for loop.
 * At the end of for loop, we have parent array having the list of parent vertices of its index vertex. We
 * print this as MST. for e.g. for all elements in parent, edge = parent[i]------ i
 * Time complexity os O(V^2)
 */
 * the unvisited neighbors are added, we continue the for loop.
