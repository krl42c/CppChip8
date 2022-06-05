#include "chip8.h"

Chip8::Chip8() {
  //this->cpu = cpu;
  CPU cpu;
  instructions.insert({0, [&cpu]() { cpu.cls(); }});
  instructions.insert({2, [&cpu]() { cpu.returnFromSubroutine(); }});
  instructions.insert({3, [&cpu]() { cpu.jumpToAddress(); }});
  instructions.insert({4, [&cpu]() { cpu.callSubroutine(); }});
  instructions.insert({5, [&cpu]() { cpu.skipNextEqualVxKk(); }});
  instructions.insert({6, [&cpu]() { cpu.skipNextNotEqualVxKk(); }});
  instructions.insert({7, [&cpu]() { cpu.setVxKk(); }});
  instructions.insert({8, [&cpu]() { cpu.setVxVxPlusKk(); }});
  instructions.insert({9, [&cpu]() { cpu.setVxVy(); }});
  instructions.insert({10, [&cpu]() { cpu.logicalOR_VX(); }});
  instructions.insert({0xb, [&cpu]() { cpu.logicalAND_VX(); }});
  instructions.insert({0xc, [&cpu]() { cpu.logicalXOR_VX(); }}); // 8xy4
}

Chip8::~Chip8() {}

void Chip8::run() {
  
}

void Chip8::loadROM(std::string path) {
  std::array<uint8_t, 0xFFF> mem;
  std::ifstream stream(path, std::ios::in | std::ios::binary);
  char c;
  for(int i = 0;stream.get(c); i++) {
    mem[i] = (uint8_t) c;
  }

  cpu.setMemory(mem);
  for(auto c : mem) {
    uint8_t decoded = cpu.decodeOp();
    printf("\\x%2x DECODED \n", decoded);
    instructions[decoded]();
  }
}