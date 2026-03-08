## 2026-03-08

```
================================================================================
       REPORT: performance tests

   # runs:              10
   default vector size: 100000000
   default matrix rows: 1000
   default matrix cols: 100000000
================================================================================

+----------------------------------+------------+------+------------+------------+
| test name                        | label      | runs | total[s]   | avg[s]     |
+----------------------------------+------------+------+------------+------------+
| lu_decompose                     | algorithms |   10 |     0.2186 |    0.02186 |
| decompose_solve_lu               | algorithms |   10 |     0.2071 |    0.02071 |
| matrix_multiply_blocked          | algorithms |   10 |      5.619 |     0.5619 |
| matrix_add                       | matrix     |   10 |      1.212 |     0.1212 |
| matrix_multiple_add              | matrix     |   10 |      1.112 |     0.1112 |
| matrix_mixed_add_sub             | matrix     |   10 |     0.8551 |    0.08551 |
| matrix_resize                    | matrix     |   10 |     0.6316 |    0.06316 |
| matrix_assign                    | matrix     |   10 |     0.9194 |    0.09194 |
| matrix_assign_add                | matrix     |   10 |     0.8335 |    0.08335 |
| matrix_assign_add_sum            | matrix     |   10 |      1.103 |     0.1103 |
| vector_assign_matrix_vector_mult | matrix     |   10 |      5.582 |     0.5582 |
| vector_add                       | vector     |   10 |      1.137 |     0.1137 |
| vector_multiple_add              | vector     |   10 |      1.117 |     0.1117 |
| vector_mixed_add_sub             | vector     |   10 |     0.8373 |    0.08373 |
| vector_add_static_vector         | vector     |   10 |      1.173 |     0.1173 |
| vector_resize                    | vector     |   10 |     0.6106 |    0.06106 |
| vector_assign                    | vector     |   10 |     0.9187 |    0.09187 |
| vector_add_assign                | vector     |   10 |     0.8178 |    0.08178 |
| vector_sum_add_assign            | vector     |   10 |      1.064 |     0.1064 |
+----------------------------------+------------+------+------------+------------+
| total                            |            |      |      25.97 |            |
+----------------------------------+------------+------+------------+------------+

================================================================================
    SUMMARY: performance tests
Performed tests     : 19
Total test result   : 0
Failed tests        : 0
Total execution time: 40.64s
================================================================================
```
