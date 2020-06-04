#include <stdio.h>
#include "mpi.h"

int main(int argc, char *argv[])
{
    int rank, size;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // char name[100];
    // int len;
    // MPI_Get_processor_name(
    //     name,
    //     &len);
    // printf("%s %d \n", name, len);
    printf("Hello, world, I am %d of %d.\n",
           rank, size);

    MPI_Finalize();

    return 0;
}
