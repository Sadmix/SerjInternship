#include <stdlib.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#include "matrix.h"

void print_gsl_matrix(const gsl_matrix* m) {
  for (int i = 0; i < m->size1; i++) {
    for (int j = 0; j < m->size2; j++)
      printf("%.2f ", gsl_matrix_get(m, i, j));
    printf("\n");
  }
}

double rand_range(double min, double max) {
  return ((double)rand())/RAND_MAX*(max-min)+min;
}

void randomize_gsl_matrix(gsl_matrix** a, int rand_min, int rand_max) {
  for (int i = 0; i < (*a)->size1; i++) {
    for (int j = 0; j < (*a)->size2; j++) {
      gsl_matrix_set(*a, i, j, rand_range(rand_min, rand_max));
    }
  }
}

int compare_matricies(const gsl_matrix* exp, const Matrix* act) {
  if (exp->size1 != act->rows)
    return 0;
  if (exp->size2 != act->cols)
    return 0;
  for (int i = 0; i < exp->size1; i++) {
    for (int j = 0; j < exp->size2; j++) {
      if (gsl_matrix_get(exp, i, j) != act->elems[i][j])
        return 0;  
    }
  }
  return 1;
}

 check_status(const Matrix *res) {
  if ((res->rows == 0) && (res->cols == 0) && (res->elems == NULL))
    return GSL_EBADLEN;
  return GSL_SUCCESS;
}

int scale_gsl_matrix(gsl_matrix** m, double scale) {
  gsl_matrix *b = gsl_matrix_alloc((*m)->size2, (*m)->size2);
  gsl_matrix *c = gsl_matrix_calloc((*m)->size1, b->size2);
  gsl_matrix_set_identity(b);
  int res = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, scale, (*m), b, 1, c);
  return res;
}