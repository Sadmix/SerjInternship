#include <stdio.h>
#include <stdlib.h>

#ifndef MATRIX_LIB
#define MATRIX_LIB 

struct matrix_t {
  int rows;
  int cols;
  double **data;
};
typedef struct matrix_t matrix;

matrix* create_matrix(int rows, int cols) {
  if (rows <= 0)
    return NULL;
  if (cols <= 0)
    return NULL;
  matrix* m = (matrix*)malloc(sizeof(matrix));
  m->cols = cols;
  m->rows = rows;
  m->data = (double**)malloc(sizeof(double*)*rows);
  for (int i = 0; i < m->rows; i++) {
    m->data[i] = (double*)malloc(sizeof(double)*cols);
  }
  return m;
}

void free_matrix(matrix* m) {
  for (int i = 0; i < m->rows; i++) {
    free(m->data[i]);
  }
  free(m->data);
  free(m);
}

void randomize_matrix(matrix* m, int rand_min, int rand_max) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      m->data[i][j] = rand()%(rand_max-rand_min)+rand_min;
    }
  }
}

int add_matrix(matrix* a, const matrix* b) {
  if (a->rows != b->rows)
    return -1;
  if (a->cols != b->cols)
    return -1;
  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < b->cols; j++) {
      a->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  }
  return 0;
}

int sub_matrix(matrix* a, const matrix* b) {
  return -1;
}

int scale_matrix(matrix* a, double alpha) {
  return -1;
}

#endif // MATRIX_LIB 
