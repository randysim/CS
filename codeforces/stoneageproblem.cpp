// Date: 5/30/2022
// Difficulty: 1200
/*
don't be afraid to use more memory to optimize better.
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
idea 1 - brute force: time limit exceeded
idea 2 - figure out what exactly has changed. don't sum over again: time limit exceeded
idea 3 - save all the queries first, then look for the latest 1 in the array by counting backwards. then start alg from there: ur dumb. you have to print out each step
idea 4 - find a way to optimize fill (find out when things are changed and store last time it was filled): Accepted
*/

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

ll sum(vector<int> a)
{
    ll s = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        s += a[i];
    }

    return s;
}

void solve()
{
}

int main()
{
    int n, q;
    cin >> n >> q;

    vector<int> a(n);
    vector<int> changed(n, -1);
    vector<vector<int>> quer(q);

    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    ll s = sum(a);
    ll lastFill = -1;
    ll lastFillValue = 0;

    for (int k = 0; k < q; ++k)
    {
        int t;
        cin >> t;

        if (t == 1)
        {
            ll i1, v;
            cin >> i1 >> v;

            if (lastFill > changed[i1 - 1])
            {
                s += v - lastFillValue;
            }
            else
            {
                s += v - a[i1 - 1];
            }

            a[i1 - 1] = v;
            changed[i1 - 1] = k;
        }
        else
        {
            ll f;
            cin >> f;
            lastFill = k;
            lastFillValue = f;
            s = f * n;
        }

        cout << s << "\n";
    }

    return 0;
}
