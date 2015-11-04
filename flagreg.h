#ifndef flag_H_INCLUDED
#define flag_H_INCLUDED

#include "mp.h"

SC_MODULE(FLAG) {
	sc_in< sc_bv<5> >  statusflag;  // First operand
	
	sc_out< sc_bv<5> >  result;  // Result
	

	void flag_thread(void);
    
	// Constructor
	SC_CTOR(FLAG) {
		SC_THREAD(flag_thread);
		sensitive << statusflag ;
	}
};

#endif
