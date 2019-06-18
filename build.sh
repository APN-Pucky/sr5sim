#rm -rf build
#rm -rf bin
#rm -rf lib
mkdir -p build
cd build
cmake ..
cmake --build . 
ctest -C Debug
cd ../bin

if [ -d "Debug" ]; then
	./Debug/sr5test.exe #windows
	./Debug/sr5sim.exe #windows
else
	if [ -d "Release" ]; then
		./Release/sr5test.exe #windows
		./Release/sr5sim.exe #windows
	else
		./sr5test #linux
		./sr5sim #linux
	fi
fi
