#include <stdio.h>
#include <string.h>
#include <queue>
using namespace std;
#define MAXN 710
#define MAXM 60010
#define INF 10000000

int init_indice[MAXN], to[MAXM], next_indice[MAXM], count;
int appel_prec[MAXN], length[MAXN], res;
bool visited[MAXN];
void add(int a, int b) {
	to[count] = b;
	next_indice[count] = init_indice[a];
	init_indice[a] = count++;
}

int bfs(int s) {
	memset(visited, 0, sizeof(visited));
	queue<int> que;
	visited[s] = 1, length[s] = 0;
	appel_prec[s] = -1;
	que.push(s);
	while (!que.empty()) {
		s = que.front();
		que.pop();
		if (length[s]*2-1 > res)
			break;
		for (int i = init_indice[s] ; i != -1 ; i = next_indice[i]) {
			if (!visited[to[i]]) {
				visited[to[i]] = 1;
				length[to[i]] = length[s]+1;
				appel_prec[to[i]] = s; // On retient depuis quel sommet on fait le bfs
				que.push(to[i]);
			}  
			else if (to[i] != appel_prec[s] && length[s]+length[to[i]]+1 < res) { // Si ce n'est pas un simple retour en arriere & qu'on a un cycle plus court
				res = length[s]+length[to[i]]+1;
			}
		}
	}
	return INF;
}

int main() {
	int TC, n, m, a, b, c = 1; 
	scanf("%d", &TC);
	while (TC--) {
		memset(init_indice, -1, sizeof(init_indice));
		count = 0;
		scanf("%d%d", &n, &m);
		for(int i = 0 ; i < m ; ++i) {
			scanf("%d%d", &a, &b);
			add(a, b);
			add(b, a);
		}  
		res = INF;
		for(int i = 0 ; i < n && res > 3 ; ++i) // BFS pour chaque sommet à la recherche de cycles
			bfs(i);
		printf("Case %d: ", c);
		if (res == INF)
			printf("impossible\n");
		else
			printf("%d\n", res);
		c++;
	}
	return 0;
}
