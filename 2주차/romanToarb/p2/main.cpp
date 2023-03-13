#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

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

        romanNum = _getch();
        if (romanNum[0] != 27)
            getline(cin, romanNum);
        else {
            break;
        }


        if (romanNum.empty()) { // �Է� ���� ������(���������) loop�� ����
            cout << "�Է� �����Դϴ�. ���α׷��� �����մϴ�." << endl;
            return;
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
        if(flag == 0)   cout << "�ƶ��� ���ڷ� ��ȯ�� ���: " << arabicNum << endl;
    }
}


int main() {

    loop();
    return 0;
}