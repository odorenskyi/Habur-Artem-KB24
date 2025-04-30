#include <cmath>
#include <iostream>
#include <iomanip>
#include "Gabur.h"

using namespace std;

// 8.1 - Обчислення за формулою
double calculateS(double x, double y, double z) {
    return log(x - y) + sqrt((M_PI * pow(x, 2)) / (x + z / (2 * pow(y, 2))));
}

// 8.2.1 - Автор
void printAuthor() {
    cout << "© Габур Артем" << endl;
}

// 8.2.2 - Логічний вираз
void printLogicalResult(char a, char b) {
    int a_num = static_cast<int>(a);
    int b_num = static_cast<int>(b);
    cout << "Результат логічного виразу a + 10 ≥ b: " << (a_num + 10 >= b_num) << endl;
}

// 8.2.3 - Значення x, y, z 
void printValues(double x, double y, double z) {
    cout << "x = " << x << " (hex: " << hex << static_cast<int>(x) << dec << ")\n";
    cout << "y = " << y << " (hex: " << hex << static_cast<int>(y) << dec << ")\n";
    cout << "z = " << z << " (hex: " << hex << static_cast<int>(z) << dec << ")\n";
}
