#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <stdio.h>
using namespace std;

bool cmp(const pair<float, float>& lhs, const pair<float, float>& rhs) { return lhs.first < rhs.first; }

float compute(vector<pair<float, float> >& levels, float& water) {
	sort(levels.begin(), levels.end(), cmp);
	vector<pair<float, float> >::iterator it = levels.begin();
	float c = 0, altitude = it->first, surface = it->second;
	while (++it != levels.end()) {
		c += surface*(it->first-altitude);
		if (c == water)
			return it->first;
		if (c > water) {
			return altitude+(water-c+surface*(it->first-altitude))/surface;
		}
		altitude = it->first;
		surface += it->second;
	}
	return altitude;
}

int main() {
	int testCases, i, n, x;
	float capacity, water, level, height, width, depth;
	cin >> testCases;
	while (testCases--) {
		capacity = 0;
		vector<pair<float, float> > levels;
		cin >> n;
		for (i = 0 ; i < n ; i++) {
			cin >> level;
			cin >> height;
			cin >> width;
			cin >> depth;
			levels.push_back(make_pair(level, width*depth));
			levels.push_back(make_pair(level+height, -width*depth));
			capacity += height*width*depth;
		}
		cin >> water;
		if (capacity < water)
			cout << "OVERFLOW" << endl;
		else
			printf("%.2f\n", compute(levels, water));

		if (testCases)
			cout << endl;
	}
	return 0;
}
