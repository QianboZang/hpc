/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School.    *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: Parallel maximum using a ping-pong                      *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/


#include <stdio.h>
#include <mpi.h>


int main (int argc, char *argv[])
{
    int my_rank, size;
    int snd_buf, rcv_buf;
    int right, left;
    int max, i;

    MPI_Status  status;
    MPI_Request request;


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);


    right = (my_rank + 1) % size;/* get rank of neighbor to your right */ 
    /* 0->1, 1->2, 2->3, 3->0*/
    left  = (my_rank + size - 1) % size;/* get rank of neighbor to your left */

    /* Implement ring maximum code
    * do not use if (rank == 0) .. else ..
    * every rank sends initialy its rank number to a neighbor, and then sends what
    * it receives from that neighbor, this is done n times with n = number of processes
    * all ranks will obtain the max.
    */
    max = 0;
    snd_buf = 3 * my_rank % (2 * size);
    MPI_Send(&snd_buf, 1, MPI_INT, right, 0, MPI_COMM_WORLD);

    for (i = 0; i < size; ++i)
    {
        MPI_Recv(&rcv_buf, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);
        if (max < rcv_buf)
            max = rcv_buf;
        MPI_Send(&max, 1, MPI_INT, right, 0, MPI_COMM_WORLD);
    }
    MPI_Recv(&max, 1, MPI_INT, left, 0, MPI_COMM_WORLD, &status);

    // printf ("Process %i:\tRight = %i\n", my_rank, right);
    // printf ("Process %i:\tLeft = %i\n", my_rank, left);
    printf ("Process %i:\tMax = %i\n", my_rank, max);

    MPI_Finalize();
    return 0;
}
