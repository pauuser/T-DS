#include "output.h"

void print_welcome(void)
{
    printf("Welcome! This programme is created to process BOOK information given in tables.\n");
    printf("It has a lot of functionality so you must read properly the instructions:\n");
    printf("    1 - You should import table from a file. The file is supposed to contain table fields separated by TABS\n\n");
    printf("\t Every line should include:\n");
    printf("\t \t * author name (1 word not more than 20 signs)\n");
    printf("\t \t * book's title (not more than 20 signs including spaces)\n");
    printf("\t \t * publisher (not more than 20 signs)\n");
    printf("\t \t * page count (not more than 30 000)\n");
    printf("\t \t * literature type (can be only 'technical', 'fiction', 'children's')\n\n");
    printf("\t If the book is technical you must provide:\n");
    printf("\t \t 1) book study area (not more than 20 signs)\n");
    printf("\t \t 2) country (can be only 'state' or 'translated')\n");
    printf("\t \t 3) publishing year (can't be negative or more than 2021)\n");
    printf("\t If the book is fictional you must provide:\n");
    printf("\t \t 1) Book type (can be only 'novel', 'play' or 'poetry')\n");
    printf("\t If the book is for chilren you must provide:\n");
    printf("\t \t 1) Book type (can be only 'fairy tale' or 'poetry')\n\n");
    printf("    2 - You must type in only what you are asked for!\n");
    printf("Uncompliance with rules leads to errors. Also you must check that your file exists!\n\n");
}

void print_menu(void)
{
    printf("0 - Exit\n");
    printf("1 - Input data from file\n");
    printf("2 - Add a new line in the end of the table\n");
    printf("3 - Delete a line of a given field\n");
    printf("4 - Search tech book information by the given area\n");
    printf("5 - Open sorted key table\n");
    printf("6 - Sort by year using the main table\n");
    printf("7 - Sort by year using the key table\n");
    printf("8 - Efficiency comparison results output\n");
    printf("9 - Sorting algorytm comparison results\n\n");
    printf("Your choice: "); 
}

void print_book(book *temp)
{
    printf("%20s ", temp->name);
    printf("%20s ", temp->title);
    printf("%20s ", temp->publisher);
    printf("%5d ", temp->pages);
    if (temp->type == TECHNICAL)
        printf("technical \t");
    else if (temp->type == FICTION)
        printf("fiction   \t");
    else
        printf("children's\t");
    if (temp->type == TECHNICAL)
    {
        printf("%11s ", temp->spec.tech_info.area);
        if (temp->spec.tech_info.type == STATE)
            printf("%11s ", "state");
        else
            printf("%11s ", "translated");
        printf("%11d",  temp->spec.tech_info.year);
    }
    else if (temp->type == FICTION)
    {
        if (temp->spec.fiction_info == FICTION_POETRY)
            printf("%11s ", "poetry");
        else if (temp->spec.fiction_info == PLAY)
            printf("%11s ", "play");
        else
            printf("%11s ", "novel");
    }
    else if (temp->type == CHILDREN)
    {
        if (temp->spec.children_info == CHILDREN_POETRY)
            printf("%11s ", "poetry");
        else
            printf("%11s", "novel");
    }
}

void print_book_table(book_table *table)
{
    for (int i = 0; i < table->quantity; i++)
    {
        print_book((table->data) + i);
        printf("\n");
    }
}

void print_key_table(page_key_table *key_table)
{
    printf("old\tnew\tpages\n");
    for (int i = 0; i < key_table->n; i++)
    {
        printf("%d\t", (key_table->pages)[i][0]);
        printf("%d\t", (key_table->pages)[i][1]);
        printf("%d\n", (key_table->pages)[i][2]);
    }
}

void print_table_by_key_table(book_table *table, page_key_table *key_table)
{
    printf("Sorted table:\n");
    int n = key_table->n;
    for (int i = 0; i < n; i++)
    {
        print_book(&(table->data)[(key_table->pages)[i][1]]);
        printf("\n");
    }
}