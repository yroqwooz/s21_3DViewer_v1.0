#ifndef S21_PARSER_H
#define S21_PARSER_H

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_struct.h"
#include "s21_transform.h"

enum { OK, INCORRECTFILE, INCORRECTDATA, MEMORYERROR };

/// @brief Структура содержит:
/// count_vertex -> количество вершин,
/// count_edges -> количество ребер,
/// vertex -> массив координат вершин типа double, где они перечисляются x y z и
/// т.д., edges -> массив векторов (массив ребер), запись идет с индексом
/// вершины начала и вершины конца.

/// @brief Парсит переданный файл и записывает данные из него в структура data
/// @param filename Полный путь до файла относительно (pwd) или относительно от

/// проекта
/// @param data Структура, в которой хранятся данные об объекте
/// @return Возращает статус ошибки.
/// OK - нет ошибок,
/// INCORRECTFILE - передан несуществующий файл,
/// INCORRECTDATA - файл содержит некорректные данные,
/// MEMORYERROR - ошибка выделения памяти.
int ParsingFile(const char *filename, obj_data *data);

/// @brief Очищает память. Уже прописаны проверки, поэтому можно сразу
/// передавать структуру
/// @param data Структура, которую нужно очистить
void FreeMemory(obj_data *data);

#endif  // S21_PARSER
