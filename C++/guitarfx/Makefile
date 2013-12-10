
CC = c++
CFLAGS = -Wall

all: guitarfx

guitarfx: guitarfx.o
	$(CC) -o $@ guitarfx.o

guitarfx.o:

clean:
	rm guitarfx *.o

.cpp.o:
	$(CC) -c $< $(CFLAGS)

