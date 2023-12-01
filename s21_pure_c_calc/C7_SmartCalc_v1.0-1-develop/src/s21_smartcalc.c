#include "s21_smartcalc.h"

double s21_smartcalc(const char* input) {
  double result = 0;
  stack *general_inversed = NULL, *general = NULL;
  stack *output = NULL, *output_for_calc = NULL;

  general = stack_reverse(parse(&general_inversed, input));
  output = polish(&general);
  output_for_calc = stack_reverse(&output);
  result = calculation(output_for_calc);
  delete_stack(&output_for_calc);
  return result;
}

void transfer(stack* output, stack** result) {
  double value = output->value;
  int priority = output->priority;
  type_t type = output->type;
  push_stack(result, value, priority, type);
}

void unary_calc(stack* output, stack** result) {
  if (output->next->type == 7) {
    double value = sqrt(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 8) {
    double value = log(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 9) {
    double value = log10(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 10) {
    double value = sin(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 11) {
    double value = cos(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 12) {
    double value = tan(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 13) {
    double value = asin(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 14) {
    double value = acos(output->value);
    push_stack(result, value, 0, 0);
  }
  if (output->next->type == 15) {
    double value = atan(output->value);
    push_stack(result, value, 0, 0);
  }
}

void binary_calc(stack* output, stack** result) {
  if (output->next->next->type == 1) {
    double value = output->value + output->next->value;
    push_stack(result, value, 0, 0);
  } else if (output->next->next->type == 2) {
    double value = output->value - output->next->value;
    push_stack(result, value, 0, 0);
  } else if (output->next->next->type == 3) {
    double value = output->value * output->next->value;
    push_stack(result, value, 0, 0);
  } else if (output->next->next->type == 4) {
    double value = output->value / output->next->value;
    push_stack(result, value, 0, 0);
  } else if (output->next->next->type == 5) {
    double value = fmod(output->value, output->next->value);
    push_stack(result, value, 0, 0);
  } else if (output->next->next->type == 6) {
    double value = pow(output->value, output->next->value);
    push_stack(result, value, 0, 0);
  }
}

double calculation(stack* output) {
  double num = 0;
  stack* result = NULL;
  while (output) {
    result = NULL;
    while (output) {
      if (output || output->next || output->next->next) {
        if (output->next && output->type == 0 &&
            (output->next->type > 6 && output->next->type < 16)) {
          unary_calc(output, &result);
          output = output->next->next;
        } else if (output->next && output->next->next && output->type == 0 &&
                   output->next->type == 0 &&
                   (output->next->next->type > 0 &&
                    output->next->next->type < 7)) {
          binary_calc(output, &result);
          output = output->next->next->next;
        } else if ((output->type == 0 && output->next &&
                    (output->next->type > 0)) ||
                   output->type > 0) {
          transfer(output, &result);
          output = output->next;
        } else if (output) {
          transfer(output, &result);
          output = output->next;
        }
      }
    }
    if (result->next == 0) num = result->value;
    output = stack_reverse(&result);
    if (output->next == 0) break;
  }
  delete_stack(&output);
  return (num);
}

stack* polish(stack** general) {
  stack* output = NULL;
  stack* aux = NULL;
  while (*general) {
    if ((*general)->type == 0 || (*general)->type == 18)
      push_stack(&output, (*general)->value, (*general)->priority,
                 (*general)->type);
    else if ((*general)->type == 16)
      push_stack(&aux, (*general)->value, (*general)->priority,
                 (*general)->type);
    else if ((*general)->type == 17) {
      while (aux->type != 16) {
        push_stack(&output, aux->value, aux->priority, aux->type);
        pop_stack(&aux);
      }
      pop_stack(&aux);
    } else if (aux != NULL && (*general)->priority > 0 &&
               (*general)->priority > aux->priority)
      push_stack(&aux, (*general)->value, (*general)->priority,
                 (*general)->type);
    else if (aux == NULL && (*general)->priority > 0)
      push_stack(&aux, (*general)->value, (*general)->priority,
                 (*general)->type);
    else if ((*general)->priority > 0 && (*general)->type != 16 &&
             (*general)->type != 17 && (*general)->priority <= aux->priority) {
      while ((aux) && ((*general)->priority <= aux->priority)) {
        push_stack(&output, aux->value, aux->priority, aux->type);
        pop_stack(&aux);
      }
      push_stack(&aux, (*general)->value, (*general)->priority,
                 (*general)->type);
    }
    pop_stack(general);
  }
  while (aux) {
    push_stack(&output, aux->value, aux->priority, aux->type);
    pop_stack(&aux);
  }
  return (output);
}

stack* stack_reverse(stack** top) {
  stack* tmp = NULL;
  while (*top) {
    push_stack(&tmp, (*top)->value, (*top)->priority, (*top)->type);
    pop_stack(top);
  }
  return tmp;
}

stack** parse(stack** top, const char* input) {
  const char* begin = input;
  while (*input != '\0') {
    if (is_digit(*input)) {
      setlocale(LC_ALL, "C");
      char num[256];
      char* p_num = num;
      while (is_digit(*input) || *input == '.') *p_num++ = *input++;
      *p_num = '\0';
      push_stack(top, atof(num), 0, 0);
    } else if (*input == '+') {
      if (input == begin) {
        push_stack(top, 0.0, 0, 0);
      } else if (*(input - 1) == '(' && is_digit(*(input + 1))) {
        push_stack(top, 0.0, 0, 0);
      }
      push_stack(top, -1, 1, 1);
      input++;
    } else if (*input == '-') {
      if (input == begin) {
        push_stack(top, 0.0, 0, 0);
      } else if (*(input - 1) == '(' && is_digit(*(input + 1))) {
        push_stack(top, 0.0, 0, 0);
      }
      push_stack(top, -1, 1, 2);
      input++;
    } else if (*input == '*') {
      push_stack(top, -1, 2, 3);
      input++;
    } else if (*input == '/') {
      push_stack(top, -1, 2, 4);
      input++;
    } else if (*input == 'm') {
      push_stack(top, -1, 3, 5);
      input += 3;
    } else if (*input == '^') {
      push_stack(top, -1, 4, 6);
      input++;
    } else if (*input == 's' && *(input + 1) == 'q') {
      push_stack(top, -1, 5, 7);
      input += 4;
    } else if (*input == 'l' && *(input + 1) == 'n') {
      push_stack(top, -1, 5, 8);
      input += 2;
    } else if (*input == 'l' && *(input + 1) == 'o') {
      push_stack(top, -1, 5, 9);
      input += 3;
    } else if (*input == 's' && *(input + 1) == 'i') {
      push_stack(top, -1, 5, 10);
      input += 3;
    } else if (*input == 'c' && *(input + 1) == 'o') {
      push_stack(top, -1, 5, 11);
      input += 3;
    } else if (*input == 't' && *(input + 1) == 'a') {
      push_stack(top, -1, 5, 12);
      input += 3;
    } else if (*input == 'a' && *(input + 1) == 's') {
      push_stack(top, -1, 5, 13);
      input += 4;
    } else if (*input == 'a' && *(input + 1) == 'c') {
      push_stack(top, -1, 5, 14);
      input += 4;
    } else if (*input == 'a' && *(input + 1) == 't') {
      push_stack(top, -1, 5, 15);
      input += 4;
    } else if (*input == '(') {
      push_stack(top, -1, -1, 16);
      input++;
    } else if (*input == ')') {
      push_stack(top, -1, -1, 17);
      input++;
    } else if (*input == 'x' || *input == 'X') {
      push_stack(top, -1, 0, 18);
      input++;
    }
  }
  return top;
}

int validate_expression(const char* input) {
  int result = SUCCESS;
  if (!is_permissible(input) || !is_real(input) || !is_bracket(input) ||
      !is_function(input)) {
    result = FAIL;
  }
  return result;
}

int validate_numbers(const char* input) {
  int result = SUCCESS;
  if (!is_permissible_numbers(input) || !is_real(input)) {
    result = FAIL;
  }
  return result;
}

int is_permissible_numbers(const char* input) {
  int result = SUCCESS;
  const char* pool = "0123456789.+-";
  while (*input != '\0') {
    if (!strchr(pool, *input)) {
      result = FAIL;
    }
    input++;
  }
  return result;
}

int is_function(const char* input) {
  int result = SUCCESS;
  while (*input != '\0') {
    if (*input == 'm') {
      if ((*(input + 1) == 'o') && (*(input + 2) == 'd') &&
          (is_digit(*(input + 3)) || (*(input + 3) == '(') ||
           (*(input + 3) == 'x') || (*(input + 3) == 'l') ||
           (*(input + 3) == 'a') || (*(input + 3) == 'c') ||
           (*(input + 3) == 's') || (*(input + 3) == 't'))) {
      } else
        result = FAIL;
    } else if (*input == 'l') {
      if ((*(input + 1) == 'n' && (*(input + 2) == '(')) ||
          (*(input + 1) == 'o' && *(input + 2) == 'g' &&
           (*(input + 3) == '('))) {
      } else
        result = FAIL;
    } else if (*input == 'c') {
      if (*(input + 1) == 'o' && *(input + 2) == 's' && *(input + 3) == '(') {
      } else if (*(input - 1) == 'a' && *(input + 1) == 'o' &&
                 (*(input + 2) == 's') && (*(input + 3) == '(')) {
      } else
        result = FAIL;
    } else if (*input == 't') {
      if (*(input - 1) != 'r' && *(input + 1) == 'a' && *(input + 2) == 'n' &&
          *(input + 3) == '(') {
      } else if (*(input - 3) == 's' && *(input - 2) == 'q' &&
                 *(input - 1) == 'r' && *(input + 1) == '(') {
      } else
        result = FAIL;
    } else if (*input == 's') {
      if ((*(input + 1) == 'i' && (*(input + 2) == 'n') &&
           (*(input + 3) == '(')) ||
          (*(input + 1) == 'q' && (*(input + 2) == 'r') &&
           (*(input + 3) == 't') && (*(input + 4) == '('))) {
      } else if (*(input - 1) == 'a' && *(input + 1) == 'i' &&
                 (*(input + 2) == 'n') && (*(input + 3) == '(')) {
      } else if (*(input - 3) == 'a' && *(input - 2) == 'c' &&
                 (*(input - 1) == 'o') && (*(input + 1) == '(')) {
      } else if (*(input - 2) == 'c' && (*(input - 1) == 'o') &&
                 (*(input + 1) == '(')) {
      } else
        result = FAIL;
    } else if (strchr("+-*/^", *input)) {
      char* pool = "0123456789x(acsltm";
      if (strchr(pool, *(input + 1))) {
      } else
        result = FAIL;
    }
    input++;
  }
  return result;
}

int is_permissible(const char* input) {
  int result = SUCCESS;
  const char* pool = "acdgilmnorqstx0123456789()+-*/^.";
  const char* pool_2 = "(+-*/^.";
  while (*input != '\0') {
    if (!strchr(pool, *input)) {
      result = FAIL;
    } else if (strchr(pool_2, *input) && *(input + 1) == '\0') {
      result = FAIL;
    }
    input++;
  }
  return result;
}

int is_bracket(const char* input) {
  int result = SUCCESS;
  const char* pool = "aclmstx0123456789(+-*/^";
  int count_left = 0;
  int count_right = 0;
  while (*input != '\0') {
    if (*input == '(' && strchr(pool, *(input + 1)))
      count_left++;
    else if (*input == ')')
      count_right++;
    input++;
  }
  if (count_left != count_right) result = FAIL;
  return result;
}

int is_real(const char* input) {
  int result = SUCCESS;
  while (*input != '\0') {
    if ((*input == '.') && (!is_digit(*(input + 1)) || !is_digit(*(input - 1))))
      result = FAIL;
    input++;
  }
  return result;
}

int is_digit(char input) {
  int result = SUCCESS;
  if ('0' > input || input > '9') result = FAIL;
  return result;
}

void push_stack(stack** top, double value, int priority, type_t type) {
  stack* tmp = malloc(sizeof(stack));
  tmp->value = value;
  tmp->priority = priority;
  tmp->type = type;
  tmp->next = *top;
  *top = tmp;
}

void pop_stack(stack** top) {
  if (!top) return;
  stack* tmp = *top;
  *top = (*top)->next;
  free(tmp);
}

void delete_stack(stack** top) {
  while (*top) {
    pop_stack(top);
  }
}