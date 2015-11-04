#include "idb.h"

void idb::idb_thread(void)
{

	sc_uint<8> opcode_t;
	sc_uint<5> flip_t;
	sc_uint<8> acc_t;
	sc_uint<8> temp_t;
	sc_uint<8> alu_data_t;
	sc_uint<3> aluop_t;
	sc_uint<8> instr_reg_t;
	sc_uint<8> reg_file_data_t;
	sc_uint<2> reg_rd_select_t;
	sc_uint<8> ad_buff_t;
	sc_uint<4> state_t;
	
	while(true)
	{
		state_t=state.read();
		if(state_t==0x3)
		{
		
		
		opcode_t=opcode.read();
		
		switch(opcode_t)
		{
		case OP_ADD_B:
			
				reg_rd_select.write(REG_B);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_ADD);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		
		case OP_ADD_H:
			
				reg_rd_select.write(REG_H);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_ADD);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		case OP_SUB_B:
			
				reg_rd_select.write(REG_B);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_SUB);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		
		case OP_SUB_H:
			
				reg_rd_select.write(REG_H);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_SUB);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;	
		case OP_XRA_B:
			
				reg_rd_select.write(REG_B);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_XOR);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		case OP_XRA_H:
			
				reg_rd_select.write(REG_H);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_XOR);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		
		case OP_ANA_B:
			
				reg_rd_select.write(REG_B);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_AND);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		case OP_ANA_H:
			
				reg_rd_select.write(REG_H);
				reg_file_data_t=reg_file_data_in.read();
				temp.write(reg_file_data_t);
				w_temp.write(1);
				aluop.write(ALU_AND);
				
				
				alu_data_t=alu_data.read();
				w_acc.write(1);
				acc_out.write(alu_data_t);
				break;
		case OP_MOV_A_B:
			
				reg_rd_select.write(REG_B);
				reg_file_data_t=reg_file_data_in.read();
				w_acc.write(1);
				acc_out.write(reg_file_data_t);
				break;		
		case OP_MOV_A_H:
			
				reg_rd_select.write(REG_H);
				reg_file_data_t=reg_file_data_in.read();
				w_acc.write(1);
				acc_out.write(reg_file_data_t);
				break;	
		
		case OP_MOV_A_C:
			
				reg_rd_select.write(REG_C);
				reg_file_data_t=reg_file_data_in.read();
				w_acc.write(1);
				acc_out.write(reg_file_data_t);
				break;	
		
		case OP_MOV_B_A:
			
				acc_t=acc_in.read();
				reg_wrt_select.write(REG_B);
				w_regfile.write(1);
				reg_file_data_out.write(acc_t);
				break;	
		
		case OP_MOV_H_A:
			
				acc_t=acc_in.read();
				reg_wrt_select.write(REG_H);
				w_regfile.write(1);
				reg_file_data_out.write(acc_t);
				break;	
		
		case OP_MOV_B_C:
			
				reg_rd_select.write(REG_C);
				reg_file_data_t=reg_file_data_in.read();
				reg_wrt_select.write(REG_B);
				w_regfile.write(1);
				reg_file_data_out.write(reg_file_data_t);
				break;		
		
		case OP_MOV_B_H:
			
				reg_rd_select.write(REG_H);
				reg_file_data_t=reg_file_data_in.read();
				reg_wrt_select.write(REG_B);
				w_regfile.write(1);
				reg_file_data_out.write(reg_file_data_t);
				break;	
				
		case OP_MOV_H_B:
			
				reg_rd_select.write(REG_B);
				reg_file_data_t=reg_file_data_in.read();
				reg_wrt_select.write(REG_H);
				w_regfile.write(1);
				reg_file_data_out.write(reg_file_data_t);	
				break;
		
		case OP_MOV_H_C:
			
				reg_rd_select.write(REG_C);
				reg_file_data_t=reg_file_data_in.read();
				reg_wrt_select.write(REG_H);
				w_regfile.write(1);
				reg_file_data_out.write(reg_file_data_t);
				break;			
	 	}
	 	}
	 	
	 	else if(state_t==0x2)
	 	{
	 		
	 		ad_buff_t=ad_buff_in.read();
	 		
	 		w_instr_reg.write(1);
	 		instr_reg.write(ad_buff_t);
	 	}
	 	
	 	else if(state_t==0x14)
	 	{
	 		acc_t=acc_in.read();
	 		w_ad_buff.write(1);
	 		ad_buff_out.write(acc_t);
	 	}
	 	
	 	else if(state_t==0x12)
	 	{
	 		ad_buff_t=ad_buff_in.read();
	 		w_acc.write(1);
	 		acc_out.write(ad_buff_t);
	 	}
	 		
wait();
}
}


