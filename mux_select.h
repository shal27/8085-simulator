#ifndef MUX_SELECT_H
#define MUX_SELECT_H

#include"mp.h"

SC_MODULE(mux_select)
{
	sc_in <sc_bv<4> > in1;
	
	sc_out<sc_bv<2> > out1;
	sc_out<sc_bv<1> > out2;
	
	
	void mux_select_thread(void);
	
	SC_CTOR(mux_select)
	{
		SC_THREAD(mux_select_thread);
			sensitive<<in1;
	}
};
#endif
