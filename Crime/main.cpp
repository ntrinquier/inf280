#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <list>
#include <queue>

using namespace std;
int n, m, x;
bool visited[1001];
int partition[1001];

bool bipartite(int i, vector<list<int> >& adj) {
	queue<int> q;
	int s, t = 0, c = 1;
	q.push(i);
	partition[i] = 1;
	while (!q.empty()) {
		s = q.front();
		q.pop();
		for (list<int>::iterator it = adj[s].begin() ; it != adj[s].end() ; ++it) {
			if (partition[*it] == -1) {
				partition[*it] = 1-partition[s];
				if (partition[*it] == 1)
					c++;
				q.push(*it);
			} else if (partition[*it] == partition[s]) {
				return false;
			}
		}
		visited[s] = true;
		t++;
	}
	x += min(c, t-c);
	return true;
}

int calc(int n, vector<list<int> >& adj) {
	memset(visited, false, n+1);
	x = 0;
	for (int i = 1 ; i <= n ; i++)
		partition[i] = -1;
	int tmp, ret = 0;
	for (int i = 1 ; i <= n ; i++)
		if (!visited[i] && !bipartite(i, adj))
			return -1;
	return x;
}

int main(int argc, char* argv[]) {
	int a, b, res, ret;
	ret = scanf("%d %d\n", &n, &m);
	while (1) {
		vector<list<int> > adj(10001);
		if (ret == EOF)
			break;
		for (int i = 0 ; i < m ; i++) {
			scanf("%d %d\n", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		res = calc(n, adj);
		if (res == -1)
			printf("Impossible\n");
		else
			printf("%d\n", res);
		ret = scanf("%d %d\n", &n, &m);
	}
	return 0;
}
