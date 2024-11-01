#include "Instruction.h"
/* Geoffrey McCloud
Taylor Jones
Geoffey McCloud wrote MFLO.c*/
void mflo_reg_assm(void) {
	if (strcmp(OP_CODE, "MFLO") != 0) {
		state = WRONG_COMMAND;
		return;
	}

	//checks for rd
	if (PARAM1.type!=REGISTER){
		state=MISSING_REG;
		return;
	}

	if (PARAM1.value>31){
		state=INVALID_REG;
		return;
	}
	//opcode for mflo, this converts the opcode which is 000000
	setBits_num(31,0,6);
	//set our funnction 010010 to bits 5-0
	setBits_str(5,"010010");
	//rd is our only parameter and is set from bits 15-11
	setBits_num(15,PARAM1.value,5);

	state=COMPLETE_ENCODE;
}

void mflo_reg_bin(void) {
	//check opcode and function
	if (checkBits(31,"000000")!=0||checkBits(5,"010010")!=0){
		state = WRONG_COMMAND;
		return;
	}
	uint32_t Rd= getBits(15,5);
	setOp("MFLO");
	setParam(1, REGISTER,Rd);
	state=COMPLETE_DECODE;
}


