# change application name here (executable output name)
TARGET=dod

# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall

PTHREAD=-pthread

CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=main.o engine.o window.o 

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)
    
main.o: src/main.c 
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB)

window.o: src/window.c src/window.h 
	$(CC) -c $(CCFLAGS) src/window.c $(GTKLIB)

engine.o: src/engine.c src/engine.h 
	$(CC) -c $(CCFLAGS) src/engine.c $(GTKLIB)
    
clean:
	rm -f *.o $(TARGET)
