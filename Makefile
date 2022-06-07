program: src/main.o src/chip8.o src/cpu.o
	g++ -O2 -Wall -Wextra -Wpedantic -std=c++2a -o emu src/main.o src/chip8.o src/cpu.o
