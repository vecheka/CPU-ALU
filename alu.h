#include<stdio.h>
#include<stdlib.h>
#ifndef ALU_H
#define ALU_H

typedef unsigned short Register;
typedef unsigned char Bit;


/*
ALU Class
*/
typedef struct alu_s {
  Register a, b, r;
} ALU_s;


/* Functions Declaration.*/
Register add(Register, Register);
void nand(Bit[], Bit[], Bit[]);

#endif