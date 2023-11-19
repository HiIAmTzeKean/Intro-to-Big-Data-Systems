
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef int VertexId;

struct Partition {
    set<VertexId> master_id;
    set<VertexId> vertex;
    int edge=0;
};

struct Vertex {
    VertexId id;
    bool been_master;
};

struct Graph {
    unordered_map<int, Vertex> vertices;
};

Graph read_graph(FILE* fin, Partition* partition, int num_partitions) {
    Graph graph;

    while (true) {
        VertexId src, dst;
        int partition_id;
        if (fread(&src, sizeof(src), 1, fin) == 0) break;
        if (fread(&dst, sizeof(dst), 1, fin) == 0) break;

        partition_id = rand() % num_partitions;
        partition[partition_id].edge++;
        partition[partition_id].vertex.insert(dst);
        partition[partition_id].vertex.insert(src);

        // if not in map, create new object
        if (graph.vertices.find(src)  == graph.vertices.end()) {
            Vertex vertex;
            vertex.id = src;
            vertex.been_master = rand() % 2;
            graph.vertices[src] = vertex;
            if (vertex.been_master==1) partition[partition_id].master_id.insert(vertex.id); 
        }
        if (graph.vertices.find(dst)  == graph.vertices.end()) {
            Vertex vertex;
            vertex.id = dst;
            vertex.been_master = rand() % 2;
            graph.vertices[dst] = vertex;
            if (vertex.been_master==1) partition[partition_id].master_id.insert(vertex.id); 
        }
    }

    // allocate all remainding vertex to partition
    for (auto& v: graph.vertices) {
        if (v.second.been_master == 0) {
            int partition_id = rand() % num_partitions;
            partition[partition_id].master_id.insert(v.second.id);
            partition[partition_id].vertex.insert(v.second.id);
        }
    }
    return graph;
}


int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: ./vertex_cut [graph_path] [partition]\n");
        exit(-1);
    }

    int num_partitions = atoi(argv[2]);
    Partition partition[num_partitions];

    FILE *fin = fopen(argv[1], "rb");
    Graph graph = read_graph(fin,partition, num_partitions);
    fclose(fin);

    printf("Size of graph %ld\n", graph.vertices.size());
    for (int i=0;i<num_partitions;i++) {
        printf("Partition %d\n", i);
        printf("%ld\n", partition[i].master_id.size());
        printf("%ld\n", partition[i].vertex.size() - partition[i].master_id.size());
        printf("%d\n", partition[i].edge);
    }

    return 0;
}