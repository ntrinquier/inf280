#include <iostream>
#include <map>
#include <string>
#include <iterator>
#include <vector>
using namespace std;

unsigned int M;
string morse_string;
string morse_table[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

int matches(unsigned int start, vector<int> &x, map<string, int> &dictionary) {
	if (start == morse_string.size())
		return 1;
	if (x[start] != -1)
		return x[start];
	
	int ret = 0;
	map<string, int>::iterator it;
	string substring;
	for (unsigned int i = 0 ; i < M && start+i < morse_string.size() ; i++) {
		substring += morse_string[start+i];
		if ((it = dictionary.find(substring)) != dictionary.end())
			ret += it->second*matches(start+i+1, x, dictionary);
	}

	x[start] = ret;
	return ret;
}

string encode_morse(const string s) {
	string ret = "";
	for (char c:s)
		ret += morse_table[c-'A'];
	if (ret.size() > M)
		M = ret.size();
	return ret;
}

int main() {
	int T, N;
	string tmp;
	map<string, int>::iterator it;
	cin >> T;
	
	while (T--) {
		M = 0;
		vector<int> x(1000, -1);
		map<string, int> dictionary;
		morse_string = "";
		cin >> morse_string;
		cin >> N;
		for (int j = 0 ; j < N ; j++) {
			cin >> tmp;
			tmp = encode_morse(tmp);
			if ((it = dictionary.find(tmp)) == dictionary.end())
				dictionary[tmp] = 1;
			else
				dictionary[tmp]++;
		}
		
		cout << matches(0, x, dictionary);
		
		if (T) {
			cout << endl << endl;
			for (int j = 0 ; j < 1000 ; j++)
				x[j] = -1;
		}
	}
	return 0;
}
