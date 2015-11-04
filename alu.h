#ifndef ALU_H_INCLUDED
#define ALU_H_INCLUDED

#include "mp.h"
 
SC_MODULE(ALU) 
	{
	sc_in<  sc_bv<3> >	aluctrl;	// Control input
	sc_in<  sc_bv<DWORD> >	a;		// First operand input 
	sc_in<  sc_bv<DWORD> >	b;		// Second operand input
	sc_out< sc_bv<DWORD> >	result;		// Result
	sc_out< sc_bv<5> > flag;		// 5 bit flag value

	void alu_thread(void);

	// Constructor
	SC_CTOR(ALU) {
		SC_THREAD(alu_thread);
		sensitive << aluctrl;
		sensitive << a;
		sensitive << b;
	}
};

#endif
