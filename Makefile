run: database
	./database something or other

database: main.o song.o library.o
	gcc main.o song.o library.o -o database

main.o: main.c song.h library.h
	gcc main.c -c

library.o: library.c library.h song.h
	gcc library.c -c

song.o: song.c song.h
	gcc song.c -c

clean: 
	rm database
	rm song.o
	rm library.o
	rm main.o

val:
	valgrind ./database something or other