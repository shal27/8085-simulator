# include "register.h"

void
REGISTER::
reg_thread(void)
{
        if( w.read() == 1)
                out.write(in.read());
        else
                out.write(out.read());
}


