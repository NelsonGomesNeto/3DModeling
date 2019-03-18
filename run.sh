rm test
g++ *.cpp Textures/*.cpp -o test -lGL -lGLU -lglut -std=c++17 -O2 -lm
./test
