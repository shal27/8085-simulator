#ifndef MP_H_INCLUDED
#define MP_H_INCLUDED

#include "systemc.h"

#define DWORD           8     	// Dataword size
#define AWORD     	16      // Address word size of registerfile
#define MEMDEVSIZE 	128	// Size (in bytes) of RAM
#define REGSIZE 	8	// Size (in words) of registerfile


// ALU operations
#define ALU_AND         0
#define ALU_OR          1
#define ALU_ADD         2
#define ALU_SUB         3
#define ALU_XOR         4
					
// opcodes
       
#define OP_ADD_B        0x80        
#define OP_ADD_H        0x84       
                  
#define OP_SUB_B	0x90
#define OP_SUB_H	0x94

#define OP_XRA_B	0xA8
#define OP_XRA_H	0xAC

#define OP_ANA_B	0xA0
#define OP_ANA_H	0xA4
#define OP_MOV_A_B	0x78
#define OP_MOV_A_H	0x7C
#define OP_MOV_A_C	0x79
#define OP_MOV_B_A	0x47
#define OP_MOV_B_C	0x41
#define OP_MOV_B_H	0x44
#define OP_MOV_H_A	0x67
#define OP_MOV_H_B	0x60
#define OP_MOV_H_C	0x61
#define OP_LDA		0x56
#define OP_STA		0x57

//registers
#define REG_A	0
#define REG_B	1
#define REG_C	2
#define REG_H	3

#endif
