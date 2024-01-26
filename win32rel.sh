cmake -B ./build/win32 -S . -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/x86_64-w64-mingw32-g++-win32 -DCMAKE_C_COMPILER=/usr/bin/x86_64-w64-mingw32-gcc-win32
cd ./build/win32
make CXX=/usr/bin/x86_64-w64-mingw32-g++-win32 CC=/usr/bin/x86_64-w64-mingw32-gcc-win32
cd ../..