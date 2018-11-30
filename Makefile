FLAGS = -std=c++17 -Wall -Wextra

all: maas4.o maasothello4.o maasstapel4.o
	g++ -o Assignment4 maasstapel4.o maasothello4.o maas4.o $(FLAGS)

maasothello4.o: maasothello4.cc maasothello4.h
	g++ -c maasothello4.cc $(FLAGS)

maas4.o: maas4.cc maasothello4.h
	g++ -c maas4.cc $(FLAGS)

maasstapel4.o: maasstapel4.cc maasstapel4.h
	g++ -c maasstapel4.cc $(FLAGS)

clean:
	@rm -f maas4.o maasothello4.o maasstapel4.o Assignment4

run:
	@./Assignment4