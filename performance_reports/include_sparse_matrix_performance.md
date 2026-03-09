```
================================================================================
       REPORT: performance tests

   # runs:                    10
   default vector size:       100000000
   default matrix rows:       1000
   default matrix cols:       100000000
   default sparse matrix dim: 100000
   default sparse matrix nnz: 1220862
================================================================================

+----------------------------------+---------------+------+------------+------------+
| test name                        | label         | runs | total[s]   | avg[s]     |
+----------------------------------+---------------+------+------------+------------+
| lu_decompose                     | algorithms    |   10 |     0.2211 |    0.02211 |
| decompose_solve_lu               | algorithms    |   10 |     0.2225 |    0.02225 |
| matrix_multiply_blocked          | algorithms    |   10 |      5.747 |     0.5747 |
| sparse_matrix_build              | sparse_matrix |   10 |     0.3024 |    0.03024 |
| sparse_matrix_mult               | sparse_matrix |   10 |      2e-07 |      2e-08 |
| matrix_add                       | matrix        |   10 |      2.281 |     0.2281 |
| matrix_multiple_add              | matrix        |   10 |      2.255 |     0.2255 |
| matrix_mixed_add_sub             | matrix        |   10 |      1.687 |     0.1687 |
| matrix_resize                    | matrix        |   10 |      1.266 |     0.1266 |
| matrix_assign                    | matrix        |   10 |      1.914 |     0.1914 |
| matrix_assign_add                | matrix        |   10 |      1.674 |     0.1674 |
| matrix_assign_add_sum            | matrix        |   10 |      2.251 |     0.2251 |
| vector_assign_matrix_vector_mult | matrix        |   10 |      11.23 |      1.123 |
| vector_add                       | vector        |   10 |       1.24 |      0.124 |
| vector_multiple_add              | vector        |   10 |      1.225 |     0.1225 |
| vector_mixed_add_sub             | vector        |   10 |      0.888 |     0.0888 |
| vector_add_static_vector         | vector        |   10 |      1.196 |     0.1196 |
| vector_resize                    | vector        |   10 |     0.6602 |    0.06602 |
| vector_assign                    | vector        |   10 |     0.9996 |    0.09996 |
| vector_add_assign                | vector        |   10 |     0.8565 |    0.08565 |
| vector_sum_add_assign            | vector        |   10 |      1.102 |     0.1102 |
+----------------------------------+---------------+------+------------+------------+
| total                            |               |      |      39.22 |            |
+----------------------------------+---------------+------+------------+------------+

================================================================================
    SUMMARY: performance tests
Performed tests     : 21
Total test result   : 0
Failed tests        : 0
Total execution time: 62.37s
================================================================================
```
