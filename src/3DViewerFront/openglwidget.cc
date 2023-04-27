#define GL_SILENCE_DEPRECATION
#include "openglwidget.h"

#include <cstring>
#include <iostream>

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

OpenGLWidget::~OpenGLWidget() {
  if (arr != nullptr) {
    remove_struct(&arr);
  }
  if (facets_arr != nullptr) {
    free(facets_arr);
    facets_arr = nullptr;
  }
}

void OpenGLWidget::initializeGL() {
  glClearColor(WidgetColor_.redF(), WidgetColor_.greenF(), WidgetColor_.blueF(),
               WidgetColor_.alphaF());
  glEnable(GL_DEPTH_TEST);
}

void OpenGLWidget::paintGL() {
  glClearColor(WidgetColor_.redF(), WidgetColor_.greenF(), WidgetColor_.blueF(),
               WidgetColor_.alphaF());
  glPointSize(PointSize_);
  glLineWidth(LineSize_);
  if (arr != nullptr) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (ParallelProjection_ == true) {
      glOrtho(-aspectratio, aspectratio, -1.0, 1.0, 1.0, 4000.0);
    } else if (CentralProjection_ == true) {
      glFrustum(-aspectratio, aspectratio, -1.0, 1.0, 1.0, 4000.0);
    }
    glEnableClientState(GL_VERTEX_ARRAY);

    if (arr->matrix_3d != nullptr) {
      glVertexPointer(3, GL_FLOAT, 0, &arr->matrix_3d->matrix[0][0]);
      if (PointType_) {
        glColor3f(PointColor_.redF(), PointColor_.greenF(),
                  PointColor_.blueF());
        if (PointType_ == 1) {
          glEnable(GL_POINT_SMOOTH);
          glEnable(GL_BLEND);
          glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
          glDrawArrays(GL_POINTS, 1, arr->matrix_3d->rows - 1);
        } else if (PointType_ == 2) {
          glDisable(GL_POINT_SMOOTH);
          glDrawArrays(GL_POINTS, 1, arr->matrix_3d->rows - 1);
        }
      }
    }

    if (StippleLine_ == true) {
      glEnable(GL_LINE_STIPPLE);
      glLineStipple(1, 0x00ff);
    }
    glColor3f(LineColor_.redF(), LineColor_.greenF(), LineColor_.blueF());
    glDrawElements(GL_LINES, count_F_ * 2, GL_UNSIGNED_INT, facets_arr);
    if (StippleLine_ == true) {
      glDisable(GL_LINE_STIPPLE);
    }
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OpenGLWidget::resizeGL(int w, int h) {
  // Инициализация матрицы проекций
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  aspectratio = qreal(w) / qreal(h);

  // Установка точки обзора
  glViewport(0, 0, (GLint)w, (GLint)h);
}

void OpenGLWidget::slot(QString qstr) {
  if (arr != nullptr) {
    remove_struct(&arr);
  }
  if (facets_arr != nullptr) {
    free(facets_arr);
    facets_arr = nullptr;
  }
  count_F_ = 0;
  char str[256] = {'\0'};
  strcat(str, qPrintable(qstr));
  fill_struct(str, &arr);
  vertex_count = arr->count_of_vertexes - 1;
  polygon_count = arr->count_of_facets;
  for (size_t i = 0; i < polygon_count; i++) {
    count_F_ += arr->polygons[i].numbers_of_vertexes_in_facets;
  }
  facets_arr = (int *)malloc(2 * count_F_ * sizeof(int));
  for (size_t i = 0, k = 0; i < polygon_count; i++) {
    for (size_t j = 0, l = 0; j < arr->polygons[i].numbers_of_vertexes_in_facets; j++, l += 2) {
      facets_arr[(k + l)] = arr->polygons[i].vertexes[j];
      if (j + 1 == arr->polygons[i].numbers_of_vertexes_in_facets) {
        facets_arr[(k + l) + 1] = arr->polygons[i].vertexes[0];
      } else {
        facets_arr[(k + l) + 1] = arr->polygons[i].vertexes[j + 1];
      }
    }
    k += arr->polygons[i].numbers_of_vertexes_in_facets * 2;
  }
  update();
  memset(str, '\0', strlen(str));
  dXTranslate_ = 0;
  dYTranslate_ = 0;
  dZTranslate_ = 0;
}

void OpenGLWidget::slotScale(float scale_x, float scale_y, float scale_z) {
  if (arr != nullptr) {
    translate_struct(arr->matrix_3d, -dXTranslate_, -dYTranslate_,
                         -dZTranslate_);
    scale_struct(arr->matrix_3d, scale_x, scale_y, scale_z);
    translate_struct(arr->matrix_3d, dXTranslate_, dYTranslate_,
                         dZTranslate_);
    update();
  }
}

void OpenGLWidget::slotTranslate(float dx, float dy, float dz) {
  if (arr != nullptr) {
    dXTranslate_ += dx;
    dYTranslate_ += dy;
    dZTranslate_ += dz;
    translate_struct(arr->matrix_3d, dx, dy, dz);
    update();
  }
}

void OpenGLWidget::slotRotate(float rotate_x, float rotate_y, float rotate_z) {
  if (arr != nullptr) {
    translate_struct(arr->matrix_3d, -dXTranslate_, -dYTranslate_,
                         -dZTranslate_);
    rotate_struct(arr->matrix_3d, rotate_x / 57.29578, rotate_y / 57.29578,
                      rotate_z / 57.29578);
    translate_struct(arr->matrix_3d, dXTranslate_, dYTranslate_,
                         dZTranslate_);
    update();
  }
}

void OpenGLWidget::slotProjectionTypeChange(bool value_1, bool value_2) {
  ParallelProjection_ = value_1;
  CentralProjection_ = value_2;
  update();
}

void OpenGLWidget::slotLineTypeChange(bool checked) {
  StippleLine_ = checked;
  update();
}

void OpenGLWidget::slotLineSizeChange(double value) {
  LineSize_ = value;
  update();
}

void OpenGLWidget::slotPointTypeChange(int value) {
  PointType_ = value;
  update();
}

void OpenGLWidget::slotPointSizeChange(double value) {
  PointSize_ = value;
  update();
}

void OpenGLWidget::slotPointColorChange(QColor value) {
  PointColor_ = value;
  update();
}

void OpenGLWidget::slotLineColorChange(QColor value) {
  LineColor_ = value;
  update();
}

void OpenGLWidget::slotWidgetColorChange(QColor value) {
  WidgetColor_ = value;
  update();
}
