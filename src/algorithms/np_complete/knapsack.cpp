#include <iostream>
using namespace std;

int n, W;
int weight[20], value[20];

int knapsack(int i, int remainingW) {
    if (i == n || remainingW == 0)
        return 0;

    // لو الوزن أكبر من المتاح → سيبه
    if (weight[i] > remainingW)
        return knapsack(i + 1, remainingW);

    // اختار الأفضل: تاخده أو تسيبه
    int take = value[i] + knapsack(i + 1, remainingW - weight[i]);
    int leave = knapsack(i + 1, remainingW);

    return max(take, leave);
}

int main() {
    n = 3;
    W = 5;
    weight[0] = 2; value[0] = 4;
    weight[1] = 3; value[1] = 5;
    weight[2] = 4; value[2] = 6;

    cout << "Max value = " << knapsack(0, W);
}
