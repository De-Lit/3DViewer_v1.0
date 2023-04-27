#include <math.h>

#include "./matrix/matrix.h"

extern void rotate_struct(matrix_t *N, float rotate_x, float rotate_y,
                              float rotate_z) {
  float sin_x_tmp = (float)sin(rotate_x);
  float cos_x_tmp = (float)cos(rotate_x);
  float sin_y_tmp = (float)sin(rotate_y);
  float cos_y_tmp = (float)cos(rotate_y);
  float sin_z_tmp = (float)sin(rotate_z);
  float cos_z_tmp = (float)cos(rotate_z);
  float temp_x;
  float temp_y;
  float temp_z;

  for (int i = 1; i < N->rows; i++) {
    // rotate_x
    temp_y = N->matrix[i][1];
    temp_z = N->matrix[i][2];
    N->matrix[i][1] = temp_y * cos_x_tmp - temp_z * sin_x_tmp;
    N->matrix[i][2] = temp_y * sin_x_tmp + temp_z * cos_x_tmp;
  }

  for (int i = 1; i < N->rows; i++) {
    // rotate_y
    temp_x = N->matrix[i][0];
    temp_z = N->matrix[i][2];
    N->matrix[i][0] = temp_x * cos_y_tmp + temp_z * sin_y_tmp;
    N->matrix[i][2] = -temp_x * sin_y_tmp + temp_z * cos_y_tmp;
  }

  for (int i = 1; i < N->rows; i++) {
    // rotate_z
    temp_x = N->matrix[i][0];
    temp_y = N->matrix[i][1];
    N->matrix[i][0] = temp_x * cos_z_tmp - temp_y * sin_z_tmp;
    N->matrix[i][1] = temp_x * sin_z_tmp + temp_y * cos_z_tmp;
  }
}
