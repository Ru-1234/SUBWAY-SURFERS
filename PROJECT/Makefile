CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SOURCES = Player.cpp Obstacle.cpp PowerUp.cpp Coin.cpp ScoreManager.cpp TrackManager.cpp GameEngine.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = PROJECT

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) highscore.txt

run: all
	./$(EXECUTABLE)

.PHONY: all clean run

