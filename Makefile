BINARYNAME = uls
CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -g
OBJDIR = obj
SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

all: $(SOURCES) $(BINARYNAME)

$(BINARYNAME): create_objdir $(OBJECTS)
	make -C libmx
	$(CC) $(CFLAGS) $(OBJECTS) -Llibmx -lmx -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
uninstall: clean
	rm -rf $(BINARYNAME)

clean:
	rm -rf $(OBJDIR)

reinstall: uninstall all

create_objdir:
	mkdir -p $(OBJDIR)

#!/bin/sh -e
#clang -std=c11 -Wall -Wextra -Werror -Wpedantic -c *.c
#ar cr minilibmx.a *.o
#rm -f *.o
#ranlib minilibmx.a

