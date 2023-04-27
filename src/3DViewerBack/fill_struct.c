#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./matrix/matrix.h"
#include "3DViewer.h"

int vertexes_I = 1;
int facets_I = 0;
static void counter(int *, int *, FILE *);
static void parser(date_t *, FILE *);
static void fill_matrix_3d(matrix_t *, char *);
static void fill_polygons(polygon_t *, char *);
static void vertexes_counter(int *, const char *);
static void fill_vertexes(polygon_t *, char *);

extern int fill_struct(char *argv, date_t **N) {
  int error = 0;
  FILE *mf = NULL_;
  mf = fopen(argv, "r");
  if (!mf) {
    error = 1;
  } else {
    int _count_of_vertexes = vertexes_I;
    int _count_of_facets = facets_I;
    counter(&_count_of_vertexes, &_count_of_facets, mf);
    fseek(mf, 0L, SEEK_SET);
    *N = (date_t *)malloc(sizeof(date_t));
    (*N)->matrix_3d = (matrix_t *)malloc(sizeof(matrix_t));
    (*N)->count_of_facets = _count_of_facets;
    (*N)->count_of_vertexes = _count_of_vertexes;
    create_matrix(_count_of_vertexes, 3, (*N)->matrix_3d);
    (*N)->polygons = (polygon_t *)malloc(_count_of_facets * sizeof(polygon_t));
    parser(*N, mf);
    fclose(mf);
    mf = NULL_;
    vertexes_I = 1;
    facets_I = 0;
  }
  return error;
}

static void counter(int *count_of_vertexes, int *count_of_facets,
                        FILE *mf) {
  char buff[3] = {'\0'};
  while (fgets(buff, 3, mf) != NULL_) {
    if (buff[0] == 'v' && buff[1] == ' ') {
      (*count_of_vertexes)++;
    } else if (buff[0] == 'f' && buff[1] == ' ') {
      (*count_of_facets)++;
    }
    buff[0] = '\0';
    buff[1] = '\0';
  }
}

static void parser(date_t *N, FILE *mf) {
  char buff[256] = {'\0'};
  int i = facets_I;
  while (fgets(buff, 256, mf) != NULL_) {
    if (buff[0] == 'v' && buff[1] == ' ') {
      fill_matrix_3d(N->matrix_3d, buff);
    } else if (buff[0] == 'f' && buff[1] == ' ') {
      fill_polygons(&N->polygons[i], buff);
      i++;
    }
    memset(buff, '\0', strlen(buff));
  }
}

static void fill_matrix_3d(matrix_t *M, char *str) {
  int i = vertexes_I;
  char *nstr = strtok(str, "v");
  char *tstr = NULL_;
  for (int j = 0; j < M->columns; j++) {
    M->matrix[i][j] = strtod(nstr, &tstr);
    nstr = tstr;
  }
  vertexes_I++;
}

static void fill_polygons(polygon_t *P, char *str) {
  vertexes_counter(&P->numbers_of_vertexes_in_facets, str);
  P->vertexes = (int *)malloc(P->numbers_of_vertexes_in_facets * sizeof(int));
  fill_vertexes(P, str);
}

static void vertexes_counter(int *count, const char *str) {
  *count = 0;
  for (int i = 1; str[i] != '\0' && str[i] != '\n'; i++) {
    if (str[i - 1] == ' ' && str[i] != ' ') {
      (*count)++;
    }
  }
}

static void fill_vertexes(polygon_t *P, char *str) {
  for (int i = 0; i < P->numbers_of_vertexes_in_facets;) {
    str++;
    if (*(str - 1) == ' ' && *str != ' ') {
      P->vertexes[i] = atoi(str);
      i++;
    }
  }
}
