#include <stdio.h>
#include <stdlib.h>

char * djb2(const unsigned char * str)
{
    unsigned long hash = 0x1505; // 5381
    unsigned char c;

    char * hashed_password = (char *)malloc(sizeof(char) * 16 + 1);

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    /* `hash` 변수가 unsigned long 이므로 `%lx` 형식 사용 */
    sprintf(hashed_password, "%lx", hash);     

    return hashed_password;
}
