#ifndef CTRL_H_INCLUDED
#define CTRL_H_INCLUDED

#include "mp.h"
#include "ctrllogic.h"
#include "stateregister.h"

SC_MODULE(CTRL) {
	
	// Ports
        sc_in< sc_bv<8> > opcode;       // opcode
	sc_in< bool > clk;
     
        sc_out< sc_bv<1> > s0;
        sc_out< sc_bv<1> > s1;
        sc_out< sc_bv<1> > mem_rd_low;
        sc_out< sc_bv<1> > ale;
        sc_out< sc_bv<1> > mem_wrt_low;
      
        sc_out< sc_bv<8> > op;		//output opcode for the internal data bus
        sc_out<sc_bv <4> > state;	//present state
        sc_out< sc_bv<1> > adb_wrt;	//address buffer
        sc_out< sc_bv<1> > db_wrt;	// address data buffer
        sc_out< sc_bv<1> > pc_wrt;
         
        STATEREGISTER *stateregister1;
        CTRLLOGIC *ctrllogic;
	sc_signal< sc_bv<4> > bus_next_state;
	sc_signal< sc_bv<4> > bus_present_state;
        
        
        
        
	void ctrl_thread(void);

	// Constructor
	SC_CTOR(CTRL) {
		SC_THREAD(ctrl_thread);
		stateregister1=new STATEREGISTER("STATEREGISTER");
		ctrllogic=new CTRLLOGIC("CTRLLOGIC");
		

		// Connections
		stateregister1->in(bus_next_state);
		stateregister1->out(bus_present_state);
		stateregister1->out1(state);
		stateregister1->clk(clk);
		ctrllogic->opcode_x(opcode);
		ctrllogic->state_x(bus_present_state);

		ctrllogic->s0_x(s0);
		ctrllogic->s1_x(s1);
		ctrllogic->mem_rd_low_x(mem_rd_low);
		ctrllogic->mem_wrt_low_x(mem_wrt_low);
		ctrllogic->ale_x(ale);
		ctrllogic->adb_wrt_x(adb_wrt);
		ctrllogic->db_wrt_x(db_wrt);
		ctrllogic->pc_wrt_x(pc_wrt);

		ctrllogic->nextstate_x(bus_next_state);
	}
};

#endif
