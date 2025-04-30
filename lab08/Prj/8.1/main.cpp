#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    double x, y, z, S;

    cout << "Введіть значення x, y, z: ";
    cin >> x >> y >> z;

    if (x <= y) {
        cout << "Помилка: вираз ln(x - y) не визначений при x ≤ y." << endl;
        return 1;
    }

    S = log(x - y) + pow(cos(x), 2) - fabs(z);

    cout << fixed << setprecision(4);
    cout << "Результат обчислення S = " << S << endl;

    system("pause"); 
    return 0;
}