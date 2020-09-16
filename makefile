#
# Alter Ego
#

BIN = exe/AlterEgo

CC = vc

VBCCINCLUDE = C:/vbcc/targets/m68k-amigaos/include/
OSINCLUDE = C:/vbcc/include_h/

CFLAGS =-quiet -c -O2 -sc -c99 -I$(VBCCINCLUDE) -I$(OSINCLUDE)
MINSTART = C:/vbcc/targets/m68k-amigaos/lib/minstart.o

AS = vasmm68k_mot.exe
AFLAGS =-quiet -Fvobj -x -IC:/vbcc/include_i/ 

SRCDIR = src
OBJDIR = obj

OBJECTS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c)) \
	$(OBJDIR)/shrinkler.o
HEADERS = $(wildcard $(SRCDIR)/*.h)

LIBS =
LINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc -s -x $(MINSTART)

RM = rm

$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) $< -o $@

$(BIN): $(OBJECTS)
	$(LINK) $(OBJECTS) -o $@ $(LIBS)

$(OBJDIR)/shrinkler.o: $(SRCDIR)/asm/shrinkler.s
	$(AS) $(AFLAGS) $(SRCDIR)/asm/shrinkler.s -o $(OBJDIR)/shrinkler.o




.PHONY: cls aec tests

aec:	$(BIN)
cls:
	$(RM) $(OBJECTS) $(TESTOBJECTS) $(BIN) $(TESTBIN)

tests:	$(TESTBIN)

#tests
TESTBIN = exe/tests

TESTOBJDIR = obj
TESTOBJECTS = $(patsubst test/%.c, obj/%.o, $(wildcard test/*.c))

OBJ-OUT = obj/main.o
TEST-MAIN-OBJ = $(filter-out $(OBJ-OUT), $(OBJECTS))




TESTLINK = vlink -nostdlib -bamigahunk -Bstatic -Cvbcc $(MINSTART)

$(TESTOBJDIR)/%.o: test/%.c
	$(CC) $(CFLAGS) $< -o $@

$(TESTBIN): $(TESTOBJECTS) $(TEST-MAIN-OBJ)
	$(TESTLINK) $(TESTOBJECTS) $(TEST-MAIN-OBJ) -o $@ $(LIBS)
