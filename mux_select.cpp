#include "mux_select.h"

void mux_select::mux_select_thread(void)
{

	sc_bv<4> in1_t;
	
	while(true)
	{
		if(in1_t==0 || in1_t==4 || in1_t==7 || in1_t==10 || in1_t==13)
				out1.write(1);
		else if(in1_t==1 || in1_t==5 || in1_t==8 || in1_t==11 || in1_t==14)
		 	out1.write(2);
		 else out1.write(0);
		 
		 if(in1_t==14)
		 	out2.write(0);
		 else out2.write(1);
		 wait();
	}
}
		
				
