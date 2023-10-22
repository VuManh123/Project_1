#include <stdio.h>
#include <stdlib.h>

/*Cau truc du lieu Union + find + Kruskal
Kruskal: Bat dau voi canh nho nhat (ko tao chu trinh)
Lap lai buoc tren den khi thu duoc (N-1) canh*/

struct Edge{
	int src, dest, weight;
};
struct Subset{
	int parent, rank;
};

int findSubset(struct Subset subsets[], int i){
	if(subsets[i].parent != i)
		subsets[i].parent = findSubset(subsets, subsets[i].parent);
	return subsets[i].parent;
}

void unionTwoSubset(struct Subset subsets[], int x, int y){
	int xroot = findSubset(subsets, x);
    int yroot = findSubset(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int compareEdges(const void* a, const void* b){
	return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

int kruskalMST(struct Edge edges[], int V, int E){
	// Tao mang luu gia tri cac canh
    struct Edge result[V];
    int e = 0, i = 0;

    // Sap xep canh theo weight
    qsort(edges, E, sizeof(struct Edge), compareEdges);

    // Khoi tao tap con cho moi dinh
    struct Subset subsets[V];
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Xay dung cay bao trum toi thieu
    while (e < V - 1 && i < E) {
        struct Edge nextEdge = edges[i++];

        int x = findSubset(subsets, nextEdge.src);
        int y = findSubset(subsets, nextEdge.dest);

        if (x != y) {
            result[e++] = nextEdge;
            unionTwoSubset(subsets, x, y);
        }
    }

    // Tinh tong weight
    int minimumCost = 0;
    for (i = 0; i < e; i++)
        minimumCost += result[i].weight;

    return minimumCost;
}

int main(){
	int N, M;
	scanf("%d %d", &N, &M);

    struct Edge edges[M];
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].src = u - 1;
        edges[i].dest = v - 1;
        edges[i].weight = w;
    }

    int result = kruskalMST(edges, N, M);
    printf("%d\n", result);

    return 0; 
} 
