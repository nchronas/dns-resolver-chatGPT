# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall

# Target executable
TARGET = my_program

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule to build the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile C source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule to remove object files and the target executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony target to run the program
run: $(TARGET)
	./$(TARGET)

#
