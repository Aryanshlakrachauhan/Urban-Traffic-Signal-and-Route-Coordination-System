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

/* --- BACKEND: Matrix Chain Multiplication (Traffic Flow Transition Matrices) --- */
void dp_matrix_chain(void) {
    /* Dimensions of 4 consecutive corridor flow transition matrices: 10x20, 20x5, 5x15, 15x10 */
    int p[] = {10, 20, 5, 15, 10};
    int n = 5;
    int m[10][10];
    int i, j, k, L, q;

    for (i = 1; i < n; i++) m[i][i] = 0;

    for (L = 2; L < n; L++) {
        for (i = 1; i < n - L + 1; i++) {
            j = i + L - 1;
            m[i][j] = INF;
            for (k = i; k <= j - 1; k++) {
                q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j]) m[i][j] = q;
            }
        }
    }
    printf("\nMatrix Chain Multiplication (Corridor Transition Matrices):\n");
    printf("  Dimensions: {10x20, 20x5, 5x15, 15x10}\n");
    printf("  Minimum Scalar Operations Required: %d\n", m[1][n - 1]);
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

/* --- BACKEND: Traveling Salesperson Problem (Maintenance Patrol Tour via Bitmask DP) --- */
void dp_tsp_patrol(void) {
    /* 4-Junction Inspection Tour Cost Matrix */
    int n = 4;
    int dist[4][4] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    int dp[16][4];
    int mask, pos, next;

    for (mask = 0; mask < (1 << n); mask++)
        for (pos = 0; pos < n; pos++)
            dp[mask][pos] = INF;

    dp[1][0] = 0; /* Start at Depot Junction 0 */

    for (mask = 1; mask < (1 << n); mask++) {
        for (pos = 0; pos < n; pos++) {
            if ((mask & (1 << pos)) && dp[mask][pos] != INF) {
                for (next = 0; next < n; next++) {
                    if (!(mask & (1 << next))) {
                        int nmask = mask | (1 << next);
                        if (dp[mask][pos] + dist[pos][next] < dp[nmask][next]) {
                            dp[nmask][next] = dp[mask][pos] + dist[pos][next];
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    int full_mask = (1 << n) - 1;
    for (pos = 1; pos < n; pos++) {
        if (dp[full_mask][pos] + dist[pos][0] < ans) {
            ans = dp[full_mask][pos] + dist[pos][0];
        }
    }
    printf("\nTSP Held-Karp Bitmask DP (4-Junction Patrol Inspection Tour):\n");
    printf("  Minimum Closed-Loop Patrol Travel Time: %d mins\n", ans);
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
    printf("4. Matrix Chain Multiplication (Flow Matrix Evaluation)\n");
    printf("5. Longest Common Subsequence (Corridor Overlap)\n");
    printf("6. Traveling Salesperson Problem (Patrol Tour Bitmask DP)\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) return;

    if (choice == 1) {
        printf("Enter Integer Budget (1 to 100): ");
        scanf("%d", &budget);
        dp_knapsack_01(reqs, N, budget);
    } else if (choice == 2) {
        dp_floyd_warshall(V, roads, E);
    } else if (choice == 3) {
        dp_bellman_ford(V, roads, E, 0);
    } else if (choice == 4) {
        dp_matrix_chain();
    } else if (choice == 5) {
        dp_lcs_routes("J0-J1-J2-J4-J5", "J0-J2-J4-J5");
    } else if (choice == 6) {
        dp_tsp_patrol();
    } else {
        printf("Invalid choice.\n");
    }
}
