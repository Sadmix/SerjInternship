/* Введите команды для работы с переменными (легко обеспечить до 26 переменных, каждая
из которых имеет имя, представленное одной буквой латинского алфавита). Добавьте переменную,
предназначенную для хранения самого последнего из напечатанных значений. */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAXOP 100    // макс. размер операнда или оператора
#define NUMBER '0'   // признак числа
#define VAR '1'      // признак переменной

int getop(char []);
void push(double);
double pop(void);
void print_top(void);
void duplicate_top(void);
void swap_top_two(void);
void clear_stack(void);
void assign_var(char var, double value);
double get_var(char var);

double last_printed = 0.0;  // переменная для хранения последнего напечатанного значения */
double variables[26];       // массив для 26 переменных

int main() {
    int type;
    double op2;
    char s[MAXOP];
    char var = 0;

    while ((type = getop(s)) != EOF) {
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
            case '=':  // Присваивание переменной
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
                print_top();
                break;
            case 'D':
                duplicate_top();
                break;
            case 'S':
                swap_top_two();
                break;
            case 'C':
                clear_stack();
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
    return 0;
}

#define MAXVAL 100

int sp = 0;          // следующая свободная позиция в стеке
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

void print_top(void) {
    if (sp > 0)
        printf("Верхний элемент стека: %.8g\n", val[sp-1]);
    else
        printf("ошибка: стек пуст\n");
}

void duplicate_top(void) {
    if (sp > 0 && sp < MAXVAL) {
        double top = val[sp-1];
        push(top);
    } else if (sp == 0) {
        printf("ошибка: стек пуст\n");
    } else {
        printf("ошибка: стек полон, нельзя дублировать элемент\n");
    }
}

void swap_top_two(void) {
    if (sp > 1) {
        double top1 = val[sp-1];
        double top2 = val[sp-2];
        val[sp-1] = top2;
        val[sp-2] = top1;
    } else {
        printf("ошибка: недостаточно элементов в стеке для обмена\n");
    }
}

void clear_stack(void) {
    sp = 0;
    printf("Стек очищен\n");
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

int getch(void);
void ungetch(int);

int getop(char s[]) {
    int i, c;
    static int lastc = 0;

    if (lastc != 0) {
        c = lastc;
        lastc = 0;
    } else {
        c = getch();
    }

    while ((s[0] = c) == ' ' || c == '\t')
        c = getch();
    s[1] = '\0';

    if (isalpha(c)) {
        return VAR;
    }

    i = 0;
    if (c == '-' && !isdigit(c = getch())) {
        lastc = c;
        return '-';
    } else if (c == '-' && isdigit(c)) {
        s[++i] = c;
    } else {
        lastc = c;
    }

    if (!isdigit(c) && c != '.')
        return s[0];

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lastc = c;
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}