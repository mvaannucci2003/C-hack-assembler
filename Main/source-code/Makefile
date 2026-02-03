CC = gcc
CFLAGS = -Wall -Iheader-files
LDFLAGS =
TARGET = main
SRC_DIR = source-files
OBJ_DIR = obj

# List the object files with the directory prefix
OBJFILES = $(OBJ_DIR)/main.o $(OBJ_DIR)/parser.o $(OBJ_DIR)/symtable.o $(OBJ_DIR)/error.o
# This rule says: to create any .o file in the obj folder,
# look for a corresponding .c file in the source-files folder.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

# Rule to create the directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

