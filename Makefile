PROGRAM      := basec
PROGRAM_ARGS := -d 128

CC           := gcc
CCFLAGS      := -Wall -Wextra -pedantic -std=c90

DEBUG        := gdb
DEBUG_FLAGS  := -tui --args


.PHONY: clean install uninstall info

all : elf

elf : $(PROGRAM).c
	$(CC) $(CCFLAGS) $(PROGRAM).c -o $(PROGRAM)

elf_debug : $(PROGRAM).c
	$(CC) $(CCFLAGS) -g $(PROGRAM).c -o $(PROGRAM)

debug : elf_debug
	$(DEBUG) $(DEBUG_FLAGS) $(PROGRAM) $(PROGRAM_ARGS)

valgrind : elf_debug
	valgrind --leak-check=full \
		 --show-leak-kinds=all \
		 --track-origins=yes \
		 --verbose \
		 ./$(PROGRAM) $(PROGRAM_ARGS)

clean :
	rm -f $(PROGRAM)

install : elf
	mkdir -p /usr/local/bin
	mv $(PROGRAM) /usr/local/bin

uninstall :
	rm -f /usr/local/bin/$(PROGRAM)

info :
	@echo 'Tools:'
	@echo '  Compiler: ' $(CC)
	@echo '  Debugger: ' $(DEBUG)
	@echo 'Rules:'
	@echo '  all       : elf'
	@echo '  elf       : build the elf file'
	@echo '  debug     : run the debugger with the program'
	@echo '  valgrind  : run valgrind with the program'
	@echo '  clean     : removes the compiled program'
	@echo '  install   : install the program in the system'
	@echo '  uninstall : uninstall the program'
	@echo '  info      : show this page'
