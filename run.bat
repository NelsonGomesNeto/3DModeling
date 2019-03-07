del test.exe
del test.o
g++ *.cpp -o test.exe -lglu32 -lopengl32 -lfreeglut -std=c++17 -O2 -lm
test.exe