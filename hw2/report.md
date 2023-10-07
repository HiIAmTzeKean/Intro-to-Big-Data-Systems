# Report for HW2

Cluster username: bds23-ghcstu08  
Student name: Ng Tze Kean  
Student type: Virutal Exchange student  

## Section 1: implementation

The code is implemented with OpenMP. The code has been modified such that loops that can be parallelized will be exploited for a faster page rank processing. Some considerations include if the variable used will be modified across threads. If so, then reduction is used to aggregate such variables in one atomic operation when all threads has ended.

## time result

The results below has been obtained after averaging the results over 10 runs.

1 thread: 5.643133 s
2 thread: 3.566303 s
3 thread: 3.064738 s
4 thread: 2.299552 s

## schedule variation

Here we will keep the number of threads to 4 and vary the schedule.

static schedule means that iterations blocks are mapped statically to the execution threads in a round-robin fashion. Running the code using static schedule returns the following time.
static runtime with 4 threads: 2.286167 s

dynamic scheduling works on a "first come, first served" basis. Two runs with the same number of threads might (and most likely would) produce completely different "iteration space" -> "threads" mappings. The overhead of assigning the load during run time seems to outweigh the benefits of load balancing. Furthermore, it seems like the load for each 'for' loop computation is well distributed among the threads, which could be why static scheduling could be faster.

(dynamic, 1) run time with 4 threads: 4.039370 s

## performance

Overall we see that as the number of threads increase from 1 to 4, the performance of the algorithm increases. This is because the load from the 'for' loops are substantially heavy and most of the computation time is incurred from the loops. Thus, by parallelizing the loops, we reduce the overall time spent.

## bonus

8 thread: 1.308711 s

Hyperthreading means that if one thread stalls, the cpu will have instructions from another thread to execute. even without an actual stall, if two threads are scheduled that use different execution resources, instructions from both can execute simultaneously on the same core. so if, for example, the code is heavily dependent on main-memory latency (e.g., unpredictable read patterns with no prefetching), hyperthreading might increase performance substantially.
