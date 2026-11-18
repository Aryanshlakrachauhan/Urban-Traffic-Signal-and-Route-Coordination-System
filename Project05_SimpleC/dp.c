#include "traffic.h"

/* --- BACKEND: 0/1 Knapsack (Exact Integer Signal Upgrade Selection) --- */
void dp_knapsack_01(SignalReq reqs[], int n, int W) {
    int dp[MAX_REQ + 1][101];
    int i, w;
    if (W > 100) W = 100;

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (i == 0 || w == 0) dp[i][w] = 0;
            else if (reqs[i - 1].cost <= w) {
                int inc = reqs[i - 1].priority + dp[i - 1][w - reqs[i - 1].cost];
                int exc = dp[i - 1][w];
                dp[i][w] = (inc > exc) ? inc : exc;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    printf("\n0/1 Knapsack Optimal Priority Score (Budget %d): %d\n", W, dp[n][W]);
}

/* --- BACKEND: Floyd-Warshall All-Pairs Shortest Path --- */
void dp_floyd_warshall(int V, Road roads[], int E) {
    int dist[MAX_V][MAX_V];
    int i, j, k;

    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (i = 0; i < E; i++) {
        if (!roads[i].blocked && roads[i].time < dist[roads[i].u][roads[i].v]) {
            dist[roads[i].u][roads[i].v] = roads[i].time;
        }
    }

    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    printf("\nAll-Pairs Shortest Travel Matrix (Floyd-Warshall):\n    ");
    for (j = 0; j < V; j++) printf("J%-4d", j);
    printf("\n");
    for (i = 0; i < V; i++) {
        printf("J%-2d ", i);
        for (j = 0; j < V; j++) {
            if (dist[i][j] == INF) printf("INF  ");
            else printf("%-5d", dist[i][j]);
        }
        printf("\n");
    }
}

/* --- BACKEND: Bellman-Ford (Handles Negative Toll Rebates) --- */
void dp_bellman_ford(int V, Road roads[], int E, int src) {
    int dist[MAX_V];
    int i, j;
    for (i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    for (i = 1; i <= V - 1; i++) {
        for (j = 0; j < E; j++) {
            if (!roads[j].blocked && dist[roads[j].u] != INF &&
                dist[roads[j].u] + roads[j].time < dist[roads[j].v]) {
                dist[roads[j].v] = dist[roads[j].u] + roads[j].time;
            }
        }
    }

    printf("\nBellman-Ford Shortest Paths from Junction %d:\n", src);
    for (i = 0; i < V; i++) {
        if (dist[i] == INF) printf("  To Junction %d: UNREACHABLE\n", i);
        else printf("  To Junction %d: %d mins\n", i, dist[i]);
    }
}

/* --- BACKEND: Longest Common Subsequence (Route Pattern Similarity) --- */
void dp_lcs_routes(const char* r1, const char* r2) {
    int m = (int)strlen(r1);
    int n = (int)strlen(r2);
    int dp[50][50];
    int i, j;

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0) dp[i][j] = 0;
            else if (r1[i - 1] == r2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
            else dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
        }
    }
    printf("\nRoute 1: %s | Route 2: %s\n", r1, r2);
    printf("Shared Junction Sequence Length (LCS): %d\n", dp[m][n]);
}

/* --- FRONTEND: Page 3 Menu --- */
void run_dp_page(int V, Road roads[], int E, SignalReq reqs[], int N) {
    int choice, budget;
    printf("\n======================================================\n");
    printf("PAGE 3: DYNAMIC PROGRAMMING MODULE\n");
    printf("======================================================\n");
    printf("1. 0/1 Knapsack (Exact Signal Upgrade Allocation)\n");
    printf("2. Floyd-Warshall (All-Pairs City Travel Matrix)\n");
    printf("3. Bellman-Ford (Single-Source with Rebate Support)\n");
    printf("4. Longest Common Subsequence (Corridor Overlap)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter Integer Budget (1 to 100): ");
        scanf("%d", &budget);
        dp_knapsack_01(reqs, N, budget);
    } else if (choice == 2) {
        dp_floyd_warshall(V, roads, E);
    } else if (choice == 3) {
        dp_bellman_ford(V, roads, E, 0);
    } else if (choice == 4) {
        dp_lcs_routes("J0-J1-J2-J4-J5", "J0-J2-J4-J5");
    } else {
        printf("Invalid choice.\n");
    }
}
