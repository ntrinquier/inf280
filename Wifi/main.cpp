#include <stdio.h>
#include <algorithm>

int houses[100001];

int cmp(const void *a, const void *b) {
	int* a_ = (int*)a;
	int* b_ = (int*)b;
	return ((*a_) < (*b_)) ? 0 : 1;
}

int main() {
	int TC, n, m, i, left, right, middle;
	scanf("%d", &TC);
	while (TC--) {
		scanf("%d%d", &n, &m);   
		for (i = 0 ; i < m ; i++)
			scanf("%d", houses+i);
		qsort(houses, m, sizeof(int), cmp); // In case houses aren't given in ascending order
		left = 0;
		right = 2*(houses[m-1]-houses[0]+1);
		while (right > left) {
			middle = (left+right)/2;
			int from = houses[0];
			int needed = 1;
			for (i = 1 ; i < m ; i++) {
				if (houses[i] > from+middle) {
					from = houses[i];
					needed++;
				}
			}
			if (needed > n)
				left = middle+1;
			else
				right = middle;
		}
		printf("%.1f\n", right/2.00);
	}
	return 0;
}
