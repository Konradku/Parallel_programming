import sys
from mpi4py import MPI

N = int(sys.argv[1])

with open('in.txt', 'r') as file:
    f = file.read()
    strings = f.split()[0:N]
    data = list(map(int, strings))

local_b = [0 for _ in range(101)]

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

chunk = int(len(data)/size)
sendbuf = None

start = MPI.Wtime()

if rank == 0:
	sendbuf = [[data[i*chunk+j] for j in range(chunk)] for i in range(size)]

comm.Barrier()

received = comm.scatter(sendbuf, 0)

for integer in received:
	local_b[integer] += 1

comm.Barrier()
# default root in reduce is 0
result = comm.reduce(local_b, lambda x, y: [x[i] + y[i] for i in range(101)])

end = MPI.Wtime()
timing = end - start

if rank == 0:
	print(f"Timing {timing}, histogram = {result}")