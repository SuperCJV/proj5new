CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

TARGET = proj5

SOURCES = proj5.cpp passserver.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET) -lcrypt

clean:
	rm -f $(TARGET)
