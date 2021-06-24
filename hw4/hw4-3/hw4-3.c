#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define OJ//这个是用来使能游戏运行的调试开关，你会在下面看到ifdef，作用就是如果这里define了OJ，那么下面游戏运行的代码就会执行，所以提交OJ的时候只需要注释掉这一行
#define FOOD_SCORE 10
#define MAX_GHOSTS 50

typedef enum gameState { losing, onGoing, winning } GameState;
typedef enum direction { up, down, left, right, idle } Direction;

typedef struct ghost
{
	bool isFoodBehind;//储存一下现在这个Ghost后面是不是有Food以便在moveGhost的时候好操作
	int placeOrder;//储存放鬼的顺序
	int position[2];//鬼的坐标
	Direction mydirection;//鬼现在的方向
}Ghost;
typedef struct game {
	char** grid;
	int columns;
	int rows;
	int foodCount;
	int score;
	GameState state;
	bool isPlayerPlaced;
	int PlayerPosition[2];
	int GhostNumber;
	Ghost* ghostList[MAX_GHOSTS];//存放所有怪的地址
} Game;

Game* NewGame(int rows, int columns) {
	
	Game* game = (Game*)malloc(sizeof(Game));
	game->foodCount = 0;
	game->score = 0;
	game->rows = rows;game->columns = columns;
	game->grid = (char**)malloc(sizeof(char*) * game->rows * game->columns);
	for (int i = 0; i < game->rows; i++)
	{
		game->grid[i] = (char*)malloc(sizeof(char) * game->columns);
		for (int j = 0; j < game->columns; j++)
		{
			game->grid[i][j] = ' ';
		}
	}
	game->state = onGoing;
	game->isPlayerPlaced = false;
	game->GhostNumber = 0;
	return game;
}
//游戏结束事件
void EndGame(Game* game) {
	
	for (int i = 0; i < game->rows; i++)
	{
		free(game->grid[i]);
	}
	free(game->grid);
	//free(game->PlayerPosition);
	for (size_t i = 0; i < game->GhostNumber; i++)
	{
		free(game->ghostList[i]);
	}
	//free(game->ghostList);
	free(game);
	return;
}
bool AddWall(Game* game, int r, int c) {

	if (r >= game->rows || c >= game->columns || r < 0 || c < 0)return false;//这里判断有没有出界，下面同理
	char cc = game->grid[r][c];//获取地图上对应坐标现在是个什么东西
	if (cc != ' ')return false;
	game->grid[r][c] = '#';
	return true;
}
bool AddFood(Game* game, int r, int c) {
	if (r >= game->rows || c >= game->columns || r < 0 || c < 0)return false;
	char cc = game->grid[r][c];
	if (cc != ' ')return false;
	game->grid[r][c] = '.';
	game->foodCount++;
	return true;
}
bool AddPacman(Game* game, int r, int c) {
	if (game->isPlayerPlaced)	return false;
	if (r >= game->rows || c >= game->columns || r < 0 || c < 0)return false;
	char cc = game->grid[r][c];
	if (cc != ' ')return false;
	game->grid[r][c] = 'C';
	game->PlayerPosition[0] = r;
	game->PlayerPosition[1] = c;
	game->isPlayerPlaced = true;
	return true;
}

