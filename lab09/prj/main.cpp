#include <iostream>
#include <windows.h>
#include <limits> // обов'язково для ignore()
#include "Modules/Gabur.h"
#include "Modules/Gabur.cpp"
#include "9_1.cpp"
#include "9_2.cpp"
#include "9_3.cpp"

using namespace std;

void task9_4() {
    double x, y, z;
    char a, b;

    cout << "\nВведіть значення x, y, z (через пробіл): ";
    cin >> x >> y >> z;

    cout << "Введіть два логічні символи (наприклад: 1 0): ";
    cin >> a >> b;

    printAuthor();
    printValues(x, y, z);

    double s = calculateS(x, y, z);
    cout << "Результат обчислення S: " << s << endl;

    printLogicalResult(a, b);
}

int main() {
    SetConsoleOutputCP(65001); // українська мова в консолі

    char команднийСимвол;

    while (true) {
        cout << "\nВведіть команду (u-завдання 4,o-бал бофорда,p-розмір носка,a-двійкові числа): ";
        cin >> команднийСимвол;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 🔧 очищаємо буфер

        switch (команднийСимвол) {
            case 'u': task9_4(); break;
            case 'o': task1(); break;
            case 'p': task2(); break;
            case 'a': task3(); break;
            default:
                cout << "\aНевідома команда! (ігноровано)" << endl;
                continue;
        }

        char вихід;
        cout <<"\nДля виходу введіть 's' або 'S',або";
        cout << "\nВведіть команду (u-завдання 4,o-бал бофорда,p-розмір носка,a-двійкові числа): "; 
        cin >> вихід;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 🔧 знову очищаємо буфер

        if (вихід == 's' || вихід == 'S') {
            cout << "Завершення програми." << endl;
            break;
        }
    }

    return 0;
}
