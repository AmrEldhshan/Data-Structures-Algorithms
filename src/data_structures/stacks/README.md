# Stacks

A stack is **LIFO**: the last element pushed is the first one popped. Think of a
pile of plates.

```text
push ->  [ 30 ]  <- top
         [ 20 ]
         [ 10 ]
pop  ->  removes 30
```

## File

`stack.h` implements a stack with a singly linked list of nodes. Because both
push and pop happen at the head, they are O(1).

It also contains small, practical utilities that show *why* stacks matter:

| Function | Purpose |
| --- | --- |
| `isBalancedExpression(expr)` | Check `()[]{}` nesting |
| `infixToPostfix(expr)` | Convert `a+b*c` to `a b c * +` |
| `evaluatePostfix(expr)` | Evaluate a postfix expression |
| `addLargeNumbers(a, b)` | Add huge numbers digit by digit |

## How the stack is built

```cpp
struct Node {
    T data;
    Node* next;
};

void push(const T& value) {
    Node* node = new Node{value, head};
    head = node;
    ++size;
}
```

`pop()` moves `head` to `head->next` and deletes the old node. `top()` reads
`head->data`. If the stack is empty, the implementation throws
`std::runtime_error` instead of returning garbage.

## Complexity

| Operation | Time |
| --- | --- |
| push | O(1) |
| pop | O(1) |
| top / peek | O(1) |
| search | O(n) |
| space | O(n) |

## Why infix to postfix needs a stack

Operators must wait until you know whether a later operator has higher
precedence. The stack stores the waiting operators. When you read `)`, you pop
until `(`. This is the classic application of a stack.

## Exercise

Evaluate `3 4 + 2 *` by hand, then run it through `evaluatePostfix`. The answer
should be `14`.
