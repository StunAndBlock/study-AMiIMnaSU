TARGET = __1
BUILDFOLDER = build
SOURCEFOLDER = src
CC = g++

CFLAGS = -std=c++17 \
         -O0 -D_FORTIFY_SOURCE=2 -fstack-protector 
#-Wall -Wextra -Werror -Wshadow 
LDFLAGS = 


MMAIN = 
MODULES = $(MMAIN) 

CPP = $(filter %.cpp,$(MODULES))
HEADERS = $(filter %.hpp %.h,$(MODULES))
OBJECTS = $(patsubst %.cpp,%.o,$(CPP))


.PHONY: all clean $(BUILDFOLDER) run

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