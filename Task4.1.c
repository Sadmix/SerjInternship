#include <stdio.h>
#include <string.h>

/* Напишите функцию strindex(s, t), которая выдает позицию самого правого вхождения
t в s или -1, если вхождения не обнаружено. */

int strindex(char s[], char t[]) {
    int i, j, k;
    int pos = -1;  // Инициализируем переменную pos значением -1
    
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')  // Если строка t полностью совпала с частью строки s
            pos = i;  // Обновляем позицию, но продолжаем искать дальше
    }
    
    return pos;
}

int main() {
    char s[] = "Hello, world! Hello!";
    char t[] = "Hello";
    
    int pos = strindex(s, t);
    
    if (pos != -1)
        printf("Самое правое вхождение строки \"%s\" в строку \"%s\" начинается с позиции %d\n", t, s, pos);
    else
        printf("Вхождение строки \"%s\" в строку \"%s\" не найдено\n", t, s);
    
    return 0;
}