
CC := gcc
CFLAGS := -O3 -std=c99
LDFLAGS := -pthread -lm

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin
EXE_NAME := nodesync

SRCS := $(shell find $(SRC_DIR) -name *.c)
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

TARGET := $(BIN_DIR)/$(EXE_NAME)

all: $(TARGET)



$(TARGET):$(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/%.c.o:%.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC_FLAGS) -c $< -o $@



install: all
	$(CP_R) $(BIN_DIR)/$(EXE_NAME) /usr/bin

uninstall:
	$(RM_RF) /usr/bin/$(EXE_NAME)

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: clean install uninstall
MKDIR_P ?= mkdir -p
CP_R ?= cp -r
RM_RF ?= rm -rf