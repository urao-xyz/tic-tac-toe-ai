CXX=g++
CXXFLAGS=-std=c++17 -I.
LDFLAGS=-lsqlite3

SRC=main.cpp tictactoe.cpp ai.cpp scoreboard.cpp
TEST_SRC=tests/test_tictactoe.cpp tests/test_ai.cpp tests/test_scoreboard.cpp

all: tictactoe

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tictactoe: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@ $(LDFLAGS)

test: tictactoe-tests

TTESTS=tests/test_tictactoe tests/test_ai tests/test_scoreboard

tictactoe-tests: $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) tests/test_tictactoe.cpp tictactoe.cpp -o tests/test_tictactoe
	$(CXX) $(CXXFLAGS) tests/test_ai.cpp tictactoe.cpp ai.cpp -o tests/test_ai
	$(CXX) $(CXXFLAGS) tests/test_scoreboard.cpp scoreboard.cpp -o tests/test_scoreboard $(LDFLAGS)

run-tests: tictactoe-tests
	for t in $(TTESTS); do $$t; done

clean:
	rm -f tictactoe $(TTESTS) *.o

.PHONY: all test clean run-tests tictactoe-tests
