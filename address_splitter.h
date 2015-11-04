#ifndef ADDRESS_SPLITTER_H
#define ADDRESS_SPLITTER_H

#include "mp.h"

SC_MODULE(address_splitter)
{
	
	sc_in<sc_bv<16> >	in;	//16 bit address from PC
	sc_out<sc_bv<8> >	out1;
	sc_out<sc_bv<8> >	out2;
	
	void address_splitter_thread(void);
	
	SC_CTOR(address_splitter)
	{
		SC_THREAD(address_splitter_thread);
			sensitive<<in;
	}
};
#endif
	
