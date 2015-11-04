#ifndef REGISTERFILE_H_INCLUDED
#define REGISTERFILE_H_INCLUDED

#include "mp.h"

SC_MODULE(REGFILE) {
	sc_in< sc_bv<2> >		r_addr_reg1;
	sc_out< sc_bv<8> >		r_data_reg1;

	

	sc_in< sc_bv<2> >		w_addr_reg;
	sc_in< sc_bv<8> >		w_data_reg;
	sc_in< sc_bv<1> >		w;

	sc_in<  bool >			clk;

	sc_bv<8>			rfile[3];

	void regfile_read_thread(void);
	void regfile_write_thread(void);


	SC_CTOR(REGFILE) {
		SC_THREAD(regfile_read_thread);
		sensitive << clk;
		sensitive << r_addr_reg1;
		
		sensitive << w_addr_reg;
		sensitive << w_data_reg;
		sensitive << w;

		SC_THREAD(regfile_write_thread);
		sensitive_neg << clk;

		
	} 
};

#endif
