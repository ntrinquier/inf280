#include <iostream>
using namespace std;

int compute(int N, int E, int T, int edges[101][101]) {
	int d[N+1], non_marked = N, i;
	bool marked[N+1];
	for (int i = 1 ; i <= N ; i++) {
		d[i] = 2147483647;
		marked[i] = false;
	}
	d[E] = 0;
	while (non_marked--) {
		int imin;
		for (i = 1 ; i <= N ; i++) {
			if (!marked[i]) {
				imin = i;
				break;
			}
		}
		for (i = imin+1 ; i <= N ; i++) {
			if (!marked[i] && d[i] < d[imin])
				imin = i;
		}
		marked[imin] = true;
		for (i = 1 ; i <= N ; i++) {
			if (!marked[i] && edges[imin][i] != -1 && d[imin]+edges[imin][i] < d[i])
				d[i] = d[imin]+edges[imin][i];
		}
	}
	int ret = 0;
	for (i = 1 ; i <= N ; i++)
		if (d[i] <= T)
			ret++;
	return ret;
}

int main() {
	int testcases, N, T, E, M, a, b, c, i, j;
	int edges[101][101];
	cin >> testcases;
	
	while (testcases--) {
		for (i = 1 ; i < 101 ; i++)
			for (j = 1 ; j < 101 ; j++)
				edges[i][j] = -1;
		cin >> N;
		cin >> E;
		cin >> T;
		cin >> M;
		for (i = 0 ; i < M ; i++) {
			cin >> a;
			cin >> b;
			cin >> c;
			edges[b][a] = c;
		}
		cout << compute(N, E, T, edges) << endl;
		if (testcases)
			cout << endl;
	}
	return 0;
}
