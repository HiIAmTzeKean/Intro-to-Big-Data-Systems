# Report for HW6

Cluster username: bds23-ghcstu08  
Student name: Ng Tze Kean  
Student type: Virtual Exchange student  

## Word Count

### Running program

To run the program ```spark-submit word_count.py /data/hw6_data/pg100.txt```

### Expected output

```bash
('', 198753)
('the', 23288)
('I', 22225)
('and', 18653)
('to', 16373)
('of', 15725)
('a', 12796)
('you', 12186)
('my', 10839)
('in', 10016)
```

### Explanation

A function helper ```process``` is used to process the lines obtained by Spark. The function ```normalizeWords``` is passed to process the words in the object. Subsequently, for each key, value pair, it will be mapped to ```wcPair``` and then reduced through the key. Finally, the result is sorted by its value to obtain the top 10 keys.

## Page Rank

### Running program

To run the program ```spark-submit page_rank.py /data/hw6_data/full.txt```

### Expected output

```bash
The top 5 nodes are...
Node 263         Val [0.00202029]
Node 537         Val [0.00194334]
Node 965         Val [0.00192545]
Node 243         Val [0.00185263]
Node 285         Val [0.00182737]
```

### Explanation

The program reads in a graph represented as an adjacency list from a text file, and calculates the PageRank score for each node in the graph.
We first declare the known facts such as the nuber of iterations = 100 and the beta = 0.8.
The program then processes the input graph data to create the matrix M, which represents the transition probabilities between nodes in the graph. The program first converts the input lines to pairs of integers, representing the source and destination nodes of each edge in the graph. The program then counts the number of outgoing edges from each node, and creates a row of the matrix M for each node. The rows of M are represented as numpy arrays, with each element of the array representing the probability of transitioning from the corresponding node to another node in the graph.

The program then initializes the PageRank vector r, which represents the probability of being at each node in the graph. The program uses the matrix M and the damping factor to iteratively update the PageRank vector r for a fixed number of iterations. The program calculates the teleport probability, which represents the probability of jumping to a random node in the graph, and uses this probability to update the PageRank vector r. The program then calculates the contribution of each incoming edge to the PageRank score of each node, and updates the PageRank vector r accordingly. The program repeats this process for the specified number of iterations = 100.
