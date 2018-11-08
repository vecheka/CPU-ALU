
#include<stdio.h>
#include<stdlib.h>
#include "cpu.h"
typedef unsigned char Bit;
typedef unsigned short Register;
#define CODE_BIT 3


/*
Put Data in the desired register number
@param theReg - register number
@param theData - data to be stored
@param theRegFile - Register File
*/
void putInRegister(int theReg, Register theData, Register theRegFile[]) {
  theRegFile[theReg] = theData;
}

/*
Get op code, Rd and Rs
@param theOpcode - array to store op code 
@param theRd - array to store Rd code
@param theRs - array to store Rs code
@param theIR - Instruction Register
*/
void getInstructionSets(Bit theOpcode[], Bit theRd[], Bit theRs[], Bit theIR[]) {
  int i, index = 0;
  for (i = 0; i < CODE_BIT; i++) {
    theOpcode[index++] = theIR[i];
  }
  index = 0;
  
  for (i = CODE_BIT; i < CODE_BIT * 2; i++) {
    theRd[index++] = theIR[i];
  }
  index = 0;

  for (i = CODE_BIT * 2; i < CODE_BIT * 3; i++) {
    theRs[index++] = theIR[i];
  }
}

/*
Get the sign extension
@param theSext - sign extension binary
@param theIR - instruction register
*/
void getSext(Bit theIR[], Bit theSext[]) {
  int i = CODE_BIT * 3, j;
  if (theIR[i] == 1) {
     for (j = 0; j < i; j++) theSext[j] = 1;
  } else for (j = 0; j < i; j++) theSext[j] = 0;
  for (i = CODE_BIT *3; i < CODE_BIT * 5; i++) {
    theSext[i] = theIR[i];
  }
} 