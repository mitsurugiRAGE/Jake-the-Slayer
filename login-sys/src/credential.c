#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/credential.h"

void login_window(char * id_, char * passwd_)
{
    /*
     * 함수 설명:
     * 사용자의 id와 패스워드를 입력받고 저장한다
     *
     * 파라미터 설명:
     * - id_: 사용자가 입력한 id를 저장할 버퍼의 주소
     * - passwd_: 사용자가 입력한 패스워드를 저장할 버퍼의 주소
     */

    printf("id: ");
    scanf("%s", id_);
    printf("passwd: ");
    scanf("%s", passwd_);
}

void import_credential(FILE * f, char * id_, char * passwd_, char * id_input_)
{
    /*
     * 함수 설명:
     * 전달받은 파일 포인터(`.cred`)에서 사용자 정보를 불러온다
     *
     *     상세:
     *     1. while-loop로 무한 반복
     *     2. `fgets()` 함수로 `.cred`의 정보를 줄 단위로 가져온다
     *         2-1. 만약 파일의 마지막에 이르면 반복문을 탈출한다
     *     3. `sscanf()` 함수로 가져온 줄의 id와 패스워드를 저장한다
     *         3-1. 만약 가져온 id와 사용자가 입력한 id가 같으면 반복문을 탈출한다
     *              (알맞은 id와 패스워드를 비교하기 위해 탐색 중지)
     *
     * 파라미터 설명:
     * - f: 자격 증명이 있는 파일
     * - id_: 자격 증명의 원본 id를 저장할 문자 배열 주소
     * - passwd_: 자격 증명의 원본 패스워드를 저장할 문자 배열 주소
     * - id_input_: 사용자가 입력한 id가 저장된 문자 배열 주소
     *              (`id_`와 비교할 때 사용)
     */

    const int line_size = 1024; // 읽을 줄의 최대 길이
    char * line = (char *)malloc(sizeof(char) * line_size); // 줄을 저장할 버퍼

    while (1)
    {
        char * p_line = fgets(line, line_size, f); // 파일을 줄 단위로 불러오기

        if (p_line == NULL) break; // 파일 끝에 이르러 더 이상 읽을게 없으면 break
            
        sscanf(line, "%32[^ :\n]:%32[^ :\n]", id_, passwd_); // 줄의 id와 패스워드를 추출 및 저장

        if (!strncmp(id_, id_input_, strlen(id_))) break; // 만약 자격 증명 상 원본 id와 사용자가 입력한 id가 같으면 break
    }

    free(line); // 메모리 해제
}
