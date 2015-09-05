SRC=src
INC=include
CXX=g++
CFLAGS=-O -std=c++11 -Wall -Wno-unused-result -I$(INC)

all: database

database: $(SRC)/database.cpp $(INC)/mongoose/mongoose.c
	$(CXX) $(CFLAGS) $^ -o $@

clean:
	-rm -rf database
