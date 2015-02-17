TARGETS := orcaroot_snot_reader

ORFLAGS = -I$(ORDIR)/Util -I$(ORDIR)/Decoders -I$(ORDIR)/IO -I$(ORDIR)/Processors -I$(ORDIR)/Management
ORLIBS = -L$(ORDIR)/lib -lORUtil -lORDecoders -lORIO -lORProcessors -lORManagement
ROOTFLAGS = -I$(shell root-config --incdir)
ROOTLIBS = -L$(shell root-config --libdir) $(shell root-config --libs)

SOURCES = $(wildcard *.cc) $(wildcard Decoders/*.cc)
HEADERS = $(SOURCES:.cc=.hh)
OBJECTS = $(SOURCES:.cc=.o)

CXXFLAGS = -O3 -W -Wall -fPIC -g -I./Decoders $(CFLAGS)
ORLIBS += -lzmq

CLANG := $(shell which clang)
ifneq ($(CLANG),)
    CXX = clang++
    CXXFLAGS += -arch x86_64 
else
    CXX = g++
    CXXFLAGS +=
endif

.PHONY: clean all .depend

all: $(TARGETS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(ROOTFLAGS) $(ORFLAGS) -o $@ -c $<

$(TARGETS): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(ROOTFLAGS) $(ORFLAGS) -o $@ $(OBJECTS) $(LDFLAGS) $(ORLIBS) $(ROOTLIBS) 

.depend:
	@echo Generating dependecies
	$(CXX) -MM $(CXXFLAGS) $(ORFLAGS) $(ROOTFLAGS) *.cc Decoders/*.cc > $@

ifneq ($(MAKECMDGOALS), clean)
-include .depend
endif

clean:
	@echo "cleaning..."
	-$(RM) -f $(TARGETS) *.o Decoders/*.o *.dSYM .depend *~


