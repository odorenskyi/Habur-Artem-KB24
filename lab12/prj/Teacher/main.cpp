#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

#ifdef _WIN32
#include <windows.h> // Для SetConsoleOutputCP
#endif

class ClassLab12_Habur {
private:
    double length;
    double width;
    double height;

public:
    // Конструктор
    ClassLab12_Habur(double l, double w, double h) {
        setLength(l);
        setWidth(w);
        setHeight(h);
    }

    // Геттери
    double getLength() const { return length; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }

    // Сеттери з валідацією
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

    // Метод для обчислення площі поверхні
    double getSurfaceArea() const {
        double area = 2 * (length * width + length * height + width * height);
        std::cout << "Розрахунок площі: area = " << area << "\n";
        return area;
    }

    // Метод для обчислення діагоналі екрану в дюймах
    double getScreenDiagonalInches() const {
        double diagonal_cm = sqrt(pow(length, 2) + pow(width, 2));
        double diagonal_inches = diagonal_cm / 2.54;
        std::cout << "Розрахунок діагоналі: diagonal_cm = " << diagonal_cm << ", diagonal_inches = " << diagonal_inches << "\n";
        return diagonal_inches;
    }

    // Метод для отримання інформації у вигляді рядка
    std::string getInfo() const {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2);
        oss << "📱 Розміри планшета:\n";
        oss << " ▸ Довжина: " << length << " см\n";
        oss << " ▸ Ширина:  " << width << " см\n";
        oss << " ▸ Висота:  " << height << " см\n";
        oss << "📏 Дюймовка екрану: " << getScreenDiagonalInches() << " дюймів\n";
        oss << "📐 Площа поверхні: " << getSurfaceArea() << " см²";
        return oss.str();
    }
};

