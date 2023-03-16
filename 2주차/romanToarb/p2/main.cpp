#include <iostream>
#include <string>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <regex>

using namespace std;


void inputThread() {
    // 키 입력 감지
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) { // esc 키 입력
            exit(0); // 프로그램 종료
        }
    }
}

bool validateRoman(string roman) {
    // 로마 숫자 형식 검사
    regex pattern("^M{0,3}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");

    // 로마 숫자 검사
    return regex_match(roman, pattern);
}

// 로마자 문자를 아라비아 숫자로 변환하는 함수
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
        cout << "로마자 숫자를 입력하세요 (종료하려면 esc 키를 누르세요): ";

        int flag = 0;

        getline(cin, romanNum);


        if (!validateRoman(romanNum)) { // 입력 값이 없으면(비어있으면) loop를 나감
            cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
            continue;
        }

        // 로마자 숫자를 아라비아 숫자로 변환하는 과정
        arabicNum = 0;
        for (int i = 0; i < romanNum.length(); i++) {
            if (romanToAr(romanNum[i]) == 0) { // 유효하지 않은 문자를 입력 받으면 flag를 올리고 변환 과정을 넘김
                cout << "잘못된 입력입니다. 다시 입력해주세요." << endl;
                flag++;
                break;
            }
            if (i < romanNum.length() - 1 && romanToAr(romanNum[i]) < romanToAr(romanNum[i + 1])) {
                arabicNum -= romanToAr(romanNum[i]); // 작은 수가 큰 수 앞에 오는 경우
            }
            else {
                arabicNum += romanToAr(romanNum[i]);
            }
        }
        if (0 < arabicNum && arabicNum < 4000) {
            if(flag == 0)   cout << "아라비아 숫자로 변환한 결과: " << arabicNum << endl;
            //continue;
        }
        else cout << "출력 가능한 범위 바깥입니다. 다시입력해 주세요 " << endl;
    }
}


int main() {

    thread t(inputThread);

    loop();
    return 0;
}