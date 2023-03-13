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


    //10의 자리
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


    //1의자리
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
            // 실패했다면
            cin.ignore(); // 입력하여 문자로 인식한'\n'도 무시
            cin.clear(); // 입력 가능상태로 되돌리기
        }
        rewind(stdin); // 입력버퍼 비우기

        if (a < 1 || a > 3999) {
            cout << "입력된 값이 잘못되었습니다." << endl;
            continue;
        }
        string s = romanize(a);

        cout << s << endl;

    }
    

    return 0;
}