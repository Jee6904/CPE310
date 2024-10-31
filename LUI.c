#include "Instruction.h"
/*Taylor Jones
Geoffrey McCloud
Taylor wrote LUI.c*/
void lui_immd_assm(void) 
{
	if (strcmp(OP_CODE, "LUI") != 0) 
	{
		state = WRONG_COMMAND;
		return;
	}

	//Checking the parameters
	if (PARAM1.type!=REGISTER)
	{
		state=MISSING_REG;
		return;
	}

	if (PARAM2.type!=IMMEDIATE)
	{
		state=INVALID_PARAM;
		return;
	}

	if (PARAM1.value>31)
	{
		state=INVALID_REG;
		return;
	}
	
	if (PARAM2.value>0XFFFF)
	{
		state=INVALID_IMMED;
		return;
	}

	//Setting the opcode
	setBits_str(31,"001111");

	//Rt is the first parameter we have
	setBits_num(20,PARAM1.value,5);

	//Setting the immediate
	setBits_num(15, PARAM2.value,16);

	//Finish
	state=COMPLETE_ENCODE;
}

void lui_immd_bin(void) 
{
	//Checking the opcode
	if (checkBits(31,"001111")!=0)
	{
		state = WRONG_COMMAND;
		return;
	}

	//lui rt, imm

	//Converting register bits into numbers
	uint32_t Rt = getBits(20, 5);
	uint32_t Imm = getBits(15, 16);

	setOp("LUI");
		
	//First param is Rt
	setParam(1,REGISTER,Rt);
	//Second param is Imm
	setParam(2,IMMEDIATE,Imm);
	
	state=COMPLETE_DECODE;
}



