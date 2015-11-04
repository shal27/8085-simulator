#include "flagreg.h"

void FLAG::flag_thread(void)
{
 sc_uint<5> t_statusflag;

 while(true)
 {
  cerr << "REGISTER" << endl;
  t_statusflag=statusflag.read();
  #ifdef VERBOSE
  cerr << "Reg (out): " << t_statusflag << endl;
  #endif

  result.write(t_statusflag);
  wait();
 }
 }
