include Makefile.inc

CXXINCLUDES:= $(CXXINCLUDES)
CXXFLAGS:= $(CXXINCLUDES) $(CXXFLAGS) -fPIC
LDFLAGS:= $(LDFLAGS) -lQtGui
LD:=g++

.PHONY: clean all distclean

m%.cpp: %.h
	moc $(CXXINCLUDES) $< -o $@

all: test SettingsEditor libQRangeSliderDesigner.so libQDoubleSliderDesigner.so

clean:
	rm -f *.o

test: test.o qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o
	$(LD) $(LDFLAGS) -o $@ $^

SettingsEditor: settingsEditor.o
	$(LD) $(LDFLAGS) -o $@ $^

libQRangeSliderDesigner.so: qRangeSlider.o mqRangeSlider.o qRangeSliderDesigner.o mqRangeSliderDesigner.o
	$(LD) -shared $(LDFLAGS) -o $@ $^

libQDoubleSliderDesigner.so: qDoubleSlider.o mqDoubleSlider.o qRangeSlider.o mqRangeSlider.o qDoubleSliderDesigner.o mqDoubleSliderDesigner.o
	$(LD) -shared $(LDFLAGS) -o $@ $^

distclean: clean
	rm -f test *.so SettingsEditor