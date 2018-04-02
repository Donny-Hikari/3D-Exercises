#!gmake

RM        ?=   rm -f
SRC       ?=   src/3DGL.cpp
BIN       ?=   bin/3DGL
TEST      ?=   test/testc.cpp
CFLAG     ?=   -lGL -lGLU -lglut -lGLEW -std=c++14

build:
	$(CXX) $(SRC) -o $(BIN) $(CFLAG)

run:
	cd $(dir $(BIN)) && pwd && ./$(notdir $(BIN))

test:
	$(CXX) $(TEST) -o $(BIN) $(CFLAG)

.PHONY: clean

clean:
	$(RM) $(BIN)
