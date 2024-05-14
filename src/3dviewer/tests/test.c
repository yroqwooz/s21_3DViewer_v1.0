/* designed by kerenfet, updated by ferdinan */

#include <check.h>
#include <stdio.h>


#include "../lib/s21_parser.h"
#include "../lib/s21_transform.h"


START_TEST(parser_1) {
  obj_data d = {0};
  int res = ParsingFile("./3dviewer/tests/xxx.obj", &d);
  ck_assert_int_eq(res, INCORRECTFILE);
}
END_TEST

START_TEST(parser_2) {
  obj_data d = {0};
  int res = ParsingFile(NULL, &d);
  ck_assert_int_eq(res, INCORRECTFILE);
}
END_TEST

START_TEST(parser_3) {
  obj_data d = {0};
  int res = ParsingFile("./3dviewer/tests/incorrect.obj", &d);
  ck_assert_int_eq(res, INCORRECTDATA);
}
END_TEST

// START_TEST(parser_4) {
//   obj_data d = {0};
//   int res = ParsingFile("./3dviewer/tests/cube.obj", &d);
//   ck_assert_int_eq(res, OK);
//   double vertices_v_arr[] = {
//       0.0000000, 0.0000000, 0.0000000, 0.0000000, 0.0000000, 2.0000000,
//       0.0000000, 2.0000000, 0.0000000, 0.0000000, 2.0000000, 2.0000000,
//       2.0000000, 0.0000000, 0.0000000, 2.0000000, 0.0000000, 2.0000000,
//       2.0000000, 2.0000000, 0.0000000, 2.0000000, 2.0000000, 2.0000000};
//   for (unsigned i = 0; i < d.count_vertex * 3; ++i) {
//     ck_assert_double_eq_tol(d.vertex[i], vertices_v_arr[i], 1e-07);
//   }
//   unsigned edges_f_array[] = {0, 6, 6, 4, 4, 0, 0, 2, 2, 6, 6, 0, 0, 3, 3,
//                               2, 2, 0, 0, 1, 1, 3, 3, 0, 2, 7, 7, 6, 6, 2,
//                               2, 3, 3, 7, 7, 2, 4, 6, 6, 7, 7, 4, 4, 7, 7,
//                               5, 5, 4, 0, 4, 4, 5, 5, 0, 0, 5, 5, 1, 1, 0};
//   for (unsigned i = 0; i < d.count_edges * 2; ++i) {
//     ck_assert_int_eq(d.edges[i], edges_f_array[i]);
//   }
//   FreeMemory(&d);
// }
// END_TEST

//afina test
START_TEST(parser_101) {
  obj_data d = {0};
  int res = ParsingFile("./3dviewer/tests/cube.obj", &d);
  ck_assert_int_eq(res, OK);
    FreeMemory(&d);
}
END_TEST

START_TEST(parser_102) {
  obj_data d = {0};
  double v_true_arr[] = { -1.0, -1.0, -1.0, 
                          -1.0, -1.0, 1.0, 
                          -1.0, 1.0, -1.0, 
                          -1.0, 1.0, 1.0, 
                          1.0, -1.0, -1.0, 
                          1.0, -1.0, 1.0, 
                          1.0, 1.0, -1.0, 
                          1.0, 1.0, 1.0 };
    int res = ParsingFile("./3dviewer/tests/cube.obj", &d);


    
    for (int i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
    }
    
  ck_assert_int_eq(res, OK);
    FreeMemory(&d);
}
END_TEST

/* поворот на 30 вокруг оси Х */
START_TEST(parser_103) {
    obj_data d = {0};

  double a = -30.0;
    double v_true_arr[] = {-1, -0.366025, 1.366025,  1,  -0.366025, 1.366025,
                           1,  1.366025,  0.366025,  -1, 1.366025,  0.366025,
                           -1, -1.366025, -0.366025, 1,  -1.366025, -0.366025,
                           1,  0.366025,  -1.366025, -1, 0.366025,  -1.366025};
    
    
    int res = ParsingFile("./3dviewer/tests/another_cube.obj", &d);
    
    turn_around_x(&d, a);
  for (unsigned i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-2);
  }
 
    FreeMemory(&d);
}


END_TEST

