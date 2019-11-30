.PHONY: all clean

WARNFLAGS := -Wall -Wpedantic -Wextra -Waddress -Waggressive-loop-optimizations \
  -Wcast-qual -Wcast-align -Wmissing-declarations \
  -Wdouble-promotion -Wuninitialized -Winit-self \
  -Wstrict-aliasing -Wsuggest-attribute=const -Wtrampolines -Wfloat-equal \
  -Wshadow -Wunsafe-loop-optimizations -Wlogical-op \
  -Wdisabled-optimization -Wconversion -Wunused-result
  
CFLAGS += -Wall -Wextra
LDLIBS += -lm
CPPFLAGS += -I include

OBJPATH=obj/
BINPATH=bin/

vpath %.h include/
vpath %.c src/

all: $(BINPATH)lavie

$(BINPATH)lavie : $(addprefix $(OBJPATH), main.o grille.o io.o jeu.o ) | $(BINPATH)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLTBS)

$(OBJPATH)main.o : main.c grille.h io.h jeu.h
$(OBJPATH)grille.o : grille.c grille.h
$(OBJPATH)io.o : io.c io.h grille.h
$(OBJPATH)jeu.o : jeu.c jeu.h

$(OBJPATH)%.o : %.c | $(OBJPATH)
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) -c $< 

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(BINPATH) :
	mkdir -p $(BINPATH)


check: $(BINPATH)lavie
	@./test/test_gol_execution.sh 

clean:
	@$(RM) -rf lavie *.o $(BINPATH) $(OBJPATH)
	@echo Clean!

dist:
	tar -c doc/ grilles/ include/ src/ test/ Doxyfile Makefile -f daiyuquan-GoL-ver2.5.tar.gz -z
