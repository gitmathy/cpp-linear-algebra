# Performance report

* With template expressions for matrix and vector

```
----------------------------------------
    REPORT: performance tests

# runs:      10
vector size: 100000000
matrix rows: 1000
matrix cols: 100000
----------------------------------------
* [matrix_resize]               : # 10: total 2.746s, average 0.2746s
* [matrix_assign_add]           : # 10: total 0.8498s, average 0.08498s
* [matrix_add]                  : # 10: total 1.222s, average 0.1222s
* [matrix_multiple_add]         : # 10: total 1.185s, average 0.1185s
* [matrix_mixed_add_sub]        : # 10: total 1.23s, average 0.123s
* [vector_resize]               : # 10: total 2.723s, average 0.2723s
* [vector_assign_add]           : # 10: total 0.8649s, average 0.08649s
* [vector_add]                  : # 10: total 1.139s, average 0.1139s
* [vector_multiple_add]         : # 10: total 1.12s, average 0.112s
* [vector_mixed_add_sub]        : # 10: total 1.194s, average 0.1194s
----------------------------------------
```

## Improvements:

### Execution policy for resize, constructor, copy constructor

To fill the values with defaults, we are using the execution policy `std::execution::par_unseq` by the code:

```cpp
std::fill(std::execution::POLICY, p_vals, p_vals + n, val);
```

This is based on the following measurements on my device:

#### Measurements for 10 executions of size 100000000

| vector resize | none [s] | seq [s] | par [s] | unseq [s] | par_unseq [s] |
|---------------|--------- |---------|---------|-----------|---------------|
| c++17         | 2.505    | 2.652   | 0.6412  | 2.644     | 0.6668        |
| c++20         | 2.515    | 2.645   | 0.715   | 2.512     | 0.65          |


