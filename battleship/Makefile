CC = g++
CFLAGS = -g -Wall
INCLUDES = -I.

SRC_DIR = src
BUILD_DIR = build

OBJS = $(BUILD_DIR)/main.o $(BUILD_DIR)/game.o $(BUILD_DIR)/exception.o $(BUILD_DIR)/base_player.o $(BUILD_DIR)/player.o $(BUILD_DIR)/ai.o $(BUILD_DIR)/ship.o $(BUILD_DIR)/square.o

TARGET = output

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(BUILD_DIR)/game.o $(BUILD_DIR)/exception.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/game.o: $(SRC_DIR)/game.cpp include/game.h $(BUILD_DIR)/base_player.o $(BUILD_DIR)/player.o $(BUILD_DIR)/ai.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/exception.o: $(SRC_DIR)/exception.cpp include/exception.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/base_player.o: $(SRC_DIR)/base_player.cpp include/base_player.h $(BUILD_DIR)/ship.o $(BUILD_DIR)/square.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/player.o: $(SRC_DIR)/player.cpp include/player.h $(BUILD_DIR)/base_player.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/ai.o: $(SRC_DIR)/ai.cpp include/ai.h $(BUILD_DIR)/base_player.o
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/ship.o: $(SRC_DIR)/ship.cpp include/ship.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BUILD_DIR)/square.o: $(SRC_DIR)/square.cpp include/square.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)
