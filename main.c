#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
void plus(double a, double b);
void minus(double a, double b);
void multiply(double a, double b);
void divide(double a, double b);
double get_number(void);
char get_first(void);

int main(void) {
    char option;
    bool a, s, m, d;
    double fir, sec;
    printf("This program executes addition, subtraction, division\n"
           "and multiplication of two numbers. You should enter two numbers and choose one\n"
           "of four operation(q for quit.\n");
    printf("Choose desirable option:\n");
    printf("a. addition          s. subtraction\n");
    printf("m. multiplication    d. division\n");
    printf("q. quit\n");
    while ((option = get_first()) != 'q') {
        a = s = m = d = false;
        switch (option) {
            case 'a': a = true;
                break;
            case 's': s = true;
                break;
            case 'm': m = true;
                break;
            case 'd': d = true;
                break;
        }
        printf("Enter the first number: \n");
        fir = get_number();
        printf("Enter the second number: \n");
        sec = get_number();

        if (a)
            plus(fir, sec);
        if (s)
            minus(fir, sec);
        if (d)
            divide(fir, sec);
        if (m)
            multiply(fir, sec);
        printf("Choose desirable option:\n");
        printf("a. addition          s. subtraction\n");
        printf("m. multiplication    d. division\n");
        printf("q. quit\n");
    }
    printf("The end of the program.");

    return 0;
}

void plus(double a, double b) {
    printf("%.1f + %.1f = %.1f\n", a, b, a + b);
}

void minus(double a, double b) {
    printf("%.1f - %.1f = %.1f\n", a, b, a - b);
}

void multiply(double a, double b) {
    printf("%.1f * %.1f = %.1f\n",a, b, a * b);
}

void divide(double a, double b) {
    while (b == 0) {
        printf("Division by zero. Enter another number.\n");
        b = get_number();
    }
    printf("%.1f / %.1f = %.1f\n", a, b, a / b);
}

char get_first(void) {
    char ch,c;
    while (1) {
        ch = tolower(getchar());
        while ((c = getchar() != '\n' && c != EOF))
            continue;
        if (ch == 'q' || ch == 'a' || ch == 's'
            || ch == 'm' || ch == 'd')
            return ch;
        else {
            printf("Invalid option\n");
            printf("Choose desirable option:\n");
            printf("a. addition          s. subtraction\n");
            printf("m. multiplication    d. division\n");
            printf("q. quit\n");
        }
    }
}

double get_number(void) {
    double num;
    char ch;
    while (scanf("%lf", &num) != 1) {

        while ((ch = getchar()) != '\n') {
            putchar(ch);
        }
        printf(" is not a number.\n");
        printf("Enter the number such as 2.5, -1.78E8 or 3: \n");

    }
    return num;

}
