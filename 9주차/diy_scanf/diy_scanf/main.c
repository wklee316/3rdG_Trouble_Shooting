#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int scanf_like(char* format, void* var);

char* substr(const char* src, int m, int n)
{
    // 목적지 문자열의 길이를 얻는다.
    int len = n - m;

    // 대상에 (len + 1) 문자를 할당합니다(추가 null 문자의 경우 +1).
    char* dest = (char*)malloc(sizeof(char) * (len + 1));

    // 소스 문자열에서 m번째와 n번째 인덱스 사이의 문자를 추출합니다.
    // 대상 문자열에 복사
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // 대상 문자열을 null 종료
    *dest = '\0';

    // 목적지 문자열을 반환
    return dest - len;
}


int main() {
    int num;
    float f_num;
    char ch;
    char str[256];

    printf("입력 : ");
    scanf_like("hi %d, ||%f, %c, %s", &num, &f_num, &ch, str);
    printf("%d %f %c %s\n", num, f_num, ch, str);

    return 0;
}

int scanf_like(char* format, void* var, void* var1, void* var2, void* var3) {
    int start = 0;
    int peek = 0;
    int apeek = 0;
    int arr[5] = { -1. };       //0: 정수 1: 실수, 2: 문자열, 3: 문자
    void* vaArr[4] = { var, var1, var2, var3 };
    char input[256] = { '\0', };
    char* str[5];
    gets(input);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            switch (format[i+1])
            {
            case 'd': arr[apeek] = 0; break;
            case 'f': arr[apeek] = 1; break;
            case 's': arr[apeek] = 2; break;
            case 'c': arr[apeek] = 3; break;
            }
            apeek++;
        }
    }
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == ' ' || input[i] == '\t' || input[i + 1] == '\0') {
            str[peek] = substr(input, start, i+1);
            start = i + 1;
            peek++;
        }
    }

    for (int i = 0; i < 4;i++) {
        switch (arr[i])
        {
        case 0:
            *(int*)vaArr[i] = atoi(str[i]);
            break;
        case 1:
            *(float*)vaArr[i] = atof(str[i]);
            break;
        case 2:
            strcpy((char*)vaArr[i], str[i]);
            break;
        case 3:
            *(char*)vaArr[i] = str[i][0];
            break;
        }
    }
}