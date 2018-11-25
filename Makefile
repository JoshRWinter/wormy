build:
	mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release ..

clean:
	rm -rf build
