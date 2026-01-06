// #include "Sortings/Comparsion-based-sorting/Quadratic-Sorting-Algorithms/InsertionSort.h"
// #include "Sortings/Comparsion-based-sorting/Sub-quadratic-Sorting-Algorithms/MergeSort.h"
// #include "Sortings/Comparsion-based-sorting/Sub-quadratic-Sorting-Algorithms/QuickSort.h"
// #include "Sortings/linear-sorting-algorithms/CountSort.h"
// #include "Sortings/linear-sorting-algorithms/RadixSort.h"
// #include "Liked-Lists/Single-Linked-List.h"
// #include "Liked-Lists/Array-Based-Lists.h"
// #include "Liked-Lists/Doubly-Linked-Lists.h"
// #include "Stacks-and-Queues/Stack/Stack.h"
// #include "Stacks-and-Queues/Queues/Queues.h"
// #include "Stacks-and-Queues/Queues/Array-Based-Queue.h"
// #include "tree/Heap/Max-priority-queue.h"
// #include "tree/BST/BSTNode.h"
// #include "RecursionExamples/Examples.h"
#include "Stacks-and-Queues/Queues/based on heap/Heap.h"
#include "Stacks-and-Queues/Queues/based on heap/PriorityQueue.h"

#include <iostream>
using namespace std;

int main() {
    std::cout << "=== Testing Heap ===" << std::endl;
    Heap h;

    h.insert(10);
    h.insert(30);
    h.insert(20);
    h.insert(5);
    h.insert(15);

    std::cout << "Heap elements: ";
    h.print();

    std::cout << "Extract Max: " << h.extractMax() << std::endl;
    std::cout << "Heap after extractMax: ";
    h.print();

    std::cout << "Extract Min: " << h.extractMin() << std::endl;
    std::cout << "Heap after extractMin: ";
    h.print();

    // Heap sort (ascending)
    std::cout << "HeapSort (ascending): ";
    h.heapSort();
    h.print();

    // Restore max heap after heapSort
    h.buildMaxHeap();
    std::cout << "Heap restored after HeapSort: ";
    h.print();

    std::cout << "\n=== Testing PriorityQueue ===" << std::endl;
    PriorityQueue pq;
    pq.insert(50);
    pq.insert(20);
    pq.insert(40);
    pq.insert(10);

    std::cout << "PriorityQueue elements: ";
    pq.print();

    std::cout << "Extract Highest Priority: " << pq.extractHighestPriority() << std::endl;
    std::cout << "PriorityQueue after extraction: ";
    pq.print();

    return 0;
}




// void displayMainMenu() {
//     cout << "\n=== Data Structures and Algorithms Testing Menu ===\n";
//     cout << "1. Sorting Algorithms\n";
//     cout << "2. Linked Lists\n";
//     cout << "3. Stack and Queue\n";
//     cout << "4. Tree Structures\n";
//     cout << "5. Recursion Examples\n";
//     cout << "0. Exit\n";
//     cout << "Enter your choice: ";
// }

// void testSortingAlgorithms() {
//     int choice;
//     do {
//         cout << "\n=== Sorting Algorithms ===\n";
//         cout << "1. Insertion Sort\n";
//         cout << "2. Merge Sort\n";
//         cout << "3. Quick Sort\n";
//         cout << "4. Count Sort\n";
//         cout << "5. Radix Sort\n";
//         cout << "0. Back to Main Menu\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         if (choice >= 1 && choice <= 5) {
//             cout << "Enter array size: ";
//             int size;
//             cin >> size;
//             int* arr = new int[size];

//             cout << "Enter " << size << " elements:\n";
//             for (int i = 0; i < size; i++) {
//                 cin >> arr[i];
//             }

//             switch(choice) {
//                 case 1:
//                     // Call InsertionSort
//                     break;
//                 case 2:
//                     // Call MergeSort
//                     break;
//                 case 3:
//                     // Call QuickSort
//                     break;
//                 case 4:
//                     // Call CountSort
//                     break;
//                 case 5:
//                     // Call RadixSort
//                     break;
//             }

//             cout << "Sorted array: ";
//             for (int i = 0; i < size; i++) {
//                 cout << arr[i] << " ";
//             }
//             cout << endl;

//             delete[] arr;
//         }
//     } while (choice != 0);
// }

// void testLinkedLists() {
//     int choice;
//     do {
//         cout << "\n=== Linked Lists ===\n";
//         cout << "1. Single Linked List\n";
//         cout << "2. Array Based List\n";
//         cout << "3. Doubly Linked List\n";
//         cout << "0. Back to Main Menu\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         // Add implementation for linked list operations
//     } while (choice != 0);
// }

// void testStackAndQueue() {
//     int choice;
//     do {
//         cout << "\n=== Stack and Queue ===\n";
//         cout << "1. Stack\n";
//         cout << "2. Queue\n";
//         cout << "3. Array Based Queue\n";
//         cout << "0. Back to Main Menu\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         // Add implementation for stack and queue operations
//     } while (choice != 0);
// }

// void testTreeStructures() {
//     int choice;
//     do {
//         cout << "\n=== Tree Structures ===\n";
//         cout << "1. Max Priority Queue (Heap)\n";
//         cout << "2. Binary Search Tree\n";
//         cout << "0. Back to Main Menu\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         // Add implementation for tree operations
//     } while (choice != 0);
// }

// void testRecursionExamples() {
//     int choice;
//     do {
//         cout << "\n=== Recursion Examples ===\n";
//         cout << "1. Factorial\n";
//         cout << "2. Tower of Hanoi\n";
//         cout << "0. Back to Main Menu\n";
//         cout << "Enter your choice: ";
//         cin >> choice;

//         switch(choice) {
//             case 1: {
//                 cout << "Enter a number: ";
//                 long long n;
//                 cin >> n;
//                 cout << "Factorial of " << n << " is: " << Factorial(n) << endl;
//                 break;
//             }
//             case 2: {
//                 cout << "Enter number of disks: ";
//                 int n;
//                 cin >> n;
//                 solveTowerOfHanoi(n, 'A', 'B', 'C');
//                 break;
//             }
//         }
//     } while (choice != 0);
// }

// int main() {
//     int choice;
//     do {
//         displayMainMenu();
//         cin >> choice;

//         switch(choice) {
//             case 1:
//                 testSortingAlgorithms();
//                 break;
//             case 2:
//                 testLinkedLists();
//                 break;
//             case 3:
//                 testStackAndQueue();
//                 break;
//             case 4:
//                 testTreeStructures();
//                 break;
//             case 5:
//                 testRecursionExamples();
//                 break;
//         }
//     } while (choice != 0);

//     cout << "Thank you for using the program!\n";
//     return 0;
// }
