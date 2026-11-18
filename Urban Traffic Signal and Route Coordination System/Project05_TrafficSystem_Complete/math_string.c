#include "traffic.h"

/* --- BACKEND: Chinese Remainder Theorem (Signal Cycle Synchronization) --- */
int mod_inverse(int a, int m) {
    int x;
    a = a % m;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return 1;
}

int crt_sync(int rem[], int mod[], int k) {
    int prod = 1, result = 0, i;
    for (i = 0; i < k; i++) prod *= mod[i];
    for (i = 0; i < k; i++) {
        int pp = prod / mod[i];
        result += rem[i] * mod_inverse(pp, mod[i]) * pp;
    }
    return result % prod;
}

/* --- BACKEND: 1. Naive String Matching --- */
void naive_search(const char* text, const char* pat) {
    int n = (int)strlen(text);
    int m = (int)strlen(pat);
    int i, j;
    printf("  [1] Naive Matches at index:            ");
    for (i = 0; i <= n - m; i++) {
        for (j = 0; j < m; j++) {
            if (text[i + j] != pat[j]) break;
        }
        if (j == m) printf("%d ", i);
    }
    printf("\n");
}

/* --- BACKEND: 2. Rabin-Karp String Matching --- */
void rabin_karp_search(const char* text, const char* pat) {
    int n = (int)strlen(text);
    int m = (int)strlen(pat);
    int d = 256;
    int q = 101;
    int p = 0, t = 0, h = 1;
    int i, j;

    for (i = 0; i < m - 1; i++) h = (h * d) % q;
    for (i = 0; i < m; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + text[i]) % q;
    }

    printf("  [2] Rabin-Karp Matches at index:       ");
    for (i = 0; i <= n - m; i++) {
        if (p == t) {
            for (j = 0; j < m; j++) {
                if (text[i + j] != pat[j]) break;
            }
            if (j == m) printf("%d ", i);
        }
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;
            if (t < 0) t += q;
        }
    }
    printf("\n");
}

/* --- BACKEND: 3. Finite Automaton String Matching --- */
int get_next_state(const char* pat, int m, int state, int x) {
    if (state < m && x == (unsigned char)pat[state]) return state + 1;
    int ns, i;
    for (ns = state; ns > 0; ns--) {
        if ((unsigned char)pat[ns - 1] == x) {
            for (i = 0; i < ns - 1; i++) {
                if (pat[i] != pat[state - ns + 1 + i]) break;
            }
            if (i == ns - 1) return ns;
        }
    }
    return 0;
}

void finite_automaton_search(const char* text, const char* pat) {
    int n = (int)strlen(text);
    int m = (int)strlen(pat);
    int (*TF)[256] = malloc((m + 1) * sizeof(*TF));
    if (!TF) return;

    int state, x, i;
    for (state = 0; state <= m; ++state) {
        for (x = 0; x < 256; ++x) {
            TF[state][x] = get_next_state(pat, m, state, x);
        }
    }

    printf("  [3] Finite Automaton Matches at index: ");
    state = 0;
    for (i = 0; i < n; i++) {
        state = TF[state][(unsigned char)text[i]];
        if (state == m) printf("%d ", i - m + 1);
    }
    printf("\n");
    free(TF);
}

/* --- BACKEND: 4. KMP String Matching --- */
void kmp_search(const char* text, const char* pat) {
    int n = (int)strlen(text);
    int m = (int)strlen(pat);
    int *lps = (int*)malloc(m * sizeof(int));
    if (!lps) return;

    int len = 0, i = 1, j = 0;
    lps[0] = 0;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else if (len != 0) {
            len = lps[len - 1];
        } else {
            lps[i] = 0;
            i++;
        }
    }

    printf("  [4] KMP Matches at index:              ");
    i = 0;
    while (i < n) {
        if (pat[j] == text[i]) { i++; j++; }
        if (j == m) {
            printf("%d ", i - j);
            j = lps[j - 1];
        } else if (i < n && pat[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    printf("\n");
    free(lps);
}

/* --- FRONTEND: Page 6 Menu --- */
void run_math_string_page(void) {
    int choice;
    int rem[3] = {2, 3, 2};
    int mod[3] = {3, 5, 7};
    const char* log_stream = "OK_JAM_ALERT_OK_JAM_ALERT_CLEAR";
    const char* pattern = "JAM_ALERT";

    printf("\n======================================================\n");
    printf("PAGE 6: NUMBER THEORY (CRT) & STRING MATCHING MODULE\n");
    printf("======================================================\n");
    printf("1. Chinese Remainder Theorem (Multi-Signal Green Wave Sync)\n");
    printf("2. Incident Event Stream Search (Naive, Rabin-Karp, Finite Automaton, KMP)\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) return;

    if (choice == 1) {
        int tick = crt_sync(rem, mod, 3);
        printf("Signal Cycle Moduli: {3s, 5s, 7s} | Offsets: {2s, 3s, 2s}\n");
        printf("Next Synchronized Green-Wave Tick (CRT): %d seconds\n", tick);
    } else if (choice == 2) {
        printf("Sensor Log: %s\n", log_stream);
        printf("Searching Pattern: %s\n\n", pattern);
        naive_search(log_stream, pattern);
        rabin_karp_search(log_stream, pattern);
        finite_automaton_search(log_stream, pattern);
        kmp_search(log_stream, pattern);
    } else {
        printf("Invalid choice.\n");
    }
}
