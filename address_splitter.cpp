#include "address_splitter.h"

void address_splitter::address_splitter_thread(void)
{
	
	sc_uint<16> in_t;	//input 16 bit address
	sc_uint<8> temp;
	
	
	while(true)
	{
		in_t=in.read();
		
		temp=in_t & 255;
		
		out1.write(temp);
		temp=in_t & 65280;
		temp=temp>>8;
		out2.write(temp);
		
		wait();
	}
}
