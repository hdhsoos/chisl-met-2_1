﻿#include <iostream>
#include <string>
#include <math.h>
using namespace std;

double F(double x) { return -exp((x * x) / 2 + x - 1.5); } // частное решение

double f(double x, double y) { return (x + 1) * y; } // исходная дифф. функция

int main() {
    setlocale(LC_ALL, "Russian");
    const double eps1 = 0.001;
    const double eps2 = 0.00001;

    double a = 1.0; double b = 2.0; double n1 = 10.0; double n2 = 20.0;
    double h1 = (b - a) / n1; double h2 = (b - a) / n2;
    double X1[100]; double Y_E1[100]; double Y_RK1[100];
    double K1_1[100]; double K2_1[100]; double K3_1[100]; double K4_1[100];
    double Y_A1[100];
    double X2[100]; double Y_E2[100]; double Y_RK2[100]; double Y_A2[100];

    X1[0] = a; Y_E1[0] = -1.0; Y_RK1[0] = -1.0; Y_A1[0] = -1.0;
    X2[0] = a; Y_E2[0] = -1.0; Y_RK2[0] = -1.0; Y_A2[0] = -1.0;

    for (int i = 1; i <= n1; i++) { X1[i] = a + i * h1; }
    for (int i = 1; i <= n2; i++) { X2[i] = a + i * h2; }
    for (int i = 0; i <= 99; i++) {}
    int i = 0;
    printf("Приближенное решение обыкновенных дифференциальных уравнений\n\n");
    printf("dy/dx = (x+1)y, y(1) = -1 на [1, 2]\n\n");
    printf("Из условия y(1) = -1 => y = -exp(x^2/2+x-1,5)\n\n");
    printf("Метод Эйлера при n = 10:\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  i |      x_i     |      y_i     |     y_i_E    |  |y_i - y_i_E| |\n");
    printf("--------------------------------------------------------------------\n");
    printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", 0, X1[0], F(X1[0]), Y_E1[0], abs(F(X1[0]) - Y_E1[0]));
    for (int i = 0; i < n1; i++) {
        Y_E1[i + 1] = Y_E1[i] + h1 * f(X1[i], Y_E1[i]); // Метод Эйлера 1
        printf("--------------------------------------------------------------------\n");
        printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", i + 1, X1[i + 1], F(X1[i + 1]), Y_E1[i + 1], abs(F(X1[i + 1]) - Y_E1[i + 1]));
    }
    printf("--------------------------------------------------------------------\n\n");
    h1 = (b - a) / n1;
    printf("Метод Рунге-Кутта при n = 10:\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  i |      x_i     |      y_i     |     y_i_RK   | |y_i - y_i_RK| |\n");
    printf("--------------------------------------------------------------------\n");
    printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", 0, X1[0], F(X1[0]), Y_RK1[0], abs(F(X1[0]) - Y_RK1[0]));
    for (int i = 0; i < n1; i++) {
        K1_1[i] = h1 * f(X1[i], Y_RK1[i]);
        K2_1[i] = h1 * f((X1[i] + h1 / 2.0), (Y_RK1[i] + K1_1[i] / 2.0));
        K3_1[i] = h1 * f((X1[i] + h1 / 2.0), (Y_RK1[i] + K2_1[i] / 2.0));
        K4_1[i] = h1 * f((X1[i] + h1), (Y_RK1[i] + K3_1[i]));
        Y_RK1[i + 1] = Y_RK1[i] + 1.0 / 6.0 * (K1_1[i] + 2.0 * K2_1[i] + 2.0 * K3_1[i] + K4_1[i]); // Метод Рунге-Кутта 1
        printf("--------------------------------------------------------------------\n");
        printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", i + 1, X1[i + 1], F(X1[i + 1]), Y_RK1[i + 1], abs(F(X1[i + 1]) - Y_RK1[i + 1]));
    }
    printf("--------------------------------------------------------------------\n\n");
    printf("Метод Адамса при n = 10:\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  i |      x_i     |      y_i     |     y_i_A    |  |y_i - y_i_A| |\n");
    printf("--------------------------------------------------------------------\n");
    printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", 0, X1[0], F(X1[0]), Y_A1[0], abs(F(X1[0]) - Y_A1[0]));
    for (int i = 0; i < n1; i++) {
        if (i < 3) {
            Y_A1[i + 1] = Y_A1[i] + 1.0 / 6.0 * (K1_1[i] + 2.0 * K2_1[i] + 2.0 * K3_1[i] + K4_1[i]);
        }
        else {
            Y_A1[i + 1] = Y_A1[i] + h1 / 24.0 * (55.0 * f(X1[i], Y_A1[i]) - 59.0 * f(X1[i - 1], Y_A1[i - 1]) + 37.0 * f(X1[i - 2], Y_A1[i - 2]) - 9.0 * f(X1[i - 3], Y_A1[i - 3])); // Метод Адамса 1
        }
        printf("--------------------------------------------------------------------\n");
        printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", i + 1, X1[i + 1], F(X1[i + 1]), Y_A1[i + 1], abs(F(X1[i + 1]) - Y_A1[i + 1]));
    }
    printf("--------------------------------------------------------------------\n\n");
    printf("\nМетод Эйлера при n = 20:\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  i |      x_i     |      y_i     |     y_i_E    |  |y_i - y_i_E| |\n");
    printf("--------------------------------------------------------------------\n");
    printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", 0, X2[0], F(X2[0]), Y_E2[0], abs(F(X2[0]) - Y_E2[0]));
    for (int i = 0; i < n2; i++) {
        Y_E2[i + 1] = Y_E2[i] + h2 * f(X2[i], Y_E2[i]); // Метод Эйлера 2
        printf("--------------------------------------------------------------------\n");
        printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", i + 1, X2[i + 1], F(X2[i + 1]), Y_E2[i + 1], abs(F(X2[i + 1]) - Y_E2[i + 1]));
    }
    printf("--------------------------------------------------------------------\n\n");
    h2 = (b - a) / n2;
    printf("Метод Рунге-Кутта при n = 20:\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  i |      x_i     |      y_i     |     y_i_RK   | |y_i - y_i_RK| |\n");
    printf("--------------------------------------------------------------------\n");
    printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", 0, X2[0], F(X2[0]), Y_RK2[0], abs(F(X2[0]) - Y_RK2[0]));
    for (int i = 0; i < n2; i++) {
        K1_1[i] = h2 * f(X2[i], Y_RK2[i]);
        K2_1[i] = h2 * f((X2[i] + h2 / 2.0), (Y_RK2[i] + K1_1[i] / 2.0));
        K3_1[i] = h2 * f((X2[i] + h2 / 2.0), (Y_RK2[i] + K2_1[i] / 2.0));
        K4_1[i] = h2 * f((X2[i] + h2), (Y_RK2[i] + K3_1[i]));
        Y_RK2[i + 1] = Y_RK2[i] + 1.0 / 6.0 * (K1_1[i] + 2.0 * K2_1[i] + 2.0 * K3_1[i] + K4_1[i]); // Метод Рунге-Кутта 2
        printf("--------------------------------------------------------------------\n");
        printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", i + 1, X2[i + 1], F(X2[i + 1]), Y_RK2[i + 1], abs(F(X2[i + 1]) - Y_RK2[i + 1]));
    }
    printf("--------------------------------------------------------------------\n\n");
    printf("Метод Адамса при n = 20:\n");
    printf("--------------------------------------------------------------------\n");
    printf("|  i |      x_i     |      y_i     |     y_i_A    |  |y_i - y_i_A| |\n");
    printf("--------------------------------------------------------------------\n");
    printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", 0, X2[0], F(X2[0]), Y_A2[0], abs(F(X2[0]) - Y_A2[0]));
    for (int i = 0; i < n2; i++) {
        if (i < 3) {
            Y_A2[i + 1] = Y_A2[i] + 1.0 / 6.0 * (K1_1[i] + 2.0 * K2_1[i] + 2.0 * K3_1[i] + K4_1[i]);
        }
        else {
            Y_A2[i + 1] = Y_A2[i] + h2 / 24.0 * (55.0 * f(X2[i], Y_A2[i]) - 59.0 * f(X2[i - 1], Y_A2[i - 1]) + 37.0 * f(X2[i - 2], Y_A2[i - 2]) - 9.0 * f(X2[i - 3], Y_A2[i - 3])); // Метод Адамса 2
        }
        printf("--------------------------------------------------------------------\n");
        printf("| %2d | %12.9lf | %12.9lf | %12.9lf |  %12.9lf  |\n", i + 1, X2[i + 1], F(X2[i + 1]), Y_A2[i + 1], abs(F(X2[i + 1]) - Y_A2[i + 1]));
    }
    printf("--------------------------------------------------------------------\n");
}
