#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sys/time.h>

#define OK 0
#define INVALID_MENU_NUM -1
#define WRONG_FILE_NAME -2
#define BROKEN_FILE -3
#define ALREADY_HAVE_INPUT -4
#define NO_BOOKS -5

#define MAX_FIELD_LEN 20
#define MAX_BOOKS_NUM 100
#define MAX_STR_LEN 20
#define MAX_FIELDS_NUM 8
#define MAX_LINE_LEN 500 // досчитать

#define YES 1
#define NO 0
#define ASCII_NUM_DIFF 48

typedef enum { TECHNICAL, FICTION, CHILDREN } book_t;

typedef enum { NOVEL, PLAY, FICTION_POETRY } fiction_info_t;

typedef enum { FAIRYTAILS, CHILDREN_POETRY } children_info_t;

typedef enum { STATE, TRANSLATED } tech_pub_t;

typedef struct
{
	char area[MAX_FIELD_LEN + 1];
    tech_pub_t type;
    short int year;
} tech_info_t;

typedef struct
{
	char name[MAX_FIELD_LEN + 1];
	char title[MAX_FIELD_LEN + 1];
	char publisher[MAX_FIELD_LEN + 1];
	int pages;
	book_t type;
	union spec_u
    {
        tech_info_t tech_info;
        fiction_info_t fiction_info;
        children_info_t children_info;
    } spec;
} book;

typedef struct
{
    book data[MAX_BOOKS_NUM];
    short int quantity;
} book_table;

typedef struct
{
    short int n;
    /* | 0 - old | 1 - new | 2 - value | */
    short int pages[MAX_BOOKS_NUM][3];
} page_key_table;

void print_welcome(void);

void print_menu(void);

int input_data_from_file(book_table *table);

int check_file(FILE *f, int n);

int check_string(char *string);

int str_to_num(char *str);

int create_mas_of_words(char *string, char **mas, int max_number, char *delims);

int count_file_len(FILE *f);

int string_is_not_empty(char *string);

book input_line(char *line);

void print_book(book *temp);

void print_book_table(book_table *table);

void add_line(book_table *table);

void delete_line(book_table *table);

int value_in_mas(char *value, char **mas, int n);

void delete_new_str_sym(char *str);

void find_tech_data_by_area(book_table *table);

int create_page_key_table(book_table *table, page_key_table *key_table);

void print_key_table(page_key_table *key_table);

void find_tech_data_by_area(book_table *table);

void open_sorted_key_table(book_table *table);

void sort_key_table(page_key_table *key_table, int64_t *bubble_time_key, int64_t *qsort_time_key, int64_t elapsed_time);

int compare_key_lines(const void *one, const void *two);

void bubble_sort_key_table(page_key_table *key_table);

void swap_lines(page_key_table *key_table, short int line1, short int line2);

int create_page_key_table(book_table *table, page_key_table *key_table);

void print_key_table(page_key_table *key_table);

void sort_table_full(book_table *table, int64_t *bubble_time_table, int64_t *qsort_time_key);

int compare_books(const void *one, const void *two);

void bubble_sort_table(book_table *table);

void swap_books(book *one, book *two);

void sort_table_key_hub(book_table *table);

void print_table_by_key_table(book_table *table, page_key_table *key_table);

void output_sort_stats(book_table table);

void output_efficiency_results(book_table table);

