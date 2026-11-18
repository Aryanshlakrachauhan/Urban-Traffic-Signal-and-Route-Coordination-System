#include "traffic.h"

/* --- Helper: Flush stdin buffer on invalid input --- */
void flush_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* --- FRONTEND: Main Application Dashboard & Scenario Controller --- */
void print_network_status(int V, Road roads[], int E) {
    int i;
    printf("\n--- Current City Road Network (%d Junctions, %d Roads) ---\n", V, E);
    for (i = 0; i < E; i++) {
        printf("  [%d] Junction %d -> %d | Time: %2d min | Cap: %2d veh/min | Status: %s\n",
               i, roads[i].u, roads[i].v, roads[i].time, roads[i].capacity,
               roads[i].blocked ? "BLOCKED (INCIDENT)" : "OPEN");
    }
}

int main(void) {
    int V = 6;
    int E = 8;
    Road roads[MAX_E] = {
        {0, 1, 5, 40, 0},
        {0, 2, 8, 35, 0},
        {1, 2, 2, 30, 0},
        {1, 3, 7, 25, 0},
        {2, 4, 4, 45, 0},
        {3, 4, 3, 30, 0},
        {3, 5, 6, 35, 0},
        {4, 5, 4, 40, 0}
    };

    int N = 4;
    SignalReq reqs[MAX_REQ] = {
        {101, 0, 15, 50, 10},
        {102, 10, 25, 70, 15},
        {103, 15, 30, 60, 12},
        {104, 30, 45, 90, 20}
    };

    int page = -1;
    int road_idx;

    while (page != 0) {
        printf("\n******************************************************\n");
        printf("  URBAN TRAFFIC SIGNAL & ROUTE COORDINATION (CSEG3053)\n");
        printf("******************************************************\n");
        printf("  [1] Page 1: Divide & Conquer + Sorting\n");
        printf("  [2] Page 2: Greedy Algorithms (Activity, Dijkstra, Kruskal, Prim, Knapsack, Huffman)\n");
        printf("  [3] Page 3: Dynamic Programming (0/1 Knapsack, Floyd, Bellman, Matrix Chain, LCS, TSP)\n");
        printf("  [4] Page 4: Backtracking & Branch-and-Bound\n");
        printf("  [5] Page 5: Network Flow (Ford-Fulkerson) & Bipartite Matching\n");
        printf("  [6] Page 6: Chinese Remainder Theorem & String Matching (Naive, RK, FA, KMP)\n");
        printf("  [7] View Road Network Status\n");
        printf("  [8] Toggle Road Incident Blockage (Live Demo Scenario Shock)\n");
        printf("  [0] Exit\n");
        printf("Select Page / Option: ");

        if (scanf("%d", &page) != 1) {
            printf("Invalid input. Please enter a number between 0 and 8.\n");
            flush_input();
            page = -1;
            continue;
        }

        switch (page) {
            case 1:
                run_dnc_page(roads, E);
                break;
            case 2:
                run_greedy_page(V, roads, E, reqs, N);
                break;
            case 3:
                run_dp_page(V, roads, E, reqs, N);
                break;
            case 4:
                run_backtracking_bnb_page(reqs, N);
                break;
            case 5:
                run_flow_matching_page(V, roads, E);
                break;
            case 6:
                run_math_string_page();
                break;
            case 7:
                print_network_status(V, roads, E);
                break;
            case 8:
                print_network_status(V, roads, E);
                printf("Enter Road Index (0 to %d) to block/unblock: ", E - 1);
                if (scanf("%d", &road_idx) == 1 && road_idx >= 0 && road_idx < E) {
                    roads[road_idx].blocked = !roads[road_idx].blocked;
                    printf("Road [%d] status updated to: %s\n",
                           road_idx, roads[road_idx].blocked ? "BLOCKED" : "OPEN");
                } else {
                    printf("Invalid road index.\n");
                    flush_input();
                }
                break;
            case 0:
                printf("Exiting Urban Traffic Coordination System.\n");
                break;
            default:
                printf("Invalid option. Choose 0 to 8.\n");
        }
    }
    return 0;
}
