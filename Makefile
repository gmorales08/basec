PROGRAM = basec

CC             = gcc
CFLAGS         = -Wall -Wextra -pedantic -std=c89
DEBUG_CFLAGS   = -g3
RELEASE_CFLAGS = -O3 -DNDEBUG

LD              = gcc
LDFLAGS         =
DEBUG_LDFLAGS   =
RELEASE_LDFLAGS = -s

DEBUGGER       = gdb
DEBUGGER_FLAGS =

SRCDIR      = .
OBJDIR      = obj
BINDIR      = bin
INSTALL_DIR = /usr/local/bin
BUILD_DIRS  = $(OBJDIR) $(BINDIR)

SRCS      = $(wildcard $(SRCDIR)/*.c)
OBJS      = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))


all: elf
# Elf build
elf: $(BUILD_DIRS)
elf: $(BINDIR)/$(PROGRAM)
# Debug build (do clean before)
debug_elf: CFLAGS  += $(DEBUG_CFLAGS)
debug_elf: LDFLAGS += $(DEBUG_LDFLAGS)
debug_elf: $(BUILD_DIRS)
debug_elf: $(BINDIR)/$(PROGRAM)
# Release build (do clean before)
release: CFLAGS     += $(RELEASE_CFLAGS)
release: LDFLAGS    += $(RELEASE_LDFLAGS)
release: $(BUILD_DIRS)
release: $(BINDIR)/$(PROGRAM)


$(BINDIR)/$(PROGRAM): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BUILD_DIRS):
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	rm -rf $(TEST_BINDIR)

.PHONY: install
install:
	mkdir -p $(INSTALL_DIR)
	mv $(BINDIR)/$(PROGRAM) $(INSTALL_DIR)

.PHONY: uninstall
uninstall:
	rm -rf $(INSTALL_DIR)/$(PROGRAM)

debug: debug_elf
	$(DEBUGGER) $(DEBUGGER_FLAGS) $(BINDIR)/$(PROGRAM)

valgrind: debug_elf
	valgrind --leak-check=full \
		 --show-leak-kinds=all \
		 --track-origins=yes \
		 --verbose \
		 ./$(BINDIR)/$(PROGRAM)

.PHONY: info
info :
	@echo 'Rules:'
	@echo '  all       : elf'
	@echo '  elf       : make an elf file'
	@echo '  debug_elf : make an elf with debug info'
	@echo '  release   : make an optimal elf build'
	@echo '  clean     : removes the program and the objects'
	@echo '  install   : install the program (sudo required)'
	@echo '  uninstall : uninstall the program (sudo required)'
	@echo '  debug     : run the debugger with the program'
	@echo '  valgrind  : run valgrind with the program'
	@echo '  info      : show this page'
	@echo 'Tools:'
	@echo '  Compiler        :' $(CC)
	@echo '    Compile flags :' $(CFLAGS)
	@echo '    Debug flags   :' $(DEBUG_CFLAGS)
	@echo '    Release flags :' $(RELEASE_CFLAGS)
	@echo '  Linker          :' $(LD)
	@echo '    Link flags    :' $(LDFLAGS)
	@echo '    Debug flags   :' $(DEBUG_LDFLAGS)
	@echo '    Release flags :' $(RELEASE_LDFLAGS)
	@echo '  Debugger :' $(DEBUGGER)
	@echo '    Flags  :' $(DEBUGGER_FLAGS)
	@echo 'Paths:'
	@echo '  Source       :' $(SRCDIR)
	@echo '  Objects      :' $(OBJDIR)
	@echo '  Binary       :' $(BINDIR)
	@echo '  Installation :' $(INSTALL_DIR)
	@echo 'Files:'
	@echo '  Source files:' $(SRCS)
	@echo '  Object files:' $(OBJS)
