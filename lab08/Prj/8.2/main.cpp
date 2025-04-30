#include <iostream>
#include <iomanip>
#include <windows.h>
#include "Modules/Gabur.h"

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    double x, y, z;
    char a, b;

    cout << "Введіть значення x, y, z: ";
    cin >> x >> y >> z;

    cout << "Введіть символи a та b: ";
    cin >> a >> b;

    if (x <= y) {
        cout << "Помилка: вираз ln(x - y) не визначений при x ≤ y." << endl;
        return 1;
    }

    // 8.2.1 
    printAuthor();

    // 8.2.2 
    printLogicalResult(a, b);

    // 8.2.3 
    printValues(x, y, z);
    // Обчислення S
    double S = calculateS(x, y, z);
    cout << fixed << setprecision(4);
    cout << "Результат обчислення S = " << S << endl;

    system("pause"); 
    return 0;
}