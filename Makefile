SRC=src
INC=include
CXX=g++
CFLAGS=-O -std=c++11 -Wall -Wno-unused-result -I$(INC)

all: lonestar

lonestar: $(SRC)/main.cpp $(INC)/mongoose/mongoose.c
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	-rm -rf lonestar
