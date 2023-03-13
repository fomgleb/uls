BINARYNAME = uls

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -MMD -MP

OBJDIR = obj
UTILS_OBJDIR = ../utils/obj
SRCDIR = src

SOURCES = $(subst ./,,$(shell find $(SRCDIR) -name "*.c"))
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

LIBMX_LIB = libmx/libmx.a

INCLUDE_LIBMX = -L$(dir $(LIBMX_LIB)) -l$(patsubst lib%.a,%,$(notdir $(LIBMX_LIB)))

all: install
	@:

install: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	make -C libmx
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_LIBMX) -o $@
	@printf "$(notdir $@)\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

clean:
	@rm -rf $(OBJDIR)
	@printf "$(notdir $(BINARYNAME))\t$@ed\n"

uninstall: clean
	@rm -rf $(BINARYNAME)
	@printf "$(notdir $(BINARYNAME))\t$@ed\n"

reinstall: uninstall all

