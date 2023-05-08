#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>


int intSize = 0;
int charSize = 0;
int strSize = 0;

bool isFormatSpecifier(char c) {
    return c == 'd' || c == 'c' || c == 's';
}

char* substr(const char* src, int m, int n)
{
    int len = n - m;

    char* dest = (char*)malloc(sizeof(char) * (len + 1));

    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }

    *dest = '\0';

    return dest - len;
}

int FileScanf(const char* format, char* input, int** intC, char** charC, char*** strC) {
    int len = strlen(format);

    char* arr = (char*)malloc((len + 1) * sizeof(char));

    // 문자열 복사
    strcpy(arr, format);
    //printf("%s\n", arr);


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
                inputS = substr(inputSL, start, end);

                intSize++;
                *intC = (int*)realloc(*intC, intSize * sizeof(int));

                (*intC)[intSize-1] = atoi(inputS);
                if ((*intC)[intSize - 1] == 0) return -1;
                inputSL = substr(inputSL, end + strlen(token) - 1, strlen(inputSL));
                //printf("%s\n", inputSL);
                //start = end +strlen(token)-1;
                break;
            case 'c': 
                if (strstr(inputSL, substr(token, 1, strlen(token))) == NULL) return -1;
                end = strstr(inputSL, substr(token, 1, strlen(token))) - inputSL;
                //printf("%d %d\n",start, end);
                inputS = substr(inputSL, start, end);
                


                charSize++;
                *charC = (char*)realloc(*charC, charSize * sizeof(char));
                if (inputS[1] != '\0') return -1;
                (*charC)[charSize - 1] = inputS[0];
                //printf("%s", strlen((*charC)[charSize - 1]));

                inputSL = substr(inputSL, end + strlen(token) - 1, strlen(inputSL));
                //start = end + strlen(token) - 1;
                break;
            case 's': 
                if (strstr(inputSL, substr(token, 1, strlen(token))) == NULL) return -1;
                end = strstr(inputSL, substr(token, 1, strlen(token))) - inputSL;
                //printf("%d %d\n", start, end);
                inputS = substr(inputSL, start, end);
                

                strSize++;
                *strC = (char**)realloc(*strC, strSize * sizeof(char*));

                (*strC)[strSize - 1] = (char*)malloc((strlen(inputS) + 1) * sizeof(char));

                strcpy((*strC)[strSize - 1], inputS);

                //printf("%d\n", strSize);
                //printf("%s\n", (*strC)[strSize - 1]);
                inputSL = substr(inputSL, end + strlen(token)-1, strlen(inputSL));
                //printf("%s\n", inputSL);
                break;
            }
        }
        else {
            char* ch = strstr(input, token);
            if (ch != input) {
                return -1;
            }
            inputSL = substr(input, strlen(token), strlen(input));
        }

        token = strtok(NULL, "%");

       
    }
    free(arr);
    return 1;
}

int main() {
    FILE* fp;
    fp = fopen("database.txt", "r");
    if (fp == NULL) {
        printf("?");
    }
    int flag;
    int* intCnt = NULL;
    char* chCnt = NULL;
    char** strCnt = NULL;

    char format[1000];
    char input[1000];

    while (fgets(format, sizeof(format), fp) != NULL) {
        fgets(input, sizeof(input), fp);
        //printf("%s%s", format, input);
        flag = FileScanf(format, input, & intCnt, & chCnt, & strCnt);
        if (flag == -1) {
            printf("wrong file format");
            return 0;
        }
    }

    printf("Int 변수는 %d개 있습니다.\n", intSize);
    for (int i = 0; i < intSize; i++) {
        printf("\t%d\n", intCnt[i]);
    }
    printf("\nchar 변수는 %d개 있습니다.\n", charSize);
    for (int i = 0; i < charSize; i++) {
        printf("\t%c\n", chCnt[i]);
    }
    printf("\nchar* 변수는 %d개 있습니다.\n", strSize);
    for (int i = 0; i < strSize; i++) {
        printf("\t%s\n", strCnt[i]);
    }

    fclose(fp);
    return 0;
}