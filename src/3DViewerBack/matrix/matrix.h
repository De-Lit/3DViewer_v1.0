#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#include "./matrix_struct.h"

#define NULL_ (void *)0

/*
 * Создание матрицы
 */
extern int create_matrix(int rows, int columns, matrix_t *result);
/*
 * Очистка матрицы
 */
extern void remove_matrix(matrix_t *A);

#endif  // SRC_MATRIX_H_
