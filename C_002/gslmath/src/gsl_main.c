#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "gsl_main.h"
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_movstat.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_filter.h>
void gsl_math_poly();
void gsl_math_pow();
void gsl_math_bessel();
void gsl_math_movstat(void);
int jac(double t, const double y[], double *dfdy,double dfdt[], void *params);
int func(double t, const double y[], double f[],void *params);
int gsl_odeiv2_Test_1(void);
int gsl_odeiv2_Test_2(void);
uint8_t gsl_Gaussian_Example_1();
void gsl_math_main()
{
    // gsl_math_pow();
    // gsl_math_bessel();
    // gsl_math_poly();
    // gsl_math_movstat();
    // gsl_odeiv2_Test_1();
    gsl_Gaussian_Example_1();
    // gsl_odeiv2_Test_2();
}
void gsl_math_pow()
{
    double x = 5.0;
    double y = gsl_pow_4(3.141); /* compute 3.141**4 */
    // printf("*--------------------------------------------*\n");
    printf("gsl_pow_4\n");
    printf("----------------------------------------------------\n \n");
    printf("J0(%g) = %.18e\n", x, y);
    printf("----------------------------------------------------\n \n");
    // printf("*--------------------------------------------*\n \n");
}
uint8_t gsl_Gaussian_Example_1()
{
    FILE *output_file;
    const size_t N = 500; /* length of time series */
    const size_t K = 51; /* window size */
    const double alpha[3] = { 0.5, 3.0, 10.0 }; /* alpha values */
    gsl_vector *x = gsl_vector_alloc(N); /* input vector */
    gsl_vector *y1 = gsl_vector_alloc(N); /* filtered output vector for alpha1 */
    gsl_vector *y2 = gsl_vector_alloc(N); /* filtered output vector for alpha2 */
    gsl_vector *y3 = gsl_vector_alloc(N); /* filtered output vector for alpha3 */
    gsl_vector *k1 = gsl_vector_alloc(K); /* Gaussian kernel for alpha1 */
    gsl_vector *k2 = gsl_vector_alloc(K); /* Gaussian kernel for alpha2 */
    gsl_vector *k3 = gsl_vector_alloc(K); /* Gaussian kernel for alpha3 */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    gsl_filter_gaussian_workspace *gauss_p = gsl_filter_gaussian_alloc(K);
    size_t i;
    double sum = 0.0;
    /* generate input signal */
    for (i = 0; i < N; ++i)
    {
        double ui = gsl_ran_gaussian(r, 1.0);
        sum += ui;
        gsl_vector_set(x, i, sum);
    }
    /* compute kernels without normalization */
    gsl_filter_gaussian_kernel(alpha[0], 0, 0, k1);
    gsl_filter_gaussian_kernel(alpha[1], 0, 0, k2);
    gsl_filter_gaussian_kernel(alpha[2], 0, 0, k3);
    /* apply filters */
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[0], 0, x, y1, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[1], 0, x, y2, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha[2], 0, x, y3, gauss_p);
    /* print kernels */
   #if 1
   // Open file for writing at the beginning
    char *Gaussian_kernels_file = "Gaussian_kernels.dat";
    remove(Gaussian_kernels_file);
    output_file = fopen(Gaussian_kernels_file, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file!\n");
        return 1;
    }
    fprintf(output_file,"%s %s %s\n",\
                        "Smooth_Data_For_Alpha_0.5",\
                        "Smooth_Data_For_Alpha_3",\
                        "Smooth_Data_For_Alpha_10");
    for (i = 0; i < K; ++i)
    {
        double k1i = gsl_vector_get(k1, i);
        double k2i = gsl_vector_get(k2, i);
        double k3i = gsl_vector_get(k3, i);
        // printf("%e %e %e\n", k1i, k2i, k3i);
        fprintf(output_file,"%e %e %e\n", k1i, k2i, k3i);
    }
    // Close the file before cleanup
    fclose(output_file);
    // fprintf("\n\n");
   #endif
    /* print filter results */
    // Open file for writing at the beginning
    char *Gaussian_filter_output_file = "Gaussian_filter_output.dat";
    remove(Gaussian_filter_output_file);
    output_file = fopen(Gaussian_filter_output_file, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file!\n");
        return 1;
    }
    fprintf(output_file,"%s %s %s %s\n",\
                        "Data",\
                        "Smooth_Data_For_Alpha_0.5",\
                        "Smooth_Data_For_Alpha_3",\
                        "Smooth_Data_For_Alpha_10");
    // printf("time_index Data Smooth_Data_For_Alpha_0.5 Smooth_Data_For_Alpha_3 Smooth_Data_For_Alpha_10\n");
    for (i = 0; i < N; ++i)
    {
        double xi = gsl_vector_get(x, i);
        double y1i = gsl_vector_get(y1, i);
        double y2i = gsl_vector_get(y2, i);
        double y3i = gsl_vector_get(y3, i);
        // printf("%.12e %.12e %.12e %.12e\n", xi, y1i, y2i, y3i);
        fprintf(output_file,"%.12e %.12e %.12e %.12e\n", xi, y1i, y2i, y3i);
    }
    // Close the file before cleanup
    fclose(output_file);

    gsl_vector_free(x);
    gsl_vector_free(y1);
    gsl_vector_free(y2);
    gsl_vector_free(y3);
    gsl_vector_free(k1);
    gsl_vector_free(k2);
    gsl_vector_free(k3);
    gsl_rng_free(r);
    gsl_filter_gaussian_free(gauss_p);
    return 0;
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

