run: database
	./database something or other

database: main.o song.o library.o helpers.o
	gcc main.o song.o library.o helpers.o -o database

main.o: main.c song.h library.h helpers.h
	gcc main.c -c

library.o: library.c library.h song.h helpers.h
	gcc library.c -c

song.o: song.c song.h
	gcc song.c -c

helpers.o: helpers.c helpers.h
	gcc helpers.c -c

clean: 
	rm database
	rm helpers.o
	rm song.o
	rm library.o
	rm main.o

val:
	valgrind ./database something or other