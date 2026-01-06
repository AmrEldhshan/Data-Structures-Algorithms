// number of prop = 2^n


#include <iostream>
using namespace std;

int arr[] = {3, 34, 4, 12, 5, 2};
int n = 6;

bool subsetSum(int i, int sum) {
    if (sum == 0)
        return true;
    if (i == n)
        return false;

    return subsetSum(i + 1, sum) ||
           subsetSum(i + 1, sum - arr[i]);
}

int main() {
    int target = 9;
    if (subsetSum(0, target))
        cout << "Subset exists";
    else
        cout << "No subset";
}
