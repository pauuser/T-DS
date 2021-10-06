#include "input.h"
#include "output.h"

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
                        print_book_table(table);
                    }
                    fclose(f);
                }
            }
        }
    }
    return ret_code;
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
    if (n < 40 || n > 100)
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
    while (*str && *str >= 32)
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