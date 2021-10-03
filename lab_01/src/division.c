#include "common.h"
#include "correct_check.h"
#include "input.h"
#include "division.h"
#include "output.h"

long_num divide_float_by_int(long_num *real, long_num *integer)
{
    char new_mantissa[MANTISSA_SIZE + 1] = { 0 };
    int added_exp = cnt_nums_after_dot(real->mantissa);

    create_multiplied_mantissa(real->mantissa, new_mantissa);
    char div_result[MANTISSA_SIZE + 1] = { 0 };
    divide_a_by_b(new_mantissa, integer->mantissa, &added_exp, div_result);

    long_num result = { 0 };
    strncpy(result.mantissa, div_result, MANTISSA_SIZE);
    result.sign_mant = decide_mant_sign(real, integer);
    result.exp = real->exp - added_exp;

    return result;
}

int cnt_nums_after_dot(char *mnt)
{
    int cnt = 0;
    while (*mnt != '.' && *mnt)
        mnt++;
    while (*mnt++)
        cnt++;
    return cnt == 0 ? 0 : (cnt - 1);
}

int divide_a_by_b(char *a, char *b, int *exp, char *result)
{
    int ret_code = OK;
    delete_zeros(a);
    while (compare_nums(a, b) < 0)
    {
        char zero[2] = "0";
        strcat(a, zero);
        *exp = *exp + 1;
    }
    char temp_div[MANTISSA_SIZE + 1] = { '0' };
    // находим первое деление
    int i = 0;
    while (*(a + i) != '\0' && compare_nums(temp_div, b) < 0 && strlen(temp_div) <= strlen(b))
    {
        temp_div[i] = *(a + i);
        i++;
    }
    temp_div[i] = '\0';
    // начинаем делить
    int meaning_nums = 0;
    while (meaning_nums <= MANTISSA_SIZE - 2 && !(*temp_div == '0' && i >= strlen(a)))
    {
        // we have temp_div and b
        // выбрали цифру
        int n = choose_closest_num(temp_div, b);
        result[meaning_nums++] = n + ASCII_NUM_DIFF; // записали результат
        // вычесть получить новый temp_div, снести следующую цифру
        char mult_res[MANTISSA_SIZE + 1];
        char minus_res[MANTISSA_SIZE + 1];
        multiply_a_by_b(b, n, mult_res);
        a_minus_b(temp_div, mult_res, minus_res);
        strcpy(temp_div, minus_res);
        if (meaning_nums == MANTISSA_SIZE - 2)
        {
            char new_num[2] = { '0', '\0' };
            strcat(temp_div, new_num);
            delete_zeros(temp_div);
        }
        else if (i >= strlen(a))
        {
            char new_num[2] = { '0', '\0' };
            strcat(temp_div, new_num);
            delete_zeros(temp_div);
            *exp = *exp + 1;
        }
        else
        {
            char new_num[2] = { *(a + i++), '\0' };
            strcat(temp_div, new_num);
            delete_zeros(temp_div);
        }
        // повторить
    }
    if (strlen(result) > MANTISSA_SIZE - 2)
    {
        ret_code = long_num_apporox(result, exp);
        *exp = *exp - 1;
    }
    if (meaning_nums < MANTISSA_SIZE - 2)
        *exp = *exp - 1;
    return ret_code;
}

int choose_closest_num(char *temp, char *del)
{
    char mult_res[MANTISSA_SIZE + 1] = { 0 };
    char minus_res[MANTISSA_SIZE + 1] = { 0 };
    int result = 1;
    for (int i = 0; i <= 9; i++)
    {
        multiply_a_by_b(del, i, mult_res);
        a_minus_b(temp, mult_res, minus_res);
        result = i;
        if (compare_nums(mult_res, temp) <= 0 && compare_nums(minus_res, del) < 0)
            break;
    }
    return result;
}

void create_multiplied_mantissa(char *str, char *new)
{
    while (*str == '0' && *str)
        str++;
    int i = 0;
    while (*str)
    {
        if (*str != '.')
            new[i++] = *str;
        str++;
    }
}

void multiply_a_by_b(char *a, int b, char *result)
{
    // assuming that 0 <= b <= 9
    int to_remember = 0;
    int len = strlen(a), temp;
    result[len] = '\0';
    for (int i = len - 1; i >= 0; i--)
    {
        temp = a[i] - ASCII_NUM_DIFF;
        result[i] = (temp * b + to_remember) % 10 + ASCII_NUM_DIFF;
        to_remember = (temp * b + to_remember) / 10;
    }
    if (to_remember != 0)
    {
        char copy[MANTISSA_SIZE + 1];
        strcpy(copy, result);
        strcpy(result + 1, copy);
        *result = to_remember + ASCII_NUM_DIFF;
    }
}

