#ifndef __H_SET__
#define __H_SET__

struct subset_t
{
	int parent;
	int rank;
};

int find_parent(struct subset_t subsets[], int i);

void union_sets(struct subset_t subsets[], int x, int y);

#endif