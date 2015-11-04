#include "ctrllogic.h"

void
CTRLLOGIC::
ctrllogic_thread(void)
{
	sc_uint<8> opcode_t;
	sc_uint<4> state_t;

	while (true) {
		// Read the input
		opcode_t = opcode_x.read();
		state_t = state_x.read();

		// Determine output
		switch (state_t) {
		case 0:
			s0_x.write(1);
			s1_x.write(1);
			ale_x.write(1);
			adb_wrt_x.write(1);
			db_wrt_x.write(0x1);
			
			nextstate_x.write(1);
			break;

		case 1:
			mem_rd_low_x.write(0);
			s0_x.write(1);
			s1_x.write(1);
			ale_x.write(0);
			pc_wrt_x.write(1);
			db_wrt_x.write(1);
			
			nextstate_x.write(2);
			
			
			break;

		case 2:
			mem_rd_low_x.write(1);
			s0_x.write(1);
			s1_x.write(1);
			ale_x.write(0);
			nextstate_x.write(3);
			break;

		case 3:
			s0_x.write(1);
			s1_x.write(1);
			ale_x.write(0);
		        mem_rd_low_x.write(1);
			
			if(opcode_t==OP_LDA || opcode_t==OP_STA)
				nextstate_x.write(4);
			else
				nextstate_x.write(0);
			 
			break;
			
			
			case 4:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(1);
				adb_wrt_x.write(1);
				db_wrt_x.write(0x1);
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				nextstate_x.write(5);
			
				break;
				
			
			case 5:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(0);
				mem_rd_low_x.write(0);
				mem_wrt_low_x.write(1);
				pc_wrt_x.write(1);
				db_wrt_x.write(1);
				nextstate_x.write(6);
			
				break;
			
			case 6:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(0);
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				nextstate_x.write(7);
				
			
				break;
				
			case 7:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(1);
				adb_wrt_x.write(1);
				db_wrt_x.write(0x1);

				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				nextstate_x.write(8);
			
				break;
				
			
			case 8:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(0);
				pc_wrt_x.write(1);
				mem_rd_low_x.write(0);
				mem_wrt_low_x.write(1);
				db_wrt_x.write(1);
				nextstate_x.write(9);
			
				break;
			
			case 9:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(0);
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				if(opcode_t==OP_STA)
					nextstate_x.write(13);
				else if(opcode_t==OP_LDA)
					nextstate_x.write(10);
				
			
				break;
				
			case 10:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(1);
				adb_wrt_x.write(1);
				db_wrt_x.write(0x1);

				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				nextstate_x.write(11);
			
				break;
				
			
			case 11:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(0);
				pc_wrt_x.write(1);
				mem_rd_low_x.write(0);
				mem_wrt_low_x.write(1);
				db_wrt_x.write(1);
				nextstate_x.write(12);
			
				break;
			
			case 12:
				
				s0_x.write(0);
				s1_x.write(1);
				ale_x.write(0);
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				
				if(opcode_t==OP_STA)
					nextstate_x.write(13);
				else if(opcode_t==OP_LDA)
					nextstate_x.write(0);
				
			
				break;
				
			case 13:
				
				s0_x.write(1);
				s1_x.write(0);
				ale_x.write(1);
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				adb_wrt_x.write(1);
				db_wrt_x.write(0x1);
				
				nextstate_x.write(14);
			
				break;
				
			case 14:
				s0_x.write(1);
				s1_x.write(0);
				ale_x.write(0);
				
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(1);
				break;
				
			case 15:
				s0_x.write(1);
				s1_x.write(0);
				ale_x.write(0);
				
				mem_rd_low_x.write(1);
				mem_wrt_low_x.write(0);
				break;
			}

		// wait for new event
		wait(); 
	}
}
