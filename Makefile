PACKAGEDIR:=$(HOME)/packages

CXXFLAGS:= -I$(PACKAGEDIR)/include
LDFLAGS:= -L$(PACKAGEDIR)/lib -lQtGui
LD:=g++

.PHONY: clean all

all: test

clean:
	rm -f *.o

test: test.o qDoubleSlider.o
	$(LD) $(LDFLAGS) -o test test.o qDoubleSlider.o
