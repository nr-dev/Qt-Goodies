include Makefile.inc

CXXINCLUDES:= $(CXXINCLUDES)
CXXFLAGS:= $(CXXINCLUDES) $(CXXFLAGS) -fPIC
LDFLAGS:= $(LDFLAGS) -lQtGui
LD:=g++

.PHONY: clean all distclean

m%.cpp: %.h
	moc $(CXXINCLUDES) $< -o $@

all: test SettingsEditor libQRangeSliderDesigner.so

clean:
	rm -f *.o

test: test.o qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o
	$(LD) $(LDFLAGS) -o test test.o mqDoubleSlider.o qDoubleSlider.o qRangeSlider.o mqRangeSlider.o

SettingsEditor: settingsEditor.o
	$(LD) $(LDFLAGS) -o SettingsEditor settingsEditor.o

libQRangeSliderDesigner.so: qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o qRangeSliderDesigner.o mqRangeSliderDesigner.o
	$(LD) -shared $(LDFLAGS) -o libQRangeSliderDesigner.so qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o qRangeSliderDesigner.o mqRangeSliderDesigner.o

distclean: clean
	rm -f test *.so SettingsEditor