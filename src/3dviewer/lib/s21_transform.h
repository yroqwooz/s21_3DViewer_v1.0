#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_struct.h"

#define S21_PI 3.14159265358979323846

/* поворот */
void turn_around_x(obj_data *obj_data, double angle_degrees);
void turn_around_y(obj_data *obj_data, double angle_degrees);
void turn_around_z(obj_data *obj_data, double angle_degrees);

/* растягивание */
void scaling(obj_data *obj_data, double new_scale);

/* передвижение  */
void move_x(obj_data *obj_data, double delta_x);
void move_y(obj_data *obj_data, double delta_y);
void move_z(obj_data *obj_data, double delta_z);
