#include <stdlib.h>

#include "../matrix.h"

static float **dynamic_array_alloc(int, int);

extern int create_matrix(int rows, int columns, matrix_t *result) {
  int result_code = OK;
  result->matrix = NULL_;
  result->rows = 0;
  result->columns = 0;
  if (rows > 0 && columns > 0) {
    result->matrix = dynamic_array_alloc(rows, columns);
    if (result->matrix != NULL_) {
      result->rows = rows;
      result->columns = columns;
    } else {
      result_code = UNCORRECT_MATRIX;
    }
  } else {
    result_code = UNCORRECT_MATRIX;
  }
  return result_code;
}

static float **dynamic_array_alloc(int N, int M) {
  float **A = (float **)malloc(N * sizeof(float *) + N * M * sizeof(float));
  float *start = (float *)((char *)A + N * sizeof(float *));
  for (int i = 0; i < N; ++i) {
    A[i] = start + i * M;
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      A[i][j] = 0;
    }
  }
  return A;
}
