#include <stdio.h>
#include <string.h>

void itoa_recursive(int n, char s[], int *i) {
    if (n < 0) {  // обрабатываем отрицательное число
        s[(*i)++] = '-';
        n = -n;
    }

    if (n / 10)  // рекурсивный вызов для следующей цифры
        itoa_recursive(n / 10, s, i);

    s[(*i)++] = n % 10 + '0';  // добавляем текущую цифру
}

void itoa(int n, char s[]) {
    int i = 0;  // инициализируем индекс
    itoa_recursive(n, s, &i);  // вызываем рекурсивную функцию
    s[i] = '\0';  // завершаем строку
}

int main() {
    int num = -12345;
    char str[100];
    
    itoa(num, str);
    printf("Результат: %s\n", str);
    
    return 0;
}