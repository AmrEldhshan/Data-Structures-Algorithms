# Data Structures and Algorithms Implementation 🚀

This repository contains implementations of various data structures and algorithms in C++. The project is organized into different modules, each focusing on specific concepts and implementations.

## Table of Contents 📑
- [Project Structure](#project-structure)
- [Data Structures](#data-structures)
  - [Linked Lists](#linked-lists)
  - [Stacks and Queues](#stacks-and-queues)
  - [Trees](#trees)
- [Algorithms](#algorithms)
  - [Sorting](#sorting)
  - [Complex Algorithms](#complex-algorithms)
  - [Recursion](#recursion)
- [Building and Running](#building-and-running)
- [Time Complexities](#time-complexities)

## Project Structure 📁

```
DataStructure-alg/
├── 📂 Sortings/
│   ├── 📂 Comparsion-based-sorting/
│   │   ├── 📂 Quadratic-Sorting-Algorithms/
│   │   │   ├── 📄 InsertionSort.h
│   │   │   ├── 📄 BubbleSort.h
│   │   │   └── 📄 SelectionSort.h
│   │   └── 📂 Sub-quadratic-Sorting-Algorithms/
│   │       ├── 📄 MergeSort.h
│   │       ├── 📄 QuickSort.h
│   │       ├── 📄 HeapSort.h
│   │       └── 📄 ShellSort.h
│   ├── 📂 linear-sorting-algorithms/
│   │   ├── 📄 CountSort.h
│   │   ├── 📄 RadixSort.h
│   │   └── 📄 BucketSort.h
│   └── 📂 ComplexAlgrothms/
│       └── 📄 rand_select.h
├── 📂 Liked-Lists/
│   ├── 📄 Single-Linked-List.h
│   ├── 📄 Array-Based-Lists.h
│   ├── 📄 Doubly-Linked-Lists.h
│   ├── 📄 Circular-linked-list.h
│   └── 📄 ordered-linked.list.h
├── 📂 Stacks-and-Queues/
│   ├── 📂 Stack/
│   │   └── 📄 Stack.h
│   └── 📂 Queues/
│       ├── 📄 Queues.h
│       ├── 📄 Array-Based-Queue.h
│       ├── 📄 circular_array_queue.h
│       ├── 📄 DLL_queue.h
│       ├── 📄 SLL_queue.h
│       └── 📄 priority_queue.h
├── 📂 tree/
│   ├── 📂 Heap/
│   │   ├── 📄 Max-priority-queue.h
│   │   └── 📄 heap.h
│   ├── 📂 BST/
│   │   └── 📄 BSTNode.h
│   └── 📂 AVL/
│       └── 📄 AVL.h
├── 📂 RecursionExamples/
│   └── 📄 Examples.h
├── 📄 main.cpp
└── 📄 CMakeLists.txt
```

## Data Structures 💾

### Linked Lists
The project implements various types of linked lists:

1. **Single Linked List** [`Single-Linked-List.h`]
   - Operations:
     - Insertion (Front/Back/Position): O(1) / O(n)
     - Deletion (Front/Back/Position): O(1) / O(n)
     - Search: O(n)
     - Traversal: O(n)

2. **Array-Based List** [`Array-Based-Lists.h`]
   - Operations:
     - Insertion: O(n)
     - Deletion: O(n)
     - Access: O(1)
     - Search: O(n)

3. **Doubly Linked List** [`Doubly-Linked-Lists.h`]
   - Operations:
     - Insertion (Front/Back/Position): O(1)
     - Deletion (Front/Back/Position): O(1)
     - Forward/Backward Traversal: O(n)
     - Search: O(n)

4. **Circular Linked List** [`Circular-linked-list.h`]
   - Operations:
     - Insertion: O(1) at head/tail, O(n) at position
     - Deletion: O(1) at head/tail, O(n) at position
     - Search: O(n)
     - Rotation: O(1)

5. **Ordered Linked List** [`ordered-linked.list.h`]
   - Operations:
     - Insertion (Maintaining Order): O(n)
     - Deletion: O(n)
     - Search: O(n)
     - IsSorted Check: O(n)

### Stacks and Queues
Implementation of various stack and queue data structures:

1. **Stack** [`Stack.h`]
   - Operations:
     - Push: O(1)
     - Pop: O(1)
     - Top: O(1)
     - IsEmpty: O(1)

2. **Queue Implementations**
   - **Basic Queue** [`Queues.h`]
     - Enqueue/Dequeue: O(1)
     - Front/Rear: O(1)
     - Memory Management: Dynamic

   - **Array Based Queue** [`Array-Based-Queue.h`]
     - Enqueue/Dequeue: O(1) amortized
     - Fixed Size Operations
     - Memory Management: Static

   - **Circular Array Queue** [`circular_array_queue.h`]
     - Enqueue/Dequeue: O(1)
     - Space Efficient
     - Wrap-around Implementation

   - **Double Linked List Queue** [`DLL_queue.h`]
     - Enqueue/Dequeue: O(1)
     - Bidirectional Operations
     - Memory Management: Dynamic

   - **Single Linked List Queue** [`SLL_queue.h`]
     - Enqueue/Dequeue: O(1)
     - Memory Efficient
     - FIFO Implementation

   - **Priority Queue** [`priority_queue.h`]
     - Enqueue: O(log n)
     - Dequeue: O(log n)
     - Peek: O(1)
     - Heap-based Implementation

### Trees
Implementation of various tree data structures:

1. **Binary Search Tree** [`BSTNode.h`]
   - Operations:
     - Insertion: O(h)
     - Deletion: O(h)
     - Search: O(h)
     - Traversal: O(n)

2. **AVL Tree** [`AVL.h`]
   - Operations:
     - Insertion: O(log n)
     - Deletion: O(log n)
     - Search: O(log n)
     - Rebalancing: O(1)
     - Height: Always O(log n)

3. **Heap Implementations**
   - **Basic Heap** [`heap.h`]
     - Insert: O(log n)
     - Delete: O(log n)
     - Heapify: O(n)

   - **Max Priority Queue** [`Max-priority-queue.h`]
     - Insert: O(log n)
     - Extract Max: O(log n)
     - Get Max: O(1)
     - Increase Key: O(log n)

## Algorithms 🔄

### Sorting
Comprehensive collection of sorting algorithms:

1. **Quadratic Sorting Algorithms**
   - **Bubble Sort** [`BubbleSort.h`]
     - Time: O(n²)
     - Space: O(1)
     - Stable: Yes

   - **Selection Sort** [`SelectionSort.h`]
     - Time: O(n²)
     - Space: O(1)
     - Stable: No

   - **Insertion Sort** [`InsertionSort.h`]
     - Time: O(n²)
     - Space: O(1)
     - Best Case: O(n)

2. **Sub-quadratic Sorting**
   - **Merge Sort** [`MergeSort.h`]
     - Time: O(n log n)
     - Space: O(n)
     - Stable: Yes

   - **Quick Sort** [`QuickSort.h`]
     - Time: Average O(n log n), Worst O(n²)
     - Space: O(log n)
     - In-place: Yes

   - **Heap Sort** [`HeapSort.h`]
     - Time: O(n log n)
     - Space: O(1)
     - In-place: Yes

   - **Shell Sort** [`ShellSort.h`]
     - Time: O(n log n) to O(n²)
     - Space: O(1)
     - Adaptive: Yes

3. **Linear-time Sorting**
   - **Count Sort** [`CountSort.h`]
     - Time: O(n + k)
     - Space: O(k)
     - Stable: Yes

   - **Radix Sort** [`RadixSort.h`]
     - Time: O(d * (n + k))
     - Space: O(n + k)
     - Stable: Yes

   - **Bucket Sort** [`BucketSort.h`]
     - Time: Average O(n + k)
     - Space: O(n + k)
     - Distribution dependent

### Complex Algorithms
Advanced algorithm implementations:

1. **Randomized Select** [`rand_select.h`]
   - Average Time: O(n)
   - Worst Time: O(n²)
   - Selection algorithm for kth smallest element
   - Based on QuickSort partitioning

### Recursion Examples
Classic recursion problem implementations:

1. **Factorial** [`Examples.h`]
   - Time: O(n)
   - Space: O(n)
   - Recursive implementation

2. **Tower of Hanoi** [`Examples.h`]
   - Time: O(2ⁿ)
   - Space: O(n)
   - Classic recursion problem

## Building and Running 🛠️

### Prerequisites
- C++ Compiler (C++20 or later)
- CMake (3.10 or later)
- Windows/Linux/MacOS operating system

### Build Instructions
1. Clone the repository
2. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```
3. Generate build files:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```

### Running the Program
After building, run the executable:
```bash
./final_revision
```

### Build Script
The project includes a PowerShell build script (`build.ps1`) that provides additional build options:
- Clean build: `./build.ps1 -Clean`
- Debug build: `./build.ps1 -Debug`
- Release build: `./build.ps1 -Config Release`
- Custom build directory: `./build.ps1 -BuildDir custom_dir`

## Project Organization 📋

### Source Organization
- All header files (.h) contain both declarations and implementations
- Implementation follows modern C++ practices
- Consistent naming conventions throughout the codebase
- Comprehensive error handling and input validation

### Code Style
- The project uses clang-format for consistent code formatting
- Style configuration is provided in `.clang-format` file
- Follows modern C++ coding guidelines
- Comprehensive comments and documentation

### Testing
The main program provides several testing features:
1. Input validation for all operations
2. Boundary condition testing
3. Performance measurement options
4. Memory leak detection (in debug mode)
5. Error handling demonstration

## Testing Different Implementations 🧪

The main program provides a comprehensive menu system to test:
1. All sorting algorithms with custom input
2. Linked list operations
3. Stack and queue operations
4. Tree structure operations
5. Recursion examples

Each module can be tested independently through the menu interface.

## Contributing 🤝

Feel free to contribute to this project by:
1. Fork the repository
2. Create a new feature branch
3. Commit your changes
4. Create a pull request

## License 📝

This project is open source and available under the MIT License.

---
Made with ❤️ using C++
