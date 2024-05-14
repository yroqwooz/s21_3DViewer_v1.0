#include "glview.h"

#include "mainwindow.h"

GLVIew::GLVIew(QWidget *parent) : QOpenGLWidget{parent} {}

void GLVIew::parse_obj() {
  FreeMemory(&this->file_data);
  file_data = {0, NULL, 0, NULL};
  if (this->filename[0] != '\0') {
    ParsingFile(this->filename, &this->file_data);
    get_normalized_coeff();
    update();
  }
}

GLVIew::~GLVIew() { FreeMemory(&file_data); }

void GLVIew::initializeGL() {
  glClearColor(bg_red, bg_green, bg_blue, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void GLVIew::paintGL() {
  glClearColor(bg_red, bg_green, bg_blue, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glVertexPointer(3, GL_DOUBLE, 0, file_data.vertex);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (this->projection_type == 0) {
    glOrtho(-1 * normalized_coeff, 1 * normalized_coeff, -1 * normalized_coeff,
            1 * normalized_coeff, -1 * normalized_coeff,
            1000 * normalized_coeff);
    glTranslatef(0, -normalized_coeff / 2, 0);
  } else {
    glFrustum(-1 * normalized_coeff, 1 * normalized_coeff,
              -1 * normalized_coeff, 1 * normalized_coeff, normalized_coeff,
              1000 * normalized_coeff);
    glTranslatef(0, 0, -2 * normalized_coeff);
    glRotatef(30, 1, 0, 0);
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  if (this->vertex_type != 0) {
    paint_dots();
  }
  paint_lines();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLVIew::paint_lines() {
  if (this->edge_type == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  }
  glLineWidth(this->edge_thickness);
  glColor3f(e_red, e_green, e_blue);
  glDrawElements(GL_LINES, file_data.count_edges * 2, GL_UNSIGNED_INT,
                 file_data.edges);
  if (this->edge_type == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLVIew::paint_dots() {
  if (this->vertex_type == 1) {
    glEnable(GL_POINT_SMOOTH);
  }
  glPointSize(this->vertex_thickness);
  glColor3f(v_red, v_green, v_blue);

  glDrawArrays(GL_POINTS, 0, file_data.count_vertex);
  if (this->vertex_type == 1) {
    glDisable(GL_POINT_SMOOTH);
  }
}

void GLVIew::get_normalized_coeff() {
  normalized_coeff = -1;
  for (size_t i = 0; i < file_data.count_vertex * 3; i++) {
    if (fabs(file_data.vertex[i]) > normalized_coeff) {
      normalized_coeff = fabs(file_data.vertex[i]);
    }
  }
}

void GLVIew::mousePressEvent(QMouseEvent *event) {
  curr_pos = event->globalPosition().toPoint();
}

void GLVIew::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - curr_pos);

  if (event->buttons() & Qt::LeftButton) {
    move_x(&this->file_data, new_pos.x() * this->normalized_coeff / 5000.0);
    move_y(&this->file_data, -new_pos.y() * this->normalized_coeff / 5000.0);
    update();
  } else if (event->buttons() & Qt::RightButton) {
    turn_around_x(&this->file_data, -new_pos.y() * 0.005);
    turn_around_y(&this->file_data, new_pos.x() * 0.005);
    update();
  }
}

void GLVIew::wheelEvent(QWheelEvent *event) {
  QPoint degrees_val = event->angleDelta() / 120;
  double step = normalized_coeff / 10;
  double scale_temp = scale_val;

  if ((int)(scale_val + degrees_val.y() * step) > 0) {
    scale_val += degrees_val.y() * step;
    scaling(&this->file_data, scale_val / scale_temp);
    update();
  }
}
