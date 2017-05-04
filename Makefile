# THE INVINCIBLE MAKEFILE
# v2.2
# by Eugenio Bargiacchi - 2013

SHELL=/bin/bash
CXX=/usr/bin/g++
WCXX=~/Projects/MinGW/bin/i686-w64-mingw32-g++

EXECUTABLE=eatmeat_andbuild
WINEXECUTABLE=ruletheskies.exe
                                                                                    
CXXFLAGS=-std=c++11 -g -Wall -pedantic -I./include/ -I./src/ -I/usr/include/lua5.2/ 
LDFLAGS=-L./lib/Diluculum/ -L./lib/SFML/ -Wl,-rpath -Wl,./lib/SFML/ -Wl,-rpath -Wl,./lib/Diluculum/ -Wl,-rpath -Wl,./lib/others -g

LIBRARIES=-lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system -ldiluculum -llua5.2
WINLIBRARIES=#-ljson_mingw_libmt -lbprinter_mingw

WINDEFINES=-DWINVER=0x0400 -D__WIN95__ -D__GNUWIN32__ -DSTRICT -DHAVE_W32API_H -D__WXMSW__ -D__WINDOWS__
WINLDFLAGS=-L./libs/ -I./ # $(shell find /usr/include/ -maxdepth 1 -type d | sed 's/^/-I/g') #-L/usr/lib/ -I/usr/include/
WINBASELIBRARIES=-lodbc32 -lwsock32 -lwinspool -lwinmm -lshell32 -lcomctl32 -lctl3d32 -lodbc32 -ladvapi32 -lodbc32 -lwsock32 -lopengl32 -lglu32 -lole32 -loleaut32 -luuid
WINSTATIC=-static-libstdc++ -static-libgcc
WINOPTIONS=--verbose

SOURCEDIR=src

SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')
# HEADERS := $(shell find $(SOURCEDIR) -name '*.h')

OBJECTSFOLDER=objects
OBJECTS=$(addprefix $(OBJECTSFOLDER)/, $(SOURCES:.cpp=.o))

WINOBJECTSFOLDER=winobjects
WINOBJECTS=$(addprefix $(WINOBJECTSFOLDER)/, $(SOURCES:.cpp=.o))

DEPFOLDER=dependencies
df=$(DEPFOLDER)/$(basename $<)

odf=$(OBJECTSFOLDER)/$(basename $<)
wodf=$(WINOBJECTSFOLDER)/$(basename $<)

EXEFOLDER=bin
WINEXEFOLDER=winbin

.PHONY : all
# Brute force compiling statement for simple compilation and no .o residual files
all: folders $(EXEFOLDER)/$(EXECUTABLE)

.PHONY: win
win: winfolders $(WINEXEFOLDER)/$(WINEXECUTABLE)
	
# Final linking of the executable
$(EXEFOLDER)/$(EXECUTABLE): $(OBJECTS) 
	$(CXX) $(shell find $(OBJECTSFOLDER) -name *.o) $(LIBRARIES) -o $@ $(LDFLAGS)

$(WINEXEFOLDER)/$(WINEXECUTABLE) : $(WINOBJECTS)
	$(WCXX) $(WINDEFINES) $(WINSTATIC) $(shell find $(WINOBJECTSFOLDER) -name *.o) -o $@ $(WINOPTIONS) $(WINLDFLAGS) $(WINLIBRARIES) $(WINBASELIBRARIES) 

# Creation of object files
# ( Actual compilation is only last instruction, the rest is creating dependency header rules )
$(OBJECTSFOLDER)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(df))
	@$(CXX) -MMD -c $(CXXFLAGS) -o $@ $<
	@cp $(odf).d $(df).P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			-e '/^$$/ d' -e 's/$$/ :/' < $(odf).d >> $(df).P; \
	rm -f $(odf).d
	$(CXX) -c $(CXXFLAGS) $< -o $@

$(WINOBJECTSFOLDER)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@mkdir -p $(dir $(df))
	@$(WCXX) -MMD -c $(CXXFLAGS) -o $@ $<
	@cp $(wodf).d $(df).P; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
			-e '/^$$/ d' -e 's/$$/ :/' < $(wodf).d >> $(df).P; \
	rm -f $(wodf).d
	$(WCXX) -c $(CXXFLAGS) $< -o $@

-include $(shell find $(DEPFOLDER) -name '*.P')

# Creation of folders
.PHONY : folders
folders: $(OBJECTSFOLDER) $(DEPFOLDER) $(EXEFOLDER)

.PHONY : winfolders
winfolders: $(WINOBJECTSFOLDER) $(DEPFOLDER) $(WINEXEFOLDER)

$(DEPFOLDER):
	mkdir $@
$(OBJECTSFOLDER):
	mkdir $@
$(EXEFOLDER):
	mkdir $@
$(WINOBJECTSFOLDER):
	mkdir $@
$(WINEXEFOLDER):
	mkdir $@


# Cleanup of object files
# ( .PHONY is to avoid calling the rule in case a file named clean exists )
.PHONY : clean
clean:
	rm -rf $(OBJECTSFOLDER)
	rm -rf $(WINOBJECTSFOLDER)
	rm -rf $(DEPFOLDER) 
