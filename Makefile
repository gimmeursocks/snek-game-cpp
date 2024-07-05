CXX = g++
CXXFLAGS = -I src/include -L src/lib -O2 -Wall -Wextra -std=c++20
RFLAGS = -DNDEBUG -mwindows -m64

TARGET = main
RELEASE_TARGET = snek
RELEASE_DIR = release

SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))

LIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
STATIC_LIBS = -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic

.PHONY: release

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(OBJECTS) -o $(TARGET) $(CXXFLAGS) $(LIBS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling..."
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

release:
	@echo "Building static release..."
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(SOURCES) -o $(RELEASE_DIR)/$(RELEASE_TARGET) $(CXXFLAGS) $(RFLAGS) $(STATIC_LIBS) $(LIBS)

run:
	./$(TARGET)

rrun:
	./$(RELEASE_DIR)/$(RELEASE_TARGET)

rzip:
	@7z a -r -mx9 $(RELEASE_TARGET).7z $(RELEASE_DIR)

clean:
	@echo "Cleaning..."
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(OBJDIR)

rclean:
	@echo "Cleaning Release..."
	rm -f $(RELEASE_DIR)/$(RELEASE_TARGET) $(RELEASE_TARGET).7z

font:
	@xxd -i -n font_ttf src/assets/fonts/*.ttf > src/include/font_data.h