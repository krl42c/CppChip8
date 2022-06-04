#include "chip8.h"

Chip8::Chip8() {
  //this->cpu = cpu;
  CPU cpu;
  instructions.insert({0x1, [&cpu]() { cpu.cls(); }});
  instructions.insert({0x2, [&cpu]() { cpu.returnFromSubroutine(); }});
  instructions.insert({0x3, [&cpu]() { cpu.jumpToAddress(); }});
  instructions.insert({0x5, [&cpu]() { cpu.callSubroutine(); }});
  instructions.insert({0x6, [&cpu]() { cpu.skipNextEqualVxKk(); }});
  instructions.insert({0x7, [&cpu]() { cpu.skipNextNotEqualVxKk(); }});
  instructions.insert({0x8, [&cpu]() { cpu.setVxKk(); }});
  instructions.insert({0x9, [&cpu]() { cpu.setVxVxPlusKk(); }});
  instructions.insert({0xa, [&cpu]() { cpu.setVxVy(); }});
  instructions.insert({0xb, [&cpu]() { cpu.logicalOR_VX(); }});
  instructions.insert({0xc, [&cpu]() { cpu.logicalAND_VX(); }});
  instructions.insert({0xd, [&cpu]() { cpu.logicalXOR_VX(); }});
}

Chip8::~Chip8() {}

void Chip8::run() {
  // TODO: read x bytes from cpu.memory, decode opcode, and call instructions[opcode]()
  
}

void Chip8::loadROM(std::string path) {
  std::ifstream stream(path, std::ios::in | std::ios::binary);
  std::vector<uint8_t> contents((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
  for(auto i : contents) {
    std::cout << (unsigned)(uint8_t)i << "\n";
  }
  std::array<uint8_t, 0xFFF> mem;
  std::move(contents.begin(), contents.begin() + 0xFFF, mem.begin());
  cpu.setMemory(mem);
}