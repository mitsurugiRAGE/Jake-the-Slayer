#include <stdio.h>
#include <stdlib.h>

#include "../include/cracker.h"

int main(int argc, char ** argv)
{
    /* 
     * 메인 함수에 적절한 인자가 전달되지 않으면 종료
     * [프로그램 실행 파일] [패스워드 리스트 경로] [크리덴셜 테이블 경로]를 입력해야 함
     */

    char logo_line[1024];

    if (argc != 3)
    {
        // 전달된 인자가 많거나 적으면 종료
        printf("usage: %s [WORDLIST PATH] [CREDENTAL TABLE PATH]\n", *argv);
        exit(1);
    }

    /* 전달 받은 파일 경로 접근 */
    FILE * wp = fopen(*(argv + 1), "r");
    FILE * tp = fopen(*(argv + 2), "r");

    FILE * lp = fopen("jake_logo", "r");

    /* 만약 파일 경로가 유효하지 않다면 프로그램 종료 */
    if (wp == NULL)
    {
        printf("Can NOT open the file '%s'.\nPlease Enter a VALID wordlist path.\n", *(argv + 1));
        exit(1);
    }

    if (tp == NULL)
    {
        printf("Can NOT open the file '%s'.\nPlease Enter a VALID table path.\n", *(argv + 2));
        exit(1);
    }

    while (1)
    {
        char * line = fgets(logo_line, sizeof(logo_line), lp);
        if (line == NULL) break;
        printf("%s", line);
    }

    crack(wp, tp);

    fclose(wp);
    fclose(tp);
    fclose(lp);

    return 0;
}
