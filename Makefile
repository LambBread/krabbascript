CC      := gcc
CFLAGS  := -Wall -Wextra -Werror -O2 -I include
SRC_DIR := src
OBJ_DIR := obj
TARGET  := kscript

SRCS    := $(shell find $(SRC_DIR) -name "*.c")
OBJS    := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "     LD $@"
	@$(CC) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "     CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean