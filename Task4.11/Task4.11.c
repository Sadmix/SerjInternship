#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
int sp = 0;          // следующая свободная позиция в стеке

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
                    if (sp < 2) {
                        printf("ошибка: недостаточно операндов для сложения\n");
                        break;
                    }
                    push(pop() + pop());
                    break;
                case '*':
                    if (sp < 2) {
                        printf("ошибка: недостаточно операндов для умножения\n");
                        break;
                    }
                    push(pop() * pop());
                    break;
                case '-':
                    if (sp < 2) {
                        printf("ошибка: недостаточно операндов для вычитания\n");
                        break;
                    }
                    op2 = pop();
                    push(pop() - op2);
                    break;
                case '/':
                    if (sp < 2) {
                        printf("ошибка: недостаточно операндов для деления\n");
                        break;
                    }
                    op2 = pop();
                    if (op2 != 0.0)
                        push(pop() / op2);
                    else
                        printf("ошибка: деление на нуль\n");
                    break;
                case '%':
                    if (sp < 2) {
                        printf("ошибка: недостаточно операндов для остатка от деления\n");
                        break;
                    }
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

double val[MAXVAL];  // стек операндов

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("ошибка: стек полон, нельзя поместить %g\n", f);
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
    static char lastc = 0;  // статическая переменная для хранения лишнего символа

    // Проверка на наличие символа в lastc
    if (lastc != 0) {
        c = lastc;
        lastc = 0;
    } else {
        // Проверяем, не вышли ли мы за пределы строки
        if (line[*index] == '\0') {
            return '\0';  // конец строки
        }
        c = line[*index];
        (*index)++;
    }

    // Пропускаем пробелы и табуляции
    while ((s[0] = c) == ' ' || c == '\t') {
        c = line[(*index)++];
    }

    s[1] = '\0';  // Для символов или операторов устанавливаем завершающий 0

    // Если это не цифра, не точка, не буква, не минус - возвращаем оператор
    if (!isdigit(c) && c != '.' && !isalpha(c) && c != '-') {
        return c;
    }

    // Если это буква, возвращаем переменную
    if (isalpha(c)) {
        return VAR;
    }

    // Проверка на отрицательное число
    if (c == '-') {
        char next = line[*index];
        if (!isdigit(next) && next != '.') {
            return '-';  // это оператор вычитания, а не отрицательное число
        }
    }

    // Считывание целой части числа
    if (isdigit(c) || c == '-') {
        s[i++] = c;
        while (isdigit(c = line[*index])) {
            s[i++] = c;
            (*index)++;
        }
    }

    // Считывание дробной части числа
    if (c == '.') {
        s[i++] = c;
        (*index)++;
        while (isdigit(c = line[*index])) {
            s[i++] = c;
            (*index)++;
        }
    }

    s[i] = '\0';  // Завершаем строку

    // Если символ не конец строки, сохраняем его в lastc для следующего вызова
    if (c != '\0') {
        lastc = c;
    }

    return NUMBER;
}