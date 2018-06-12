# mine-clearance-
//扫雷
//game.h
#ifndef __GAME_H__
#define __GAME_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROW 9
#define COL 9

#define ROWS ROW+2
#define COLS COL+2

#define EASY_COUNT 10


void init_board(char board[ROWS][COLS], int rows, int cols,char set);
void display_board(char board[ROWS][COLS], int row, int col);
void set_mine(char board[ROWS][COLS], int row, int col);
int remove_mine(char board1[ROWS][COLS], char board2[ROWS][COLS], int row, int col);
int count_show_mine(char board[ROWS][COLS], int row, int col);
void open_board(char board[ROWS][COLS], int x, int y);
int get_mine_count(char board[ROWS][COLS], int row, int col);
void stamp_mine(char board[ROWS][COLS], int row, int col);
#endif//__GAME_H__



//game.c
#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void init_board(char board[ROWS][COLS], int rows, int cols,char set)
{
	int i = 0;
	int j = 0;

	for (i = 0; i < rows;i++)
	{
		for (j = 0; j < cols;j++)
		{
			board[i][j] = set;
		}

	}


}
void display_board(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	int count = 0;
	printf("     1  2  3  4  5  6  7  8  9  10\n");
	for (i = 1; i <=row+1; i++)
	{
		printf(" %2d  %c  %c  %c  %c  %c  %c  %c  %c  %c  %c\n", i, board[i][1], board[i][2], board[i][3], board[i][4], board[i][5], board[i][6], board[i][7], board[i][8], board[i][9], board[i][10]);
		
	}
	
	for (i = 1; i <= row + 1; i++)
	{
		for (j = 1; j <= col + 1; j++)
		{
			if (board[i][j] == 'p')
			{
				count++;
			}
		}
	}
	printf("地雷个数：%d\n", (EASY_COUNT-count));
	
}

void set_mine(char board[ROWS][COLS], int row, int col)
{
	int x = 0;
	int y = 0;
    int count = EASY_COUNT;
	srand((unsigned)time(NULL));

	while (count)
	{
		x = (rand() % (row+1)) + 1;  //随机数放在循环内  循环一次随机取数一次
		y = (rand() % (col+1)) + 1;
		if (board[x][y] == '0')
		{
			board[x][y] = '1';
			//display_board(board, ROW, COL);
			--count;
		}
	}
}

int count_show_mine(char board[ROWS][COLS], int row, int col)//判断剩余未知区域的个数，个数为雷数时玩家赢
{
	int i = 0;
	int j = 0;
	int count = 0;

	for (i = 1; i <= row+1; i++)
	{
		for (j = 1; j <= col+1; j++)
		{
			if (board[i][j] == '*')
			{
				count++;
			}
		}

	}
	return count;
}

