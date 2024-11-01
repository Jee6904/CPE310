#include "Instruction.h"
/*Taylor Jones
Geoffrey McCloud
Taylor wrote MFHI.c*/
void mfhi_reg_assm(void) 
{
	if (strcmp(OP_CODE, "MFHI") != 0) 
	{
		state = WRONG_COMMAND;
		return;
	}

	//Check for parameter
	if (PARAM1.type!=REGISTER)
	{
		state=MISSING_REG;
		return;
	}

	if (PARAM1.value>31)
	{
		state=INVALID_REG;
		return;
	}

	//Setting opcode (000000)
	setBits_num(31,0,6);

	//Setting the function
	setBits_str(5,"010000");

	//Setting rd as the only parameter
	setBits_num(15,PARAM1.value,5);

	state=COMPLETE_ENCODE;
}

void mfhi_reg_bin(void) 
{
	//Checking the opcode and function
	if (checkBits(31,"000000")!=0||checkBits(5,"010000")!=0)
	{
		state = WRONG_COMMAND;
		return;
	}

	uint32_t Rd= getBits(15,5);
	setOp("MFHI");
	setParam(1, REGISTER,Rd);
	
	state=COMPLETE_DECODE;
}


