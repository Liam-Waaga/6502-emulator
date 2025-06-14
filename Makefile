NAME = 6502
GIT_LINK = https://github.com/da-ostrich-king/6502-emulator


CC = gcc
CFLAGS = -g -Wpedantic -Wall -Wextra -O3 -std=c23
CFLAGS += -D_POSIX_C_SOURCE=199309L
CFLAGS += -DGIT_LINK=\"$(GIT_LINK)\"


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

.PHONY: clean all

# Exists to do some checking before compilation starts
default:
	mkdir -p $(BUILDDIR)
ifeq ($(BEAR_EXISTS),)
	$(MAKE) all
else
	bear --output $(COMPILE_COMMANDS) -- $(MAKE) all
endif


all: $(OBJECTFILES)
	mkdir -p $(BUILDDIR)
	$(CC) $^ -o $(BUILDDIR)/$(BINNAME) $(LINKFLAGS)

clean:
	rm -r $(BUILDDIR) || true


$(OBJECTFILES): $(SOURCEFILES)
	@printf "Compiling $@\n"
	mkdir -p $(shell dirname "$@")
	test $@ -nt $(shell echo "$@" | sed 's/\.o/\.c/g' | sed 's/build\/objects/src/g') || $(CC) -c $(shell echo "$@" | sed 's/\.o/\.c/g' | sed 's/build\/objects/src/g') -o $@ $(CFLAGS)
	@printf "Compiled $@\n\n"
