#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <limits>
#include <locale.h>
#include <windows.h>

using namespace std;

// Константи
const string AUTHOR = "Габур Артем, ЦНТУ Кропивницький 2025";
const string FIRST_COSMONAUT = "Леонід Каденюк";
const string WISH_TEXT = "Хай щастить!";

// Вірш Тарана
const char* POEM =
"Хай щастить у Вашій хаті мамо\n"
"Всім хто переступить Ваш поріг\n"
"Добрим людям і птахам так само\n"
"І котові що в теплі приліг\n"
"Хай щастить кожненькій деревині\n"
"Що до хати віти притуля\n"
"Хай щастить малесенькій травині\n"
"Й вітерцю що приліта здаля";

// Функція для перевірки чи є слово
bool isWord(const string& token) {
    for (char ch : token) {
        if (isalpha(ch)) return true;
    }
    return false;
}

// Функція для перевірки чи є пунктуація
bool isPunctuation(const string& token) {
    for (char ch : token) {
        if (isalpha(ch)) return false;
    }
    return !token.empty();
}

// Функція для додавання вірша та дати до файлу
void appendPoemWithTimestamp() {
    ofstream fout("input.txt", ios::app);

    if (!fout.is_open()) {
        cerr << "Помилка відкриття input.txt" << endl;
        return;
    }

    fout << "\n" << POEM;

    time_t now = time(0);
    char* dt = ctime(&now);
    fout << "\nПоточний час: " << dt << endl;

    fout.close();
    cout << "Вірш та поточний час додано до input.txt." << endl;
}

// Функція для обчислення s_calculation
double calculateS(double x, double y, double z) {
    if (x <= y) {
        cerr << "Помилка: x має бути більшим за y для обчислення логарифму." << endl;
        return NAN; // Повертаємо NaN (Not a Number) у випадку помилки
    }
    double denominator = x + z / (2 * pow(y, 2));
    if (denominator == 0) {
        cerr << "Помилка: ділення на нуль." << endl;
        return NAN;
    }
    return log(x - y) + sqrt((3.14159265 * pow(x, 2)) / denominator);
}

// Функція для запису результату обчислення та двійкового коду числа b
void processCalculation() {
    double x, y, z;
    int b;

    cout << "Введіть значення x: ";
    cin >> x;
    cout << "Введіть значення y: ";
    cin >> y;
    cout << "Введіть значення z: ";
    cin >> z;
    cout << "Введіть натуральне число для b: ";
    cin >> b;

    double result = calculateS(x, y, z);

    if (isnan(result)) {
        cerr << "Помилка в обчисленні функції." << endl;
        return;
    }

    ofstream fout("output.txt", ios::app);
    if (!fout.is_open()) {
        cerr << "Помилка відкриття output.txt" << endl;
        return;
    }

    fout << "Результат обчислення функції: " << result << endl;
    cout << "Результат обчислення функції: " << result << endl;

    // Перетворення числа b у двійковий код
    string binary;
    int temp = b;
    while (temp > 0) {
        binary = to_string(temp % 2) + binary;
        temp /= 2;
    }

    if (binary.empty()) {
        binary = "0";
    }

    cout << "Число " << b << " у двійковому коді: " << binary << endl;

    fout.close();
}

// Головна функція обробки
void processText() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cerr << "Помилка відкриття input.txt" << endl;
        return;
    }

    fout << AUTHOR << "\n\n";

    set<string> poemWords;
    istringstream poemStream(POEM);
    string pw;
    while (poemStream >> pw) {
        pw.erase(remove_if(pw.begin(), pw.end(), ::ispunct), pw.end());
        poemWords.insert(pw);
    }

    string word;
    set<char> punctuationMarks;

    while (fin >> word) {
        if (isWord(word)) {
            int letterCount = 0;
            string pureWord;
            for (char ch : word) {
                if (isalpha(ch)) {
                    letterCount++;
                    pureWord += ch;
                }
            }

            fout << "Слово: \"" << pureWord << "\" — кількість літер: " << letterCount << endl;

            if (poemWords.count(pureWord)) {
                fout << "Це слово є у вірші." << endl;
            } else {
                fout << "Цього слова немає у вірші." << endl;
            }
        } else if (isPunctuation(word)) {
            for (char ch : word) {
                if (ispunct(ch)) {
                    punctuationMarks.insert(ch);
                }
            }
        }
    }

    if (!punctuationMarks.empty()) {
        fout << "У файлі знайдено знаки пунктуації: ";
        bool first = true;
        for (char mark : punctuationMarks) {
            if (!first) {
                fout << ", ";
            }
            fout << "\"" << mark << "\"";
            first = false;
        }
        fout << endl << WISH_TEXT << endl;
    } else {
        fout << FIRST_COSMONAUT << endl;
    }

    fin.close();
    fout.close();
    cout << "Обробку завершено. Перевірте output.txt" << endl;
}

int main() {
    setlocale(LC_ALL, "ukr");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    do {
        cout << "Оберіть дію:" << endl;
        cout << "1. Перевірка та створення output.txt" << endl;
        cout << "2. Доповнити input.txt" << endl;
        cout << "3. Обчислити функцію та вивести двійковий код числа" << endl;
        cout << "0. Вийти" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
            case 1:
                processText();
                break;
            case 2:
                appendPoemWithTimestamp();
                break;
            case 3:
                processCalculation();
                break;
            case 0:
                cout << "Вихід з програми." << endl;
                break;
            default:
                cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}
