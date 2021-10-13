#include "random.h"
#include "input.h"
#include "operations.h"
#include "addition.h"

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

void measure_time(void)
{
    srand(time(NULL));
    struct timeval tv_start, tv_stop;
    int64_t elapsed_time;

    for (ll size = 10; size <= 10000; size *= 5)
    {
        printf("Size of matrix: %lld x %lld\n", size, size);
        printf("Fill\tFull matrix\tCSR matrix\tFull memory\tCSR memory\n");
        for (int i = 20; i <= 100; i = i + 20)
        {
            printf("%-5d%%\t", i);
            ld **one = generate_rand_matrix(size, size, i);
            ld **two = generate_rand_matrix(size, size, i);

            csr_matrix one_csr = transfer_full_to_csr(one, &size, &size);
            csr_matrix two_csr = transfer_full_to_csr(two, &size, &size);
            
            ld **res = init_matrix(size, size);
            gettimeofday(&tv_start, NULL);
            for (ll i = 0; i < size; i++)
                for (ll j = 0; j < size; j++)
                    res[i][j] = one[i][j] + two[i][j];
            gettimeofday(&tv_stop, NULL);
            elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);

            printf("%-10lld\t", (ll) elapsed_time);

            gettimeofday(&tv_start, NULL);
            csr_matrix res_csr = add_csr_matrices(&one_csr, &two_csr, size);
            gettimeofday(&tv_stop, NULL);
            elapsed_time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
            printf("%-10lld\t", (ll) elapsed_time);

            printf("%-10lld\t%-10lld\n", size * sizeof(ld *) + size * size * sizeof(ld), res_csr.nz * 2 * sizeof(ld) + sizeof(ll) + (size + 1) * sizeof(ptr_list));

            free_matrix(one, size);
            free_matrix(two, size);
            free_matrix(res, size);

            free_csr_matrix(&one_csr);
            free_csr_matrix(&two_csr);
            free_csr_matrix(&res_csr);
        }
    }
}