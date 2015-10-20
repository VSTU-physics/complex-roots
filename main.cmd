g++ -Wall -std=c++11 -O2 -c integrals.cpp -o integrals.o
g++ -Wall -std=c++11 -O2 -c roots.cpp -o roots.o
g++ -Wall -std=c++11 -O2 -c rectangle.cpp -o rectangle.o
g++ -Wall -std=c++11 -O2 -c main.cpp -o main.o
g++  integrals.o  roots.o  rectangle.o  main.o -o complex.exe
complex.exe
pause
