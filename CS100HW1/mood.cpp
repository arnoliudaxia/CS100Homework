#pragma warning(disable : 4996)
#include <stdio.h>
#include <math.h>

int classNum = 0;
int lasth=8, lastm=0;
int startTime = 8 * 60;
float mood = 100;
int timeux(int h, int m)
{
	return h * 60 + m;
}
int main()
{

	printf("How many lectures today?\n");
	scanf("%d", &classNum);
	for (int i = 0; i < classNum; i++)
	{
		int h1, h2, m1, m2, idle_time;
		scanf("%d:%d-%d:%d", &h1, &m1, &h2, &m2);
		mood += .5 * (timeux(h1, m1)-timeux(lasth,lastm));
		mood = (mood > 100  )?  100:mood;
		int classtime = timeux(h2, m2) - timeux(h1, m1);
		if (classtime <= 60)mood -= .4 * classtime;
		else mood -= 24 + .8 * (classtime - 60);
		if (mood <= 0)
		{
			printf("Gezi Wang has been sent to hospital.\n");
			return 0;
		}
		lasth = h2;lastm = m2;
	}
	mood += .5 * (timeux(22, 0) - timeux(lasth, lastm));
	mood = (mood > 100) ? 100 : mood;
	printf("His mood level is %.1f at the end of the day.\n",mood);
}


