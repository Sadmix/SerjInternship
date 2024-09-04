#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* atof: преобразование строки s в double 
double atof (char s[])
{
double val, power;
int i, sign;
for (i = 0; isspace (s[i]); i++)
; игнорирование левых символов-разделителей 
sign = (s[i] == '-') ? -1 : 1;
if (s[i] == '+' || s[i] == '-')
i++;
for (val = 0.0; isdigit (s[i]); i++)
val = 10.0 * val + (s[i] - '0');
if (s[i] =='.')
i++;
for (power = 1.0; isdigit(s[i]); i++) {
val = 10.0 * val + (s[i] - '0');
power *= 10.0;
}
return sign * val / power;
} */


/* Дополните функцию atof таким образом, чтобы она справлялась с числами вида
123.456e-6 */



/* atof: преобразование строки s в double */
double atof(char s[]) {
    double val, power;
    int i, sign, exp_sign;
    int exp = 0; // Переменная для хранения значения экспоненты

    // Пропуск начальных символов-разделителей
    for (i = 0; isspace(s[i]); i++)
        ;

    // Определение знака числа
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    // Преобразование целой части числа
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    // Преобразование дробной части числа
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    
    // Применение знака и деление на power, чтобы получить число с плавающей точкой
    val = sign * val / power;

    // Обработка экспоненты (если есть)
    if (s[i] == 'e' || s[i] == 'E') {
        i++;
        exp_sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
            i++;
        for (exp = 0; isdigit(s[i]); i++)
            exp = 10 * exp + (s[i] - '0');
        if (exp_sign == 1)
            while (exp-- > 0)
                val *= 10;
        else
            while (exp-- > 0)
                val /= 10;
    }

    return val;
}