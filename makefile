# Specify the target binary
TARGET = bloatfetch

# Specify the source files
SOURCES = $(wildcard *.c)

# Specify the object files
OBJECTS = $(SOURCES:.c=.o)

# Specify the compiler and flags
CC = clang
CFLAGS = -Wall -O2

# Build the target
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Clean up the build
clean:
	rm -f $(OBJECTS) $(TARGET)

# Install the program
install: $(TARGET)
	install -m 0755 $(TARGET) /bin

# Uninstall the program
uninstall:
	rm -f /bin/$(TARGET)
