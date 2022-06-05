#include "cpu.h"
#include "chip8.h"

int main() {
  Chip8 chip8;  
  chip8.loadROM("./PONG");

  return 0;
}