# cpp-linear-algebra
Basic linear algebra

## Timing reference:

### Without template expression
```
Running performance tests

Dimension: 100000000
# runs: 10

assign_add
add
multiple_add
Timing Report
| description      | # | duration [s]  | avg duration [s] |
-------------------|---|---------------|-------------------
| run_multiple_add | 1 |       25.6382 |          25.6382 |
| run_add          | 1 |        8.1315 |           8.1315 |
| run_assign_add   | 1 |        0.4504 |           0.4504 |
-------------------|---|---------------|-------------------
| Overall          | 1 |       37.5033 |       N/A        |
```

### With template expressions

```
Running performance tests

Dimension: 100000000
# runs: 10

assign_add
add
multiple_add
Timing Report
| description      | # | duration [s]  | avg duration [s] |
-------------------|---|---------------|-------------------
| run_multiple_add | 1 |        1.3221 |           1.3221 |
| run_add          | 1 |        1.5408 |           1.5408 |
| run_assign_add   | 1 |        0.4238 |           0.4238 |
-------------------|---|---------------|-------------------
| Overall          | 1 |        6.5127 |       N/A        |
```
