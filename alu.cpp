#include "alu.h"
 
void
ALU::
alu_thread(void)
{
	sc_int<DWORD> t_result;
	sc_int<DWORD> t_a;
	sc_int<DWORD> t_b;
	sc_uint<9> temp;	// for carry flag
	int count;		// for parity flag
	sc_uint<5> temp2;  // for auxiliary carry flag
	sc_int<DWORD> temp1;
	sc_uint<3> t_aluctrl;
	sc_uint<5> t_flag;
	bool t_flag_carry;
	bool t_flag_auxcarry;
	bool t_flag_parity;
	bool t_flag_zero;
	bool t_flag_sign;	
	while (true) 
	{
		#ifdef VERBOSE
		cerr << "ALU" << endl;
		#endif
	
		// Read the inputs
		t_a = a.read();
		t_b = b.read();
		t_aluctrl= aluctrl.read();
		temp=0;
		count=0;

	
		// Calculate result using selected operation
		switch (t_aluctrl) {
				
			case ALU_AND:// And
				t_result = t_a & t_b;
				break;
			case ALU_OR:// Or
				t_result = t_a | t_b;
				break;
			case ALU_ADD:// Add
				{
				t_result = t_a + t_b;
				temp=t_a + t_b;
				break;
				}
			case ALU_SUB:// Subtract
				{
				t_result = t_a - t_b;
				if(t_b>t_a)
					temp=511;
				 // 9 1's in binary
	
				break;
				}
			case ALU_XOR:
				t_result=t_a ^ t_b;
				break;
			}
				

		// Calculate the zero output
		if (t_result == 0)
			t_flag_zero=1;
		else
			t_flag_zero = 0;
			
		t_flag_carry=temp.range(8,8);
		
		t_flag_sign=t_result.range(7,7);
		
		temp1=t_result;
		
		while(temp1>0)
		{
			if((temp1 % 2)==1)
				++count;
			temp1/=2;
		
		}
		if(count%2==0)
			t_flag_parity=0;
		else	t_flag_parity=1;
		
		
		temp2=t_a.range(3,0) + t_b.range(3,0);
		t_flag_auxcarry=temp2.range(4,4);
		
				
		result.write(t_result);
		t_flag=t_flag_carry+t_flag_parity*2+t_flag_auxcarry*4+t_flag_auxcarry*8+t_flag_zero*16+t_flag_sign*32;
		flag.write(t_flag);
		
		

		// Wait for next event
		wait();
	}
}
