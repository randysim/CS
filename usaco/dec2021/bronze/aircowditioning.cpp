// Date: 7/25/2022

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <math.h>
#include <unordered_map>
#define ll long long

using namespace std;

/*
O(n) solution for Usaco Bronze, December 2021: "Air Cownditioning"
id = ideal temperatures, cur = current temperatures
create a vector d where d[i] =  id[i] - cur[i]
loop through d[i], and if d[i] > d[i - 1] where i > 0, then
add d[i] - d[i - 1] to the count. else, do nothing.

if the signs are different, then break the chain and add d[i] to the count.
the logic is finding "peaks" where the number of steps to turn the entire peak
to 0 is the maximum point. example: (1, 2, 3, 2, 1) requires 3 steps to turn it to (0, 0, 0, 0, 0, 0)
1 2 3 2 1 -> 0 1 2 1 0 -> 0 0 1 0 0 -> 0 0 0 0 0. However, in the case of
1 2 3 2 1 2 3 2 1 after subtracting the first 1, there becomes two seperate peaks
0 1 2 1 0 1 2 1 0 because we can use the decrement of the first peak to also lower the second peak at the same time.
*/
ll solve(vector<int> id, vector<int> cur)
{
    ll c = 0;

    vector<int> d;
    for (int i = 0; i < id.size(); ++i)
    {
        d.push_back(id[i] - cur[i]);
    }

    int sign = 0;
    int amt = 1;
    for (int i = 0; i < d.size(); ++i)
    {
        if (d[i] == 0)
        {
            sign = 0;
            amt = 1;
            continue;
        }

        int cursign = d[i] > 0 ? 1 : -1;

        if (cursign != sign)
        {
            sign = cursign;
            amt = abs(d[i]);
            c += amt;
            continue;
        }

        if (i > 0)
        {
            if (abs(d[i]) > amt)
            {
                // only add additional
                int newAmt = abs(d[i]);
                c += newAmt - amt;
                amt = newAmt;
            }
            else
            {
                amt = abs(d[i]);
            }
        }
        else
        {
            amt = abs(d[i]);
            c += amt;
        }
    }

    return c;
}

int main()
{
    ll n;
    cin >> n;

    vector<int> ideal(n);
    vector<int> current(n);

    for (int i = 0; i < n; ++i)
    {
        cin >> ideal[i];
    }

    for (int i = 0; i < n; ++i)
    {
        cin >> current[i];
    }

    cout << solve(ideal, current) << "\n";
    return 0;
}
