#ifndef PC_H_INCLUDED 
#define PC_H_INCLUDED

#include "mp.h"

SC_MODULE(PC) 
{
	sc_in< sc_bv<AWORD> > in;		// Data input
	sc_in< sc_bv<1> > w;		// Write control signal
	sc_out< sc_bv<AWORD> > out;		// Data output
	sc_in< bool > clk;		// Clock
	
	void pc_thread(void);
		
	SC_CTOR(PC) 
	{
		SC_METHOD(pc_thread);
		sensitive << clk.pos();
	}
};

#endif
