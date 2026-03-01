# LU decomposition

## Before blocking:

```
+-----------------------------+----------------+------+------------+------------+
| test name                   | label          | runs | total[s]   | avg[s]     |
+-----------------------------+----------------+------+------------+------------+
| decompose_solve_lu_col: row | col_algorithms |   10 |      10.77 |      1.077 |
| decompose_solve_lu_col: col | col_algorithms |   10 |      10.88 |      1.088 |
| lu_decomposecol: row        | col_algorithms |   10 |      10.81 |      1.081 |
| lu_decomposecol: col        | col_algorithms |   10 |      10.85 |      1.085 |
| decompose_solve_lu_row: row | row_algorithms |   10 |     0.8042 |    0.08042 |
| decompose_solve_lu_row: col | row_algorithms |   10 |     0.8125 |    0.08125 |
| lu_decomposerow: row        | row_algorithms |   10 |     0.7849 |    0.07849 |
| lu_decomposerow: col        | row_algorithms |   10 |     0.8096 |    0.08096 |
+-----------------------------+----------------+------+------------+------------+
| total                       |                |      |      46.53 |            |
+-----------------------------+----------------+------+------------+------------+
```

## After blocking (only consider row-row and col-col)

```
================================================================================
       REPORT: performance tests

   # runs:              10
   default vector size: 100000000
   default matrix rows: 1000
   default matrix cols: 100000000
================================================================================

+------------------------------+----------------+------+------------+------------+
| test name                    | label          | runs | total[s]   | avg[s]     |
+------------------------------+----------------+------+------------+------------+
| decompose_solve_lu(col): col | col_algorithms |   10 |     0.3389 |    0.03389 |
| lu_decompose (col): col      | col_algorithms |   10 |     0.3194 |    0.03194 |
| decompose_solve_lu(row): row | row_algorithms |   10 |     0.2135 |    0.02135 |
| lu_decompose (row): row      | row_algorithms |   10 |     0.1984 |    0.01984 |
+------------------------------+----------------+------+------------+------------+
| total                        |                |      |       1.07 |            |
+------------------------------+----------------+------+------------+------------+

================================================================================
    SUMMARY: performance tests
Performed tests     : 4
Total test result   : 0
Failed tests        : 0
Total execution time: 1.418s
================================================================================
```

## Comparison with Eigen:
```
Solving a linear equation system (size 1000) 10 times for column based storage took: 0.17524s, avg: 0.017524
Solving a linear equation system (size 1000) 10 times for column based storage took: 0.167743s, avg: 0.0167743
```
