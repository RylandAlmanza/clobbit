CC=gcc
LIBS=-lm -lncurses
DEPS = entity.h part.h frame.h orientation.h cell.h point.h

main: $(DEPS) main.c entity.c part.c frame.c orientation.c
	$(CC) main.c entity.c part.c frame.c orientation.c -o main $(LIBS)
