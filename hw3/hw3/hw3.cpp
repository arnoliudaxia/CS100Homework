#pragma warning(disable : 4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


void prinfinvalid()
{
	printf("This number is invalid.\n");
}
void printAlllowed()
{
	printf("This car is allowed to drive.\n");
}
void printNotAllowed()
{
	printf("This car is not allowed to drive.\n");
}
int howmanyletters(char string[], int length)
{
	int counter = 0;

	for (int i = 0;i < length;i++)
	{
		if (isupper(string[i]) != 0)counter++;
	}
	return counter;

}
int howmanydigits(char string[], int length)
{
	int counter = 0;

	for (int i = 0;i < length;i++)
	{
		if (isdigit(string[i]) != 0)counter++;
	}
	return counter;
}
int isletter(char input)
{
	if (isupper(input) != 0)return 1;
	return 0;
}
int isshuzi(char input)
{
	if (isdigit(input) != 0)return 1;
	return 0;
}

int ifweekday(char weekname[])
{
	if (strcmp(weekname, "Mon") == 0)goto isweekday;
	if (strcmp(weekname, "Tue") == 0)goto isweekday;
	if (strcmp(weekname, "Wed") == 0)goto isweekday;
	if (strcmp(weekname, "Thu") == 0)goto isweekday;
	if (strcmp(weekname, "Fri") == 0)goto isweekday;
	if (strcmp(weekname, "Sat") == 0)goto nonweekday;
	if (strcmp(weekname, "Sun") == 0)goto nonweekday;
isweekday:
	return 1;
nonweekday:
	return 0;
}
int ifplateVaild(char platename[])//0:invaid 1:normalcar 2:special car
{
	int ifvaild = 0;
	if (strchr(platename, 'I') != NULL || strchr(platename, 'O') != NULL)return 0;
	if (strlen(platename) == 6&&howmanyletters(platename,6)==1)
	{
		if (platename[0] == 'D' || platename[0] == 'F' || platename[5] == 'D' || platename[5] == 'F')ifvaild = 2;
	}
	else if (strlen(platename) == 5)
	{
		if (howmanydigits(platename,5) == 5)return 1;
		if (howmanyletters(platename, 5) == 1)
		{
			if  (isletter(platename[0]))
			{
					ifvaild = 1;
					if (platename[0] == 'T' || platename[0] == 'X')ifvaild = 2;
			}
			else if (isletter(platename[4]))
			{
				ifvaild = 1;
			}
			
		}
		if (ifvaild)return ifvaild;
		//customer
		if (howmanyletters(platename, 5)==2)
		{
			if (isletter(platename[0]) && isletter(platename[4]))ifvaild = 1;
			else
			{
				for (int i = 0;i < 5;i++)
				{
					if (isletter(platename[i]))
					{
						if (isletter(platename[i + 1]))
						{
							ifvaild = 1;
							
						}
						break;
					}
				}
			}
		}
		if (howmanyletters(platename, 5)==1)
		{
			if (isletter(platename[1]) || isletter(platename[2]))ifvaild = 1;
		}
		for (int i = 0;i < 3;i++)
		{
			if (isshuzi(platename[i]))
			{
				if (platename[i] == platename[i + 1]&& platename[i + 1] == platename[i + 2])
				ifvaild = 0;
			}
		}
	}
	return ifvaild;
}
int lastDigit(char string[],int length)
{
	for (int i = length-1;;i--)
	{
		if (isupper(string[i]))continue;
		return string[i]-'0';
	}
}

int main()
{
	int carType = 0;//1:normal car 2:special car 
	char input[8];
	int month, day;
	char week[4];
	for (int i = 0;i < 3;i++)
	{
		scanf("%s %d/%d %s", input, &month, &day, week);
		if (!(carType = ifplateVaild(input)))prinfinvalid();
		else
		{
			if (carType== 2)printAlllowed();
			else
			{
				if (ifweekday(week))
				{
					if ((lastDigit(input,strlen(input)) % 2 == day % 2 )) //even
						printAlllowed();

					else
						printNotAllowed();
				}
				else { printAlllowed(); }
			}
		}
	}
}
