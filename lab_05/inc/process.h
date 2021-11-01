#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-4

int arr_process_modeling(int requests_num, 
                            double min_t1, double max_t1, 
                                double min_t2, double max_t2,
                                    double min_pr1, double max_pr1,
                                        double min_pr2, double max_pr2);

int list_process_modeling(int requests_num, 
                            double min_t1, double max_t1, 
                                double min_t2, double max_t2,
                                    double min_pr1, double max_pr1,
                                        double min_pr2, double max_pr2);