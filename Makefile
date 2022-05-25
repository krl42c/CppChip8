program: src/main.o src/chip8.o src/cpu.o
	g++ -o emu src/main.o src/chip8.o src/cpu.o
