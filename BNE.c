#include "Instruction.h"
/*Taylor Jones
Geoffrey McCloud
Taylor wrote BNE.c*/
void bne_immd_assm(void) 
{
	if (strcmp(OP_CODE, "BNE") != 0) 
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

	if (PARAM1.value>31){
		state=INVALID_REG;
		return;
	}

	if (PARAM2.value>31){
		state=INVALID_REG;
		return;
	}
	
	if (PARAM3.value>0XFFFF){
		state=INVALID_IMMED;
		return;
	}

	//Setting the opcode
	setBits_str(31,"000101");

	//rs
	setBits_num(25,PARAM2.value,5);

	//rt
	setBits_num(20,PARAM2.value,5);

	//Setting the immediate
	setBits_num(15, PARAM3.value,16);

	//Finish
	state=COMPLETE_ENCODE;
}

void bne_immd_bin(void) 
{
	//Checking the opcode 
	if (checkBits(31,"000101")!=0)
	{
		state = WRONG_COMMAND;
		return;
	}

	//Converting register bits into numbers
	uint32_t Rs= getBits(25,5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Imm = getBits(15, 16);

	setOp("BNE");
	
	//bne rs, rt, imm

	//First param is Rs
	setParam(1,REGISTER,Rs);
	//Second param is Rt
	setParam(2,REGISTER,Rt);
	//Third param is Imm
	setParam(3,IMMEDIATE,Imm);

	state=COMPLETE_DECODE;
}



