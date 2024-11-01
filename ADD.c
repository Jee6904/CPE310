#include "Instruction.h"
/* Geoffrey McCloud
Taylor Jones
Geoffey McCloud wrote ADD.c*/
void add_reg_assm(void) {
	if (strcmp(OP_CODE, "ADD") != 0) {
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
	if (PARAM3.type!=REGISTER){
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
	if (PARAM3.value>31){
		state=INVALID_REG;
		return;
	}
	

	//opcode for add, this converts the opcode which is 000000 to binary and sets it at bits 31-26 of the instruction, we can use the setbits num since opcode is 0
	setBits_num(31,0,6);

	//converts function into binary which is last 6 bits which is 100000, so we start at bit 5
	setBits_str(5,"100000");
	//shamt is empty so we dont set bits for it?

	//rs is the first 5 bits after the opcode, in the machine instruction R format its the first register source so it uses PARAM2 since the 
	//second register in the ASM instruction represents the first source register
	setBits_num(25,PARAM2.value,5);

	//rt is the next 5 bits, in machine inst its second source register so it uses param 3
	//since third register in ASM add inst represents second source register 
	setBits_num(20,PARAM3.value,5);

	//rd is the next 5 bits, in machine its dest reg so we use param 1 since its the first register in the ASM inst
	setBits_num(15,PARAM1.value,5);

	//finish
	state=COMPLETE_ENCODE;


}

void add_reg_bin(void) {

	//check the opcode and the function since it selected the operation in the opcode field
	if (checkBits(31,"000000")!=0||checkBits(5,"100000")!=0){
		state = WRONG_COMMAND;
		return;
	}

	//now we convert the register bits into numbers
	uint32_t Rd = getBits(15, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Rs = getBits(25, 5);

	//form the ASM instruction
	setOp("ADD");
	//Purpose: sets the specified parameter to the specified type and value
	//Params: uint32_t param_num - which parameter to change
			//Param_Type type - what type to set the parameter to
			//uint32_t value - what value to set the parameter to
	//first parameter in ADD is rd
	setParam(1,REGISTER,Rd);
	//second param in ADD is rs
	setParam(2,REGISTER,Rs);
	//third param in ADD is rt
	setParam(3,REGISTER,Rt);
	state=COMPLETE_DECODE;
}


