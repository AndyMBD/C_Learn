#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "chapter_08_vectors_and_matrices.h"
// #include "gsl_math.h"
#include <gsl/gsl_math.h>
#include <gsl/gsl_poly.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_block.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
uint8_t gsl_vector_1();
uint8_t gsl_vector_2();
uint8_t gsl_matrix_1();
uint8_t gsl_matrix_2();
uint8_t gsl_matrix_3();
void chapter_08_vectors_and_matrices_main()
{
    // gsl_vector_1();
    // gsl_vector_2();
    // gsl_matrix_1();
    // gsl_matrix_2();
    gsl_matrix_3();
}
uint8_t gsl_vector_1()
{

    int i;
    gsl_vector *v = gsl_vector_alloc(3);
    for (i = 0; i < 3; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
    }
    for (i = 0; i < 100; i++) /* OUT OF RANGE ERROR */
    {
        printf("v_%d = %g\n", i, gsl_vector_get(v, i));
    }
    gsl_vector_free(v);
    return 0;
}
uint8_t gsl_vector_2()
{

    int i;
    gsl_vector *v = gsl_vector_alloc(100);
    for (i = 0; i < 100; i++)
    {
        gsl_vector_set(v, i, 1.23 + i);
    }
    {
        FILE *f = fopen("test.dat", "w");
        gsl_vector_fprintf(f, v, "%.5g");
        fclose(f);
    }
    gsl_vector_free(v);
    return 0;
}
uint8_t gsl_matrix_1()
{
    int i, j;
    gsl_matrix *m = gsl_matrix_alloc(10, 3);
    for (i = 0; i < 10; i++)
        for (j = 0; j < 3; j++)
            gsl_matrix_set(m, i, j, 0.23 + 100 * i + j);
    for (i = 0; i < 100; i++) /* OUT OF RANGE ERROR */
        for (j = 0; j < 3; j++)
            printf("m(%d,%d) = %g\n", i, j,
                   gsl_matrix_get(m, i, j));
    gsl_matrix_free(m);
    return 0;
}
uint8_t gsl_matrix_2()
{
    int i, j, k = 0;
    gsl_matrix *m = gsl_matrix_alloc(100, 100);
    gsl_matrix *a = gsl_matrix_alloc(100, 100);
    for (i = 0; i < 100; i++)
        for (j = 0; j < 100; j++)
            gsl_matrix_set(m, i, j, 0.23 + i + j);
    {
        FILE *f = fopen("test.dat", "wb");
        gsl_matrix_fwrite(f, m);
        fclose(f);
    }
    {
        FILE *f = fopen("test.dat", "rb");
        gsl_matrix_fread(f, a);
        fclose(f);
    }
    for (i = 0; i < 100; i++)
        for (j = 0; j < 100; j++)
        {
            double mij = gsl_matrix_get(m, i, j);
            double aij = gsl_matrix_get(a, i, j);
            if (mij != aij)
                k++;
        }
    gsl_matrix_free(m);
    gsl_matrix_free(a);
    printf("differences = %d (should be zero)\n", k);
    return (k > 0);
}
uint8_t gsl_matrix_3()
{
    size_t i, j;
    gsl_matrix *m = gsl_matrix_alloc(10, 10);
    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            gsl_matrix_set(m, i, j, sin(i) + cos(j));
    for (j = 0; j < 10; j++)
    {
        gsl_vector_view column = gsl_matrix_column(m, j);
        double d;
        d = gsl_blas_dnrm2(&column.vector);
        printf("matrix column %zu, norm = %g\n", j, d);
    }
    gsl_matrix_free(m);
    return 0;
}