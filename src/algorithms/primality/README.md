# Primality testing

A prime number has exactly two divisors: 1 and itself. These files show five
ways to decide whether a number is prime, from the simplest to the fastest.

## Files

| File | Method | Type | Time |
| --- | --- | --- | --- |
| `trial_division.cpp` | Test divisors up to √n | Deterministic | O(√n) |
| `sieve_of_eratosthenes.cpp` | Mark multiples of each prime | Deterministic | O(n log log n) |
| `fermat_primality_test.cpp` | Fermat's little theorem | Probabilistic | O(k log n) |
| `miller_rabin_test.cpp` | Strong probable-prime test | Probabilistic | O(k log³ n) |
| `aks_primality_test.cpp` | AKS | Deterministic, polynomial | — |

`k` is the number of random witnesses.

## Trial division

If `n` has a factor greater than √n, it must also have one smaller than √n. So
it is enough to test `i = 2 .. √n`.

## Sieve of Eratosthenes

Create a boolean array of size `n + 1`, start assuming every number is prime,
then cross out multiples of each prime starting at `i²`. What remains is prime.
This is the fastest way to find **all** primes up to `n`.

## Fermat test

Fermat's little theorem says: if `p` is prime and `a` is not a multiple of `p`,
then `a^(p-1) ≡ 1 (mod p)`.

Pick random `a` and check the congruence. A composite that passes is called a
**Fermat liar**. Carmichael numbers (for example `561`) pass many Fermat tests,
so this test alone is not safe.

## Miller-Rabin

Miller-Rabin writes `n - 1 = d * 2^s` with `d` odd, then checks a stronger
condition on `a^d`. It has no known "liar" set as bad as Carmichael numbers, and
with enough witnesses the error probability is negligible. It is the standard
practical test.

## AKS — important note

The AKS test is the first deterministic polynomial-time primality test. The file
in this repository is a **teaching placeholder**: its comment says so, and it
currently falls back to trial division. A real implementation is long and is a
good contribution if you want to study the algorithm in depth.

## Run

```bash
./build/bin/algo_trial_division
./build/bin/algo_sieve
./build/bin/algo_fermat
./build/bin/algo_miller_rabin
./build/bin/algo_aks
```

## Exercises

1. Run Fermat and Miller-Rabin on `561`. What do they report? Research why.
2. Modify the sieve to count primes instead of printing them. Compare with `n /
   ln(n)`.
3. Why is trial division enough up to √n?
