include ../Makefile.inc

CXXINCLUDES:= $(CXXINCLUDES)
CXXFLAGS:= $(CXXINCLUDES) $(CXXFLAGS) -fPIC
LDFLAGS:= $(LDFLAGS) -lQtGui
LD:=g++

.PHONY: clean all distclean

m%.cpp: %.h
	moc $(CXXINCLUDES) $< -o $@

all: libQRangeSliderDesigner.so libQDoubleSliderDesigner.so

libQRangeSliderDesigner.so: ../qRangeSlider.o ../mqRangeSlider.o qRangeSliderDesigner.o mqRangeSliderDesigner.o
	$(LD) -shared $(LDFLAGS) -o $@ $^

libQDoubleSliderDesigner.so: ../qDoubleRangeSlider.o ../mqDoubleRangeSlider.o ../qRangeSlider.o ../mqRangeSlider.o qDoubleRangeSliderDesigner.o mqDoubleRangeSliderDesigner.o
	$(LD) -shared $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o

distclean: clean
	rm -f test *.so SettingsEditor