# Jake the Slayer: Password Cracker (C Language Project)
djb2 해시 알고리즘을 사용하는 간단한 패스워드 크래킹 도구입니다.

```text
   ___  ___   _   __ _____
  |_  |/ _ \ | | / /|  ___|
    | / /_\ \| |/ / | |__
    | |  _  ||    \ |  __|
/\__/ / | | || |\  \| |___
\____/\_| |_/\_| \_/\____/


 _   _
| | | |
| |_| |__   ___
| __| '_ \ / _ \
| |_| | | |  __/
 \__|_| |_|\___|


 _____ _       _____   _____________
/  ___| |     / _ \ \ / /  ___| ___ \
\ `--.| |    / /_\ \ V /| |__ | |_/ /
 `--. \ |    |  _  |\ / |  __||    /
/\__/ / |____| | | || | | |___| |\ \
\____/\_____/\_| |_/\_/ \____/\_| \_|
```

## 프로젝트 개요
Jake the Slayer는 유출된 크리덴셜 파일과 워드리스트를 비교하여 평문 패스워드를 찾아내는 간단한 프루트 포스 크래커입니다.
학습 및 교육을 목적으로 제작된 프로젝트로, 실제 서비스와 보안 환경 등에 악용을 금합니다.
## 기능
- djb2 기반 단방향 해시 함수 구현
- 유출된 credential 테이블 파싱 기능
- 워드리스트 기반 브루트 포스 매칭
- 매칭 실패 시 "PASSWORD NOT FOUND" 출력
- 간단한 텍스트 로고 출력
## 프로젝트 구조
```tree
Jake-the-Slayer
├── jake_logo
├── login-sys
│   ├── bin
│   ├── build
│   ├── include
│   │   ├── credential.h
│   │   └── hash.h
│   └── src
│       ├── .cred
│       ├── credential.c
│       ├── hash.c
│       └── mock-login-sys.c
├── Makefile
├── README.md
└── slayer
    ├── bin
    ├── build
    ├── include
    │   ├── cracker.h
    │   └── hash.h
    └── src
        ├── cracker.c
        ├── hash.c
        ├── head-rockyou.txt
        ├── jake.c
        └── leaked_cred
```
## 클론과 빌드
- 아래 명령으로 레포지터리를 클론합니다:
```sh
$ mkdir ~/Jake; git clone https://github.com/mitsurugiRAGE/Jake-the-Slayer.git ~/Jake
```
- 생성된 프로젝트 디렉터리로 이동하고 빌드합니다 (Makefile 사용):
```sh
$ cd ~/Jake; make
```
- 빌드가 완료되었으면, 아래 명령으로 로그인 시스템 실행 할 수 있습니다:
```sh
$ make run-login
```
- 또한 아래 명령으로 패스워드 크래커 실행를 실행할 수 있습니다:
```sh
$ make run-jake ARGS="./slayer/src/head-rockyou.txt ./slayer/src/leaked_cred"
```
## 테스트 환경
- OS: Debian GNU/Linux 12 (bookworm) aarch64
- Hardware: Raspberry Pi 5 Model B
- Compiler: GCC 12.2.0 (Debian 12.2.0-14+deb12u1)
- Shell: zsh 5.9
## LICENSE
이 프로젝트는 MIT License 하에 배포됩니다.
자세한 내용은 저장소의 [LICENSE](./LICENSE)를 참고하세요.
