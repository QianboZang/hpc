/****************************************************************
 *                                                              *
 * This file has been written as a sample solution to an        *
 * exercise in a course given at the CSCS-USI Summer School.    *
 * It is made freely available with the understanding that      *
 * every copy of this file must include this header and that    *
 * CSCS/USI take no responsibility for the use of the enclosed  *
 * teaching material.                                           *
 *                                                              *
 * Purpose: : Parallel matrix-vector multiplication and the     *
 *            and power method                                  *
 *                                                              *
 * Contents: C-Source                                           *
 *                                                              *
 ****************************************************************/



#include <stdio.h>
#include <mpi.h>
#include <math.h>
#include <stdlib.h>
#include "hpc-power.h"
#include "hpc-power.c"

double *generateMatrix(int n, int rows, int my_rank);
double norm(double *x, int rows) ;
void matVec(double *A, int rows, int cols, double *x, double *ans);
void powerMethod(double *A, int rows, int cols, double *x, double *ans);
void printVec(double *x, int n);
void printMat(double *A, int rows, int cols);


int main (int argc, char *argv[])
{
    int my_rank, size;
    int snd_buf, rcv_buf;
    int right, left;
    int sum, i;

    MPI_Status  status;
    MPI_Request request;


    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    /* This subproject is about to write a parallel program to
       multiply a matrix A by a vector x, and to use this routine in
       an implementation of the power method to find the absolute
       value of the largest eigenvalue of the matrix. Your code will
       call routines that we supply to generate matrices, record
       timings, and validate the answer.
    */

    int n = 6400, iter = 1000;
    const int rows = n / size;
    double *A = generateMatrix(n, rows, my_rank);
    double *x = (double *)calloc(n, sizeof(double));
    double *ans = (double *)calloc(n, sizeof(double));
    double start, end;

    if (my_rank == 0) 
        for (i = 0; i < n; i++) 
            x[i] = i + 1;

    MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    start = hpc_timer();
    for (i = 0; i < iter; ++i)
        powerMethod(A, rows, n, x, ans);
    end = hpc_timer();

    double time = end - start;
    double ans_norm =  norm(x, n);
    printf("Execution Time: %f seconds, the norm of the answer: %f\n", time, ans_norm);

    int flag = hpc_verify(x, n, time);
    if (flag) 
        printf("Succeed!\n");
    else 
        printf("Fail!\n");
    
    free(A);
    free(x);
    free(ans);
    MPI_Finalize();
    return 0;
}

double *generateMatrix(int n, int rows, int my_rank) 
{
    int i = 0, j = 0;
    double *A = (double *)calloc(n * rows, sizeof(double));
    int up = my_rank * rows * n;
    int down = up + rows * n;

    for (i = up, j = 0; i < down; ++i, ++j) 
        A[j] = 1; 

    return A;
}


double norm(double *x, int rows) 
{
    int i;
    double result = 0;

    for (i = 0; i < rows; i++) 
        result = result + x[i] * x[i];

    return pow(result, 0.5);
}

void matVec(double *A, int rows, int cols, double *x, double *ans) 
{
    int i, j;
    double *temp = (double *)calloc(rows, sizeof(double));
    
    for (i = 0; i < rows; ++i) 
        for (j = 0; j < cols; ++j) 
            temp[i] = temp[i] + A[i * cols + j] * x[j];

    MPI_Gather(temp, rows, MPI_DOUBLE, ans, rows, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(ans, cols, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    free(temp);
}


void powerMethod(double *A, int rows, int cols, double *x, double *ans) 
{
    int i;
    double x_norm;

    x_norm = norm(x, cols);
    
    for (i = 0; i < cols; ++i) 
        x[i] = x[i] / x_norm;
    
    matVec(A, rows, cols, x, ans);
    for (i = 0; i < cols; i++) 
        x[i] = ans[i];
}


void printVec(double *x, int n) 
{
    int j = 0;
    printf("[");
    for (j = 0; j < n; ++j) 
        printf("%.2lf ", x[j]);
  
    printf("]\n");
}

void printMat(double *A, int rows, int cols) 
{
    printf("[\n");
    for (int i = 0; i < rows; ++i) {
        printf("    ");
        printVec(&A[i * cols], cols);
    }
    printf("]\n");
}
