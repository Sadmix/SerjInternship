#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getfloat(float *pn);

char buf[BUFSIZE];  // буфер для ungetch
int bufp = 0;       // следующая свободная позиция в буфере

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}

/* getfloat: читает следующее число с плавающей точкой из ввода в *pn */
int getfloat(float *pn)
{
    int c, sign;
    float power = 1.0;

    while (isspace(c = getch()))  // пропуск символов разделителей
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
        return c;  // Вернуть некорректный символ
    }

    sign = (c == '-') ? -1 : 1;

    /* Проверяем следующий символ после + или - */
    if (c == '+' || c == '-') {
        int temp = getch();
        if (!isdigit(temp) && temp != '.') {  // Если за знаком не следует цифра или точка
            ungetch(temp);  // Возвращаем символ обратно
            return c;       // Возвращаем знак как некорректный ввод
        }
        c = temp;  // Если символ является цифрой или точкой, продолжаем
    }

    /* Целая часть числа */
    for (*pn = 0.0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    /* Дробная часть */
    if (c == '.') {
        c = getch();
        for (; isdigit(c); c = getch()) {
            *pn = 10.0 * *pn + (c - '0');
            power *= 10.0;  // Сдвиг для дробной части
        }
    }

    *pn *= sign / power;  // Применяем знак и масштабируем дробную часть

    if (c != EOF)
        ungetch(c);

    return 1;  // Возвращаем 1, если число успешно считано
}

int main(void)
{
    float n;
    int result;
    while ((result = getfloat(&n)) != EOF) {
        if (result == 1)  // Если было корректно считано число
            printf("Считано число с плавающей точкой: %f\n", n);
        else
            printf("Это не число: %c\n", result);  // Выводим некорректный символ
    }

    return 0;
}

/*
- В качестве основного результата в переменную передаётся значение типа float.
- Для индикации результата работы функции возвращается значение типа int.
*/