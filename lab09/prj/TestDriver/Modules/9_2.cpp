#include <iostream>
#include <windows.h> 

using namespace std;

void task2(){
    SetConsoleOutputCP(65001);

    int rozmirUA;
    cout << "Введіть розмір чоловічих шкарпеток за українською системою (23, 25, 27, 29, 31): ";
    cin >> rozmirUA;

    string rozmirEU, rozmirUS;

    switch (rozmirUA) {
        case 23:
            rozmirEU = "37/38";
            rozmirUS = "8";
            break;
        case 25:
            rozmirEU = "39/40";
            rozmirUS = "9";
            break;
        case 27:
            rozmirEU = "41/42";
            rozmirUS = "10";
            break;
        case 29:
            rozmirEU = "43/44";
            rozmirUS = "11";
            break;
        case 31:
            rozmirEU = "45/46";
            rozmirUS = "12";
            break;
        default:
            cout << "Помилка: невідомий розмір. Будь ласка, введіть один із таких: 23, 25, 27, 29, 31." << endl;
        return;
    }

    cout << "Розмір у системі ЄС: " << rozmirEU << endl;
    cout << "Розмір у системі США/Великобританії: " << rozmirUS << endl;
}
