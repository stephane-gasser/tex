SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	@echo PAS ENCORE COMPLET
#	g++ -o $@ $^

%.o: %.cpp
	g++ -c $<

#.PHONY: jumpout.cpp
