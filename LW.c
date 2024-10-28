#include "Instruction.h"
/* Geoffrey McCloud
Taylor Jones
Geoffey McCloud wrote LW.c*/
void lw_immd_assm(void) {
	if (strcmp(OP_CODE, "LW") != 0) {
		state = WRONG_COMMAND;
		return;
	}

    //check params rd, immm(rs)

	if (PARAM1.type!=REGISTER){
		state=MISSING_REG;
		return;
	}
	if (PARAM2.type!=IMMEDIATE){
		state=INVALID_PARAM;
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
	if (PARAM2.value>0XFFFF){
		state=INVALID_IMMED;
		return;
	}
    if (PARAM3.value>31){
        state=INVALID_REG;
        return;
    }

    //lw opcode rs rt offset
	//opcode for div, this converts the opcode which is 100011
	setBits_str(31,"100011");

	//rs is the first 5 bits after the opcode, in the machine instruction I format its the first register source so it uses PARAM1 since the 
	//first register in the ASM instruction represents the first source register
	setBits_num(25,PARAM1.value,5);

	//rt is the next 5 bits, in machine inst its second source register so it uses param 3
	//since second register in ASM inst represents second source register 
	setBits_num(20,PARAM3.value,5);

    //immediate last 15 bits, this gets parsed in after first parameter so we use param 2
    setBits_num(15, PARAM2.value,16);


	//finish
	state=COMPLETE_ENCODE;

}

void lw_immd_bin(void) {
	//check the opcode 
	if (checkBits(31,"100011")!=0){
		state = WRONG_COMMAND;
		return;
	}
    //now we convert the register bits into numbers
	uint32_t Rs= getBits(25,5);
	uint32_t Rt = getBits(20, 5);
	uint32_t Immm=getBits(15,16);

	//form the ASM instruction
	setOp("LW");
	//Purpose: sets the specified parameter to the specified type and value
	//Params: uint32_t param_num - which parameter to change
			//Param_Type type - what type to set the parameter to
			//uint32_t value - what value to set the parameter to
	//DIV rt, immm(rs)
	//first parameter is rd
	setParam(1,REGISTER,Rt);
    //second param is immediate
    setParam(2,IMMEDIATE,Immm);
	//third param is rs
	setParam(3,REGISTER,Rs);
	
	state=COMPLETE_DECODE;
}