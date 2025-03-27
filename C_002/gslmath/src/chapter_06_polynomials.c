#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_06_polynomials.h"
// #include "gsl_math.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_errno.h>

void gsl_math_poly();
void chapter_06_polynomials_main()
{
    gsl_math_poly();

}
void gsl_math_poly()
{
    double x = 5.0;
    int i;
    /* coefficients of P(x) = -1 + x^5 */
    double a[6] = {-1, 0, 0, 0, 0, 1};
    double z[10];
    gsl_poly_complex_workspace *w = gsl_poly_complex_workspace_alloc(6);
    gsl_poly_complex_solve(a, 6, w, z);
    // printf("*--------------------------------------------*\n");
    printf("gsl_poly_complex_solve\n");
    printf("----------------------------------------------------\n");
    gsl_poly_complex_workspace_free(w);
    for (i = 0; i < 5; i++)
    {
        printf("z%d = %+.18f %+.18f\n",
               i, z[2 * i], z[2 * i + 1]);
    }
    printf("----------------------------------------------------\n");
    // printf("*--------------------------------------------*\n");
}
