/* Исходя из предложенной нами схемы, дополните программу-калькулятор таким образом,
чтобы она "понимала" оператор получения остатка от деления (%) и отрицательные числа. */

#include <stdio.h>
#include <stdlib.h>  // для atof() 
#include <ctype.h>   // для isdigit()
#include <math.h>    // для fmod() 

#define MAXOP 100    // макс. размер операнда или оператора 
#define NUMBER '0'   // признак числа 

int getop(char []);
void push(double);
double pop(void);

/* калькулятор с обратной польской записью */
int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
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
            case '%':  // Добавление оператора остатка от деления
                op2 = pop();
                if (op2 != 0.0)
                    push(fmod(pop(), op2));
                else
                    printf("ошибка: деление на нуль\n");
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("ошибка: неизвестная операция %s\n", s);
                break;
        }
    }
    return 0;
}

#define MAXVAL 100  /* максимальная глубина стека */

int sp = 0;          /* следующая свободная позиция в стеке */
double val[MAXVAL];  /* стек операндов */

/* push: положить значение f в стек */
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("ошибка: стек полон, нельзя поместить %g\n", f);
}

/* pop: взять и вернуть верхнее значение из стека */
double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("ошибка: стек пуст\n");
        return 0.0;
    }
}


int getch(void);
void ungetch(int);

/* getop: извлекает следующий оператор или операнд */
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

    i = 0;

    if (c == '-' && !isdigit(c = getch())) {
        lastc = c;
        return '-'; // это оператор, не число
    } else if (c == '-' && isdigit(c)) {
        s[++i] = c; // это отрицательное число
    } else {
        lastc = c;
    }

    if (!isdigit(c) && c != '.')
        return s[0];  // не число

    if (isdigit(c))  // накопление целой части 
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')    // накопление дробной части
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        lastc = c;
    return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];  /* буфер для ungetch */
int bufp = 0;       /* следующая свободная позиция в буфере */

int getch(void) {  /* взять (возможно возвращенный) символ */
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {  /* вернуть символ в поток */
    if (bufp >= BUFSIZE)
        printf("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}