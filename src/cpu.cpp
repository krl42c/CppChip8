#include "cpu.h"
#include <array>
#include <iostream>

#define LOG_EVENT(event) std::cout << event << "\n"

CPU::CPU() {
  pc = 0;
  sp = 0;
  opcode = 0;
  std::cout << "Created CPU\n";
  //memory.fill(0);
}

CPU::~CPU() {
  std::cout << "Destroyed CPU\n";
}

uint8_t CPU::decodeOp() {
  uint8_t decoded;
  opcode = memory[pc];
  opcode = (memory[pc] << 8) | memory[pc+1];

  decoded = (opcode & 0xF000) >> 12;
  printf("FULL OPCODE: \\x%2x \n", opcode);
  return decoded;
}

void CPU::setMemory(std::array<uint8_t, 0xFFF> memory) {
  this->memory = memory;
}

/* INSTRUCTION IMPLEMENTATIONS */
void CPU::cls() {
  pc += 2;
}

void CPU::returnFromSubroutine() {
  LOG_EVENT("RETURN_FROM_SUBROUTINE");
  if(sp > 0)
    sp--;
  pc = memory[sp];
  pc += 2;
}

void CPU::jumpToAddress() { pc = opcode & 0x0FFF; }

void CPU::callSubroutine() {
  LOG_EVENT("CALL_SUBROUTINE");
  memory[sp] = pc;
  if(sp > 0)
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
  LOG_EVENT("SKIP_NEXT_NOT_EQUAL_VX_KK");
  uint8_t target = shiftBitsVREG_X(opcode);
  uint8_t kk = getKK(opcode);

  if (v_regs[target] != kk) {
    this->pc += 4; // Skip instruction
  }
  else {
    this->pc += 2;
  }
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

void CPU::SHR() {
  v_regs[0xF] = v_regs[shiftBitsVREG_X(opcode)] & 0x1;
  v_regs[shiftBitsVREG_X(opcode)] >>= 1;
  pc +=2;

}
void CPU::SUBN() {
  pc +=2 ;

}
void CPU::SHL() {
  pc +=2 ;

}
void CPU::SNE() {

}

void CPU::LD() {

}
void CPU::JPV0() {

}
void CPU::RND() {

}

void CPU::DRW() {

}
void CPU::SKP() {

}
void CPU::SKNP() {

}
void CPU::LD_VX_DT() {

}
void CPU::LD_VX_K() {

}
void CPU::LD_DT_VX() {

}
void CPU::LD_ST_VX() {

}
void CPU::ADD_I_VX() {

} 

void CPU::LD_F_VX() {

}

void CPU::LD_B_BX() {

}

void CPU::LD_I_VX() {

}
void CPU::LD_VX_I() {

}

uint8_t CPU::shiftBitsVREG_X(uint8_t opcode) { return (opcode & 0x0F00) >> 8; }

uint8_t CPU::shiftBitsVREG_Y(uint8_t opcode) { return (opcode & 0x00F0) >> 4; }

uint8_t CPU::getKK(uint8_t opcode) { return (opcode & 0x00FF); }

uint16_t CPU::getPC() { return pc; }
