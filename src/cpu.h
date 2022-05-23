#include <array>
#ifndef CPU_H
#define CPU_H

class CPU {
public:
  CPU();
  ~CPU();
  uint8_t decodeOp();
  void executeCycle();
  void setMemory(std::array<uint8_t, 0xFFF> memory);

private:
  std::array<uint8_t, 0xFFF> memory;
  std::array<uint8_t, 16> v_regs;
  uint16_t I;
  uint8_t delay_timer;
  uint8_t sound_timer;
  uint16_t pc;
  uint16_t sp;
  uint8_t opcode;
};

#endif