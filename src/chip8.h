#include "cpu.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>

#ifndef CHIP8_H
#define CHIP8_H

class Chip8 {
public:
  Chip8(CPU cpu);
  Chip8();
  ~Chip8();
  void loadROM(std::string path);
  void run();

private:
  std::map<int, std::function<void()>> instructions;
  CPU cpu;
};
#endif
