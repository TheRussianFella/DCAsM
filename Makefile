main: main.o parser.o lang_specs.o processor.o
	g++ -g -Wall -o main main.o parser.o lang_specs.o processor.o

main.o: main.cpp parser.h lang_specs.h
	g++ -g -Wall -c main.cpp

parser.o: parser.h parser.cpp
	g++ -g -Wall -c parser.cpp

lang_specs.o: lang_specs.h lang_specs.cpp
	g++ -g -Wall -c lang_specs.cpp

processor.o: processor.h processor.cpp lang_specs.cpp
	g++ -g -Wall -c processor.cpp
