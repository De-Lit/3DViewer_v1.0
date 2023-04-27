#include <stdlib.h>

#include "./matrix/matrix.h"
#include "3DViewer.h"

extern void remove_struct(date_t **N) {
  for (int i = 0; i < (*N)->count_of_facets; i++) {
    free((*N)->polygons[i].vertexes);
    (*N)->polygons[i].vertexes = NULL_;
  }
  free((*N)->polygons);
  (*N)->polygons = NULL_;
  remove_matrix((*N)->matrix_3d);
  free((*N)->matrix_3d);
  (*N)->matrix_3d = NULL_;
  free(*N);
  *N = NULL_;
}
