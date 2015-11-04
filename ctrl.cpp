#include "ctrl.h"

void
CTRL::
ctrl_thread(void)
{
		op.write(opcode.read());
}
