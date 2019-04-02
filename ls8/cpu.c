#include "cpu.h"
#include <stdlib.h>
#include <string.h>
#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
    // From print8.ls8
    0b10000010, // LDI R0,8
    0b00000000,
    0b00001000,
    0b01000111, // PRN R0
    0b00000000,
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.

    unsigned char command = cpu->ram[cpu->pc];
    //printf("%d\n", command == LDI);
    int operand_one, operand_two;

    switch(command) {
        case LDI:
            //Retrieve the Two Arguments from RAM
            operand_one = cpu->ram[++cpu->pc];
            operand_two = cpu->ram[++cpu->pc];
            //printf("Operand One: %d\n", operand_one);
            //printf("Operand Two: %d\n", operand_two);
            cpu->registers[operand_one] = (unsigned char)operand_two;
            //printf("Register Zero: %d\n", cpu->registers[operand_one]);
            cpu->pc++;
            //printf("Program Counter: %d\n", cpu->pc);
        case PRN:
            //printf("Program Counter: %d\n", cpu->pc);
            operand_one = cpu->ram[++cpu->pc];
            //printf("Program Counter: %d\n", cpu->pc);
            //printf("Operand One: %d\n", operand_one);
            printf("%d\n", cpu->registers[operand_one]);
            cpu->pc++;
        case HLT:
            //printf("COMMAND: %d\n", cpu->ram[cpu->pc]);
            printf("HALTED\n");
            running = 0;
            break;
        default:
            printf("Unrecognized Instruction\n");
            exit(1);
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  memset(cpu->registers, '0',  8 * sizeof(char));
  memset(cpu->ram, '0',  256 * sizeof(char));
}

void cpu_ram_read(struct cpu *cpu, int increment)
{

}

void cpu_ram_write()
{

}
