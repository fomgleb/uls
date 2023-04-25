BINARYNAME = uls

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic -gdwarf-4 -MMD -MP

OBJDIR = obj
SRCDIR = src
LIBMX_DIR = libmx

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.o)))
DEPENDS = $(subst $(SRCDIR)/,,$(addprefix $(OBJDIR)/, $(SOURCES:.c=.d)))

LIBMX_LIB = $(LIBMX_DIR)/libmx.a

INCLUDE_LIBMX = -L$(dir $(LIBMX_LIB)) -l$(patsubst lib%.a,%,$(notdir $(LIBMX_LIB)))

define make_command
	@make --no-print-directory -C
endef

PHONY := all
all: $(BINARYNAME)
	@:

$(BINARYNAME): $(SOURCES) $(OBJDIR) $(OBJECTS)
	$(make_command) $(LIBMX_DIR)
	@$(CC) $(CFLAGS) $(OBJECTS) $(INCLUDE_LIBMX) -o $@
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
	@printf "$(notdir $(BINARYNAME))\t$@\n"

PHONY += uninstall
uninstall: clean
	@rm -rf $(BINARYNAME)
	@printf "$(notdir $(BINARYNAME))\t$@\n"

PHONY += reinstall
reinstall: uninstall all

PHONY += uninstall_with_libs
uninstall_with_libs:
	$(make_command) $(LIBMX_DIR) uninstall
	$(make_command) . uninstall

PHONY += reinstall_with_libs
reinstall_with_libs:
	$(make_command) $(LIBMX_DIR) reinstall
	$(make_command) . reinstall

.PHONY: $(PHONY)
