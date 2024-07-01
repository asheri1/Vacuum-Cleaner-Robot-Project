# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -pedantic

# Project name
TARGET = myrobot

# Source and header files
SRCS = FileParser.cpp House.cpp VacuumCleaner.cpp OutputHandler.cpp myrobot.cpp
HDRS = FileParser.h House.h VacuumCleaner.h Algorithm.h OutputHandler.h myrobot.h Coordinates.h

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default rule
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean
