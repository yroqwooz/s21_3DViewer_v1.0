#include "s21_transform.h"

void turn_around_x(obj_data *obj_data, double angle_degrees) {
  double angle_radians = angle_degrees * (S21_PI / 180.0);
  double cos_a = cos(angle_radians);
  double sin_a = sin(angle_radians);
  size_t num_vertices = obj_data->count_vertex;
  double *vertex_array = obj_data->vertex;

  for (size_t i = 0; i < 3 * num_vertices; i += 3) {
    double buf_y = vertex_array[i + 1];
    double buf_z = vertex_array[i + 2];
    vertex_array[i + 1] = cos_a * buf_y - sin_a * buf_z;
    vertex_array[i + 2] = sin_a * buf_y + cos_a * buf_z;
  }
}

/* вращение y */
void turn_around_y(obj_data *obj_data, double angle_degrees) {
  double angle_radians = angle_degrees * (S21_PI / 180.0);
  double cos_a = cos(angle_radians);
  double sin_a = sin(angle_radians);
  size_t num_vertices = obj_data->count_vertex;
  double *vertex_array = obj_data->vertex;

  for (size_t i = 0; i < 3 * num_vertices; i += 3) {
    double buf_x = vertex_array[i];
    double buf_z = vertex_array[i + 2];
    vertex_array[i] = cos_a * buf_x - sin_a * buf_z;
    vertex_array[i + 2] = sin_a * buf_x + cos_a * buf_z;
  }
}

/* вращение по z */
void turn_around_z(obj_data *obj_data, double angle_degrees) {
  double angle_radians = angle_degrees * (S21_PI / 180.0);
  double cos_a = cos(angle_radians);
  double sin_a = sin(angle_radians);
  size_t num_vertices = obj_data->count_vertex;
  double *vertex_array = obj_data->vertex;

  for (size_t i = 0; i < 3 * num_vertices; i += 3) {
    double buf_x = vertex_array[i];
    double buf_y = vertex_array[i + 1];
    vertex_array[i] = cos_a * buf_x - sin_a * buf_y;
    vertex_array[i + 1] = sin_a * buf_x + cos_a * buf_y;
  }
}

void scaling(obj_data *obj_data, double new_scale) {
  if (new_scale != 0.0) {
    size_t num_vertices = obj_data->count_vertex;
    double *vertex_array = obj_data->vertex;
    for (size_t i = 0; i < 3 * num_vertices; i++) {
      vertex_array[i] *= new_scale;
    }
  }
}

/*  здесь delta_x/y/z величина на которую нужно подвинуть 3д-фигню по x/y/z */
void move_x(obj_data *obj_data, double delta_x) {
  if (delta_x != 0.0) {
    size_t num_vertices = obj_data->count_vertex;
    double *vertex_array = obj_data->vertex;
    for (size_t i = 0; i < 3 * num_vertices; i += 3) {
      vertex_array[i] += delta_x;
    }
  }
}

void move_y(obj_data *obj_data, double delta_y) {
  if (delta_y != 0.0) {
    size_t num_vertices = obj_data->count_vertex;
    double *vertex_array = obj_data->vertex;
    for (size_t i = 0; i < 3 * num_vertices; i += 3) {
      vertex_array[i + 1] += delta_y;
    }
  }
}

void move_z(obj_data *obj_data, double delta_z) {
  if (delta_z != 0.0) {
    size_t num_vertices = obj_data->count_vertex;
    double *vertex_array = obj_data->vertex;
    for (size_t i = 0; i < 3 * num_vertices; i += 3) {
      vertex_array[i + 2] += delta_z;
    }
  }
}