void MovePacman(Game* game, Direction direction) {
	
	game->score--;
	int y = game->PlayerPosition[0], x = game->PlayerPosition[1];
	switch (direction)
	{
	case left:
		x--;
		break;
	case right:
		x++;
		break;
	case down:
		y++;
		break;
	case up:
		y--;
		break;
	default:
		break;
	}
	bool cango = true;
	cango = y < game->rows&& x >= 0 && y >= 0 && x < game->columns;
	if (!cango)return;
	char dest = game->grid[y][x];
	if (dest == '.')
	{
		game->score += FOOD_SCORE;
		game->foodCount--;
		if (game->foodCount == 0)game->state = winning;
	}
	if (dest == '#')return;
	game->grid[game->PlayerPosition[0]][game->PlayerPosition[1]] = ' ';
	game->PlayerPosition[0] = y;
	game->PlayerPosition[1] = x;
	if (dest == '@')
	{
		game->state = losing;
		return;
	}
	game->grid[y][x] = 'C';


}
#pragma region Part4
bool AddGhost(Game* game, int r, int c, Direction direction) {
	if (r >= game->rows || c >= game->columns || r < 0 || c < 0)return false;
	char cc = game->grid[r][c];
	if (!(cc == ' ' || cc == '.'))return false;
	game->GhostNumber++;
	if (game->GhostNumber > MAX_GHOSTS)assert(1!=1);
	Ghost* ghost = (Ghost*)malloc(sizeof(Ghost));
	ghost->isFoodBehind = cc == '.';
	ghost->position[0] = r;
	ghost->position[1] = c;
	ghost->placeOrder = game->GhostNumber;
	ghost->mydirection = direction;
	game->ghostList[game->GhostNumber - 1] = ghost;
	game->grid[r][c] = '@';
	return true;
}
Direction changDirection(Direction originalDirection)
{
	switch (originalDirection)
	{
	case up:
		return down;
	case down:
		return up;
	case left:
		return right;
	case right:
		return left;
	default:
		break;
	}
}
void MoveGhosts(Game* game) {
	for (size_t i = 0; i < game->GhostNumber; i++)
	{
		bool isReversed = 0;
		Ghost* currentGhost = game->ghostList[i];
	Again:;
		int y = currentGhost->position[0], x = currentGhost->position[1];
		switch (currentGhost->mydirection)
		{
		case left:
			x--;
			break;
		case right:
			x++;
			break;
		case down:
			y++;
			break;
		case up:
			y--;
			break;
		default:
			break;
		}
		char dest;
		bool cango = y < game->rows&& x >= 0 && y >= 0 && x < game->columns;
		if (!cango)dest = '?';
		else { 
			dest = game->grid[y][x];
		}
		game->grid[currentGhost->position[0]][currentGhost->position[1]] = \
			currentGhost->isFoodBehind ? '.' : ' ';
		switch (dest)
		{
		case '#':
		case '?':
		case '@':
			if (!isReversed)
			{
				//掉头
				currentGhost->mydirection = changDirection(currentGhost->mydirection);
				isReversed = true;
				goto Again;
			}
			else {
				isReversed = false;
				game->grid[currentGhost->position[0]][currentGhost->position[1]] = '@';
				continue;
			}
		case '.':
			currentGhost->isFoodBehind = true;
			break;
		case 'C':
			game->state = losing;
			break;
		default:
			currentGhost->isFoodBehind = false;
			break;
		}

		game->grid[y][x] = '@';
		currentGhost->position[0] = y;
		currentGhost->position[1] = x;
	}
	return;
}
#pragma endregion


#ifdef OJ

