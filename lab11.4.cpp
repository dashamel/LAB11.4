#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <windows.h> 

using namespace std;

// ������� ��������� ���������� �����
void CreateFile(const string& filename) {
    ofstream fout(filename);
    if (!fout.is_open()) {
        cout << "������� ��������� �����!" << endl;
        return;
    }

    cout << "������ ����� ��� �����. ��� ���������� ������ ������� �����." << endl;
    cin.ignore(); // �������� ������
    string line;
    while (true) {
        cout << "������ �����: ";
        getline(cin, line);
        if (line.empty()) break;
        fout << line << endl;
    }
    fout.close();
    cout << "���� \"" << filename << "\" ��������!" << endl;
}

// ������� ��� ��������, �� ����� ���������� � ��������� �������
bool IsLineIdentical(const string& line) {
    for (size_t i = 1; i < line.size(); ++i) {
        if (line[i] != line[0]) {
            return false;
        }
    }
    return true;
}

// ������� ������ �����
void AnalyzeFile(const string& inputFile, const string& outputFile, char targetChar) {
    ifstream fin(inputFile);
    if (!fin.is_open()) {
        cout << "������� �������� ����� ��� �������!" << endl;
        return;
    }

    ofstream fout(outputFile);
    if (!fout.is_open()) {
        cout << "������� ��������� ����� ��� ������ ����������!" << endl;
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

    fout << "���������� ������ ����� \"" << inputFile << "\":\n";
    fout << "1. ʳ������ �����, �� ����������� � ������� '" << targetChar << "': " << startsWithChar << "\n";
    fout << "2. ʳ������ �����, �� ����������� � ����������� ����� ��������: " << sameStartEnd << "\n";
    fout << "3. ʳ������ �����, �� ����������� � ��������� �������: " << identicalChars << "\n";
    fout << "4. ʳ������ ������� �����: " << emptyLines << "\n";

    cout << "����� ���������. ���������� �������� � ���� \"" << outputFile << "\"." << endl;

    fin.close();
    fout.close();
}

int main() { 
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string inputFilename, outputFilename;
    cout << "������ ��'� ���������� �����: ";
    cin >> inputFilename;

    int choice;
    do {
        cout << "\n����:\n";
        cout << "1. �������� ��������� ����\n";
        cout << "2. ���������� ��������� ����\n";
        cout << "0. �����\n";
        cout << "��� ����: "; 
        cin >> choice;

        switch (choice) {
        case 1:
            CreateFile(inputFilename);
            break;

        case 2: {
            char targetChar;
            cout << "������ ������ ��� ������: ";
            cin >> targetChar;

            cout << "������ ��'� ����� ��� ������ ����������: ";
            cin >> outputFilename;

            AnalyzeFile(inputFilename, outputFilename, targetChar);
            break;
        }

        case 0:
            cout << "�������� ���������." << endl;
            break;

        default:
            cout << "������� ����, ��������� �� ���." << endl;
        }
    } while (choice != 0);

    return 0;
}
