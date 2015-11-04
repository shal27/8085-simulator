# include "pc.h"

void
PC::
pc_thread(void)
{
	sc_uint<16> t;
        if( w.read() == 1)
                {
                t=in.read();
                t++;
                out.write(t);
                }		//increment pc by 1
                
        else
                out.write(out.read());
}

