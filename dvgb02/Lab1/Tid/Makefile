# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Source files for executables
SRCS1 = time_client.c
SRCS2 = time_server.c

# Object files for executables
OBJS1 = $(SRCS1:.c=.o)
OBJS2 = $(SRCS2:.c=.o)

# Executable names
EXEC1 = time_client
EXEC2 = time_server

# Default target to build both executables
all: $(EXEC1) $(EXEC2)

# Link object files to create executable
$(EXEC1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^
$(EXEC2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $^

# Compile source files to object files
$(OBJS1): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
$(OBJS2): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS1) $(OBJS2) $(EXEC1) $(EXEC2)

.PHONY: all clean