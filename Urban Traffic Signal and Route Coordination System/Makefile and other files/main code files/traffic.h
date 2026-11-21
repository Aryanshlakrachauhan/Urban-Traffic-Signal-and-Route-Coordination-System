#ifndef TRAFFIC_H
#define TRAFFIC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_V 20
#define MAX_E 50
#define MAX_REQ 20
#define INF 999999

typedef struct {
    int u;
    int v;
    int time;
    int capacity;
    int blocked;
} Road;

typedef struct {
    int id;
    int start;
    int end;
    int priority;
    int cost;
} SignalReq;

/* Page 1: Divide & Conquer + Sorting */
void run_dnc_page(Road roads[], int E);

/* Page 2: Greedy Algorithms (Activity Selection, Dijkstra, Kruskal, Prim, Fractional Knapsack, Huffman) */
void run_greedy_page(int V, Road roads[], int E, SignalReq reqs[], int N);

/* Page 3: Dynamic Programming (0/1 Knapsack, Floyd-Warshall, Bellman-Ford, Matrix Chain, LCS, TSP) */
void run_dp_page(int V, Road roads[], int E, SignalReq reqs[], int N);

/* Page 4: Backtracking & Branch and Bound (Subset Sum, N-Queens, 0/1 Knapsack BnB) */
void run_backtracking_bnb_page(SignalReq reqs[], int N);

/* Page 5: Network Flow & Bipartite Matching (Ford-Fulkerson & Max Matching) */
void run_flow_matching_page(int V, Road roads[], int E);

#endif
