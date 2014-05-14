#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <iterator>
using namespace std;

string morse_string;
int morse_string_size;
map<char, string> morse_table;
unsigned int sol;

void matches(int i, int factor, vector<string> &dictionary) {
	int suffix_length = morse_string_size-i;
	if (suffix_length <= 0) {
		sol += factor;
		return;
	}
	map<int, int> c;
	for (vector<string>::iterator it = dictionary.begin() ; it != dictionary.end() ; it++) {
		if (((*it).size() <= suffix_length) && (morse_string.substr(i, (*it).size()) == *it)) {
			if (c.find((*it).size()) == c.end())
				c[(*it).size()] = 0;
			else
				c[(*it).size()]++;
		}
	}
	
	for (map<int, int>::iterator it = c.begin() ; it != c.end() ; it++) {
		matches(i+it->first, factor*(it->second), dictionary);
	}
}

string encode_morse(string s) {
	string ret = "";
	for (unsigned int i = 0 ; i < s.length() ; ++i) {
		ret += morse_table[s[i]];
	}
	return ret;
}

int main() {
	morse_table['A'] = ".-"; morse_table['B'] = "-..."; morse_table['C'] = "-.-."; morse_table['D'] = "-.."; morse_table['E'] = "."; morse_table['F'] = "..-."; morse_table['G'] = "--."; morse_table['H'] = "...."; morse_table['I'] = ".."; morse_table['J'] = ".---"; morse_table['K'] = "-.-"; morse_table['L'] = ".-.."; morse_table['M'] = "--"; morse_table['N'] = "-."; morse_table['O'] = "---"; morse_table['P'] = ".--."; morse_table['Q'] = "--.-"; morse_table['R'] = ".-."; morse_table['S'] = "..."; morse_table['T'] = "-"; morse_table['U'] = "..-"; morse_table['V'] = "...-"; morse_table['W'] = ".--"; morse_table['X'] = "-..-"; morse_table['Y'] = "-.--"; morse_table['Z'] = "--..";
	int T, N;
	string tmp;
	vector<string> dictionary;
	cin >> T;
	
	while (T--) {
		morse_string = "";
		cin >> morse_string;
		morse_string_size = morse_string.size();
		cin >> N;
		for (int j = 0 ; j < N ; j++) {
			cin >> tmp;
			dictionary.push_back(encode_morse(tmp));
		}
		
		sol = 0;
		matches(0, 1, dictionary);
		cout << sol;
		
		if (T)
			cout << endl << endl;
	}
	
	return 0;
}
