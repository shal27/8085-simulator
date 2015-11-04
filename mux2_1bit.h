#ifndef MUX2_1BIT_H_INCLUDED
#define MUX2_1BIT_H_INCLUDED

#include "mp.h"

SC_MODULE(MUX2_1BIT) {
	sc_in<  sc_bv<1> >	in0;	// First input
	sc_in<  sc_bv<1> > 	in1;	// Second input
	sc_in<  sc_bv<1> >	sel;	// Selection bit
	sc_out< sc_bv<1> >	out;	// Output

	void mux2_1bit_thread(void);

	SC_CTOR(MUX2_1BIT) {
		SC_THREAD(mux2_1bit_thread);
		sensitive << in0;
		sensitive << in1;
		sensitive << sel;
	}
};



#endif
