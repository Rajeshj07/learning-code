#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int BLOCK_SIZE;

// Structure to store query details
struct Query {
    int id;
    int l, r;
    
    // Sort comparator for Mo's Algorithm
    bool operator<(const Query& other) const {
        int b1 = l / BLOCK_SIZE;
        int b2 = other.l / BLOCK_SIZE;
        if (b1 != b2) {
            return b1 < b2;
        }
        // Hilbert curve / zig-zag optimization to improve cache performance
        return (b1 & 1) ? (r < other.r) : (r > other.r);
    }
};

const int MAX_VAL = 1000005; // Maximum frequency code constraint (10^6)
long long current_energy = 0;
int freq[MAX_VAL];

inline void add(int val) {
    int f = freq[val];
    current_energy += 2LL * f + 1;
    freq[val]++;
}

inline void remove(int val) {
    int f = freq[val];
    current_energy -= 2LL * f - 1;
    freq[val]--;
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    BLOCK_SIZE = max(1, (int)(n / sqrt(q)));

    vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].l >> queries[i].r;
        queries[i].id = i;
    }

    // Sort queries in offline Mo's order
    sort(queries.begin(), queries.end());

    vector<long long> answers(q);
    int cur_l = 1, cur_r = 0;

    for (int i = 0; i < q; ++i) {
        int L = queries[i].l;
        int R = queries[i].r;

        // Adjust pointers to match range [L, R]
        while (cur_r < R) {
            cur_r++;
            add(a[cur_r]);
        }
        while (cur_r > R) {
            remove(a[cur_r]);
            cur_r--;
        }
        while (cur_l < L) {
            remove(a[cur_l]);
            cur_l++;
        }
        while (cur_l > L) {
            cur_l--;
            add(a[cur_l]);
        }

        answers[queries[i].id] = current_energy;
    }

    // Print all results in original query order
    for (int i = 0; i < q; ++i) {
        cout << answers[i] << "\n";
    }

    return 0;
}
