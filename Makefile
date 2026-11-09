# CineMatch build helper.
#
#   make build   compile the C++ recommendation engine
#   make run     build (if needed) and start the Flask app
#   make clean   remove build artifacts

ifeq ($(OS),Windows_NT)
    ENGINE := engine.exe
else
    ENGINE := engine
endif

CXX      ?= g++
CXXFLAGS ?= -O2 -std=c++17 -Wall -Wextra -pedantic
PYTHON   ?= python

.PHONY: all build run clean

all: build

build: $(ENGINE)

$(ENGINE): engine.cpp
	$(CXX) $(CXXFLAGS) engine.cpp -o $(ENGINE)

run: build
	$(PYTHON) app.py

clean:
	-$(RM) $(ENGINE)
