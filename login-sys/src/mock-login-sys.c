#include <stdio.h>
#include <string.h>

#include "../include/credential.h"

int main(void)
{
    const char * CREDENTIAL = "login-sys/src/.cred"; // 자격 증명 파일 이름 지정
    FILE * fp = fopen(CREDENTIAL, "r"); // 자격 증명 파일을 읽기 모드로 열기

    char id_buf[32]; // 자격증명 원본 id를 저장할 버퍼
    char passwd_buf[32]; // 자격증명 원본 패스워드를 저장할 버퍼

    char id_input[32]; // 사용자가 입력한 id를 저장할 버퍼
    char passwd_input[32]; // 사용자가 입력한 패스워드를 저장할 버퍼

    login_window(id_input, passwd_input);
    import_credential(fp, id_buf, passwd_buf, id_input);
  
    /* 만약 입력된 id와 패스워드가 `.cred`에 있는 것과 모두 일치한다면 */
    if (!strcmp(id_buf, id_input) && !strcmp(passwd_buf, passwd_input))
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

    fclose(fp);

    return 0;
}
