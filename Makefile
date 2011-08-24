include Makefile.inc

CXXINCLUDES:= $(CXXINCLUDES)
CXXFLAGS:= $(CXXINCLUDES) $(CXXFLAGS) -fPIC
LDFLAGS:= $(LDFLAGS) -lQtGui
LD:=g++

.PHONY: clean all designer distclean

m%.cpp: %.h
	moc $(CXXINCLUDES) $< -o $@

all: test SettingsEditor designer

test: test.o qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o
	$(LD) $(LDFLAGS) -o $@ $^

SettingsEditor: settingsEditor.o
	$(LD) $(LDFLAGS) -o $@ $^

designer: qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o
	cd designer; $(MAKE) 

clean:
	rm -f *.o
	cd designer; $(MAKE) clean

distclean: clean
	rm -f test *.so SettingsEditor
	cd designer; $(MAKE) distclean
