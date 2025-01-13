#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>
#include <CUnit/Basic.h>

#include "matrix.h"
#include "test_utils.h"

void exit(int code) {
  printf("Failed: shouldn't use exit() function\n");
  CU_FAIL_FATAL();
}

int init_suite(void) {
  gsl_set_error_handler_off();
  return 0;
}

int clean_suite(void) {
  return 0;
}

void test_create_matrix_corner(void) {
  create(0, 0);
  create(-1, -1);
  create(1, 0);
  create(0, 1);
  // CU_ASSERT(create_matrix(0, 0) == NULL);
  // CU_ASSERT(create_matrix(-1, -1) == NULL);
  // CU_ASSERT(create_matrix(1, 0) == NULL);
  // CU_ASSERT(create_matrix(0, 1) == NULL);
}

void test_create_matrix_rand(void) {
  // srand(time(0));
  // for (int i = 0; i < 1000; i++) {
  //   int rows = rand()%(20-1)+1;
  //   int cols = rand()%(20-1)+1;
  //   Matrix m = create(rows, cols);
  //   CU_ASSERT(m.rows = rows);
  //   CU_ASSERT(m.cols = cols);
  //   free_matrix(&m);
  // }
}

void test_randomize_rand(void) {
  // for (int i = 0; i < 1000; i++) {
  //   int rows = 3;
  //   int cols = 3;
  //   gsl_matrix *a = gsl_matrix_alloc(rows, cols);
  //   srand(i);
  //   randomize_gsl_matrix(&a, 0, 10);
  //   Matrix b = create(rows, cols);
  //   srand(i);
  //   randomize(&b, 0, 10);
  //   CU_ASSERT(compare_matricies(a, &b));
  //   gsl_matrix_free(a);
  //   free_matrix(&b);
  // }
}

void test_add_matrix_simple(void) {
  // Matrix a = create(3, 3);
  // Matrix b = create(2, 2);
  // Matrix res = add(&a, &b);
  // free_matrix(&b);
  // b = create(3, 3);
  // res = add(&a, &b);
  // free_matrix(&a);
  // free_matrix(&b);
}

void test_add_matrix_rand(void) {
  // for (int i = 0; i < 1000; i++) {
  //   srand(i);
  //   gsl_matrix *a = gsl_matrix_alloc(rand()%5+2, rand()%5+2);
  //   gsl_matrix *b = gsl_matrix_alloc(rand()%5+2, rand()%5+2);
  //   int res = gsl_matrix_add(a, b);
  //   srand(i);
  //   Matrix a_ = create(rand()%5+2, rand()%5+2);
  //   Matrix b_ = create(rand()%5+2, rand()%5+2);
  //   Matrix res_ = add(&a_, &b_);
  //   if (res == GSL_SUCCESS)
  //     CU_ASSERT(compare_matricies(a, &a_));
  // }
}

void test_sub_matrix_simple(void) {
  // Matrix a = create(3, 3);
  // Matrix b = create(2, 2);
  // Matrix res = add(&a, &b);
  // free_matrix(&b);
  // b = create(3, 3);
  // res = sub(&a, &b);
  // free_matrix(&a);
  // free_matrix(&b);
}

void test_sub_matrix_rand(void) {
  // for (int i = 0; i < 1000; i++) {
  //   srand(i);
  //   gsl_matrix *a = gsl_matrix_alloc(rand()%5+2, rand()%5+2);
  //   gsl_matrix *b = gsl_matrix_alloc(rand()%5+2, rand()%5+2);
  //   int res = gsl_matrix_sub(a, b);
  //   srand(i);
  //   matrix *a_ = create_matrix(rand()%5+2, rand()%5+2);
  //   matrix *b_ = create_matrix(rand()%5+2, rand()%5+2);
  //   int res_ = sub_matrix(a_, b_);
  //   res_ = (res_ == -1) ? GSL_EBADLEN : GSL_SUCCESS;
  //   CU_ASSERT(res == res_);
  //   if (res_ == GSL_SUCCESS)
  //     CU_ASSERT(compare_matricies(a, a_));
  // }
}

void test_scale_matrix_simple(void) {
}

void test_scale_matrix_rand(void) {
  // for (int i = 0; i < 100; i++) {
  //   srand(i);
  //   int alpha = rand()%100-50;
  //   gsl_matrix *a = gsl_matrix_alloc(rand()%4+1, rand()%4+1);
  //   int res = scale_gsl_matrix(&a, alpha);
  //   srand(i);
  //   int alpha_ = rand()%100-50;
  //   matrix *a_ = create_matrix(rand()%4+1, rand()%4+1);
  //   int res_ = scale_matrix(a_, alpha_);
  //   CU_ASSERT(res == res_);
  //   CU_ASSERT(compare_matricies(a, a_));
  // }
}

void test_mul_matrix_simple(void) {
}

void test_mul_matrix_rand(void) { 
  // for (int i = 0; i < 100; i++) {
  //   srand(i);
  //   gsl_matrix *a = gsl_matrix_alloc(rand()%4+1, rand()%4+1);
  //   gsl_matrix *b = gsl_matrix_alloc(rand()%4+1, rand()%4+1);
  //   gsl_matrix *c = gsl_matrix_calloc(a->size1, b->size2);
  //   int res = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, a, b, 1, c);
  //   srand(i);
  //   gsl_matrix *a_ = gsl_matrix_alloc(rand()%4+1, rand()%4+1);
  //   gsl_matrix *b_ = gsl_matrix_alloc(rand()%4+1, rand()%4+1);
  //   gsl_matrix *c_ = gsl_matrix_calloc(a->size1, b->size2);
  //   int res_ = gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1, a_, b_, 1, c_);
  //   CU_ASSERT(res == res_);
    // CU_ASSERT(compare_matricies(a, a_));
  // }
}

int main()
{
  CU_pSuite simple = NULL;
  CU_pSuite rand = NULL;

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  simple = CU_add_suite("Simple", init_suite, clean_suite);
  if (NULL == simple) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  rand = CU_add_suite("Rand", init_suite, clean_suite);
  if (NULL == rand) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if (
    (NULL == CU_add_test(simple, "Create matrix", test_create_matrix_corner)) ||
    (NULL == CU_add_test(rand, "Create matrix", test_create_matrix_rand)) ||
    (NULL == CU_add_test(rand, "Randomize matrix", test_randomize_rand)) || 
    (NULL == CU_add_test(simple, "Add matrix", test_add_matrix_simple)) ||
    (NULL == CU_add_test(rand, "Add matrix", test_add_matrix_rand)) ||
    (NULL == CU_add_test(simple, "Sub matrix", test_sub_matrix_simple)) ||
    (NULL == CU_add_test(rand, "Sub matrix", test_sub_matrix_rand)) ||
    (NULL == CU_add_test(simple, "Scale matrix", test_scale_matrix_simple)) ||
    (NULL == CU_add_test(rand, "Scale matrix", test_scale_matrix_rand)) ||
    (NULL == CU_add_test(simple, "Mul matrix", test_mul_matrix_simple)) ||
    (NULL == CU_add_test(rand, "Mul matrix", test_mul_matrix_rand)))
  {
    CU_cleanup_registry();
    return CU_get_error();
  }

  CU_basic_set_mode(CU_BRM_NORMAL);
  CU_basic_run_tests();
  int res = CU_get_number_of_failures();
  CU_cleanup_registry();
  return (res > 0) ? -1 : 0;
}
