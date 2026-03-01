# Visual studio

```
================================================================================
       REPORT: performance tests

   # runs:              10
   default vector size: 100000000
   default matrix rows: 1000
   default matrix cols: 100000000
================================================================================

+---------------------------------------+---------------------+------+------------+------------+
| test name                             | label               | runs | total[s]   | avg[s]     |
+---------------------------------------+---------------------+------+------------+------------+
| vector_add                            | vector              |   10 |      1.173 |     0.1173 |
| vector_multiple_add                   | vector              |   10 |      1.189 |     0.1189 |
| vector_mixed_add_sub                  | vector              |   10 |      1.166 |     0.1166 |
| vector_resize                         | vector              |   10 |      1.388 |     0.1388 |
| vector_assign                         | vector              |   10 |      1.636 |     0.1636 |
| vector_add_assign                     | vector              |   10 |     0.8376 |    0.08376 |
| vector_sum_add_assign                 | vector              |   10 |        1.2 |       0.12 |
| matrix_add row                        | row_matrix          |   10 |      1.164 |     0.1164 |
| matrix_multiple_add row               | row_matrix          |   10 |      1.169 |     0.1169 |
| matrix_mixed_add_sub row              | row_matrix          |   10 |      1.188 |     0.1188 |
| matrix_resize row                     | row_matrix          |   10 |       1.42 |      0.142 |
| matrix_assign row                     | row_matrix          |   10 |      1.683 |     0.1683 |
| matrix_assign_add row                 | row_matrix          |   10 |     0.8552 |    0.08552 |
| matrix_assign_add_sum row             | row_matrix          |   10 |     0.8589 |    0.08589 |
| vector_assign_matrix_vector_mult row  | row_matrix          |   10 |     0.2355 |    0.02355 |
| matrix_add col                        | col_matrix          |   10 |      8.011 |     0.8011 |
| matrix_multiple_add col               | col_matrix          |   10 |      13.02 |      1.302 |
| matrix_mixed_add_sub col              | col_matrix          |   10 |       9.95 |      0.995 |
| matrix_resize col                     | col_matrix          |   10 |      1.526 |     0.1526 |
| matrix_assign col                     | col_matrix          |   10 |      1.744 |     0.1744 |
| matrix_assign_add col                 | col_matrix          |   10 |     0.9765 |    0.09765 |
| matrix_assign_add_sum col             | col_matrix          |   10 |      1.034 |     0.1034 |
| matrix_multiply_blocked_row row * row | matrix_mult_blocked |   10 |      11.07 |      1.107 |
| matrix_multiply_blocked_row row * col | matrix_mult_blocked |   10 |      10.52 |      1.052 |
| matrix_multiply_blocked_row col * row | matrix_mult_blocked |   10 |      16.57 |      1.657 |
| matrix_multiply_blocked_row col * col | matrix_mult_blocked |   10 |      20.01 |      2.001 |
| matrix_multiply_blocked_col row * row | matrix_mult_blocked |   10 |      19.11 |      1.911 |
| matrix_multiply_blocked_col row * col | matrix_mult_blocked |   10 |       18.5 |       1.85 |
| matrix_multiply_blocked_col col * row | matrix_mult_blocked |   10 |      16.79 |      1.679 |
| matrix_multiply_blocked_col col * col | matrix_mult_blocked |   10 |      16.55 |      1.655 |
| decompose_solve_lu_col: row           | col_algorithms      |   10 |      13.25 |      1.325 |
| decompose_solve_lu_col: col           | col_algorithms      |   10 |      9.944 |     0.9944 |
| matrix_add_sub_mixed_storage          | mixed_matrix        |   10 |      2.496 |     0.2496 |
| matrix_assign_storage_mismatch        | mixed_matrix        |   10 |      2.316 |     0.2316 |
| decompose_solve_lu_row: row           | row_algorithms      |   10 |      3.116 |     0.3116 |
| decompose_solve_lu_row: col           | row_algorithms      |   10 |      3.204 |     0.3204 |
| vector_assign_matrix_vector_mult col  | cols_matrix         |   10 |       1.34 |      0.134 |
+---------------------------------------+---------------------+------+------------+------------+
| total                                 |                     |      |      218.2 |            |
+---------------------------------------+---------------------+------+------------+------------+

================================================================================
    SUMMARY: performance tests
Performed tests     : 37
Total test result   : 0
Failed tests        : 0
Total execution time: 237.9s
================================================================================
```
