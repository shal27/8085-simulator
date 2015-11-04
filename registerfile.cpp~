#include "registerfile.h"

void
REGFILE::
regfile_read_thread(void)
{
	sc_uint<2>	a_wreg;
	sc_uint<2>	a_reg1;
	sc_uint<8>		d_wreg;
	sc_uint<1>		w_t;
	bool			clk_t;

	while (true) {

		#ifdef VERBOSE
		cerr 	<< "REGFILE" 
			<< " Time is:" 
			<< sc_get_curr_simcontext()->time_stamp() << endl;
		#endif

		clk_t = clk.read();

		if (clk_t == 1) {
			a_reg1 = r_addr_reg1.read();
			r_data_reg1.write(rfile[a_reg1]);
			#ifdef VERBOSE
			cerr	<< "...reading $" << a_reg1 << " = " 
				<< rfile[a_reg1] << " $\n"; 
			#endif
		}
		wait();
	}
}

void
REGFILE::
regfile_write_thread(void)
{
	sc_uint<2>	a_wreg;
	sc_uint<2>	a_reg1;
	sc_uint<8>		d_wreg;
	sc_uint<1>		w_t;

	while(true) {
		#ifdef VERBOSE
		cerr << "REGFILE write" << endl;
		#endif

		w_t = w.read();
		if (w_t == 1) {
			a_wreg = w_addr_reg.read();
			d_wreg = w_data_reg.read();

			#ifdef VERBOSE
			cerr	<< "...writing $" << a_wreg << " = " 
				<< d_wreg << endl;
			#endif
			if (a_wreg < 4 && a_wreg != 0) {
				rfile[a_wreg] = d_wreg;
			}
		}
		wait();
	}
}

