#include <stdio.h>
#include "credential.h"

void import_credential(FILE * f, char * line_, int str_size, char * id_, char * passwd_)
{
    fgets(line_, str_size, f);
    sscanf(line_, "%32[^ :\n]:%32[^ :\n]", id_, passwd_);
}

void login_window(char * id_, char * passwd_)
{
    printf("id: ");
    scanf("%s", id_);
    printf("passwd: ");
    scanf("%s", passwd_);
}
