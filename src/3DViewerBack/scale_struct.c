#include "./matrix/matrix.h"

extern void scale_struct(matrix_t *N, float scale_x, float scale_y,
                             float scale_z) {
  for (int i = 1; i < N->rows; i++) {
    N->matrix[i][0] *= scale_x;
    N->matrix[i][1] *= scale_y;
    N->matrix[i][2] *= scale_z;
  }
}
