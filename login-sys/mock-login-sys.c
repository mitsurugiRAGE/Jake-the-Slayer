#include <stdio.h>
#include <string.h>
#include "credential.h"

int main(void)
{
    const char * CREDENTIAL = ".cred";
    FILE * fp = fopen(CREDENTIAL, "r");

    char line[1024];
    char id_buf[32];
    char passwd_buf[32];

    char id_input[32];
    char passwd_input[32];

    int line_size = sizeof(line) / sizeof(char);

    import_credential(fp, line, line_size, id_buf, passwd_buf);
  
    login_window(id_input, passwd_input);

    if (!(strcmp(id_buf, id_input)) && !(strcmp(passwd_buf, passwd_input)))
    {
      printf("WELCOME! %s!", id_buf);
    }

    else
    {
      printf("ID or password is INCORRECT.\n");
    }

    fclose(fp);

    return 0;
}
