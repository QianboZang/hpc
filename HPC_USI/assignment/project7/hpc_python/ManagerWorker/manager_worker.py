import time
import sys
import numpy as np
from mpi4py import MPI  # MPI_Init and MPI_Finalize automatically called
import matplotlib.pyplot as plt
from mandelbrot_task import *
import matplotlib as mpl
mpl.use('Agg')

# some parameters
MANAGER = 0  # rank of manager
TAG_TASK = 1  # task message tag
TAG_TASK_DONE = 2  # tasks done message tag
TAG_DONE = 3  # done message tag


def manager(comm, tasks):
    """
    The manager.

    Parameters
    ----------
    comm : mpi4py.MPI communicator
        MPI communicator
    tasks : list of objects with a do_task() method perfroming the task
        List of tasks to accomplish

    Returns
    -------
    done_tasks : list of mandelbrot_patch objects
        List of completed tasks
    TasksDoneByWorker: an integer->integer dictionary
        Tacks which worker did how many tasks.
    """
    size = comm.Get_size()
    done_tasks = []
    to_do = 0
    TasksDoneByWorker = {}
    for des in range(size):
        if not tasks:
            break
        if des == MANAGER:
            continue
        task = tasks.pop()
        comm.send(task, dest=des, tag=TAG_TASK)
        to_do += 1
    while to_do > 0 or tasks:
        status = MPI.Status()
        task = comm.recv(status=status, tag=TAG_TASK_DONE)
        des = status.Get_source()
        done_tasks.append(task)
        to_do -= 1
        if des not in TasksDoneByWorker:
            TasksDoneByWorker[des] = 0
        TasksDoneByWorker[des] += 1
        if tasks:
            task = tasks.pop()
            comm.send(task, dest=des, tag=TAG_TASK)
            to_do += 1
    for des in range(size):
        if des== MANAGER:
            continue
        comm.send(None, dest=des, tag=TAG_DONE)
    return done_tasks, TasksDoneByWorker


def worker_get_task(comm):
    status = MPI.Status()
    task = comm.recv(source=MANAGER, status=status)
    if status.Get_tag() == TAG_DONE:
        return None
    return task


def worker(comm):
    """
    The worker.

    Parameters
    ----------
    comm : mpi4py.MPI communicator
        MPI communicator
    """
    while True: 
        task = worker_get_task(comm)
        if not task:
            break
        task.do_work()
        comm.send(task, dest=MANAGER, tag=TAG_TASK_DONE)
       
        
def readcmdline(rank):
    """
    Read command line arguments

    Parameters
    ----------
    rank : int
        Rank of calling MPI process

    Returns
    -------
    nx : int
        number of gridpoints in x-direction
    ny : int
        number of gridpoints in y-direction
    ntasks : int
        number of tasks
    """
    # report usage
    if len(sys.argv) != 4:
        if rank == MANAGER:
            print("Usage: manager_worker nx ny ntasks")
            print("  nx     number of gridpoints in x-direction")
            print("  ny     number of gridpoints in y-direction")
            print("  ntasks number of tasks")
        sys.exit()

    # read nx, ny, ntasks
    nx = int(sys.argv[1])
    if nx < 1:
        sys.exit("nx must be a positive integer")
    ny = int(sys.argv[2])
    if ny < 1:
        sys.exit("ny must be a positive integer")
    ntasks = int(sys.argv[3])
    if ntasks < 1:
        sys.exit("ntasks must be a positive integer")

    return nx, ny, ntasks


if __name__ == "__main__":
    # get COMMON WORLD communicator, size & rank
    comm = MPI.COMM_WORLD
    size = comm.Get_size()
    my_rank = comm.Get_rank()

    # report on MPI environment
    if my_rank == MANAGER:
        print(f"MPI initialized with {size:5d} processes")        

    if my_rank == MANAGER:
        # read command line arguments
        nx, ny, ntasks = readcmdline(my_rank)

        # start timer
        timespent = - time.perf_counter()
        # Manager gets to define the computation problem.
        x_min = -2.
        x_max = +1.
        y_min = -1.5
        y_max = +1.5
        M = mandelbrot(x_min, x_max, nx, y_min, y_max, ny, ntasks)
        tasks = M.get_tasks()

        done_tasks, TasksDoneByWorker = manager(comm, tasks)

        # Manager gets to compute the final result too.
        m = M.combine_tasks(done_tasks)

        plt.imshow(m.T, cmap="gray", extent=[x_min, x_max, y_min, y_max])
        plt.savefig("mandelbrot.png")
    else:
        worker(comm)
 
    
    if my_rank == MANAGER:
        # stop timer
        timespent += time.perf_counter()
        # inform that done
        print(f"Run took {timespent:f} seconds")
        for i in range(size):
            if i == MANAGER:
                continue
            print(f"Process {i:5d} has done {TasksDoneByWorker[i]:10d} tasks")
        print("Done.")