/* поворот y 90 градусов*/
START_TEST(parser_104) {
    obj_data d = {0};

  double a = -90.0;
    double v_true_arr[] = {1,  -1, 1, 1,  -1, -1, 1,  1, -1, 1,  1, 1,
                           -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1};
    int res = ParsingFile("./3dviewer/tests/another_cube.obj", &d);
    turn_around_y(&d, a);
  for (unsigned i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
  }
    FreeMemory(&d);
}
END_TEST


/* поаорот z */
START_TEST(parser_105) {
    obj_data d = {0};

  double a = -50.0;
    double v_true_arr[] = {-1.408832, 0.123257,  1,  -0.123257, -1.408832, 1,
                           1.408832,  -0.123257, 1,  0.123257,  1.408832,  1,
                           -1.408832, 0.123257,  -1, -0.123257, -1.408832, -1,
                           1.408832,  -0.123257, -1, 0.123257,  1.408832,  -1};
    int res = ParsingFile("./3dviewer/tests/another_cube.obj", &d);
    turn_around_z(&d, a);
  for (unsigned i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
  }
    FreeMemory(&d);
}
END_TEST

START_TEST(parser_106) {
    obj_data d = {0};

  double a = 1;
  double v_true_arr[] = {-1, -1, 1,  1, -1, 1,  1, 1, 1,  -1, 1, 1,
                         -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1};
    int res = ParsingFile("./3dviewer/tests/another_cube.obj", &d);
    scaling(&d, a);
  for (int i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
  }
    FreeMemory(&d);
}
END_TEST

START_TEST(parser_107) {
    obj_data d = {0};

  double a = 2;
  double v_true_arr[] = {-2, -2, 2,  2, -2, 2,  2, 2, 2,  -2, 2, 2,
                         -2, -2, -2, 2, -2, -2, 2, 2, -2, -2, 2, -2};
    int res = ParsingFile("./3dviewer/tests/another_cube.obj", &d);
    scaling(&d, a);
  for (int i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
  }
    FreeMemory(&d);
}
END_TEST

START_TEST(parser_108) {
    obj_data d = {0};

  double a = 0.1;
  double v_true_arr[] = {-0.9, -1, 1,  1.1, -1, 1,  1.1, 1, 1,  -0.9, 1, 1,
                         -0.9, -1, -1, 1.1, -1, -1, 1.1, 1, -1, -0.9, 1, -1};
    int res = ParsingFile("./3dviewer/tests/another_cube.obj", &d);
    move_x(&d, a);
  for (int i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
  }
    FreeMemory(&d);
}
END_TEST

START_TEST(parser_109) {
  obj_data d = {0};
  double v_true_arr[] = {
      -0.5,  -0.5,  0.5,
      0.5,  -0.5,  0.5,
      0.5,  0.5,  0.5,
      -0.5,  0.5,  0.5,
      -0.5,  -0.5,  -0.5,
      0.5,  -0.5,  -0.5,
      0.5,  0.5,  -0.5,
      -0.5,  0.5,  -0.5};
    int res = ParsingFile("./3dviewer/tests/another_cube2.obj", &d);
    for (int i = 0; i < d.count_vertex*3; i++) {
      ck_assert_double_eq_tol(d.vertex[i], v_true_arr[i], 1e-6);
    }
    
  ck_assert_int_eq(res, OK);
    FreeMemory(&d);
}
END_TEST



Suite *viewer_tests(void) {
  Suite *suite = suite_create("3DViewerV1.0");
  TCase *parsing = tcase_create("parsing");

  tcase_add_test(parsing, parser_1);
  tcase_add_test(parsing, parser_2);
  tcase_add_test(parsing, parser_3);
    /* afina test */
  tcase_add_test(parsing, parser_101);
  tcase_add_test(parsing, parser_102);
  tcase_add_test(parsing, parser_103);
  tcase_add_test(parsing, parser_104);
  tcase_add_test(parsing, parser_105);
  tcase_add_test(parsing, parser_106);
  tcase_add_test(parsing, parser_107);
  tcase_add_test(parsing, parser_108);
    tcase_add_test(parsing, parser_109);


  suite_add_tcase(suite, parsing);

  return suite;
}

int main(void) {
  int count_failed;
  Suite *s = viewer_tests();
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  count_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (count_failed == 0) ? 0 : 1;
}
