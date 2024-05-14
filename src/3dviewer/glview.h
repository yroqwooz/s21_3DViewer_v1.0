#ifndef GLVIEW_H
#define GLVIEW_H

#pragma once
#include <QFileDialog>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QSurfaceFormat>
#include <QTimer>
#include <QWheelEvent>

#include "mainwindow.h"

extern "C" {
#include "lib/s21_parser.h"
#include "lib/s21_struct.h"
#include "lib/s21_transform.h"
}
// #include "lib/transform.h"
// #include "lib/s21_parser.h"
// #include "lib/s21_struct.h"

class GLVIew : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit GLVIew(QWidget *parent = nullptr);

  char *filename;
  obj_data file_data = {0, 0, NULL, NULL};

  int projection_type = 0;

  void parse_obj();
  void restore_default_vals();
  double normalized_coeff;

  // QString v_red;
  // QString v_green;
  // QString v_blue;

  // QString e_red;
  // QString e_green;
  // QString e_blue;

  // QString bg_red;
  // QString bg_green;
  // QString bg_blue;

  double v_red;
  double v_green;
  double v_blue;

  double e_red;
  double e_green;
  double e_blue;

  double bg_red;
  double bg_green;
  double bg_blue;

  int vertex_type = 0;
  int vertex_thickness = 3;

  int edge_type = 0;
  int edge_thickness = 3;

  double scale_val = 5;
  double rotate_x;
  double rotate_y;
  double rotate_z;
  double translate_x;
  double translate_y;
  double translate_z;

  ~GLVIew();

 protected:
  void initializeGL() override;
  // void resizeGL(int w, int h);
  void paintGL() override;

  void paint_lines();
  void paint_dots();

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  void get_normalized_coeff();
  QTimer timer;

  QPoint curr_pos;
  QPoint new_pos;

  // public slots:
  //     void getFileName();

  // float matrix[24] = {
  //     -0.25, -0.25, -0.25,
  //      0.25, -0.25, -0.25,
  //     -0.25, -0.25, 0.25,
  //     0.25, -0.25, 0.25,
  //     -0.25, 0.25, -0.25,
  //     0.25, 0.25, -0.25,
  //     -0.25, 0.25, 0.25,
  //     0.25, 0.25, 0.25
  // };
  // int matrix_links[24] = {
  //                        0, 1,
  //                        1, 3,
  //                        3, 2,
  //                        2, 0,

  //                        4, 5,
  //                        5, 7,
  //                        7, 6,
  //                        6, 4,
  //     0, 4,
  //     1, 5,
  //     2, 6,
  //     3, 7,

  // };

  void get_normalized_coef();
};

#endif  // GLVIEW_H
