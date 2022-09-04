.PHONY: all clean

CFLAGS += -O0

all: main
clean:
	rm -r *.o *.so
main: main.c liblib.so
	gcc $(CFLAGS) $< -o main -Wl,-rpath=. -L. -llib

liblib.so: lib.o
	gcc $(CFLAGS) -shared $< -o liblib.so
lib.o: lib.c
	gcc $(CFLAGS) -c -fPIC $< 
