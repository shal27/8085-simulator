#include "mux2_1bit.h"

void
MUX2_1BIT::
mux2_1bit_thread(void)
{
	sc_bv<1> data;

	while (true) {
		#ifdef VERBOSE
		cerr << "MUX" << endl;
		#endif

		// Read correct input
		if(sel.read() == 0)
			data = in0.read();
		else
			data = in1.read();

		// Write output
		out.write(data);

		// wait for new event
		wait();
	}
}


