#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_29_ordinary_differential_equations.h"
// #include "gsl_math.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gsl_main.h"
#include "file_write.h"
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

int func(double t, const double y[], double f[],
         void *params);
int jac(double t, const double y[], double *dfdy,
        double dfdt[], void *params);
int gsl_odeiv2_Test_1(void);
int gsl_odeiv2_Test_2(void);
int ode_func(double t, const double y[], double f[],
             void *params);
int ode_jac(double t, const double y[], double *dfdy,
            double dfdt[], void *params);
int ode_main_1(void);
uint32_t chapter_29_ordinary_differential_equations_main()
{
    // gsl_odeiv2_Test_1();
    // gsl_odeiv2_Test_2();
    ode_main_1();
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
    char file_name[] = "gsl_odeiv2_Test_1.dat";
    FILE *output_file = create_file_to_write(file_name);
    fprintf(output_file,"%s %s %s\n", "t", "y[0]", "y[1]");
    
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
        fprintf(output_file,"%.5e %.5e %.5e\n", t, y[0], y[1]);
        // printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
    }
    gsl_odeiv2_driver_free(d);
    
    fclose(output_file);
    return 0;
}
int gsl_odeiv2_Test_2(void)
{
    char file_name[] = "gsl_odeiv2_Test_2.dat";
    FILE *output_file = create_file_to_write(file_name);
    fprintf(output_file,"%s %s %s\n", "t", "y[0]", "y[1]");
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
        fprintf(output_file,"%.5e %.5e %.5e\n", t, y[0], y[1]);
        // printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
    }
    gsl_odeiv2_evolve_free(e);
    gsl_odeiv2_control_free(c);
    gsl_odeiv2_step_free(s);
    fclose(output_file);
    return 0;
}

int ode_func(double t, const double y[], double f[],
             void *params)
{
    (void)(t); /* avoid unused parameter warning */
    double mu = *(double *)params;
    f[0] = y[1];
    f[1] = -y[0] - mu * y[1] * (y[0] * y[0] - 1);
    return GSL_SUCCESS;
}
int ode_jac(double t, const double y[], double *dfdy,
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
int ode_main_1(void)
{
    char file_name[] = "ode_main.dat";
    FILE *output_file;
    double mu = 10;
    gsl_odeiv2_system sys = {ode_func, ode_jac, 2, &mu};
    gsl_odeiv2_driver *d =
        gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rk8pd,
                                      1e-6, 1e-6, 0.0);
    int i;
    double t = 0.0, t1 = 100.0;
    double y[2] = {1.0, 0.0};

    output_file = create_file_to_write(file_name);
    fprintf(output_file, "%s %s %s\n",
            "Time",
            "y[0]",
            "y[1]");
    for (i = 1; i <= 100; i++)
    {
        double ti = i * t1 / 100.0;
        int status = gsl_odeiv2_driver_apply(d, &t, ti, y);
        if (status != GSL_SUCCESS)
        {
            printf("error, return value=%d\n", status);
            break;
        }
        fprintf(output_file, "%.5e %.5e %.5e\n", t, y[0], y[1]);
        // printf("%.5e %.5e %.5e\n", t, y[0], y[1]);
    }
    gsl_odeiv2_driver_free(d);
    fclose(output_file);
    return 0;
}
