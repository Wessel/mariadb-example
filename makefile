CC := gcc

SRC_DIR := src
LIB_DIR := lib
OBJ_DIR := obj
OUT_DIR := out
INC_DIR := include
SRC_FILES := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

LIBS := $(mysql_config --libs) $(mysql_config --cflags) -lmysqlclient
CFLAGS := -I$(INC_DIR)

dev: $(OBJ_FILES)
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS) && strace ./out/dev

run: $(OBJ_FILES)
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS) && ./out/run

prod: $(OBJ_FILES)
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $<

.PHONY: clean

clean:
# rm -f $(OBJ_DIR)/*.o *~ core $(INC_DIR)/*~
	rm -f $(OBJ_DIR)/*.o $(OUT_DIR)/*