#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <set>
#include <queue>
#include <iterator>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include <cstring>
using namespace std;

bool must_be_deleted(pair<int, set<int> > x) {
	return x.second.empty();
}

void compute(vector<pair<int, set<int> > > &edges) {
	priority_queue<int, vector<int>, greater<int> > output;
	set<int>::iterator it;
	int t;
	vector<pair<int, set<int> > >::iterator it_v;
	
	while (edges.size() != 0) {
		for (it_v = edges.begin() ; it_v != edges.end() ; ++it_v)
			if ((it_v->second).empty())
				output.push(it_v->first);
		edges.erase(remove_if(edges.begin(), edges.end(), must_be_deleted), edges.end());
		t = output.top();
		output.pop();
		cout << t+1;
		for (it_v = edges.begin() ; it_v != edges.end() ; ++it_v)
			if ((it = (it_v->second).find(t)) != (it_v->second).end())
				(it_v->second).erase(it);
		if (edges.size() != 0 || output.size() != 0)
			cout << " ";
	}
	
	while (output.size() != 0) {
		cout << output.top()+1;
		output.pop();
		if (output.size() != 0)
			cout << " ";
	}
	cout << endl;
}

int main() {
	int testcases, N, M, k, Ti, tmp_int, i;
	cin >> testcases;
	
	while (testcases--) {
		cin >> N;
		cin >> M;
		vector<pair<int, set<int> > > edges;
		bool ok[N];
		memset(ok, false, N);
		
		for (i = 0 ; i < M ; i++) {
			set<int> tmp_set;
			cin >> Ti;
			ok[Ti-1] = true;
			cin >> k;
			for (int j = 0 ; j < k ; j++) {
				cin >> tmp_int;
				tmp_set.insert(tmp_int-1);
			}
			edges.push_back(make_pair(Ti-1, tmp_set));
		}
		set<int> empty_set;
		for (i = 0 ; i < N ; i++)
			if (!ok[i])
				edges.push_back(make_pair(i, empty_set));
		compute(edges);
		if (testcases)
			cout << endl;
	}
	return 0;
}
