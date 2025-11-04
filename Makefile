# ===== Compiler Settings =====
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -O2
RM := rm -f

# ===== Specify Directory =====
LOGIN_DIR := login-sys
## SLAYER_DIR := slayer

# ===== Target Binary =====
LOGIN_BIN := $(LOGIN_DIR)/mock-login
## SLAYER_BIN = $(SLAYER_DIR)/jake

# ===== Specify Source =====
LOGIN_SRCS := $(LOGIN_DIR)/mock-login-sys.c $(LOGIN_DIR)/credential.c
LOGIN_OBJS := $(LOGIN_SRCS:.c=.o)

## SLAYER_SRCS :=
## SLAYER_OBJS := $(SLAYER_SRCS:.c=.o)

# ===== Targets =====
## .PHONY: all
## all: $(LOGIN_BIN) $(SLAYER_BIN)
.PHONY: all
all: $(LOGIN_BIN)

# ===== Build Rules =====
$(LOGIN_BIN): $(LOGIN_OBJS)
	$(CC) $(CFLAGS) $^ -o $@
## $(SLAYER_BIN): $(SLAYER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# ===== run =====
## .PHONY: run-login run-jake
## run-login: $(LOGIN_BIN)
##	   ./$(LOGIN_BIN)
## run-jake: $(SLAYER_BIN)
##	   ./$(SLAYER_BIN)
.PHONY: run-login
run-login: $(LOGIN_BIN)
	./$(LOGIN_BIN)

# ===== clear =====
.PHONY: clean
clean:
	$(RM) $(LOGIN_OBJS)
## clean: $(RM) $(LOGIN_OBJS) $(SLAYER_OBJS)
