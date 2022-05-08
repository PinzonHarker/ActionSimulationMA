#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>

struct my_f_params
{
  double a;
  double b;
  double c;
};

double
my_f(double x, void *p)
{
  struct my_f_params *params = (struct my_f_params *)p;
  double a = (params->a);
  double b = (params->b);
  double c = (params->c);

  return (a * x + b) * x + c;
}

int main(int argc, char const *argv[])
{
   gsl_function F;
  struct my_f_params params = {3.0, 2.0, 1.0};

   F.function = &my_f;
   F.params = &params;

  for (int ii = 0; ii < 10; ii++)
  {
    double x = ii + 0.0;
    std::cout << my_f(x, &params) << std::endl;
  }

  return 0;
}
