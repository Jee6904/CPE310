#include "Instruction.h"
/* Geoffrey McCloud
Taylor Jones
Geoffey McCloud wrote DIV.c*/
void div_reg_assm(void) {
	if (strcmp(OP_CODE, "DIV") != 0) {
		state = WRONG_COMMAND;
		return;
	}


	//check params div opcode rs rt (no rd or shamt, function=000000)

	if (PARAM1.type!=REGISTER){
		state=MISSING_REG;
		return;
	}
	if (PARAM2.type!=REGISTER){
		state=MISSING_REG;
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


	//opcode for div, this converts the opcode which is 000000
	setBits_num(31,0,6);

	//rs is the first 5 bits after the opcode, in the machine instruction I format its the first register source so it uses PARAM1 since the 
	//first register in the ASM instruction represents the first source register
	setBits_num(25,PARAM1.value,5);

	//rt is the next 5 bits, in machine inst its second source register so it uses param 2
	//since second register in ASM inst represents second source register 
	setBits_num(20,PARAM2.value,5);


	//for the function 011010 bits 5-0
	setBits_str(5, "011010");

	//finish
	state=COMPLETE_ENCODE;

}

void div_reg_bin(void) {
	//check the opcode 
	if (checkBits(31,"000000")!=0||checkBits(5,"011010")!=0){
		state = WRONG_COMMAND;
		return;
	}

	//now we convert the register bits into numbers
	uint32_t Rs= getBits(25,5);
	uint32_t Rt = getBits(20, 5);
	

	//form the ASM instruction
	setOp("DIV");
	//Purpose: sets the specified parameter to the specified type and value
	//Params: uint32_t param_num - which parameter to change
			//Param_Type type - what type to set the parameter to
			//uint32_t value - what value to set the parameter to
	//DIV rs, rt
	//first parameter is rd
	setParam(1,REGISTER,Rs);
	//second param is rs
	setParam(2,REGISTER,Rt);
	
	state=COMPLETE_DECODE;
}


