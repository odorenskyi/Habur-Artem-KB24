#include <iostream>
#include <string>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <windows.h>
#include <cstdlib>
using namespace std;

// task1 — опис вітру за шкалою Бофорта
string getWindDescription(int бал) {
    if (бал < 0 || бал > 12) return "Помилка";
    switch (бал) {
        case 0: return "Штиль";
        case 1: return "Тихий вітер";
        case 2: return "Легкий вітер";
        case 3: return "Слабкий вітер";
        case 4: return "Помірний вітер";
        case 5: return "Свіжий вітер";
        case 6: return "Сильний вітер";
        case 7: return "Міцний вітер";
        case 8: return "Дуже міцний вітер";
        case 9: return "Шторм";
        case 10: return "Сильний шторм";
        case 11: return "Шквальний шторм";
        case 12: return "Ураган (буревій)";
    }
    return "Помилка";
}

// task2 — розмір шкарпеток
string getSocksSize(int rozmirUA) {
    switch (rozmirUA) {
        case 23: return "37/38";
        case 25: return "39/40";
        case 27: return "41/42";
        case 29: return "43/44";
        case 31: return "45/46";
        default: return "Помилка";
    }
}

// task3 — бітовий аналіз
string binaryAnalysis(unsigned int N) {
    if (N > 7483650) return "Помилка";

    bitset<32> bits(N);
    bool D7 = bits[7];

    int count0 = 0, count1 = 0;
    for (int i = 0; i < 32; ++i) {
        if (bits[i] == 0) count0++;
        else count1++;
    }

    return D7 ? "count0=" + to_string(count0) : "sum1=" + to_string(count1);
}

// task4 — математичне обчислення
double calculateS(double x, double y, double z) {
    if ((x - y) <= 0 || y == 0) return NAN;

    double numerator = 3.14159265 * pow(x, 2);
    double denominator = x + z / (2 * pow(y, 2));
    if (denominator == 0) return NAN;

    return log(x - y) + sqrt(numerator / denominator);
}

// Автор
void printAuthor() {
    cout << "© Габур Артем" << endl;
}

// тест для string
// тест для string
void runTest(const string& name, const string& actual, const string& expected) {
    cout << name << ": ";
    if (actual == expected)
        cout << "✅ (Очікувалось: \"" << expected << "\", отримано: \"" << actual << "\")" << endl;
    else
        cout << "❌ (Очікувалось: \"" << expected << "\", отримано: \"" << actual << "\")" << endl;
}

// тест для double
void runTestDouble(const string& name, double actual, double expected, double epsilon = 1e-6) {
    cout << name << ": ";
    if (isnan(expected) && isnan(actual)) {
        cout << "✅ (Очікувалось: NAN, отримано: NAN)" << endl;
    }
    else if (fabs(actual - expected) < epsilon) {
        cout << "✅ (Очікувалось: " << expected << ", отримано: " << actual << ")" << endl;
    }
    else {
        cout << "❌ (Очікувалось: " << expected << ", отримано: " << actual << ")" << endl;
    }
}


int main() {
    SetConsoleOutputCP(65001);

    cout << "\n--- ТЕСТИ ЗАДАЧІ 9.1 ---\n" << endl;
    // task1
    runTest("Task1 Бал 0", getWindDescription(0), "Штиль");
    runTest("Task1 Бал 3", getWindDescription(3), "Слабкий вітер");
    runTest("Task1 Бал 12", getWindDescription(12), "Ураган (буревій)");
    runTest("Task1 Бал -1", getWindDescription(-1), "Помилка");

    cout << "\n--- ТЕСТИ ЗАДАЧІ 9.2 ---\n" << endl;

    runTest("UA=23", getSocksSize(23), "37/38");
    runTest("UA=25", getSocksSize(25), "39/40");
    runTest("UA=27", getSocksSize(27), "41/42");
    runTest("UA=29", getSocksSize(29), "43/44");
    runTest("UA=31", getSocksSize(31), "45/46");
    runTest("UA=22 (некоректне)", getSocksSize(22), "Помилка");

    cout << "\n--- ТЕСТИ ЗАДАЧІ 9.3 ---\n" << endl;

    // task3
    runTest("Task3 N = 15", binaryAnalysis(15), "sum1=4");
    runTest("Task3 N = 256", binaryAnalysis(256), "sum1=1");
    runTest("Task3 N = 8000000", binaryAnalysis(8000000), "Помилка");

    cout << "\n--- ТЕСТИ ЗАДАЧІ 9.4 ---\n" << endl;

    // task4
    double x1 = 5.0, y1 = 2.0, z1 = 3.0;
    double expected1 = log(x1 - y1) + sqrt((3.14159265 * pow(x1, 2)) / (x1 + z1 / (2 * pow(y1, 2))));
    runTestDouble("Task4 x=5, y=2, z=3", calculateS(x1, y1, z1), expected1);

    double x2 = 4.0, y2 = 4.0, z2 = 2.0;
    runTestDouble("Task4 x=4, y=4, z=2", calculateS(x2, y2, z2), NAN);

    // автор
    printAuthor();

    system("pause");

    return 0;
}
