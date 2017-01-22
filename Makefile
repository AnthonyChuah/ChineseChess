COMPILER_FLAGS = -Wall -g -c

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

game: main.o board.o unit.o soldier.o cannon.o chariot.o horseman.o elephant.o mandarin.o general.o
	g++ main.o board.o unit.o soldier.o cannon.o chariot.o horseman.o elephant.o mandarin.o general.o $(LINKER_FLAGS) -o game

main.o: main.cpp board.h unit.h soldier.h chariot.h horseman.h elephant.h mandarin.h general.h includes.h
	g++ $(COMPILER_FLAGS) main.cpp

board.o: board.cpp board.h unit.h soldier.h chariot.h horseman.h elephant.h mandarin.h general.h includes.h
	g++ $(COMPILER_FLAGS) board.cpp

unit.o: unit.cpp board.h unit.h includes.h
	g++ $(COMPILER_FLAGS) unit.cpp

soldier.o: soldier.cpp board.h unit.h soldier.h includes.h
	g++ $(COMPILER_FLAGS) soldier.cpp

cannon.o: cannon.cpp board.h unit.h cannon.h includes.h
	g++ $(COMPILER_FLAGS) cannon.cpp

chariot.o: chariot.cpp board.h unit.h chariot.h includes.h
	g++ $(COMPILER_FLAGS) chariot.cpp

horseman.o: horseman.cpp board.h unit.h horseman.h includes.h
	g++ $(COMPILER_FLAGS) horseman.cpp

elephant.o: elephant.cpp board.h unit.h elephant.h includes.h
	g++ $(COMPILER_FLAGS) elephant.cpp

mandarin.o: mandarin.cpp board.h unit.h mandarin.h includes.h
	g++ $(COMPILER_FLAGS) mandarin.cpp

general.o: general.cpp board.h unit.h general.h includes.h
	g++ $(COMPILER_FLAGS) general.cpp

clean:
	rm -f game *.o

.PHONY: clean
