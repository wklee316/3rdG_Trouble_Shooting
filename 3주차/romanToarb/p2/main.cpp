#include <iostream>
#include <string>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <regex>

using namespace std;


void inputThread() {
    // Ű �Է� ����
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) { // esc Ű �Է�
            exit(0); // ���α׷� ����
        }
    }
}

bool validateRoman(string roman) {
    // �θ� ���� ���� �˻�
    regex pattern("^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");

    // �θ� ���� �˻�
    return regex_match(roman, pattern);
}

// �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� �Լ�
int romanToAr(char c) {
    switch (c) {
    case 'I': return 1;
    case 'V': return 5;
    case 'X': return 10;
    case 'L': return 50;
    case 'C': return 100;
    case 'D': return 500;
    case 'M': return 1000;
    default: return 0;
    }
}

string romanNum;
int arabicNum = 0;

void loop() {
    while (true) {
        cout << "�θ��� ���ڸ� �Է��ϼ��� (�����Ϸ��� esc Ű�� ��������): ";

        int flag = 0;

        getline(cin, romanNum);


        if (!validateRoman(romanNum)) { // �Է� ���� ������(���������) loop�� ����
            cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
            continue;
        }

        // �θ��� ���ڸ� �ƶ��� ���ڷ� ��ȯ�ϴ� ����
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            if (romanToAr(romanNum[i]) == 0) { // ��ȿ���� ���� ���ڸ� �Է� ������ flag�� �ø��� ��ȯ ������ �ѱ�
                cout << "�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���." << endl;
                flag++;
                break;
            }
            if (i < romanNum.length() - 1 && romanToAr(romanNum[i]) < romanToAr(romanNum[i + 1])) {
                arabicNum -= romanToAr(romanNum[i]); // ���� ���� ū �� �տ� ���� ���
            }
            else {
                arabicNum += romanToAr(romanNum[i]);
            }
        }
        if (0 < arabicNum && arabicNum < 4000) {
            if(flag == 0)   cout << "�ƶ��� ���ڷ� ��ȯ�� ���: " << arabicNum << endl;
            //continue;
        }
        else cout << "��� ������ ���� �ٱ��Դϴ�. �ٽ��Է��� �ּ��� " << endl;
    }
}


int main() {

    thread t(inputThread);

    loop();
    return 0;
}