#include <stdio.h>
#include "mpi.h"

int main(){
    int rank;
    int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int token;

    if(rank != 0){
        MPI_Recv(&token, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%d received token %d from process %d \n", rank, token, rank-1);
    }else{
        token = -1;
    }
    MPI_Send(&token, 1, MPI_INT, (rank+1) % size, 0, MPI_COMM_WORLD);

    if(rank == 0){
        MPI_Recv(&token, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("%d received token %d from process %d \n", rank, token, size-1);
    }


    MPI_Finalize();
    return 0;
}