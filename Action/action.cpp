#include <iostream>
#include <cmath>
#include <gsl/gsl_math.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_integration.h>

double m = 1.0;       // kg masa 1 del cuerpo
const double G = 9.8; // m/s^2 gravedad terrestre general
struct
{
    double t_1 = 0.0;
    double t_2 = 3.0;
} param_ini;

double f(double x, void *params);

double x(double t, void *params);
double dx(double t);

double kinetic_e(double v);
double potencial_0();
double potential_g(double x);

/*
 * Programa para simular cálculo de la acción respecto movimiento de un
 * cuerpo en un eje coordenado x con el tiempo, produce una gráfica de
 * la acción mínima representada por el movimiento real respecto variaciones
 * infinitesimales de la curva.
 *
 * @authors AndresApellidoSegundo AndresPinzonHarker
 */
int main(int argc, char const *argv[])
{

    gsl_integration_workspace *w = gsl_integration_workspace_alloc(1000);

    /*  Key for aproximation by Gauss-Kronrod rules
     *   GSL_INTEG_GAUSS15   1
     *   GSL_INTEG_GAUSS21   2
     *   GSL_INTEG_GAUSS31   3
     *   GSL_INTEG_GAUSS41   4
     *   GSL_INTEG_GAUSS51   5
     *   GSL_INTEG_GAUSS61   6
     */
    double key = 4;
    double result, error;
    double expected = 18.0;
    double alpha = 1.0;

    gsl_function L;
    L.function = &f;
    L.params = &alpha;

    gsl_integration_qag(&L, param_ini.t_1, param_ini.t_2, 0, 1e-4, 1000, key,
                        w, &result, &error);

    std::cout << "Probando potencial cero con energía cinética 1/2*m*v^2. x(t) = t como movimiento clásico y desviaciones";
    std::cout << "\n";

    std::cout.precision(4);
    std::cout.setf(std::ios::scientific);
    std::cout << "Resultado de la acción          = " << result << "joule-s" << "\n"
              << "Comparación Teórica             = " << expected << "joule-s" << "\n"
              << "Error estimado en máquina       = " << error << "\n"
              << "Desviación respecto teórico     = " << result - expected << std::endl;

    gsl_integration_workspace_free(w);
    return EXIT_SUCCESS;
}

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

// Cálculo de lagrangiano respecto las funciones de potencial y cinética.
double f(double t, void *params)
{
    double alpha = *(double *)params;
    double f = kinetic_e(dx(t)) - potential_g(x(t, &alpha));
    return f;
}
// Energía cinética
double kinetic_e(double v)
{
    double f = 0.5 * m * v * v;
    return f;
}
/*
 * Diferentes potenciales para hallar el mínimo y las variaciones.
 */
double potencial_0() { return 0; };
double potential_g(double x)
{
    double f = m * G * x;
    return f;
}