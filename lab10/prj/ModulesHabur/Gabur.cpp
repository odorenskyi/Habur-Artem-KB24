#include <cmath>
#include <iostream>
#include <iomanip>
#include "Gabur.h"

using namespace std;

// 8.1 - Обчислення за формулою
double calculateS(double x, double y, double z) {
    return log(x - y) + sqrt((3,14159265 * pow(x, 2)) / (x + z / (2 * pow(y, 2))));
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

//10.1
#include <fstream>
#include <string>
#include <cctype>

void task10_1() {
    std::ifstream fin("vkhid.txt");
    std::ofstream fout("vykhid.txt");

    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "Не вдалося відкрити файли.\n";
        return;
    }

    std::string input;
    getline(fin, input);

    // Авторська інформація
    fout << "Розробник: Габур Артем, КПІ, Київ, Україна, 2025\n";

    // Перевірка: це слово чи знак пунктуації?
    bool isWord = true;
    for (char c : input) {
        if (!isalpha(static_cast<unsigned char>(c)) && c != '’' && c != '\'') {
            isWord = false;
            break;
        }
    }

    if (isWord) {
        fout << "Кількість літер у слові: " << input.length() << "\n";
    } else {
        fout << "Хай щастить!\n";
    }

    // Перевірка на входження у вірш
    std::string verseLine = "Хай щастить у Вашій хаті, мамо";
    if (verseLine.find(input) != std::string::npos) {
        fout << "Слово \"" << input << "\" є у фразі з вірша А. Тарана.\n";
    } else {
        fout << "Слово \"" << input << "\" відсутнє у фразі з вірша А. Тарана.\n";
    }

    fin.close();
    fout.close();
}
//10.2
#include <ctime>

void task10_2() {
    std::ofstream fout("vykhid.txt", std::ios::app); // відкриваємо для допису

    if (!fout.is_open()) {
        std::cerr << "Не вдалося відкрити vykhid.txt для допису.\n";
        return;
    }

    // Вірш
    fout << "\nВірш Анатолія Тарана:\n";
    fout << "Хай щастить у Вашій хаті, мамо,\n";
    fout << "Всім, хто переступить Ваш поріг:\n";
    fout << "Добрим людям, і птахам так само,\n";
    fout << "І котові, що в теплі приріг;\n";
    fout << "Хай щастить кожненькій деревині,\n";
    fout << "Що до хати віти притулив,\n";
    fout << "Хай щастить маленькій травинці\n";
    fout << "Й вітрецю, що прилітав здаля.\n";

    // Дата й час
    std::time_t now = std::time(nullptr);
    fout << "\nДата та час допису: " << std::asctime(std::localtime(&now));

    fout.close();
}
//10.3
void task10_3() {
    std::ifstream fin("numbers.txt"); // x y z b
    std::ofstream fout("vykhid.txt", std::ios::app);

    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "Помилка відкриття файлів.\n";
        return;
    }

    double x, y, z;
    int b;
    fin >> x >> y >> z >> b;

    double result = calculateS(x, y, z);
    fout << "\nРезультат обчислення S = " << result << "\n";

    fout << "Число b в двійковій системі: ";
    for (int i = 31; i >= 0; --i) {
        fout << ((b >> i) & 1);
    }
    fout << "\n";

    fin.close();
    fout.close();
}

