#include "traffic.h"

/* --- BACKEND: BFS Helper for Ford-Fulkerson (Edmonds-Karp) --- */
int bfs_residual(int rGraph[MAX_V][MAX_V], int V, int s, int t, int parent[]) {
    int visited[MAX_V];
    int queue[MAX_V];
    int front = 0, rear = 0, i, u, v;

    for (i = 0; i < V; i++) visited[i] = 0;
    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (front < rear) {
        u = queue[front++];
        for (v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                parent[v] = u;
                if (v == t) return 1;
                queue[rear++] = v;
                visited[v] = 1;
            }
        }
    }
    return 0;
}

/* --- BACKEND: Ford-Fulkerson Maximum Corridor Throughput --- */
int ford_fulkerson_flow(int V, Road roads[], int E, int s, int t) {
    int rGraph[MAX_V][MAX_V];
    int parent[MAX_V];
    int i, j, u, v, max_flow = 0;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            rGraph[i][j] = 0;

    for (i = 0; i < E; i++) {
        if (!roads[i].blocked) {
            rGraph[roads[i].u][roads[i].v] += roads[i].capacity;
        }
    }

    while (bfs_residual(rGraph, V, s, t, parent)) {
        int path_flow = INF;
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            if (rGraph[u][v] < path_flow) path_flow = rGraph[u][v];
        }
        for (v = t; v != s; v = parent[v]) {
            u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }
        max_flow += path_flow;
    }
    return max_flow;
}

/* --- BACKEND: Maximum Bipartite Matching (Traffic Police / Drone Assignment) --- */
int bpm_dfs(int bpGraph[4][4], int u, int seen[], int matchR[]) {
    int v;
    for (v = 0; v < 4; v++) {
        if (bpGraph[u][v] && !seen[v]) {
            seen[v] = 1;
            if (matchR[v] < 0 || bpm_dfs(bpGraph, matchR[v], seen, matchR)) {
                matchR[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

void run_bipartite_matching(void) {
    /* 4 Emergency Units matched to 4 Congested Junctions */
    int bpGraph[4][4] = {
        {1, 1, 0, 0},
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {0, 0, 1, 0}
    };
    int matchR[4] = {-1, -1, -1, -1};
    int seen[4];
    int u, i, result = 0;

    for (u = 0; u < 4; u++) {
        for (i = 0; i < 4; i++) seen[i] = 0;
        if (bpm_dfs(bpGraph, u, seen, matchR)) result++;
    }

    printf("\nMaximum Bipartite Matching (Traffic Units -> Junctions): %d assigned\n", result);
    for (i = 0; i < 4; i++) {
        if (matchR[i] != -1) {
            printf("  Junction %d <- Assigned Traffic Unit %d\n", i, matchR[i]);
        }
    }
}

/* --- FRONTEND: Page 5 Menu --- */
void run_flow_matching_page(int V, Road roads[], int E) {
    int choice;
    printf("\n======================================================\n");
    printf("PAGE 5: NETWORK FLOW & BIPARTITE MATCHING MODULE\n");
    printf("======================================================\n");
    printf("1. Ford-Fulkerson Max Traffic Throughput (Junction 0 -> %d)\n", V - 1);
    printf("2. Maximum Bipartite Matching (Traffic Units to Junctions)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int flow = ford_fulkerson_flow(V, roads, E, 0, V - 1);
        printf("Maximum Vehicle Flow Capacity (0 -> %d): %d vehicles/min\n", V - 1, flow);
    } else if (choice == 2) {
        run_bipartite_matching();
    } else {
        printf("Invalid choice.\n");
    }
}
