image: main
	rm image.ppm
	./main >> image.ppm

main: main.cpp
	g++ -g main.cpp -o main
