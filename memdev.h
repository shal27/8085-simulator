#ifndef MEMDEV_H_INCLUDED
#define MEMDEV_H_INCLUDED

#include "mp.h"

SC_MODULE(MEMDEV) {
	sc_in < sc_bv<DWORD> > address_lsb;
	sc_in < sc_bv<DWORD> > address_msb;
	
	sc_out< sc_bv<DWORD> > d_read;
	sc_in < sc_bv<DWORD> > d_write;
	sc_in <sc_bv<1> > w;
	sc_in <sc_bv<1> >  r;
	sc_in <bool> clk;
	
	sc_in <sc_bv<1> > s0;
	sc_in <sc_bv<1> > s1;

	sc_bv<8>* memdevfile;

	void memdev_thread(void);
	void memdev_init(const char *filename);
	void memdev_dump(const char *filename);

	SC_CTOR(MEMDEV) {
		SC_THREAD(memdev_thread);
		sensitive << clk;
		sensitive << address_lsb;
		sensitive << address_msb;
		sensitive << d_write;
		sensitive << w;
		sensitive << r;

		memdevfile = new sc_bv<8> [MEMDEVSIZE];

	};
};

#endif
