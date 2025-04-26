#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

double f(double x) {
    return 4.0 / (1.0 + x * x);
}

int main(int argc, char *argv[]) {
    int rank, size, n = 1000000, i;
    double local_sum = 0.0, global_sum = 0.0;
    double a = 0.0, b = 1.0, h, x;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    h = (b - a) / n; // Step size
    for (i = rank; i < n; i += size) {
        x = a + (i + 0.5) * h;
        local_sum += f(x);
    }
    local_sum *= h;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Calculated value of pi: %.15f\n", global_sum);
    }

    MPI_Finalize();
    return 0;
}