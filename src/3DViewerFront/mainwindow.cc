#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <cstring>

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  openGLWidget = new OpenGLWidget();

  ui->horizontalLayout->insertWidget(0, openGLWidget);

#ifdef Q_OS_MAC
  settings = new QSettings("grenoullelogique.fr", "Squash", this);
#else
  settings = new QSettings("Settings.ini", QSettings::IniFormat, this);
#endif

  connect(this, &MainWindow::signal, openGLWidget, &OpenGLWidget::slot);
  connect(this, &MainWindow::signalScale, openGLWidget,
          &OpenGLWidget::slotScale);
  connect(this, &MainWindow::signalTranslate, openGLWidget,
          &OpenGLWidget::slotTranslate);
  connect(this, &MainWindow::signalRotate, openGLWidget,
          &OpenGLWidget::slotRotate);
  connect(this, &MainWindow::signalProjectionTypeChange, openGLWidget,
          &OpenGLWidget::slotProjectionTypeChange);
  connect(this, &MainWindow::signalLineTypeChange, openGLWidget,
          &OpenGLWidget::slotLineTypeChange);
  connect(this, &MainWindow::signalLineSizeChange, openGLWidget,
          &OpenGLWidget::slotLineSizeChange);
  connect(this, &MainWindow::signalPointTypeChange, openGLWidget,
          &OpenGLWidget::slotPointTypeChange);
  connect(this, &MainWindow::signalPointSizeChange, openGLWidget,
          &OpenGLWidget::slotPointSizeChange);
  connect(this, &MainWindow::signalPointColorChange, openGLWidget,
          &OpenGLWidget::slotPointColorChange);
  connect(this, &MainWindow::signalLineColorChange, openGLWidget,
          &OpenGLWidget::slotLineColorChange);
  connect(this, &MainWindow::signalWidgetColorChange, openGLWidget,
          &OpenGLWidget::slotWidgetColorChange);

  readSettings();
}

MainWindow::~MainWindow() {
  writeSettings();
  delete ui;
  delete openGLWidget;
  delete settings;
}

void MainWindow::readSettings() {
  QColor color;
  settings->beginGroup("ProjectionType");
  if (settings->value("Parallel", true).toBool()) {
    ui->radioButtonParallel->setChecked(true);
  } else {
    ui->radioButtonCentral->setChecked(true);
  }
  settings->endGroup();
  settings->beginGroup("EdgeSettings");
  settings->beginGroup("EdgeType");
  if (settings->value("StippleLine", false).toBool()) {
    ui->radioButtonStippleLine->setChecked(true);
  }
  settings->endGroup();
  settings->beginGroup("EdgeSize");
  ui->horizontalSliderLineSize->setValue(
      settings->value("EdgeSize", ui->horizontalSliderLineSize->value())
          .toInt());
  settings->endGroup();
  settings->beginGroup("EdgeColor");
  color.setRgbF(settings->value("LineColorRed", 25).toFloat(),
                settings->value("LineColorGreen", 195).toFloat(),
                settings->value("LineColorBlue", 251).toFloat(), 1);
  setLineColor(color);
  settings->endGroup();
  settings->endGroup();
  settings->beginGroup("VertexSettings");
  settings->beginGroup("VertexType");
  if (settings->value("None", true).toBool()) {
    ui->radioButtonPointTypeNone->setChecked(true);
  } else if (settings->value("Round", false).toBool()) {
    ui->radioButtonPointTypeRound->setChecked(true);
  } else if (settings->value("Square", false).toBool()) {
    ui->radioButtonPointTypeSquare->setChecked(true);
  }
  settings->endGroup();
  settings->beginGroup("VertexSize");
  ui->horizontalSliderPointSize->setValue(
      settings->value("VertexSize", ui->horizontalSliderPointSize->value())
          .toInt());
  settings->endGroup();
  settings->beginGroup("VertexColor");
  color.setRgbF(settings->value("VertexColorRed", 25).toFloat(),
                settings->value("VertexColorGreen", 195).toFloat(),
                settings->value("VertexColorBlue", 251).toFloat(), 1);
  setPointColor(color);
  settings->endGroup();
  settings->endGroup();
  settings->beginGroup("BackgroundColor");
  color.setRgbF(settings->value("BackgroundColorRed", 212).toFloat(),
                settings->value("BackgroundColorGreen", 212).toFloat(),
                settings->value("BackgroundColorBlue", 212).toFloat(), 1);
  setWidgetColor(color);
  settings->endGroup();
}

