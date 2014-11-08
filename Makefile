CC=gcc

CFLAGS=-c -O3 -std=c99

EXECUTABLE_FLAGS=-o
SHARED_LIB_FLAGS=-Wl,--version-script=libgeohash.version -fPIC -shared -o

EXECUTABLE_NAME=geohash
SHARED_LIB_NAME=lib$(EXECUTABLE_NAME).so

# build rules

exe: main.o geohash.o
	$(CC) main.o geohash.o $(EXECUTABLE_FLAGS) $(EXECUTABLE_NAME)

shared: geohash.o
	$(CC) geohash.o $(SHARED_LIB_FLAGS) $(SHARED_LIB_NAME)

static: geohash.o
	ar rcs libgeohash.a geohash.o

# object compilation

main.o: main.c
	$(CC) $(CFLAGS) main.c

geohash.o:  geohash.c
	$(CC) $(CFLAGS) geohash.c

# clean rule

clean:
	rm -rf *.o $(EXECUTABLE_NAME) $(SHARED_LIB_NAME)
