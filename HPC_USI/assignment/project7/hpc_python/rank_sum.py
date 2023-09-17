from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

sum_gen = comm.reduce(rank, op=MPI.SUM, root=0)

data = np.array(rank, dtype='i')
sum_buff = np.empty(1, dtype='i')
comm.Reduce([data, MPI.INT], sum_buff, op=MPI.SUM, root=0)

if rank == 0:
    print("sum with generic Python objects:", sum_gen)
    print("sum with communication of buffer-like objects:", sum_buff[0])