void MainWindow::writeSettings() {
  QColor color;
  settings->beginGroup("ProjectionType");
  settings->setValue("Parallel", ui->radioButtonParallel->isChecked());
  settings->setValue("Central", ui->radioButtonCentral->isChecked());
  settings->endGroup();
  settings->beginGroup("EdgeSettings");
  settings->beginGroup("EdgeType");
  settings->setValue("StippleLine", ui->radioButtonStippleLine->isChecked());
  settings->endGroup();
  settings->beginGroup("EdgeSize");
  settings->setValue("EdgeSize", ui->horizontalSliderLineSize->value());
  settings->endGroup();
  settings->beginGroup("EdgeColor");
  color = ui->labelLineColor->palette().color(backgroundRole());
  settings->setValue("LineColorRed", color.redF());
  settings->setValue("LineColorGreen", color.greenF());
  settings->setValue("LineColorBlue", color.blueF());
  settings->endGroup();
  settings->endGroup();
  settings->beginGroup("VertexSettings");
  settings->beginGroup("VertexType");
  settings->setValue("None", ui->radioButtonPointTypeNone->isChecked());
  settings->setValue("Round", ui->radioButtonPointTypeRound->isChecked());
  settings->setValue("Square", ui->radioButtonPointTypeSquare->isChecked());
  settings->endGroup();
  settings->beginGroup("VertexSize");
  settings->setValue("VertexSize", ui->horizontalSliderPointSize->value());
  settings->endGroup();
  settings->beginGroup("VertexColor");
  color = ui->labelPointColor->palette().color(backgroundRole());
  settings->setValue("VertexColorRed", color.redF());
  settings->setValue("VertexColorGreen", color.greenF());
  settings->setValue("VertexColorBlue", color.blueF());
  settings->endGroup();
  settings->endGroup();
  settings->beginGroup("BackgroundColor");
  color = ui->labelBackgroundColor->palette().color(backgroundRole());
  settings->setValue("BackgroundColorRed", color.redF());
  settings->setValue("BackgroundColorGreen", color.greenF());
  settings->setValue("BackgroundColorBlue", color.blueF());
  settings->endGroup();
}

void MainWindow::on_pushButton_clicked() {
  QString qstr = QFileDialog::getOpenFileName(this, "Выбрать файл",
                                              "../obj_files", ".obj (*.obj)");
  if (strlen(qPrintable(qstr))) {
    ui->label->setText(qstr);
    emit signal(qstr);
    char str[256] = {'\0'};
    strcat(str, qPrintable(qstr));
    ui->statusbar->showMessage(
        QString("File name: %1   Vertexes: %2   Polygons: %3   Edges: %4")
            .arg(strrchr(str, '/') + 1)
            .arg(openGLWidget->vertex_count)
            .arg(openGLWidget->polygon_count)
            .arg(openGLWidget->vertex_count + openGLWidget->polygon_count - 2));
    ui->horizontalSliderScale->setSliderPosition(200);
    lableScaleValue = 1;
    ui->labelScaleValue->setText("1.00");
    valueTranslateX = 0;
    valueTranslateY = 0;
    valueTranslateZ = 0;
    ui->labelTranslateValueX->setText("0");
    ui->labelTranslateValueY->setText("0");
    ui->labelTranslateValueZ->setText("0");
    ui->horizontalSliderTranslateX->setSliderPosition(0);
    ui->horizontalSliderTranslateY->setSliderPosition(0);
    ui->horizontalSliderTranslateZ->setSliderPosition(0);
    valueRotateX = 0;
    valueRotateY = 0;
    valueRotateZ = 0;
    ui->horizontalSliderRotateX->setSliderPosition(0);
    ui->horizontalSliderRotateY->setSliderPosition(0);
    ui->horizontalSliderRotateZ->setSliderPosition(0);
    ui->doubleTranslateKSpinBox->setValue(0.0);
    emit signalTranslate(0, 0, -50);
    ui->labelTranslateValueZ->setText(QString::number(-50));
  }
}

