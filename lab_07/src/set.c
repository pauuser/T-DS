#include "../inc/set.h"

/*
Функция поиска родителя вершины (в каком множестве она сейчас)
*/
int find_parent(struct subset_t subsets[], int i)
{
	if (subsets[i].parent != i)
	{
        subsets[i].parent = find_parent(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

/*
Функция объединения вершин в одну
*/
void union_sets(struct subset_t subsets[], int x, int y)
{
	int xroot = find_parent(subsets, x);
	int yroot = find_parent(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
		subsets[xroot].parent = yroot;
	else if (subsets[xroot].rank > subsets[yroot].rank)
		subsets[yroot].parent = xroot;
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}