int main(void)
{
    setbuf(stdout, NULL);

    int ret_code = OK;

    book_table table;
    table.quantity = 0;

    print_welcome();
    int choice = -1;
    while (choice != 0 && ret_code == OK)
    {
        print_menu();
        if (scanf("%d", &choice) != 1)
            ret_code = INVALID_MENU_NUM;
        else if (choice > 9 || choice < 0)
            ret_code = INVALID_MENU_NUM;
        else if (choice == 1)
            ret_code = input_data_from_file(&table);
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

    return ret_code;
}

void output_sort_stats(book_table table)
{
    struct timeval tv_start, tv_stop;
    int64_t key_creation_time = 0;

    int64_t bubble_time_key = 0, qsort_time_key = 0;
    int64_t bubble_time_table = 0, qsort_time_table = 0;

    book_table table_copy = table;

    page_key_table key_table = { 0 };

    gettimeofday(&tv_start, NULL);
    int rc = create_page_key_table(&table, &key_table);
    gettimeofday(&tv_stop, NULL);
    key_creation_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);

    if (rc == OK)
    {
        page_key_table key_table_copy = key_table;

        printf("MEASURING KEY TABLE...\n");
        printf("Please type simple:\n");
        sort_key_table(&key_table, &bubble_time_key, &qsort_time_key, key_creation_time);
        printf("Please type fast:\n");
        sort_key_table(&key_table_copy, &bubble_time_key, &qsort_time_key, key_creation_time);

        printf("MEASURING FULL TABLE...\n");
        printf("Please type simple:\n");
        sort_table_full(&table, &bubble_time_table, &qsort_time_table);
        printf("Please type fast:\n");
        sort_table_full(&table_copy, &bubble_time_table, &qsort_time_table);

        printf("Efficiency results:\n");
        printf("Case       \t\tTable\t\tKey table\n");
        printf("Bubble     \t\t%lld us\t\t%lld us\n", bubble_time_table, bubble_time_key);
        printf("Qsort      \t\t%lld us\t\t%lld us\n", qsort_time_table, qsort_time_key);
        if (qsort_time_table == 0 || qsort_time_key == 0)
            printf("Not enough data for comparison yet!\n");
        else
            printf("Qsort is   \t\t%lldx faster\t\t%lldx faster\n", qsort_time_table / bubble_time_table, qsort_time_key / bubble_time_key);
    }
    else
        printf("No data yet!\n");
}

void output_efficiency_results(book_table table)
{
    struct timeval tv_start, tv_stop;
    int64_t key_creation_time = 0;

    int64_t bubble_time_key = 0, qsort_time_key = 0;
    int64_t bubble_time_table = 0, qsort_time_table = 0;
    int table_storage = 0, key_storage = 0;

    book_table table_copy = table;

    page_key_table key_table = { 0 };

    gettimeofday(&tv_start, NULL);
    int rc = create_page_key_table(&table, &key_table);
    gettimeofday(&tv_stop, NULL);
    key_creation_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
    (tv_stop.tv_usec - tv_start.tv_usec);

    if (rc == OK)
    {
        page_key_table key_table_copy = key_table;

        printf("MEASURING KEY TABLE...\n");
        key_storage = sizeof(key_table);

        printf("Please type simple:\n");
        sort_key_table(&key_table, &bubble_time_key, &qsort_time_key, key_creation_time);

        printf("Please type fast:\n");
        sort_key_table(&key_table_copy, &bubble_time_key, &qsort_time_key, key_creation_time);

        printf("MEASURING FULL TABLE...\n");
        table_storage = sizeof(table);

        printf("Please type simple:\n");
        sort_table_full(&table, &bubble_time_table, &qsort_time_table);

        printf("Please type fast:\n");
        sort_table_full(&table_copy, &bubble_time_table, &qsort_time_table);

        printf("EFFICIENCY TEST RESULTS:\n");
        printf("Case   \t\tTable\t\tKey table\n");
        printf("Bubble \t\t%lld us\t\t%lld us\n", bubble_time_table, bubble_time_key);
        printf("Qsort  \t\t%lld us\t\t%lld us\n", qsort_time_table, qsort_time_key);
        printf("Storage\t\t%d\t\t%d\n", table_storage, key_storage);
    }
    else
        printf("No data yet!\n");
}

