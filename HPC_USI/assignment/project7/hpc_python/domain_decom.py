from mpi4py import MPI
import numpy as np

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

dims = MPI.Compute_dims(size, [0, 0])

periods = [1, 1]
comm_cart = comm.Create_cart(dims, periods, False)
coords = comm_cart.Get_coords(rank)

west, east = comm_cart.Shift(1, 1)
south, north = comm_cart.Shift(0, 1)

print('#{} has coord {} and neighbours: north->{}, south->{}, east->{}, west->{}'.format(rank, coords, north, south, east, west))

request = comm_cart.isend(rank, north)
rankS_recv = comm_cart.recv(source=south)
request = comm_cart.isend(rank, east)
rankW_recv = comm_cart.recv(source=west)
request = comm_cart.isend(rank, south)
rankN_recv = comm_cart.recv(source=north)
request = comm_cart.isend(rank, west)
rankE_recv = comm_cart.recv(source=east)

if not rankN_recv == north:
    print("error")
    exit(-1)
if not rankS_recv == south:
    print("error")
    exit(-1)
if not rankE_recv == east:
    print("error")
    exit(-1)
if not rankW_recv == west:
    print("error")
    exit(-1)

print(rank, " done correctly")