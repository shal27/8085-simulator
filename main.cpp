#include "alu.h"
#include "registerfile.h"
#include "idb.h"
#include "pc.h"
#include "ctrl.h"
#include "memdev.h"
#include "register.h"
#include "flagreg.h"
#include "address_splitter.h"
#include "mux3.h"
#include "mux_select.h"
#include "mux2_1bit.h"


int sc_main(int argc, char *argv[])
{
	//char stbuf[256];
	sc_report_handler::
	set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	
	//data signals
	sc_signal<sc_bv<3> >idb_aluop_s;
 	sc_signal<sc_bv<8> >acc_out_s;
 	sc_signal<sc_bv<8> >idb_acc_out_s;
	sc_signal<sc_bv<8> >temp_out_s;
	sc_signal<sc_bv<5> >alu_flag_s;
	sc_signal<sc_bv<8> >idb_temp_s;
	sc_signal<sc_bv<16> >pc_out_s;
	sc_signal<sc_bv<8> >multi2_s;
	sc_signal<sc_bv<8> >address_splitter_ob_out2_s;
	sc_signal<sc_bv<8> >address_splitter_ob_out1_s;
	sc_signal<sc_bv<8> >address_buffer_out_s;
	sc_signal<sc_bv<8> >idb_instr_reg_s;
	sc_signal<sc_bv<8> >ir_out_s;
	sc_signal<sc_bv<4> >ctrl_state_s;
	sc_signal<sc_bv<8> >ctrl_op_s;	
	sc_signal<sc_bv<5> >flag_result_s;
	sc_signal<sc_bv<8> >alu_result_s;
	sc_signal<sc_bv<8> >idb_ad_buff_s;
	sc_signal<sc_bv<2> >idb_reg_wrt_select_s;
	sc_signal<sc_bv<2> >idb_reg_rd_select_s;
	sc_signal<sc_bv<4> >mux_select_input_s;
	sc_signal<sc_bv<8> >mux1_output_s;
	sc_signal<sc_bv<8> >memdev_d_read_s;
	sc_signal<sc_bv<8> >idb_reg_file_data_out_s;
	sc_signal<sc_bv<8> >regfile_r_data_reg1_s;
	
	
	//control signals
	sc_signal<sc_bv<1> >idb_w_temp_s;
	sc_signal<sc_bv<1> >idb_w_reg_file_s;
	sc_signal<sc_bv<1> >ctrl_adb_wrt_s;
	sc_signal<sc_bv<1> >ctrl_pc_wrt_s;
	sc_signal<sc_bv<1> >ctrl_ale_s;
	sc_signal<sc_bv<1> >idb_w_instr_reg_s;
	sc_signal<sc_bv<1> >ctrl_mem_wrt_low_s;
	sc_signal<sc_bv<1> >ctrl_mem_rd_low_s;
	sc_signal<sc_bv<1> >ctrl_s0_s;
	sc_signal<sc_bv<1> >ctrl_s1_s;
	sc_signal<sc_bv<1> >idb_w_ad_buff_s;
	sc_signal<sc_bv<1> >idb_w_acc_s;
	sc_signal<sc_bv<2> >mux_select_out1_s;
	sc_signal<sc_bv<1> >ctrl_db_wrt_s;
	sc_signal<sc_bv<1> >mux_select_out2_s;
	sc_signal<sc_bv<1> >mux2_output_s;
	
		
	//clock
	sc_clock clock("clock",20); 

	// instantiation
	ALU alu("ALU");
	FLAG flag("FLAG");
	idb idb_ob("idb");
	CTRL ctrl("CTRL");
	MEMDEV memdev("MEMDEV");
	PC pc("PC");
	address_splitter address_splitter_ob("address_splitter");
	REGFILE regfile("REGFILE");
	REGISTER acc("REGISTER1");
	REGISTER temp("REGISTER2");
	REGISTER ir("REGISTER3");
	REGISTER address_buffer("REGISTER4");
	REGISTER address_data_buffer("REGISTER5");
	MUX3 mux1("MUX1");
	MUX2_1BIT mux2("MUX2");
	mux_select mux_select_ob("mux_selection");
	
	//signalling
	alu.aluctrl(idb_aluop_s);
	alu.a(acc_out_s);
	alu.b(temp_out_s);
	alu.result(alu_result_s);
	alu.flag(alu_flag_s);
	
	flag.statusflag(alu_flag_s);
	flag.result(flag_result_s);
	
	temp.in(idb_temp_s);
	temp.w(idb_w_temp_s);
	temp.clk(clock);
	temp.out(temp_out_s);
	
	acc.in(idb_acc_out_s);
	acc.w(idb_w_acc_s);
	acc.clk(clock);
	acc.out(acc_out_s);
	
	
	address_splitter_ob.in(pc_out_s);
	address_splitter_ob.out1(address_splitter_ob_out1_s);
	address_splitter_ob.out2(address_splitter_ob_out2_s);
	
	
	address_buffer.in(address_splitter_ob_out1_s);
	address_buffer.w(ctrl_adb_wrt_s);
	address_buffer.clk(clock);
	address_buffer.out(address_buffer_out_s);
	
	
	address_data_buffer.in(mux1_output_s);
	address_data_buffer.w(mux2_output_s);
	address_data_buffer.clk(clock);
	address_data_buffer.out(multi2_s);
	
	memdev.address_lsb(multi2_s);
	memdev.address_msb(address_buffer_out_s);
	memdev.d_write(multi2_s);
	memdev.w(ctrl_mem_wrt_low_s);
	memdev.r(ctrl_mem_rd_low_s);
        memdev.clk(clock);
        memdev.s0(ctrl_s0_s);
        memdev.s1(ctrl_s1_s);
        memdev.d_read(memdev_d_read_s);
        
        ir.in(idb_instr_reg_s);
        ir.w(idb_w_instr_reg_s);
        ir.clk(clock);
        ir.out(ir_out_s);
        
        
        ctrl.opcode(ir_out_s);
        ctrl.clk(clock);
        ctrl.s0(ctrl_s0_s);
        ctrl.s1(ctrl_s1_s);
        ctrl.mem_rd_low(ctrl_mem_rd_low_s);
        ctrl.mem_wrt_low(ctrl_mem_wrt_low_s);
        ctrl.ale(ctrl_ale_s);
        ctrl.state(ctrl_state_s);
        ctrl.op(ctrl_op_s);
        ctrl.pc_wrt(ctrl_pc_wrt_s);
        ctrl.db_wrt(ctrl_db_wrt_s);
        ctrl.adb_wrt(ctrl_adb_wrt_s);
        
        
        idb_ob.opcode(ctrl_op_s);
        idb_ob.acc_in(acc_out_s);
        idb_ob.acc_out(idb_acc_out_s);    
        idb_ob.flip_flop(flag_result_s); 
        idb_ob.alu_data(alu_result_s);
        idb_ob.reg_file_data_out(idb_reg_file_data_out_s);
        idb_ob.reg_file_data_in(regfile_r_data_reg1_s);
        idb_ob.ad_buff_out(idb_ad_buff_s);
        idb_ob.ad_buff_in(multi2_s);
        idb_ob.state(ctrl_state_s);
        idb_ob.w_regfile(idb_w_reg_file_s);
        idb_ob.w_instr_reg(idb_w_instr_reg_s);
        idb_ob.w_temp(idb_w_temp_s);
        idb_ob.w_acc(idb_w_acc_s) ;
        idb_ob.w_ad_buff(idb_w_ad_buff_s);
        idb_ob.reg_wrt_select(idb_reg_wrt_select_s);
        idb_ob.aluop(idb_aluop_s);
        idb_ob.reg_rd_select(idb_reg_rd_select_s);              
	idb_ob.instr_reg(idb_instr_reg_s);
	idb_ob.temp(idb_temp_s);
	
	regfile.r_addr_reg1(idb_reg_rd_select_s);
	regfile.w_addr_reg(idb_reg_wrt_select_s);
	regfile.w(idb_w_reg_file_s);
	regfile.clk(clock);
	regfile.w_data_reg(idb_reg_file_data_out_s);
	regfile.r_data_reg1(regfile_r_data_reg1_s);
	
	pc.in(pc_out_s);
	pc.w(ctrl_pc_wrt_s);
	pc.clk(clock);
	pc.out(pc_out_s);
	
	mux_select_ob.in1(ctrl_state_s);
	mux_select_ob.out1(mux_select_out1_s);
	mux_select_ob.out2(mux_select_out2_s);
	
	mux1.in0(idb_ad_buff_s);
	mux1.in1(address_splitter_ob_out1_s);
	mux1.sel(mux_select_out1_s);
	mux1.in2(memdev_d_read_s);
	mux1.out(mux1_output_s);
	
	mux2.in0(idb_w_ad_buff_s);
	mux2.in1(ctrl_db_wrt_s);
	mux2.sel(mux_select_out2_s);
	mux2.out(mux2_output_s);
	
	
	cerr << "Connections OK";

	//Initialization
	memdev.memdev_init("mp.bin");
	cerr << "Memory OK";

	// Tracing
	sc_trace_file *tf;
	tf = sc_create_vcd_trace_file("mp.vcd");
	cerr << "TraceFile OK";

	// Signals
	sc_trace(tf, clock, "clock");
	sc_trace(tf, idb_aluop_s, "aluop");
	sc_trace(tf, temp_out_s, "temp_reg");
	sc_trace(tf, alu_result_s, "alu_result");
	sc_trace(tf, alu_flag_s, "flag_result");
	sc_trace(tf, pc_out_s, "pc_out");
	sc_trace(tf, multi2_s, "data_buffer");
	sc_trace(tf, address_splitter_ob_out2_s, "address_msb");
	sc_trace(tf, address_splitter_ob_out1_s, "address_lsb");
	sc_trace(tf, idb_instr_reg_s, "instruction_register");
	sc_trace(tf, ctrl_state_s, "current_state");
	sc_trace(tf, flag_result_s, "flag_register_content");
	sc_trace(tf, ctrl_s0_s, "s0");
	sc_trace(tf, ctrl_s1_s, "s1");
	sc_trace(tf, ctrl_ale_s, "ale");
	sc_trace(tf, ctrl_mem_wrt_low_s, "write_low");
	sc_trace(tf, ctrl_mem_rd_low_s, "read_low");
	
	/*for (int i = 0; i < REGSIZE; i++) {
		sprintf(stbuf, "REGFILE.reg(%d)", i);
		sc_trace(tf, regfile.rfile[i], stbuf);
	}

	for (int i = 0; i < MEMDEVSIZE; i++) {
		sprintf(stbuf, "MEMDEV.dmem(%d)", i);
		sc_trace(tf, memdev.memdevfile[i], stbuf);
	}
*/
	cerr << "Tracing OK";
	// Simulation
	int sim_time = 2000;
	if (argc == 2)
		sim_time = atoi(argv[1]);

	sc_start(sim_time, SC_NS);
	sc_close_vcd_trace_file(tf);
	memdev.memdev_dump("mp.dump");

	return 0;
}
	
	
	
        	


