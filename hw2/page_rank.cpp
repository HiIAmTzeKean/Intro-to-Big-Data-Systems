#include "page_rank.h"
#include <cmath>
#include <iostream>
#include <omp.h>
#include <stdlib.h>
#include <utility>

#include "./common/CycleTimer.h"
#include "./common/graph.h"

// pageRank --
//
// g:           graph to process (see common/graph.h)
// solution:    array of per-vertex vertex scores (length of array is
// num_nodes(g)) damping:     page-rank algorithm's damping parameter
// convergence: page-rank algorithm's convergence threshold
//
void pageRank(Graph g, double *solution, double damping, double convergence) {
    // initialize vertex weights to uniform probability. Double
    // precision scores are used to avoid underflow for large graphs
    int numNodes = num_nodes(g);
    double equal_prob = 1.0 / numNodes;
    double *solution_new = new double[numNodes];
    double *score_old = solution;
    double *score_new = solution_new;
    bool converged = false;
    double broadcastScore = 0.0;
    double globalDiff = 0.0;
    int iter = 0;
    const Vertex *in_end;
    const Vertex *in_begin;

    #pragma omp parallel for
    for (int i = 0; i < numNodes; ++i) {
        solution[i] = equal_prob;
    }

    while (!converged && iter < MAXITER) {
        iter++;
        broadcastScore = 0.0;
        globalDiff = 0.0;

        #pragma omp parallel for reduction(+:broadcastScore)
        for (int j = 0; j < numNodes; j++){
            if (outgoing_size(g, j) == 0) broadcastScore += damping * score_old[j] / numNodes;
        }

        #pragma omp parallel for reduction(+:globalDiff)
        for (int i = 0; i < numNodes; i++){
            const Vertex* in_start = incoming_begin(g, i);
            const Vertex* in_end = incoming_end(g, i);
            double sum = 0.0;
            for (const Vertex* v = in_start; v != in_end; v++){
                sum += score_old[*v] / (double)outgoing_size(g, *v);
            }

            sum = (damping * sum) + (1.0 - damping) / numNodes;

            sum += broadcastScore;
	  score_new[i] = sum;
	  globalDiff += fabs(sum - score_old[i]);
      }

        converged = globalDiff < convergence;
        std::swap(score_new, score_old);
    }
    if (score_new != solution) {
        memcpy(solution, score_new, sizeof(double) * numNodes);
    }
    delete[] solution_new;
}
