CC=gcc
LIBS=-lm -ltcod -ltcodxx
DEPS=src/*.h

linux64: $(DEPS) src/*.c
	$(CC) src/*.c -o bin64/main -Iinclude -Llib64 $(LIBS) -Wl,-rpath=. -Wall

linux32: $(DEPS) src/*.c
	$(CC) src/*.c -o bin32/main -Iinclude -Llib32 $(LIBS) -Wl,-rpath=. -Wall
