#ifndef SRC_3DVIEWER_H_
#define SRC_3DVIEWER_H_

#include "struct.h"

#define NULL_ (void *)0

extern int fill_struct(char *argv, date_t **N);
extern void translate_struct(matrix_t *N, float dx, float dy, float dz);
extern void rotate_struct(matrix_t *N, float rotate_x, float rotate_y,
                              float rotate_z);
extern void scale_struct(matrix_t *N, float scale_x, float scale_y,
                             float scale_z);
extern void remove_struct(date_t **N);

#endif  // SRC_3DVIEWER_H_
