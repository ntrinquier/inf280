#include <iostream>
using namespace std;

bool compute(int x, int k, int *values) {
	int change, q0, q1, q2, q3, q4;

	for (q0 = 0 ; q0 <= (int)(x/values[0]) ; q0++) {
		change = x-q0*values[0];
		if (k == 1) {
			if (change == 0)
				return true;
		} else {
			for (q1 = 0 ; q1 <= q0 ; q1++) {
				change = x-q0*values[0]-q1*values[1];
				if (k == 2) {
					if (change == 0)
						return true;
				} else {
					for (q2 = 0 ; q2 <= q1 ; q2++) {
						change = x-q0*values[0]-q1*values[1]-q2*values[2];
						if (k == 3) {
							if (change == 0)
								return true;
						} else {
							for (q3 = 0 ; q3 <= q2 ; q3++) {
								change = x-q0*values[0]-q1*values[1]-q2*values[2]-q3*values[3];
								if (k == 4) {
									if (change == 0)
										return true;
								} else {
									q4 = (int)(change/values[4]);
									if (q4*values[4] == change && q4 <= q3)
										return true;
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}

int main() {
	int T, x, k;
	cin >> T;
	int values[5];
	
	while (T--) {
		cin >> x;
		cin >> k;
		for (int j = 0 ; j < k ; j++)
			cin >> values[j];
		
		if (compute(x, k, values))
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
			
		if (T)
			cout << endl;
	}
	return 0;
}
