BINARYNAME = libmx.a

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -MMD -MP

OBJDIR = obj
SRCDIR = src

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

PHONY := all
all: install
	@:

PHONY += install
install: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	@ar cr $@ $(OBJECTS)
	@printf "$(notdir $@)\tcreated\n"

-include $(DEPENDS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $@

PHONY += clean
clean:
	@rm -rf $(OBJDIR)
	@printf "$(notdir $(BINARYNAME))\t$@ed\n"

PHONY += uninstall
uninstall: clean
	@rm -rf $(BINARYNAME)
	@printf "$(notdir $(BINARYNAME))\t$@ed\n"

PHONY += reinstall
reinstall: uninstall all

.PHONY: $(PHONY)
