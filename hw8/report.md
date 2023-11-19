# Report for HW8

Cluster username: bds23-ghcstu08  
Student name: Ng Tze Kean  
Student type: Virutal Exchange student  

## Part 1

### Running code

```shell
# compiling code
g++ -o edge_cut edge_cut.cpp
g++ -o vertex_cut vertex_cut.cpp
# Examples of usage
./edge_cut /data/hw8_data/small-5.graph 2
./vertex_cut /data/hw8_data/small-5.graph 2
```

### Output

```shell
# Running edge_cut on small_graph
# ------ 2 partition
Partition 0
1
3
2
2
Partition 1
4
5
2
8
# ------ 3 partition
Partition 0
1
2
1
1
Partition 1
3
5
2
8
Partition 2
1
2
1
1
# ------ 4 partition
Partition 0
0
0
0
0
Partition 1
2
3
2
2
Partition 2
1
3
2
2
Partition 3
2
5
4
6
# 8
Partition 0
0
0
0
0
Partition 1
2
3
2
2
Partition 2
0
0
0
0
Partition 3
1
3
2
2
Partition 4
0
0
0
0
Partition 5
0
0
0
0
Partition 6
1
3
2
2
Partition 7
1
5
4
4
```

### Edge cut visual

<img src="./Edge cut.png" alt="edge cut diagram"/>

### Vertex cut visual

Using a random edge allocation approach, the follow is a possible output. Note that the master vertex is also decided randomly.

<img src="./Vertex cut.png" alt="vertex cut diagram"/>

## Analysis

The choice of the number of partitions in a graph partitioning algorithm can significantly impact the quality of the partitioning and the performance of subsequent distributed computations. Both edge cut and vertex cut methods are influenced by the number of partitions, and their behavior can vary based on the characteristics of the graph and the specific partitioning algorithm used. Here's how different numbers of partitions can affect the output:

### Edge Cut Method:

1. **Increasing Number of Partitions:**
   - **Pros:** With more partitions, you may achieve better load balance as the workload is distributed among more processing units. This can be beneficial for parallelism.
   - **Pros:** Completely parallel and easy to distribute.
   - **Cons:** However, as the number of partitions increases, the edge cut may also increase. More partitions mean more potential edges crossing partition boundaries, leading to higher communication overhead.

2. **Decreasing Number of Partitions:**
   - **Pros:** Fewer partitions can lead to reduced communication overhead, as fewer edges span partition boundaries.
   - **Cons:** Load imbalance might occur, especially if the graph structure is not evenly distributed.

### Vertex Cut Method:

1. **Increasing Number of Partitions:**
   - **Pros:** Similar to the edge cut method, increasing the number of partitions can improve load balance by distributing vertices more evenly.
   - **Cons:** The number of vertices crossing partitions might also increase, leading to higher communication costs.

2. **Decreasing Number of Partitions:**
   - **Pros:** Reducing the number of partitions can minimize communication costs, especially if the graph has a relatively uniform structure.
   - **Cons:** The decrease in partition might 
