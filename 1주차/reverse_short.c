#include <iostream>

using namespace std;

int main()
{
    unsigned short a;
   
   
   
    cin >> a;
   
    if(a > 65,534) {
        cout << "입력된 값이 unsigned short 의 표현범위를 벗어났습니다";
        return 0;
    }
   
    string s = to_string(a);
    int len = s.length();
    for(int i=0; i<len/2; i++){
        int temp=s[i];
        s[i]=s[len-1-i];
        s[len-1-i]=temp;
    }
   
    if(stoi(s) > 65,535) cout << "입력된 값을 변환한 값이 unsigned short의 표현범위를 벗어났습니다";
    else a = stoi(s);
    cout << a;
    return 0;
}