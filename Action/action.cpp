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

// Lagrangiano respecto los campos
double f_0(double x, void *params);
double f_g(double x, void *params);

double x(double t, void *params);
double dx(double t);

double kinetic_e(double v);
double potential_0();
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
    std::cout.precision(4);
    std::cout.setf(std::ios::scientific);
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
    double expected1 = 1.5;
    double expected2 = -0.7;
    double alpha = 1.0;

    std::cout << "Masa: " << m << "\t" << "t_1 = " << param_ini.t_1 << "\t" << "t_2 = " << param_ini.t_2 << std::endl;

    std::cout << "Probando potencial cero con energía cinética 1/2*m*v^2. x(t) = t como movimiento clásico y desviaciones en un campo cero. Se puede modificar \\
accediendo a x(t) prueba y colocando la función en parametros de t" << std::endl;
    gsl_function L_0;
    L_0.function = &f_0;
    L_0.params = &alpha;

    gsl_integration_qag(&L_0, param_ini.t_1, param_ini.t_2, 0, 1e-4, 1000, key,
                        w, &result, &error);

    std::cout << "Resultado de la acción computacional  = " << result << "    joule-s"
              << "\n"
              << "Comparación Teórica (manualmente)     = " << expected1 << "  joule-s"
              << "\n"
              << "Error estimado en máquina             = " << error << "\n"
              << "Desviación respecto teórico           = " << result - expected1 << std::endl;

    std::cout << "Probando potencial con gravedad y energía cinética 1/2*m*v^2. x(t) = t^2 como movimiento clásico y desviaciones en un campo gravitacional. \\
    Se puede modificar accediendo a x(t) prueba y colocando la función en parametros de t" << std::endl;

    gsl_function L_g;
    L_g.function = &f_g;
    L_g.params = &alpha;

    gsl_integration_qag(&L_g, param_ini.t_1, param_ini.t_2, 0, 1e-4, 1000, key,
                        w, &result, &error);

    std::cout << "Resultado de la acción computacional  = " << result << "    joule-s"
              << "\n"
              << "Comparación Teórica (manualmente)     = " << expected2 << "  joule-s"
              << "\n"
              << "Error estimado en máquina             = " << error << "\n"
              << "Desviación respecto teórico           = " << result - expected2 << std::endl;

    gsl_integration_workspace_free(w);
    return EXIT_SUCCESS;
}

// x(t) test: finding the best actional about potencial.
double x_0(double t, void *params)
{
    return pow(t, 1);
}

double x_g(double t, void *params)
{
    return pow(t, 2);
}

// diferencial de x(t)
double dx_0(double t)
{
    double result, abserr;
    gsl_function X;
    X.function = &x_0;

    gsl_deriv_central(&X, t, 1e-8, &result, &abserr);
    return result;
}

double dx_g(double t)
{
    double result, abserr;
    gsl_function X;
    X.function = &x_g;

    gsl_deriv_central(&X, t, 1e-8, &result, &abserr);
    return result;
}

// Cálculo de lagrangiano respecto las funciones de potencial y cinética.
double f_g(double t, void *params)
{
    double alpha = *(double *)params;
    double f = kinetic_e(dx_g(t)) - potential_g(x_g(t, &alpha));
    return f;
}

double f_0(double t, void *params)
{
    double alpha = *(double *)params;
    double f = kinetic_e(dx_0(t) - potential_0());
    return f;
}
// Energía
// Energía cinética
double kinetic_e(double v)
{
    double f = 0.5 * m * v * v;
    return f;
}
/*
 * Diferentes potenciales para hallar el mínimo y las variaciones.
 */
double potential_0() { return 0; };
double potential_g(double x)
{
    double f = m * G * x;
    return f;
}