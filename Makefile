all: main.exe

main.exe: main.o plot.o color.o matrix.o matrixf.o util.o image.o transform.o
	g++ -g -std=c++11 *.o -o main.exe -lglfw3 -lopengl32 -lgdi32 -lglad -ltiff

main.o: main.cpp plot.h
	g++ -g -std=c++11 -c main.cpp

plot.o: plot.cpp plot.h
	g++ -g  -std=c++11 -c plot.cpp

color.o: color.cpp color.h
	g++ -g  -std=c++11 -c color.cpp

matrix.o: matrix.cpp matrix.h
	g++ -g  -std=c++11 -c matrix.cpp

matrixf.o: matrixf.cpp matrix.h
	g++ -g  -std=c++11 -c matrixf.cpp

transform.o: transform.cpp transform.h
	g++ -g  -std=c++11 -c transform.cpp

image.o: image.cpp image.h
	g++ -g  -std=c++11 -c image.cpp

util.o: util.cpp util.h
	g++ -g  -std=c++11 -c util.cpp

run: main.exe
	main.exe

clean:
	del *.o

SublimeGDB: main.exe
	gdb --interpreter=mi --args main.exe