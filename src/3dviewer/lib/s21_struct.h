#ifndef S21_STRUCT_H
#define S21_STRUCT_H

/// @brief Структура содержит:
/// count_vertex -> количество вершин,
/// count_edges -> количество ребер,
/// vertex -> массив координат вершин типа double, где они перечисляются x y z и
/// т.д., edges -> массив векторов (массив ребер), запись идет с индексом
/// вершины начала и вершины конца.
typedef struct {
  unsigned count_vertex;
  unsigned count_edges;
  double *vertex;
  unsigned *edges;
} obj_data;

typedef struct {
  double min_x;
  double min_y;
  double min_z;
  double max_x;
  double max_y;
  double max_z;
} min_max_struct;

#endif  // S21_STRUCT_H
