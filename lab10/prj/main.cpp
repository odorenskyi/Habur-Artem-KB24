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

// ���������
const string AUTHOR = "����� �����, ���� ������������� 2025";
const string FIRST_COSMONAUT = "����� �������";
const string WISH_TEXT = "��� �������!";

// ³�� ������
const char* POEM =
"��� ������� � ����� ��� ����\n"
"��� ��� ����������� ��� ����\n"
"������ ����� � ������ ��� ����\n"
"� ����� �� � ���� �����\n"
"��� ������� ��������� �������\n"
"�� �� ���� ��� �������\n"
"��� ������� ���������� ������\n"
"� ������ �� ������ �����";

// ������� ��� �������� �� � �����
bool isWord(const string& token) {
    for (char ch : token) {
        if (isalpha(ch)) return true;
    }
    return false;
}

// ������� ��� �������� �� � ����������
bool isPunctuation(const string& token) {
    for (char ch : token) {
        if (isalpha(ch)) return false;
    }
    return !token.empty();
}

// ������� ��� ��������� ���� �� ���� �� �����
void appendPoemWithTimestamp() {
    ofstream fout("input.txt", ios::app);

    if (!fout.is_open()) {
        cerr << "������� �������� input.txt" << endl;
        return;
    }

    fout << "\n" << POEM;

    time_t now = time(0);
    char* dt = ctime(&now);
    fout << "\n�������� ���: " << dt << endl;

    fout.close();
    cout << "³�� �� �������� ��� ������ �� input.txt." << endl;
}

// ������� ��� ���������� s_calculation
double calculateS(double x, double y, double z) {
    if (x <= y) {
        cerr << "�������: x �� ���� ������ �� y ��� ���������� ���������." << endl;
        return NAN; // ��������� NaN (Not a Number) � ������� �������
    }
    double denominator = x + z / (2 * pow(y, 2));
    if (denominator == 0) {
        cerr << "�������: ������ �� ����." << endl;
        return NAN;
    }
    return log(x - y) + sqrt((3.14159265 * pow(x, 2)) / denominator);
}

// ������� ��� ������ ���������� ���������� �� ��������� ���� ����� b
void processCalculation() {
    double x, y, z;
    int b;

    cout << "������ �������� x: ";
    cin >> x;
    cout << "������ �������� y: ";
    cin >> y;
    cout << "������ �������� z: ";
    cin >> z;
    cout << "������ ���������� ����� ��� b: ";
    cin >> b;

    double result = calculateS(x, y, z);

    if (isnan(result)) {
        cerr << "������� � ��������� �������." << endl;
        return;
    }

    ofstream fout("output.txt", ios::app);
    if (!fout.is_open()) {
        cerr << "������� �������� output.txt" << endl;
        return;
    }

    fout << "��������� ���������� �������: " << result << endl;
    cout << "��������� ���������� �������: " << result << endl;

    // ������������ ����� b � �������� ���
    string binary;
    int temp = b;
    while (temp > 0) {
        binary = to_string(temp % 2) + binary;
        temp /= 2;
    }

    if (binary.empty()) {
        binary = "0";
    }

    cout << "����� " << b << " � ��������� ���: " << binary << endl;

    fout.close();
}

// ������� ������� �������
void processText() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cerr << "������� �������� input.txt" << endl;
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

            fout << "�����: \"" << pureWord << "\" � ������� ����: " << letterCount << endl;

            if (poemWords.count(pureWord)) {
                fout << "�� ����� � � ����." << endl;
            } else {
                fout << "����� ����� ���� � ����." << endl;
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
        fout << "� ���� �������� ����� ����������: ";
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
    cout << "������� ���������. �������� output.txt" << endl;
}

int main() {
    setlocale(LC_ALL, "ukr");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    int choice;
    do {
        cout << "������ ��:" << endl;
        cout << "1. �������� �� ��������� output.txt" << endl;
        cout << "2. ��������� input.txt" << endl;
        cout << "3. ��������� ������� �� ������� �������� ��� �����" << endl;
        cout << "0. �����" << endl;
        cout << "��� ����: ";
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
                cout << "����� � ��������." << endl;
                break;
            default:
                cout << "������� ����. ��������� �� ���." << endl;
        }
    } while (choice != 0);

    return 0;
}
