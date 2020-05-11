SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

myTeX: $(OBJ)
	g++ -std=c++17 -o $@ $^

%.o: %.cpp
	g++ -std=c++17 -c $<

clean:
	rm -rf *.o
