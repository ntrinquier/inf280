#include <iostream>
#include <algorithm>
using namespace std;

bool perfectly_cut(double *cut, int n, int size, double w) {
	sort(cut, cut+n);
	if (w/2 < cut[0] || cut[n-1]+w/2 < size)
		return false;

	for (int k = 0 ; k < n-1 ; k++) {
		if (cut[k]+w < cut[k+1])
			return false;
	}
	return true;
}

int main() {
	int length = 100, width = 75;
	int nx, ny;
	double w;
	double cutx[1000];
	double cuty[1000];

	cin >> nx;
	cin >> ny;
	cin >> w;
	
	while (nx != 0 || ny != 0 || w != 0.0) {		
		for (int k = 0 ; k < nx ; k++)
			cin >> cutx[k];
		for (int k = 0 ; k < ny ; k++)
			cin >> cuty[k];

		if (perfectly_cut(cutx, nx, width, w) && perfectly_cut(cuty, ny, length, w))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;

		cin >> nx;
		cin >> ny;
		cin >> w;
	}
	return 0;
}
