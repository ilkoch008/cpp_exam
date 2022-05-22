## mutex vs atomic_flag

Here you can see simple wrappers for ```std::unordered_map```, which are supposed to be thread-safe. 
In methods, that can modify data, added mutex lock in one case, and 
```test_and_set``` loop in another.

You can see measurement results below:

Mutex with ```RANGE = 100```

| n_writers | time, ms |
|-----------|----------|
| 0         | 0        |
| 1         | 1759     |
| 2         | 2934     |
| 3         | 3968     |
| 4         | 4969     |
| 5         | 6007     |
| 6         | 6839     |
| 7         | 7979     |
| 8         | 9064     |
| 9         | 10092    |
| 10        | 10874    |

```atomic_flag``` with the same ```RANGE```:

| n_writers | time, ms |
|-----------|----------|
| 0         | 0        |
| 1         | 23       |
| 2         | 56       |
| 3         | 86       |
| 4         | 117      |
| 5         | 154      |
| 6         | 169      |
| 7         | 201      |
| 8         | 235      |
| 9         | 258      |
| 10        | 295      |

```RANGE``` is the value that represents max range for key values (from 0 to ```RANGE```). 
This parameter has strong correlation with hash-table size, but in this task it has 
almost no influence on elapsed time (but it would in case of using something like 
```compare_and_swap```, I just don't know how to implement in an appropriate way
something like this for ```unordered_map```). 

```n_writers``` is the value, that represents number of threads, performing 
modifying operations on map. There is also always one thread, that performs ```find```.

Also worth pointing that in this tables total amount of work has a linear dependence on
```n_writers```, because each thread does the same amount of work. So actual plateau should
look like linear increasing.

### Computer Params

|         |                               |
|---------|-------------------------------|
| __CPU__ | Intel Core i5-7300HQ 2.50 GHz |
| __OS__  | Windows 10  21H2 19044.1706   |

