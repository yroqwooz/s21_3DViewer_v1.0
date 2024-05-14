#include "s21_parser.h"

void CountObjData(FILE *file, obj_data *data) {
  char *str = NULL;
  size_t lenght = 0;
  while (getline(&str, &lenght, file) != EOF) {
    if (strncmp(str, "v ", 2) == 0) {
      data->count_vertex++;
    } else if (strncmp(str, "f ", 2) == 0) {
      char *token = strtok(str + 2, " ");
      while (token) {
        if (atoi(token)) data->count_edges++;
        token = strtok(NULL, " ");
      }
    }
  }
  if (str) free(str);
  fseek(file, 0, SEEK_SET);
}

void FreeMemory(obj_data *data) {
  if (data->vertex) free(data->vertex);
  if (data->edges) free(data->edges);
  data->count_vertex = 0;
  data->count_edges = 0;
  data->vertex = NULL;
  data->edges = NULL;
}

int AllocateMemory(obj_data *data) {
  int exit = OK;
  data->vertex = calloc(data->count_vertex * 3, sizeof(double));
  data->edges = calloc(data->count_edges * 2, sizeof(unsigned));
  if (!data->vertex || !data->edges) {
    exit = MEMORYERROR;
    FreeMemory(data);
  }
  return exit;
}

void ParseEdge(obj_data *data, char *str, size_t *it_f,
               size_t current_count_vertex) {
  char *token = strtok(str + 2, " ");
  unsigned first_index = 0;
  bool is_first_index = true;
  while (token) {
    long index = atoi(token);
    if (index < 0)
      index += current_count_vertex;
    else
      index -= 1;

    if (is_first_index && atoi(token)) {
      first_index = index;
      data->edges[*it_f] = first_index;
      *it_f += 1;
      is_first_index = false;
    } else if (atoi(token)) {
      data->edges[*it_f] = index;
      *it_f += 1;
      data->edges[*it_f] = index;
      *it_f += 1;
    }
    token = strtok(NULL, " ");
  }
  data->edges[*it_f] = first_index;
  *it_f += 1;
}

int ParseVertex(obj_data *data, char *str, size_t *it_v,
                size_t *current_count_vertex, min_max_struct *lim) {
  int exit = OK;
  double x = 0, y = 0, z = 0;
  if (sscanf(str, "v %lf %lf %lf", &x, &y, &z) == 3) {
    data->vertex[*it_v] = x;
    *it_v += 1;
    data->vertex[*it_v] = y;
    *it_v += 1;
    data->vertex[*it_v] = z;
    *it_v += 1;
    *current_count_vertex += 1;

    lim->min_x = fmin(lim->min_x, x);
    // printf("%lf\n", lim->min_x);
    lim->min_y = fmin(lim->min_y, y);
    lim->min_z = fmin(lim->min_z, z);

    lim->max_x = fmax(lim->max_x, x);
    // printf("%lf\n", lim->min_x + lim->max_x);
    lim->max_y = fmax(lim->max_y, y);
    lim->max_z = fmax(lim->max_z, z);
  } else
    exit = INCORRECTDATA;
  return exit;
}

int ParseData(FILE *file, obj_data *data) {
  int exit = AllocateMemory(data);
  min_max_struct lim = {DBL_MAX,  DBL_MAX,  DBL_MAX,
                        -DBL_MAX, -DBL_MAX, -DBL_MAX};
  if (exit == OK) {
    char *str = NULL;
    size_t lenght = 0, it_v = 0, it_f = 0, current_count_vertex = 0;
    while (getline(&str, &lenght, file) != EOF && exit == OK) {
      if (strncmp(str, "v ", 2) == 0) {
        exit = ParseVertex(data, str, &it_v, &current_count_vertex, &lim);
      } else if (strncmp(str, "f ", 2) == 0) {
        ParseEdge(data, str, &it_f, current_count_vertex);
      }
    }

    if (str) free(str);
  }
  // printf("Before: %lf %lf %lf\n", data->vertex[0], data->vertex[1],
  // data->vertex[2]);
  move_x(data, -((lim.min_x + lim.max_x) / 2));
  // printf("After: %lf %lf %lf\n", data->vertex[0], data->vertex[1],
  // data->vertex[2]);
  move_y(data, -((lim.min_y + lim.max_y) / 2));
  move_z(data, -((lim.min_z + lim.max_z) / 2));
  return exit;
}

int ParsingFile(const char *filename, obj_data *data) {
  if (!filename || !data) return INCORRECTFILE;
  int exit = 0;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    exit = INCORRECTFILE;
  } else {
    CountObjData(file, data);
    exit = ParseData(file, data);
    fclose(file);
  }
  if (exit != OK) FreeMemory(data);
  return exit;
}
