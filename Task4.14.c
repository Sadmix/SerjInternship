/* Определите swap(t, x, y) в виде макроса, который осуществляет обмен значениями
указанного типа t между аргументами x и y. (Примените блочную структуру.) */

#include <stdio.h>

#define swap(t, x, y) { t temp = x; x = y; y = temp; }

int main() {
    int a = 5, b = 10;
    printf("До swap: a = %d, b = %d\n", a, b);
    swap(int, a, b);
    printf("После swap: a = %d, b = %d\n", a, b);

    double x = 1.23, y = 4.56;
    printf("До swap: x = %.2f, y = %.2f\n", x, y);
    swap(double, x, y);
    printf("После swap: x = %.2f, y = %.2f\n", x, y);

    return 0;
}