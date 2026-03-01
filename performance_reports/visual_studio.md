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
| vector_add                            | vector              |   10 |      1.245 |     0.1245 |
| vector_multiple_add                   | vector              |   10 |      1.254 |     0.1254 |
| vector_mixed_add_sub                  | vector              |   10 |      1.234 |     0.1234 |
| vector_resize                         | vector              |   10 |      1.372 |     0.1372 |
| vector_assign                         | vector              |   10 |       1.63 |      0.163 |
| vector_add_assign                     | vector              |   10 |     0.8671 |    0.08671 |
| vector_sum_add_assign                 | vector              |   10 |      1.248 |     0.1248 |
| matrix_add row                        | row_matrix          |   10 |      1.276 |     0.1276 |
| matrix_multiple_add row               | row_matrix          |   10 |      1.283 |     0.1283 |
| matrix_mixed_add_sub row              | row_matrix          |   10 |      1.212 |     0.1212 |
| matrix_resize row                     | row_matrix          |   10 |      1.367 |     0.1367 |
| matrix_assign row                     | row_matrix          |   10 |      1.559 |     0.1559 |
| matrix_assign_add row                 | row_matrix          |   10 |     0.8611 |    0.08611 |
| matrix_assign_add_sum row             | row_matrix          |   10 |     0.8673 |    0.08673 |
| vector_assign_matrix_vector_mult row  | row_matrix          |   10 |     0.2518 |    0.02518 |
| matrix_add col                        | col_matrix          |   10 |      9.519 |     0.9519 |
| matrix_multiple_add col               | col_matrix          |   10 |      10.01 |      1.001 |
| matrix_mixed_add_sub col              | col_matrix          |   10 |      11.17 |      1.117 |
| matrix_resize col                     | col_matrix          |   10 |      1.413 |     0.1413 |
| matrix_assign col                     | col_matrix          |   10 |      1.562 |     0.1562 |
| matrix_assign_add col                 | col_matrix          |   10 |     0.8529 |    0.08529 |
| matrix_assign_add_sum col             | col_matrix          |   10 |     0.8602 |    0.08602 |
| matrix_multiply_blocked_row row * row | matrix_mult_blocked |   10 |      9.598 |     0.9598 |
| matrix_multiply_blocked_row row * col | matrix_mult_blocked |   10 |      9.745 |     0.9745 |
| matrix_multiply_blocked_row col * row | matrix_mult_blocked |   10 |      14.55 |      1.455 |
| matrix_multiply_blocked_row col * col | matrix_mult_blocked |   10 |      17.53 |      1.753 |
| matrix_multiply_blocked_col row * row | matrix_mult_blocked |   10 |      18.37 |      1.837 |
| matrix_multiply_blocked_col row * col | matrix_mult_blocked |   10 |      18.09 |      1.809 |
| matrix_multiply_blocked_col col * row | matrix_mult_blocked |   10 |      16.47 |      1.647 |
| matrix_multiply_blocked_col col * col | matrix_mult_blocked |   10 |      16.04 |      1.604 |
| decompose_solve_lu(col): col          | col_algorithms      |   10 |      0.634 |     0.0634 |
| lu_decompose (col): col               | col_algorithms      |   10 |     0.6226 |    0.06226 |
| matrix_add_sub_mixed_storage          | mixed_matrix        |   10 |      2.249 |     0.2249 |
| matrix_assign_storage_mismatch        | mixed_matrix        |   10 |      2.096 |     0.2096 |
| decompose_solve_lu(row): row          | row_algorithms      |   10 |     0.5734 |    0.05734 |
| lu_decompose (row): row               | row_algorithms      |   10 |     0.5686 |    0.05686 |
| vector_assign_matrix_vector_mult col  | cols_matrix         |   10 |     0.9318 |    0.09318 |
+---------------------------------------+---------------------+------+------------+------------+
| total                                 |                     |      |        181 |            |
+---------------------------------------+---------------------+------+------------+------------+

================================================================================
    SUMMARY: performance tests
Performed tests     : 37
Total test result   : 0
Failed tests        : 0
Total execution time: 201.4s
================================================================================
```
