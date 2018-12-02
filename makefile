CC = gcc
CFLAGS = -g -Wall
SRCDIR = src
EXTDIR = external
BUILDDIR = build
TARGET = bin/enigma
SRCEXT = c

SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

LDFLAGS = -lm
LDLIBS = -L$(EXTDIR)/iniparser/libiniparser.a

INC = -I include

all: $(TARGET)
	@$(MAKE) -C $(EXTDIR)/iniparser Makefile

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ $(INC) $(LDLIBS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	$(RM) build/*
	$(RM) bin/*
	@$(MAKE) -C $(EXTDIR)/iniparser clean
