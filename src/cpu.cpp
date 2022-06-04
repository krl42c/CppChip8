#include "cpu.h"
#include <array>
#include <iostream>

CPU::CPU() {
  pc = 0;
  sp = 0;
  memory.fill(0);
}

CPU::~CPU() {}

uint8_t CPU::decodeOp() {
  uint8_t decoded;
  opcode = memory[pc];
  opcode = opcode << 8;
  opcode += memory[pc + 1];

  decoded = (opcode & 0xF000) >> 12;
  std::cout << decoded << "\n";

  return decoded;
}

void CPU::setMemory(std::array<uint8_t, 0xFFF> memory) {
  memory = memory;
}

/* INSTRUCTION IMPLEMENTATIONS */
void CPU::cls() {}

void CPU::returnFromSubroutine() {
  sp--;
  pc = memory[this->sp];
  pc += 2;
}

void CPU::jumpToAddress() { pc = opcode & 0x0FFF; }

void CPU::callSubroutine() {
  memory[sp] = pc;
  sp--;
  pc = opcode & 0x0FFF;
}

void CPU::skipNextEqualVxKk() {
  uint8_t vreg = shiftBitsVREG_X(opcode);
  uint8_t kk = getKK(opcode);

  if (v_regs[vreg] == kk)
    pc += 4; // Skip instruction
  else
    pc += 2;
}

void CPU::skipNextNotEqualVxKk() {
  uint8_t target = shiftBitsVREG_X(opcode);
  uint8_t kk = getKK(opcode);

  if (v_regs[target] != kk)
    pc += 4; // Skip instruction
  else
    pc += 2;
}

void CPU::setVxKk() {
  v_regs[shiftBitsVREG_X(opcode)] = getKK(opcode);
  pc += 2;
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

constexpr uint8_t CPU::shiftBitsVREG_X(uint8_t opcode) { return (opcode & 0x0F00) >> 8; }

constexpr uint8_t CPU::shiftBitsVREG_Y(uint8_t opcode) { return (opcode & 0x00F0) >> 4; }

constexpr uint8_t CPU::getKK(uint8_t opcode) { return (opcode & 0x00FF); }
