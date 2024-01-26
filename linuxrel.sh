cmake -B ./build/linux -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/g++ -DCMAKE_C_COMPILER=/usr/bin/gcc
cd ./build/linux
make CXX=/usr/bin/g++ CC=/usr/bin/gcc
cd ../..