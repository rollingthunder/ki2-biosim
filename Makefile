CC=clang++
# ARCH=-arch i386 
ARCH=
CFLAGS=-std=c++11 -stdlib=libc++ -c -Wall $(ARCH)
WXCPPFLAGS=$(shell wx-config --cppflags) -DHAVE_TYPE_TRAITS
LDFLAGS=-stdlib=libc++ $(ARCH)
WXLDFLAGS=$(shell wx-config std --libs)
SOURCES=Source/biosim_app.cpp Source/biosim_gui.cpp Source/biosim_gui_impl.cpp Source/creature.cpp Source/image.cpp Source/model.cpp Source/sim_area_widget.cpp Source/world_map.cpp 
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sim

all: $(SOURCES) $(EXECUTABLE) mat
	mv $(EXECUTABLE) Build
clean : 
	rm -f $(EXECUTABLE) $(OBJECTS)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(WXLDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(WXCPPFLAGS) $< -o $@

mat :
	mkdir -p ./Build
	cp -R ./Material/* ./Build

