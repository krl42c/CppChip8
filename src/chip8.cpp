#include "chip8.h"
Chip8::Chip8(CPU cpu) {
  this->cpu = cpu;
  instructions.insert({0x1, [&cpu]() { cpu.cls(); }});
  instructions.insert({0x2, [&cpu]() { cpu.returnFromSubroutine(); }});
  instructions.insert({0x3, [&cpu]() { cpu.jumpToAddress(); }});
  instructions.insert({0x5, [&cpu]() { cpu.callSubroutine(); }});
}

Chip8::~Chip8() {}

void Chip8::run() {}

void Chip8::loadROM(std::string path) {}