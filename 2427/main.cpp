#include <iostream>
#include <map>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <string>
#define PERIODICITY 18980 
using namespace std;
string dayNames_s[] = {"Imix", "Ik", "Akbal", "Kan", "Chikchan", "Kimi", "Manik", "Lamat", "Muluk", "Ok", "Chuen", "Eb", "Ben", "Ix", "Men", "Kib", "Kaban", "Etznab", "Kawak", "Ajaw"};
string monthNames_s[] = {"Pohp", "Wo", "Sip", "Zotz", "Sek", "Xul", "Yaxkin", "Mol", "Chen", "Yax", "Sak", "Keh", "Mak", "Kankin", "Muan", "Pax", "Kayab", "Kumku", "Wayeb"};
map<string, int> dayNames;
map<string, int> monthNames;

void compute(int dayNumber_, int dayName_, int dayNumber_bis_, int monthName_) {
	int dayNumber = 9, dayName = dayNames["Ajaw"], dayNumber_bis = 3, monthName = monthNames["Sip"]; // = 8.0.0.0.0
	int x = 0, long_date = 8*144000, tmp, a, b, c, d;
	while ((dayNumber_ != dayNumber || dayName_ != dayName || dayNumber_bis_ != dayNumber_bis || monthName_ != monthName) && (x < PERIODICITY)) {
		x++;
		dayNumber++;
		if (dayNumber == 14)
			dayNumber = 1;
		dayName++;
		if (dayName == 21)
			dayName = 1;
		dayNumber_bis++;
		if (((dayNumber_bis == 21) && (monthName != 19)) || ((dayNumber_bis == 6) && (monthName == 19))) {
			dayNumber_bis = 1;
			monthName++;
			if (monthName == 20)
				monthName = 1;
		}
	}
	if (x == PERIODICITY) {
		cout << "NO SOLUTION" << endl;
		return;
	}
	long_date += x;
	while (long_date < 10*144000) {
		tmp = long_date;
		a = tmp/144000;
		tmp -= a*144000;
		b = tmp/7200;
		tmp -= b*7200;
		c = tmp/360;
		tmp -= c*360;
		d = tmp/20;
		tmp -= d*20;
		cout << a << "." << b << "." << c << "." << d << "." << tmp << endl;
		long_date += PERIODICITY;
	}
}

int main() {
	int testcases, i, n, m;
	char tmp[10], tmp_bis[10];
	for (i = 1 ; i < 21 ; i++)
		dayNames.insert(make_pair(dayNames_s[i-1], i));
	for (i = 1 ; i < 20 ; i++)
		monthNames.insert(make_pair(monthNames_s[i-1], i));
	cin >> testcases;
	
	while (testcases--) {
		scanf("%d.%s %d.%s", &n, &tmp, &m, &tmp_bis);
		compute(n, dayNames[tmp], m, monthNames[tmp_bis]);
		if (testcases)
			cout << endl;
	}
	return 0;
}
