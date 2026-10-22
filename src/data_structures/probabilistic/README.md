# Probabilistic data structures

These structures trade exactness for space or speed. They are common in
databases, caches, network monitoring, and analytics.

## Files

| File | Structure | Guarantee | Space |
| --- | --- | --- | --- |
| `count_min_sketch.h` | Count-min sketch | Frequency estimate never underestimates | O(width × depth) |
| `hyperloglog.h` | HyperLogLog | Cardinality estimate with ~1.04/√m error | O(2^precision) bytes |
| `cuckoo_filter.h` | Cuckoo filter | Membership with deletion, false positives only | O(capacity) |

## Count-min sketch

Hash each item once per row and take the minimum counter. Collisions can only
increase counters, so `estimate(x) >= trueFrequency(x)`. More rows reduce the
overestimate probability; more columns reduce the collision rate.

## HyperLogLog

The hash prefix chooses a register. The suffix's leading-zero count updates that
register's maximum. The harmonic mean of `2^register` estimates the number of
distinct items. Small cardinalities use a linear-counting correction.

## Cuckoo filter

Each item is reduced to a fingerprint and has two candidate buckets. Insertion
"kicks" a fingerprint to its alternate bucket if both buckets are full. Lookups
check both buckets. Deletion works because fingerprints are stored explicitly;
false positives are possible, false negatives are not (unless an item is
deleted twice).

## Run the demos

```bash
./build/bin/demo_count_min_sketch
./build/bin/demo_hyperloglog
./build/bin/demo_cuckoo_filter
```
