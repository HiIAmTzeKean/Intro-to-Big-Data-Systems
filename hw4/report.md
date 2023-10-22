# Report for HW4

Cluster username: bds23-ghcstu08  
Student name: Ng Tze Kean  
Student type: Virutal Exchange student  

## Part 1

### Question 1

1. **Initialization**: When the GFS master node starts up or is rebooted, it begins by initializing its data structures and internal state. It loads the metadata it has persisted (e.g., the file and chunk namespaces) into memory.

2. **Scanning Chunk Servers**: The master initiates a scan of all the available chunk servers in the GFS cluster. During this scanning process, it contacts each chunk server to collect information about the chunks that they are responsible for.

3. **Chunkserver Heartbeats**: Chunk servers periodically send heartbeats to the master to report their status. These heartbeats include information about the chunks they are hosting, including the chunk's unique ID and the version of the chunk. The master uses this information to update its knowledge of chunk locations.

4. **Recovery and Re-replication**: During the scan, the master may also identify chunks that are under-replicated or have missing replicas due to previous chunk server failures. In such cases, the master coordinates the recovery of missing replicas by instructing other chunk servers to create new replicas.

5. **Updating the Chunk Map**: As the master collects data during the scanning process, it updates its internal chunk map, which keeps track of which chunks are stored on which chunk servers. The master maintains this map in memory for efficient access.

6. **Client Queries**: When a client wants to read or write data, it contacts the master to obtain the current locations of the required chunks. The master provides this information based on its in-memory chunk map, which reflects the latest status of chunk locations in the cluster.

### Question 2
The approach of having the master node dynamically obtain the locations of each chunk at startup in the Google File System (GFS) offers several benefits compared to persisting this information on the master node:

1. **Dynamic Adaptation**: GFS is designed to handle a large number of chunk servers and massive amounts of data. By dynamically obtaining chunk locations at startup, the system can adapt to changes in the cluster configuration. If a chunk server has failed or new chunk servers have been added since the last startup, the dynamic approach ensures that the master has an up-to-date view of the cluster's status. This adaptability is crucial for handling large-scale distributed systems with changing hardware conditions.

2. **Simplicity and Scalability**: Persisting the locations of each chunk on the master would require significant storage capacity and potentially slow down the master's startup and maintenance processes. By not persisting this information, the master's data structures remain relatively lightweight and efficient, allowing it to scale easily and perform its essential functions effectively.

3. **Reduced Overhead**: Persisting chunk locations would create overhead on the master node's disk I/O and storage capacity, as it would need to constantly update this information due to dynamic changes in the cluster. By obtaining the chunk locations dynamically, the master can avoid unnecessary I/O and storage requirements.

4. **Consistency**: In a dynamic approach, the master can be more certain that the chunk location information is consistent with the current state of the chunk servers. If the locations were persisted and not kept in sync, there could be discrepancies between the persisted information and the actual state of the cluster, leading to potential data inconsistencies.

5. **Fault Tolerance**: If a master node fails and needs to be replaced or restarted, obtaining the chunk locations dynamically ensures that the system can quickly recover without relying on potentially outdated persisted information.

## Part 2

Assume in a cluster of GFS of 1000 servers. Each server has 10 disks with 10TB storage capacity and 100MB/s I/O bandwidth for each disk. The ethernet that connects servers has bandwidth of 1Gbps.

### Question 1

What is the minimum time required to recovery a node failure (i.e. distribute its replica to other survived server nodes)?

The amount of data data transfer needed for recovery is twice the capacity of the lost DataNode as each replica must be read once from a source disk and written once to the target disk. I assume that the node that fails has full disk capacity used, and hence all 10TB must be copied over.

$$
\begin{align*}
&\text{Data transfer during recovery for a disk}\\
&= 2 ⋅ (Node Capacity)\\
&= 2 \cdot 10 disk \cdot 10 TB\\
&= 200 TB\\
&= 204800 GB
\end{align*}
$$

The re-replication rate is the limited by the available aggregate IO bandwidth in the cluster:

$$
\begin{align*}
&\text{Cluster aggregate IO bandwidth}\\
&= (Disk IO bandwidth) \cdot (Number of disks)\\
&= (100 ⋅ 1000 nodes ⋅ 10disk) MB/s\\
&= 1000,000 MB/s\\
&> 1Gbps
\end{align*}
$$
Hence, we will take the bandwidth to be the upper limit of 1Gbps.

$$
\begin{align*}
&\text{Minimum Recovery Time}\\
&= (Data transfer during recovery for a disk) / (Cluster aggregate IO bandwidth)\\
&= 204800 \div 0.125GB/s\\
&= 455hours
\end{align*}
$$

### Question 2

For quality of service, usually the recovery traffic is throttled. If the bandwidth used for recovery is 100Mbps per machine, what is the roughly time required to recover a failure node?

A bandwidth of 100Mbps = 100 div (8*1024) GB/s

Using back the equation from Q1
$$
\begin{align*}
&\text{Minimum Recovery Time}\\
&= \frac{(\text{Data transfer during recovery for a disk})}{(Cluster aggregate IO bandwidth)}\\
&= 204800 \div \frac{100}{8*1024}\\
&= 4660hours
\end{align*}
$$

### Question 3

$$
\begin{align*}
\text{For a single node,}\\
MTBF &= \frac{uptime}{failures}\\
10000 &= \frac{365*24}{failures}\\
failures &= 0.876
\end{align*}
$$

Thus, it is expected that a node would fail approximately 0.876 times a year.

### Question 4

As the time for recovery is substantial, there must be sufficient replicas to ensure that the system does not go down.
