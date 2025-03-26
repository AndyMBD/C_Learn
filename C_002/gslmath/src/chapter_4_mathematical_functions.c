#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_4_mathematical_functions.h"
// #include "gsl_math.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_complex.h>
#include <gsl/gsl_complex_math.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_errno.h>

void chapter_4_1_Mathematical_Constants();
void chapter_5_complex_numbers();
void chapter_6_polynomials();
uint32_t chapter_4_main()
{
    // chapter_4_1_Mathematical_Constants();
    chapter_5_complex_numbers();
    // chapter_6_polynomials();
}
void chapter_4_1_Mathematical_Constants()
{
    printf("%-10s = %.12e\n", "M_E",        M_E);
    printf("%-10s = %.12e\n", "M_LOG2E",    M_LOG2E);
    printf("%-10s = %.12e\n", "M_LOG10E",   M_LOG10E);
    printf("%-10s = %.12e\n", "M_SQRT2",    M_SQRT2);
    printf("%-10s = %.12e\n", "M_SQRT1_2",  M_SQRT1_2);
    printf("%-10s = %.12e\n", "M_SQRT3",    M_SQRT3);
    printf("%-10s = %.12e\n", "M_PI",       M_PI);
    printf("%-10s = %.12e\n", "M_PI_2",     M_PI_2);
    printf("%-10s = %.12e\n", "M_PI_4",     M_PI_4);
    printf("%-10s = %.12e\n", "M_SQRTPI",   M_SQRTPI);
    printf("%-10s = %.12e\n", "M_2_SQRTPI", M_2_SQRTPI);
    printf("%-10s = %.12e\n", "M_1_PI",     M_1_PI);
    printf("%-10s = %.12e\n", "M_2_PI",     M_2_PI);
    printf("%-10s = %.12e\n", "M_LN10",     M_LN10);
    printf("%-10s = %.12e\n", "M_LN2",      M_LN2);
    printf("%-10s = %.12e\n", "M_LNPI",     M_LNPI);
    printf("%-10s = %.12e\n", "M_EULER",    M_EULER);
    // printf("\n\n");
    printf("\n");
    printf("%-10s \n", "*******");
    
    printf("%-10s = %.12e\n", "GSL_POSINF",    GSL_POSINF);
    printf("%-10s = %.12e\n", "GSL_NEGINF",    GSL_NEGINF);
    printf("%-10s = %.12e\n", "GSL_NAN",       GSL_NAN);
    
    printf("\n");
    // printf("\n\n");
    printf("%-10s \n", "*******");
    printf("%-10s = %.12e\n", "gsl_log1p",  gsl_log1p(M_E));
    printf("%-10s = %.12e\n", "gsl_expm1",  gsl_expm1(M_E));
    printf("%-10s = %.12e\n", "gsl_hypot",  gsl_hypot(M_E,M_E));
    printf("%-10s = %.12e\n", "gsl_hypot3", gsl_hypot3(M_E, M_E, M_E));
    printf("%-10s = %.12e\n", "gsl_acosh",  gsl_acosh(M_PI));
    printf("%-10s = %.12e\n", "gsl_asinh",  gsl_asinh(M_PI));
    printf("%-10s = %.12e\n", "gsl_atanh",  gsl_atanh(M_PI));
    printf("%-10s = %.12e\n", "gsl_ldexp",  gsl_ldexp(M_E, 1));
    // printf("%-10s = %.12e\n", "gsl_frexp",  gsl_frexp(1.0,1));
}
void chapter_5_complex_numbers()
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
void chapter_6_polynomials()
{

}