// Функція для порівняння рядків з допуском для чисел з плаваючою точкою
bool compareWithTolerance(const std::string &actual, const std::string &expected) {
    std::istringstream issActual(actual);
    std::istringstream issExpected(expected);

    std::string lineActual, lineExpected;
    int lineNum = 0;
    while (std::getline(issActual, lineActual) && std::getline(issExpected, lineExpected)) {
        lineNum++;

        // Видаляємо пробіли з початку і кінця рядка
        lineActual.erase(0, lineActual.find_first_not_of(" \t\n\r"));
        lineActual.erase(lineActual.find_last_not_of(" \t\n\r") + 1);
        lineExpected.erase(0, lineExpected.find_first_not_of(" \t\n\r"));
        lineExpected.erase(lineExpected.find_last_not_of(" \t\n\r") + 1);

        // Якщо рядки порожні, пропускаємо їх
        if (lineActual.empty() && lineExpected.empty()) {
            continue;
        }

        // Якщо один з рядків порожній, а інший ні, то вони різні
        if (lineActual.empty() || lineExpected.empty()) {
            return false;
        }

        // Перевіряємо, чи рядки ідентичні
        if (lineActual == lineExpected) {
            continue;
        }

        // Якщо рядки не ідентичні, то шукаємо числа в них
        try {
            std::vector<double> numsActual, numsExpected;

            // Витягуємо всі числа з рядка lineActual
            size_t posActual = 0;
            while (posActual < lineActual.size()) {
                if (isdigit(lineActual[posActual]) || lineActual[posActual] == '.' || lineActual[posActual] == '-') {
                    size_t start = posActual;
                    while (posActual < lineActual.size() &&
                           (isdigit(lineActual[posActual]) || lineActual[posActual] == '.' || lineActual[posActual] == '-')) {
                        posActual++;
                    }
                    std::string numStr = lineActual.substr(start, posActual - start);
                    try {
                        double num = std::stod(numStr);
                        numsActual.push_back(num);
                    } catch (...) {
                        // Якщо не вдалося конвертувати в число, продовжуємо пошук
                    }
                } else {
                    posActual++;
                }
            }

            // Витягуємо всі числа з рядка lineExpected
            size_t posExpected = 0;
            while (posExpected < lineExpected.size()) {
                if (isdigit(lineExpected[posExpected]) || lineExpected[posExpected] == '.' || lineExpected[posExpected] == '-') {
                    size_t start = posExpected;
                    while (posExpected < lineExpected.size() &&
                           (isdigit(lineExpected[posExpected]) || lineExpected[posExpected] == '.' || lineExpected[posExpected] == '-')) {
                        posExpected++;
                    }
                    std::string numStr = lineExpected.substr(start, posExpected - start);
                    try {
                        double num = std::stod(numStr);
                        numsExpected.push_back(num);
                    } catch (...) {
                        // Якщо не вдалося конвертувати в число, продовжуємо пошук
                    }
                } else {
                    posExpected++;
                }
            }

            // Якщо кількість чисел в рядках не збігається, то рядки різні
            if (numsActual.size() != numsExpected.size()) {
                return false;
            }

            // Порівнюємо числа з допуском
            bool numsMatch = true;
            for (size_t i = 0; i < numsActual.size(); ++i) {
                if (std::abs(numsActual[i] - numsExpected[i]) > 0.01) {
                    numsMatch = false;
                    break;
                }
            }

            if (numsMatch) {
                // Якщо числа співпадають, то порівнюємо рядки без чисел
                std::string nonNumActual = lineActual;
                std::string nonNumExpected = lineExpected;

                // Замінюємо числа в рядках на порожній рядок
                posActual = 0;
                while (posActual < nonNumActual.size()) {
                    if (isdigit(nonNumActual[posActual]) || nonNumActual[posActual] == '.' || nonNumActual[posActual] == '-') {
                        size_t start = posActual;
                        while (posActual < nonNumActual.size() &&
                               (isdigit(nonNumActual[posActual]) || nonNumActual[posActual] == '.' || nonNumActual[posActual] == '-')) {
                            posActual++;
                        }
                        nonNumActual.replace(start, posActual - start, "");
                    } else {
                        posActual++;
                    }
                }

                posExpected = 0;
                while (posExpected < nonNumExpected.size()) {
                    if (isdigit(nonNumExpected[posExpected]) || nonNumExpected[posExpected] == '.' || nonNumExpected[posExpected] == '-') {
                        size_t start = posExpected;
                        while (posExpected < nonNumExpected.size() &&
                               (isdigit(nonNumExpected[posExpected]) || nonNumExpected[posExpected] == '.' || nonNumExpected[posExpected] == '-')) {
                            posExpected++;
                        }
                        nonNumExpected.replace(start, posExpected - start, "");
                    } else {
                        posExpected++;
                    }
                }

                // Видаляємо зайві пробіли
                nonNumActual.erase(std::unique(nonNumActual.begin(), nonNumActual.end(),
                                     [](char a, char b) { return a == ' ' && b == ' '; }), nonNumActual.end());
                nonNumExpected.erase(std::unique(nonNumExpected.begin(), nonNumExpected.end(),
                                     [](char a, char b) { return a == ' ' && b == ' '; }), nonNumExpected.end());

                // Порівнюємо рядки без чисел
                if (nonNumActual != nonNumExpected) {
                    return false;
                }

                continue;
            } else {
                // Якщо числа різняться більше ніж на 0.01, рядки вважаються різними
                return false;
            }
        } catch (...) {
            // Якщо не числа - порівнюємо як рядки
            return false;
        }
    }

    // Перевіряємо, чи не залишилося непорівняних рядків
    if (std::getline(issActual, lineActual) || std::getline(issExpected, lineExpected)) {
        return false;
    }

    return true;
}

