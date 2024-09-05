/* Напишите рекурсивную версию функции reverse(s), переставляющую элементы строки
в ту же строку в обратном порядке. */

#include <stdio.h>
#include <string.h>

void reverse_helper(char s[], int start, int end) {
    if (start >= end) {
        return;  // ничего не нужно менять
    }

    // Меняем местами символы на позиции start и end
    char temp = s[start];
    s[start] = s[end];
    s[end] = temp;

    // Рекурсивный вызов для следующей части строки
    reverse_helper(s, start + 1, end - 1);
}

void reverse(char s[]) {
    reverse_helper(s, 0, strlen(s) - 1);
}

int main() {
    char str[] = "hello";
    reverse(str);
    printf("Обратная строка: %s\n", str);
    return 0;
}