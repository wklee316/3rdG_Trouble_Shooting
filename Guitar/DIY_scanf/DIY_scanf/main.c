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
    // ������ ���ڿ��� ���̸� ��´�.
    int len = n - m;

    // ��� (len + 1) ���ڸ� �Ҵ��մϴ�(�߰� null ������ ��� +1).
    char* dest = (char*)malloc(sizeof(char) * (len + 1));

    // �ҽ� ���ڿ����� m��°�� n��° �ε��� ������ ���ڸ� �����մϴ�.
    // ��� ���ڿ��� ����
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    // ��� ���ڿ��� null ����
    *dest = '\0';

    // ������ ���ڿ��� ��ȯ
    return dest - len;
}

int FileScanf(const char* format, ...) {
    char input[100];
    printf("Enter a value: ");
    gets(input);
    int cnt = countType(format);
    //printf("cnt : %d\n",cnt);
    int len = strlen(format);

    // �޸� �Ҵ�
    char* arr = (char*)malloc((len + 1) * sizeof(char));

    // ���ڿ� ����
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
    flag = FileScanf("���� %s�Դϴ�. ������%d�� �Դϴ�. ���� ������ %c �Դϴ�.", statement, &score, &grade);
    //FileScanf("�Է°��� %s �Դϴ�.", statement);

    if (flag == -1)
        printf("wrong Input");
    else
        printf("�̸�: %s\n����: %d\n����: %c", statement, score, grade);
    //printf("����: %s\n", statement);

    return 0;
}