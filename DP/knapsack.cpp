#include <stdio.h>
#include <algorithm>

using namespace std;

int knapsack(int W, int wt[], int val[], int n)
{
    int dp[W + 1] = {0};

    for (int i = 0; i < n; i++)
    {
        for (int w = W; w >= wt[i]; w--)
        {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}

int main()
{
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);

    printf("Maximum value = %d\n", knapsack(W, wt, val, n));
    return 0;
}
