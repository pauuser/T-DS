#ifndef __H_SET__
#define __H_SET__

struct subset_t
{
	int parent;
	int rank;
};

//Функция поиска родителя вершины (в каком множестве она сейчас)
int find_parent(struct subset_t subsets[], int i);

// Функция объединения вершин в одну
void union_sets(struct subset_t subsets[], int x, int y);

#endif