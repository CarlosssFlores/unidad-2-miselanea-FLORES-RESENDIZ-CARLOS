#include <stdio.h>
#include <math.h>
//Sea el siguiente sistema:
//         x² + y² = 10
//          xy + y³=7

// Funciones para las iteraciones
float g_1(float x_siguiente[]);
float g_2(float x_siguiente[]);
float error_x(float x_siguiente[]);
float error_y(float x_siguiente[]);
void proceso();

int main(){
    proceso();    
    return 0;
}

void proceso()
{
    int iteracion = 0;
    float x_siguiente[] = {1.5, 1.5}; 

    while (iteracion < 100)
    {
        float convergencia_x = error_x(x_siguiente);
        float convergencia_y = error_y(x_siguiente);

        if (convergencia_x < 1 && convergencia_y < 1)
        {
            x_siguiente[0] = g_1(x_siguiente);
            x_siguiente[1] = g_2(x_siguiente);
            printf("\nIteración %d: ", iteracion + 1);
            printf("(%.6f, %.6f)", x_siguiente[0], x_siguiente[1]);
            printf("  Error x: %.6f, Error y: %.6f", convergencia_x, convergencia_y);
        }
        else
        {
            printf("El método iterativo no converge.");
            break;
        }

        iteracion++;
    }
}

// Definición de las funciones de iteración
float g_1(float x_siguiente[])
{
    return sqrt(10 - pow(x_siguiente[1], 2));
}

float g_2(float x_siguiente[])
{
    return pow(7 - x_siguiente[0] * x_siguiente[1], 1.0 / 3.0);
}

// Funciones para calcular el error de convergencia
float error_x(float x_siguiente[])
{
    return fabs(-(x_siguiente[1]) / (3 * pow(7 - (x_siguiente[0] * x_siguiente[1]), 2.0 / 3.0)));
}

float error_y(float x_siguiente[])
{
    return fabs(-(x_siguiente[0]) / (3 * pow(7 - x_siguiente[1] * x_siguiente[0], 2.0 / 3.0))) + fabs(-(x_siguiente[1]) / (sqrt(10 - pow(x_siguiente[1], 2))));
}
