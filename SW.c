#include "Instruction.h"
/*Taylor Jones
Geoffrey McCloud
Taylor wrote SW.c*/

void sw_immd_assm(void) 
{
	if (strcmp(OP_CODE, "SW") != 0) 
	{
		state = WRONG_COMMAND;
		return;
	}

    //Checking the parameters
	if (PARAM1.type!=REGISTER){
		state=MISSING_REG;
		return;
	}

	if (PARAM2.type!=IMMEDIATE){
		state=INVALID_PARAM;
		return;
	}

    if (PARAM3.type!=REGISTER)
	{
        state=MISSING_REG;
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

    if (PARAM3.value>31)
	{
        state=INVALID_REG;
        return;
    }

    //Setting the opcode
	setBits_str(31,"101011");

	//Setting rs
	setBits_num(25,PARAM1.value,5);
	//Setting rt
	setBits_num(20,PARAM3.value,5);
    //Setting the immediate
    setBits_num(15, PARAM2.value,16);

	//Finish
	state=COMPLETE_ENCODE;
}

void sw_immd_bin(void) 
{
	//Checking the opcode 
	if (checkBits(31,"101011")!=0)
	{
		state = WRONG_COMMAND;
		return;
	}

    //Converting register bits into numbers
	uint32_t Rs = getBits(25,5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Imm = getBits(15,16);

	setOp("SW");
	
	//sw rt imm(rs)

	//First parameter is rs
	setParam(1,REGISTER,Rs);
    //Second param is immediate
    setParam(2,IMMEDIATE,Imm);
	//Third param is rt
	setParam(3,REGISTER,Rt);
	
	state=COMPLETE_DECODE;
}