int remove_mine(char board1[ROWS][COLS], char board2[ROWS][COLS], int row, int col)//扫雷函数，踩到雷返回0，没有踩到雷返回1
{
	int x = 0;
	int y = 0;
	int static step = 1;
	int count = 0;
	srand((unsigned)time(NULL));

	
	
	if (step == 1)//第一步不被炸死
	{
		printf("示例：“1 1”\n");
		printf("请玩家输入要排查雷的坐标：");
		scanf("%d %d", &x, &y);

		if (( x >= 1 && x <= row + 1) && ( y >= 1 && y <= col + 1))//判断输入坐标是否有误，输入错误重新输入
		{
			if (board1[x][y] == '0')//没踩到雷
			{
				int mine_num = get_mine_count(board1, x, y);//该坐标周围雷的个数
				board2[x][y] = mine_num + '0';
				open_board(board1, board2, x, y);
				display_board(board2, ROW, COL);
				stamp_mine(board2, ROW, COL);

				step++;
				
				if (count_show_mine(board2, row, col) == EASY_COUNT)//判断剩余未知区域的个数，个数为雷数时玩家赢
				{
					display_board(board2, ROW, COL);
					printf("恭喜玩家，扫雷成功\n");
					return 0;
				}
				else
					return 1;
				
			}
			else if (board1[x][y] == '1')//第一步踩到雷不被炸死
			{
				int a = 0;
				int b = 0;
				/*a = (rand() % row) + 1;
				b = (rand() % col) + 1;
                */
				while (1)
				{
					a = (rand() % row) + 1;
					b = (rand() % col) + 1;

					if (board1[a][b] != '1')
					{
						int tmp = 0;
						board1[x][y] = board1[a][b];
						board1[a][b] = board1[x][y];
						break;
					}
				}

				int mine_num = get_mine_count(board1, x, y);//该坐标周围雷的个数
				board2[x][y] = mine_num + '0';
				open_board(board1, board2, x, y);
				display_board(board2, ROW, COL);
				stamp_mine(board2, ROW, COL);

				step++;
				return 1;
			}

		}
		else
		{
			printf("输入错误,请重新输入\n");
		}
		step++;
		return 1;//没踩到雷
		
	}
	else
	{
		printf("示例：“1 1”\n");
		printf("请玩家输入要排查雷的坐标：");
		scanf("%d %d", &x, &y);

		if ((x >= 1 && x <= row+1) && (y >= 1 && y <= col+1))//判断输入坐标是否有误，输入错误重新输入
		{
			if (board1[x][y] == '0')//没踩到雷
			{
				int mine_num = get_mine_count(board1, x, y);//该坐标周围雷的个数
				board2[x][y] = mine_num + '0';
				open_board(board1, board2, x, y);
				display_board(board2, ROW, COL);
				stamp_mine(board2, ROW, COL);

				if (count_show_mine(board2, row, col) == EASY_COUNT)//判断剩余未知区域的个数，个数为雷数时玩家赢
				{
					display_board(board2, ROW, COL);
					printf("恭喜玩家，扫雷成功\n");
					return 0;
				}
			}
			else if (board1[x][y] == '1')//踩到雷
			{
				printf("非常遗憾，您被雷炸死了，排雷失败\n");
				return 0;
			}

		}
		else
		{
			printf("输入错误，请重新输入\n");
		}

		return 1;//没踩到雷

	}
	
}
//void get_mine_count(char board1[ROWS][COLS], char board2[ROWS][COLS], int row, int col)
//{
//	int x = 0;
//	int y = 0;
//	int count = 0;
//
//	while (1)
//	{
//		printf("示例：“1 1”\n");
//		printf("请玩家输入要排查雷的坐标：");
//		scanf("%d %d", &x, &y);
//		if ((x >= 1 && x <= row + 1) && (y >= 1 && y <= col + 1))
//		{
//			if (board1[x][y] == '0')
//			{
//				int i = 0;
//				int j = 0;
//
//				for (i = x - 1; i <= x + 1; i++)
//				{
//					for (j = y - 1; j <= y + 1; j++)
//					{
//						if (board1[i][j] == '1')
//						{
//							count++;
//						}
//					}
//				}
//				board2[x][y] = count + '0';
//			}
//		}
//		else
//		{
//			printf("坐标输入错误，请重新输入");
//		}
//	}
	
	//方法2
	//int x = 0;
	//int y = 0;

	//if (1 == coordinate)
	//{
	//	while (1)
	//	{
	//		printf("示例：“1 ” 范围（1-10）\n");
	//		printf("请玩家输入要排查雷的坐标：");
	//		scanf("%d", &x);
	//		if (x >= 1 && x <= row + 1)
	//		{
	//			break;
	//		}
	//		else
	//		{
	//			printf("坐标输入错误，请重新输入\n");
	//		}

	//	}
	//	return x;
	//}
	//else if (2 == coordinate)
	//{
	//	while (1)
	//	{
	//		printf("示例：“1 ” 范围（1-10）\n");
	//		printf("请玩家输入要排查雷的坐标：");
	//		scanf("%d", &y);
	//		if (y >= 1 && y <= col + 1)
	//		{
	//			break;
	//		}
	//		else
	//		{
	//			printf("坐标输入错误，请重新输入\n");
	//		}

	//	}
	//	return y;

	//}
