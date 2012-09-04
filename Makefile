APPS = orcaroot_snot_reader

include $(ORDIR)/buildTools/BasicAppMakefile

CXXFLAGS += -fPIC -g 
ORLIBS += -lzmq

CLANG := $(shell which clang)
ifneq ($(CLANG),)
    CXX = clang++
    CXXFLAGS += -arch x86_64 
else
    CXX = g++
    CXXFLAGS +=
endif

#CXXFLAGS +=  -fblocks -g -O3 -I. $(ORFLAGS) $(ROOTFLAGS)

#root_dict:
#	$(ROOTSYS)/bin/rootcint -f PackedEvent_dict.cc -c -p -I. -I$(ROOTSYS)/include -D_REENTRANT PackedEvent.hh LinkDef.hh 

#clean_root_dict:
#	@rm -f PackedEvent_dict.cc PackedEvent_dict.h

