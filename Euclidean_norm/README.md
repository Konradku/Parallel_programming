# Euclidean norm

Parallel implementation of computing an euclidean norm of a vector, written in Cusing MPI (Message Passing Interface) paradigm. The result is reduced in rank 0 and written to standard output.

# Running the program

```
mpirun -n [number of processes] euclidean_norm.c
```