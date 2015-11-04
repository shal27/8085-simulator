#ifndef IDB_H
#define IDB_H
#include "mp.h"

SC_MODULE(idb)
{
	sc_in 		<sc_bv<8> > opcode;
	sc_in		<sc_bv<8> > acc_in;
	sc_out		<sc_bv<8> > acc_out;
	
	sc_out		<sc_bv<8> > temp;
	sc_in		<sc_bv<5> > flip_flop;
	sc_in		<sc_bv<8> > alu_data;
	sc_out		<sc_bv<8> > instr_reg;
	sc_in		<sc_bv<8> > reg_file_data_in;
	sc_out		<sc_bv<8> > reg_file_data_out;
	
	sc_out 		<sc_bv<2> > reg_rd_select;
	sc_out 		<sc_bv<2> > reg_wrt_select;
	
	sc_in		<sc_bv<8> > ad_buff_in;		//address data buffer
	sc_out		<sc_bv<8> > ad_buff_out;
	sc_out		<sc_bv<3> > aluop;
	sc_in		<sc_bv<4> > state;
	sc_out		<sc_bv<1> > w_ad_buff;
	sc_out		<sc_bv<1> > w_acc;
	sc_out		<sc_bv<1> > w_temp;
	sc_out		<sc_bv<1> > w_instr_reg;
	sc_out		<sc_bv<1> > w_regfile;

	void idb_thread(void);

	SC_CTOR(idb)
	{
		SC_THREAD(idb_thread);
			sensitive<< opcode;
			sensitive<< flip_flop;
			sensitive<< alu_data;
			sensitive<< reg_file_data_in;
			sensitive<< ad_buff_in;
			sensitive<< state;
			sensitive<< acc_in;

	}
};

#endif
