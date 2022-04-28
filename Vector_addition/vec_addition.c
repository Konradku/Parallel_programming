#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int N = 1048576;

int main (int argc, char *argv[]) {

    int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int chunk = N/size;

    double start, stop;
	double timing;
    
    double *A = malloc(N * sizeof *A);
    double *B = malloc(N * sizeof *B);
    double *C = malloc(N * sizeof *C);

    double *chunk_a = malloc(chunk * sizeof *chunk_a);
    double *chunk_b = malloc(chunk * sizeof *chunk_b);
    double *chunk_c = malloc(chunk * sizeof *chunk_c); 

    srand (time(NULL));
    for (int i = 0; i < N; i++){
        B[i] = (double) rand()/RAND_MAX;
        C[i] = (double) rand()/RAND_MAX;
    }


	start = MPI_Wtime();

    MPI_Scatter(B, chunk, MPI_DOUBLE, chunk_b, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(C, chunk, MPI_DOUBLE, chunk_c, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < chunk; i++){
        chunk_a[i] = chunk_b[i] + chunk_c[i];
    }

    MPI_Gather(chunk_a, chunk, MPI_DOUBLE, A, chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    stop = MPI_Wtime();
	timing = stop - start;
	MPI_Finalize();

    if (rank == 0){
        printf("A[0]:%lf, B[0]:%lf C[0]:%lf\nA[N-1]:%lf, B[N-1]:%lf C[N-1]:%lf\nTiming: %lf\n", A[0], B[0], C[0], A[N-1], B[N-1], C[N-1], timing);
    }

    free(A);
    free(B);
    free(C);
    free(chunk_a);
    free(chunk_b);
    free(chunk_c);    
}
