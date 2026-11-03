# Test Cases

## Test Case 1: Standard Reference String

Number of Frames: 3

Reference String:
7 0 1 2 0 3 0 4 2 3 0 3 2

Expected Results:

| Algorithm | Page Faults | Page Hits |
|---|---:|---:|
| FIFO | 10 | 3 |
| LRU | 9 | 4 |
| Optimal | 7 | 6 |

## Test Case 2: Repeated Pages

Number of Frames: 3

Reference String:
1 1 1 1 1

Expected Results:

| Algorithm | Page Faults | Page Hits |
|---|---:|---:|
| FIFO | 1 | 4 |
| LRU | 1 | 4 |
| Optimal | 1 | 4 |

## Test Case 3: One Frame

Number of Frames: 1

Reference String:
1 2 1 2

Expected Results:

| Algorithm | Page Faults | Page Hits |
|---|---:|---:|
| FIFO | 4 | 0 |
| LRU | 4 | 0 |
| Optimal | 4 | 0 |