//}


int get_mine_count(char board[ROWS][COLS], int x, int y)//统计坐标周围雷数
{
	int i = 0;
	int j = 0;
	int count = 0;

	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1;j++)
		{
			if (board[i][j] == '1')
			{
				count++;
			}
		}
	}
	return count;
}

void open_board(char board1[ROWS][COLS], char board2[ROWS][COLS], int x, int y)
{
	int i = 0;
	int j = 0;
	int mine_num = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1;j++)
		{
			if (board1[i][j]=='0')
			{
				mine_num = get_mine_count(board1, i, j);
				board2[i][j] = mine_num + '0';

				if (mine_num == 0)
				{
					board2[i][j] = '0';

				}
			}
		
		}
	}
}

void stamp_mine(char board[ROWS][COLS], int row, int col)
{

	int x = 0;
	int y = 0;
	int input1 = 0;
	int input2 = 0;

	while (1)
	{
		printf("玩家是否需要标记雷？标记请输入“1”,退出请输入“0”\n");
		scanf("%d", &input1);

		if (1 == input1)
		{
			while (1)
			{
				printf("示例：“1 1”\n");
				printf("请玩家输入要更改雷的坐标：");
				scanf("%d %d", &x, &y);

				if ((x >= 1 && x <= row + 1) && (y >= 1 && y <= col + 1))//判断输入坐标是否有误，输入错误重新输入
				{
					if (board[x][y] == '*')
					{
						board[x][y] ='p';
						display_board(board, ROW, COL);
					}
					break;
				}
				else
				{
					printf("坐标输入错误，请重新输入\n");
				}

			}

			while (1)
			{

				printf("是否确定该坐标为雷？\n");
				printf("确定请输入“1”,修改请输入“0”\n");
				scanf("%d", &input2);

				if (1 == input2)
				{
					break;
				}
				else if (0 == input2)
				{
					board[x][y] = '*';
					break;
				}
				else
				{
					printf("输入错误，请重新输入\n");
				}

			}

			break;
		}
		else if (0 == input1)
		{
			break;
		}
		else
		{
			printf("输入错误，请重新输入\n");
		}
	}
}




//test.c
#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
void menu()
{
	printf("-----------------------\n");
	printf("----1.play   0.exit----\n");
	printf("-----------------------\n");
}
void game()
{
	int mine_num = EASY_COUNT;
	int ret = 1;
	char mine[ROWS][COLS] = { 0 };//存雷的数组
	char show[ROWS][COLS] = { 0 };//排查数组
	

	init_board(mine, ROWS, COLS,'0');
	init_board(show, ROWS, COLS,'*');
	set_mine(mine, ROW, COL);//布置雷

	display_board(mine, ROW, COL);
	display_board(show, ROW, COL);
	while (ret)//问题 怎么接受函数返回的两个返回值？
	{
		//int ret1 = 0;
		//int ret2 = 0;
		//
		//ret1 = player_move(mine, ROW, COL, 1);//玩家输入要排雷的坐标，横坐标用1表示
		//ret2 = player_move(mine, ROW, COL, 2);//玩家输入要排雷的坐标，纵坐标用2表示
		
		ret = remove_mine(mine,show, ROW, COL);//排雷
		

		//get_mine_count(mine,show, ROW, COL);//计算该坐标周围雷数
		
	}
	
}

int main()
{
	
	int input = 0;
	
	do
	{
		menu();
		printf("请输入一个数：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			game();
		case 0:
			printf("退出游戏?\n");
			break;
		default:
			printf("输入错误，请重新输\n");
			break;
		}
	} while (input);
	return 0;
}
