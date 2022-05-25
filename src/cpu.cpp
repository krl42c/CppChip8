#include "cpu.h"
#include <array>
#include <iostream>

CPU::CPU() {
  this->pc = 0;
  this->sp = 0;
  this->memory.fill(0);
}

CPU::~CPU() {}

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
void CPU::cls() {}

void CPU::returnFromSubroutine() {
  this->sp--;
  this->pc = this->memory[this->sp];
  this->pc += 2;
}

void CPU::jumpToAddress() { this->pc = this->opcode & 0x0FFF; }

void CPU::callSubroutine() {
  this->memory[this->sp] = this->pc;
  this->sp--;
  this->pc = this->opcode & 0x0FFF;
}

void CPU::skipNextEqualVxKk() {
  uint8_t vreg = shiftBitsVREG_X(this->opcode);
  uint8_t kk = getKK(this->opcode);

  if (this->v_regs[vreg] == kk)
    this->pc += 4; // Skip instruction
  else
    this->pc += 2;
}

void CPU::skipNextNotEqualVxKk() {
  uint8_t target = this->shiftBitsVREG_X(this->opcode);
  uint8_t kk = this->getKK(this->opcode);

  if (this->v_regs[target] != kk)
    this->pc += 4; // Skip instruction
  else
    this->pc += 2;
}

void CPU::setVxKk() {
  v_regs[shiftBitsVREG_X(this->opcode)] = getKK(opcode);
  this->pc += 2;
}

void CPU::setVxVxPlusKk() {
  uint8_t target = shiftBitsVREG_X(opcode);
  uint8_t kk = getKK(opcode);

  v_regs[target] += kk;
  pc += 2;
}

void CPU::setVxVy() {
  uint8_t vx = shiftBitsVREG_X(opcode);
  uint8_t vy = shiftBitsVREG_Y(opcode);
  v_regs[vx] = v_regs[vy];
  pc += 2;
}

void CPU::logicalOR_VX() {
  /* 8xy1 - OR Vx, Vy */
  uint8_t vx = shiftBitsVREG_X(opcode);
  uint8_t vy = shiftBitsVREG_Y(opcode);
  v_regs[vx] = v_regs[vx] | v_regs[vy];
  pc += 2;
}

void CPU::logicalAND_VX() {
  uint8_t vx = shiftBitsVREG_X(opcode);
  uint8_t vy = shiftBitsVREG_Y(opcode);
  v_regs[vx] = v_regs[vx] & v_regs[vy];
  pc += 2;
}

void CPU::logicalXOR_VX() {
  uint8_t vx = shiftBitsVREG_X(opcode);
  uint8_t vy = shiftBitsVREG_Y(opcode);
  v_regs[vx] = v_regs[vx] ^ v_regs[vy];
  pc += 2;
}

uint8_t CPU::shiftBitsVREG_X(uint8_t opcode) { return (opcode & 0x0F00) >> 8; }

uint8_t CPU::shiftBitsVREG_Y(uint8_t opcode) { return (opcode & 0x00F0) >> 4; }

uint8_t CPU::getKK(uint8_t opcode) { return (opcode & 0x00FF); }
