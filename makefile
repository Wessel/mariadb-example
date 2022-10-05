# C compiler to use
CC := gcc

# Directory mappings
SRC_DIR := src
LIB_DIR := lib
OBJ_DIR := obj
OUT_DIR := out
INC_DIR := include

# Map all object and source files
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# All optional libs and Cflags to append to the final command
LIBS := $(mysql_config --libs) $(mysql_config --cflags) -lmysqlclient
CFLAGS := -I$(INC_DIR)

# Special and default commands
.PHONY: clean help
.DEFAULT_GOAL := help

# Macro for creating object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $<

## All make commands ##
help: ## Lists all commands
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

clean: ## Clean up all object files and executables
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/*

dev: $(OBJ_FILES) ## Build, run and debug the project
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS) && strace ./out/dev

run: $(OBJ_FILES) ## Build and run the project
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS) && ./out/run

prod: $(OBJ_FILES) ## Build the project
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS)
