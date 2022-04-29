#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include <math.h>

int N = 1024;

int main (int argc, char *argv[]) {

    int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int chunk = N/size;

    double start, stop;
	double timing;
    
    double *A = malloc(N * sizeof *A);

    double *chunk_a = malloc(chunk * sizeof *chunk_a);
    double *chunk_buffer = malloc(chunk * sizeof *chunk_buffer);

    double result;
    double local_sum = 0.0;

    srand (rank + time(NULL));
    for (int i = 0; i < N; i++){
        A[i] = (double) rand()/RAND_MAX;
    }

	start = MPI_Wtime();

    MPI_Scatter(A, chunk, MPI_DOUBLE, chunk_a, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++){
        chunk_buffer[i] = chunk_a[i] * chunk_a[i];
        local_sum += chunk_buffer[i];
    }

    MPI_Reduce(&local_sum, &result, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double sqrt_result = sqrt(result);

    stop = MPI_Wtime();
	timing = stop - start;
	MPI_Finalize();

    if (rank == 0){
        printf("Result: %lf\nTiming: %lf\n", sqrt_result, timing);
    }

    free(A);
    free(chunk_a);
    free(chunk_buffer);
}