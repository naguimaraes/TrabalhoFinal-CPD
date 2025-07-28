CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

SRCDIR = include
OBJDIR = obj

SOURCES = main.cpp $(SRCDIR)/hashtable.cpp $(SRCDIR)/player.cpp $(SRCDIR)/positions.cpp $(SRCDIR)/trie.cpp $(SRCDIR)/user.cpp

OBJECTS = $(SOURCES:.cpp=.o)

TARGET = main.exe

$(TARGET): $(SOURCES)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	@./$(TARGET)

.PHONY: clean run
