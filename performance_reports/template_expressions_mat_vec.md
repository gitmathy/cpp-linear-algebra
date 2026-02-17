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

### Execution policy for resize, constructor

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


### Execution policy for copy constructor and assignment

To fill the values while copying, we are using the execution policy `std::execution::par_unseq` by the code:

```cpp
std::copy(std::execution::POLICY, rhs.p_vals, rhs.p_vals + rhs.p_size, p_vals);
```

This is based on the following measurements on my device:

#### Measurements for 10 executions of size 100000000

| vector assign | none [s] | seq [s] | par [s] | unseq [s] | par_unseq [s] |
|---------------|--------- |---------|---------|-----------|---------------|
| c++17         | 2.895    | 2.85    | 0.9225  | 2.747     | 0.9631        |
| c++20         | 2.863    | 2.881   | 0.9742  | 2.715     | 0.9552        |

### Execution policy for assign add

To fill the values with +=, we are using the execution policy `std::execution::par_unseq` by the code:

```cpp
    auto range = std::views::iota(size_type(0), p_size);
    std::for_each(execution::par_unseq, range.begin(), range.end(),
                  [this, &rhs](size_type i) { this->p_vals[i] += rhs.p_vals[i]; });
```

This is based on the following measurements on my device:

#### Measurements for 10 executions of size 100000000

| vector assign add   | plain loop [s] | none [s] | seq [s] | par [s] | unseq [s] | par_unseq [s] |
|---------------------|----------------|----------|---------|---------|-----------|---------------|
| c++20 transform     | 0.8434         | 1.093    | 0.9103  | 0.8611  | 0.8767    | 0.8773        |
| c++20 for_each      |                | 1.382    | 0.901   | 0.8357  | 0.9071    | 0.8328        |

### Execution policy for assign sum

To fill the values with +=, we are using the execution policy `std::execution::par_unseq` by the code:

```cpp
auto range = std::views::iota(size_type(0), p_size);
std::for_each(execution::par_unseq, range.begin(), range.end(),
                [this, &exp](size_type i) { this->p_vals[i] = exp.evaluate(i); });
```

This is based on the following measurements on my device:

#### Measurements for 10 executions of size 100000000

| vector add          | plain loop [s] | none [s] | seq [s] | par [s] | unseq [s] | par_unseq [s] |
|---------------------|----------------|----------|---------|---------|-----------|---------------|
| single sum          | 1.11           | 1.16     | 1.108   | 1.114   | 1.164     | 1.097         |
| multiple sum        | 1.17           | 1.161    | 1.175   | 1.159   | 1.154     | 1.175         |
