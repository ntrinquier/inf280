#include <cstdio>
#include <cstring>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 50001, M = 100000, D = 16;

int depth[N], tree[N][D], dang[N][D];
int n, m, count_, parent[N], first_edge[N], to[2*N], weight[2*N], next_edge[2*N];
pair<int, pair <int, int> > edges[M];

int get_parent(int i) {
	if (!parent[i])
		return i;
	return parent[i] = get_parent(parent[i]);
}

void add(int u, int v, int w) {
	to[count_] = v;
	weight[count_] = w;
	next_edge[count_] = first_edge[u];
	first_edge[u] = count_++;
}

void DFS(int p, int u) {
	depth[u] = depth[p]+1;
	tree[u][0] = p;
	for (int i = 0 ; i+1 < D && tree[u][i] ; i++)
		tree[u][i+1] = tree[tree[u][i]][i];
	for (int i = 0 ; i+1 < D ; i++)
		dang[u][i+1] = max(dang[u][i], dang[tree[u][i]][i]);
	for (int i = first_edge[u] ; i != -1 ; i = next_edge[i]) {
		if (to[i] != p) {
			dang[to[i]][0] = weight[i];
			DFS(u, to[i]);
		}
	}
}

int jump(int u, int delta) {
	for (int i = 0 ; i < D ; i++)
		if (delta >> i & 1)
			u = tree[u][i];
	return u;
}

int lowest_common_ancestor(int x, int y) {
	if (depth[x] > depth[y])
		swap(x, y);
	y = jump(y, depth[y]-depth[x]);
	if (x == y)
		return x;
	for (int i = D-1 ; i >= 0 ; i--) {
		if (tree[x][i] != tree[y][i]) {
			x = tree[x][i];
			y = tree[y][i];
		}
	}
	return tree[x][0];
}

int calc(int u, int d) {
	int ret = INT_MIN;
	for (int i = 0 ; i < D ; i++) {
		if (d >> i & 1) {
			ret = max(ret, dang[u][i]);
			u = tree[u][i];
		}
	}
	return ret;
}

int main() {
	int TC = 0, i, j, x, y, z, q;
	while (scanf("%d%d", &n, &m) == 2) {
		memset(parent, 0, sizeof(parent));
		memset(first_edge, -1, sizeof(first_edge));
		memset(tree, 0, sizeof(tree));
		memset(depth, -1, sizeof(depth));
		for (i = 0 ; i <= n ; i++)
			for (j = 0 ; j < D ; j++)
				dang[i][j] = INT_MIN;
		for (i = 0 ; i < m ; i++)
			scanf("%d%d%d", &edges[i].second.first, &edges[i].second.second, &edges[i].first);
		sort(edges, edges+m);
		count_ = 0;
		for (i = 0 ; i < m ; i++) { // Construction de l'arbre
			x = edges[i].second.first;
			y = edges[i].second.second;
			if (get_parent(x) != get_parent(y)) {
				parent[get_parent(x)] = get_parent(y);
				add(x, y, edges[i].first);
				add(y, x, edges[i].first);
			}
		}
		DFS(0, 1);
		scanf("%d", &q);
		if (TC++)
			printf("\n");
		while (q--) {
			scanf("%d%d", &x, &y);
			z = lowest_common_ancestor(x, y);
			printf("%d\n", max(calc(x, depth[x]-depth[z]), calc(y, depth[y]-depth[z])));
		}
	}
	return 0;
}
