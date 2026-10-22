# Game theory

Impartial games have no hidden information and the same moves for both players.
Two tools solve most introductory problems: the **Nim-sum** and **Grundy
numbers**.

## File

| File | Contents |
| --- | --- |
| `game_theory.cpp` | Nim winner and winning move, Sprague-Grundy for a subtraction game |

## Nim

Players remove any positive number of objects from one pile. The position is
losing for the player to move exactly when

```text
piles[0] XOR piles[1] XOR ... XOR piles[n-1] == 0
```

A winning move changes one pile so that the XOR becomes zero.

## Grundy numbers

For any impartial game:

```text
grundy(position) = mex{ grundy(next position) for every legal move }
```

`mex` is the smallest non-negative integer not in the set. A position is losing
when its Grundy number is 0. The Grundy number of a sum of independent games is
the XOR of their Grundy numbers.

## Run

```bash
./build/bin/algo_game_theory
```

## Exercises

1. Find a winning move for piles `{3, 4, 5}` by hand.
2. Compute Grundy numbers for the subtraction game `{1, 2, 3}`.
3. Why does the XOR rule work for Nim?
4. Add a move that may split one pile into two piles.
