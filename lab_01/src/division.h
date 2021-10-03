#ifndef H_DIVISION_FUNC
#define H_DIVISION_FUNC

long_num divide_float_by_int(long_num *real, long_num *integer);

int cnt_nums_after_dot(char *mnt);

int divide_a_by_b(char *a, char *b, int *exp, char *result);

int choose_closest_num(char *temp, char *del);

void create_multiplied_mantissa(char *str, char *new);

void multiply_a_by_b(char *a, int b, char *result);

void delete_new_str_sym(char *str);

void a_minus_b(char *a, char *b, char *result);

void delete_zeros(char *str);

char decide_mant_sign(long_num *a, long_num *b);

int compare_nums(char *a, char *b);

void reformat_long_num(long_num *num);

int long_num_apporox(char *num, int *exp);

void delete_ending_zeroes(char *mantissa);

#endif
