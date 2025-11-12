#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/credential.h"
#include "../include/hash.h"

int main(void)
{
    const char * CREDENTIAL = "login-sys/src/.cred"; // 자격 증명 파일 이름 지정
    FILE * fp = fopen(CREDENTIAL, "r"); // 자격 증명 파일을 읽기 모드로 열기

    char id_buf[32]; // 자격증명 원본 id를 저장할 버퍼
    char passwd_buf[32]; // 자격증명 원본 패스워드를 저장할 버퍼

    char id_input[32]; // 사용자가 입력한 id를 저장할 버퍼
    char passwd_input[32]; // 사용자가 입력한 패스워드를 저장할 버퍼
    char * passwd_hashed;

    login_window(id_input, passwd_input);
    import_credential(fp, id_buf, passwd_buf, id_input);
    passwd_hashed = djb2((const unsigned char *)passwd_input);
  
    /* 만약 입력된 id와 패스워드가 `.cred`에 있는 것과 모두 일치한다면 */
    if (!strcmp(id_buf, id_input) && !strcmp(passwd_buf, passwd_hashed))
    {
        // 환영 메시지 출력
        printf("WELCOME! %s!", id_buf);
    }

    /* 입력된 것과 `.cred`의 정보가 하나라도 불일치한다면 */ 
    else
    {
        // id나 패스워드가 잘못되었다고 출력
        printf("ID or password is INCORRECT.\n");
    }

    free(passwd_hashed); // `hash.c`에서 동적할당된 메모리 해제
    fclose(fp);

    return 0;
}
