#include "random.h"
#include "input.h"

ld **generate_rand_matrix(ll m, ll n, ll rand_num)
{
    ld **a = init_matrix(m, n);
    for (ll i = 0; i < rand_num; i++)
    {
        ll i = rand() % n;
        ll j = rand() % m;
        a[i][j] = rand() % 100;
    }
    return a;
}
