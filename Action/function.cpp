#include <iostream>
#include <cmath>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_integration.h>
#include "function.h"

// x(t) test: finding the best actional about potencial.
double x(double t, void *params)
{
    return pow(t, 1);
}

//diferencial de x(t)
double dx(double t){
    double result, abserr;
    gsl_function X;
    X.function = &x;
    
    gsl_deriv_central (&X, t, 1e-8, &result, &abserr);
    return result;
}