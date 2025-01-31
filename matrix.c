#include "matrix.h"
#include <time.h>

// Создание новой матрицы
Matrix create(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return (Matrix){0, 0, NULL};
    }
    
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.elems = (double **)malloc(rows * sizeof(double *));
    if (m.elems == NULL) {
        return (Matrix){0, 0, NULL};
    }

    for (int i = 0; i < rows; i++) {
        m.elems[i] = (double *)malloc(cols * sizeof(double));
        if (m.elems[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(m.elems[j]);
            }
            free(m.elems);
            return (Matrix){0, 0, NULL};
        }
    }

    return m;
}

// Освобождение памяти матрицы
void free_matrix(Matrix *m) {
    if (m->elems != NULL) {
        for (int i = 0; i < m->rows; i++) {
            free(m->elems[i]);
            m->elems[i] = NULL;
        }
        free(m->elems);
        m->elems = NULL;
    }
}

// Инициализация матрицы случайными значениями
void randomize(Matrix *m, double min, double max) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            m->elems[i][j] = min + ((double)rand() / RAND_MAX) * (max - min);
        }
    }
}

// Сложение двух матриц
Matrix add(Matrix *a, Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        return (Matrix){0, 0, NULL};
    }

    Matrix c = create(a->rows, a->cols);
    if (c.elems == NULL) {
        return c; // Возвращаем пустую матрицу
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            c.elems[i][j] = a->elems[i][j] + b->elems[i][j];
        }
    }
    return c;
}

// Вычитание двух матриц
Matrix sub(Matrix *a, Matrix *b) {
    if (a->rows != b->rows || a->cols != b->cols) {
        return (Matrix){0, 0, NULL};
    }

    Matrix c = create(a->rows, a->cols);
    if (c.elems == NULL) {
        return c; // Возвращаем пустую матрицу
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            c.elems[i][j] = a->elems[i][j] - b->elems[i][j];
        }
    }
    return c;
}

// Умножение двух матриц
Matrix mul(Matrix *a, Matrix *b) {
    if (a->cols != b->rows) {
        return (Matrix){0, 0, NULL};
    }

    Matrix c = create(a->rows, b->cols);
    if (c.elems == NULL) {
        return c; // Возвращаем пустую матрицу
    }

    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < b->cols; j++) {
            c.elems[i][j] = 0;
            for (int k = 0; k < a->cols; k++) {
                c.elems[i][j] += a->elems[i][k] * b->elems[k][j];
            }
        }
    }
    return c;
}

// Умножение матрицы на скаляр
Matrix mul_scalar(Matrix *m, double scalar) {
    Matrix result = create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            result.elems[i][j] = m->elems[i][j] * scalar;
        }
    }
    return result;
}
