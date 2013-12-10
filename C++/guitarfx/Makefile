# Makefile

CC = c++
CFLAGS = -Wall

OBJECTS = guitarfx.o amplifier.o

all: guitarfx

guitarfx: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
	rm `find . -perm +111 -type f`

