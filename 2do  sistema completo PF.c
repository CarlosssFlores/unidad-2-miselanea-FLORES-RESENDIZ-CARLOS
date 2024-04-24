#include <stdio.h>
#include <math.h>
//Sea el siguiente sistema:
//      2x - y - e^(-x)=0
//      -x + 2y - e^(-y)=0

// Prototipos de funciones
float calcular_g_1(float x_siguiente[]);
float calcular_g_2(float x_siguiente[]);
float calcular_convergencia_x1(float x_siguiente[]);
float calcular_convergencia_x2(float x_siguiente[]);
float calcular_error(float x_actual[], float x_anterior[]);
void proceso();

int main() {
    proceso();    
    return 0;
}

void proceso() {
    int iteracion = 0;
    float x_siguiente[] = {1, 1}; 
    float x_actual[2], error;

    while (iteracion < 100) {
        float convergencia_x1 = calcular_convergencia_x1(x_siguiente);
        float convergencia_x2 = calcular_convergencia_x2(x_siguiente);

        if (convergencia_x1 < 1 && convergencia_x2 < 1) {
            x_actual[0] = x_siguiente[0];
            x_actual[1] = x_siguiente[1];

            x_siguiente[0] = calcular_g_1(x_actual);
            x_siguiente[1] = calcular_g_2(x_actual);

            error = calcular_error(x_siguiente, x_actual);

            printf("\nIteración %d - Solución: %.15f, %.15f - Error: %.15f", iteracion + 1, x_siguiente[0], x_siguiente[1], error);

            if (error < 0.00001) {
                printf("\nConvergencia alcanzada.");
                break;
            }
        } else {
            printf("El método no converge.");
            break;
        }

        iteracion++;
    }
}

// Funciones para calcular las iteraciones
float calcular_g_1(float x_siguiente[]) {
    return (x_siguiente[1] + exp(-x_siguiente[0])) / 2.0;
}

float calcular_g_2(float x_siguiente[]) {
    return (x_siguiente[0] + exp(-x_siguiente[1])) / 2.0;
}

// Funciones para calcular la convergencia
float calcular_convergencia_x1(float x_siguiente[]) {
    return fabs(-(exp(-x_siguiente[0])) / 2) + (1 / 2.0);
}

float calcular_convergencia_x2(float x_siguiente[]) {
    return (1 / 2.0) + fabs(-(exp(-x_siguiente[1])) / 2);
}

// Función para calcular el error
float calcular_error(float x_actual[], float x_anterior[]) {
    return sqrt(pow(x_actual[0] - x_anterior[0], 2) + pow(x_actual[1] - x_anterior[1], 2));
}
