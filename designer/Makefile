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

libQDoubleSliderDesigner.so: ../qDoubleSlider.o ../mqDoubleSlider.o ../qRangeSlider.o ../mqRangeSlider.o qDoubleSliderDesigner.o mqDoubleSliderDesigner.o
	$(LD) -shared $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o

distclean: clean
	rm -f test *.so SettingsEditor