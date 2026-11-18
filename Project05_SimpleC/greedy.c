#include "traffic.h"

/* --- BACKEND: Activity Selection for Non-Overlapping Signal Phases --- */
void greedy_activity_selection(SignalReq reqs[], int n) {
    SignalReq arr[MAX_REQ], temp;
    int i, j;
    for (i = 0; i < n; i++) arr[i] = reqs[i];

    /* Simple Bubble Sort by finish time */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j].end > arr[j + 1].end) {
                temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }
        }
    }

    printf("\nSelected Non-Overlapping Green Signal Phases:\n");
    int last_end = -1;
    for (i = 0; i < n; i++) {
        if (arr[i].start >= last_end) {
            printf("  Phase ID %d: [%d sec -> %d sec] (Priority: %d)\n",
                   arr[i].id, arr[i].start, arr[i].end, arr[i].priority);
            last_end = arr[i].end;
        }
    }
}

/* --- BACKEND: Dijkstra Shortest Path --- */
void dijkstra_shortest_path(int V, Road roads[], int E, int src) {
    int graph[MAX_V][MAX_V];
    int dist[MAX_V], visited[MAX_V];
    int i, j, count, u, v;

    for (i = 0; i < V; i++) {
        dist[i] = INF;
        visited[i] = 0;
        for (j = 0; j < V; j++) graph[i][j] = INF;
    }

    for (i = 0; i < E; i++) {
        if (!roads[i].blocked && roads[i].time < graph[roads[i].u][roads[i].v]) {
            graph[roads[i].u][roads[i].v] = roads[i].time;
        }
    }

    dist[src] = 0;
    for (count = 0; count < V - 1; count++) {
        int min_dist = INF;
        u = -1;
        for (i = 0; i < V; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                u = i;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nDijkstra Shortest Travel Times from Junction %d:\n", src);
    for (i = 0; i < V; i++) {
        if (dist[i] == INF) printf("  To Junction %d: UNREACHABLE\n", i);
        else printf("  To Junction %d: %d mins\n", i, dist[i]);
    }
}

/* --- BACKEND: Kruskal MST for Smart Sensor Cable Backbone --- */
int find_parent(int parent[], int i) {
    while (parent[i] != i) i = parent[i];
    return i;
}

void kruskal_mst(int V, Road roads[], int E) {
    Road arr[MAX_E], temp;
    int parent[MAX_V];
    int i, j, total_cost = 0, edges_used = 0;

    for (i = 0; i < E; i++) arr[i] = roads[i];
    for (i = 0; i < V; i++) parent[i] = i;

    for (i = 0; i < E - 1; i++) {
        for (j = 0; j < E - i - 1; j++) {
            if (arr[j].time > arr[j + 1].time) {
                temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }
        }
    }

    printf("\nKruskal Minimum Spanning Tree (Sensor Network Backbone):\n");
    for (i = 0; i < E; i++) {
        if (arr[i].blocked) continue;
        int r1 = find_parent(parent, arr[i].u);
        int r2 = find_parent(parent, arr[i].v);
        if (r1 != r2) {
            printf("  Link (%d - %d) | Cost/Time: %d\n", arr[i].u, arr[i].v, arr[i].time);
            total_cost += arr[i].time;
            parent[r1] = r2;
            edges_used++;
        }
    }
    printf("Total MST Backbone Cost: %d (Edges connected: %d/%d)\n", total_cost, edges_used, V - 1);
}

/* --- BACKEND: Fractional Knapsack for Emergency Bandwidth Allocation --- */
void fractional_knapsack(SignalReq reqs[], int n, int max_bw) {
    SignalReq arr[MAX_REQ], temp;
    int i, j;
    for (i = 0; i < n; i++) arr[i] = reqs[i];

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            double r1 = (double)arr[j].priority / arr[j].cost;
            double r2 = (double)arr[j + 1].priority / arr[j + 1].cost;
            if (r1 < r2) {
                temp = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = temp;
            }
        }
    }

    int rem = max_bw;
    double total_val = 0.0;
    printf("\nFractional Knapsack (Bandwidth Budget = %d):\n", max_bw);
    for (i = 0; i < n; i++) {
        if (arr[i].cost <= rem) {
            rem -= arr[i].cost;
            total_val += arr[i].priority;
            printf("  Take 100%% of Phase %d (Cost: %d, Value: %d)\n", arr[i].id, arr[i].cost, arr[i].priority);
        } else if (rem > 0) {
            double frac = (double)rem / arr[i].cost;
            total_val += arr[i].priority * frac;
            printf("  Take %.1f%% of Phase %d (Cost used: %d, Value: %.2f)\n", frac * 100.0, arr[i].id, rem, arr[i].priority * frac);
            rem = 0;
        }
    }
    printf("Total Priority Value Achieved: %.2f\n", total_val);
}

/* --- FRONTEND: Page 2 Menu --- */
void run_greedy_page(int V, Road roads[], int E, SignalReq reqs[], int N) {
    int choice, src, budget;
    printf("\n======================================================\n");
    printf("PAGE 2: GREEDY ALGORITHMS MODULE\n");
    printf("======================================================\n");
    printf("1. Signal Phase Scheduling (Activity Selection)\n");
    printf("2. Fastest Vehicle Route (Dijkstra's Algorithm)\n");
    printf("3. Sensor Fiber Backbone (Kruskal's MST)\n");
    printf("4. Bandwidth Allocation (Fractional Knapsack)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        greedy_activity_selection(reqs, N);
    } else if (choice == 2) {
        printf("Enter Source Junction (0 to %d): ", V - 1);
        scanf("%d", &src);
        if (src >= 0 && src < V) dijkstra_shortest_path(V, roads, E, src);
        else printf("Invalid junction ID.\n");
    } else if (choice == 3) {
        kruskal_mst(V, roads, E);
    } else if (choice == 4) {
        printf("Enter Bandwidth Budget (e.g., 25): ");
        scanf("%d", &budget);
        fractional_knapsack(reqs, N, budget);
    } else {
        printf("Invalid choice.\n");
    }
}
