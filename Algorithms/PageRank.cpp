//As close to the metal as possible - no stl overhead, no virtual disspatch, minimal heap church
#include<iostream>
#include<cstdlib>
#include<cmath>

using namespace std;

#define DAMPING 0.85
#define EPSILON 1e-6
#define MAX_ITER 100

void pagerank(int N, int **outlink, int *outdeg, double *rank){
    double *newrank = (double*)malloc(N*sizeof(double));
    double init_val = 1.0/(double)N;

    for(int i = 0; i < N; i++)
        rank[i] = init_val;
    
    for(int iter = 0; iter = MAX_ITER; iter++){
        for(int i = 0; i < N; i++)
            newrank[i] = (1.0 - DAMPING)/(double)N;
        
        for(int u = 0; u < N; u++){
            double share = rank[u]/(double)outdeg[u];
            for(int j = 0; j < outdeg[u]; j++){
                int v = outlink[u][j];
                newrank[v] += DAMPING * share;
            }
        }
        double diff = 0.0;
        for(int i = 0; i < N; i++)
            diff += fabs(newrank[i] - rank[i]);
        
        for(int i = 0; i < N; i++)
            rank[i] = newrank[i];
        if(diff < EPSILON)
            break;
    }
    free(newrank);
}
int main() {
    int N = 4; // number of nodes

    // Outdegree array
    int outdeg[4] = {2, 1, 1, 1};

    // Allocate adjacency lists
    int **outlinks = (int**) malloc(N * sizeof(int*));
    outlinks[0] = (int*) malloc(2 * sizeof(int));
    outlinks[1] = (int*) malloc(1 * sizeof(int));
    outlinks[2] = (int*) malloc(1 * sizeof(int));
    outlinks[3] = (int*) malloc(1 * sizeof(int));

    // Fill adjacency lists
    outlinks[0][0] = 1; outlinks[0][1] = 2;
    outlinks[1][0] = 2;
    outlinks[2][0] = 0;
    outlinks[3][0] = 2;

    // Rank array
    double *rank = (double*) malloc(N * sizeof(double));

    // Compute PageRank
    pagerank(N, outlinks, outdeg, rank);

    // Output
    for (int i = 0; i < N; i++)
        printf("Node %d: %.6f\n", i, rank[i]);

    // Cleanup
    for (int i = 0; i < N; i++)
        free(outlinks[i]);
    free(outlinks);
    free(rank);

    return 0;
}