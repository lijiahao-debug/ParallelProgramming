#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <time.h>

int main()
{
    int rank;
    int size;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int number_amount;
    if (rank == 0)
    {
        const int MAX_NUMBERS = 100;
        int numbers[MAX_NUMBERS];
        srand(time(NULL));
        number_amount = (rand() / (float)RAND_MAX) * MAX_NUMBERS;

        MPI_Send(numbers, number_amount, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("process %d send %d numbers to 1\n", rank, number_amount);
    }
    else
    {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &number_amount);

        int * number_buffer = (int*)malloc(sizeof(int) * number_amount);
        MPI_Recv(number_buffer, number_amount, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("process %d dynamically received %d numbers from 0.\n", 
            rank, number_amount);
        free(number_buffer);
    }

    MPI_Finalize();
    return 0;
}
