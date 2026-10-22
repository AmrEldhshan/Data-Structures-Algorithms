#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Game theory: Nim and Grundy numbers
//
// Nim: several piles; a move removes any positive number of objects from one
// pile. The position is losing exactly when the XOR of pile sizes is 0.
//
// Grundy numbers generalise Nim to any impartial game:
//   grundy(position) = mex{ grundy(next position) }
// A position is losing when its Grundy number is 0.
// ---------------------------------------------------------------------------
int nimSum(const vector<int>& piles) {
    int result = 0;
    for (int pile : piles) result ^= pile;
    return result;
}

// Returns the pile and the new size for a winning move, or {-1, -1}.
pair<int, int> winningNimMove(const vector<int>& piles) {
    int target = nimSum(piles);
    if (target == 0) return {-1, -1};

    for (int i = 0; i < static_cast<int>(piles.size()); ++i) {
        int smaller = piles[i] ^ target;
        if (smaller < piles[i]) return {i, smaller};
    }

    return {-1, -1};
}

int mex(const vector<bool>& seen) {
    for (int value = 0; value < static_cast<int>(seen.size()); ++value) {
        if (!seen[value]) return value;
    }
    return static_cast<int>(seen.size());
}

vector<int> grundyNumbers(int limit, const vector<int>& moves) {
    vector<int> grundy(limit + 1, 0);

    for (int position = 1; position <= limit; ++position) {
        vector<bool> seen(limit + 2, false);

        for (int move : moves) {
            if (move > position) break;
            seen[grundy[position - move]] = true;
        }

        grundy[position] = mex(seen);
    }

    return grundy;
}

int main() {
    vector<int> piles = {3, 4, 5};
    cout << "Nim piles: 3 4 5\n";
    cout << "nim-sum: " << nimSum(piles) << '\n';

    auto [pile, newSize] = winningNimMove(piles);
    if (pile == -1) {
        cout << "position is losing for the player to move\n";
    } else {
        cout << "winning move: pile " << pile << " from " << piles[pile]
             << " to " << newSize << '\n';
    }

    // Subtraction game: a player may remove 1, 3, or 4 objects.
    vector<int> moves = {1, 3, 4};
    vector<int> grundy = grundyNumbers(20, moves);

    cout << "\nsubtraction game {1,3,4}, Grundy numbers:\n  ";
    for (int i = 0; i <= 20; ++i) cout << grundy[i] << ' ';
    cout << "\npositions with Grundy 0 are losing: ";
    for (int i = 0; i <= 20; ++i) {
        if (grundy[i] == 0) cout << i << ' ';
    }
    cout << '\n';

    return 0;
}
