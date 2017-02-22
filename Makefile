BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src
INCDIR=./include

CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -I$(INCDIR) $(shell pkg-config SDL_image --cflags)
LDFLAGS=$(shell pkg-config SDL_image --libs) -lSDL_ttf

SRC_FILES=$(wildcard $(SRCDIR)/*.c)
OBJ_FILES=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC_FILES))
#EDIT_OBJS=$(filter-out $(OBJDIR)/jouer.o, $(OBJ_FILES))

PROG=$(BINDIR)/CubeSolver

.PHONY: all
all: $(PROG)


$(PROG): $(OBJ_FILES)
	$(CC) $^ -o $@ $(LDFLAGS) -g


$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -g $< -c -o $@


$(OBJ_FILES): |$(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR) $(BINDIR)


.PHONY: valgrind

valgrind: $(EDITOR)
	valgrind --leak-check=full --show-possibly-lost=yes --show-reachable=yes --track-origins=yes --suppressions=sdl.supp $<

.PHONY: dependencies
dependencies: $(SRC_FILES)
	$(CC) $^ -I$(INCDIR) -MM -MG | sed -e 's/[a-zA-Z_]*\.o/$$(OBJDIR)\/&/' > tmp
	sed -e '/^#dependencies$$/,$$d' Makefile > tmpmake
	echo '#dependencies' >> tmpmake
	cat tmpmake tmp > Makefile
	rm tmp tmpmake

#everything beyond this line is automatically generated
#dependencies
$(OBJDIR)/mouvements.o: src/mouvements.c include/constantes.h include/mouvements.h \
 include/combinaison.h include/mouvements.h include/conversions.h
$(OBJDIR)/menu.o: src/menu.c include/menu.h include/constantes.h
$(OBJDIR)/main.o: src/main.c include/constantes.h include/solveur.h \
 include/mouvements.h include/image.h include/menu.h \
 include/conversions.h include/combinaison.h include/mouvements.h
$(OBJDIR)/combinaison.o: src/combinaison.c include/constantes.h \
 include/combinaison.h include/mouvements.h include/mouvements.h
$(OBJDIR)/conversions.o: src/conversions.c include/constantes.h \
 include/conversions.h include/mouvements.h include/mouvements.h
$(OBJDIR)/image.o: src/image.c include/constantes.h include/image.h
$(OBJDIR)/solveur.o: src/solveur.c include/solveur.h include/mouvements.h \
 include/constantes.h include/combinaison.h include/mouvements.h \
 include/conversions.h
