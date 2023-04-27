#ifndef SRC_STRUCT_H_
#define SRC_STRUCT_H_

#include "./matrix/matrix_struct.h"

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t *matrix_3d;
  polygon_t *polygons;
} date_t;

#endif  // SRC_STRUCT_H_
