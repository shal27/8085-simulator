#ifndef REGISTER_H_INCLUDED 
#define REGISTER_H_INCLUDED

#include "mp.h"

SC_MODULE(REGISTER) 
{
	sc_in< sc_bv<DWORD> > in;		// Data input
	sc_in< sc_bv<1> > w;		// Write control signal
	sc_out< sc_bv<DWORD> > out;		// Data output
	sc_in< bool > clk;		// Clock
	
	void reg_thread(void);
		
	SC_CTOR(REGISTER) 
	{
		SC_METHOD(reg_thread);
		sensitive << clk.pos();
	}
};

#endif
