#include <stdio.h>
#include <string.h>

char grid[40][40];
char grid_mirror[40][40];
bool mask[40][40];
char words[23][200];
int n, m, k;

int min(const int& a, const int& b) {
	return (a < b) ? a : b;
}

void check_line(int line, char* word, int length) {
	for (int i = 0 ; i <= m-length ; i++)
		for (int j = 0 ; j < length ; j++)
			if (grid[line][i+j] != word[j])
				break;
			else if (j == length-1)
				for (int tmp = i ; tmp < i+length ; tmp++)
					mask[line][tmp] = true;
}

void check_line_backwards(int line, char* word, int length) {
	for (int i = 0 ; i <= m-length ; i++)
		for (int j = 0 ; j < length ; j++)
			if (grid[line][i+j] != word[length-j-1])
				break;
			else if (j == length-1)
				for (int tmp = i ; tmp < i+length ; tmp++)
					mask[line][tmp] = true;
}

void check_column(int column, char* word, int length) {
	for (int j = 0 ; j <= n-length ; j++)
		for (int i = 0 ; i < length ; i++)
			if (grid[i+j][column] != word[i])
				break;
			else if (i == length-1)
				for (int tmp = j ; tmp < j+length ; tmp++)
					mask[tmp][column] = true;
}

void check_column_backwards(int column, char* word, int length) {
	for (int j = 0 ; j <= n-length ; j++)
		for (int i = 0 ; i < length ; i++)
			if (grid[i+j][column] != word[length-i-1])
				break;
			else if (i == length-1)
				for (int tmp = j ; tmp < j+length ; tmp++)
					mask[tmp][column] = true;
}

void check_diagonal_left(int line, int column, char* word, int length) {
	for (int d = 0 ; d <= min(n, m)-length ; d++)
		for (int t = 0 ; t < length ; t++)
			if (grid[line+d+t][column+d+t] != word[t])
				break;
			else if (t == length-1)
				for (int tmp = 0 ; tmp < length ; tmp++)
					mask[line+d+tmp][column+d+tmp] = true;
}

void check_diagonal_left_backwards(int line, int column, char* word, int length) {
	for (int d = 0 ; d <= min(n, m)-length ; d++)
		for (int t = 0 ; t < length ; t++)
			if (grid[line+d+t][column+d+t] != word[length-t-1])
				break;
			else if (t == length-1)
				for (int tmp = 0 ; tmp < length ; tmp++)
					mask[line+d+tmp][column+d+tmp] = true;
}

void check_diagonal_right(int line, int column, char* word, int length) {
	for (int d = 0 ; d <= min(n, m)-length ; d++)
		for (int t = 0 ; t < length ; t++)
			if (grid_mirror[line+d+t][column+d+t] != word[t])
				break;
			else if (t == length-1)
				for (int tmp = 0 ; tmp < length ; tmp++)
					mask[line+d+tmp][m-(column+d+tmp)-1] = true;
}

void check_diagonal_right_backwards(int line, int column, char* word, int length) {
	for (int d = 0 ; d <= min(n, m)-length ; d++)
		for (int t = 0 ; t < length ; t++)
			if (grid_mirror[line+d+t][column+d+t] != word[length-t-1])
				break;
			else if (t == length-1)
				for (int tmp = 0 ; tmp < length ; tmp++)
					mask[line+d+tmp][m-(column+d+tmp)-1] = true;
}

int main() {
	int i, j;
	scanf("%d%d%d", &n, &m, &k);
	for (i = 0 ; i < k ; i++)
		scanf("%s\n", &words[i]);
	for (i = 0 ; i < n ; i++) {
		for (j = 0 ; j < m ; j++) {
			scanf("%c", grid[i]+j);
			grid_mirror[i][m-j-1] = grid[i][j];
			mask[i][j] = false;
		}
		scanf("\n");
	}
	// SEARCH
	int line, column, length;
	for (int word_index = 0 ; word_index < k ; word_index++) {
		length = strlen(words[word_index]);
		// LINE
		for (line = 0 ; line < n ; line++) {
			check_line(line, words[word_index], length);
			check_line_backwards(line, words[word_index], length);
		}
		// COLUMN
		for (column = 0 ; column < m ; column++) {
			check_column(column, words[word_index], length);
			check_column_backwards(column, words[word_index], length);
		}
		// DIAGONALS
		for (line = 0 ; line <= n-length ; line++) {
			for (column = 0 ; column <= m-length ; column++) {
				check_diagonal_left(line, column, words[word_index], length);
				check_diagonal_left_backwards(line, column, words[word_index], length);
				check_diagonal_right(line, column, words[word_index], length);
				check_diagonal_right_backwards(line, column, words[word_index], length);
			}
		}
	}
	printf("\n");
	for (i = 0 ; i < n ; i++)
		for (j = 0 ; j < m ; j++)
			if (!mask[i][j])
				printf("%c", grid[i][j]);
	printf("\n");
	return 0;
}
