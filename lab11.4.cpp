#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <windows.h> 

using namespace std;

// Функція створення текстового файлу
void CreateFile(const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "Помилка створення файлу!" << endl;
        return;
    }

    cout << "Введіть рядки для файлу. Для завершення введіть порожній рядок." << endl;
    cin.ignore(); // Очищення буфера
    string line;
    while (true) {
        cout << "Введіть рядок: ";
        getline(cin, line);
        if (line.empty()) break;
        fout << line << endl;
    }
    fout.close();
    cout << "Файл \"" << filename << "\" створено!" << endl;
}

// Функція для перевірки, чи рядок складається з однакових символів
bool IsLineIdentical(const string& line) {
    for (size_t i = 1; i < line.size(); ++i) {
        if (line[i] != line[0]) {
            return false;
        }
    }
    return true;
}

// Функція аналізу файлу
void AnalyzeFile(const string& inputFile, const string& outputFile, char targetChar) {
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cout << "Помилка відкриття файлу для читання!" << endl;
        return;
    }

    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cout << "Помилка створення файлу для запису результатів!" << endl;
        fin.close();
        return;
    }

    int startsWithChar = 0, sameStartEnd = 0, identicalChars = 0, emptyLines = 0;
    string line;

    while (getline(fin, line)) {
        if (line.empty()) {
            emptyLines++;
            continue;
        }

        if (line[0] == targetChar) {
            startsWithChar++;
        }

        if (line.front() == line.back()) {
            sameStartEnd++;
        }

        if (IsLineIdentical(line)) {
            identicalChars++;
        }
    }

    fout << "Результати аналізу файлу \"" << inputFile << "\":\n";
    fout << "1. Кількість рядків, які починаються з символу '" << targetChar << "': " << startsWithChar << "\n";
    fout << "2. Кількість рядків, які починаються і закінчуються одним символом: " << sameStartEnd << "\n";
    fout << "3. Кількість рядків, які складаються з однакових символів: " << identicalChars << "\n";
    fout << "4. Кількість порожніх рядків: " << emptyLines << "\n";

    cout << "Аналіз завершено. Результати записано у файл \"" << outputFile << "\"." << endl;

    fin.close();
    fout.close();
}

int main() { 
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string inputFilename, outputFilename;
    cout << "Введіть ім'я текстового файлу: ";
    cin >> inputFilename;

    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Створити текстовий файл\n";
        cout << "2. Аналізувати текстовий файл\n";
        cout << "0. Вийти\n";
        cout << "Ваш вибір: "; 
        cin >> choice;

        switch (choice) {
        case 1:
            CreateFile(inputFilename);
            break;

        case 2: {
            char targetChar;
            cout << "Введіть символ для аналізу: ";
            cin >> targetChar;

            cout << "Введіть ім'я файлу для запису результатів: ";
            cin >> outputFilename;

            AnalyzeFile(inputFilename, outputFilename, targetChar);
            break;
        }

        case 0:
            cout << "Програма завершена." << endl;
            break;

        default:
            cout << "Невірний вибір, спробуйте ще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}
