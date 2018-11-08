/*
Program outline:
A program that takes an Intruction Register(IR) in hexadecimal value in the format of 0x???? (? standing for a value), and executes according to the given IR.

First 3 bits is the Opcode which determines the ALU:
	000 signals for adding
	001 signals for adi
	010 signals for nand
Next 3 bits is the Register Data which determines the register of the first operand and the distination register of the result.
Next 3 bits is the Rs which determines the register of the second operand.
The last 7 bits is the sign extension.

The program executes according to the following format of input:
	./a.out -ir 0x???? -r# 0x? -r# 0x? 
	?: hexadecimal value
	#: register number


Programmer: Vecheka Chhourn, Allen Whitemarsh

Date: 10/15/2018

*** Note *** : Please compile using gcc main.c cpu.c alu.c.

*/


#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "cpu.h"
#include "alu.h"
typedef unsigned char Bit;
typedef unsigned short Register;
#define REG_BITS 16
#define HEX_BITS 4

/*
Get decimal value of a hex number
@param theHext - hex number
@return a integer value
*/
Register getInteger(char theHex) {
  return theHex <= '9' ? theHex - '0' : theHex - 'A' + 10; 
}


/*
Convert a decimal to a binary value
@param theDec - decimal number to be converted
@param theBinary - binary array
@param theSize - bit size of the binary
*/
void decimalToBinary(int theDec, Bit theBinary[], int theSize) {
  int i = theSize - 1;
  while (theDec > 0) {
    theBinary[i] = theDec % 2;
    i--;
    theDec /= 2;
  }
}

/*
Convert a binary to a decimal value
@param theBinary - binary to be converted
@param theSize - size of the binary
*/
int binaryToDecimal(Bit theBinary[], int theSize) {
  int i, num = 0;
  int deg = theSize - 1;
  for (i = 0; i < theSize; i++) {
    num += (1 << deg--) * theBinary[i]; 
  }
  return num;
}

/*
Take the two complment of a binary
@param theBinary - binary to be converted
@param theSize - size of the binary
*/
void twoComplement(Bit theBinary[], int theSize) {
  int len = theSize - 1;
  while (theBinary[len] != 1) len--;
  len--;
  while (len >= 0) {
    if (theBinary[len] == 0) theBinary[len--] = 1;
    else theBinary[len--] = 0;
  }
}



// for testing
void print(Bit theArray[], int theSize) {
  int i;
  for (i = 0; i < theSize; i++) {
    printf("%d ", theArray[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  
  CPU_s cpus; // initiate cpu class
  ALU_s alu; // initiate alu class
  Bit ir[REG_BITS] = {0};
  Bit opCode[HEX_BITS - 1] = {0};
  Bit Rd[HEX_BITS - 1] = {0};
  Bit Rs[HEX_BITS - 1] = {0};

  // read and store IR from command argument
  long n = strtol(argv[2], NULL, 16);
  decimalToBinary(n, ir, REG_BITS);
  memcpy(cpus.ir, ir, REG_BITS);

  // get registers' numbers and store data in correct register 
  int first_reg = getInteger(argv[3][2]);
  int second_reg = getInteger(argv[5][2]);
  putInRegister(first_reg, strtol(argv[4], NULL, 16), cpus.reg_file);
  putInRegister(second_reg, strtol(argv[6], NULL, 16), cpus.reg_file);

  // get opcode, Rd, Rs, and sext
  getInstructionSets(opCode, Rd, Rs, cpus.ir);
  getSext(cpus.ir, cpus.sext);

  // get opcode, Rd, Rs in integer
  int op = binaryToDecimal(opCode, HEX_BITS - 1);
  int rd = binaryToDecimal(Rd, HEX_BITS - 1);
  int rs = binaryToDecimal(Rs, HEX_BITS - 1);

  // add, adi or nand operations
  alu.a = cpus.reg_file[rd];
  alu.b = cpus.reg_file[rs];
  
  
  Bit r[REG_BITS] = {0};  
  if (op == 0) { // add
    alu.r = add(alu.a, alu.b);
    putInRegister(rd, alu.r, cpus.reg_file);
    printf("R%d = 0x%X, R%d = 0x%X, ADD 0x%X, 0x%X = 0x%X -> R%d\n",
            rd, alu.a, rs, alu.b,
             alu.a, alu.b, alu.r, rd);  

  } else if (op == 1) { // adi
    alu.a = cpus.reg_file[rs];
    alu.b = binaryToDecimal(cpus.sext, REG_BITS);
    alu.r = add(alu.a, alu.b);
    decimalToBinary(alu.r, r,REG_BITS);
    if (r[0] == 1) {
      twoComplement(r, REG_BITS);
      alu.r = -binaryToDecimal(r, REG_BITS);
    } 
    putInRegister(rd, alu.r, cpus.reg_file);
    printf("R%d = 0x%X, sext = 0x%X, ADI 0x%X, 0x%X = 0x%X -> R%d\n",
            rs, alu.a, alu.b, alu.a, alu.b, alu.r, rd);

  } else if (op == 2) { // nand
    Bit a[REG_BITS] = {0};
    Bit b[REG_BITS] = {0};
    decimalToBinary(alu.a, a, REG_BITS);
    decimalToBinary(alu.b, b, REG_BITS);
    nand(a, b, r);
    if (r[0] == 1) {
      twoComplement(r, REG_BITS);
      alu.r = -binaryToDecimal(r, REG_BITS);
    } else alu.r = binaryToDecimal(r, REG_BITS);
    putInRegister(rd, alu.r, cpus.reg_file);
    printf("R%d = 0x%X, R%d = 0x%0X, NAND 0x%X, 0x%X = 0x%X -> R%d\n",first_reg, alu.a, second_reg, alu.b,
           alu.a, alu.b, alu.r, rd); 
  }

  


  return 0;
}