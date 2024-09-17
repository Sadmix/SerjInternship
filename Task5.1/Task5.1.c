/* Функция getint написана так, что знаки - или +, за которыми не следует цифра, она
понимает как "правильное" представление нуля. Скорректируйте программу таким образом, чтобы в
подобных случаях она возвращала прочитанный знак назад во ввод. */

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
        ungetch(c);  // не число
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    /* Проверяем следующий символ после + или - */
    if (c == '+' || c == '-') {
        int temp = getch();
        if (!isdigit(temp)) {     // Если за знаком не следует цифра
            ungetch(temp);        // Возвращаем символ обратно
            ungetch(c);           // Возвращаем знак обратно
            return 0;
        }
        c = temp;  // Если символ является цифрой, продолжаем
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);

    return c;
}

int main(void)
{
    int n, result;
    while ((result = getint(&n)) != EOF) {
        if (result)  // Если было корректно считано число
            printf("Считано число: %d\n", n);
        else
            printf("Это не число\n");
    }

    return 0;
}