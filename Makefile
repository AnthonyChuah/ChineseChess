game: main.o board.o unit.o soldier.o cannon.o chariot.o horseman.o elephant.o mandarin.o general.o
	g++ main.o board.o unit.o soldier.o cannon.o chariot.o horseman.o elephant.o mandarin.o general.o -o game

main.o: main.cpp board.h unit.h soldier.h chariot.h horseman.h elephant.h mandarin.h general.h includes.h
	g++ -Wall -g -c main.cpp

board.o: board.cpp board.h unit.h soldier.h chariot.h horseman.h elephant.h mandarin.h general.h includes.h
	g++ -Wall -g -c board.cpp

unit.o: unit.cpp board.h unit.h includes.h
	g++ -Wall -g -c unit.cpp

soldier.o: soldier.cpp board.h unit.h soldier.h includes.h
	g++ -Wall -g -c soldier.cpp

cannon.o: cannon.cpp board.h unit.h cannon.h includes.h
	g++ -Wall -g -c cannon.cpp

chariot.o: chariot.cpp board.h unit.h chariot.h includes.h
	g++ -Wall -g -c chariot.cpp

horseman.o: horseman.cpp board.h unit.h horseman.h includes.h
	g++ -Wall -g -c horseman.cpp

elephant.o: elephant.cpp board.h unit.h elephant.h includes.h
	g++ -Wall -g -c elephant.cpp

mandarin.o: mandarin.cpp board.h unit.h mandarin.h includes.h
	g++ -Wall -g -c mandarin.cpp

general.o: general.cpp board.h unit.h general.h includes.h
	g++ -Wall -g -c general.cpp

clean:
	rm -f game *.o

.PHONY: clean
