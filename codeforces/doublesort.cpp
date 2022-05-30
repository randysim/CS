// Date: 5/29/2022
// Difficulty: 1200
/*
try and write better code. some stuff could be optimized. its ok because
this problem had small numbers but for bigger numbers, learn optimization.
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#define ll long long

using namespace std;

/*
EXAMPLE:
4
2 3 1 2 -> 1 3 2 2 -> 1 2 3 2 -> 1 2 2 3
2 3 2 3 -> 2 3 2 3 -> 2 2 3 3 -> 2 2 3 3

1 3 2 2
2 3 2 3

1 2 3 2
2 2 3 3

1 2 2 3
2 2 3 3
*/

/*
IDEAS:
Take first array. copy + sort. Then loop forward till find desired number and swap. Do same swaps for second arr. Then check if second is sorted and then print out moves + swaps.
issue 1 (what if array 1 is repeated elements and sorted but array 2 isn't and is not sorted.)
ex:
2
2 2
2 1
solution: do the same thing for b after sorting a. then check if both are sorted (good thing max of 100 elem in array)
it works. there's probably some weird pattern. i think i invented math. whatever. brute force works on small numbers.
*/

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void solve(vector<int> a, vector<int> b)
{
    int swaps = 0;

    vector<int> asort(a.size());
    vector<int> bsort(b.size());
    for (int i = 0; i < a.size(); ++i)
    {
        asort[i] = a[i];
        bsort[i] = b[i];
    }

    sort(asort.begin(), asort.end());
    sort(bsort.begin(), bsort.end());

    vector<vector<int>> swapList;

    for (int k = 0; k < a.size() - 1; ++k)
    {
        if (asort[k] != a[k])
        {
            // look for correct value forward
            int c = k + 1;
            while (c < a.size() && a[c] != asort[k])
            {
                c++;
            }

            swap(a[k], a[c]);
            swap(b[k], b[c]);
            vector<int> swapData = {k + 1, c + 1};
            swapList.push_back(swapData);
            swaps++;
        }
    }

    for (int h = 0; h < b.size() - 1; ++h)
    {
        if (bsort[h] != b[h])
        {
            // looh for correct value forward
            int f = h + 1;
            while (f < b.size() && b[f] != bsort[h])
            {
                f++;
            }

            swap(a[h], a[f]);
            swap(b[h], b[f]);
            vector<int> swapData = {h + 1, f + 1};
            swapList.push_back(swapData);
            swaps++;
        }
    }

    if (swaps > 10000)
    {
        cout << -1 << "\n";
        return;
    }

    // check if b is sorted
    for (int j = 0; j < b.size(); ++j)
    {
        if (b[j] != bsort[j] || a[j] != asort[j])
        {
            cout << -1 << "\n";
            return;
        }
    }

    // print everything out
    cout << swaps << "\n";
    for (int d = 0; d < swapList.size(); ++d)
    {
        cout << swapList[d][0] << " " << swapList[d][1] << "\n";
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<int> a(n);
        vector<int> b(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        for (int k = 0; k < n; ++k)
        {
            cin >> b[k];
        }

        solve(a, b);
    }

    return 0;
}
