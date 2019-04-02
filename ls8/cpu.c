#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename)
{
  FILE *file = fopen(filename, "r");
  FILE *dummy = fopen(filename, "r");

  if(file == NULL) {
      printf("File is not opening!\n");
  }

  //Used to get each line
  char line[100];

  int line_count = 0;
  int line_increment = 0;

  //Use dummy to get line count
  //This is needed because there's an extra line
  //of complete whitespace that needs to be ignored
  while(!feof(dummy)) {
    char ch = fgetc(dummy);
    if(ch == '\n'){
        line_count++;
    }
  }

  //Data is equivalent to line_count
  long data[line_count];
  int i = 0;
  while(i < line_count) {
    fgets(line, 100, file);
      if(line[0] == '#'){
          line_count--;
          continue;
      }
    *(line+8) = '\0';
    printf("%s", line);
    long l = strtol(line, NULL, 2);
    printf(" Decimal: %lu", l);
    data[i] = l;
    printf(" Line: %d\n", i+1);
    i++;
  }

  int address = 0;

  for (int i = 0; i < line_count; i++) {
    cpu->ram[address++] = data[i];
  }

  fclose(file);
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
    int operand_one, operand_two;

    switch(command) {
        case LDI:
            //Retrieve the Two Arguments from RAM
            operand_one = cpu->ram[++cpu->pc];
            operand_two = cpu->ram[++cpu->pc];
            cpu->registers[operand_one] = (unsigned char)operand_two;
            cpu->pc++;
        case PRN:
            operand_one = cpu->ram[++cpu->pc];
            printf("%d\n", cpu->registers[operand_one]);
            cpu->pc++;
        case HLT:
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
