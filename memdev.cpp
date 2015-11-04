#include "memdev.h"
#define MEMDEV_BITMASK 0xffff

void
MEMDEV::
memdev_thread(void)
{
	sc_uint<DWORD> addr_lsb_t;
	sc_uint<DWORD> addr_msb_t;
	sc_uint<AWORD> addr_t;
	sc_uint<DWORD> data_t;
	sc_uint<1> w_t;
	sc_uint<1> r_t;
	sc_uint<DWORD> data;

	while (true) {

		if (clk.read() == 1) 
		{	// Check that data must be read from mem
			r_t = r.read();
		
			if(r_t == 0) 
				{	// Read word
				addr_lsb_t = address_lsb.read();
				addr_msb_t=address_msb.read();
				addr_t=(addr_msb_t,addr_lsb_t);
				addr_t = addr_t & MEMDEV_BITMASK;

                		if (addr_t < MEMDEVSIZE) 
                			{	
						data = 0;
					
						data_t = memdevfile[addr_t];
						data=data | data_t;
						d_read.write(data);
					}
				 } 
		}
		
		if (clk.read() == 0) 
		{	// Check that data must be written to mem
			w_t = w.read();

			if(w_t == 0) 
			{	// write word to ram
				addr_lsb_t = address_lsb.read();
				addr_msb_t=address_msb.read();
				addr_t=(addr_msb_t,addr_lsb_t);
				addr_t = addr_t & MEMDEV_BITMASK;


				data = d_write.read();

				if (addr_t < MEMDEVSIZE) 
					{
						memdevfile[addr_t] = data & 0xf;
					} 
				
				else 	
					{
					cout << "WARNING: writting to invalid ";
					cout << "memory location. (";
					cout << addr_t << ")" << endl;
					}
 			} 
		}
        	wait();
	}
}

void
MEMDEV::
memdev_init(const char *filename)
{
	sc_uint<DWORD> word;
	sc_uint<AWORD> addr = 0;
	int c;

	ifstream memdevf(filename, ios::in | ios::binary);

	while (!memdevf.eof()) {
		word = 0;

		c = memdevf.get();
                if (c==-1) 
			break;

		word = c;

		memdevfile[addr] = word;
		addr++;

		if (addr >= MEMDEVSIZE)
			break;
	}
}

void
MEMDEV::
memdev_dump(const char *filename)
{
	ofstream memdevf(filename, ios::out | ios::binary);
	char c;
	sc_uint<8> a;

	for (unsigned int i = 0; i < MEMDEVSIZE; i++) {
		a = memdevfile[i];
		c = a;
		memdevf.put(c);
	}
	
	memdevf.close();
}
