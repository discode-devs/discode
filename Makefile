CC ?= clang

SRCDIR := src
OBJDIR := obj

SRC := $(wildcard $(SRCDIR)/**/*.c) $(wildcard $(SRCDIR)/**/**/*.c)
OBJS := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

MAIN := src/main
BUILDDIR := build
BINNAME := discode

CFLAGS := -pthread -Wall -Wextra -O2 -g -I$(SRCDIR)
LDFLAGS := -ldiscord -lcurl

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(MAIN)

$(MAIN): $(MAIN).c $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILDDIR)/$(BINNAME) $^ $(LDFLAGS)
	mkdir -p build/logs
	cp -r src/commands build
	
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(dir $(OBJS))

echo:
	@ echo SRC: $(SRC)
	@ echo OBJS: $(OBJS)

cmd:
	rm -rf build/commands
	cp -r src/commands build

clean:
	rm -rf $(MAIN)
	rm -rf $(OBJDIR)
	rm -rf build/logs
	rm build/discode
	rm -rf build/commands