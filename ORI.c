#include "Instruction.h"
/*Taylor Jones
Geoffrey McCloud
Taylor wrote ORI.c*/
void ori_immd_assm(void) 
{
	if (strcmp(OP_CODE, "ORI") != 0) 
	{
		state = WRONG_COMMAND;
		return;
	}

	if (PARAM1.type!=REGISTER)
	{
		state=MISSING_REG;
		return;
	}

	if (PARAM2.type!=REGISTER)
	{
		state=MISSING_REG;
		return;
	}

	if (PARAM3.type!=IMMEDIATE)
	{
		state=INVALID_PARAM;
		return;
	}

	if (PARAM1.value>31)
	{
		state=INVALID_REG;
		return;
	}

	if (PARAM2.value>31)
	{
		state=INVALID_REG;
		return;
	}

	if (PARAM3.value>0XFFFF)
	{
		state=INVALID_IMMED;
		return;
	}
	
	//Setting the opcode
	setBits_str(31, "001101");

	//Rs is the second parameter
	setBits_num(25,PARAM2.value,5);
	//Rt is the first parameter
	setBits_num(20,PARAM1.value,5);
	//Setting the immediate
	setBits_num(15,PARAM3.value,16);

	state=COMPLETE_ENCODE;
}

void ori_immd_bin(void) 
{
	//Checking the opcode
	if (checkBits(31,"001101")!=0)
	{
		state = WRONG_COMMAND;
		return;
	}

	//ori rt, rs, imm

	//Converting register bits into numbers
	uint32_t Rs = getBits(25, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Imm = getBits(15, 5);

	//Set opcode
	setOp("ORI");
	
	//First param is Rt
	setParam(1,REGISTER,Rt);
	//Second param is Rs
	setParam(2,REGISTER,Rs);
	//Third param is Imm
	setParam(3,IMMEDIATE, Imm);
	
	state=COMPLETE_DECODE;
}



