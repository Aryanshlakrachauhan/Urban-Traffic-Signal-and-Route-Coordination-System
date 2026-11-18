# Project 05: Urban Traffic Signal and Route Coordination System (Simple C)

## Compilation and Run (Offline)
```bash
gcc -std=c17 -O2 -Wall main.c dnc_sort.c greedy.c dp.c backtracking_bnb.c flow_matching.c math_string.c -o traffic_sim
./traffic_sim
```
Or using Make:
```bash
make
make run
```

## Implemented Algorithm Modules
1. **Divide & Conquer + Sorting (`dnc_sort.c`)**: Merge Sort, Quick Sort, Binary Search (Iterative & Recursive), Maximum Subarray (D&C).
2. **Greedy Algorithms (`greedy.c`)**: Activity Selection, Dijkstra's Shortest Path, Kruskal's MST, Prim's MST, Fractional Knapsack, Huffman Coding.
3. **Dynamic Programming (`dp.c`)**: 0/1 Knapsack, Floyd-Warshall, Bellman-Ford, Matrix Chain Multiplication, Longest Common Subsequence (LCS), Traveling Salesperson Problem (Bitmask DP).
4. **Backtracking & Branch-and-Bound (`backtracking_bnb.c`)**: Subset Sum Backtracking, N-Queens Solver, 0/1 Knapsack Branch-and-Bound.
5. **Network Flow & Bipartite Matching (`flow_matching.c`)**: Ford-Fulkerson (Edmonds-Karp BFS) Max-Flow, Maximum Bipartite Matching.
6. **Number Theory & String Matching (`math_string.c`)**: Chinese Remainder Theorem (CRT), Naive, Rabin-Karp, Finite Automaton, KMP.
