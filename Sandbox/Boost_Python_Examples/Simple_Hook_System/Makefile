
# TODO: Generalize this
PYVER=$(shell python -V 2>&1 | awk '{print $$2}' | cut -c 1-3)
CFLAGS=-I/usr/include/python$(PYVER) -g
LDFLAGS=-lpython$(PYVER) -lboost_python

bin/main: src/main.cpp bin/
	g++ $(CFLAGS) -o bin/main src/main.cpp $(LDFLAGS)

bin/:
	mkdir -p bin

clean:
	rm -f bin/main

run: bin/main config/conf.py
	./bin/main ./config/conf.py
