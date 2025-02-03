# Compiler
CXX = clang++
CXXFLAGS = -std=c++20

# THis paths are specifically for MacOs with apple silicon chips
# Raylib paths (installed via Homebrew)
INCLUDE = -I/opt/Homebrew/include
LIBS = -L/opt/Homebrew/lib -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

# Target
TARGET = ${FILE_NAME}
SRC = ${FILE_NAME}.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(INCLUDE) $(LIBS) && ./$(TARGET)

clean:
	rm -f $(TARGET)
