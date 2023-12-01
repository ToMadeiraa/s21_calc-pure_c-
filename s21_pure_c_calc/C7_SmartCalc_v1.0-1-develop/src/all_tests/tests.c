#include <check.h>

#include "../s21_smartcalc.h"

/* GENERAL */
START_TEST(general_1) {
  char test[] = "0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(general_2) {
  char test[] = "1";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1);
}
END_TEST

START_TEST(general_3) {
  char test[] = "25";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 25);
}
END_TEST

START_TEST(general_4) {
  char test[] = "-25";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, -25);
}
END_TEST

START_TEST(general_5) {
  char test[] = "-0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(general_6) {
  char test[] = "0.1";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0.1);
}
END_TEST

START_TEST(general_7) {
  char test[] = "123.456";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 123.456);
}
END_TEST

START_TEST(general_8) {
  char test[] = "-123.456";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, -123.456);
}
END_TEST

START_TEST(general_9) {
  char test[] = "+0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(general_10) {
  char test[] = "+1";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1);
}
END_TEST

START_TEST(general_11) {
  char test[] = "+25";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 25);
}
END_TEST

/* PLUS */
START_TEST(plus_1) {
  char test[] = "0+0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(plus_2) {
  char test[] = "0+1";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1);
}
END_TEST

START_TEST(plus_3) {
  char test[] = "0+1+2";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 3);
}
END_TEST

START_TEST(plus_4) {
  char test[] = "0+1+2+3";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 6);
}
END_TEST

START_TEST(plus_5) {
  char test[] = "1+2+3+4+5";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 15);
}
END_TEST

START_TEST(plus_6) {
  char test[] = "0+1.5";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1.5);
}
END_TEST

START_TEST(plus_7) {
  char test[] = "1.5+1.5";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 3);
}
END_TEST

START_TEST(plus_8) {
  char test[] = "2.5+1.5";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 2.5 + 1.5);
}
END_TEST

START_TEST(plus_9) {
  char test[] = "123.456+76.544";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 200);
}
END_TEST

START_TEST(plus_10) {
  char test[] = "123.456+(-123.456)";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(plus_11) {
  char test[] = "-0+0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(plus_12) {
  char test[] = "-0+0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(plus_13) {
  char test[] = "-125+25";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, -100);
}
END_TEST

START_TEST(plus_14) {
  char test[] = "-666.666+0.666";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, -666, 1E-07);
}
END_TEST

START_TEST(plus_15) {
  char test[] = "-666.666+0.666";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, -666, 1E-07);
}
END_TEST

// /* MINUS */
START_TEST(minus_1) {
  char test[] = "1-1";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(minus_2) {
  char test[] = "1.5-1";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0.5);
}
END_TEST

START_TEST(minus_3) {
  char test[] = "1.5-0.5";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1);
}
END_TEST

START_TEST(minus_4) {
  char test[] = "1.5-1.2";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, 0.3, 1E-07);
}
END_TEST

START_TEST(minus_5) {
  char test[] = "666.666-123.456";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, 666.666 - 123.456, 1E-07);
}
END_TEST

START_TEST(minus_6) {
  char test[] = "666.666-(+123.456)";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, 666.666 - (+123.456), 1E-07);
}
END_TEST

START_TEST(minus_7) {
  char test[] = "666.666-(+123.456)";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, 666.666 - (+123.456), 1E-07);
}
END_TEST

START_TEST(minus_8) {
  char test[] = "10-20";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, -10.0);
}
END_TEST

/* DIV */
START_TEST(div_1) {
  char test[] = "10/20";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0.5);
}
END_TEST

START_TEST(div_2) {
  char test[] = "0/0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_nan(result);
}
END_TEST

START_TEST(div_3) {
  char test[] = "-0/0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_nan(result);
}
END_TEST

START_TEST(div_4) {
  char test[] = "666/333";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 2);
}
END_TEST

START_TEST(div_5) {
  char test[] = "666.666/333.333";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 2);
}
END_TEST

START_TEST(div_6) {
  char test[] = "1/0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_infinite(result);
}
END_TEST

START_TEST(div_7) {
  char test[] = "-1/0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_infinite(result);
}
END_TEST

// /* MULTI */
START_TEST(multi_1) {
  char test[] = "0*0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(multi_2) {
  char test[] = "-0*0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(multi_3) {
  char test[] = "-0*(-0)";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(multi_4) {
  char test[] = "2*2";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 4);
}
END_TEST

START_TEST(multi_5) {
  char test[] = "2*2*2";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 8);
}
END_TEST

START_TEST(multi_6) {
  char test[] = "1*0";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 0);
}
END_TEST

START_TEST(multi_7) {
  char test[] = "10*10";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 100);
}
END_TEST

START_TEST(multi_8) {
  char test[] = "1.5*2.5";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1.5 * 2.5);
}
END_TEST

/* COMPLECATED */
START_TEST(comp_1) {
  char test[] = "1+2*3-10";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1 + 2 * 3 - 10);
}
END_TEST

START_TEST(comp_2) {
  char test[] = "1+2*3^10";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, 1 + 2 * pow(3, 10));
}
END_TEST

START_TEST(comp_3) {
  char test[] = "sin(10)+cos(ln(20.5)-123.456/0.01)";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq_tol(result, sin(10) + cos(log(20.5) - 123.456 / 0.01),
                           1E-06);
}
END_TEST

