#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <utility>

using namespace std;
typedef pair <int, int> pair_type;

int N;
vector <pair_type> adj[100000];

int dijkstra(int c1, int c2) {
	set<pair_type> q;
	vector<int> d(N, 1000000);
	d[c1] = 0;
	q.insert(make_pair(0, c1));
	while (q.size() > 0) {
		pair_type p = *q.begin();
		q.erase(q.begin());
		if (p.second == c2)
			return p.first;
		for (int i = 0 ; i < (int) adj[p.second].size() ; i++) {
			pair_type x(p.first+adj[p.second][i].first, adj[p.second][i].second);
			if (x.first < d[x.second]) {
				q.erase(make_pair(d[x.second], x.second));
				q.insert(x);
				d[x.second] = x.first;
			}
		}
	}
	return -1;
}

int main(int argc, char* argv[]) {
	int TC, nc, c, tmp, c1, c2;
	cin >> TC;

	while (TC--) {
		if ('\n' == cin.peek())
			cin.ignore();
		cin >> N;
		for (int i = 0 ; i < N ; i++) {
			cin >> c >> nc;
			for (int j = 0 ; j < nc ; j++) {
				cin >> tmp;
				adj[c].push_back(make_pair(1, tmp));
			}
		}
		cin >> c1 >> c2;
		printf("%d %d %d\n", c1, c2, dijkstra(c1, c2)-1);
		if (TC)
			printf("\n");
		for (int i = 0 ; i < N ; i++)
			adj[i].clear();
	}
	return 0;
}
