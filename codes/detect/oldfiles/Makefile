.PHONY: all clean

CPP = g++
SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))
PKGFLAGS = `pkg-config --libs --cflags opencv4`

all: $(PROGS)

%: %.cpp
	$(CPP) -o $@ $< $(PKGFLAGS)
