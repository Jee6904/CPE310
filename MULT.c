#include "Instruction.h"
/* Taylor Jones
Geoffrey McCloud
Taylor wrote MULT.c
*/
void mult_reg_assm(void) 
{
	if (strcmp(OP_CODE, "MULT") != 0) 
	{
		state = WRONG_COMMAND;
		return;
	}

	//Check parameters
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

	//Converts opcode to 000000
	setBits_num(31,0,6);

	//Setting the bits
	setBits_num(25,PARAM1.value,5);
	setBits_num(20,PARAM2.value,5);

	//For the function 011000 bits 5-0
	setBits_str(5, "011000");

	//Finish
	state=COMPLETE_ENCODE;
}

void mult_reg_bin(void) 
{
	//Check the opcode 
	if (checkBits(31,"000000")!=0)
	{
		state = WRONG_COMMAND;
		return;
	}

	//Converting the register bits into numbers
	uint32_t Rs= getBits(25,5);
	uint32_t Rt = getBits(20, 5);
	
	setOp("MULT");
	
	//MULT rs, rt
	
	//First param is Rs
	setParam(1,REGISTER,Rs);
	
	//Second param is Rt
	setParam(2,REGISTER,Rt);
	
	state=COMPLETE_DECODE;
}


