
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <set>
#include <unordered_map>
#include <algorithm>
using namespace std;
typedef int VertexId;
// srun -n 1 a.out small-5.graph 

struct Partition {
    set<VertexId> master_id;
    set<VertexId> vertex;
    int edge=0;
    int replicated_edge=0;
};

struct Vertex {
    VertexId id;
    int partition;
    set<VertexId> in;
    set<VertexId> out;
};

struct Graph {
    unordered_map<int, Vertex> vertices;
};

Graph read_graph(FILE* fin, int num_partitions) {
    Graph graph;

    while (true) {
        VertexId src, dst;
        if (fread(&src, sizeof(src), 1, fin) == 0) break;
        if (fread(&dst, sizeof(dst), 1, fin) == 0) break;

        printf("edge: (%d %d)\n", src, dst);

        // if not in map, create new object
        if (graph.vertices.find(src)  == graph.vertices.end()) {
            Vertex vertex;
            vertex.id = src;
            vertex.partition = rand() % num_partitions;
            graph.vertices[src] = vertex;
            // src -> dst
            graph.vertices[src].out.insert(dst);
        }
        else {
            graph.vertices[src].out.insert(dst);
        }

        if (graph.vertices.find(dst)  == graph.vertices.end()) {
            Vertex vertex;
            vertex.id = dst;
            vertex.partition = rand() % num_partitions;
            graph.vertices[dst] = vertex;
            // src -> dst
            graph.vertices[dst].in.insert(src);
        }
        else {
            graph.vertices[dst].in.insert(src);
        }
    }
    return graph;
}


int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "usage: ./edge_cut [graph_path] [partitions]\n");
        exit(-1);
    }

    int num_partitions = atoi(argv[2]);
    Partition partition[num_partitions];

    FILE *fin = fopen(argv[1], "rb");
    Graph graph = read_graph(fin,num_partitions);
    fclose(fin);

    // any dst containing the master vertex will be added to edge and replicated_edge
    // if src is a master then it will be deducted from replicated_edge
    for (auto& entry : graph.vertices) {
        int partition_id = entry.second.partition;
        int u_id = entry.second.id;

        // insert to its partition
        partition[partition_id].master_id.insert(u_id);

        // update all mirror vertex
        partition[partition_id].vertex.insert(u_id);
        partition[partition_id].vertex.insert(entry.second.in.begin(),entry.second.in.end());
        partition[partition_id].vertex.insert(entry.second.out.begin(),entry.second.out.end());

        partition[partition_id].replicated_edge += entry.second.out.size() + entry.second.in.size();
        partition[partition_id].edge += entry.second.out.size() + entry.second.in.size();

        // check if the current vertex is linked to any other previous master
        // deduct the replicated accordingly
        if (partition[partition_id].master_id.size()==1) continue;
        else {
            // check for each master excluding itself
            for (auto& v : partition[partition_id].master_id) {
                if (v==u_id) continue;

                // check if the out/in going edge of v contains current entry
                // if id_1 has id_2 in edge, then it will be a double count
                if (entry.second.in.find(v) != entry.second.in.end()) {
                    partition[partition_id].replicated_edge -=2;
                }

                if (entry.second.out.find(v) != entry.second.out.end()) {
                    partition[partition_id].replicated_edge -=2;
                }
            }
        }
    }
    
    printf("--------------------------------\n");
    for (int partition_id=0; partition_id<num_partitions; partition_id++){
        printf("Partition %d\n", partition_id);
        printf("%ld\n", partition[partition_id].master_id.size());
        // for (auto& v : partition[partition_id].master_id) { printf("%d, ", v); };
        // printf("---\n");
        printf("%ld\n", partition[partition_id].vertex.size());
        // for (auto& v : partition[partition_id].vertex) { printf("%d, ", v); };
        // printf("---\n");
        printf("%d\n", partition[partition_id].replicated_edge);
        printf("%d\n", partition[partition_id].edge);
    }
    return 0;
}