#include <iostream>
#include <bitset>
#include <windows.h> 

using namespace std;

void task3() {
    SetConsoleOutputCP(65001); 

    unsigned int N;
    cout << "Введіть натуральне число від 0 до 7483650: ";
    cin >> N;

    if (N > 7483650) {
        cout << "Помилка: число перевищує 7483650!" << endl;
        return;
    }

    bitset<32> bits(N);

    bool D7 = bits[7];

    int count0 = 0, sum1 = 0;

    for (int i = 0; i < 32; ++i) {
    if (!bits[i])
        count0++;
    else
        sum1++;
    }


    // Тернарний оператор:
    D7 ? cout << "Кількість двійкових нулів: " << count0 << endl
       : cout << "Сума двійкових одиниць: " << sum1 << endl;

    return;
}
