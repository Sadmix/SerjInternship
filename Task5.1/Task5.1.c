#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
int getint(int *pn);

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

/* прочитать следующее целое из ввода в *pn */
int getint(int *pn)
{
    int c, sign;

    while (isspace(c = getch()))  // пропуск символов разделителей
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        return c;    // Возвращаем символ, который не является числом
    }

    sign = (c == '-') ? -1 : 1;

    /* Проверяем следующий символ после + или - */
    if (c == '+' || c == '-') {
        int temp = getch();
        if (!isdigit(temp)) {     // Если за знаком не следует цифра
            ungetch(temp);        // Возвращаем символ обратно
            return c;             // Возвращаем знак как некорректный ввод
        }
        c = temp;  // Если символ является цифрой, продолжаем
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return 1;  // Возвращаем 1, если число успешно считано
}

int main(void)
{
    int n, result;
    while ((result = getint(&n)) != EOF) {
        if (result == 1)  // Если было корректно считано число
            printf("Считано число: %d\n", n);
        else
            printf("Это не число: %c\n", result);  // Выводим некорректный символ
    }

    return 0;
}