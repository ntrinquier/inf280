#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> primes;
	// Sieve
	bool is_prime[1000001];
	is_prime[0] = is_prime[1] = false;
	is_prime[2] = true;
	primes.push_back(2);
	for (int k = 3 ; k < 1000001 ; k++)
		is_prime[k] = (k%2 == 1);
		
	for (int k = 3 ; k < 1000001 ; k += 2) {
		if (is_prime[k]) {
			primes.push_back(k);
			for (int j = 2*k ; j < 1000001 ; j += k)
				is_prime[j] = false;
		}
	}
	// End of Sieve
	
	int n, p, q;
	cin >> n;
	
	while (n) {
		bool found = false;
		for (unsigned int i = 0 ; i < primes.size() ; i++) {
			p = primes[i];
			q = n-p;
			if (q <= 0)
				break;
			if (is_prime[q]) {
				found = true;
				break;
			}
		}
		if (found)
			cout << n << " = " << p << " + " << q << endl;
		else
			cout << "Goldbach's conjecture is wrong." << endl;

		cin >> n;
	}
	
	return 0;
}
