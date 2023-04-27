#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QImage>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

#include "openglwidget.h"
#include "qtgifimage/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  void readSettings();
  void writeSettings();

 private slots:
  void on_pushButton_clicked();
  void on_pushScaleButton_clicked();
  void on_pushTranslateButton_clicked();

  void on_horizontalSliderScale_valueChanged(int value);

  void on_horizontalSliderRotateX_valueChanged(int value);
  void on_horizontalSliderRotateY_valueChanged(int value);
  void on_horizontalSliderRotateZ_valueChanged(int value);

  void on_horizontalSliderTranslateX_valueChanged(int value);
  void on_horizontalSliderTranslateY_valueChanged(int value);
  void on_horizontalSliderTranslateZ_valueChanged(int value);

  void on_spinBoxRotateX_valueChanged(int arg1);
  void on_spinBoxRotateY_valueChanged(int arg1);
  void on_spinBoxRotateZ_valueChanged(int arg1);

  void on_radioButtonParallel_toggled(bool checked);
  void on_radioButtonCentral_toggled(bool checked);
  void on_radioButtonStippleLine_toggled(bool checked);
  void on_doubleSpinBoxLineSize_valueChanged(double arg1);

  void on_horizontalSliderLineSize_valueChanged(int value);
  void on_doubleSpinBoxPointSize_valueChanged(double arg1);

  void on_horizontalSliderPointSize_valueChanged(int value);

  void on_radioButtonPointTypeNone_toggled(bool checked);

  void on_radioButtonPointTypeRound_toggled(bool checked);

  void on_radioButtonPointTypeSquare_toggled(bool checked);

  void on_pushButtonPointColor_clicked();

  void on_pushButtonLineColor_clicked();

  void on_pushButtonWidgetColor_clicked();
  void on_pushButtonSaveScreenshot_clicked();

  void on_pushButtonSaveGif_clicked();
  void MakeGif();
  void GetFileName(QString *name);

 signals:
  void signal(QString);
  void signalScale(float scale_x, float scale_y, float scale_z);
  void signalTranslate(float dx, float dy, float dz);
  void signalRotate(float rotate_x, float rotate_y, float rotate_z);
  void signalProjectionTypeChange(bool, bool);
  void signalLineTypeChange(bool);
  void signalLineSizeChange(double);
  void signalPointTypeChange(int);
  void signalPointSizeChange(double);
  void signalPointColorChange(QColor);
  void signalLineColorChange(QColor);
  void signalWidgetColorChange(QColor);

 private:
  void setPointColor(QColor);
  void setWidgetColor(QColor);
  void setLineColor(QColor);

  OpenGLWidget *openGLWidget;
  Ui::MainWindow *ui;
  QSettings *settings;

  float scaleValue = 200;
  double lableScaleValue = 1;
  float valueTranslateX = 0;
  float valueTranslateY = 0;
  float valueTranslateZ = 0;
  int valueRotateX = 0;
  int valueRotateY = 0;
  int valueRotateZ = 0;

  QGifImage *gif;
  QImage *frame;
  QTimer *time;
  int miliseconds;
  QString file_name;
  bool recording = false;
};
#endif  // MAINWINDOW_H
