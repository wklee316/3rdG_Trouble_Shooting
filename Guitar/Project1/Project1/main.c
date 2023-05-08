#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>

bool isFormatSpecifier(char c) {
    return c == 'd' || c == 'f' || c == 'lf' || c == 's';
}

int countType(char* str) {
    int c = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '%') {
            if (str[i + 1] == 'd');
            else if (str[i + 1] == 'c');
            else if (str[i + 1] == 's');
            c++;
        }
    }
    return c;
}

void FileScanf(const char* format, ...) {
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

    char* tmp1, *tmp2;
    char* token = strtok_s(arr, " ", &tmp1);
    char* inputToken = strtok_s(input, " ",&tmp2);


    while (token != NULL && inputToken != NULL) {
        //printf("tok : %s\ninput : %s\n\n",token, inputToken);
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

    va_end(args);
}

int main() {
    int age;
    char statement[100];

    printf("%x\n", &age);
    FileScanf("나는 %d 살입니다. 입력값은 %s 입니다.", &age, statement);
    //FileScanf("입력값은 %s 입니다.", statement);

    printf("나이: %d\n", age);
    printf("문장: %s\n", statement);

    return 0;
}