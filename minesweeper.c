#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define BOARD_SIZE		10
#define SQUARE_NUM		(BOARD_SIZE*BOARD_SIZE)
#define MINE_NUM		17
#define SHUFFLE_NUM		100000

int mine_board[BOARD_SIZE][BOARD_SIZE];
/* 0 : non-mined, 1 : mined */

int display_board[BOARD_SIZE][BOARD_SIZE];
/* -1 : no mines around, 0 : unknown, 1~8 : number of mines */

void init_board(); // initialize mine_board by randomly planting fixed number of mines
void show_interface(); // print display_board
int sweep(int x, int y);
/*
 * sweep a square on (x, y). if there is no mines around square on (x, y), recursively sweep adjacent squares
 * return : 1 if player sweeps mined square, else 0
 */

int check_game(); 
/*
 * check if the player swept all non-mined squares
 * return : 1 if player swept all non-mined squares, else 0
 */

int main(void)
{
	int a=0, b=0, x, y;

	init_board();
	while(1) {
		show_interface();
		printf("Enter the coordinate(x y)=");
		scanf("%d %d", &x, &y);
		
		if (sweep(y-1,x-1)==1) {
			
		while (a<BOARD_SIZE) {
			while (b<BOARD_SIZE) {
				if(mine_board[a][b]==1) {
					display_board[a][b]=-1;
				
				}
				b++;
			}
			b=0;
			a++;
		}
			
			
		
		show_interface();
		printf("you fail!\n");
		return 0;
		}

		if (check_game()==1) {
			printf("you success!\n");
			return 0;
		}
	}

}
void init_board()
{
	int i;
	int shuffle[BOARD_SIZE * BOARD_SIZE];
	int temp;
	int r1, r2;

	srand(time(NULL)); // set seed

	// initialize shuffle array
	for(i=0; i<SQUARE_NUM; i++)
		shuffle[i] = i;

	// shuffling
	for(i=0; i<SHUFFLE_NUM; i++)
	{
		r1 = rand() % SQUARE_NUM;
		r2 = rand() % SQUARE_NUM;

		temp = shuffle[r1];
		shuffle[r1] = shuffle[r2];
		shuffle[r2] = temp;
	}

	// get mine coordinates from shuffled array
	for(i=0; i<MINE_NUM; i++)
		mine_board[shuffle[i]/BOARD_SIZE][shuffle[i]%BOARD_SIZE] = 1;
}

void show_interface()
{
	int i, j;

	system("clear"); // clear the screen

	// rest of this function just prints out display_board
	printf("    ");
	for(i=0; i<BOARD_SIZE; i++)
		printf(" %2d ", i+1);
	printf("-> X\n");

	for(i=0; i<BOARD_SIZE; i++)
	{
		printf("\n %2d ", i+1);

		for(j=0; j<BOARD_SIZE; j++)
		{
			if(display_board[i][j] == -1)
			{
				if(mine_board[i][j] == 1)
					printf("  * ");
				else
					printf("  X ");
			}
			else if(display_board[i][j] == 0)
				printf("  - ");
			else
				printf("  %d ", display_board[i][j]);
		}
		printf("\n");
	}
	printf("\n  |\n  v\n\n  Y\n\n");
}

int sweep(int x, int y)
{
	if (x<0 || y<0 || x>=BOARD_SIZE || y>=BOARD_SIZE) {
		return 0;
	}

	if (display_board[x][y]!=0) {
		return 0;
	}
	int a, b;

	a=x;
	b=y;

	if (mine_board[x][y]==1) {
		return 1;
	}

	else {


		while (a<=x+2) {
			while (b<=y+2) {
				if (mine_board[a-1][b-1]==1 && a>0 && a<=BOARD_SIZE && b>0 && b<=BOARD_SIZE) {
					display_board[x][y]++;
				}
				b++;
			}
			b=y;
			a++;
		}

		if (display_board[x][y]==0) {
			display_board[x][y]--;
			sweep(x-1,y-1);
			sweep(x,y-1);
			sweep(x+1,y-1);
			sweep(x-1,y);
			sweep(x+1,y);
			sweep(x-1,y+1);
			sweep(x,y+1);
			sweep(x+1,y+1);
		}
		return 0;
	}
}

int check_game()
{
	int a=0, b=0;
	while (a<BOARD_SIZE) {
		while (b<BOARD_SIZE) {
			if (display_board[a][b]==0 && mine_board[a][b]==0) {
				return 0;
			}
			b++;
		}
		a++;
	}
	return 1;
}
