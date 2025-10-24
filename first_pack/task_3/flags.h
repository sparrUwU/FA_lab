#ifndef FLAGS_H
#define FLAGS_H

typedef enum status_code {
    OK,
    OVERFLOW_ERROR, 
    INPUT_ERROR, 
    NOT_OK
} status_code;

typedef struct {
    char solutions[256];
} solution_result;

status_code q_equation(double epsilon, double a, double b, double c, solution_result results[6]);
status_code m_is_multiples(const char *dividend, const char *divisor, char *answer);
status_code t_side_of_triangle(double epsilon, double a, double b, double c, int *is_right_triangle);

int double_equals(double a, double b, double epsilon);
solution_result roots_of_equation(double epsilon, double a, double b, double c);

#endif