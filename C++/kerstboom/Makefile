
CC = c++
CFLAGS = -Wall

all: kerstboom

kerstboom: kerstboom.o
	$(CC) -o $@ kerstboom.o

clean:
	rm *.o
	rm `find . -perm +111 -type f`

.cpp.o:
	$(CC) -c $< $(CFLAGS)

