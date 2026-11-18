#include "traffic.h"

/* --- BACKEND: Merge Sort --- */
void merge_roads(Road arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    Road L[MAX_E], R[MAX_E];
    int i, j, k;

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i].time <= R[j].time) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

void merge_sort_roads(Road arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_roads(arr, l, m);
        merge_sort_roads(arr, m + 1, r);
        merge_roads(arr, l, m, r);
    }
}

/* --- BACKEND: Quick Sort --- */
int partition_roads(Road arr[], int low, int high) {
    int pivot = arr[high].time;
    int i = low - 1;
    int j;
    Road temp;
    for (j = low; j < high; j++) {
        if (arr[j].time < pivot) {
            i++;
            temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}

void quick_sort_roads(Road arr[], int low, int high) {
    if (low < high) {
        int pi = partition_roads(arr, low, high);
        quick_sort_roads(arr, low, pi - 1);
        quick_sort_roads(arr, pi + 1, high);
    }
}

/* --- BACKEND: Iterative & Recursive Binary Search --- */
int binary_search_iter(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

int binary_search_rec(int arr[], int low, int high, int target) {
    if (low > high) return -1;
    int mid = low + (high - low) / 2;
    if (arr[mid] == target) return mid;
    if (arr[mid] < target) return binary_search_rec(arr, mid + 1, high, target);
    return binary_search_rec(arr, low, mid - 1, target);
}

/* --- BACKEND: Maximum Subarray (Divide & Conquer) --- */
int max_crossing_sum(int arr[], int l, int m, int r) {
    int sum = 0, left_sum = -INF, right_sum = -INF, i;
    for (i = m; i >= l; i--) {
        sum += arr[i];
        if (sum > left_sum) left_sum = sum;
    }
    sum = 0;
    for (i = m + 1; i <= r; i++) {
        sum += arr[i];
        if (sum > right_sum) right_sum = sum;
    }
    return left_sum + right_sum;
}

int max_subarray_dnc(int arr[], int l, int r) {
    if (l == r) return arr[l];
    int m = (l + r) / 2;
    int a = max_subarray_dnc(arr, l, m);
    int b = max_subarray_dnc(arr, m + 1, r);
    int c = max_crossing_sum(arr, l, m, r);
    int best = (a > b) ? a : b;
    return (best > c) ? best : c;
}

/* --- FRONTEND: Page 1 Menu --- */
void run_dnc_page(Road roads[], int E) {
    Road copy[MAX_E];
    int i, choice, target;
    int junction_ids[6] = {10, 20, 30, 40, 50, 60};
    int traffic_delta[6] = {-5, 12, 18, -4, 25, -10};

    for (i = 0; i < E; i++) copy[i] = roads[i];

    printf("\n======================================================\n");
    printf("PAGE 1: DIVIDE & CONQUER + SORTING MODULE\n");
    printf("======================================================\n");
    printf("1. Sort Roads by Travel Time (Merge Sort)\n");
    printf("2. Sort Roads by Travel Time (Quick Sort)\n");
    printf("3. Search Junction ID (Iterative & Recursive Binary Search)\n");
    printf("4. Find Peak Congestion Window (Max Subarray D&C)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 2) {
        if (choice == 1) merge_sort_roads(copy, 0, E - 1);
        else quick_sort_roads(copy, 0, E - 1);

        printf("\nSorted Roads (Fastest to Slowest):\n");
        for (i = 0; i < E; i++) {
            printf("  Road %d -> %d | Time: %d min | Cap: %d | Blocked: %s\n",
                   copy[i].u, copy[i].v, copy[i].time, copy[i].capacity,
                   copy[i].blocked ? "YES" : "NO");
        }
    } else if (choice == 3) {
        printf("Available Sorted Junction IDs: 10, 20, 30, 40, 50, 60\n");
        printf("Enter Junction ID to search: ");
        scanf("%d", &target);
        int idx1 = binary_search_iter(junction_ids, 6, target);
        int idx2 = binary_search_rec(junction_ids, 0, 5, target);
        printf("Iterative Search Index: %d | Recursive Search Index: %d\n", idx1, idx2);
    } else if (choice == 4) {
        int peak = max_subarray_dnc(traffic_delta, 0, 5);
        printf("Hourly Traffic Change Array: {-5, 12, 18, -4, 25, -10}\n");
        printf("Maximum Cumulative Traffic Surge: +%d vehicles\n", peak);
    } else {
        printf("Invalid choice.\n");
    }
}