void sort_table_key_hub(book_table *table)
{
    page_key_table key_table = { 0 };
    int rc = create_page_key_table(table, &key_table);

    if (rc != OK)
        printf("No books yet!\n");
    else
    {
        sort_key_table(&key_table, NULL, NULL, 0);
        print_table_by_key_table(table, &key_table);
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

void sort_table_full(book_table *table, int64_t *bubble_time_table, int64_t *qsort_time_table)
{
    struct timeval tv_start, tv_stop;

    printf("Choose sorting algorythm [simple/fast]: ");
    char a[MAX_FIELD_LEN + 1];
    if (scanf("%s", a) == 1)
    {
        if (strcmp(a, "simple") == 0)
        {
            gettimeofday(&tv_start, NULL);
            bubble_sort_table(table);
            gettimeofday(&tv_stop, NULL);

            if (bubble_time_table != NULL)
                *bubble_time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else if (strcmp(a, "fast") == 0)
        {
            gettimeofday(&tv_start, NULL);
            qsort(table->data, table->quantity, sizeof(book), compare_books);
            gettimeofday(&tv_stop, NULL);

            if (qsort_time_table != NULL)
                *qsort_time_table = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            printf("No such algorithm!\n");
    }
    else
        printf("Input error!\n");
}

int compare_books(const void *one, const void *two)
{
    book *book1 = (book *)one;
    book *book2 = (book *)two;
    return (book1->pages - book2->pages);
}

void open_sorted_key_table(book_table *table)
{
    page_key_table key_table = { 0 };

    int rc = create_page_key_table(table, &key_table);

    if (rc != OK)
        printf("No books yet!\n");
    else
    {
        printf("The unsorted key table:\n");
        print_key_table(&key_table);

        sort_key_table(&key_table, NULL, NULL, 0);
        printf("The sorted key table:\n");
        print_key_table(&key_table);
    }
}

void sort_key_table(page_key_table *key_table, int64_t *bubble_time_key, int64_t *qsort_time_key, int64_t elapsed_time)
{
    printf("Choose sorting algorythm [simple/fast]: ");
    char a[MAX_FIELD_LEN + 1];
    if (scanf("%s", a) == 1)
    {
        struct timeval tv_start, tv_stop;
        if (strcmp(a, "simple") == 0)
        {
            gettimeofday(&tv_start, NULL);
            bubble_sort_key_table(key_table);
            gettimeofday(&tv_stop, NULL);
            if (bubble_time_key != NULL)
                *bubble_time_key = elapsed_time + (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else if (strcmp(a, "fast") == 0)
        {
            gettimeofday(&tv_start, NULL);
            qsort(key_table->pages, key_table->n, sizeof(short) * 3, compare_key_lines);
            gettimeofday(&tv_stop, NULL);
            if (qsort_time_key != NULL)
                *qsort_time_key = elapsed_time + (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL +
                (tv_stop.tv_usec - tv_start.tv_usec);
        }
        else
            printf("No such algorithm!\n");
    }
    else
        printf("Input error!\n");
}

int compare_key_lines(const void *one, const void *two)
{
    short *line1 = (short *)one;
    short *line2 = (short *)two;
    return (*(line1 + 2) - *(line2 + 2));
}

void bubble_sort_table(book_table *table)
{
    int n = table->quantity;
    for (int i = 0; i < n; i++)
        for (int j = n - 2; j >= i; j--)
            if ((table->data)[j].pages > (table->data)[j + 1].pages)
                swap_books((table->data) + j, (table->data) + j + 1);
}

void swap_books(book *one, book *two)
{
    book temp = *one;
    *one = *two;
    *two = temp;
}

void bubble_sort_key_table(page_key_table *key_table)
{
    int n = key_table->n;
    for (int i = 0; i < n; i++)
        for (int j = n - 2; j >= i; j--)
            if ((key_table->pages)[j][2] > (key_table->pages)[j + 1][2])
                swap_lines(key_table, j, j + 1);
}

void swap_lines(page_key_table *key_table, short int line1, short int line2)
{
    short int i_new = (key_table->pages)[line1][1];
    short int pages = (key_table->pages)[line1][2];

    (key_table->pages)[line1][1] = (key_table->pages)[line2][1];
    (key_table->pages)[line1][2] = (key_table->pages)[line2][2];

    (key_table->pages)[line2][1] = i_new;
    (key_table->pages)[line2][2] = pages;
}

int create_page_key_table(book_table *table, page_key_table *key_table)
{
    int ret_code = OK;

    if (table->quantity == 0)
        ret_code = NO_BOOKS;
    else
    {
        key_table->n = table->quantity;
        for (int i = 0; i < key_table->n; i++)
        {
            (key_table->pages)[i][1] = i;
            (key_table->pages)[i][0] = i;
            (key_table->pages)[i][2] = ((table->data) +  i)->pages;
        }
    }

    return ret_code;    
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

void find_tech_data_by_area(book_table *table)
{
    if (table->quantity == 0)
        printf("No input data yet!\n");
    else
    {
        char fld[MAX_FIELD_LEN + 2];
        fgets(fld, MAX_FIELD_LEN + 2, stdin);

        printf("Input the area: ");
        fgets(fld, MAX_FIELD_LEN + 2, stdin);
        delete_new_str_sym(fld);

        int found_i[MAX_BOOKS_NUM] = { 0 }, n = 0;
        for (int i = 0; i < table->quantity; i++)
        {
            if ((table->data)[i].type == TECHNICAL && strcmp((table->data)[i].spec.tech_info.area, fld) == 0)
                found_i[n++] = i;
        }
        if (n <= 0)
            printf("Nothing found!\n");
        else
        {
            printf("Found:\n");
            for (int in = 0; in < n; in++)
            {
                print_book((table->data) + found_i[in]);
                printf("\n");
            }
        }
    }
}

void delete_line(book_table *table)
{
    if (table->quantity == 0)
        printf("No input data yet!\n");
    else
    {
        char fld[MAX_FIELD_LEN + 2];
        fgets(fld, MAX_FIELD_LEN + 2, stdin);

        printf("\nAllowed field names:\n");
        printf("name, title, publisher, pages, type\n");
        printf("for technical type: area, tech_type, year\n");
        printf("for fiction type: fiction_type\n");
        printf("for children's type: children_type\n\n");

        printf("Input the field: ");
        fgets(fld, MAX_FIELD_LEN + 2, stdin);
        delete_new_str_sym(fld);
        char *fields[] = { "name", "title", "publisher", "pages", "type", "area", 
        "tech_type", "year", "fiction_type", "children_type" };

        if (value_in_mas(fld, fields, 10) == YES)
        {
            char key[MAX_FIELD_LEN + 2];
            printf("Input the key: ");
            fgets(key, MAX_FIELD_LEN + 1, stdin);
            delete_new_str_sym(key);
            
            int found_i[MAX_BOOKS_NUM] = { 0 }, n = 0;
            for (int i = 0; i < table->quantity; i++)
            {
                if (strcmp(fld, "name") == 0 && strcmp((table->data)[i].name, key) == 0)
                    found_i[n++] = i;
                else if (strcmp(fld, "title") == 0 && strcmp((table->data)[i].title, key) == 0)
                    found_i[n++] = i;
                else if (strcmp(fld, "publisher") == 0 && strcmp((table->data)[i].publisher, key) == 0)
                    found_i[n++] = i;
                else if (strcmp(fld, "pages") == 0 && (table->data)[i].pages == str_to_num(key))
                    found_i[n++] = i;
                else if (strcmp(fld, "type") == 0)
                {
                    if (strcmp(key, "technical") == 0 && (table->data)[i].type == TECHNICAL)
                        found_i[n++] = i;
                    if (strcmp(key, "fiction") == 0 && (table->data)[i].type == FICTION)
                        found_i[n++] = i;
                    if (strcmp(key, "children's") == 0 && (table->data)[i].type == CHILDREN)
                        found_i[n++] = i;
                }
                else if (strcmp(fld, "area") == 0 && strcmp((table->data)[i].spec.tech_info.area, key))
                    found_i[n++] = i;
                else if (strcmp(fld, "tech_type") == 0)
                {
                    if (strcmp(key, "state") == 0 && (table->data)[i].spec.tech_info.type == STATE)
                        found_i[n++] = i;
                    if (strcmp(key, "translated") == 0 && (table->data)[i].spec.tech_info.type == TRANSLATED)
                        found_i[n++] = i;
                }
                else if (strcmp(fld, "year") == 0 && (table->data)[i].spec.tech_info.year == str_to_num(key))
                    found_i[n++] = i;
                else if (strcmp(fld, "fiction_type") == 0)
                {
                    if (strcmp(key, "novel") == 0 && (table->data)[i].spec.fiction_info == NOVEL)
                        found_i[n++] = i;
                    if (strcmp(key, "poetry") == 0 && (table->data)[i].spec.fiction_info == FICTION_POETRY)
                        found_i[n++] = i;
                    if (strcmp(key, "play") == 0 && (table->data)[i].spec.fiction_info == PLAY)
                        found_i[n++] = i;
                }
                else if (strcmp(fld, "children_type") == 0)
                {
                    if (strcmp(key, "poetry") == 0 && (table->data)[i].spec.children_info == CHILDREN_POETRY)
                        found_i[n++] = i;
                    if (strcmp(key, "fairy tails") == 0 && (table->data)[i].spec.children_info == FAIRYTAILS)
                        found_i[n++] = i;
                }
            }
            if (n <= 0)
                printf("Nothing found!\n");
            else
            {
                printf("Found these lines: \n");
                for (int i = 0; i < n; i++)
                {
                    print_book((table->data) + found_i[i]);
                    printf("\n");
                }
                for (int i = n - 1; i >= 0; i--)
                {
                    for (int j = found_i[i]; j <= table->quantity - 2; j++)
                        (table->data)[j] = (table->data)[j + 1];
                    (*table).quantity -= 1;
                }
                printf("Deleted!\n");
                printf("Do you want to output the table? [Y/N]: ");
                char a;
                if (scanf("%c", &a) == 1 && a == 'Y')
                    print_book_table(table);
            }
        }
        else
            printf("No such field!\n");
    }
}

void delete_new_str_sym(char *str)
{
    while (*(++str));
    str--;
    *str = '\0';
}

int value_in_mas(char *value, char **mas, int n)
{
    int ret_code = NO;
    for (int i = 0; i < n && ret_code == NO; i++)
        if (strcmp(value, mas[i]) == 0)
            ret_code = YES;

    return ret_code;
}

void add_line(book_table *table)
{
    if (table->quantity == 0)
        printf("No input data yet!\n");
    else
    {
        book temp_book = { 0 };

        for (int i = 0; i < 1; i++)
        {
            char temp[MAX_FIELD_LEN + 2];
            fgets(temp, MAX_FIELD_LEN + 2, stdin);
            printf("Input name: ");
            fgets(temp, MAX_FIELD_LEN + 2, stdin);
            if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
            {
                printf("Wrong input!\n");
                break;
            }
            else
                strncpy(temp_book.name, temp, strlen(temp) - 1);
            
            strcpy(temp, "0");
            printf("Input title: ");
            fgets(temp, MAX_FIELD_LEN + 2, stdin);
            if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
            {
                printf("Wrong input!\n");
                break;
            }
            else
                strncpy(temp_book.title, temp, strlen(temp) - 1);
            
            strcpy(temp, "0");
            printf("Input publisher: ");
            fgets(temp, MAX_FIELD_LEN + 2, stdin);
            if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
            {
                printf("Wrong input!\n");
                break;
            }
            else
                strncpy(temp_book.publisher, temp, strlen(temp) - 1);
            
            strcpy(temp, "0");
            printf("Input pages: ");
            fgets(temp, MAX_FIELD_LEN + 2, stdin);
            if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN || str_to_num(temp) > 30000 || str_to_num(temp) <= 0)
            {
                printf("Wrong input!\n");
                break;
            }
            else
                temp_book.pages = str_to_num(temp);

            strcpy(temp, "0");
            printf("Input book type [technical / ficition / children's]: ");
            fgets(temp, MAX_FIELD_LEN + 2, stdin);
            if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
            {
                printf("Wrong input!\n");
                break;
            }
            else if (strcmp(temp, "technical\n") == 0)
            {
                temp_book.type = TECHNICAL;
                strcpy(temp, "0");
                printf("Input area: ");
                fgets(temp, MAX_FIELD_LEN + 2, stdin);
                if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
                { 
                    printf("Wrong input!\n");
                    break;
                }
                else
                    strncpy(temp_book.spec.tech_info.area, temp, strlen(temp) - 1);
                
                strcpy(temp, "0");
                printf("Input type [state / translated]: ");
                fgets(temp, MAX_FIELD_LEN + 2, stdin);
                if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
                {
                    printf("Wrong input!\n");
                    break;
                }
                else if (strcmp(temp, "state\n") == 0)
                    temp_book.spec.tech_info.type = STATE;
                else if (strcmp(temp, "translated\n") == 0)
                    temp_book.spec.tech_info.type = TRANSLATED;
                else
                {
                    printf("Wrong input!\n");
                    break;
                }
                    
                strcpy(temp, "0");
                printf("Input year: ");
                fgets(temp, MAX_FIELD_LEN + 2, stdin);
                if (string_is_not_empty(temp) == NO || strlen(temp) > MAX_FIELD_LEN || str_to_num(temp) > 2021 || str_to_num(temp) <= 0)
                {
                    printf("Wrong input!\n");
                    break;
                }
                else
                    temp_book.spec.tech_info.year = str_to_num(temp);
            }
            else if (strcmp(temp, "fiction\n") == 0)
            {
                temp_book.type = FICTION;
                strcpy(temp, "0");
                printf("Input type [novel / poetry / translated]: ");
                fgets(temp, MAX_FIELD_LEN + 2, stdin);
                if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
                {
                    printf("Wrong input!\n");
                    break;
                }
                else if (strcmp(temp, "novel\n") == 0)
                    temp_book.spec.fiction_info = NOVEL;
                else if (strcmp(temp, "poetry\n") == 0)
                    temp_book.spec.fiction_info = FICTION_POETRY;
                else if (strcmp(temp, "play\n") == 0)
                    temp_book.spec.fiction_info = PLAY;
                else
                {
                    printf("Wrong input!\n");
                    break;
                }
            }
            else if (strcmp(temp, "children's\n") == 0)
            {
                temp_book.type = CHILDREN;
                strcpy(temp, "0");
                printf("Input type [poetry / fairy tails]: ");
                fgets(temp, MAX_FIELD_LEN + 2, stdin);
                if (string_is_not_empty(temp) == NO || strlen(temp) - 1 > MAX_FIELD_LEN)
                {
                    printf("Wrong input!\n");
                    break;
                }
                else if (strcmp(temp, "fairy tails\n") == 0)
                    temp_book.spec.children_info = FAIRYTAILS;
                else if (strcmp(temp, "poetry\n") == 0)
                    temp_book.spec.children_info = CHILDREN_POETRY;
                else
                {
                    printf("Wrong input!\n");
                    break;
                }
            }
            else
            {
                printf("Wrong input!\n");
                break;
            }
            (table->data)[table->quantity] = temp_book;
            (*table).quantity += 1;
            printf("Do you want to output the table? [Y/N]: ");
            char a;
            if (scanf("%c", &a) == 1 && a == 'Y')
                print_book_table(table);
        }
    }
}

int input_data_from_file(book_table *table)
{
    int ret_code = OK;
    if (table->quantity != 0)
        printf("You already have input another file!\n\n");
    else
    {
        if (table->quantity != 0)
            printf("You already have data!\n");
        else
        {
            printf("Input the text file name: ");
            char filename[MAX_STR_LEN + 1];
            if (scanf("%s", filename) != 1)
                ret_code = WRONG_FILE_NAME;
            else
            {
                FILE *f = fopen(filename, "r");
                if (f == NULL)
                    ret_code = WRONG_FILE_NAME;
                else
                {
                    int n = count_file_len(f);
                    ret_code = check_file(f, n);
                    if (ret_code == OK)
                    {
                        for (int i = 0; i < n; i++)
                        {
                            char temp[MAX_LINE_LEN + 1];
                            fgets(temp, MAX_LINE_LEN + 1, f);
                            book temp_line = input_line(temp);
                            strncpy(temp, "0", 2);

                            (*table).data[i] = temp_line;
                            (*table).quantity += 1;
                        }
                    }
                    print_book_table(table);
                    fclose(f);
                }
            }
        }
    }
    return ret_code;
}

void print_book(book *temp)
{
    printf("%s\t", temp->name);
    printf("%s\t", temp->title);
    printf("%s\t", temp->publisher);
    printf("%d\t", temp->pages);
    if (temp->type == TECHNICAL)
        printf("technical\t");
    else if (temp->type == FICTION)
        printf("fiction\t\t");
    else
        printf("children's\t");
    if (temp->type == TECHNICAL)
    {
        printf("%s\t", temp->spec.tech_info.area);
        if (temp->spec.tech_info.type == STATE)
            printf("state\t");
        else
            printf("translated\t");
        printf("%d\t",  temp->spec.tech_info.year);
    }
    else if (temp->type == FICTION)
    {
        if (temp->spec.fiction_info == FICTION_POETRY)
            printf("poetry\t");
        else if (temp->spec.fiction_info == PLAY)
            printf("play\t");
        else
            printf("novel\t");
    }
    else if (temp->type == CHILDREN)
    {
        if (temp->spec.children_info == CHILDREN_POETRY)
            printf("poetry\t");
        else
            printf("fairy tails\t");
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

book input_line(char *line)
{
    book temp = { 0 };
    char *fields[MAX_FIELDS_NUM + 1];
    create_mas_of_words(line, fields, MAX_FIELDS_NUM + 1, "\t\n");
    strncpy(temp.name, fields[0], MAX_FIELD_LEN + 1);
    strncpy(temp.title, fields[1], MAX_FIELD_LEN + 1);
    strncpy(temp.publisher, fields[2], MAX_FIELD_LEN + 1);
    temp.pages = str_to_num(fields[3]);
    if (strcmp(fields[4], "technical") == 0)
    {
        temp.type = TECHNICAL;
        strcpy(temp.spec.tech_info.area, fields[5]);
        temp.spec.tech_info.type = (strcmp(fields[6], "state") == 0) ? STATE : TRANSLATED;
        temp.spec.tech_info.year = str_to_num(fields[7]);
    }
    else if (strcmp(fields[4], "children's") == 0)
    {
        temp.type = CHILDREN;
        temp.spec.children_info = (strcmp(fields[5], "poetry") == 0) ? CHILDREN_POETRY : FAIRYTAILS;
    }
    else
    {
        temp.type = FICTION;
        if (strcmp(fields[5], "novel") == 0)
            temp.spec.fiction_info = NOVEL;
        if (strcmp(fields[5], "play") == 0)
            temp.spec.fiction_info = PLAY;
        if (strcmp(fields[5], "poetry") == 0)
            temp.spec.fiction_info = FICTION_POETRY;
    }
    return temp;
}

int check_file(FILE *f, int n)
{
    rewind(f);
    int ret_code = OK;
    if (n < 1 || n > 101)
        ret_code = BROKEN_FILE;
    else
    {
        for (int i = 0; i < n && ret_code == OK; i++)
        {
            char temp_s[MAX_LINE_LEN + 1];
            fgets(temp_s, MAX_LINE_LEN + 1, f);
            if (check_string(temp_s) != OK)
                ret_code = BROKEN_FILE;
        }
    }
    rewind(f);

    return ret_code;
}

int check_string(char *string)
{
    int ret_code = OK;
    char *fields[MAX_FIELDS_NUM + 1];
    int fields_num = create_mas_of_words(string, fields, MAX_FIELDS_NUM + 1, "\t\n");
    if (fields_num != 8 && fields_num != 6)
        ret_code = BROKEN_FILE;
    else
    {
        for (int i = 0; i < fields_num && ret_code == OK; i++)
            if (strlen(fields[i]) > MAX_FIELD_LEN)
                ret_code = BROKEN_FILE;
    }
    if (ret_code == OK)
    {
        if (str_to_num(fields[3]) > 30000 || str_to_num(fields[3]) < 1)
            ret_code = BROKEN_FILE;
        else if (strncmp(fields[4], "technical", MAX_FIELD_LEN + 1) != 0 && 
        strncmp(fields[4], "fiction", MAX_FIELD_LEN + 1) != 0 && 
        strncmp(fields[4], "children's", MAX_FIELD_LEN + 1) != 0)
            ret_code = BROKEN_FILE;
        else if (strncmp(fields[4], "technical", MAX_FIELD_LEN + 1) == 0 &&
        (fields_num != 8 || str_to_num(fields[7]) > 2021 || str_to_num(fields[7]) < 0))
            ret_code = BROKEN_FILE;
        else if (strncmp(fields[4], "fiction", MAX_FIELD_LEN + 1) == 0 && 
        (fields_num != 6 && strncmp(fields[5], "novel", MAX_FIELD_LEN + 1) != 0 && 
        strncmp(fields[5], "play", MAX_FIELD_LEN + 1) != 0 && 
        strncmp(fields[5], "poetry", MAX_FIELD_LEN + 1) != 0))
            ret_code = BROKEN_FILE;
        else if (strncmp(fields[4], "children's", MAX_FIELD_LEN + 1) == 0 && 
        (fields_num != 6 && strncmp(fields[5], "fairy tails", MAX_FIELD_LEN + 1) != 0 && 
        strncmp(fields[5], "poetry", MAX_FIELD_LEN + 1) != 0))
            ret_code = BROKEN_FILE;
    }

    return ret_code;
}

int str_to_num(char *str)
{
    int n = 0;
    while (*str && *str != '\n')
        n = n * 10 + *(str++) - ASCII_NUM_DIFF;
    return n;
}

int create_mas_of_words(char *string, char **mas, int max_number, char *delims)
{
    int cnt = 0;
    char *ch = strtok(string, delims);
    while (ch && cnt < max_number)
    {
        mas[cnt++] = ch;  // записывается адрес начала слова
        ch = strtok(NULL, delims);
    }
    return cnt;
}

int count_file_len(FILE *f)
{
    int n = 0;
    int empty_string = NO;
    while (!feof(f) && n < 102)
    {
        char temp[MAX_LINE_LEN + 1];
        fgets(temp, MAX_LINE_LEN + 1, f);
        int sc = string_is_not_empty(temp);
        if (sc == YES && empty_string == YES)
            n = BROKEN_FILE;
        else if (sc == NO)
            empty_string = YES;
        else
            n++;
        strcpy(temp, "\n");
    }
    rewind(f);

    return n;
}

int string_is_not_empty(char *string)
{
    char spaces[] = "\t \n'\",.!?-+:;*_@#$\\<>";
    short len_spaces = strlen(spaces);
    int spc = 0;
    while (*string)
    {
        int found = NO;
        for (int i = 0; i < len_spaces; i++)
            if (*string == spaces[i])
                found = YES;
        if (found != YES)
            spc += 1;
        string++;
    }

    return spc == 0 ? NO : YES;
}

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