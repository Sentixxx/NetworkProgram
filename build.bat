rmdir /s /q cmake-build-debug
mkdir cmake-build-debug
cd cmake-build-debug
cmake -G "MinGW Makefiles" ..
cmake --build .
