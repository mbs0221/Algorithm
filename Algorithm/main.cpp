#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "sort.h"

using namespace std;

string lcs(const string str1, const string str2){
	int length = 0;
	int position = 0;
	vector<int> row0(str2.size());
	vector<int> row1(str2.size());
	for (int i = 0; i < str1.size(); i++){
		row1.assign(row0.size(), 0);
		for (int j = 0; j < str2.size(); j++){
			if (str2[j] == str1[i]){
				if (j == 0){
					row1[j] = 1;
				}
				else{
					row1[j] = row0[j - 1] + 1;
				}
				if (row1[j]>length){
					length = row1[j];
					position = j;
				}
			}
		}
		row0.assign(row1.begin(), row1.end());
	}
	return str2.substr(position - length + 1, length);
}

string lcs2(const string str1, const string str2){
	int **matrix, length, x, y;
	matrix = new int*[str1.size()];
	length = 0;
	for (int i = 0; i < str1.size(); i++){
		matrix[i] = new int[str2.size()];
		for (int j = 0; j < str2.size(); j++){
			if (str2[j] == str1[i]){
				if (i > 0 || j > 0){
					matrix[i][j] = matrix[i - 1][j - 1] + 1;
				}
				else{
					matrix[i][j] = 1;
				}
				if (matrix[i][j]>length){
					length = matrix[i][j];
					x = j, y = i;
				}
			}
		}
	}
	return str2.substr(y - length + 1, length);
}

long int gcd(long int a, long int b)
{
	long int c;

	while (b){
		c = a%b;
		a = b;
		b = c;
	}
	return a;
}

long int lcm(long int a, long int b)
{
	return (a*b) / gcd(a, b);
}

void main()
{
	Sort s;
	int a[] = { 31, 32, 54, 67, 76, 34, 23, 35, 28, 23 };
	s.insert_sort(a, 9);
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	char c;
	cin >> c;
}