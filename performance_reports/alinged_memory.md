# Before aligning memory

```
================================================================================
       REPORT: performance tests

   # runs:              10
   default vector size: 100000000
   default matrix rows: 1000
   default matrix cols: 100000000
================================================================================

+--------------------------------------+----------------+------+------------+------------+
| test name                            | label          | runs | total[s]   | avg[s]     |
+--------------------------------------+----------------+------+------------+------------+
| matrix_multiply rowrow               | matrix_mult    |   10 |   0.003077 |  0.0003077 |
| matrix_multiply rowcol               | matrix_mult    |   10 |   0.001324 |  0.0001324 |
| decompose_solve_lu_col: row          | col_algorithms |   10 |      10.78 |      1.078 |
| decompose_solve_lu_col: col          | col_algorithms |   10 |      11.66 |      1.166 |
| decompose_solve_lu_row: row          | row_algorithms |   10 |     0.8893 |    0.08893 |
| decompose_solve_lu_row: col          | row_algorithms |   10 |     0.8996 |    0.08996 |
| matrix_add_sub_mixed_storage         | mixed_matrix   |   10 |       12.9 |       1.29 |
| matrix_assign_storage_mismatch       | mixed_matrix   |   10 |      15.76 |      1.576 |
| vector_assign_matrix_vector_mult col | cols_matrix    |   10 |      10.22 |      1.022 |
| matrix_add col                       | col_matrix     |   10 |      46.21 |      4.621 |
| matrix_multiple_add col              | col_matrix     |   10 |      44.83 |      4.483 |
| matrix_mixed_add_sub col             | col_matrix     |   10 |      52.47 |      5.247 |
| matrix_resize col                    | col_matrix     |   10 |     0.6943 |    0.06943 |
| matrix_assign col                    | col_matrix     |   10 |     0.9829 |    0.09829 |
| matrix_assign_add col                | col_matrix     |   10 |     0.9446 |    0.09446 |
| matrix_assign_add_sum col            | col_matrix     |   10 |      0.944 |     0.0944 |
| matrix_add row                       | row_matrix     |   10 |      3.027 |     0.3027 |
| matrix_multiple_add row              | row_matrix     |   10 |      1.239 |     0.1239 |
| matrix_mixed_add_sub row             | row_matrix     |   10 |      1.284 |     0.1284 |
| matrix_resize row                    | row_matrix     |   10 |     0.7457 |    0.07457 |
| matrix_assign row                    | row_matrix     |   10 |      1.141 |     0.1141 |
| matrix_assign_add row                | row_matrix     |   10 |     0.8707 |    0.08707 |
| matrix_assign_add_sum row            | row_matrix     |   10 |     0.9076 |    0.09076 |
| vector_assign_matrix_vector_mult row | row_matrix     |   10 |     0.4488 |    0.04488 |
| vector_add                           | vector         |   10 |      1.238 |     0.1238 |
| vector_multiple_add                  | vector         |   10 |       1.33 |      0.133 |
| vector_mixed_add_sub                 | vector         |   10 |      1.238 |     0.1238 |
| vector_resize                        | vector         |   10 |      0.787 |     0.0787 |
| vector_assign                        | vector         |   10 |     0.9991 |    0.09991 |
| vector_add_assign                    | vector         |   10 |     0.9574 |    0.09574 |
| vector_sum_add_assign                | vector         |   10 |      1.329 |     0.1329 |
+--------------------------------------+----------------+------+------------+------------+
| total                                |                |      |      227.7 |            |
+--------------------------------------+----------------+------+------------+------------+

================================================================================
    SUMMARY: performance tests
Performed tests     : 31
Total test result   : 0
Failed tests        : 0
Total execution time: 262.1s
================================================================================
```

# After aligning memory

================================================================================
       REPORT: performance tests

   # runs:              10
   default vector size: 100000000
   default matrix rows: 1000
   default matrix cols: 100000000
================================================================================

+--------------------------------------+----------------+------+------------+------------+
| test name                            | label          | runs | total[s]   | avg[s]     |
+--------------------------------------+----------------+------+------------+------------+
| matrix_multiply rowrow               | matrix_mult    |   10 |   0.003316 |  0.0003316 |
| matrix_multiply rowcol               | matrix_mult    |   10 |    0.00135 |   0.000135 |
| decompose_solve_lu_col: row          | col_algorithms |   10 |      11.38 |      1.138 |
| decompose_solve_lu_col: col          | col_algorithms |   10 |      11.32 |      1.132 |
| decompose_solve_lu_row: row          | row_algorithms |   10 |     0.8503 |    0.08503 |
| decompose_solve_lu_row: col          | row_algorithms |   10 |      0.814 |     0.0814 |
| matrix_add_sub_mixed_storage         | mixed_matrix   |   10 |      9.774 |     0.9774 |
| matrix_assign_storage_mismatch       | mixed_matrix   |   10 |      12.91 |      1.291 |
| vector_assign_matrix_vector_mult col | cols_matrix    |   10 |      8.922 |     0.8922 |
| matrix_add col                       | col_matrix     |   10 |       37.7 |       3.77 |
| matrix_multiple_add col              | col_matrix     |   10 |      36.45 |      3.645 |
| matrix_mixed_add_sub col             | col_matrix     |   10 |      37.38 |      3.738 |
| matrix_resize col                    | col_matrix     |   10 |     0.6353 |    0.06353 |
| matrix_assign col                    | col_matrix     |   10 |     0.9512 |    0.09512 |
| matrix_assign_add col                | col_matrix     |   10 |     0.9931 |    0.09931 |
| matrix_assign_add_sum col            | col_matrix     |   10 |     0.9403 |    0.09403 |
| matrix_add row                       | row_matrix     |   10 |      1.395 |     0.1395 |
| matrix_multiple_add row              | row_matrix     |   10 |      1.878 |     0.1878 |
| matrix_mixed_add_sub row             | row_matrix     |   10 |      1.301 |     0.1301 |
| matrix_resize row                    | row_matrix     |   10 |     0.6915 |    0.06915 |
| matrix_assign row                    | row_matrix     |   10 |     0.9524 |    0.09524 |
| matrix_assign_add row                | row_matrix     |   10 |      1.018 |     0.1018 |
| matrix_assign_add_sum row            | row_matrix     |   10 |       1.06 |      0.106 |
| vector_assign_matrix_vector_mult row | row_matrix     |   10 |     0.4736 |    0.04736 |
| vector_add                           | vector         |   10 |      2.123 |     0.2123 |
| vector_multiple_add                  | vector         |   10 |      1.576 |     0.1576 |
| vector_mixed_add_sub                 | vector         |   10 |      1.926 |     0.1926 |
| vector_resize                        | vector         |   10 |     0.7938 |    0.07938 |
| vector_assign                        | vector         |   10 |      1.131 |     0.1131 |
| vector_add_assign                    | vector         |   10 |      1.132 |     0.1132 |
| vector_sum_add_assign                | vector         |   10 |      1.353 |     0.1353 |
+--------------------------------------+----------------+------+------------+------------+
| total                                |                |      |      189.8 |            |
+--------------------------------------+----------------+------+------------+------------+
