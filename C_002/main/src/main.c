#include <stdio.h>
#include <gsl/gsl_sf_bessel.h>
int main ()
{
  double x = 5.0;
  double y = gsl_sf_bessel_J0 (x);
  printf ("J0(%g) = %.18e\n", x, y);
  printf ("hellow world\n");
  return 0;
  // Expected output: J0(5) = -1.775967713143382600e-001
}