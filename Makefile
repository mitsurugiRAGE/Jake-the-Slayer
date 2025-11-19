# ===== Compiler Settings =====
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -O2
RM := rm -f

# ===== Specify Directory =====
LOGIN_DIR := login-sys
LOGIN_SRC_DIR := $(LOGIN_DIR)/src
LOGIN_INC_DIR := $(LOGIN_DIR)/include
LOGIN_BIN_DIR := $(LOGIN_DIR)/bin
LOGIN_BUILD_DIR := $(LOGIN_DIR)/build

SLAYER_DIR := slayer
SLAYER_SRC_DIR := $(SLAYER_DIR)/src
SLAYER_INC_DIR := $(SLAYER_DIR)/include
SLAYER_BIN_DIR := $(SLAYER_DIR)/bin
SLAYER_BUILD_DIR := $(SLAYER_DIR)/build

# ===== Target Binary =====
LOGIN_BIN := $(LOGIN_BIN_DIR)/mock-login
SLAYER_BIN = $(SLAYER_BIN_DIR)/jake

# ===== Specify Source =====
LOGIN_SRCS := $(wildcard $(LOGIN_SRC_DIR)/*.c)
LOGIN_OBJS := $(patsubst $(LOGIN_SRC_DIR)/%.c,$(LOGIN_BUILD_DIR)/%.o,$(LOGIN_SRCS))
LOGIN_DEPS := $(LOGIN_OBJS:.o=.d)

SLAYER_SRCS := $(wildcard $(SLAYER_SRC_DIR)/*.c)
SLAYER_OBJS := $(patsubst $(SLAYER_SRC_DIR)/%.c,$(SLAYER_BUILD_DIR)/%.o,$(SLAYER_SRCS))
SLAYER_DEPS := $(SLAYER_OBJS:.o=.d)

# ===== Targets =====
.PHONY: all
 all: $(LOGIN_BIN) $(SLAYER_BIN)

# ===== Build Rules =====
$(LOGIN_BIN): $(LOGIN_OBJS) | $(LOGIN_BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(LOGIN_BUILD_DIR)/%.o: $(LOGIN_SRC_DIR)/%.c | $(LOGIN_BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -I$(LOGIN_INC_DIR) -c $< -o $@

$(LOGIN_BUILD_DIR) $(LOGIN_BIN_DIR):
	mkdir -p $@

$(SLAYER_BIN): $(SLAYER_OBJS) | $(SLAYER_BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(SLAYER_BUILD_DIR)/%.o: $(SLAYER_SRC_DIR)/%.c | $(SLAYER_BUILD_DIR)
	$(CC) $(CFLAGS) -MMD -MP -I$(SLAYER_INC_DIR) -c $< -o $@

$(SLAYER_BUILD_DIR) $(SLAYER_BIN_DIR):
	mkdir -p $@

# ===== run =====
.PHONY: run-login run-jake
run-login: $(LOGIN_BIN)
	./$(LOGIN_BIN)
run-jake: $(SLAYER_BIN)
	./$(SLAYER_BIN) $(ARGS)

# ===== clear =====
.PHONY: clean
clean:
	$(RM) $(LOGIN_OBJS) $(SLAYER_OBJS) $(LOGIN_DEPS) $(SLAYER_DEPS) $(LOGIN_BIN) $(SLAYER_BIN)

-include $(LOGIN_DEPS)
