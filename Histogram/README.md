# Histogram

The program histogram.py reads from the file in.txt n integers from range [0:100] and then calculates the histogram in a parallel manner. The result is reduced in rank 0 and written to standard output.

# Running the program

```
mpiexec -n [number of processes] python histogram.py [number of items in input]
```