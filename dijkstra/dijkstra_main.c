#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX 100
#define INF 1000000

typedef struct GraphType {
	int n;
	int weight[MAX][MAX];
}GraphType;

int found[MAX];
int distance[MAX];

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for(i=0;i<n;i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void printf_status(GraphType* g)
{
	static int step = 1;
	printf("STEP %d: ", step++);
	for (int i = 0; i < g->n; i++)
	{
		if (distance[i] == INF)
			printf("*");
		else
			printf("%2d ", distance[i]);

	}
	printf("\n");
	printf(" found: ");
	for (int i = 0; i < g->n; i++)
		printf("%2d ", found[i]);
	printf("\n\n");
}
void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++)
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;

	}
	found[start] = TRUE;
	distance[start] = 0;
	for (i = 0; i < g->n; i++)
	{
		printf_status(g);
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w])
					distance[w] = distance[u] + g->weight[u][w];
	}
}
int main(void)
{
	GraphType g = { 10,
	{{0,12,INF,INF,INF,15,INF,INF,INF,INF},
	{12,0,4,INF,10,INF,INF,INF,INF,INF},
	{INF,4,0,13,3,INF,INF,INF,INF,INF},
	{INF,INF,13,0,4,INF,INF,15,INF,INF},
	{INF,10,3,INF,0,INF,10,INF,INF,INF},
	{15,INF,INF,INF,INF,0,7,INF,21,INF},
	{INF,INF,INF,INF,10,7,0,9,INF,19},
	{INF,INF,INF,15,INF,INF,9,0,INF,5},
	{INF,INF,INF,INF,INF,21,INF,INF,0,25},
	{INF,INF,INF,INF,INF,INF,19,5,25,0}}
	};
	shortest_path(&g, 0);
	return 0;
}