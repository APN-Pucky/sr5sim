rm -rf build
rm -rf bin
rm -rf lib
mkdir -p build
cd build
cmake ..
cmake --build .
cmake --install .
ctest -C Debug
