#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    int num_guardians = 2 * N;
    vector<vector<long long>> cost(num_guardians, vector<long long>(num_guardians));

    for (int i = 0; i < num_guardians; ++i) {
        for (int j = 0; j < num_guardians; ++j) {
            cin >> cost[i][j];
        }
    }

    int total_states = 1 << num_guardians;
    // dp[mask] stores the maximum compatibility score for the subset of paired guardians represented by 'mask'
    vector<long long> dp(total_states, -1);
    dp[0] = 0; // Base case: 0 guardians paired -> 0 total score

    for (int mask = 0; mask < total_states; ++mask) {
        if (dp[mask] == -1) continue; // Unreachable state

        // Find the first unpaired guardian (first bit that is 0)
        int first_unpaired = -1;
        for (int i = 0; i < num_guardians; ++i) {
            if (!(mask & (1 << i))) {
                first_unpaired = i;
                break;
            }
        }

        // If all guardians are paired, move on
        if (first_unpaired == -1) continue;

        // Try pairing the first unpaired guardian with all other remaining unpaired guardians
        for (int partner = first_unpaired + 1; partner < num_guardians; ++partner) {
            if (!(mask & (1 << partner))) {
                int next_mask = mask | (1 << first_unpaired) | (1 << partner);
                dp[next_mask] = max(dp[next_mask], dp[mask] + cost[first_unpaired][partner]);
            }
        }
    }

    // Output the optimal answer when all guardians are paired
    cout << dp[total_states - 1] << "\n";

    return 0;
}
