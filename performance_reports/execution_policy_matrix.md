## Before execution policy for matrix:

```
----------------------------------------
    REPORT: performance tests

# runs:      10
vector size: 100000000
matrix rows: 1000
matrix cols: 100000
----------------------------------------
* [matrix_resize]               : # 10: total 2.775s, average 0.2775s
* [matrix_assign]               : # 10: total 3.037s, average 0.3037s
* [matrix_assign_storage_missmatch]: # 10: total 15.74s, average 1.574s
* [matrix_assign_add]           : # 10: total 0.8298s, average 0.08298s
* [matrix_assign_add_sum]       : # 10: total 0.8343s, average 0.08343s
* [matrix_add]                  : # 10: total 1.138s, average 0.1138s
* [matrix_multiple_add]         : # 10: total 1.311s, average 0.1311s
* [matrix_mixed_add_sub]        : # 10: total 1.164s, average 0.1164s
----------------------------------------
```

## After execution policy for matrix:

```
----------------------------------------
    REPORT: performance tests

# runs:      10
vector size: 100000000
matrix rows: 1000
matrix cols: 100000
----------------------------------------
* [matrix_resize]               : # 10: total 0.7258s, average 0.07258s
* [matrix_assign]               : # 10: total 0.9301s, average 0.09301s
* [matrix_assign_storage_missmatch]: # 10: total 13.42s, average 1.342s
* [matrix_assign_add]           : # 10: total 0.8692s, average 0.08692s
* [matrix_assign_add_sum]       : # 10: total 1.02s, average 0.102s
* [matrix_add]                  : # 10: total 1.403s, average 0.1403s
* [matrix_multiple_add]         : # 10: total 1.167s, average 0.1167s
* [matrix_mixed_add_sub]        : # 10: total 1.189s, average 0.1189s
```
