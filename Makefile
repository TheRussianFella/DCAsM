main: main.o parser.o lang_specs.o processor.o
	g++ -g -o main main.o parser.o lang_specs.o processor.o

main.o: main.cpp parser.h lang_specs.h
	g++ -g -c main.cpp

parser.o: parser.h parser.cpp
	g++ -g -c parser.cpp

lang_specs.o: lang_specs.h lang_specs.cpp
	g++ -g -c lang_specs.cpp

processor.o: processor.h processor.cpp lang_specs.cpp
	g++ -g -c processor.cpp
