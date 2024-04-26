#include <stdio.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 1024
#define MAX_REGS_COUNT 4

bool running = true;
int pc = 0, sp = -1;
int stack[MAX_STACK_SIZE];
int regs[MAX_REGS_COUNT];

typedef enum {
	A,
	B,
	C,
	D,
} Register;

typedef enum {
	PSH,
	POP,
	ADD,
	SUB,
	MUL,
	DIV,
	DIS,
	DTOP,
	SET,
	MOV,
	LOAD,
	TRN,
	HLT
} InstructionSet;

const int program[] = {
	PSH, 5,
	PSH, 6,
	ADD,
	DTOP,
	PSH, 3,
	PSH, 6,
	DTOP,
	ADD,
	ADD,
	PSH, 5,
	PSH, 7,
	DTOP,
	POP,
	SUB,
	DTOP,
	DIS, A,
	DIS, B,
	SET, A, 13,
	MOV, A, B,
	DIS, A,
	DIS, B,
	SET, A, 5,
	DIS, A,
	DIS, B,
	LOAD, B,
	LOAD, A,
	DIV,
	DTOP,
	TRN, A,
	DIS, A,
	HLT
};

int fetch()
{
	int instructionToExecute = program[pc];
	pc++;
	return instructionToExecute;
}

bool check_overflow()
{
	if(sp >= MAX_STACK_SIZE-1) {
		printf("STACK OVERFLOW\n");
		return true;
	}
	return false;
}

bool check_underflow()
{
	if(sp < 0) {
		printf("STACK UNDERFLOW\n");
		return true;
	}
	return false;
}

char register_to_char(Register reg)
{
	return reg + 'A'; 
}

bool eval_psh_instr()
{
	if(check_overflow()) return false;
	sp++;
	stack[sp] = program[pc++];
	return true;
}


bool eval_load_instr(Register reg)
{
	if(check_overflow()) return false;
	sp++;
	stack[sp] = regs[reg];
	return true;
}

bool eval_pop_instr()
{
	if(check_underflow()) return false;
	sp--;
	return true;
}

bool eval_dtop_instr()
{
	if(sp > -1 && sp < MAX_STACK_SIZE) {
		printf("TOP OF THE STACK: %d\n", stack[sp]);
		return true;
	}
	return false;
}

bool eval_set_instr() 
{
	int regIndex = program[pc++];
	int val = program[pc++];
	regs[regIndex] = val;
	return true;
}

bool eval_mov_instr() 
{
	int srcRegIndex = program[pc++];
	int dstRegIndex = program[pc++];
	regs[dstRegIndex] = regs[srcRegIndex];
	return true;
}

bool eval_dis_instr() 
{
	int regIndex = program[pc++];
	printf("REG: %c VAlUE: %d\n", register_to_char(regIndex), regs[regIndex]);
	return true;
}

bool eval_hlt_instr() 
{
	running = false;
	return true;
}

bool eval_arithmetic_expression(InstructionSet operator) 
{
	if(check_underflow()) return false;
	int secondOperand = stack[sp];
	sp--;
	if(check_underflow()) return false;
	int firstOperand = stack[sp];
	switch (operator) 
	{
		case ADD: stack[sp] = firstOperand + secondOperand;
			  break;
		case SUB: stack[sp] = firstOperand - secondOperand;
			  break;
		case MUL: stack[sp] = firstOperand * secondOperand;
			  break;
		case DIV: stack[sp] = firstOperand / secondOperand;
			  break;
		default: return false;
	}
	return true;
} 

bool eval_trn_instr(Register reg)
{
	if(check_underflow()) return false;
	regs[reg] = stack[sp];
	return true;

}

bool execute(InstructionSet instr)
{
	switch(instr)
	{
		case PSH: return eval_psh_instr();
		case POP: return eval_pop_instr();
		case ADD: return eval_arithmetic_expression(ADD);
		case SUB: return eval_arithmetic_expression(SUB);
		case MUL: return eval_arithmetic_expression(MUL);
		case DIV: return eval_arithmetic_expression(DIV);
		case DTOP:return eval_dtop_instr();
		case LOAD:return eval_load_instr(program[pc++]);
		case SET: return eval_set_instr();
		case MOV: return eval_mov_instr();
		case TRN: return eval_trn_instr(program[pc++]);
		case DIS: return eval_dis_instr();
		case HLT: return eval_hlt_instr();
		default: return false;
	}

	return false;
}



int main()
{
	while(running) 
	{
		bool state = execute(fetch());
		if(state == false)
		{
			printf("ABNORMAL SUSPENSION\n");
			return -1;
		}
	}
	return 0;
}

