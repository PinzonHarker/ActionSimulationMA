#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>

double m = 0.2; //kg masa 1 del cuerpo

double f(double x, void *params);

/*
* Programa para simular cálculo de la acción respecto movimiento de un 
* cuerpo en un eje coordenado x con el tiempo, produce una gráfica de
* la acción mínima representada por el movimiento real respecto variaciones
* infinitesimales de la curva 
*/
int main(int argc, char const *argv[])
{
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);

    double result, error;
    double expected = -4.0;
    double alpha = 1.0;

    gsl_function F;
    F.function = &f;
    F.params = &alpha;

    gsl_integration_qags(&F, 0, 1, 0, 1e-7, 1000,
                         w, &result, &error);

    printf("result          = % .18f\n", result);
    printf("exact result    = % .18f\n", expected);
    printf("estimated error = % .18f\n", error);
    printf("actual error    = % .18f\n", result - expected);
    printf("intervals       = %zu\n", w->size);

    gsl_integration_workspace_free(w);
    return 0;
}
// Cálculo de lagrangiano para 
double f(double x, void *params)
{
    double alpha = *(double *)params;
    double f = log(alpha * x) / sqrt(x);
    return f;
}

double potential(double x, void *params){
    double alpha = *(double *)params;
    double f = mgh
}