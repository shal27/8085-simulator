#ifndef STATEREGISTER_H_INCLUDED 
#define STATEREGISTER_H_INCLUDED

#include "mp.h"

SC_MODULE(STATEREGISTER) 
{
	sc_in< sc_bv<4> > in;		// Data input
	sc_out< sc_bv<4> > out;		// Data output
	sc_out< sc_bv<4> > out1;	// Data output
	sc_in< bool > clk;		// Clock
	
	void state_reg_thread(void);
		
	SC_CTOR(STATEREGISTER) 
	{
		SC_METHOD(state_reg_thread);
		sensitive << clk.pos();
	}
};

#endif
