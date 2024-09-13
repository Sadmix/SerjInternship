#include <stdio.h>
#include <string.h>
#include <ctype.h>  // Для использования функции tolower

/* Функция для поиска самого правого вхождения строки t в строку s, игнорируя регистр символов */
int strindexNoCase(char s[], char t[]) {
    int i, j, k;
    int pos = -1;  // Инициализируем переменную pos значением -1
    
    for (i = 0; s[i] != '\0'; i++) {
        for (j = i, k = 0; t[k] != '\0' && tolower(s[j]) == tolower(t[k]); j++, k++)
            ;
        if (k > 0 && t[k] == '\0')  // Если строка t полностью совпала с частью строки s
            pos = i;  // Обновляем позицию, но продолжаем искать дальше
    }
    
    return pos;
}

int main() {
    char s[] = "Hello, world! Hello!";
    char t[] = "hELLO";
    
    int pos = strindexNoCase(s, t);
    
    if (pos != -1)
        printf("Самое правое вхождение строки \"%s\" в строку \"%s\" начинается с позиции %d\n", t, s, pos);
    else
        printf("Вхождение строки \"%s\" в строку \"%s\" не найдено\n", t, s);
    
    return 0;
}