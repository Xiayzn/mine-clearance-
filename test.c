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