void MainWindow::on_pushScaleButton_clicked() {
  emit signalScale((float)ui->doubleScaleSpinBox->value(),
                   (float)ui->doubleScaleSpinBox->value(),
                   (float)ui->doubleScaleSpinBox->value());
  lableScaleValue *= ui->doubleScaleSpinBox->value();
  ui->labelScaleValue->setText(QString::asprintf("%.3lf", lableScaleValue));
}

void MainWindow::on_pushTranslateButton_clicked() {
  emit signalTranslate((float)ui->doubleTranslateXSpinBox->value(),
                       (float)ui->doubleTranslateYSpinBox->value(),
                       (float)ui->doubleTranslateZSpinBox->value());
  ui->labelTranslateValueX->setText(
      QString::number(ui->labelTranslateValueX->text().toFloat() +
                      (float)ui->doubleTranslateXSpinBox->value()));
  ui->labelTranslateValueY->setText(
      QString::number(ui->labelTranslateValueY->text().toFloat() +
                      (float)ui->doubleTranslateYSpinBox->value()));
  ui->labelTranslateValueZ->setText(
      QString::number(ui->labelTranslateValueZ->text().toFloat() +
                      (float)ui->doubleTranslateZSpinBox->value()));
}

void MainWindow::on_horizontalSliderScale_valueChanged(int value) {
  double scale = 1;
  if (scaleValue > value) {
    emit signalScale(0.99f, 0.99f, 0.99f);
    scale = 0.99;
  } else if (value > scaleValue) {
    emit signalScale(1.f / 0.99f, 1.f / 0.99f, 1.f / 0.99f);
    scale = 1. / 0.99;
  }
  scaleValue = value;
  lableScaleValue *= scale;
  ui->labelScaleValue->setText(QString::asprintf("%.3lf", lableScaleValue));
}

void MainWindow::on_horizontalSliderRotateX_valueChanged(int value) {
  float dX = value - valueRotateX;
  valueRotateX = value;
  emit signalRotate(dX, 0, 0);
  ui->spinBoxRotateX->setValue(value);
}

void MainWindow::on_horizontalSliderRotateY_valueChanged(int value) {
  float dY = value - valueRotateY;
  valueRotateY = value;
  emit signalRotate(0, dY, 0);
  ui->spinBoxRotateY->setValue(value);
}

void MainWindow::on_horizontalSliderRotateZ_valueChanged(int value) {
  float dZ = value - valueRotateZ;
  valueRotateZ = value;
  emit signalRotate(0, 0, dZ);
  ui->spinBoxRotateZ->setValue(value);
}

void MainWindow::on_horizontalSliderTranslateX_valueChanged(int value) {
  float dX = (value - valueTranslateX) / 100;
  emit signalTranslate(dX * ui->doubleTranslateKSpinBox->value(), 0, 0);
  valueTranslateX = value;
  ui->labelTranslateValueX->setText(
      QString::number(ui->labelTranslateValueX->text().toDouble() +
                      dX * ui->doubleTranslateKSpinBox->value()));
}

void MainWindow::on_horizontalSliderTranslateY_valueChanged(int value) {
  float dY = (value - valueTranslateY) / 100;
  emit signalTranslate(0, dY * ui->doubleTranslateKSpinBox->value(), 0);
  valueTranslateY = value;
  ui->labelTranslateValueY->setText(
      QString::number(ui->labelTranslateValueY->text().toDouble() +
                      dY * ui->doubleTranslateKSpinBox->value()));
}

void MainWindow::on_horizontalSliderTranslateZ_valueChanged(int value) {
  float dZ = (value - valueTranslateZ) / 100;
  emit signalTranslate(0, 0, dZ * ui->doubleTranslateKSpinBox->value());
  valueTranslateZ = value;
  ui->labelTranslateValueZ->setText(
      QString::number(ui->labelTranslateValueZ->text().toDouble() +
                      dZ * ui->doubleTranslateKSpinBox->value()));
}

void MainWindow::on_spinBoxRotateX_valueChanged(int arg1) {
  ui->horizontalSliderRotateX->setValue(arg1);
}

void MainWindow::on_spinBoxRotateY_valueChanged(int arg1) {
  ui->horizontalSliderRotateY->setValue(arg1);
}

void MainWindow::on_spinBoxRotateZ_valueChanged(int arg1) {
  ui->horizontalSliderRotateZ->setValue(arg1);
}

