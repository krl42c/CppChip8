#include <array>
#include <iostream>
#include "cpu.h"

CPU::CPU() {

}

CPU::~CPU() {

}

uint8_t CPU::decodeOp() {
  uint8_t decoded;
  this->opcode = this->memory[this->pc];
  this->opcode = this->opcode << 8;
  this->opcode += this->memory[this->pc + 1];

  decoded = (this->opcode & 0xF000) >> 12;
  std::cout << decoded << "\n";
  return decoded;
}


void CPU::executeCycle() {
  switch (decodeOp()) {
    case 0x1:
      /*
      Set program counter to nnn
      nnn - lowest 12 bits => perform AND on opcode
      */
      pc = opcode & 0x0FFF;
      break;
    case 0x2:
      /*
      2nnn - CALL addr
      Save current pc on stack
      Get address from nnn by performing AND on opcode into pc
      */
      memory[sp] = pc & 0x00FF;
      sp += 1;
      memory[sp] = (pc & 0x00FF) >> 8;
      sp += 1;
      pc = opcode & 0x0FFF;
      break;
    case 0x3:
      uint8_t reg_num = (opcode & 0x0F00) >> 8;
      if (v_regs[reg_num] == (opcode & 0x00FF)) {
        pc += 2;
      }
      break;
  }
}

void CPU::setMemory(std::array<uint8_t, 0xFFF> memory) {
  this->memory = memory;
}

