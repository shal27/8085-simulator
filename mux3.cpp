#include "mux3.h"

void
MUX3::
mux3_thread(void)
{
	sc_bv<DWORD> data;

	while (true) {
		#ifdef VERBOSE
		cerr << "MUX" << endl;
		#endif

		// Read correct input
		if(sel.read() == 0)
			data = in0.read();
		else if(sel.read() ==1)
			data = in1.read();
		else
			data=in2.read();

		// Write output
		out.write(data);

		// wait for new event
		wait();
	}
}


