#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>   
#include <stdlib.h>  

// Определение структуры матрицы
typedef struct {
    int rows;
    int cols;
    double **elems;
} Matrix;

// Прототипы функций
Matrix create(int rows, int cols);
void free_matrix(Matrix *m);
void randomize(Matrix *m, double min, double max);
Matrix add(Matrix *a, Matrix *b);
Matrix sub(Matrix *a, Matrix *b);
Matrix mul(Matrix *a, Matrix *b);
Matrix mul_scalar(Matrix *m, double scalar);
void print_matrix(Matrix *m);

#endif 