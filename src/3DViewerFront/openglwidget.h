#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QMainWindow>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QWidget>
#include <QtOpenGL>
#if defined(linux) || defined(_WIN32)
#include <GL/glut.h> /*Для Linux и Windows*/
#else
#include <GLUT/GLUT.h> /*Для Mac OS*/
#endif

extern "C" {
#include "3DViewer.h"
}

class OpenGLWidget : public QOpenGLWidget {
 public:
  int vertex_count = 0;
  int polygon_count = 0;
  OpenGLWidget(QWidget *parent = nullptr);
  ~OpenGLWidget();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 public slots:
  void slot(QString);
  void slotScale(float scale_x, float scale_y, float scale_z);
  void slotTranslate(float dx, float dy, float dz);
  void slotRotate(float rotate_x, float rotate_y, float rotate_z);
  void slotProjectionTypeChange(bool, bool);
  void slotLineTypeChange(bool);
  void slotLineSizeChange(double);
  void slotPointSizeChange(double);
  void slotPointTypeChange(int);
  void slotPointColorChange(QColor);
  void slotLineColorChange(QColor);
  void slotWidgetColorChange(QColor);

 private:
  date_t *arr = nullptr;
  int *facets_arr = nullptr;
  int count_F_ = 0;
  float dXTranslate_ = 0;
  float dYTranslate_ = 0;
  float dZTranslate_ = 0;
  bool ParallelProjection_ = true;
  bool CentralProjection_ = false;
  bool StippleLine_ = false;
  double LineSize_ = 1;
  int PointType_ = 0;
  double PointSize_ = 1;
  QColor PointColor_;
  QColor LineColor_;
  QColor WidgetColor_;
  qreal aspectratio;
};
#endif  // OPENGLWIDGET_H
