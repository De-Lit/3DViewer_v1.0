#include <stdlib.h>

#include "../matrix.h"

extern void remove_matrix(matrix_t *A) {
  free(A->matrix);
  A->matrix = NULL_;
  A->rows = 0;
  A->columns = 0;
}
