# PageFaultSimulation-Fall2021
---
## Description
<p> 
Given a string that represents a stream of virtual addresses, this program finds the number of page faults that would occur if the stream was fed to a page table using the FIFO, LRU, and optimal page replacement algorithms.

---
## Features
- Get the number of page faults from using a FIFO page replacement algorithm
- Get the number of page faults from using a LRU page replacement algorithm
- Get the number of page faults from using an optimal page replacement algorithm
---
## Usage
#### Sample Output:
```
Using a string that represents a stream of 200 virtual addresses entering a page table that can store 1 through 10 entries
------
table size: 1
fifo page faults: 196
lru page faults: 196
opt page faults: 196
------
table size: 2
fifo page faults: 190
lru page faults: 190
opt page faults: 172
------
table size: 3
fifo page faults: 186
lru page faults: 186
opt page faults: 159
------
table size: 4
fifo page faults: 184
lru page faults: 185
opt page faults: 146
------
table size: 5
fifo page faults: 179
lru page faults: 177
opt page faults: 137
------
table size: 6
fifo page faults: 176
lru page faults: 173
opt page faults: 129
------
table size: 7
fifo page faults: 174
lru page faults: 172
opt page faults: 122
------
table size: 8
fifo page faults: 171
lru page faults: 170
opt page faults: 116
------
table size: 9
fifo page faults: 164
lru page faults: 165
opt page faults: 111
------
table size: 10
fifo page faults: 157
lru page faults: 160
opt page faults: 106
```
---
## Authors
Collan Parker
