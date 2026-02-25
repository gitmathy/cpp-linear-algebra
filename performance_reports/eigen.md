## Performance of EIGEN

## c = -a- b + a - b

### EIGEN:
```
Computing 10 times sum/add operation of matrices of size (1000 x 100000) took: 0.848234s, avg: 0.0848234
```

### la

```
matrix_mixed_add_sub row             | row_matrix |   10 |      1.026 |     0.1026 |
```


## c = a*b (dimension 1000x1000)

### EIGEN:

```
(1000 x 1000) took: 0.360193s, avg: 0.0360193
```

### la

```
| matrix_multiply rowrow | matrix_mult |   10 |      20.85 |      2.085 |
| matrix_multiply rowcol | matrix_mult |   10 |      2.308 |     0.2308 |
```
