#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_24_digital_filtering.h"
// #include "gsl_math.h"
#include <gsl/gsl_math.h>
#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_filter.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_vector.h>
#include "file_write.h"
uint8_t gsl_Gaussian_Example_1();
uint8_t gsl_Gaussian_Example_2();
uint8_t Square_Wave_Signal_Example();
uint32_t chapter_24_digital_filtering_main()
{
    // gsl_Gaussian_Example_1();
    // gsl_Gaussian_Example_2();
    Square_Wave_Signal_Example();
}
uint8_t gsl_Gaussian_Example_1()
{
    FILE *output_file;
    const size_t N = 500;                     /* length of time series */
    const size_t K = 51;                      /* window size */
    const double alpha[3] = {0.5, 3.0, 10.0}; /* alpha values */
    gsl_vector *x = gsl_vector_alloc(N);      /* input vector */
    gsl_vector *y1 = gsl_vector_alloc(N);     /* filtered output vector for alpha1 */
    gsl_vector *y2 = gsl_vector_alloc(N);     /* filtered output vector for alpha2 */
    gsl_vector *y3 = gsl_vector_alloc(N);     /* filtered output vector for alpha3 */
    gsl_vector *k1 = gsl_vector_alloc(K);     /* Gaussian kernel for alpha1 */
    gsl_vector *k2 = gsl_vector_alloc(K);     /* Gaussian kernel for alpha2 */
    gsl_vector *k3 = gsl_vector_alloc(K);     /* Gaussian kernel for alpha3 */
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
    if (output_file == NULL)
    {
        fprintf(stderr, "Error opening output file!\n");
        return 1;
    }
    fprintf(output_file, "%s %s %s\n",
        "Smooth_Data_For_Alpha_0.5",
        "Smooth_Data_For_Alpha_3",
        "Smooth_Data_For_Alpha_10");
        for (i = 0; i < K; ++i)
        {
        double k1i = gsl_vector_get(k1, i);
        double k2i = gsl_vector_get(k2, i);
        double k3i = gsl_vector_get(k3, i);
        // printf("%e %e %e\n", k1i, k2i, k3i);
        fprintf(output_file, "%e %e %e\n", k1i, k2i, k3i);
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
    if (output_file == NULL)
    {
        fprintf(stderr, "Error opening output file!\n");
        return 1;
    }
    fprintf(output_file, "%s %s %s %s\n",
            "Data",
            "Smooth_Data_For_Alpha_0.5",
            "Smooth_Data_For_Alpha_3",
            "Smooth_Data_For_Alpha_10");
    // printf("time_index Data Smooth_Data_For_Alpha_0.5 Smooth_Data_For_Alpha_3 Smooth_Data_For_Alpha_10\n");
    for (i = 0; i < N; ++i)
    {
        double xi = gsl_vector_get(x, i);
        double y1i = gsl_vector_get(y1, i);
        double y2i = gsl_vector_get(y2, i);
        double y3i = gsl_vector_get(y3, i);
        // printf("%.12e %.12e %.12e %.12e\n", xi, y1i, y2i, y3i);
        fprintf(output_file, "%.12e %.12e %.12e %.12e\n", xi, y1i, y2i, y3i);
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
uint8_t gsl_Gaussian_Example_2()
{
    FILE *output_file;
    const size_t N = 1000;                 /* length of time series */
    const size_t K = 61;                   /* window size */
    const double alpha = 3.0;              /* Gaussian kernel has +/- 3 standard,deviations */
    gsl_vector *x = gsl_vector_alloc(N);   /* input vector */
    gsl_vector *y = gsl_vector_alloc(N);   /* filtered output vector */
    gsl_vector *dy = gsl_vector_alloc(N);  /* first derivative filtered vector */
    gsl_vector *d2y = gsl_vector_alloc(N); /* second derivative filtered vector */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    gsl_filter_gaussian_workspace *gauss_p = gsl_filter_gaussian_alloc(K);
    size_t i;

    char *gsl_Gaussian_Example_2 = "gsl_Gaussian_Example_2.dat";
    remove(gsl_Gaussian_Example_2);
    output_file = fopen(gsl_Gaussian_Example_2, "w");
    if (output_file == NULL)
    {
        fprintf(stderr, "Error opening output file!\n");
        return 1;
    }
    /* print results */
    fprintf(output_file, "%s %s %s %s %s\n",
            "Signal",
            "Gaussian_Smooth_Signal",
            "First_Differenced_Signal",
            "1st_Order_Gaussian_Smooth_Signal",
            "2nd_Order_Gaussian_Smooth_Signal");

    /* generate input signal */
    for (i = 0; i < N; ++i)
    {
        double xi = (i > N / 2) ? 0.5 : 0.0;
        double ei = gsl_ran_gaussian(r, 0.1);
        gsl_vector_set(x, i, xi + ei);
    }
    /* apply filters */
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 0, x, y, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 1, x, dy, gauss_p);
    gsl_filter_gaussian(GSL_FILTER_END_PADVALUE, alpha, 2, x, d2y, gauss_p);
    for (i = 0; i < N; ++i)
    {
        double xi = gsl_vector_get(x, i);
        double yi = gsl_vector_get(y, i);
        double dyi = gsl_vector_get(dy, i);
        double d2yi = gsl_vector_get(d2y, i);
        double dxi;
        /* compute finite difference of x vector */
        if (i == 0)
            dxi = gsl_vector_get(x, i + 1) - xi;
        else if (i == N - 1)
            dxi = gsl_vector_get(x, i) - gsl_vector_get(x, i - 1);
        else
            dxi = 0.5 * (gsl_vector_get(x, i + 1) - gsl_vector_get(x, i - 1));
        fprintf(output_file, "%.12e %.12e %.12e %.12e %.12e\n",
                xi,
                yi,
                dxi,
                dyi,
                d2yi);
        // printf("%.12e %.12e %.12e %.12e %.12e\n",
        //        xi,
        //        yi,
        //        dxi,
        //        dyi,
        //        d2yi);
    }
    fclose(output_file);
    gsl_vector_free(x);
    gsl_vector_free(y);
    gsl_vector_free(dy);
    gsl_vector_free(d2y);
    gsl_rng_free(r);
    gsl_filter_gaussian_free(gauss_p);
    return 0;
}
uint8_t Square_Wave_Signal_Example()
{
    FILE *output_file;
    const size_t N = 1000; /* length of time series */
    const size_t K = 7;    /* window size */
    const double f = 5.0;  /* frequency of square wave in Hz!*/
    gsl_filter_median_workspace *median_p = gsl_filter_median_alloc(K);
    gsl_filter_rmedian_workspace *rmedian_p = gsl_filter_rmedian_alloc(K);
    gsl_vector *t = gsl_vector_alloc(N);         /* time */
    gsl_vector *x = gsl_vector_alloc(N);         /* input vector */
    gsl_vector *y_median = gsl_vector_alloc(N);  /* median filtered output */
    gsl_vector *y_rmedian = gsl_vector_alloc(N); /* recursive median filtered output */
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    size_t i;

    char *gsl_Gaussian_Example_2 = "gsl_Gaussian_Example_2.dat";
    remove(gsl_Gaussian_Example_2);
    output_file = fopen(gsl_Gaussian_Example_2, "w");
    if (output_file == NULL)
    {
        fprintf(stderr, "Error opening output file!\n");
        return 1;
    }
    /* print results */
    fprintf(output_file, "%s %s %s %s\n",
            "Time",
            "Data",
            "Standard_Median_Filter",
            "Recursive_Median_Filter");
    /* generate input signal */
    for (i = 0; i < N; ++i)
    {
        double ti = (double)i / (N - 1.0);
        double tmp = sin(2.0 * M_PI * f * ti);
        double xi = (tmp >= 0.0) ? 1.0 : -1.0;
        double ei = gsl_ran_gaussian(r, 0.1);
        gsl_vector_set(t, i, ti);
        gsl_vector_set(x, i, xi + ei);
    }
    gsl_filter_median(GSL_FILTER_END_PADVALUE, x, y_median, median_p);
    gsl_filter_rmedian(GSL_FILTER_END_PADVALUE, x, y_rmedian, rmedian_p);
    /* print results */
    for (i = 0; i < N; ++i)
    {
        double ti = gsl_vector_get(t, i);
        double xi = gsl_vector_get(x, i);
        double medi = gsl_vector_get(y_median, i);
        double rmedi = gsl_vector_get(y_rmedian, i);
        fprintf(output_file, "%f %f %f %f\n",
                ti,
                xi,
                medi,
                rmedi);
        // printf("%f %f %f %f\n",
        //        ti,
        //        xi,
        //        medi,
        //        rmedi);
    }
    fclose(output_file);
    gsl_vector_free(t);
    gsl_vector_free(x);
    gsl_vector_free(y_median);
    gsl_vector_free(y_rmedian);
    gsl_rng_free(r);
    gsl_filter_median_free(median_p);
    return 0;
}