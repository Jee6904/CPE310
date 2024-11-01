#include "Instruction.h"
/* Geoffrey McCloud
Taylor Jones
Geoffey McCloud wrote SUB.c*/
void sub_reg_assm(void) {
	if (strcmp(OP_CODE, "SUB") != 0) {
		state = WRONG_COMMAND;
		return;
	}
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
	//opcode for sub is 000000
	setBits_num(31,0,6);
	//set function 100101 to bits 5-0
	setBits_str(5,"100010");
	//encode rs first after opcode which is the second param we parse in
	setBits_num(25,PARAM2.value,5);
	//encode rt which is parsed as the third param
	setBits_num(20,PARAM3.value,5);
	//encode rd which is parsed in as the first param
	setBits_num(15,PARAM1.value,5);

	state=COMPLETE_ENCODE;
}

void sub_reg_bin(void) {
	//check the opcode and the function since it selected the operation in the opcode field
	if (checkBits(31,"000000")!=0||checkBits(5,"100010")!=0){
		state = WRONG_COMMAND;
		return;
	}
	//pull register values
	uint32_t Rd = getBits(15, 5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Rs = getBits(25, 5);

	//set opcode
	setOp("SUB");
	//SUB rd,rs,rt
	setParam(1,REGISTER,Rd);
	setParam(2,REGISTER,Rs);
	setParam(3,REGISTER,Rt);
	
	state=COMPLETE_DECODE;
}


