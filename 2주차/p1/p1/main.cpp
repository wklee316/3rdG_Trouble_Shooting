#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

string romanize(int num) {
    string s = "";

    int thous, hund, ten, one;

    thous = num / 1000;
    hund = (num % 1000) / 100;
    ten = (num % 100) / 10;
    one = num % 10;
    for (int i = 0; i < thous; i++) {
        s = s + "M";
    }
    if (hund < 4)
        for (int i = 0; i < hund; i++)
            s = s + "C";
    else if (hund == 4)
        s = s + "CD";
    else if (hund >= 5 && hund < 9)
    {
        s = s + "D";
        for (int i = 0; i < (hund - 5); i++)
            s = s + "C";
    }
    else s = s + "CM";


    //10�� �ڸ�
    if (ten < 4)
        for (int i = 0; i < ten; i++)
            s = s + "X";
    else if (ten == 4)
        s = s + "XL";
    else if (ten >= 5 && ten < 9)
    {
        s = s + "L";
        for (int i = 0; i < (ten - 5); i++)
            s = s + "X";
    }
    else s = s + "XC";


    //1���ڸ�
    if (one < 4)
        for (int i = 0; i < one; i++)
            s = s + "I";
    else if (one == 4)
        s = s + "IV";
    else if (one >= 5 && one < 9)
    {
        s = s + "V";
        for (int i = 0; i < (one - 5); i++)
            s = s + "I";
    }
    else s = s + "IX";

    return s;
}

int main()
{
    int a;


    while (1) {
        cin >> a;
        if (cin.peek() == 27) return 0;
        if (cin.fail()) {
            // �����ߴٸ�
            cin.ignore(); // �Է��Ͽ� ���ڷ� �ν���'\n'�� ����
            cin.clear(); // �Է� ���ɻ��·� �ǵ�����
        }
        rewind(stdin); // �Է¹��� ����

        if (a < 1 || a > 3999) {
            cout << "�Էµ� ���� �߸��Ǿ����ϴ�." << endl;
            continue;
        }
        string s = romanize(a);

        cout << s << endl;

    }
    

    return 0;
}