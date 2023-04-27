#ifndef SRC_MATRIX_STRUCT_H_
#define SRC_MATRIX_STRUCT_H_

#define SUCCESS 1
#define FAILURE 0

enum { OK, UNCORRECT_MATRIX, CALCULATION_ERROR };

typedef struct matrix_struct {
  float **matrix;
  int rows;
  int columns;
} matrix_t;

#endif  // SRC_MATRIX_STRUCT_H_
