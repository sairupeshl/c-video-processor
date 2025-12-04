# Compiler to use
CC = gcc

# Compiler flags
# -g: Add debugging information
# -Wall: Turn on all warnings
CFLAGS = -g -Wall

# Libraries to link
# -lm: Math library
LIBS = -lm

# The name of your final program
TARGET = filter

# The source files needed
SRCS = filter.c helpers.c

# To build the target, type 'make'
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LIBS)

# To clean up, type 'make clean'
clean:
	rm -f $(TARGET)