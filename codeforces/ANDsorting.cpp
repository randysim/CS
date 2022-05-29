// Date: 5/28/2022
// Difficulty: 1100
/*
Study more bitwise lol
what's a submask??
tbh i kinda got lucky on this one i just assumed this was the way
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
plan:
ints 0 to n-1
each occurs EXACTLY ONCE
a number n should go to the nth position of the array.

just swap the ones you need and figure out what X is

7
0 1 2 3 5 6 4
should be 4

1
4
0 3 1 2 -> 1 3 0 2 -> 1 0 3 2 -> 1 2 3 0 -> 0 1 2 3
should be 0, got 1
*/

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

void solve(vector<int> a)
{
    int ans = 0;
    bool flag = false;

    for (int i = 0; i < a.size(); ++i)
    {
        if (i != a[i])
        {
            if (!flag)
            {
                ans = i & a[i];
                flag = true;
            }
            else
            {
                ans &= i & a[i];
            }
        }
    }

    cout << ans;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;

        vector<int> a(n);

        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
        }

        solve(a);
        cout << "\n";
    }

    return 0;
}
