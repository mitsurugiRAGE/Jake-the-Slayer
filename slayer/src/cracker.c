#include <stdio.h>
#include <string.h>

#include "../include/cracker.h"
#include "../include/hash.h"

void crack(FILE * wordlist, FILE * cred)
{
    /*
     * 순서:
     * 1. 크리덴셜 테이블에서 ID와 해싱된 패스워드를 추출한다
     * 2. 워드리스트에서 패스워드 하나를 가져온다 (1 라인 당 1 패스워드)
     * 3. `2.`에서 추출한 패스워드를 해싱하고 `1.`에서 추출한 기존 패스워드와 비교한다
     * 4. 만약 그 둘이 같으면, 평문 패스워드를 워드리스트에서 알아냈다고 판단, "ID:Plain Password" 양식으로 출력하고 파일에 저장한다
     * 5. 만약 워드리스트에서 알맞는 평문 패스워드를 찾지 못하였으면, 패스워드를 찾지 못했음을 출력한다
     * 6. 크리덴셜 테이블을 끝까지 순회하며 `2. - 5.` 과정을 반복한다
     * 7. 출력 대상 파일(slayed.txt)을 닫고 크래킹 종료
     */

    FILE * output_file = fopen("./slayed.txt", "w"); // 결과를 출력할 파일 열기 (쓰기 모드)

    char cred_line[128]; // 크리덴셜 테이블을 줄 단위로 저장할 버퍼
    char cred_id[32]; // 크리덴셜 테이블에서 추출한 ID를 저장할 배열
    char cred_pw[32]; // 크리덴셜 테이블에서 추출한 패스워드를 저장할 배열

    char wordlist_line[64]; // 워드리스트에서 추출한 패스워드를 저장할 버퍼
    char * wordlist_hash; // `wordlist_line`에 담긴 패스워드를 해싱하여 저장할 포인터 변수

    printf("\n===== RESULT =====\n");

    /* 무한 루프; 크리덴셜 테이블의 끝까지 순회한다면 루프 종료 */
    while (1)
    {
        char * cred_table = fgets(cred_line, sizeof(cred_line), cred); // 크리덴셜 테이블 줄 단위로 가져오기

        if (cred_table == NULL) break; // 더 이상 읽을 라인이 없으면 루프 탈출

        sscanf(cred_line, "%[^ :\n]:%[^ :\n]", cred_id, cred_pw); // `ID:HASHED PASSWORD` 형식의 라인에서 ID와 해시된 패스워드 추출

        /*
         * 워드리스트 파일을 처음부터 읽을 수 있도록 `rewind()` (EOF 상태 방지)
         * 아래 while loop는 워드리스트 파일의 끝에 도달했을 때 루프를 탈출하게 되는데,
         * 그대로 EOF에 머물러 있게 되면 아래 루프를 진행하지 않게 됨
         */

        rewind(wordlist); 

        while (1)
        {
            char * wls = fgets(wordlist_line, sizeof(wordlist_line), wordlist); // 워드리스트 파일의 평문 패스워드 추출

            if (wls == NULL)
            {
                /*
                 * 만약 워드리스트 파일 끝까지 이르렀어도 패스워드를 찾지 못하면
                 * 워드리스트 내에 알맞은 패스워드가 없다고 판단,
                 * 패스워드를 찾지 못했다는 로그를 모니터와 파일에 출력;
                 * 루프 탈출
                 */

                printf("%s:PASSWORD NOT FOUND\n", cred_id); // 모니터 출력
                fprintf(output_file, "%s:PASSWORD NOT FOUND\n", cred_id); // 파일 출력

                break; // 루프 탈출
            }

            wordlist_line[strcspn(wordlist_line, "\n")] = '\0'; // 개행 문자를 NULL 문자로 교체
            wordlist_hash = djb2((const unsigned char *)wordlist_line); // 평문 패스워드 해싱 (djb2)

            if (!strcmp(wordlist_hash, cred_pw))
            {
                /* 
                 * 워드리스트의 해시된 패스워드와
                 * 크리덴셜 테이블의 해시된 패스워드가 일치하면
                 * 평문 패스워드를 알아냈다고 판단,
                 * "ID:PLAIN PASSWORD" 형식으로 모니터와 파일에 출력
                 * 루프 탈출
                 */

                printf("%s:%s\n", cred_id, wordlist_line); // 모니터 출력
                fprintf(output_file, "%s:%s\n", cred_id, wordlist_line); // 파일 출력

                break; // 루프 탈출
            }
        }
    }

    printf("==================\n");
    fclose(output_file); // 출력 파일 닫기
}
