# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# The name of our final executable program
TARGET = Project

# All the .cpp source files
SRCS = main.cpp Student.cpp Course.cpp Enrollment.cpp

# All the .o object files, derived from the .cpp files
OBJS = $(SRCS:.cpp=.o)

# Default rule: build everything
all: $(TARGET)

# Rule to link all the object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)  # <<< THIS LINE MUST START WITH A TAB!

# Rule to compile a .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@         # <<< THIS LINE MUST START WITH A TAB!

# Rule to clean up the directory (remove compiled files)
clean:
	rm -f $(TARGET) $(OBJS)                  # <<< THIS LINE MUST START WITH A TAB!
