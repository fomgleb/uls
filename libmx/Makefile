BINARYNAME = libmx.a
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
OBJDIR = obj
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

all: create_objdir $(SOURCES) $(BINARYNAME)

$(BINARYNAME): $(OBJECTS)
	ar cr $(BINARYNAME) $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
uninstall: clean
	rm -rf $(BINARYNAME)

clean:
	rm -rf $(OBJDIR)

reinstall: uninstall all

create_objdir:
	mkdir -p $(OBJDIR)

# main.bin: main.c $(BINARYNAME)
# 	$(CC) $(CFLAGS) main.c -L. -lmx -o main.bin

#!/bin/sh -e
#clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c *.c
#ar cr minilibmx.a *.o
#rm -f *.o
#ranlib minilibmx.a

