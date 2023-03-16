#include <iostream>
#include <regex>
using namespace std;

bool validateRoman(string roman) {
    // 로마 숫자 형식 검사
    regex pattern("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");

    // 로마 숫자 검사
    return regex_match(roman, pattern);
}

int main() {
    string roman;
    cout << "로마 숫자를 입력하세요: ";
    cin >> roman;

    if (validateRoman(roman)) {
        cout << "올바른 로마 숫자입니다." << endl;
    }
    else {
        cout << "올바르지 않은 로마 숫자입니다." << endl;
    }

    return 0;
}

