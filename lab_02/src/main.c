#include "common.h"
#include "input.h"
#include "operations.h"
#include "output.h"
#include "sort_key.h"
#include "sort_table.h"
#include "stats.h"

int main(void)
{
    setbuf(stdout, NULL);

    book_table table;
    table.quantity = 0;

    print_welcome();
    int choice = -1;
    while (choice != 0)
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
        {
            printf("No such option! You have to restart!\n");
            break;
        }
        else if (choice > 9 || choice < 0)
            printf("No such option!\n");
        else if (choice == 1)
        {
            if (input_data_from_file(&table) != OK)
                printf("Something wrong in file or you already have one!\n");
        }
        else if (choice == 2)
            add_line(&table);
        else if (choice == 3)
            delete_line(&table);
        else if (choice == 4)
            find_tech_data_by_area(&table);
        else if (choice == 5)
            open_sorted_key_table(&table);
        else if (choice == 6)
        {
            sort_table_full(&table, NULL, NULL);
            print_book_table(&table);
        }
        else if (choice == 7)
            sort_table_key_hub(&table);
        else if (choice == 8)
            output_efficiency_results(table);
        else if (choice == 9)
            output_sort_stats(table);
    }

    return OK;
}
