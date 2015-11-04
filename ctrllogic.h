#ifndef CTRLLOGIC_H_INCLUDED
#define CTRLLOGIC_H_INCLUDED

#include "mp.h"

SC_MODULE(CTRLLOGIC) {
	sc_in< sc_bv<8> > opcode_x;	// Instruction bits [31-26]
	sc_in< sc_bv<4> > state_x;	// Present State
	sc_out< sc_bv<1> > s0_x;
	sc_out< sc_bv<1> > s1_x;
	sc_out< sc_bv<1> > mem_rd_low_x;
	sc_out< sc_bv<1> > mem_wrt_low_x;
	sc_out< sc_bv<1> > ale_x;
	sc_out< sc_bv<1> > pc_wrt_x;
	sc_out< sc_bv<1> > db_wrt_x;
	sc_out< sc_bv<1> > adb_wrt_x;
	

	sc_out< sc_bv<4> > nextstate_x;	// Next State

	void ctrllogic_thread(void);

	// Constructor
	SC_CTOR(CTRLLOGIC) {
		SC_THREAD(ctrllogic_thread);
		sensitive << opcode_x;
		sensitive << state_x;
	}
};

#endif