//只要传上面的
void PrintGame(Game* game);
void PlayGame(Game* game);
void AddElements(Game* game)//1:1复刻给的游戏
{
	AddFood(game, 0, 0);
	AddFood(game, 0, 1);
	AddFood(game, 0, 2);
	AddFood(game, 0, 3);
	AddWall(game, 0, 4);
	AddFood(game, 0, 5);
	AddFood(game, 0, 6);
	AddFood(game, 0, 7);
	AddFood(game, 0, 8);
	AddFood(game, 0, 9);
	AddFood(game, 0, 10);
	AddFood(game, 0, 11);
	AddFood(game, 0, 12);
	AddWall(game, 0, 13);
	AddFood(game, 0, 14);
	AddFood(game, 0, 15);
	AddFood(game, 0, 16);
	AddFood(game, 0, 17);
	AddFood(game, 1, 0);
	AddWall(game, 1, 1);
	AddWall(game, 1, 2);
	AddFood(game, 1, 3);
	AddWall(game, 1, 4);
	AddFood(game, 1, 5);
	AddWall(game, 1, 6);
	AddWall(game, 1, 7);
	AddWall(game, 1, 8);
	AddWall(game, 1, 9);
	AddWall(game, 1, 10);
	AddWall(game, 1, 11);
	AddFood(game, 1, 12);
	AddWall(game, 1, 13);
	AddFood(game, 1, 14);
	AddWall(game, 1, 15);
	AddWall(game, 1, 16);
	AddFood(game, 1, 17);
	AddFood(game, 2, 0);
	AddWall(game, 2, 1);
	AddFood(game, 2, 2);
	AddGhost(game, 2, 3, right);
	AddGhost(game, 2, 4, right);
	AddGhost(game, 2, 5, right);
	AddFood(game, 2, 4);
	AddFood(game, 2, 5);
	AddFood(game, 2, 6);
	AddFood(game, 2, 7);
	AddFood(game, 2, 8);
	AddFood(game, 2, 9);
	AddFood(game, 2, 10);
	AddFood(game, 2, 11);
	AddFood(game, 2, 12);
	AddFood(game, 2, 13);
	AddFood(game, 2, 14);
	AddFood(game, 2, 15);
	AddWall(game, 2, 16);
	AddFood(game, 2, 17);
	AddFood(game, 3, 0);
	AddWall(game, 3, 1);
	AddFood(game, 3, 2);
	AddWall(game, 3, 3);
	AddWall(game, 3, 4);
	AddFood(game, 3, 5);
	AddWall(game, 3, 6);
	AddWall(game, 3, 7);
	AddFood(game, 3, 8);
	AddFood(game, 3, 9);
	AddWall(game, 3, 10);
	AddWall(game, 3, 11);
	AddFood(game, 3, 12);
	AddWall(game, 3, 13);
	AddWall(game, 3, 14);
	AddFood(game, 3, 15);
	AddWall(game, 3, 16);
	AddFood(game, 3, 17);
	AddFood(game, 4, 0);
	AddFood(game, 4, 1);
	AddFood(game, 4, 2);
	AddFood(game, 4, 3);
	AddFood(game, 4, 4);
	AddFood(game, 4, 5);

	AddGhost(game, 4, 5, down);
	AddWall(game, 4, 6);
	AddFood(game, 4, 7);
	AddFood(game, 4, 8);
	AddFood(game, 4, 9);
	AddFood(game, 4, 10);
	AddWall(game, 4, 11);
	AddFood(game, 4, 12);
	AddFood(game, 4, 13);
	AddFood(game, 4, 14);
	AddFood(game, 4, 15);
	AddFood(game, 4, 16);
	AddFood(game, 4, 17);
	AddFood(game, 5, 0);
	AddWall(game, 5, 1);
	AddFood(game, 5, 2);
	AddWall(game, 5, 3);
	AddWall(game, 5, 4);
	AddFood(game, 5, 5);
	AddWall(game, 5, 6);
	AddWall(game, 5, 7);
	AddWall(game, 5, 8);
	AddWall(game, 5, 9);
	AddWall(game, 5, 10);
	AddWall(game, 5, 11);
	AddFood(game, 5, 12);
	AddWall(game, 5, 13);
	AddWall(game, 5, 14);
	AddFood(game, 5, 15);
	AddWall(game, 5, 16);
	AddFood(game, 5, 17);
	AddFood(game, 6, 0);
	AddWall(game, 6, 1);
	AddFood(game, 6, 2);
	AddFood(game, 6, 3);
	AddFood(game, 6, 4);
	AddFood(game, 6, 5);
	AddFood(game, 6, 6);
	AddFood(game, 6, 7);
	AddFood(game, 6, 8);
	AddFood(game, 6, 9);
	AddFood(game, 6, 10);
	AddFood(game, 6, 11);
	AddFood(game, 6, 12);
	AddFood(game, 6, 13);
	AddFood(game, 6, 14);
	AddFood(game, 6, 15);
	AddWall(game, 6, 16);
	AddFood(game, 6, 17);
	AddFood(game, 7, 0);
	AddWall(game, 7, 1);
	AddWall(game, 7, 2);
	AddFood(game, 7, 3);
	AddWall(game, 7, 4);
	AddFood(game, 7, 5);
	AddWall(game, 7, 6);
	AddWall(game, 7, 7);
	AddWall(game, 7, 8);
	AddWall(game, 7, 9);
	AddWall(game, 7, 10);
	AddWall(game, 7, 11);
	AddFood(game, 7, 12);
	AddWall(game, 7, 13);
	AddFood(game, 7, 14);
	AddWall(game, 7, 15);
	AddWall(game, 7, 16);
	AddFood(game, 7, 17);
	AddFood(game, 8, 0);
	AddFood(game, 8, 1);
	AddFood(game, 8, 2);
	AddFood(game, 8, 3);
	AddWall(game, 8, 4);
	AddFood(game, 8, 5);
	AddFood(game, 8, 6);
	AddFood(game, 8, 7);
	AddPacman(game, 8, 8);
	AddFood(game, 8, 9);
	AddFood(game, 8, 10);
	AddFood(game, 8, 11);
	AddFood(game, 8, 12);
	AddWall(game, 8, 13);
	AddFood(game, 8, 14);
	AddFood(game, 8, 15);
	AddFood(game, 8, 16);
	AddFood(game, 8, 17);
	AddGhost(game, 4, 0,right);
}
int main() {
	Game* game = NewGame(9, 18);


	/*AddFood(game, 2, 2);
	AddFood(game, 3, 1);
	AddWall(game, 2, 1);
	AddWall(game, 2, 2);
	AddWall(game, 2, 3);
	AddWall(game, 2, 4);
	AddPacman(game, 4, 1);*/
	//AddGhost(game,0, 2,down);
	AddElements(game);

	PlayGame(game);
	//printf("%d", game->score);
	printf("Press any key to exit.");
	EndGame(game);
}

