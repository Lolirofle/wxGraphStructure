## Dependencies using apt-get ##

	apt-get install libwxbase3.0-0 libwxbase3.0-dev libwxgtk3.0-0 libwxgtk3.0-dev wx3.0-examples wx3.0-headers wx-common

## Build using CMake ##
Preparing:

	apt-get install cmake

Compiling:

	mkdir build
	cd build
	cmake -DCMAKE_BUILD_TYPE=Release ..
	make

## Build (Cross-compiling to Windows) using MXE and CMake ##
Preparing:

	git clone https://github.com/mxe/mxe.git mxe
	cd mxe
	make
	make wxwidgets

Compiling:

	mkdir build/windows
	cd build/windows
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=<INSERT PATH TO MXE ROOT FOLDER>/usr/i686-pc-mingw32.static/share/cmake/mxe-conf.cmake -DC_LANG_VERSION=gnu11 -DCXX_LANG_VERSION=gnu++11 ../..
	make
