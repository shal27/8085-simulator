#ifndef MUX3_H_INCLUDED
#define MUX3_H_INCLUDED

#include "mp.h"

SC_MODULE(MUX3) {
	sc_in<  sc_bv<DWORD> >	in0;	// First input
	sc_in<  sc_bv<DWORD> > 	in1;	// Second input
	sc_in<  sc_bv<DWORD> > 	in2;	// Third input
	sc_in<  sc_bv<2> >	sel;	// Selection bit
	sc_out< sc_bv<DWORD> >	out;	// Output

	void mux3_thread(void);

	SC_CTOR(MUX3) {
		SC_THREAD(mux3_thread);
		sensitive << in0;
		sensitive << in1;
		sensitive << in2;
		sensitive << sel;
	}
};



#endif