void delete_new_str_sym(char *str)
{
    while (*(++str));
    str--;
    *str = '\0';
}


void a_minus_b(char *a, char *b, char *result)
{
    // assuming that a > b
    char b_corrected[MANTISSA_SIZE] = { '\0' };
    if (strlen(a) > strlen(b))
    {
        // выравнивание разрядной сетки
        for (int i = 0; i < (strlen(a) - strlen(b)); i++)
            strcat(b_corrected, "0");
        strncat(b_corrected, b, MANTISSA_SIZE - strlen(a) + strlen(b));
    }
    else
        strncpy(b_corrected, b, MANTISSA_SIZE);
    strncpy(result, a, MANTISSA_SIZE);
    int len = strlen(a), borrow = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        a[i] = a[i] - ASCII_NUM_DIFF;
        b_corrected[i] -= ASCII_NUM_DIFF;
        if (borrow == 0)
        {
            if (a[i] < b_corrected[i])
            {
                result[i] = 10 - b_corrected[i] + a[i];
                borrow = 1;
            }
            else
                result[i] = a[i] - b_corrected[i];
        }
        else
        {
            if (a[i] == 0)
                result[i] = 9 - b_corrected[i];
            else if (a[i] - 1 < b_corrected[i])
                result[i] = 10 - b_corrected[i] + a[i] - 1;
            else
            {
                result[i] = a[i] - 1 - b_corrected[i];
                borrow = 0;
            }
        }
        result[i] = result[i] + ASCII_NUM_DIFF;
        a[i] = a[i] + ASCII_NUM_DIFF;
    }
    delete_zeros(result);
}

void delete_zeros(char *str)
{
    char *temp_p = str;
    while (*str == '0' && *(str + 1) != '\0')
    {
        while (*(temp_p + 1))
        {
            *temp_p = *(temp_p + 1);
            temp_p++;
        }
        *temp_p = '\0';
        temp_p = str;
    }
}

char decide_mant_sign(long_num *a, long_num *b)
{
    char sign;
    if (a->sign_mant == '+' && b->sign_mant == '-')
        sign = '-';
    else if (a->sign_mant == '-' && b->sign_mant == '+')
        sign = '-';
    else
        sign = '+';
    return sign;
}


int compare_nums(char *a, char *b)
{
    int n = 0;
    if (*a == '0' && *b != '0')
        n = -1;
    else if (*a != '0' && *b == '0')
        n = 1;
    else if (strlen(a) > strlen(b))
        n = 1;
    else if (strlen(a) < strlen(b))
        n = -1;
    else
        n = strcmp(a, b);
    return n;
}

void reformat_long_num(long_num *num)
{
    char copy[MANTISSA_SIZE + 3];
    strcpy(copy, num->mantissa);
    (*num).exp = num->exp + strlen(copy);
    char add_str[3] = "0.";
    delete_ending_zeroes(copy);
    strcpy(num->mantissa, add_str);
    strcpy(num->mantissa + 2, copy);
}

int long_num_apporox(char *num, int *exp)
{
    int ret_code = OK;
    int len = MANTISSA_SIZE - 2;
    int i = len;
    int to_plus = 0;
    if (num[i] >= 5 + ASCII_NUM_DIFF)
    {
        if (num[i - 1] != 9 + ASCII_NUM_DIFF)
            num[i - 1] = num[i - 1] + 1;
        else
        {
            i--;
            to_plus = 1;
            while (i >= 0 && to_plus == 1)
            {
                if (num[i] == 9 + ASCII_NUM_DIFF)
                {
                    num[i] = '0';
                    to_plus = 1;
                }
                else
                {
                    num[i] = num[i] + 1;
                    to_plus = 0;
                }
                i--;
            }
        }
        if (to_plus == 1)
        {
            *exp -= 1;
            num[0] = '1';
        }
    }
    num[MANTISSA_SIZE - 2] = '\0';
    return ret_code;
}

void delete_ending_zeroes(char *mantissa)
{
    while (*(++mantissa));
    mantissa--;
    while (*mantissa == '0' && *mantissa)
    {
        *mantissa = '\0';
        mantissa--;
    }
}
