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

    csr_matrix a_csr;
    init_csr_matrix(&a_csr);

    csr_matrix b_csr;
    init_csr_matrix(&b_csr);

    int choice = -1, exit = NO;
    while (choice != 0 && exit == NO)
    {
        print_menu();
        if (scanf("%d", &choice) == 1)
        {
            if (choice == 1)
                input_matrices(&a, &b, &a_csr, &b_csr, &m_a, &n_a, &m_b, &n_b);
            else if (choice == 2)
                add_matrices(a, b, &a_csr, &b_csr, &m_a, &n_a, &m_b, &n_b);
            else if (choice == 3)
            {
                measure_time();
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
    free_csr_matrix(&a_csr);
    free_csr_matrix(&b_csr);
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
