#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;

	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0) : size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size) : size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}
	int getParent(int table) {
		// find parent and compress path
		while (sets[table].parent != table) {
			table = sets[table].parent;
		}
		return table;
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		if (realDestination != realSource) {
			if (sets[realDestination].size > sets[realSource].size) {
				sets[realDestination].size += sets[realSource].size;
				max_table_size = max(sets[realDestination].size, max_table_size);
				sets[realSource].parent = sets[realDestination].parent;
			}
			else {
				sets[realSource].size += sets[realDestination].size;
				max_table_size = max(sets[realSource].size, max_table_size);
				sets[realDestination].parent = sets[realSource].parent;
			}
		}
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
		--destination;
		--source;

		tables.merge(destination, source);
		cout << tables.max_table_size << endl;
	}

	return 0;
}