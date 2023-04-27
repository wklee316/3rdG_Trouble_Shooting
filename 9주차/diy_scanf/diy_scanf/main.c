#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

int scanf_like(char* format, void* var);

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


int main() {
    int num;
    float f_num;
    char ch;
    char str[256];

    printf("�Է� : ");
    scanf_like("hi %d, ||%f, %c, %s", &num, &f_num, &ch, str);
    printf("%d %f %c %s\n", num, f_num, ch, str);

    return 0;
}

int scanf_like(char* format, void* var, void* var1, void* var2, void* var3) {
    int start = 0;
    int peek = 0;
    int apeek = 0;
    int arr[5] = { -1. };       //0: ���� 1: �Ǽ�, 2: ���ڿ�, 3: ����
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