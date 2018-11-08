#include<stdio.h>
#include<stdlib.h>
#ifndef CPU_H
#define CPU_H

#define NO_OF_REGISTERS 8
typedef unsigned short Register;
typedef unsigned char Bit;


/*
CPU Class
*/
typedef struct cpu_s {
  Register reg_file[NO_OF_REGISTERS];
  Bit ir[NO_OF_REGISTERS * 2];
  Bit sext[NO_OF_REGISTERS * 2];
} CPU_s;



/* Functions Declaration.*/
void putInRegister(int, Register, Register[]);
void getInstructionSets(Bit[], Bit[], Bit[], Bit[]);
void getSext(Bit[], Bit[]);

#endif