void MainWindow::on_radioButtonParallel_toggled(bool checked) {
  if (checked == true) {
    emit signalProjectionTypeChange(checked, false);
  }
}

void MainWindow::on_radioButtonCentral_toggled(bool checked) {
  if (checked == true) {
    emit signalProjectionTypeChange(false, checked);
  }
}

void MainWindow::on_radioButtonStippleLine_toggled(bool checked) {
  emit signalLineTypeChange(checked);
}

void MainWindow::on_doubleSpinBoxLineSize_valueChanged(double arg1) {
  ui->horizontalSliderLineSize->setValue(arg1 * 10);
}

void MainWindow::on_horizontalSliderLineSize_valueChanged(int value) {
  emit signalLineSizeChange((double)value / 10);
  ui->doubleSpinBoxLineSize->setValue((double)value / 10);
}

void MainWindow::on_doubleSpinBoxPointSize_valueChanged(double arg1) {
  ui->horizontalSliderPointSize->setValue(arg1 * 10);
}

void MainWindow::on_horizontalSliderPointSize_valueChanged(int value) {
  emit signalPointSizeChange((double)value / 10);
  ui->doubleSpinBoxPointSize->setValue((double)value / 10);
}

void MainWindow::on_radioButtonPointTypeNone_toggled(bool checked) {
  ui->labelPointSize->setEnabled(!checked);
  ui->doubleSpinBoxPointSize->setEnabled(!checked);
  ui->horizontalSliderPointSize->setEnabled(!checked);
  if (checked) {
    emit signalPointTypeChange(0);
  }
}

void MainWindow::on_radioButtonPointTypeRound_toggled(bool checked) {
  if (checked) {
    emit signalPointTypeChange(1);
  }
}

void MainWindow::on_radioButtonPointTypeSquare_toggled(bool checked) {
  if (checked) {
    emit signalPointTypeChange(2);
  }
}

void MainWindow::on_pushButtonPointColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    setPointColor(color);
  }
}

void MainWindow::setPointColor(QColor color) {
  QVariant variant = color;
  QString colcode = variant.toString();
  ui->labelPointColor->setStyleSheet("background-color : " + colcode + "");
  emit signalPointColorChange(color);
}

void MainWindow::on_pushButtonLineColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    setLineColor(color);
  }
}

void MainWindow::setLineColor(QColor color) {
  QVariant variant = color;
  QString colcode = variant.toString();
  ui->labelLineColor->setStyleSheet("background-color : " + colcode + "");
  emit signalLineColorChange(color);
}

void MainWindow::on_pushButtonWidgetColor_clicked() {
  QColor color = QColorDialog::getColor(Qt::white);
  if (color.isValid()) {
    setWidgetColor(color);
  }
}

void MainWindow::setWidgetColor(QColor color) {
  QVariant variant = color;
  QString colcode = variant.toString();
  ui->labelBackgroundColor->setStyleSheet("background-color : " + colcode + "");
  emit signalWidgetColorChange(color);
}

void MainWindow::on_pushButtonSaveScreenshot_clicked() {
  QImage img = openGLWidget->grabFramebuffer();
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath(), tr("Images (*.jpeg *.bmp)"));
  if (!fileName.isNull()) {
    img.save(fileName);
  }
}

void MainWindow::GetFileName(QString *name) {
  *name = QFileDialog::getSaveFileName(this, tr("Save GIF"), QDir::homePath(),
                                       tr("Gif (*.gif)"));
}

void MainWindow::on_pushButtonSaveGif_clicked() {
  miliseconds = 0;
  frame = new QImage();
  gif = new QGifImage();
  time = new QTimer();
  GetFileName(&file_name);
  if (!file_name.isNull() && !recording) {
    recording = true;
    connect(time, SIGNAL(timeout()), this, SLOT(MakeGif()));
    time->start(100);
    ui->pushButtonSaveGif->setText("Recording");
  }
}

void MainWindow::MakeGif() {
  *frame = openGLWidget->grabFramebuffer();
  *frame = frame->scaled(640, 480);
  gif->addFrame(*frame, 100);
  miliseconds += 100;
  if (miliseconds >= 4000) {
    time->stop();
    gif->save(file_name);
    recording = false;
    ui->pushButtonSaveGif->setText("Gif");
  }
}
