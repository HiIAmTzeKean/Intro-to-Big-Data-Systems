# Report for HW3

Cluster username: bds23-ghcstu08  
Student name: Ng Tze Kean  
Student type: Virutal Exchange student  

## Detailed description of your implementation

The idea was to use the since the binary tree reduction which only works when N is a power of two. Since the array sizes are given in powers of 2, the reduction through using send and recv operations (using only point-to-point communications).

## Time result

### NP=2

65536 int use_time : 2692 us [MPI_Reduce]  
65536 int use_time : 6712 us [YOUR_Reduce]  
CORRECT !  
1048576 int use_time : 23440 us [MPI_Reduce]  
1048576 int use_time : 26360 us [YOUR_Reduce]  
CORRECT !  
16777216 int use_time : 399673 us [MPI_Reduce]  
16777216 int use_time : 338232 us [YOUR_Reduce]  
CORRECT !  
268435456 int use_time : 6758424 us [MPI_Reduce]  
268435456 int use_time : 4017002 us [YOUR_Reduce]  
CORRECT !  

### NP=4

65536 int use_time : 9428 us [MPI_Reduce]  
65536 int use_time : 23439 us [YOUR_Reduce]  
CORRECT !  
1048576 int use_time : 86322 us [MPI_Reduce]  
1048576 int use_time : 107925 us [YOUR_Reduce]  
CORRECT !  
16777216 int use_time : 839317 us [MPI_Reduce]  
16777216 int use_time : 479555 us [YOUR_Reduce]  
CORRECT !  
268435456 int use_time : 5146443 us [MPI_Reduce]  
268435456 int use_time : 5471731 us [YOUR_Reduce]  
CORRECT !  

### NP=8

65536 int use_time : 21125 us [MPI_Reduce]  
65536 int use_time : 29338 us [YOUR_Reduce]  
CORRECT !  
1048576 int use_time : 101996 us [MPI_Reduce]  
1048576 int use_time : 148918 us [YOUR_Reduce]  
CORRECT !  
16777216 int use_time : 980657 us [MPI_Reduce]  
16777216 int use_time : 616196 us [YOUR_Reduce]  
CORRECT !  
268435456 int use_time : 5925155 us [MPI_Reduce]  
268435456 int use_time : 6840311 us [YOUR_Reduce]  
CORRECT !  
