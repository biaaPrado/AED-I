#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int u;
    int v;
    int cost;
} Edge;

static Edge edges[200001];
static int parent[200001];

int compareEdges(const void *a, const void *b) {
    Edge *e1 = (Edge *)a;
    Edge *e2 = (Edge *)b;
    return e1->cost - e2->cost;
}

int find_set(int i) {
    if (parent[i] == i)
        return i;
    return parent[i] = find_set(parent[i]);
}

void union_sets(int a, int b) {
    int root_a = find_set(a);
    int root_b = find_set(b);
    if (root_a != root_b) {
        parent[root_b] = root_a;
    }
}

int main() {
    int m, n;

    while (scanf("%d %d", &m, &n) == 2 && (m != 0 || n != 0)) {
        
        long long total_cost = 0;

        for (int i = 0; i < n; i++) {
            scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].cost);
            total_cost += edges[i].cost;
        }

        qsort(edges, n, sizeof(Edge), compareEdges);

        for (int i = 0; i < m; i++) {
            parent[i] = i;
        }

        long long mst_cost = 0;
        int edges_in_mst = 0;

        for (int i = 0; i < n; i++) {
            int root_u = find_set(edges[i].u);
            int root_v = find_set(edges[i].v);

            if (root_u != root_v) {
                mst_cost += edges[i].cost;
                union_sets(root_u, root_v);
                edges_in_mst++;
            }
            
            if (edges_in_mst == m - 1) {
                break;
            }
        }

        long long savings = total_cost - mst_cost;
        printf("%lld\n", savings);
    }

    return 0;
}