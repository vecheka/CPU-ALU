#include<stdio.h>
#include<stdlib.h>
#include "alu.h"
typedef unsigned short Register;
typedef unsigned char Bit;
#define REG_BITS 16

/*
Add two registers
@param theA - first register
@param theB - second register
@return resulting register
*/
Register add(Register theA, Register theB) {
  return theA + theB;
}

/*
NAND two registers
@param theA - first register
@param theB - second register
@param theR - resulting regiser
*/
void nand(Bit theA[], Bit theB[], Bit theR[]) {
  int i;
  for (i = 0; i < REG_BITS; i++) {
    theR[i] = !(theA[i] && theB[i]);
  }
}