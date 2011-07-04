PACKAGEDIR:=$(HOME)/packages

CXXFLAGS:= -I$(PACKAGEDIR)/include -I./qt-everywhere-opensource-src-4.6.3/include/QtGui -I./qt-everywhere-opensource-src-4.6.3/include/QtCore -g2
LDFLAGS:= -Wl,-rpath=$(PACKAGEDIR)/lib -L$(PACKAGEDIR)/lib -lQtGui 
LD:=g++

.PHONY: clean all

m%.cpp: %.h
	moc $< -o $@

all: test

clean:
	rm -f *.o

test: test.o qDoubleSlider.o mqDoubleSlider.o #qabstractslider2.o mqabstractslider2.o
	$(LD) $(LDFLAGS) -o test test.o mqDoubleSlider.o qDoubleSlider.o

