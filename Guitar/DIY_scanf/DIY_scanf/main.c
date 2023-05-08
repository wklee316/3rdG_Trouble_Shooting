#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

bool isFormatSpecifier(char c) {
    return c == 'd' || c == 'c' || c == 's';
}

int countType(char* str) {
    int c = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '%') {
            switch (str[i + 1])
            {
            case 'd':
            case 'c':
            case 's': c++;
                break;

            }
        }
    }
    return c;
}

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

int FileScanf(const char* format, ...) {
    char input[100];
    printf("Enter a value: ");
    gets(input);
    int cnt = countType(format);
    //printf("cnt : %d\n",cnt);
    int len = strlen(format);

    // 메모리 할당
    char* arr = (char*)malloc((len + 1) * sizeof(char));

    // 문자열 복사
    strcpy(arr, format);
    //printf("%s\n", arr);
    va_list args;
    va_start(args, format);

    int peek = 0;
    char* inputS;
    char* inputSL = input;
    char* token = strtok(arr, "%");
    int start = 0;
    int end;
    //char* inputToken = strtok_s(input, " ", &tmp2);


    while (token != NULL) {
        //printf("tok : %s\ninput : %s\n\n",token, inputToken);

        if (isFormatSpecifier(token[0])) {
            switch (token[0])
            {
            case 'd':
                if (strstr(inputSL, substr(token, 1, strlen(token))) == NULL) return -1;
                end = strstr(inputSL, substr(token, 1, strlen(token))) - inputSL;
                //printf("%d %d\n", start, end);
                inputS = substr(inputSL, start, end);
                int* intPtr = va_arg(args, int*);
                //printf("%s\n",inputS);
                //printf("%x", intPtr);

                *intPtr = atoi(inputS);

                inputSL = substr(inputSL, end + strlen(token) - 1, strlen(inputSL));
                //printf("%s\n", inputSL);
                //start = end +strlen(token)-1;
                break;
            case 'c':
                if (strstr(inputSL, substr(token, 1, strlen(token))) == NULL) return -1;
                end = strstr(inputSL, substr(token, 1, strlen(token))) - inputSL;
                //printf("%d %d\n",start, end);
                inputS = substr(inputSL, start, end);
                char* chPtr = va_arg(args, char*);
                //printf("%s\n", inputS);
                *chPtr = inputS[0];

                inputSL = substr(inputSL, end + strlen(token) - 1, strlen(inputSL));
                //start = end + strlen(token) - 1;
                break;
            case 's':
                if (strstr(inputSL, substr(token, 1, strlen(token))) == NULL) return -1;
                end = strstr(inputSL, substr(token, 1, strlen(token))) - inputSL;
                //printf("%d %d\n", start, end);
                inputS = substr(inputSL, start, end);
                char* strPtr = va_arg(args, char*);
                //printf("%s\n", inputS);
                strcpy(strPtr, inputS);

                inputSL = substr(inputSL, end + strlen(token) - 1, strlen(inputSL));
                //printf("%s\n", inputSL);
                //start = end + strlen(token) - 1;
                break;
            }
        }
        else {
            char* ch = strstr(input, token);
            if (ch != input) {
                return -1;
            }
            inputSL = substr(input, strlen(token), strlen(input));
            //start = strlen(token);
        }

        token = strtok(NULL, "%");

        /*
        if (isFormatSpecifier(token[strlen(token) - 1])) {
            if (strcmp(token, "%d") == 0) {
                int* intPtr = va_arg(args, int*);
                //printf("%x", intPtr);

                *intPtr = atoi(inputToken);
            }
            else if (strcmp(token, "%s") == 0) {
                char* strPtr = va_arg(args, char*);
                strcpy(strPtr, inputToken);
            }
            else {
                printf("Unsupported format.\n");
                return;
            }
        }
        else {
            if (strcmp(token, inputToken) != 0) {
                printf("Input value does not match the format.\n");
                return;
            }
        }

        token = strtok_s(NULL, " ", &tmp1);
        inputToken = strtok_s(NULL, " ", &tmp2);
    }
    */
    }
    va_end(args);
}

int main() {
    int age;
    int score;
    char grade;
    char statement[100];
    int flag;
    flag = FileScanf("나는 %s입니다. 점수는%d점 입니다. 따라서 학점은 %c 입니다.", statement, &score, &grade);
    //FileScanf("입력값은 %s 입니다.", statement);

    if (flag == -1)
        printf("wrong Input");
    else
        printf("이름: %s\n점수: %d\n학점: %c", statement, score, grade);
    //printf("문장: %s\n", statement);

    return 0;
}