START_TEST(comp_4) {
  char test[] = "sin(cos(20mod19)+0.05^(-3))";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, sin(cos(20 % 19) + pow(0.05, -3)));
}
END_TEST

START_TEST(comp_5) {
  char test[] = "sin(cos(20modln(19))+0.05^(-3))";
  double result = s21_smartcalc(test);
  ck_assert_ldouble_eq(result, sin(cos(fmod(20, log(19))) + pow(0.05, -3)));
}
END_TEST

/* MISCELLANEOUS */
START_TEST(misc_1) {
  char test[] = "123+ln(x)-5";
  int result = validate_expression(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(misc_2) {
  char test[] = "-90.123";
  int result = validate_numbers(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(misc_3) {
  char test[] = "sin(x)";
  int result = validate_expression(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(misc_4) {
  char test[] = "tan(x)";
  int result = validate_expression(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(misc_5) {
  char test[] = "5mod3";
  int result = validate_expression(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(misc_6) {
  char test[] = "sqrt(asin(x))";
  int result = validate_expression(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(misc_7) {
  char test[] = "acos(x)";
  int result = validate_expression(test);
  ck_assert_int_eq(result, 1);
}
END_TEST

Suite *example_create() {
  Suite *suite = suite_create("TESTS");

  TCase *tcase_general = tcase_create("GENERAL");
  tcase_add_test(tcase_general, general_1);
  tcase_add_test(tcase_general, general_2);
  tcase_add_test(tcase_general, general_3);
  tcase_add_test(tcase_general, general_4);
  tcase_add_test(tcase_general, general_5);
  tcase_add_test(tcase_general, general_6);
  tcase_add_test(tcase_general, general_7);
  tcase_add_test(tcase_general, general_8);
  tcase_add_test(tcase_general, general_9);
  tcase_add_test(tcase_general, general_10);
  tcase_add_test(tcase_general, general_11);
  suite_add_tcase(suite, tcase_general);

  TCase *tcase_plus = tcase_create("PLUS");
  tcase_add_test(tcase_plus, plus_1);
  tcase_add_test(tcase_plus, plus_2);
  tcase_add_test(tcase_plus, plus_3);
  tcase_add_test(tcase_plus, plus_4);
  tcase_add_test(tcase_plus, plus_5);
  tcase_add_test(tcase_plus, plus_6);
  tcase_add_test(tcase_plus, plus_7);
  tcase_add_test(tcase_plus, plus_8);
  tcase_add_test(tcase_plus, plus_9);
  tcase_add_test(tcase_plus, plus_10);
  tcase_add_test(tcase_plus, plus_11);
  tcase_add_test(tcase_plus, plus_12);
  tcase_add_test(tcase_plus, plus_13);
  tcase_add_test(tcase_plus, plus_14);
  tcase_add_test(tcase_plus, plus_15);
  suite_add_tcase(suite, tcase_plus);

  TCase *tcase_minus = tcase_create("MINUS");
  tcase_add_test(tcase_minus, minus_1);
  tcase_add_test(tcase_minus, minus_2);
  tcase_add_test(tcase_minus, minus_3);
  tcase_add_test(tcase_minus, minus_4);
  tcase_add_test(tcase_minus, minus_5);
  tcase_add_test(tcase_minus, minus_6);
  tcase_add_test(tcase_minus, minus_7);
  tcase_add_test(tcase_minus, minus_8);
  suite_add_tcase(suite, tcase_minus);

  TCase *tcase_div = tcase_create("DIV");
  tcase_add_test(tcase_div, div_1);
  tcase_add_test(tcase_div, div_2);
  tcase_add_test(tcase_div, div_3);
  tcase_add_test(tcase_div, div_4);
  tcase_add_test(tcase_div, div_5);
  tcase_add_test(tcase_div, div_6);
  tcase_add_test(tcase_div, div_7);
  suite_add_tcase(suite, tcase_div);

  TCase *tcase_multi = tcase_create("MULTI");
  tcase_add_test(tcase_multi, multi_1);
  tcase_add_test(tcase_multi, multi_2);
  tcase_add_test(tcase_multi, multi_3);
  tcase_add_test(tcase_multi, multi_4);
  tcase_add_test(tcase_multi, multi_5);
  tcase_add_test(tcase_multi, multi_6);
  tcase_add_test(tcase_multi, multi_7);
  tcase_add_test(tcase_multi, multi_8);
  suite_add_tcase(suite, tcase_multi);

  TCase *tcase_comp = tcase_create("COMP");
  tcase_add_test(tcase_comp, comp_1);
  tcase_add_test(tcase_comp, comp_2);
  tcase_add_test(tcase_comp, comp_3);
  tcase_add_test(tcase_comp, comp_4);
  tcase_add_test(tcase_comp, comp_5);
  suite_add_tcase(suite, tcase_comp);

  TCase *tcase_misc = tcase_create("MISC");
  tcase_add_test(tcase_misc, misc_1);
  tcase_add_test(tcase_misc, misc_2);
  tcase_add_test(tcase_misc, misc_3);
  tcase_add_test(tcase_misc, misc_4);
  tcase_add_test(tcase_misc, misc_5);
  tcase_add_test(tcase_misc, misc_6);
  tcase_add_test(tcase_misc, misc_7);
  suite_add_tcase(suite, tcase_misc);

  return suite;
}

int main() {
  int count;
  Suite *s = example_create();
  SRunner *runner = srunner_create(s);
  srunner_run_all(runner, CK_NORMAL);
  count = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}