#Place this makefile in the same directory as your
#all .cpp and .h files
#at the command prompt
#make
#./matrix  (or whatever you call the TARGET)

SOURCES = main.cpp BShip/BShipGame.cpp BShip/BShipGrid.cpp BShip/BShip.cpp BShip/BShipController.cpp BShip/UserController.cpp BShip/CPUController.cpp

######Change from matrix to (for example hw1) .#######
TARGET = battleship_michal

#-------Do Not Change below this line-------------

#Compile with g++
CC = g++

#use -g for gnu debugger and -std= for c++11 compiling
CXXFLAGS = -g -std=c++11

OBJS:=${SOURCES:.cpp=.o}

######Do NOT change this...Tabs Matter!#########
$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

#slightly modified by michal

.cpp.o:
	$(CC) -c $(CXXFLAGS) $< -o $@




#In order to get rid of all .o files create, at the command prompt
#make clean

clean:
	rm -f $(OBJS) $(TARGET) core

