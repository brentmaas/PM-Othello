all: maas4.o maasothello4.o
	g++ -o Assignment4 maasothello4.o maas4.o -std=c++17 -Wall -Wextra

maasothello4.o: maasothello4.cc maasothello4.h
	g++ -c maasothello4.cc -std=c++17 -Wall -Wextra

maas4.o: maas4.cc maasothello4.h
	g++ -c maas4.cc -std=c++17 -Wall -Wextra