rm -rf build
mkdir -p build
cd build
cmake -DCMAKE_INSTALL_PREFIX=.. ..
cmake --build . 
cmake --install .
ctest -C Debug
echo "----------------------------"
../bin/sr5sim.exe