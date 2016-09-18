CFLAGS = -W -Wall -pedantic
OPTIMISATION = -fomit-frame-pointer
EXE = Sudon

GTK = `pkg-config --cflags --libs gtk+-2.0`
MATHS = -lm


Sudon: main.o init.o core.o affichage.o gestion.o callbacks.o signaux.o gen_grille.o operations_tableaux.o
	gcc $(OPTIMISATION) $^ $(GTK) $(MATHS) -o $(EXE) 

%.o : %.c main.h
	gcc $(OPTIMISATION) $(GTK) -c $<

clean:
	rm -f *.o
	
clean_all:
	rm -f *.o $(EXE)
	
archive:
	tar cfvz Sudon.tar.gz *.c *.h *.data makefile interface.glade logo.png

exec:
	make
	make clean
	./Sudon

