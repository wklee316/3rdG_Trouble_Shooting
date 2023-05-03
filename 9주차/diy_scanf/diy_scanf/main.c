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

    int a;

    printf("입력 : ");
    a = scanf_like("%d\t%f %c %s", &num, &f_num, &ch, str);
    if (a == 1)  printf("%d %f %c %s\n", num, f_num, ch, str);
    else printf("wrong input");

    return 0;
}

int scanf_like(char* format, void* var, void* var1, void* var2, void* var3) {
    int start = 0;
    int cnt = 0;
    int formatC = 0;
    int inputC = 0;
    int flag = 1;
    void* vaArr[4] = { var, var1, var2, var3 };
    char input[256] = { '\0', };
    char* str[5];


    gets(input);

    while (format[formatC] != '\0' && input[inputC] != '\0') {

        if (format[formatC] == '%') {
            switch (format[++formatC])
            {
            case 'd':
                start = inputC;
                while (input[inputC] != ' ' && input[inputC] != '\t' && input[inputC + 1] != '\0') inputC++;
                str[cnt] = substr(input, start, inputC + 1);
                //printf("%s", str[cnt]);
                if (atoi(str[cnt]) == 0) {
                    flag = -1;
                    return flag;
                }
                *(int*)vaArr[cnt] = atoi(str[cnt]);
                inputC--;
                cnt++;
                break;
            case 'f':
                start = inputC;
                while ((input[inputC] != ' ') && (input[inputC] != '\t') && (input[inputC + 1] != '\0')) inputC++;
                str[cnt] = substr(input, start, inputC + 1);
                //printf("%s", str[cnt]);
                if (atof(str[cnt]) == 0) {
                    flag = -1;
                    return flag;
                }
                *(float*)vaArr[cnt] = atof(str[cnt]);
                inputC--;
                cnt++;
                break;
            case 's':
                start = inputC;
                while ((input[inputC] != ' ') && (input[inputC] != '\t') && (input[inputC + 1] != '\0')) inputC++;
                str[cnt] = substr(input, start, inputC + 1);
                //printf("%s", str[cnt]);
                strcpy((char*)vaArr[cnt], str[cnt]);
                inputC--;
                cnt++;
                break;
            case 'c':
                start = inputC;
                while ((input[inputC] != ' ') && (input[inputC] != '\t') && (input[inputC + 1] != '\0')) inputC++;
                str[cnt] = substr(input, start, inputC + 1);
                //printf("\n\n%s\n\n", str[cnt]);
                if (inputC - start > 1) {
                    flag = -1;
                    return flag;
                }
                *(char*)vaArr[cnt] = str[cnt][0];
                inputC--;
                cnt++;
                break;
            }
        }
        else if (format[formatC] == '\\' && format[formatC+1] == 't') {

            if (input[inputC] != '\t') {
                flag = -1;
                return flag;
            }
            formatC ++;
        }
        else if (format[formatC] != input[inputC]) {
            flag = -1;
            //printf("???\n %c %c\n", format[formatC], input[inputC]);
            return flag;
        }

        //printf("%d", cnt);
        formatC++;
        inputC++;
    }

    if (cnt != 4) flag = -1;

    return flag;
}