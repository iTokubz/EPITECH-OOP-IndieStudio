Indie Studio (Bomberman)

To compile in the build folder and generate binary at the root:

cmake -B build && cmake --build build


To compile all in the root but the useless files will be at the root:

cmake . && make
