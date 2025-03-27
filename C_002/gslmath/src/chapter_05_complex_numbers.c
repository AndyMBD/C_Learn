#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_05_complex_numbers.h"
// #include "gsl_math.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>

void chapter_05_complex_numbers();

void chapter_05_complex_numbers_main()
{
    chapter_05_complex_numbers();

}
void chapter_05_complex_numbers()
{
    gsl_complex x, y;
    GSL_REAL(x) = 4;
    GSL_IMAG(x) = 2;
    GSL_REAL(y) = GSL_REAL(x);
    GSL_IMAG(y) = GSL_REAL(x);
    y = gsl_complex_polar(1.0, M_PI_4);
    printf("%-10s = %.12e\n", "gsl_complex_abs(x)",    gsl_complex_abs(y));
    printf("%-10s = %.12e\n", "gsl_complex_arg(x)",    gsl_complex_arg(y)/M_PI*180);

}