#pragma region 与我无瓜
#ifdef _MSC_VER

#include <windows.h>

#endif // _MSC_VER

void PrintGame(Game* game) {
	if (!game || !game->grid) return;

	// If visual C++, clear console.
#ifdef _MSC_VER 
	system("cls");
#else
// Clears terminal screen
#ifndef _ONLINE_JUDGE
	fflush(stdout);
	system("clear");
#endif

#endif

	// The game grid
	printf(" ");
	for (int i = 0; i < game->columns; i++)
		printf("_");
	printf(" \n");

	for (int i = 0; i < game->rows; i++) {
		printf("|");
		for (int j = 0; j < game->columns; j++)
			printf("%c", game->grid[i][j]);
		printf("|\n");
	}
	printf("\\");
	for (int i = 0; i < game->columns; i++)
		printf("-");
	printf("/\n\n");

	// Messages on different states
	switch (game->state) {
	case losing:
		printf("Pacman died! Your score: %d\n", game->score);
		break;
	case onGoing:
		printf("Score: %d\n", game->score);
		printf("There are %d foods remaining!\n", game->foodCount);
		printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
		break;
	case winning:
		printf("Victory! Your score: %d\n", game->score);
		break;
	default:
		printf("ERROR: invalid game state!\n");
	}
}

void PlayGame(Game* game) {
	if (!game) return;


	PrintGame(game);




	// Main loop of game. Terminates when the game ends.
	while (true) {
		// We only care about one charater, but should eat the whole line of input.
		char input[127];
		scanf("%s", input);
		Direction direction;
		switch (input[0]) {
		case 'w':
		case 'W':
			direction = up; break;
		case 'a':
		case 'A':
			direction = left; break;
		case 's':
		case 'S':
			direction = down; break;
		case 'd':
		case 'D':
			direction = right; break;
		case 'i':
		case 'I':
			direction = idle; break;
		default:
			PrintGame(game);
			continue;
		}

		// Pacman moves first
		MovePacman(game, direction);

		// Loses if Pacman bumps into a ghost
		if (game->state != onGoing) {
			break;
		}

		// If you haven't implemented ghosts, this does nothing.
		MoveGhosts(game);

		// Loses if a ghost kills Pacman
		if (game->state != onGoing) {
			break;
		}
		PrintGame(game);

	}


	PrintGame(game);

	//printf("Press any key to exit.\n");
	//getchar();
	//getchar();
}
#pragma endregion
#endif // OJ
