.PHONY: run

# TODO: Generalize this
PYVER=$(shell python -V 2>&1 | awk '{print $$2}' | cut -c 1-3)
CFLAGS=-I/usr/include/python$(PYVER) -g -shared -fPIC
LDFLAGS=-lpython$(PYVER) -lboost_python

lib/libpyembex.so: src/main.cpp lib/
	g++ $(CFLAGS) -o lib/libpyembex.so src/main.cpp $(LDFLAGS)

lib/:
	mkdir -p lib

clean:
	rm -f bin/main lib/libpyembex.so

run: lib/libpyembex.so script/main.py
	mkdir -p run
	cp lib/libpyembex.so run
	cp script/main.py run
	cp -r python/* run/
	cd run && python main.py

