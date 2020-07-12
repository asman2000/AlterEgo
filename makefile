#
# Alter Ego
#

BIN = exe/AlterEgo

CC = vc
CFLAGS =-quiet -c -O2 -sc -c99 -IC:/vbcc/targets/m68k-amigaos/include/ -IC:/vbcc/include_h/

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c))
HEADERS = $(wildcard $(SRCDIR)/*.h)

LIBS = -LC:/VBCC/targets/m68k-amigaos/lib -lvc -lamiga
LINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc -s -x C:/vbcc/targets/m68k-amigaos/lib/minstart.o

RM = rm

$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(BIN): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@ $(LIBS)


.PHONY: cls aec

aec:	$(BIN)
cls:
	$(RM) $(OBJECTS) $(BIN)

#tests

TESTOBJDIR = obj
TESTOBJECTS = $(patsubst test/%.c, obj/%.o, $(wildcard test/*.c))
TESTLINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc C:/vbcc/targets/m68k-amigaos/lib/startup.o


$(TESTOBJDIR)/%.o: test/%.c
	$(CC) $(CFLAGS) $< -o $@

tests: $(TESTOBJECTS)
	$(TESTLINK) $(TESTOBJECTS) -o $@ $(LIBS)
