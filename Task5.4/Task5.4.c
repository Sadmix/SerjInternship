/*
Напишите функцию strend(s, t), которая выдает 1, если строка t расположена в конце
строки s, и нуль в противном случае.
*/

#include <stdio.h>

/* strend: возвращает 1, если строка t расположена в конце строки s, и 0 в противном случае */
int strend(char *s, char *t) {
    char *s_start = s;
    char *t_start = t;

    // Находим длину строк s и t
    while (*s != '\0') {
        s++;
    }
    while (*t != '\0') {
        t++;
    }

    // Проверяем, достаточно ли длинна s для строки t
    while (t >= t_start && *s == *t) {
        if (t == t_start && *s == *t) {
            return 1;  // Строка t найдена в конце строки s
        }
        s--;
        t--;
    }

    return 0;  // Строка t не найдена в конце строки s
}

int main(void) {
    char s[] = "This is a test";
    char t[] = "test";

    if (strend(s, t)) {
        printf("Строка '%s' расположена в конце строки '%s'.\n", t, s);
    } else {
        printf("Строка '%s' НЕ расположена в конце строки '%s'.\n", t, s);
    }

    return 0;
}