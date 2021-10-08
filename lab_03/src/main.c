#include "common.h"
#include "input.h"
#include "output.h"
#include "operations.h"

int main(void)
{
    setbuf(stdout, NULL);
    print_welcome();
    long long n = 0, m = 0;
    int choice = -1, exit = NO;
    while (choice != 0 && exit == NO)
    {
        print_menu();
        if (scanf("%d", &choice) == 1)
        {
            if (choice == 1)
            {
                long double **a = create_full_matrix(&m, &n);
                if (a != NULL) 
                    print_full_matr(a, m, n);
                csr_matrix a_csr = transfer_full_to_csr(a, &m, &n);
                print_csr_matrix(&a_csr);
            }
            else if (choice == 2)
            {

            }
            else if (choice == 3)
            {

            }
            else if (choice == 0)
            {
                exit = YES;
            }
            else
                printf("Wrong input!\n");
        }
        else
            printf("Wrong input!\n");
    }
    return OK;
}

void print_menu()
{
    printf("\n1 - INPUT MATRIX\n");
    printf("2 - ADD MATRICES\n");
    printf("3 - MEASURE TIME AND MEMORY\n");
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
