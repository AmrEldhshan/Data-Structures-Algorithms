# Number theory

Number-theory routines appear in cryptography, hashing, competitive
programming, and almost every area that deals with divisibility or modular
arithmetic.

## Files

| File | Contents |
| --- | --- |
| `number_theory.h` | GCD, LCM, extended GCD, modular exponentiation, modular inverse, totient, factorisation, binomial, Catalan |
| `crt.cpp` | Chinese remainder theorem |
| `pollard_rho.cpp` | Pollard's rho factorisation + deterministic Miller-Rabin |
| `matrix_exponentiation.cpp` | General matrix power and Fibonacci |
| `gaussian_elimination.cpp` | Solve a linear system with partial pivoting |
| `ntt.cpp` | Number-theoretic transform and polynomial multiplication |
| `../../demos/number_theory_demo.cpp` | Runnable demonstration |

Primarily: `number_theory::gcd`, `lcm`, `extendedGcd`, `modPow`, `modInverse`,
`totient`, `factorize`, `binomialMod`, `catalan`.

## Euclid's algorithm

```text
gcd(a, b) = gcd(b, a mod b)
gcd(a, 0) = a
```

Each step at least halves `b`, so the running time is `O(log min(a, b))`.

**Extended GCD** also finds `x` and `y` such that

```text
a * x + b * y = gcd(a, b)
```

When `gcd(a, m) = 1`, `x` is the modular inverse of `a` modulo `m`. This is how
`modInverse` works without exponentiation.

## Modular exponentiation

Compute `base^exponent mod m` by repeated squaring:

```text
3^13 = 3^8 * 3^4 * 3^1
```

The exponent is halved each step, so the cost is `O(log exponent)` instead of
`O(exponent)`.

## Euler's totient

`phi(n)` counts numbers in `[1, n]` that are coprime to `n`. Factorise `n` and
use

```text
phi(n) = n * product(1 - 1/p) for every distinct prime p
```

For `n = 36 = 2² * 3²`, `phi(36) = 36 * (1/2) * (2/3) = 12`.

## Factorisation

`factorize(n)` trial-divides up to `sqrt(n)` and returns `(prime, exponent)`
pairs. It is `O(sqrt n)`, fine for teaching and small inputs. Large inputs need
Pollard's rho (in `pollard_rho.cpp`) for large inputs.

## Chinese remainder theorem

Given pairwise-coprime moduli `m_i` and residues `a_i`, CRT reconstructs the
unique solution modulo `M = product(m_i)`:

```text
x = sum(a_i * (M / m_i) * inverse(M / m_i mod m_i)) mod M
```

The program checks that the moduli are pairwise coprime and verifies the answer.

## Pollard's rho

For large composites, trial division is too slow. Pollard's rho uses the
sequence `x -> x² + c (mod n)` and Floyd's cycle detection; a non-trivial
`gcd(|x - y|, n)` reveals a factor. Miller-Rabin decides whether a remaining
value is prime, and the two routines recurse until the factorisation is
complete. The demo uses deterministic 64-bit Miller-Rabin bases and overflow-safe
modular multiplication.

## Matrix exponentiation

Repeated squaring works for matrices too. For Fibonacci:

```text
[F(n+1)]   [1 1]^n   [F(1)]
[F(n)  ] = [1 0]   * [F(0)]
```

The cost is `O(k³ log n)` for `k x k` matrices.

## Gaussian elimination

Forward elimination with partial pivoting turns `Ax = b` into an upper-triangular
system; back substitution then finds `x`. The demo reports a singular matrix if
a pivot is (numerically) zero.

## NTT (fast polynomial multiplication)

The number-theoretic transform evaluates a polynomial at powers of a primitive
root of unity modulo `998244353`. Pointwise multiplication of two transforms,
followed by the inverse transform, multiplies polynomials in O(n log n) instead
of O(n²).

## Binomial coefficients

`C(n, r) = n! / (r! (n-r)!)`. `binomialMod` precomputes factorials modulo a
prime larger than `n` and uses a modular inverse. `catalan(n)` evaluates the
Catalan recurrence directly.

## Run

```bash
./build/bin/demo_number_theory
./build/bin/algo_crt
./build/bin/algo_pollard_rho
./build/bin/algo_matrix_exponentiation
./build/bin/algo_gaussian_elimination
./build/bin/algo_ntt
```

## Exercises

1. Compute `gcd(1071, 462)` by hand with Euclid.
2. Find `x` and `y` for `30x + 18y = 6`.
3. Why does `modInverse` require `gcd(a, m) = 1`?
4. Compute `phi(100)` from its prime factorisation.
5. How many trailing zeros does `100!` have? (Hint: count factors of 5.)
6. Verify that `Catalan(n)` counts balanced parenthesis strings for `n = 1..5`.
