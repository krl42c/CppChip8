#include "chip8.h"

Chip8::Chip8() {
  cpu = std::make_shared<CPU>();
  //TODO: fix instructions, these are not in the correct order for testing purposes...
  instructions.insert({0, [&](){cpu->cls();}});
  instructions.insert({1, [&](){cpu->cls();}});
  instructions.insert({2, [&]() { cpu->returnFromSubroutine(); }});
  instructions.insert({3, [&]() { cpu->jumpToAddress(); }});
  instructions.insert({4, [&]() { cpu->callSubroutine(); }});
  instructions.insert({5, [&]() { cpu->skipNextEqualVxKk(); }});
  instructions.insert({6, [&]() { cpu->skipNextNotEqualVxKk(); }});
  instructions.insert({7, [&]() { cpu->setVxKk(); }});
  instructions.insert({8, [&]() { cpu->setVxVxPlusKk(); }});
  instructions.insert({9, [&]() { cpu->setVxVy(); }});
  instructions.insert({10, [&]() { cpu->logicalOR_VX(); }});
  instructions.insert({0xb, [&]() { cpu->logicalAND_VX(); }});
  instructions.insert({0xc, [&]() { cpu->logicalXOR_VX(); }}); // 8xy4
  instructions.insert({0xd, [&]() { cpu->SHR(); }}); 
  instructions.insert({0xe, [&]() { cpu->SUBN(); }}); 
  instructions.insert({0xf, [&]() { cpu->SUBN(); }}); 
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

  cpu->setMemory(mem);
  //testing
  while(cpu->getPC() < 500) {
    uint8_t decoded = cpu->decodeOp();
    printf("\\x%2x DECODED \n", decoded);
    instructions[decoded]();
  }
}

bool Chip8::loadROM_A(std::string path) {
  std::array<uint8_t, 0xFFF> mem;
  std::ifstream stream(path, std::ios::in | std::ios::binary);
  if(!stream)
    return false;

  char c;
  for(int i = 0;stream.get(c); i++) {
    mem[i] = (uint8_t) c;
  }
  cpu->setMemory(mem);
  return true;
}