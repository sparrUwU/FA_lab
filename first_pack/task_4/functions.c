#include <math.h>
#include "functions.h"

#define MAX_ITER 1000000

double e_by_limit(double eps) {
    double prev, curr = 1.0;
    int n = 1;

    do {
        prev = curr;
        curr = pow(1.0 + 1.0/n, n);
        n++;
    } while (fabs(curr - prev) > eps && n < MAX_ITER);

    return curr;
}

double e_by_series(double eps) {
    double sum = 1.0, term = 1.0;
    int n = 1;

    while (term > eps && n < MAX_ITER) {
        term /= n;
        sum += term;
        n++;
    }

    return sum;
}

double e_by_equation(double eps) {
    double x = 2.0, prev;

    do {
        prev = x;
        x = prev - (log(prev) - 1) * prev;
    } while (fabs(x - prev) > eps);

    return x;
}

double pi_by_limit(double eps) {
    double prev, curr;
    
    double factorial_n = 1.0;
    double factorial_2n = 2.0;
    double power_2n = 2.0;
    
    double numerator = pow(power_2n * factorial_n, 4);
    double denominator = pow(factorial_2n, 2);
    curr = numerator / denominator;

    int n = 2;

    do {
        prev = curr;
        factorial_n *= n;

        factorial_2n *= (2 * n);
        
        power_2n *= 2.0;

        double numerator = pow(power_2n * factorial_n, 4);
        double denominator = n * pow(factorial_2n, 2);
        curr = numerator / denominator;
        
        n++;
    } while ((fabs(curr - prev) > eps && n < MAX_ITER));
    
    return curr;
}

double pi_by_series(double eps) {
    double sum = 0.0, term;
    int n = 1;

    do {
        term = (n % 2 == 0 ? -1.0 : 1.0) / (2 * n - 1);
        sum += term;
        n++;
    } while (fabs(term) > eps && n < MAX_ITER);

    return 4 * sum;
}


double pi_by_equation(double eps) {
    double x = 3.0;
    double prev;
    int iter = 0;
    
    do {
        prev = x;
        x = prev + (cos(prev) + 1 ) / sin(prev);
        iter++;
    } while (fabs(x - prev) > eps && iter < MAX_ITER);
    
    return x;
}

double ln2_by_limit(double eps) {
    double prev, curr;
    curr = pow(2, 1.0) - 1;
    int n = 2;

    do {
        prev = curr;
        curr = n * (pow(2, 1.0/n) - 1);
        n++;
    } while (fabs(curr - prev) > eps && n < MAX_ITER);

    return curr;
}

double ln2_by_series(double eps) {
    double sum = 0.0, term;
    int n = 1;
    do {
        term = (n % 2 == 0 ? -1.0 : 1.0) / n;
        sum += term;
        n++;
    } while (fabs(term) > eps && n < MAX_ITER);
    return sum;
}

double ln2_by_equation(double eps) {
    double x = 0.7, prev;
    do {
        prev = x;
        x = prev - (pow(e_by_limit(eps), prev) - 2) / exp(prev); // исправить е
    } while (fabs(x - prev) > eps);
    return x;
}

// фывфыв
double factorial(int n) {
    double result = 1.0;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int is_prime(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}
// фыаыфав

double sqrt2_by_iteration(double eps) {
    double x = 0.5;
    double prev;
    int n = 0;
    
    do {
        prev = x;
        x = (x - (x * x) / 2.0) + 1.0;
        n++;
    } while (fabs(x - prev) > eps && n < MAX_ITER);
    
    return x;
}

double sqrt2_by_product(double eps) {
    double product = 1.0;
    double prev;
    int k = 2;
    
    do {
        prev = product;
        product *= pow(2.0, pow(2.0, -k));
        k++;
    } while (fabs(product - prev) > eps && k < MAX_ITER);
    
    return product;
}

double sqrt2_by_equation(double eps) {
    double x = 1.5;
    double prev;
    
    do {
        prev = x;
        x = x - (x * x - 2.0) / (2.0 * x);
    } while (fabs(x - prev) > eps);
    
    return x;
}