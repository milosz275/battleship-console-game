output: build/main.o
	g++ -g -Wall -o output build/main.o build/Game.o build/Exception.o build/BasePlayer.o build/Player.o build/Ai.o build/Ship.o build/Square.o

build/main.o: src/main.cpp build/Game.o build/Exception.o
	g++ -g -Wall -c src/main.cpp -o build/main.o -I.

build/Game.o: src/Game.cpp include/Game.h build/BasePlayer.o build/Player.o build/Ai.o
	g++ -g -Wall -c src/Game.cpp -I. -o build/Game.o

build/Exception.o: src/Exception.cpp include/Exception.h
	g++ -g -Wall -c src/Exception.cpp -I. -o build/Exception.o

build/BasePlayer.o: src/BasePlayer.cpp include/BasePlayer.h build/Ship.o build/Square.o
	g++ -g -Wall -c src/BasePlayer.cpp -I. -o build/BasePlayer.o

build/Player.o: src/Player.cpp include/Player.h build/BasePlayer.o
	g++ -g -Wall -c src/Player.cpp -I. -o build/Player.o

build/Ai.o: src/Ai.cpp include/Ai.h build/BasePlayer.o
	g++ -g -Wall -c src/Ai.cpp -I. -o build/Ai.o

build/Ship.o: src/Ship.cpp include/Ship.h
	g++ -g -Wall -c src/Ship.cpp -I. -o build/Ship.o

build/Square.o: src/Square.cpp include/Square.h
	g++ -g -Wall -c src/Square.cpp -I. -o build/Square.o

clean:
	rm build/*.o output
