#include <array>
#include <iostream>
#include "cpu.h"

CPU::CPU() {
  this->pc = 0;
  this->sp = 0;
  this->memory.fill(0);
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

