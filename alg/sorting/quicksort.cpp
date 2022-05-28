#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#define ll long long

// Date: 5/28/2022
// Referenced: https://www.youtube.com/watch?v=SLauY6PpjW4
// Notes: It is useful to draw out the sorting algorithm and do it step by step (did it in aggie.io)
// when testing, make sure to test for every edge case
// C++ arrays suck, vectors are so much more convenient
// difference between passing * and & into function parameter. vector<int> *v is a pointer you have to dereference, vector<int> &v is the exact reference to it already, it's just more convenient.

using namespace std;

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
int partition(vector<int> &v, int left, int right, int pivot)
{
	while (left <= right)
	{

		while (v[left] < pivot)
		{
			left++;
		}

		while (v[right] > pivot)
		{
			right--;
		}

		if (left <= right)
		{
			swap(v[left], v[right]);
			left++;
			right--;
		}
	}

	return left;
}

void quicksort(vector<int> &v, int left, int right)
{
	if (left >= right)
	{
		return;
	}

	int pivot = v[(left + right) / 2];
	int index = partition(v, left, right, pivot);
	quicksort(v, left, index - 1);
	quicksort(v, index, right);
}

/*
TEST CASES
7
9 2 6 4 3 5 1
7
2 3 4 1 5 6 7
2
2 1
8
9 2 6 5 4 3 5 1
*/

int main()
{
	int t;
	cin >> t;

	vector<int> a(t);

	for (int i = 0; i < t; ++i)
	{
		cin >> a[i];
	}

	quicksort(a, 0, t - 1);

	cout << endl;
	for (int k = 0; k < t; ++k)
	{
		cout << a[k] << " ";
	}
}
