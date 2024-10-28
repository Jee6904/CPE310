#include "Instruction.h"
/* Geoffrey McCloud
Taylor 
Geoffey McCloud wrote BEQ.c*/
void beq_immd_assm(void) {
	if (strcmp(OP_CODE, "BEQ") != 0) {
		state = WRONG_COMMAND;
		return;
	}
	

	//check params 

	if (PARAM1.type!=REGISTER){
		state=MISSING_REG;
		return;
	}
	if (PARAM2.type!=REGISTER){
		state=MISSING_REG;
		return;
	}
	if (PARAM3.type!=IMMEDIATE){
		state=INVALID_PARAM;
		return;
	}

	//Since registers are numbered 0-31 there shouldnt be any that are mroe than that 
	if (PARAM1.value>31){
		state=INVALID_REG;
		return;
	}
	if (PARAM2.value>31){
		state=INVALID_REG;
		return;
	}
	//Immediate can only be 16 bits 2^16-1=FFFF
	if (PARAM3.value>0XFFFF){
		state=INVALID_IMMED;
		return;
	}

	//opcode for add, this converts the opcode which is 000100
	setBits_str(31,"000100");


	//rs is the first 5 bits after the opcode, in the machine instruction I format its the first register source so it uses PARAM2 since the 
	//second register in the ASM instruction represents the first source register
	setBits_num(25,PARAM2.value,5);

	//rt is the next 5 bits, in machine inst its second source register so it uses param 3
	//since third register in ASM beq inst represents second source register 
	setBits_num(20,PARAM2.value,5);

	//next 16 bits are the immediate 
	setBits_num(15, PARAM3.value,16);

	//finish
	state=COMPLETE_ENCODE;

}

void beq_immd_bin(void) {
	//check the opcode 
	if (checkBits(31,"000100")!=0){
		state = WRONG_COMMAND;
		return;
	}

	//now we convert the register bits into numbers
	uint32_t Rs= getBits(25,5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Immm = getBits(15, 16);

	//form the ASM instruction
	setOp("BEQ");
	//Purpose: sets the specified parameter to the specified type and value
	//Params: uint32_t param_num - which parameter to change
			//Param_Type type - what type to set the parameter to
			//uint32_t value - what value to set the parameter to
	//beq rs, rt, immm
	//first parameter is rd
	setParam(1,REGISTER,Rs);
	//second param is rs
	setParam(2,REGISTER,Rt);
	//third param in ADD is rt
	setParam(3,IMMEDIATE,Rt);

	state=COMPLETE_DECODE;
}



