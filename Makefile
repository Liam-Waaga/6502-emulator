NAME = 6502
GIT_LINK = https://github.com/da-ostrich-king/6502-emulator


CC = gcc
CFLAGS = -g -Wpedantic -Wall -Wextra -std=c23
CFLAGS += -D_POSIX_C_SOURCE=199309L
CFLAGS += -DGIT_LINK=\"$(GIT_LINK)\"
CFLAGS += -Isrc -Isrc/devices -Isrc/log


LINKFLAGS = 
BINNAME = 

ifeq ($(OS),Windows_NT)
BINNAME = $(NAME).exe
LINKFLAGS += 
else
LINKFLAGS += 
BINNAME = $(NAME)
endif

BUILDDIR := build
SRCDIR := src

SOURCEFILES := $(shell ls $(SRCDIR)/**/*.c)
SOURCEFILES += $(shell ls $(SRCDIR)/*.c)
OBJECTFILES := $(shell echo $(SOURCEFILES) | sed 's/\.c/\.o/g' | sed 's/src/$(BUILDDIR)\/objects/g')

COMPILE_COMMANDS = build/compile_commands.json
BEAR_EXISTS := $(shell command -v bear 2>/dev/null)

THREAD_COUNT := $(shell nproc)

.PHONY: clean all compile_commands



all: $(OBJECTFILES)
	mkdir -p $(BUILDDIR)
	$(CC) $^ -o $(BUILDDIR)/$(BINNAME) $(LINKFLAGS)

clean:
	rm -r $(BUILDDIR) || true

compile_commands:
	mkdir -p $(BUILDDIR)
ifeq ($(BEAR_EXISTS),)
	@printf "Bear does not exist on system, cannot generate compile_commands.json.\n"
	@printf "Please run `make all` instead which will not generate compile_commands.json.\n"
	@printf "Or install bear."
	false
else
	make clean
	mkdir -p $(BUILDDIR)
	bear --output $(COMPILE_COMMANDS) -- $(MAKE) all -j$(THREAD_COUNT)
endif


$(OBJECTFILES): $(SOURCEFILES)
	@printf "Compiling $@\n"
	mkdir -p $(shell dirname "$@")
	test $@ -nt $(shell echo "$@" | sed 's/\.o/\.c/g' | sed 's/build\/objects/src/g') || $(CC) -c $(shell echo "$@" | sed 's/\.o/\.c/g' | sed 's/build\/objects/src/g') -o $@ $(CFLAGS)
	@printf "Compiled $@\n\n"