void gsl_math_movstat(void)
{
    const size_t N = 500; /* length of time series */
    const size_t K = 11;  /* window size */
    gsl_movstat_workspace *w = gsl_movstat_alloc(K);
    gsl_vector *x = gsl_vector_alloc(N);
    gsl_vector *xmean = gsl_vector_alloc(N);
    gsl_vector *xmin = gsl_vector_alloc(N);
    gsl_vector *xmax = gsl_vector_alloc(N);
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    size_t i;
    for (i = 0; i < N; ++i)
    {
        double xi = cos(4.0 * M_PI * i / (double)N);
        double ei = gsl_ran_gaussian(r, 0.1);
        gsl_vector_set(x, i, xi + ei);
    }
    /* compute moving statistics */
    gsl_movstat_mean(GSL_MOVSTAT_END_PADVALUE, x, xmean, w);
    gsl_movstat_minmax(GSL_MOVSTAT_END_PADVALUE, x, xmin, xmax, w);
    /* print results */
    for (i = 0; i < N; ++i)
    {
        printf("%zu %f %f %f %f\n",
               i,
               gsl_vector_get(x, i),
               gsl_vector_get(xmean, i),
               gsl_vector_get(xmin, i),
               gsl_vector_get(xmax, i));
    }
    gsl_vector_free(x);
    gsl_vector_free(xmean);
    gsl_rng_free(r);
    gsl_movstat_free(w);
}

int func(double t, const double y[], double f[],
         void *params)
{
    (void)(t); /* avoid unused parameter warning */
    double mu = *(double *)params;
    f[0] = y[1];
    f[1] = -y[0] - mu * y[1] * (y[0] * y[0] - 1);
    return GSL_SUCCESS;
}
int jac(double t, const double y[], double *dfdy,
        double dfdt[], void *params)
{
    (void)(t); /* avoid unused parameter warning */
    double mu = *(double *)params;
    gsl_matrix_view dfdy_mat = gsl_matrix_view_array(dfdy, 2, 2);
    gsl_matrix *m = &dfdy_mat.matrix;
    gsl_matrix_set(m, 0, 0, 0.0);
    gsl_matrix_set(m, 0, 1, 1.0);
    gsl_matrix_set(m, 1, 0, -2.0 * mu * y[0] * y[1] - 1.0);
    gsl_matrix_set(m, 1, 1, -mu * (y[0] * y[0] - 1.0));
    dfdt[0] = 0.0;
    dfdt[1] = 0.0;
    return GSL_SUCCESS;
}


int gsl_odeiv2_Test_1(void)
{
    double mu = 10;
    gsl_odeiv2_system sys = {func, jac, 2, &mu};
    gsl_odeiv2_driver *d =
        gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd,
                                      1e-6, 1e-6, 0.0);
    int i;
    double t = 0.0, t1 = 100.0;
    double y[2] = {1.0, 0.0};
    for (i = 1; i <= 100; i++)
    {
        double ti = i * t1 / 100.0;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        if (status != GSL_SUCCESS)
        {
            printf("error, return value=%d\n", status);
            break;
        }
        printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
    }
    gsl_odeiv2_driver_free(d);
    return 0;
}
int gsl_odeiv2_Test_2(void)
{
    const gsl_odeiv2_step_type *T = gsl_odeiv2_step_rk8pd;
    gsl_odeiv2_step *s = gsl_odeiv2_step_alloc(T, 2);
    gsl_odeiv2_control *c = gsl_odeiv2_control_y_new(1e-6, 0.0);
    gsl_odeiv2_evolve *e = gsl_odeiv2_evolve_alloc(2);
    double mu = 10;
    gsl_odeiv2_system sys = {func, jac, 2, &mu};
    double t = 0.0, t1 = 100.0;
    double h = 1e-6;
    double y[2] = {1.0, 0.0};
    while (t < t1)
    {
        int status = gsl_odeiv2_evolve_apply(e, c, s,
                                             &sys,
                                             &t, t1,
                                             &h, y);
        if (status != GSL_SUCCESS)
            break;
        printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
    }
    gsl_odeiv2_evolve_free(e);
    gsl_odeiv2_control_free(c);
    gsl_odeiv2_step_free(s);
    return 0;
}