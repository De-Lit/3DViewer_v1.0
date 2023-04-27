#include "./matrix/matrix.h"

extern void translate_struct(matrix_t *N, float dx, float dy, float dz) {
  for (int i = 1; i < N->rows; i++) {
    N->matrix[i][0] += dx;
    N->matrix[i][1] += dy;
    N->matrix[i][2] += dz;
  }
}
