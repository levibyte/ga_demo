OUT=GeneticAlgoDemo.bin
FLAGS=-DTEXT_RENDER
FLAGS=-DIMAGE_RENDER

SRCS=src/main.cpp src/logic.cpp

ifeq ($(USER),levons)
	LIBS=-L ~/levi/downloads/SDL2-2.0.5/build/.libs -lSDL2 -lfreetype -ldl -lrt
	INCLS=-I ~/levi/downloads/SDL2-2.0.5/include 
else
	LIBS=./deps/linux/SDL2/libSDL2.a ./deps/linux/SDL2_ttf/libSDL2_ttf.a -lfreetype -ldl -lrt
	INCLS=-I ./deps/linux/SDL2/include -I ./deps/linux/SDL2_ttf
endif

ifeq ($(OS),Windows_NT)
	OUT=GeneticAlgoDemo.exe
	#-enable-stdcall-fixup
	FLAGS=  -static-libstdc++ -DOS_WINDOWS -lmingw32 -static-libgcc 
	#LIBS=-L ./deps/win/SDL2/lib/win32 -lSDL2 ./deps/win/SDL2/lib/win32/SDL2.lib 
	LIBS=./deps/win/SDL2/lib/win32/SDL2.lib 
	INCLS=-I ./deps/win/SDL2/include
	#cp ./deps/win/SDL2/lib/win32/SDL2.dll ./bin
endif



default:
	clear
	rm -f ./bin/$(OUT) 
	g++ -Wfatal-errors -g $(FLAGS) $(INCLS) $(SRCS) $(LIBS) -o ./bin/$(OUT)