# include "stateregister.h"

void
STATEREGISTER::
state_reg_thread(void)
{
 
                out.write(in.read());
                out1.write(in.read());
    
}


