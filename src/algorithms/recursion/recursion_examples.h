//
// Created by Amr on 6/4/2025.
//

#ifndef EXAMPLES_H
#define EXAMPLES_H
#include <iostream>
using namespace std;
long long Factorial(long long n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    return n * Factorial(n - 1);
}


void solveTowerOfHanoi(int numbersOfDisks, char sourceRod,char auxiliaryRod,char targetRod) {
    if (numbersOfDisks <= 0) {
        return; // Nothing to move
    }

    if (numbersOfDisks == 1) {
        cout << "move disk 1 from " << sourceRod << " to " << targetRod << endl;
        return; // Base case: stop recursing
    }

    // Move the top n-1 disks out of the way.
    solveTowerOfHanoi(numbersOfDisks - 1, sourceRod, targetRod, auxiliaryRod);

    // Move the largest remaining disk onto the target rod.
    cout << "move disk " << numbersOfDisks << " from " << sourceRod << " to " << targetRod << endl;

    // Move the n-1 disks from the auxiliary rod onto the largest disk.
    solveTowerOfHanoi(numbersOfDisks - 1 , auxiliaryRod, sourceRod, targetRod);
}


#endif //EXAMPLES_H
