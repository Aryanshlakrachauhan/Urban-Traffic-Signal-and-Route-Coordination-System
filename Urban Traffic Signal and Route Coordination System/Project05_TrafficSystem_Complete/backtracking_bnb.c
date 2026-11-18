#include "traffic.h"

/* --- BACKEND: Subset Sum Backtracking (Exact Green-Wave Power Load) --- */
void subset_sum_bt(int loads[], int n, int idx, int curr_sum, int target, int chosen[], int chosen_len) {
    int i;
    if (curr_sum == target) {
        printf("  Valid Junction Combination: { ");
        for (i = 0; i < chosen_len; i++) printf("%d ", chosen[i]);
        printf("}\n");
        return;
    }
    if (idx >= n || curr_sum > target) return;

    chosen[chosen_len] = loads[idx];
    subset_sum_bt(loads, n, idx + 1, curr_sum + loads[idx], target, chosen, chosen_len + 1);
    subset_sum_bt(loads, n, idx + 1, curr_sum, target, chosen, chosen_len);
}

/* --- BACKEND: N-Queens Constraint Solver (Non-Interfering Sensor Towers) --- */
int is_safe_queen(int board[], int row, int col) {
    int i;
    for (i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row)) return 0;
    }
    return 1;
}

int solve_nqueens(int board[], int row, int n) {
    int col, i, j;
    if (row == n) {
        printf("\nNon-Interfering 4x4 Sensor Grid Placement:\n");
        for (i = 0; i < n; i++) {
            printf("  ");
            for (j = 0; j < n; j++) {
                printf("%c ", (board[i] == j) ? 'S' : '.');
            }
            printf("\n");
        }
        return 1;
    }
    for (col = 0; col < n; col++) {
        if (is_safe_queen(board, row, col)) {
            board[row] = col;
            if (solve_nqueens(board, row + 1, n)) return 1;
        }
    }
    return 0;
}

/* --- BACKEND: Branch and Bound (0/1 Knapsack Exact Search with Upper Bound Pruning) --- */
int best_bnb_val = 0;

void knapsack_bnb(SignalReq reqs[], int n, int idx, int curr_w, int curr_v, int W) {
    int i;
    if (curr_w <= W && curr_v > best_bnb_val) {
        best_bnb_val = curr_v;
    }
    if (idx >= n || curr_w >= W) return;

    /* Upper bound estimation */
    int bound = curr_v;
    for (i = idx; i < n; i++) bound += reqs[i].priority;
    if (bound <= best_bnb_val) return; /* Prune branch */

    if (curr_w + reqs[idx].cost <= W) {
        knapsack_bnb(reqs, n, idx + 1, curr_w + reqs[idx].cost, curr_v + reqs[idx].priority, W);
    }
    knapsack_bnb(reqs, n, idx + 1, curr_w, curr_v, W);
}

/* --- FRONTEND: Page 4 Menu --- */
void run_backtracking_bnb_page(SignalReq reqs[], int N) {
    int choice, target, budget;
    int loads[5] = {10, 15, 20, 25, 30};
    int chosen[5];
    int board[4];

    printf("\n======================================================\n");
    printf("PAGE 4: BACKTRACKING & BRANCH-AND-BOUND MODULE\n");
    printf("======================================================\n");
    printf("1. Subset Sum Backtracking (Exact Power Grid Target)\n");
    printf("2. N-Queens Constraint Solver (4x4 Radar Placement)\n");
    printf("3. Branch & Bound 0/1 Knapsack (Pruned Exact Search)\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) return;

    if (choice == 1) {
        printf("Available Signal Loads: {10, 15, 20, 25, 30}\n");
        printf("Enter Target Power Load (e.g., 45): ");
        scanf("%d", &target);
        subset_sum_bt(loads, 5, 0, 0, target, chosen, 0);
    } else if (choice == 2) {
        solve_nqueens(board, 0, 4);
    } else if (choice == 3) {
        printf("Enter Bandwidth Budget (e.g., 25): ");
        scanf("%d", &budget);
        best_bnb_val = 0;
        knapsack_bnb(reqs, N, 0, 0, 0, budget);
        printf("Branch-and-Bound Optimal Value (with Pruning): %d\n", best_bnb_val);
    } else {
        printf("Invalid choice.\n");
    }
}
