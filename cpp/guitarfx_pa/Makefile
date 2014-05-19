# Makefile

CC = c++
CFLAGS  = -Wall
LDFLAGS = -lportaudio

OBJECTS = guitarfx.o audio_io.o audiofx.o amplifier.o tremelo.o bitcrusher.o chorus.o overdrive.o dynamiccompressor.o

all: guitarfx

guitarfx: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o
	rm `find . -perm +111 -type f`

touch:
	touch ./*.cpp
	touch ./*.h

