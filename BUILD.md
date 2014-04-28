## Dependencies using apt-get ##

	apt-get install libwxbase3.0-0 libwxbase3.0-dev libwxgtk3.0-0 libwxgtk3.0-dev wx3.0-examples wx3.0-headers wx-common

## Build using CMake##

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make
