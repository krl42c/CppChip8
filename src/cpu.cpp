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
      cls();
      break;
    case 0x2:
      returnFromSubroutine();
      break;
    case 0x3:
      callSubroutine();
      break;
  }
}

void CPU::setMemory(std::array<uint8_t, 0xFFF> memory) {
  this->memory = memory;
}

/* INSTRUCTION IMPLEMENTATIONS */
void CPU::cls() {
  
}

void CPU::returnFromSubroutine() {
  this->sp--;
  this->pc = this->memory[this->sp];
  this->pc += 2;
}

void CPU::jumpToAddress() {
  this->pc = this->opcode & 0x0FFF;
}

void CPU::callSubroutine() {
  this->memory[this->sp] = this->pc;
  this->sp--;
  this->pc = this->opcode & 0x0FFF;
}

