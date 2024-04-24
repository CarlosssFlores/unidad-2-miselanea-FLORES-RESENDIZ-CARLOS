#include <stdio.h>
#include <math.h>

void calcular_fx(float *fx);
void calcular_Jacobiana_fx(float *fx, float (*Jacobiana)[3][3]);
void resolver_sistema(float (*sistema)[3][4], float (*jacobiana)[3][3], float *fx);
void imprimir_matriz(int filas, int columnas, float *matriz);
void pivotear(int filas, int columnas, float *matriz, float *vectorPivote, float *vectorPivoteaux, int j);

int main() {
    int iteracion = 0;
    float solucion_actual[] = {0.1 , 0.1, -0.1}; 
    float solucion[3];
    for (int i = 0; i < 3; i++) solucion[i] = solucion_actual[i];

    while (iteracion++ < 100) {
        float matriz_Jacobiana[3][3], nueva_matriz[3][4] = {{0.0}}; 

        calcular_Jacobiana_fx(solucion_actual, &matriz_Jacobiana);
        calcular_fx(solucion_actual);
        resolver_sistema(&nueva_matriz, &matriz_Jacobiana, solucion_actual);

        printf("\nIteración %d\n", iteracion);
        printf("\nMatriz resultante:\n");
        imprimir_matriz(3, 4, (float *)nueva_matriz);

        for (int i = 0; i < 3; i++) {
            solucion_actual[i] += nueva_matriz[i][3];
            solucion[i] = solucion_actual[i];
        }
        printf("\n\nLa solución actual es: %.9f, %.9f, %.9f", solucion_actual[0], solucion_actual[1], solucion_actual[2]);
    }

    return 0;
}

void calcular_fx(float *fx) {
    double num_x, num_y, num_z;
    float pi = M_PI;
    num_x = 3 * fx[0] - cos(fx[1] * fx[2]) - 0.5;
    num_y = pow(fx[0], 2) - 81 * pow(fx[1] + 0.1, 2) + sin(fx[2]) + 1.06;
    num_z = exp(-fx[0] * fx[1]) + 20 * fx[2] + (10 * pi - 3) / 3;
    printf("%.5f", pi);
    fx[0] = (float)num_x;
    fx[1] = (float)num_y;
    fx[2] = (float)num_z;
    printf("\n\n\nVector de dimensión 3:\n");
    for (int i = 0; i < 3; i++) printf("%.7f \n", fx[i]);
}

void calcular_Jacobiana_fx(float *fx, float (*Jacobiana)[3][3]) {
    (*Jacobiana)[0][0] = 3;
    (*Jacobiana)[0][1] = fx[2] * sin(fx[1] * fx[2]);
    (*Jacobiana)[0][2] = fx[1] * sin(fx[1] * fx[2]);
    (*Jacobiana)[1][0] = 2 * fx[0];
    (*Jacobiana)[1][1] = -162 * (fx[1] + 0.1);
    (*Jacobiana)[1][2] = cos(fx[2]);
    (*Jacobiana)[2][0] = -fx[1] * exp(-1 * fx[0] * fx[1]);
    (*Jacobiana)[2][1] = -fx[0] * exp(-1 * fx[0] * fx[1]);
    (*Jacobiana)[2][2] = 20;
    printf("\n\n\nMatriz de 3x3:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%.7f ", (*Jacobiana)[i][j]);
        }
        printf("\n");
    }
}

void resolver_sistema(float (*sistema)[3][4], float (*jacobiana)[3][3], float *fx) {
    int filas = 3, columnas = 4;
    float matriz_A[3][4];

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) matriz_A[i][j] = (*jacobiana)[i][j];
        matriz_A[i][3] = -fx[i];
    }

    printf("\nMatriz Inicial\n");
    imprimir_matriz(filas, columnas, (float *)matriz_A);
    printf("\n");

    float pivoteaux = 0, vector_pivote[columnas], vector_pivoteaux[columnas], n = 0;

    for (int j = 0; j < columnas - 1; j++) {
        pivotear(filas, columnas, (float *)matriz_A, vector_pivote, vector_pivoteaux, j);

        for (int i = 0; i < filas; i++) {
            if (i != j && j < columnas - 1) n = matriz_A[i][j];

            for (int k = 0; k < columnas; k++) matriz_A[i][k] = (-1 * n * vector_pivote[k]) + matriz_A[i][k];

            if (i == j) {
                for (int l = 0; l < columnas; l++) {
                    matriz_A[i][l] = vector_pivoteaux[l];
                    if (matriz_A[i][l] == -0) matriz_A[i][l] = 0;
                }
            }
        }

        n = 0;
        for (int k = 0; k < columnas; k++) vector_pivote[k] = 0;
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) (*sistema)[i][j] = matriz_A[i][j];
    }
}

void imprimir_matriz(int filas, int columnas, float *matriz) {
    int contar = 0;
    for (int i = 0; i < filas * columnas; i++) {
        if (contar < columnas) {
            printf("%.9f\t", matriz[i]);
            contar++;
        } else {
            contar = 0;
            printf("\n%.9f\t", matriz[i]);
            contar++;
        }
    }
}

void pivotear(int filas, int columnas, float *matriz, float *vectorPivote, float *vectorPivoteaux, int j) {
    float pivoteaux = 0, matriz_temporal[filas][columnas];
    int sumi = 0;

    for (int i = 0; i < filas; i++) {
        for (int k = 0; k < columnas; k++) {
            matriz_temporal[i][k] = matriz[sumi];
            sumi++;
        }
    }

    for (int i = 0; i < filas; i++) {
        if (i == j) {
            pivoteaux = matriz_temporal[i][j];
            for (int l = 0; l < columnas; l++) {
                matriz_temporal[i][l] = matriz_temporal[i][l] / pivoteaux;
                vectorPivote[l] = matriz_temporal[i][l];
                vectorPivoteaux[l] = matriz_temporal[i][l];
            }
        }
    }

    sumi = 0;
    for (int i = 0; i < filas; i++) {
        for (int k = 0; k < columnas; k++) {
            matriz[sumi] = matriz_temporal[i][k];
            sumi++;
        }
    }
}
