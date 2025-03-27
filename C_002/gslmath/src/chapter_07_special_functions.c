#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_07_special_functions.h"
// #include "gsl_math.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf_bessel.h>
void gsl_math_bessel();

void chapter_07_special_functions_main()
{
    gsl_math_bessel();
}
void gsl_math_bessel()
{

    double x = 5.0;
    double y = gsl_sf_bessel_J0(x);
    // printf("*--------------------------------------------*\n");
    printf("gsl_sf_bessel_J0\n");
    printf("----------------------------------------------------\n \n");
    printf("J0(%g) = %.18e\n", x, y);
    printf("----------------------------------------------------\n \n");
    // printf("*--------------------------------------------*\n \n");
}