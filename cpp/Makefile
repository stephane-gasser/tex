SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

myTeX: $(OBJ)
	g++ -o $@ $^

%.o: %.cpp
	g++ -c $<
