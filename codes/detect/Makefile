.PHONY: all clean

GCC = gcc
SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))
PKGFLAGS = `pkg-config --libs --cflags opencv4`
LSTDC = -lstdc++

all: $(PROGS)

%: %.cpp
	$(GCC) -o $@ $< $(PKGFLAGS) $(LSTDC)
