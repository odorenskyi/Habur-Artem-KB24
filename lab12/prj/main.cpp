#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <cmath>
#ifdef _WIN32
#include <windows.h>
#endif

class ClassLab12_Habur {
private:
    double length;
    double width;
    double height;

public:
    ClassLab12_Habur(double l, double w, double h) {
        setLength(l);
        setWidth(w);
        setHeight(h);
    }

    double getLength() const { return length; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }

    void setLength(double l) {
        if (l <= 0) throw std::invalid_argument("Довжина повинна бути додатною!");
        length = l;
    }

    void setWidth(double w) {
        if (w <= 0) throw std::invalid_argument("Ширина повинна бути додатною!");
        width = w;
    }

    void setHeight(double h) {
        if (h <= 0) throw std::invalid_argument("Висота повинна бути додатною!");
        height = h;
    }

    double getSurfaceArea() const {
        return 2 * (length * width + length * height + width * height);
    }

    double getScreenDiagonalInches() const {
        double diagonal_cm = sqrt(pow(length, 2) + pow(width, 2));
        return diagonal_cm / 2.54;
    }

    // Вивід інформації про об'єкт
    void printInfo() const {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "📱 Розміри планшета:\n";
        std::cout << " ▸ Довжина: " << length << " см\n";
        std::cout << " ▸ Ширина:  " << width << " см\n";
        std::cout << " ▸ Висота:  " << height << " см\n";
        std::cout << "📏 Дюймовка екрану: " << getScreenDiagonalInches() << " дюймів\n";
        std::cout << "📐 Площа поверхні: " << getSurfaceArea() << " см²\n";
    }
};

// Функція для безпечного введення числа
double getPositiveDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if (value > 0) {
                return value;
            } else {
                std::cout << "Значення має бути додатним. Спробуйте ще раз.\n";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Невірний ввід. Введіть число.\n";
        }
    }
}

// Вивід інформації про автора
void printAuthorInfo() {
    std::cout << "Автор: Габур А.О\n";
    std::cout << "Група: КБ-24\n";
    std::cout << "Завдання: Розробка програми для роботи з планшетом\n";
}

// Вивід формул
void printFormulas() {
    std::cout << "\n Використані формули:\n";
    std::cout << "1. Площа поверхні планшета:\n";
    std::cout << "   S = 2 * (a*b + a*h + b*h)\n";
    std::cout << "   де a — довжина, b — ширина, h — висота\n\n";
    std::cout << "2. Дюймовка екрану:\n";
    std::cout << "   D = √(a² + b²) / 2.54\n";
    std::cout << "   де a — довжина, b — ширина, 2.54 — коефіцієнт переведення см в дюйми\n";
    std::cout << "==================================================\n";
}

// Вивід меню
void showMenu() {
    std::cout << "\n📋 Меню:\n";
    std::cout << "1. Показати інформацію про планшет\n";
    std::cout << "2. Змінити довжину\n";
    std::cout << "3. Змінити ширину\n";
    std::cout << "4. Змінити висоту\n";
    std::cout << "5. Вийти\n";
    std::cout << "Ваш вибір: ";
}

// Функція для безпечного введення вибору меню
int getMenuChoice() {
    int choice;
    while (true) {
        showMenu();
        if (std::cin >> choice) {
            if (choice >= 1 && choice <= 5) {
                return choice;
            } else {
                std::cout << "Невірний вибір. Введіть число від 1 до 5.\n";
            }
        } else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Невірний ввід. Введіть число від 1 до 5.\n";
        }
    }
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
#endif

    try {
        // Вивід інформації про автора та формули на початку програми
        printAuthorInfo();
        printFormulas();

        // Початковий об'єкт
        ClassLab12_Habur tablet(24.5, 15.3, 0.8);

        int choice;
        do {
            choice = getMenuChoice();

            switch (choice) {
                case 1:
                    tablet.printInfo();
                    break;

                case 2: {
                    double newLength = getPositiveDouble("Введіть нову довжину (см): ");
                    try {
                        tablet.setLength(newLength);
                        std::cout << "✅ Довжину змінено.\n";
                    } catch (const std::exception& ex) {
                        std::cerr << "Помилка: " << ex.what() << "\n";
                    }
                    break;
                }

                case 3: {
                    double newWidth = getPositiveDouble("Введіть нову ширину (см): ");
                    try {
                        tablet.setWidth(newWidth);
                        std::cout << "✅ Ширину змінено.\n";
                    } catch (const std::exception& ex) {
                        std::cerr << "Помилка: " << ex.what() << "\n";
                    }
                    break;
                }

                case 4: {
                    double newHeight = getPositiveDouble("Введіть нову висоту (см): ");
                    try {
                        tablet.setHeight(newHeight);
                        std::cout << "✅ Висоту змінено.\n";
                    } catch (const std::exception& ex) {
                        std::cerr << "Помилка: " << ex.what() << "\n";
                    }
                    break;
                }

                case 5:
                    std::cout << "Програму завершено...\n";
                    break;
            }
        } while (choice != 5);
    }
    catch (const std::exception& ex) {
        std::cerr << "Критична помилка: " << ex.what() << "\n";
    }

    return 0;
}
