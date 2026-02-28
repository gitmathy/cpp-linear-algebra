## With block sizes of 64: (matrix size of 1000) (Not parallelized)

```
+-----------------------------------+-------------------------+------+------------+------------+
| test name                         | label                   | runs | total[s]   | avg[s]     |
+-----------------------------------+-------------------------+------+------------+------------+
| matrix_multiply row * row         | matrix_mult_non_blocked |   10 |       20.5 |       2.05 |
| matrix_multiply row * col         | matrix_mult_non_blocked |   10 |      2.597 |     0.2597 |
| matrix_multiply col * row         | matrix_mult_non_blocked |   10 |      172.9 |      17.29 |
| matrix_multiply col * col         | matrix_mult_non_blocked |   10 |      17.84 |      1.784 |
| matrix_multiply_blocked row * row | matrix_mult_blocked     |   10 |      1.437 |     0.1437 |
| matrix_multiply_blocked row * col | matrix_mult_blocked     |   10 |      2.161 |     0.2161 |
| matrix_multiply_blocked col * row | matrix_mult_blocked     |   10 |        1.5 |       0.15 |
| matrix_multiply_blocked col * col | matrix_mult_blocked     |   10 |      4.876 |     0.4876 |
+-----------------------------------+-------------------------+------+------------+------------+
| total                             |                         |      |      223.8 |            |
+-----------------------------------+-------------------------+------+------------+------------+
```

## With block sizes of 63 (matrix size of 1000) (Parallelized with execution policy: par_unseq):

```
+-----------------------------------+---------------------+------+------------+------------+
| test name                         | label               | runs | total[s]   | avg[s]     |
+-----------------------------------+---------------------+------+------------+------------+
| matrix_multiply_blocked row * row | matrix_mult_blocked |   10 |     0.1969 |    0.01969 |
| matrix_multiply_blocked row * col | matrix_mult_blocked |   10 |     0.2093 |    0.02093 |
| matrix_multiply_blocked col * row | matrix_mult_blocked |   10 |     0.2102 |    0.02102 |
| matrix_multiply_blocked col * col | matrix_mult_blocked |   10 |     0.7345 |    0.07345 |
+-----------------------------------+---------------------+------+------------+------------+
| total                             |                     |      |      1.351 |            |
+-----------------------------------+---------------------+------+------------+------------+
```

## Optimized col*col with Stack buffer

```
+-----------------------------------+---------------------+------+------------+------------+
| test name                         | label               | runs | total[s]   | avg[s]     |
+-----------------------------------+---------------------+------+------------+------------+
| matrix_multiply_blocked row * row | matrix_mult_blocked |   10 |     0.2021 |    0.02021 |
| matrix_multiply_blocked row * col | matrix_mult_blocked |   10 |     0.2073 |    0.02073 |
| matrix_multiply_blocked col * row | matrix_mult_blocked |   10 |      0.208 |     0.0208 |
| matrix_multiply_blocked col * col | matrix_mult_blocked |   10 |     0.4716 |    0.04716 |
+-----------------------------------+---------------------+------+------------+------------+
| total                             |                     |      |      1.089 |            |
+-----------------------------------+---------------------+------+------------+------------+
```

## Super optimized

```
+-----------------------------------+---------------------+------+------------+------------+
| test name                         | label               | runs | total[s]   | avg[s]     |
+-----------------------------------+---------------------+------+------------+------------+
| matrix_multiply_blocked row * row | matrix_mult_blocked |   10 |     0.2072 |    0.02072 |
| matrix_multiply_blocked row * col | matrix_mult_blocked |   10 |     0.2017 |    0.02017 |
| matrix_multiply_blocked col * row | matrix_mult_blocked |   10 |     0.2138 |    0.02138 |
| matrix_multiply_blocked col * col | matrix_mult_blocked |   10 |     0.1675 |    0.01675 |
+-----------------------------------+---------------------+------+------------+------------+
| total                             |                     |      |     0.7902 |            |
+-----------------------------------+---------------------+------+------------+------------+
```

## Matrix size of 2000:

```
+-----------------------------------+---------------------+------+------------+------------+
| test name                         | label               | runs | total[s]   | avg[s]     |
+-----------------------------------+---------------------+------+------------+------------+
| matrix_multiply_blocked row * row | matrix_mult_blocked |   10 |       1.59 |      0.159 |
| matrix_multiply_blocked row * col | matrix_mult_blocked |   10 |      1.666 |     0.1666 |
| matrix_multiply_blocked col * row | matrix_mult_blocked |   10 |      1.851 |     0.1851 |
| matrix_multiply_blocked col * col | matrix_mult_blocked |   10 |      1.592 |     0.1592 |
+-----------------------------------+---------------------+------+------------+------------+
| total                             |                     |      |      6.699 |            |
+-----------------------------------+---------------------+------+------------+------------+
```

## Matrix size of 3000:

```
+-----------------------------------+---------------------+------+------------+------------+
| test name                         | label               | runs | total[s]   | avg[s]     |
+-----------------------------------+---------------------+------+------------+------------+
| matrix_multiply_blocked row * row | matrix_mult_blocked |   10 |      5.728 |     0.5728 |
| matrix_multiply_blocked row * col | matrix_mult_blocked |   10 |      5.957 |     0.5957 |
| matrix_multiply_blocked col * row | matrix_mult_blocked |   10 |      6.763 |     0.6763 |
| matrix_multiply_blocked col * col | matrix_mult_blocked |   10 |      4.878 |     0.4878 |
+-----------------------------------+---------------------+------+------------+------------+
| total                             |                     |      |      23.33 |            |
+-----------------------------------+---------------------+------+------------+------------+
```

## Matrix of size 3000 using column wise and row wise outputs:

```
+---------------------------------------+---------------------+------+------------+------------+
| test name                             | label               | runs | total[s]   | avg[s]     |
+---------------------------------------+---------------------+------+------------+------------+
| matrix_multiply_blocked_row row * row | matrix_mult_blocked |   10 |      5.056 |     0.5056 |
| matrix_multiply_blocked_row row * col | matrix_mult_blocked |   10 |      6.127 |     0.6127 |
| matrix_multiply_blocked_row col * row | matrix_mult_blocked |   10 |      6.401 |     0.6401 |
| matrix_multiply_blocked_row col * col | matrix_mult_blocked |   10 |      4.698 |     0.4698 |
| matrix_multiply_blocked_col row * row | matrix_mult_blocked |   10 |      4.501 |     0.4501 |
| matrix_multiply_blocked_col row * col | matrix_mult_blocked |   10 |      6.862 |     0.6862 |
| matrix_multiply_blocked_col col * row | matrix_mult_blocked |   10 |       5.69 |      0.569 |
| matrix_multiply_blocked_col col * col | matrix_mult_blocked |   10 |      6.059 |     0.6059 |
+---------------------------------------+---------------------+------+------------+------------+
| total                                 |                     |      |      45.39 |            |
+---------------------------------------+---------------------+------+------------+------------+
```

## Eigen (size 3000)

```
Computing 10 times multiply operation of matrices (row wise) of size (3000 x 3000) took: 9.57112s, avg: 0.957112
Computing 10 times multiply operation of matrices (column wise) of size (3000 x 3000) took: 8.84635s, avg: 0.884635
```

## Eigen (1000 size):
Computing 10 times multiply operation of matrices of size (1000 x 1000) took: 0.373137s, avg: 0.0373137

