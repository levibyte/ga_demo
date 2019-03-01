PROGNAME:=ga_algo
SRCS_CORE:=$(wildcard src/core/*.cpp) 
SRCS_RENDERER:=$(wildcard src/renderer/*.cpp) 

SRCS:=$(SRCS_CORE) $(SRCS_RENDERER)

INCS:=
FLAGS:=-Wno-narrowing -Wfatal-errors

LIBS+=./deps/linux/SDL2/libSDL2.a -L ./deps/linux/SDL2_image-2.0.3 -lSDL2_image -L ./deps/linux/SDL2_ttf/libSDL2_ttf.so -lSDL2_ttf -ldl -lrt -pthread 
INCLS+=$(INCS) -I ./deps/linux/SDL2/include -I ./deps/linux/SDL2_image-2.0.3/include -I ./deps/linux/SDL2_ttf/include
OUT=$(PROGNAME).bin

default:
	clear
	rm -f ./bin/$(OUT)  
	mkdir -p ./bin
	g++ -std=c++11 $(SRCS) $(FLAGS) $(INCLS) $(LIBS) -o ./bin/$(OUT)
