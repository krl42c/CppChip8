#include "cpu.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <memory>

#ifndef CHIP8_H
#define CHIP8_H

class Chip8 {
public:
  Chip8(CPU cpu);
  Chip8();
  ~Chip8();
  void loadROM(std::string path);
  bool loadROM_A(std::string path);
  void run();
  std::shared_ptr<CPU> cpu;
private:
  std::map<int, std::function<void()>> instructions;
};
#endif