// Структура для зберігання результатів тесту
struct TestResult {
    int testNumber;
    bool passed;
    std::string expectedOutput;
    std::string actualOutput;
};

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001); // Встановлення UTF-8 виводу в Windows
#endif

    // Відкриваємо файл з тестами
    std::ifstream testFile("tests.txt");
    if (!testFile.is_open()) {
        std::cerr << "Помилка: не вдалося відкрити файл tests.txt\n";
        return 1;
    }

    // Читаємо весь файл в пам'ять
    std::stringstream buffer;
    buffer << testFile.rdbuf();
    std::string fileContent = buffer.str();
    testFile.close();

    // Розділяємо файл на окремі тести
    std::vector<std::string> testCases;
    size_t pos = 0;
    while (pos < fileContent.length()) {
        // Знаходимо початок наступного тесту
        size_t testStart = fileContent.find_first_not_of("\n\r", pos);
        if (testStart == std::string::npos) break;

        // Знаходимо кінець поточного тесту (наступний тест або кінець файлу)
        size_t testEnd = fileContent.find("\n\n", testStart);
        if (testEnd == std::string::npos) testEnd = fileContent.length();

        // Отримуємо текст тесту
        std::string testStr = fileContent.substr(testStart, testEnd - testStart);
        testCases.push_back(testStr);

        pos = testEnd + 2; // Пропускаємо два символи нового рядка
    }

    // Виконуємо кожен тест і зберігаємо результати
    std::vector<TestResult> results;
    int passedTests = 0;
    int totalTests = testCases.size();

    if (totalTests == 0) {
        std::cout << "У файлі tests.txt не знайдено жодного тесту.\n";
        return 0;
    }

    // Створюємо об'єкт планшета з початковими значеннями
    ClassLab12_Habur tablet(24.5, 15.3, 0.8);

    // Виконання тестів і збереження результатів
    for (size_t i = 0; i < testCases.size(); i++) {
        const auto& testCase = testCases[i];
        std::istringstream iss(testCase);

        // Читаємо перший рядок тесту (заголовок)
        std::string testHeader;
        std::getline(iss, testHeader);

        // Парсимо заголовок тесту
        size_t dot1 = testHeader.find('.');
        if (dot1 == std::string::npos) continue;

        size_t dot2 = testHeader.find('.', dot1 + 1);
        if (dot2 == std::string::npos) dot2 = testHeader.length();

        size_t space = testHeader.find(' ', dot2 + 1);
        if (space == std::string::npos) space = testHeader.length();

        int testNum = 0;
        int menuOption = 0;
        double inputValue = 0.0;

        try {
            testNum = std::stoi(testHeader.substr(0, dot1));
            menuOption = std::stoi(testHeader.substr(dot1 + 1, dot2 - dot1 - 1));

            // Виправлений парсинг вхідного значення
            size_t startNum = testHeader.find_first_not_of(" ", dot2 + 1);
            if (startNum != std::string::npos) {
                size_t endNum = testHeader.find_first_of(" ", startNum);
                if (endNum == std::string::npos) endNum = testHeader.length();
                std::string numStr = testHeader.substr(startNum, endNum - startNum);
                if (!numStr.empty()) {
                    inputValue = std::stod(numStr);
                }
            }
            std::cout << "Значення для тесту " << i+1 << ": menuOption=" << menuOption << ", inputValue=" << inputValue << "\n";
        } catch (...) {
            std::cout << "Помилка: не вдалося розібрати заголовок тесту " << i+1 << "\n";
            continue;
        }

        // Читаємо очікуваний вивід (все, що залишилося)
        std::string expectedOutput;
        std::string line;
        bool firstLine = true;
        while (std::getline(iss, line)) {
            if (firstLine) {
                // Пропускаємо порожній рядок після заголовка
                if (line.empty()) {
                    firstLine = false;
                    continue;
                }
            }
            if (!line.empty()) {
                expectedOutput += line + "\n";
            }
        }
        if (!expectedOutput.empty()) {
            expectedOutput.pop_back(); // Видаляємо останній символ нового рядка
        }

        // Вивід для дебагу
        std::cout << "Обробляємо тест " << i+1 << ": " << testHeader << "\n";
        std::cout << "Очікуваний вивід для тесту " << i+1 << ":\n" << expectedOutput << "\n";

        // Виконуємо відповідну дію
        std::string actualOutput;
        try {
            switch (menuOption) {
                case 1: { // Показати інформацію про планшет
                    actualOutput = tablet.getInfo();
                    break;
                }
                case 2: { // Змінити довжину
                    try {
                        tablet.setLength(inputValue);
                        actualOutput = "✅ Довжину змінено.\n";
                        // Вивід стану об'єкта для дебагу
                        std::cout << "Після зміни довжини (тест " << i+1 << "): " << tablet.getInfo() << "\n";
                    } catch (const std::exception& ex) {
                        actualOutput = "🚫 Помилка: " + std::string(ex.what()) + "\n";
                        std::cout << "Виняток в тесті " << i+1 << ": " << ex.what() << "\n";
                    }
                    break;
                }
                case 3: { // Змінити ширину
                    try {
                        tablet.setWidth(inputValue);
                        actualOutput = "✅ Ширину змінено.\n";
                        // Вивід стану об'єкта для дебагу
                        std::cout << "Після зміни ширини (тест " << i+1 << "): " << tablet.getInfo() << "\n";
                    } catch (const std::exception& ex) {
                        actualOutput = "🚫 Помилка: " + std::string(ex.what()) + "\n";
                        std::cout << "Виняток в тесті " << i+1 << ": " << ex.what() << "\n";
                    }
                    break;
                }
                case 4: { // Змінити висоту
                    try {
                        tablet.setHeight(inputValue);
                        actualOutput = "✅ Висоту змінено.\n";
                        // Вивід стану об'єкта для дебагу
                        std::cout << "Після зміни висоти (тест " << i+1 << "): " << tablet.getInfo() << "\n";
                    } catch (const std::exception& ex) {
                        actualOutput = "🚫 Помилка: " + std::string(ex.what()) + "\n";
                        std::cout << "Виняток в тесті " << i+1 << ": " << ex.what() << "\n";
                    }
                    break;
                }
                case 5: { // Вийти
                    actualOutput = "Програму завершено...\n";
                    break;
                }
                default: {
                    actualOutput = "Невідома опція меню: " + std::to_string(menuOption);
                }
            }
        } catch (const std::exception& ex) {
            actualOutput = "🚫 Помилка: " + std::string(ex.what()) + "\n";
            std::cout << "Виняток в тесті " << i+1 << ": " << ex.what() << "\n";
        }

        // Вивід для дебагу
        std::cout << "Фактичний вивід для тесту " << i+1 << ":\n" << actualOutput << "\n";

        // Якщо ми не отримали вивід (наприклад, для успішної зміни параметрів),
        // то генеруємо вивід, який буде порівнюватися з очікуваним
        if (actualOutput.empty() && menuOption == 1) {
            // Це вже зроблено вище
        } else if (actualOutput.empty()) {
            // Для опцій 2-4, якщо не було винятку, генеруємо повідомлення про успіх
            if (menuOption >= 2 && menuOption <= 4) {
                if (inputValue <= 0) {
                    // Якщо вхідне значення недодатне, а ми не отримали помилку - це помилка
                    actualOutput = "Помилка очікування винятку для недодатного значення\n";
                } else {
                    // Якщо вхідне значення додатне, очікуємо повідомлення про успіх
                    if (menuOption == 2) {
                        actualOutput = "✅ Довжину змінено.\n";
                    } else if (menuOption == 3) {
                        actualOutput = "✅ Ширину змінено.\n";
                    } else if (menuOption == 4) {
                        actualOutput = "✅ Висоту змінено.\n";
                    }
                }
            }
        }

        // Порівнюємо очікуваний і фактичний вивід
        bool passed = false;
        if (menuOption == 1) {
            // Для опції 1 порівнюємо весь вивід
            passed = compareWithTolerance(actualOutput, expectedOutput);
        } else {
            // Для інших опцій порівнюємо повідомлення
            std::string normalizedActual = actualOutput;
            std::string normalizedExpected = expectedOutput;

            // Якщо очікується помилка (вхідне значення <= 0)
            if (inputValue <= 0 && menuOption >= 2 && menuOption <= 4) {
                if (normalizedActual.find("Помилка:") != std::string::npos ||
                    normalizedActual.find("🚫 Помилка:") != std::string::npos) {
                    passed = true;
                }
            } else {
                // Якщо очікується успішне виведення
                // Видаляємо всі пробіли для кращого порівняння
                normalizedActual.erase(std::remove(normalizedActual.begin(), normalizedActual.end(), ' '), normalizedActual.end());
                normalizedExpected.erase(std::remove(normalizedExpected.begin(), normalizedExpected.end(), ' '), normalizedExpected.end());

                // Перевіряємо, чи містить фактичний вивід очікуваний текст
                if (normalizedExpected.find("✅") != std::string::npos) {
                    // Очікуємо повідомлення про успіх
                    passed = (normalizedActual.find("✅") != std::string::npos);
                } else {
                    // Очікуємо повідомлення про помилку
                    passed = (normalizedActual.find("Помилка:") != std::string::npos ||
                             normalizedActual.find("🚫") != std::string::npos);
                }
            }
        }

        // Вивід для дебагу
        std::cout << "Тест " << i+1 << ": " << (passed ? "Успіх" : "Невдача") << "\n";
        std::cout << "----------------------------\n";

        // Зберігаємо результат тесту
        results.push_back({static_cast<int>(i+1), passed, expectedOutput, actualOutput});
        if (passed) passedTests++;
    }

    // Виводимо короткий звіт про результати всіх тестів
    std::cout << "Результати тестів:\n";
    for (const auto& result : results) {
        std::cout << result.testNumber << ". " << (result.passed ? "Успіх" : "Невдача") << "\n";
    }

    // Виводимо загальні результати
    std::cout << "\nЗагальні результати:\n";
    std::cout << "Пройдено тестів: " << passedTests << " з " << totalTests << "\n";
    std::cout << "Відсоток успішних тестів: " << (100.0 * passedTests / totalTests) << "%\n";

    // Виводимо детальну інформацію про невдалі тести
    std::cout << "\nДеталі невдалих тестів:\n";
    for (const auto& result : results) {
        if (!result.passed) {
            std::cout << "Тест " << result.testNumber << ":\n";
            std::cout << "Очікувалося:\n" << result.expectedOutput << "\n";
            std::cout << "Отримано:\n" << result.actualOutput << "\n";
            std::cout << "----------------------------\n";
        }
    }

    system("pause");

    return 0;
}
