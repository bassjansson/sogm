
CC      = c++
CFLAGS  = -Wall
LDFLAGS =

OBJECTS = Main.o Filter.o Complex.o

all: PieterFilter

PieterFilter: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
	rm `find . -perm +111 -type f`

touch:
	touch ./*.cpp
	touch ./*.h

