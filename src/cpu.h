#include <array>
#include <functional>
#include <map>

#ifndef CPU_H
#define CPU_H

class CPU {
public:
  CPU();
  ~CPU();
  uint8_t decodeOp();
  void executeCycle();
  void setMemory(std::array<uint8_t, 0xFFF> memory);

  // Instructions
  void cls();                  // 00E0 - CLS
  void returnFromSubroutine(); // 00EE - RET
  void jumpToAddress();        // 1nnn - JP addr
  void callSubroutine();       // 2nnn - CALL addr
  // Logical instructions
  void skipNextEqualVxKk();
  void skipNextNotEqualVxKk();
  void skipNextEqualVxVy();
  void setVxKk();
  void setVxVxPlusKk();
  void setVxVy();

  void logicalOR_VX();
  void logicalAND_VX();
  void logicalXOR_VX();

  // Bit util
  uint8_t shiftBitsVREG_X(uint8_t opcode);
  uint8_t shiftBitsVREG_Y(uint8_t opcode);
  uint8_t getKK(uint8_t opcode);

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