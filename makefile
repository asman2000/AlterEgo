#
# Alter Ego
#

BIN = exe/AlterEgo

CC = vc
CFLAGS =-quiet -c -O2 -sc -c99 -IC:/vbcc/targets/m68k-amigaos/include/ -IC:/vbcc/include_h/

AS = vasmm68k_mot.exe
AFLAGS =-quiet -Fvobj -x -IC:/vbcc/include_i/ 

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c)) \
	$(OBJDIR)/shrinkler.o
HEADERS = $(wildcard $(SRCDIR)/*.h)

#LIBS = -LC:/VBCC/targets/m68k-amigaos/lib -lvc -lamiga
LIBS =
LINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc -s -x C:/vbcc/targets/m68k-amigaos/lib/minstart.o

RM = rm

$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(BIN): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@ $(LIBS)

$(OBJDIR)/shrinkler.o: $(SRCDIR)/asm/shrinkler.s
	$(AS) $(AFLAGS) $(SRCDIR)/asm/shrinkler.s -o $(OBJDIR)/shrinkler.o




.PHONY: cls aec

aec:	$(BIN)
cls:
	$(RM) $(OBJECTS) $(TESTOBJECTS) $(BIN)

#tests

TESTOBJDIR = obj
TESTOBJECTS = $(patsubst test/%.c, obj/%.o, $(wildcard test/*.c))
#	$(OBJDIR)/shrinkler.o

OBJ-OUT = obj/main.o
TEST-MAIN-OBJ = $(filter-out $(OBJ-OUT), $(OBJECTS))


TESTLINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc C:/vbcc/targets/m68k-amigaos/lib/minstart.o


$(TESTOBJDIR)/%.o: test/%.c
	$(CC) $(CFLAGS) $< -o $@

tests: $(TESTOBJECTS) $(TEST-MAIN-OBJ)
	$(TESTLINK) $(TESTOBJECTS) $(TEST-MAIN-OBJ) -o $@ $(LIBS)
