#include <stdio.h>
#include <string.h>

#include "../include/cracker.h"
#include "../include/hash.h"

void crack(FILE * wordlist, FILE * cred)
{
    FILE * output_file = fopen("./slayed.txt", "w");

    char cred_id[32];
    char cred_pw[32];
    char cred_line[128];

    char wordlist_line[64];
    char * wordlist_hash;

    printf("\n===== RESULT =====\n");

    while (1)
    {
        char * cred_table = fgets(cred_line, sizeof(cred_line), cred);

        if (cred_table == NULL) break; 

        sscanf(cred_line, "%[^ :\n]:%[^ :\n]", cred_id, cred_pw);

        rewind(wordlist);

        while (1)
        {
            char * wls = fgets(wordlist_line, sizeof(wordlist_line), wordlist);

            if (wls == NULL)
            {
                printf("%s:PASSWORD NOT FOUND\n", cred_id);
                fprintf(output_file, "%s:PASSWORD NOT FOUND\n", cred_id);

                break;
            }

            wordlist_line[strcspn(wordlist_line, "\n")] = '\0';
            wordlist_hash = djb2((const unsigned char *)wordlist_line);

            if (!strcmp(wordlist_hash, cred_pw))
            {
                printf("%s:%s\n", cred_id, wordlist_line);
                fprintf(output_file, "%s:%s\n", cred_id, wordlist_line);

                break;
            }
        }
    }

    printf("==================\n");
    fclose(output_file);
}


