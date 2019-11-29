.PHONY: all clean

WARNFLAGS := -Wall -Wpedantic -Wextra -Waddress -Waggressive-loop-optimizations \
  -Wcast-qual -Wcast-align -Wmissing-declarations \
  -Wdouble-promotion -Wuninitialized -Winit-self \
  -Wstrict-aliasing -Wsuggest-attribute=const -Wtrampolines -Wfloat-equal \
  -Wshadow -Wunsafe-loop-optimizations -Wlogical-op \
  -Wdisabled-optimization -Wconversion -Wunused-result

ifeq (${MODE},TEXTE)
ROOT_DIR = text_mode/
CFLAGS += -Wall -Wextra 
LDLIBS += -lm
CPPFLAGS += -I include
IFLAGS =
else
ROOT_DIR = 
CFLAGS += -Wall -Wextra -g -O0
LDLIBS += -lcairo -lm -lX11
CPPFLAGS += -I include 
IFLAGS += -I/usr/include/cairo
endif

OBJPATH=$(ROOT_DIR)obj/
BINPATH=$(ROOT_DIR)bin/
LIBPATH=$(ROOT_DIR)lib/

vpath %.h $(ROOT_DIR)include/
vpath %.c $(ROOT_DIR)src/
vpath %.o $(ROOT_DIR)obj/

all: $(BINPATH)lavie

$(BINPATH)lavie : $(addprefix $(OBJPATH), main.o grille.o io.o jeu.o ) | $(BINPATH)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS) $(IFLAGS)
	ar -rcs libjeu.a $^
	mkdir -p $(LIBPATH)
	@cp libjeu.a $(LIBPATH)
	@rm libjeu.a

$(OBJPATH)main.o : main.c grille.h io.h jeu.h
$(OBJPATH)grille.o : grille.c grille.h
$(OBJPATH)io.o : io.c io.h grille.h
$(OBJPATH)jeu.o : jeu.c jeu.h

$(OBJPATH)%.o : %.c | $(OBJPATH)
	$(CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(IFLAGS) -c $< 


$(OBJPATH):
	mkdir -p $(OBJPATH)

$(BINPATH) :
	mkdir -p $(BINPATH)
	cp nice.png $(BINPATH)
	

check: $(BINPATH)lavie
	@./test/test_gol_execution.sh 

clean:
	@rm -rf lavie *.o $(LIBPATH) $(BINPATH) $(OBJPATH)
	@echo Clean!

dist:
	tar -c doc/ grilles/ include/ src/ lib/ Makefile test/ text_mode/ Doxyfile -f daiyuquan-GoL-ver2.5.tar.xz -z
