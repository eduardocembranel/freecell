# Declaration of variables
CC = gcc
CC_FLAGS = -w
CC_LINKS = -lm
 
# File names
EXEC = freecell
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
 
# Main target
$(EXEC): $(OBJECTS)
				$(CC) $(CC_LINKS) $(OBJECTS) -o $(EXEC)

.PHONY: clean
# To obtain object files
%.o: %.c
				$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
				rm -f $(OBJECTS) $(EXEC)