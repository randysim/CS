// Date: 5/27/2022
// Difficulty: 1400
// Had to look at editorial, apparently you can brute force even O(n^2) as long as the numbers are small enough
// need to work on basics, practice more constructive algorithm problems

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

void solve(vector<vector<int>> &ar, ll n, ll m)
{

    bool flag = false;
    vector<int> bad;
    for (int i = 0; i < n && bad.empty(); ++i)
    {
        vector<int> correct = ar[i];
        sort(correct.begin(), correct.end());

        for (int k = 0; k < m; ++k)
        {
            if (correct[k] != ar[i][k])
            {
                bad.push_back(k);
            }
        }
    }

    if (bad.size() == 0)
    {
        cout << 1 << " " << 1;
        return;
    }

    if (bad.size() > 2)
    {
        cout << -1;
        return;
    }

    for (int r = 0; r < n; ++r)
    {
        swap(ar[r][bad[0]], ar[r][bad[1]]);
    }

    for (int t = 0; t < n; ++t)
    {
        for (int b = 0; b < m - 1; ++b)
        {
            if (ar[t][b] > ar[t][b + 1])
            {
                cout << -1;
                return;
            }
        }
    }

    cout << bad[0] + 1 << " " << bad[1] + 1;
}

int main()
{
    int t;
    cin >> t;

    for (int i = 0; i < t; ++i)
    {
        ll n, m;
        cin >> n >> m;

        vector<vector<int>> arr(n, vector<int>(m));
        for (ll r = 0; r < n; ++r)
        {
            for (ll c = 0; c < m; ++c)
            {
                cin >> arr[r][c];
            }
        }
        solve(arr, n, m);
        cout << "\n";
    }
}
