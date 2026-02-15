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

#### double

```
Timing Report
| description          | # | duration [s]  | avg duration [s] |
-----------------------|---|---------------|-------------------
| run_multiple_add     | 1 |        1.3432 |           1.3432 |
| run_add              | 1 |        1.6670 |           1.6670 |
| run_multiple_add_sub | 1 |        1.3383 |           1.3383 |
| run_assign_add       | 1 |        0.8400 |           0.8400 |
| init                 | 1 |        2.2248 |           2.2248 |
-----------------------|---|---------------|-------------------
| Overall              | 1 |        8.5145 |       N/A        |
```

#### float

```
Timing Report
| description          | # | duration [s]  | avg duration [s] |
-----------------------|---|---------------|-------------------
| run_multiple_add     | 1 |        0.6917 |           0.6917 |
| run_add              | 1 |        0.8109 |           0.8109 |
| run_multiple_add_sub | 1 |        0.6858 |           0.6858 |
| run_assign_add       | 1 |        0.4314 |           0.4314 |
| init                 | 1 |        2.3098 |           2.3098 |
-----------------------|---|---------------|-------------------
| Overall              | 1 |        5.3297 |       N/A        |
```

## Matrix and vector, vector with template expressions, matrix without

```
| description              | # | duration [s]  | avg duration [s] |
---------------------------|---|---------------|-------------------
| mat_run_multiple_add     | 1 |       21.9540 |          21.9540 |
| mat_run_add              | 1 |        8.2352 |           8.2352 |
| mat_run_assign_add       | 1 |        0.7975 |           0.7975 |
| vec_run_multiple_add_sub | 1 |        1.3455 |           1.3455 |
| vec_run_multiple_add     | 1 |        1.3279 |           1.3279 |
| vec_run_add              | 1 |        1.6720 |           1.6720 |
| vec_run_assign_add       | 1 |        1.0796 |           1.0796 |
| init                     | 2 |        4.4303 |           2.2151 |
---------------------------|---|---------------|-------------------
| Overall                  | 1 |       42.4324 |       N/A        |
```

## Matrix and vector with template expressions

```
Timing Report
| description              | # | duration [s]  | avg duration [s] |
---------------------------|---|---------------|-------------------
| mat_run_multiple_add     | 1 |        1.3435 |           1.3435 |
| run_multiple_add_sub     | 1 |        1.3479 |           1.3479 |
| mat_run_add              | 1 |        1.6759 |           1.6759 |
| mat_run_assign_add       | 1 |        0.8368 |           0.8368 |
| vec_run_multiple_add_sub | 1 |        1.4457 |           1.4457 |
| vec_run_multiple_add     | 1 |        1.3815 |           1.3815 |
| vec_run_add              | 1 |        1.6906 |           1.6906 |
| vec_run_assign_add       | 1 |        0.8674 |           0.8674 |
| init                     | 2 |        4.4453 |           2.2227 |
---------------------------|---|---------------|-------------------
| Overall                  | 1 |       16.7358 |       N/A        |
```

## Todo
* [ ] Do we need dedicated vector and matrix operants?
