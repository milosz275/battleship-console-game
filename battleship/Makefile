output: build/main.o
	g++ -g -Wall -o output build/main.o build/game.o build/exception.o build/base_player.o build/player.o build/ai.o build/ship.o build/square.o

build/main.o: src/main.cpp build/game.o build/exception.o
	g++ -g -Wall -c src/main.cpp -o build/main.o -I.

build/game.o: src/game.cpp include/game.h build/base_player.o build/player.o build/ai.o
	g++ -g -Wall -c src/game.cpp -I. -o build/game.o

build/exception.o: src/exception.cpp include/exception.h
	g++ -g -Wall -c src/exception.cpp -I. -o build/exception.o

build/base_player.o: src/base_player.cpp include/base_player.h build/ship.o build/square.o
	g++ -g -Wall -c src/base_player.cpp -I. -o build/base_player.o

build/player.o: src/player.cpp include/player.h build/base_player.o
	g++ -g -Wall -c src/player.cpp -I. -o build/player.o

build/ai.o: src/ai.cpp include/ai.h build/base_player.o
	g++ -g -Wall -c src/ai.cpp -I. -o build/ai.o

build/ship.o: src/ship.cpp include/ship.h
	g++ -g -Wall -c src/ship.cpp -I. -o build/ship.o

build/square.o: src/square.cpp include/square.h
	g++ -g -Wall -c src/square.cpp -I. -o build/square.o

clean:
	rm build/*.o output
