CXX = g++                             
CXXFLAGS = -std=c++20 -Wall -Wextra
LDFLAGS = -pthread
LDLIBS = -lboost_system -lboost_thread

SRC = chatRoom.cpp 
OBJ = $(SRC:.cpp=.o)                   

chatApp: $(OBJ) 
	$(CXX) $(LDFLAGS) $(OBJ) $(LDLIBS) -o chatApp

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o chatApp