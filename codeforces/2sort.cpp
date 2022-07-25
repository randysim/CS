// Date: 6/26/2022
// Difficulty: 1400
/*
Good job. Getting better at solving simple problems. Better thought process
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
IDEA 1: Brute Force - Check each subarray and check if next term is at least greater than half of previous term [TIME LIMIT EXCEEDED]
IDEA 2: Preprocess the array so that a[i] = a[i - 1] / a[i]. Then count chains of subarrays less than 2
IDEA 3: do idea 2 but all in one loop
*/

void solve(vector<int> a, ll n, ll k)
{
    ll c = 0;
    ll running = 1;
    for (ll m = 1; m < n; ++m)
    {
        if (a[m - 1] < a[m] * 2)
        {
            running++;
        }
        else
        {
            if (running >= k + 1)
            {
                c += running - k;
            }
            running = 1;
        }
    }

    if (running >= k + 1)
    {
        c += running - k;
    }

    cout << c;
}
// 22 1 1 4 1 1 1
int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        ll n, k;
        cin >> n >> k;

        vector<int> a(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        solve(a, n, k);
        cout << "\n";
    }

    return 0;
}
