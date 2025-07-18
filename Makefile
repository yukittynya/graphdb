CC = clang
FLAGS = -Werror -flto -O3 -ffast-math

build/bin/graphdb: build/main.o build/hashtable.o | build/bin
	$(CC) $(FLAGS) $? -o $@ 

build/main.o: src/main.c | build
	$(CC) $(FLAGS) -c $? -o $@ 

build/hashtable.o: src/lib/hashtable/hashtable.c | build
	$(CC) $(FLAGS) -c $? -o $@ 
	
build: 
	mkdir -p build

build/bin: | build
	mkdir -p build/bin

.PHONY = clean
clean:
	rm -rvf build

.PHONY = run
run: clean build/bin/graphdb
	./build/bin/graphdb
