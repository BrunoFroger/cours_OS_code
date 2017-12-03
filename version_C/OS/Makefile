OS:bin/os

bin/os: obj/scheduler.o\
	obj/monitor.o\
	obj/gestTaches.o\
	obj/gestMemoire.o\
	obj/shell.o\
	obj/lanceTache.o\
	obj/commandeInterne.o\
	obj/os.o
	gcc obj/*.o -o $@

obj/os.o: src/os.c
	gcc -c src/os.c -o $@ 

obj/gestMemoire.o: src/gestMemoire.c\
	inc/mem.h
	gcc -c src/gestMemoire.c -o $@

obj/commandeInterne.o: src/commandeInterne.c\
	inc/tache.h
	gcc -c src/commandeInterne.c -o $@

obj/lanceTache.o: src/lanceTache.c\
	inc/tache.h
	gcc -c src/lanceTache.c -o $@

obj/shell.o: src/shell.c\
	inc/tache.h
	gcc -c src/shell.c -o $@

obj/gestTaches.o: src/gestTaches.c\
	inc/tache.h
	gcc -c src/gestTaches.c -o $@ 

obj/scheduler.o: src/scheduler.c\
	inc/tache.h
	gcc -c src/scheduler.c -o $@ 

obj/monitor.o: src/monitor.c\
	inc/tache.h
	gcc -c src/monitor.c -o $@ 

clean:
	rm -f obj/*.o *.bin
