#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP 100    // макс. размер операнда или оператора
#define NUMBER '0'   // признак числа
#define VAR '1'      // признак переменной

void push(double);
double pop(void);
int getop(char s[], char line[], int *index);
void assign_var(char var, double value);
double get_var(char var);

double last_printed = 0.0;  // переменная для хранения последнего напечатанного значения
double variables[26];       // массив для 26 переменных

int main() {
    char line[MAXOP];
    int type, index;
    double op2;
    char s[MAXOP];
    char var = 0;

    while (fgets(line, MAXOP, stdin) != NULL) {
        index = 0;
        while ((type = getop(s, line, &index)) != '\0') {
            switch (type) {
                case NUMBER:
                    push(atof(s));
                    break;
                case VAR:
                    var = s[0];
                    push(get_var(var));
                    break;
                case '+':
                    push(pop() + pop());
                    break;
                case '*':
                    push(pop() * pop());
                    break;
                case '-':
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("ошибка: деление на нуль\n");
                    break;
                case '%':
                    op2 = pop();
                    if (op2 != 0.0)
                        push(fmod(pop(), op2));
                    else
                        printf("ошибка: деление на нуль\n");
                    break;
                case '=':
                    pop(); // удалить переменную из стека
                    if (var >= 'A' && var <= 'Z')
                        assign_var(var, pop());
                    else
                        printf("ошибка: неверная переменная %c\n", var);
                    break;
                case 's':
                    push(sin(pop()));
                    break;
                case 'e':
                    push(exp(pop()));
                    break;
                case 'p':
                    op2 = pop();
                    push(pow(pop(), op2));
                    break;
                case 'P':
                    printf("\t%.8g\n", last_printed);
                    break;
                case 'D':
                    push(last_printed);
                    break;
                case '\n':
                    last_printed = pop();
                    printf("\t%.8g\n", last_printed);
                    break;
                default:
                    printf("ошибка: неизвестная операция %s\n", s);
                    break;
            }
        }
    }
    return 0;
}

#define MAXVAL 100

int sp = 0;          // следующая свободная позиция в стеке
double val[MAXVAL];  // стек операндов

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("ошибка: стек полон, не могу поместить %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("ошибка: стек пуст\n");
        return 0.0;
    }
}

void assign_var(char var, double value) {
    if (var >= 'A' && var <= 'Z')
        variables[var - 'A'] = value;
    else
        printf("ошибка: неверная переменная %c\n", var);
}

double get_var(char var) {
    if (var >= 'A' && var <= 'Z')
        return variables[var - 'A'];
    else {
        printf("ошибка: неверная переменная %c\n", var);
        return 0.0;
    }
}

int getop(char s[], char line[], int *index) {
    int i = 0;
    char c;

    while ((c = line[*index]) == ' ' || c == '\t')
        (*index)++;

    s[0] = c;
    s[1] = '\0';

    if (!isdigit(c) && c != '.' && !isalpha(c) && c != '-') {
        (*index)++;
        return c;  // не число и не переменная
    }

    if (isalpha(c)) {
        (*index)++;
        return VAR;  // это переменная
    }

    if (c == '-') {
        char next = line[*index + 1];
        if (!isdigit(next) && next != '.') {
            (*index)++;
            return '-';  // это оператор вычитания, а не отрицательное число
        }
    }

    if (isdigit(c) || c == '-') {  // накопление целой части
        while (isdigit(line[++(*index)] = c = line[*index]))
            s[++i] = c;
    }

    if (c == '.')  // накопление дробной части
        while (isdigit(line[++(*index)] = c = line[*index]))
            s[++i] = c;

    s[i] = '\0';
    return NUMBER;
}