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
