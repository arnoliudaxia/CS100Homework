#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>


int registers[5] = { 0,0,0,0,0 };
//char *instructions[20] ;
int tonegletelines = 0;
int instructions[20][4];//add ~ div 1~4 let 5 beg 6 print 7
int main()
{
	int looptimes = 0;
	scanf("%d", &looptimes);
	//load RAM
	for (size_t i = 0; i < looptimes; i++)
	{
		char instruction[8];
		scanf("%s ", instruction);
		if (strcmp(instruction, "add") == 0)
		{
			instructions[i][0] = 1;
			scanf("x%d x%d x%d", &instructions[i][1], &instructions[i][2], &instructions[i][3]);
		}
		if (strcmp(instruction, "sub") == 0)
		{
			instructions[i][0] = 2;
			scanf("x%d x%d x%d", &instructions[i][1], &instructions[i][2], &instructions[i][3]);
		}
		if (strcmp(instruction, "mul") == 0)
		{
			instructions[i][0] = 3;
			scanf("x%d x%d x%d", &instructions[i][1], &instructions[i][2], &instructions[i][3]);
		}
		if (strcmp(instruction, "div") == 0)
		{
			instructions[i][0] = 4;
			scanf("x%d x%d x%d", &instructions[i][1], &instructions[i][2], &instructions[i][3]);
		}
		if (strcmp(instruction, "print") == 0)
		{
			instructions[i][0] = 7;
			scanf("x%d", &instructions[i][1]);
		}
		if (strcmp(instruction, "let") == 0)
		{
			instructions[i][0] = 5;
			scanf("x%d %d", &instructions[i][1], &instructions[i][2]);
		}
		if (strcmp(instruction, "bge") == 0)
		{
			instructions[i][0] = 6;
			scanf("x%d x%d %d", &instructions[i][1], &instructions[i][2], &instructions[i][3]);
		}
	}
	instructions[looptimes][0] = -1;
	//push CPU
	int exe = 0;
	while (1)
	{
		int instruction = instructions[exe][0];
		int op1 = instructions[exe][1], op2 = instructions[exe][2], op3 = instructions[exe][3];
		switch (instruction)
		{
		case 1:
			registers[ op1 - 1] = registers[ op2- 1] + registers[op3- 1];
			break;
		case 2:
			registers[op1 - 1] = registers[op2 - 1] - registers[op3 - 1];
			break;
		case 3:
			registers[op1 - 1] = registers[op2 - 1] * registers[op3 - 1];
			break;
		case 4:
			registers[op1 - 1] = registers[op2 - 1] / registers[op3 - 1];
			break;
		case 5:
			registers[op1 - 1] = op2;
			break;
		case 6:
			if (registers[op1 - 1] >= registers[op2 - 1])exe = op3 - 2;
			break;
		case 7:
			printf("x%d = %d\n", op1, registers[op1 - 1]);
			break;
		case -1:
			return 0;
		default:
			printf("Unknown instruction!!");
		}
		exe++;
	}
	
	
	


}

