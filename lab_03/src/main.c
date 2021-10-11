#include "common.h"
#include "input.h"
#include "output.h"
#include "operations.h"
#include "addition.h"
#include "random.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_welcome();
    long long n_a = 0, m_a = 0, m_b = 0, n_b = 0;
    ld **a = NULL, **b = NULL;
    csr_matrix a_csr = { 0 };
    csr_matrix b_csr = { 0 };

    int choice = -1, exit = NO;
    while (choice != 0 && exit == NO)
    {
        print_menu();
        if (scanf("%d", &choice) == 1)
        {
            if (choice == 1)
            {
                if (a != NULL && b != NULL)
                {
                    printf("You alreay have matrices! Do you want to reinput them? [Y / N]: ");
                    char temp[20];
                    scanf("%s", temp);
                    if (strcmp(temp, "Y") == 0)
                    {
                        free_matrix(a, m_a);
                        free_matrix(b, m_b);
                        free_csr_matrix(&a_csr);
                        free_csr_matrix(&b_csr);
                        a = NULL;
                        b = NULL;
                    }
                }
                if (a == NULL)
                {
                    printf("Input the first matrix: \n");
                    a = create_full_matrix(&m_a, &n_a);
                }
                if (a == NULL)
                {
                    printf("The first matrix was not created! You must try again!\n");
                    continue;
                }
                if (b == NULL)
                {
                    printf("Input the second matrix: \n");
                    b = create_full_matrix(&m_b, &n_b);
                }
                if (b == NULL)
                {
                    printf("The second matrix was not created! You must try again!\n");
                    continue;
                }
                if (a != NULL && b != NULL)
                {
                    a_csr = transfer_full_to_csr(a, &m_a, &n_a);
                    b_csr = transfer_full_to_csr(b, &m_b, &n_b);

                    printf("Do you want to see the input?\n");
                    printf("Full matrix A [Y / N]: ");
                    char temp[20];
                    scanf("%s", temp);
                    if (strcmp(temp, "Y") == 0)
                        print_full_matr(a, m_a, n_a);
                    
                    printf("CSR matrix A [Y / N]: ");
                    scanf("%s", temp);
                    if (strcmp(temp, "Y") == 0)
                        print_csr_matrix(&a_csr);
                    
                    printf("Full matrix B [Y / N]: ");
                    scanf("%s", temp);
                    if (strcmp(temp, "Y") == 0)
                        print_full_matr(a, m_a, n_a);
                    
                    printf("CSR matrix B [Y / N]: ");
                    scanf("%s", temp);
                    if (strcmp(temp, "Y") == 0)
                        print_csr_matrix(&b_csr);
                }
            }
            else if (choice == 2)
            {
                if (a != NULL && b != NULL && m_a == m_b && n_a == n_b && m_a > 0 && n_a > 0)
                {
                    printf("How do you want to add matrices? [Full (F) / CSR (C)]: ");
                    char temp[20];
                    scanf("%s", temp);
                    if (strcmp(temp, "F") == 0)
                    {
                        ld **res_normal = add_normal_matrices(a, b, m_a, n_a);
                        if (res_normal == NULL)
                            printf("Can't add!\n");
                        else
                        {
                            char temp[20];
                            printf("Do you want to see the result? [Y / N]: ");
                            scanf("%s", temp);
                            if (strcmp(temp, "Y") == 0)
                                print_full_matr(res_normal, m_a, n_a);
                        }
                    }
                    else if (strcmp(temp, "C") == 0)
                    {
                        csr_matrix res_csr = add_csr_matrices(&a_csr, &b_csr, m_a);
                        char temp[20];

                        printf("Do you want to see the result in CSR form? [Y / N]: ");
                        scanf("%s", temp);
                        if (strcmp(temp, "Y") == 0)
                            print_csr_matrix(&res_csr);

                        printf("Do you want to see the full matrix? [Y / N]: ");
                        scanf("%s", temp);
                        if (strcmp(temp, "Y") == 0)
                            print_full_from_csr(&res_csr, m_a, n_a);

                        printf("Do you want to check the result? [Y / N]: ");
                        scanf("%s", temp);
                        if (strcmp(temp, "Y") == 0)
                        {
                            ld **res_normal = add_normal_matrices(a, b, m_a, n_a);
                            csr_matrix res_csr_correct = transfer_full_to_csr(res_normal, &m_a, &n_a);
                            if (csr_matrices_match(&res_csr_correct, &res_csr, m_a) == YES)
                                printf("Matrices match!\n");
                            else
                                printf("Matrices don't match!\n");
                        }
                    }
                    else
                        printf("Unknown command!\n");
                }
                else
                    printf("Wrong input! Can't add matrices!\n");
            }
            else if (choice == 3)
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
            else if (choice == 0)
                exit = YES;
            else
                printf("Wrong input!\n");
        }
        else
        {
            read_needless_syms();
            printf("Wrong input!\n");
        }
    }
    free_matrix(a, m_a);
    free_matrix(b, m_b);
    return OK;
}

void print_menu()
{
    printf("\n| 1 - INPUT MATRIX            |\n");
    printf("| 2 - ADD MATRICES            |\n");
    printf("| 3 - MEASURE TIME AND MEMORY |\n");
    printf("| 0 - EXIT                    |\n\n");
    printf("Your choice: ");
}

void print_welcome()
{
    printf("Welcome! This programme adds matrices.\n");
    printf("Firstly, you must input the matrices.\n");
    printf("Please carefully choose how you will do it.\n");
    printf("You can input floating number in the ways provided:\n");
    printf("Input full matrix or only non-zero elements either from file or keyboard.\n");
    printf("Matrices should be of the same size to be added.\n");
    printf("After the addition, you must choose they way to print the result.\n");
}
