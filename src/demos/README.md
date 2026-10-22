# Demos

Small programs that bring the headers together.

| File | CMake target | What it shows |
| --- | --- | --- |
| `main.cpp` | `dsa_demo` | Every sorting algorithm on the same array, all four searches, factorial, Tower of Hanoi |
| `heap_demo.cpp` | `demo_heap` | Inserting into a max-heap, extracting max/min, heap sort, restoring the heap, and a heap-based priority queue |

## Run

```bash
./build/bin/dsa_demo
./build/bin/demo_heap
```

Or build and run with a single command from the repository root:

```bash
g++ -std=c++20 -Isrc src/demos/main.cpp -o /tmp/dsa_demo && /tmp/dsa_demo
```

## Reading order

1. `main.cpp` — start here; it shows the header include style.
2. `heap_demo.cpp` — a complete walkthrough of one data structure.
3. The per-topic examples under `src/data_structures/` and `src/algorithms/`.

## Adding a demo

Create `my_demo.cpp`, include the headers you need, and add one line to
`CMakeLists.txt`:

```cmake
dsa_add_demo(my_demo "${CMAKE_CURRENT_SOURCE_DIR}/src/demos/my_demo.cpp")
```

Keep the demo small. Its job is to show *how to call* the implementation, not to
re-implement it.
