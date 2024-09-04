/* Напишите программу ungets(s), возвращающую строку s во входной поток. Должна ли
ungets "знать" что-либо о переменных buf и bufр, или ей достаточно пользоваться только функцией
ungetch? */

#include <stdio.h>
#define BUFSIZE 100

char buf[BUFSIZE];  // буфер для ungetch 
int bufp = 0;       // следующая свободная позиция в буфере

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: слишком много символов\n");
    else
        buf[bufp++] = c;
}

/* ungets: возвращает строку s во входной поток */
void ungets(char s[]) {
    int i;

    // Строка возвращается в обратном порядке, так как ungetch кладет символы в буфер
    for (i = 0; s[i] != '\0'; i++)
        ; // находим конец строки

    while (i > 0)
        ungetch(s[--i]);  // возвращаем символы строки в обратном порядке
}

int main() {
    char s[] = "Hello, world!";
    ungets(s);

    int c;
    while ((c = getch()) != EOF) {
        putchar(c); // печатаем возвращенные символы
    }

    return 0;
}