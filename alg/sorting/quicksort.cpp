#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#define ll long long

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
