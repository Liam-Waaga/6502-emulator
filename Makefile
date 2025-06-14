NAME = 6502

CC = gcc
CFLAGS = -g -Wpedantic -Wall -Wextra -O3

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

.PHONY: clean all

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
