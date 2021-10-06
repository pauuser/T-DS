#include "operations.h"
#include "input.h"
#include "output.h"

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
    else if (table->quantity == 100)
        printf("Table overflow!\n");
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
