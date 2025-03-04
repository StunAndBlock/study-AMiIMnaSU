TARGET = matrix.out
BUILDFOLDER = build
SOURCEFOLDER =src
CC = g++

CFLAGS = -std=c++17 \
         -O0 -D_FORTIFY_SOURCE=2 -fstack-protector 
#-Wall -Wextra -Werror -Wshadow 
LDFLAGS = 


MMAIN =$(SOURCEFOLDER)/main.cpp
MDIRLOGIC =$(SOURCEFOLDER)/logic 
MDIRMATRIX =$(MDIRLOGIC)/matrix
MMATRIX =src/logic/matrix/matrix.cpp src/logic/matrix/matrix.hpp
MODULES =$(MMAIN) $(MMATRIX)

CPP =$(filter %.cpp,$(MODULES))
HEADERS =$(filter %.hpp %.h,$(MODULES))
OBJECTS =$(patsubst %.cpp,%.o,$(CPP))


.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS) | $(BUILDFOLDER)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(BUILDFOLDER)/$(TARGET)  

$(OBJECTS): %.o: %.cpp $(HEADERS)
	$(CC) -c $< -o $@

$(BUILDFOLDER):
	mkdir $(BUILDFOLDER) && touch $(BUILDFOLDER)/.gitkeep

clean:
	rm -f $(OBJECTS)
	rm -f $(BUILDFOLDER)/$(TARGET)

run: $(BUILDFOLDER)/$(TARGET)  
	clear
	$(BUILDFOLDER)/$(TARGET)