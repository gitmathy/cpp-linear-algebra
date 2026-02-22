# Testing different compiler options for performance

We here only consider tests labeled by `"row_matrix", "vector", "row_algorithms"`.

## Starting point

```
PERF_CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -Ofast -I. -MMD -MP -DPARALLEL
```

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
| decompose_solve_lu_row: row          | row_algorithms |   10 |      1.041 |     0.1041 |
| decompose_solve_lu_row: col          | row_algorithms |   10 |      1.106 |     0.1106 |
| matrix_add row                       | row_matrix     |   10 |      1.106 |     0.1106 |
| matrix_multiple_add row              | row_matrix     |   10 |      1.151 |     0.1151 |
| matrix_mixed_add_sub row             | row_matrix     |   10 |      1.161 |     0.1161 |
| matrix_resize row                    | row_matrix     |   10 |      0.622 |     0.0622 |
| matrix_assign row                    | row_matrix     |   10 |     0.9684 |    0.09684 |
| matrix_assign_add row                | row_matrix     |   10 |     0.8394 |    0.08394 |
| matrix_assign_add_sum row            | row_matrix     |   10 |     0.8654 |    0.08654 |
| vector_assign_matrix_vector_mult row | row_matrix     |   10 |     0.5766 |    0.05766 |
| vector_add                           | vector         |   10 |      1.095 |     0.1095 |
| vector_multiple_add                  | vector         |   10 |      1.149 |     0.1149 |
| vector_mixed_add_sub                 | vector         |   10 |      1.153 |     0.1153 |
| vector_resize                        | vector         |   10 |     0.6192 |    0.06192 |
| vector_assign                        | vector         |   10 |     0.9582 |    0.09582 |
| vector_add_assign                    | vector         |   10 |     0.8418 |    0.08418 |
| vector_sum_add_assign                | vector         |   10 |      1.178 |     0.1178 |
+--------------------------------------+----------------+------+------------+------------+
| total                                |                |      |      16.43 |            |
+--------------------------------------+----------------+------+------------+------------+
```

### First set of optimizations

Compiler:
```
PERF_CXXFLAGS := -Wall -Wextra -pedantic -std=c++20 -O3 -Ofast -ffast-math -march=native -mtune=native -flto -mavx2 -fopt-info-vec-optimized -finline-limit=20000 -fstrict-aliasing -funroll-loops -floop-interchange -I. -MMD -MP -DPARALLEL
```

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
| decompose_solve_lu_row: row          | row_algorithms |   10 |     0.7643 |    0.07643 |
| decompose_solve_lu_row: col          | row_algorithms |   10 |     0.8331 |    0.08331 |
| matrix_add row                       | row_matrix     |   10 |      1.144 |     0.1144 |
| matrix_multiple_add row              | row_matrix     |   10 |      1.162 |     0.1162 |
| matrix_mixed_add_sub row             | row_matrix     |   10 |      1.182 |     0.1182 |
| matrix_resize row                    | row_matrix     |   10 |      0.625 |     0.0625 |
| matrix_assign row                    | row_matrix     |   10 |     0.9198 |    0.09198 |
| matrix_assign_add row                | row_matrix     |   10 |     0.8341 |    0.08341 |
| matrix_assign_add_sum row            | row_matrix     |   10 |     0.8243 |    0.08243 |
| vector_assign_matrix_vector_mult row | row_matrix     |   10 |     0.4271 |    0.04271 |
| vector_add                           | vector         |   10 |      1.089 |     0.1089 |
| vector_multiple_add                  | vector         |   10 |      1.167 |     0.1167 |
| vector_mixed_add_sub                 | vector         |   10 |     0.9862 |    0.09862 |
| vector_resize                        | vector         |   10 |     0.6435 |    0.06435 |
| vector_assign                        | vector         |   10 |     0.9227 |    0.09227 |
| vector_add_assign                    | vector         |   10 |     0.8212 |    0.08212 |
| vector_sum_add_assign                | vector         |   10 |      1.062 |     0.1062 |
+--------------------------------------+----------------+------+------------+------------+
| total                                |                |      |      15.41 |            |
+--------------------------------------+----------------+------+------------+------------+
```
