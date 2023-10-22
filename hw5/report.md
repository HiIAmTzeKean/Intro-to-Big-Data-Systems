# Report for HW5

Cluster username: bds23-ghcstu08  
Student name: Ng Tze Kean  
Student type: Virutal Exchange student  

## Part 1

### Q1

The result of mapping are shuffled and sent to reducers, which could cost a lot of network traffic. Propose an approach to address this issue.

### Response

- Combiners: Combiners are mini-reducers that can be used to perform a local aggregation of data on each mapper node before it's sent to reducers. By reducing the data size before shuffling, you can significantly reduce the amount of data transferred over the network. This is especially effective when there is a lot of redundancy in the intermediate key-value pairs produced by the mappers.
- Partitioning and Clustering: Instead of relying on the default partitioning strategy, consider designing a custom partitioner that groups related data together. This can minimize the amount of data that needs to be shuffled across the network. For example, if you're processing geospatial data, you can partition data based on geographic regions to reduce inter-region data shuffling.
- Data Compression: Use data compression techniques to reduce the size of the data being transferred. Tools like Snappy, Gzip, or BZip2 can be employed to compress intermediate data before sending it to the reducers. This can significantly reduce the network traffic, but it comes at the cost of additional CPU usage for compression and decompression.
- Data Filtering: Filter and pre-process the data on the mapper side to reduce the amount of data that is sent to the reducers. Remove unnecessary or redundant data early in the mapping phase to reduce the overall data volume.
- Data Skew Handling: Identify and handle data skew, where certain keys have a disproportionate amount of data. You can implement specialized strategies, like skewed key optimization or using secondary reducers, to distribute the load more evenly among reducers.
- Optimize Input and Output Formats: Choose appropriate input and output formats that minimize data serialization and deserialization overhead. Optimized file formats like SequenceFile or Avro can reduce the size of data on disk and during network transfer.
- Use Distributed Caching: If certain data is used by multiple reducers, you can use distributed caching to make that data available on the nodes where the reducers are running. This reduces the need to transfer the same data over the network multiple times.

### Q2
If a mapper or reducer task is too slow, which would make the whole map-reduce task very slow. Propose an approach to address this issue.

### Response

- Combiners: Combiners are mini-reducers that can be used to perform a local aggregation of data on each mapper node before it's sent to reducers. By reducing the data size before shuffling, you can significantly reduce the amount of data transferred over the network. This is especially effective when there is a lot of redundancy in the intermediate key-value pairs produced by the mappers.
- Partitioning and Clustering: Instead of relying on the default partitioning strategy, consider designing a custom partitioner that groups related data together. This can minimize the amount of data that needs to be shuffled across the network. For example, if you're processing geospatial data, you can partition data based on geographic regions to reduce inter-region data shuffling.
- Data Compression: Use data compression techniques to reduce the size of the data being transferred. Tools like Snappy, Gzip, or BZip2 can be employed to compress intermediate data before sending it to the reducers. This can significantly reduce the network traffic, but it comes at the cost of additional CPU usage for compression and decompression.
- Data Filtering: Filter and pre-process the data on the mapper side to reduce the amount of data that is sent to the reducers. Remove unnecessary or redundant data early in the mapping phase to reduce the overall data volume.
- Data Skew Handling: Identify and handle data skew, where certain keys have a disproportionate amount of data. You can implement specialized strategies, like skewed key optimization or using secondary reducers, to distribute the load more evenly among reducers.
- Optimize Input and Output Formats: Choose appropriate input and output formats that minimize data serialization and deserialization overhead. Optimized file formats like SequenceFile or Avro can reduce the size of data on disk and during network transfer.
- Use Distributed Caching: If certain data is used by multiple reducers, you can use distributed caching to make that data available on the nodes where the reducers are running. This reduces the need to transfer the same data over the network multiple times.

## Part 2

The OutDegreeMapper class extends the Mapper class and overrides its map method. This method takes an input key-value pair, which in this case is an Object and a Text object, and outputs a key-value pair, which is a Text and an IntWritable object. The map method first extracts the source node ID and destination node ID from the input Text object, and then emits a key-value pair with the source node ID as the key and a value of 1 as the value.

The OutDegreeReducer class extends the Reducer class and overrides its reduce method. This method takes a key-value pair, which is a Text and an Iterable of IntWritable objects, and outputs a key-value pair, which is a Text and an IntWritable object. The reduce method iterates over the IntWritable values and sums them up to calculate the out-degree of the node represented by the input key. The result is then emitted as a key-value pair with the input key as the key and the out-degree as the value.