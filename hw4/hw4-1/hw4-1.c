#pragma warning(disable : 4996)
#include <stdio.h>
#include<string.h>
#include<stdlib.h>


int table[4][11];
int remains()
{
	int counter = 0;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (table[i][j])counter += table[i][j];
		}
	}
	return counter;
}
int Check()
{
	if (remains() == 2)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				if (table[i][j] == 2)
				{
					return 1;
				}
			}
		}
		return 0;
	}
	//遍历
	//先挑三个的，最后挑两个
	for (size_t norshape = 0; norshape < 4; norshape++)
	{
			for (size_t i = 0; i < 10; i++)
			{
				if (table[norshape][i] >= 1 && i < 8 &&norshape!=3)
				{
					if (table[norshape][i + 1] && (table[norshape][i + 2]))
					{
						table[norshape][i]--, table[norshape][i + 1]--, table[norshape][i + 2]--;

						if (Check())return 1;
						table[norshape][i]++, table[norshape][i + 1]++, table[norshape][i + 2]++;
					}
				}
				if (table[norshape][i] >= 3)
				{
					table[norshape][i] -= 3;
					if (Check()) return 1;
					table[norshape][i] += 3;
				}

			}
		}
	return 0;
}

int CheckWin(char* mahjongHand[])
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 11; j++)
		{
			table[i][j] = 0;
		}
	}
	for (size_t i = 0; i < 14; i++)
	{
		int number;
		char c;
		sscanf(mahjongHand[i], "%d%c", &number, &c);
		switch (c)
		{
		case 'p':
			table[0][number]++;
			break;
		case 'm':
			table[1][number]++;

			break;
		case 's':
			table[2][number]++;

			break;
		case 'z':
			if (number < 5)
				table[3][number - 1]++;
			else
				table[3][number - 1]++;

			break;
		default:
			break;
		}
	}
	return Check();

}
int CountWaitingTiles(char* currentTiles[])
{
	int count = 0;
	char* possibleAns[] = { "1p","2p","3p","4p","5p","6p","7p","8p","9p", \
		"1s","2s","3s","4s","5s","6s","7s","8s","9s", "1m","2m","3m","4m","5m","6m","7m","8m","9m", \
		"1z","2z","3z","4z","5z","6z","7z" };
	char* buqi[14];
	for (size_t i = 0; i < 13; i++)
	{
		buqi[i] = currentTiles[i];
	}
	for (size_t i = 0; i < sizeof(possibleAns)/sizeof(possibleAns[0]); i++)
	{
		int howmany = 0;
		for (size_t j = 0; j < 13; j++)
		{
			if (strcmp(possibleAns[i], currentTiles[j]) == 0)
				howmany++;
		}
		if (howmany > 3)continue;
		buqi[13] = possibleAns[i];
		if (CheckWin(buqi))
		{
			count++;
			//printf("%s\n", buqi[13]);
		}
	}

	return count;
}
int main()
{
	char* hand1[13] = { "9s", "1z", "1s", "2s", "3s", "4s", "5s", "6s", \
					  "7s", "8s", "9s", "9s", "9s" };
	char* hand2[14] = { "3p", "3p", "3p", "7p", "8p", "9p", "2s", "2s", "4s", "5s", "7s", "8s", "9s" };
	char* hand3[14] = { "3s", "3m", "8m", "1s", "7m", "7m", "6s", "8p", "8m", "5s", "2s", "6z", "5m", "4s" };
	char* hand4[14] = { "4m", "5m", "2z", "2m", "4p", "2z", "7m", "9p", "2s", "9p", "9p", "7p", "9s", "6s" };
	char* hand5[14] = { "1m", "2z", "7s", "3m", "8m", "2m", "4z", "3z", "8s", "6p", "3p", "2m", "7p", "9s" };
	char* kk[13] = { "3p", "3p", "3p", "7p", "8p", "9p", "2s", "2s", "4s", "5s", "7s", "8s", "9s" };
	printf("%d", CountWaitingTiles(hand1));
	printf("%d", CountWaitingTiles(hand2));
	printf("%d", CountWaitingTiles(hand3));
	printf("%d", CountWaitingTiles(hand4));
	printf("%d", CountWaitingTiles(hand5));

	//printf("%d", CheckWin(hand1));

	return 0;
}