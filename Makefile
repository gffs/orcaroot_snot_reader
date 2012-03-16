APPS = orcaroot_snot_reader

include $(ORDIR)/buildTools/BasicAppMakefile

#CXXFLAGS +=  -fblocks -g -O3 -arch x86_64 -I. $(ORFLAGS) $(ROOTFLAGS)
#CXX = clang++
#ORLIBS += -lavalanche

root_dict:
	$(ROOTSYS)/bin/rootcint -f PackedEvent_dict.cc -c -p -I. -I$(ROOTSYS)/include -D_REENTRANT PackedEvent.hh LinkDef.hh 

clean_root_dict:
	@rm -f PackedEvent_dict.cc PackedEvent_dict.h

