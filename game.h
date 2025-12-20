#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<graphics.h>

#define Size 30 //设置格子大小
IMAGE img[21];//定义一个对象
IMAGE menu[5];//定义一个对象
clock_t begin, end;//时钟

char** Malloc2d(char*** a, const int row, const int col);//二维数组自定义
void Destroy(char*** a, const int row, const int col);//消除二维数组的内存
int SelectDifficulty();//选择难度
void INIB(char** a, const int row, const int col, char set);//初始化棋盘
void Menuinit();//菜单图形初始化
void Drawinit();//图形初始化
void TimeCount();//时间函数
int MouseSelectMode(char** a, char** b, const int row, const int col, const int mine);//鼠标操作
void SetMine(char** a, int row, int col, int c, int d);//随机布置雷
void DisplayA();//打印"process"与操作数目与剩余雷数（雷减标记数）
void DisplayB(char** a, const int row, const int col);//打印棋盘
void DisplayChange(char** a, char** b, const int row, const int col);//打印最终棋盘
void GameDraw(char** b, const int row, const int col);//呈现棋盘
int get_minecount(char** a, int x, int y);//查找3x3雷数
void open(char** a, char** b, int x, int y);//打开格子
int judgement(char** b, const int row, const int col, const int mine);//判断是否赢得游戏
int judgementLeftClick(char** b, const int x, const int y); //判断左击操作是否正确
int judgementDoubleClick(char** b, int x, int y);//判断双击操作是否正确
void Win(char** a, char** b);//胜利函数
void Lose(char** a, char** b);//失败函数
int FindMine(char** a, char** b, const int row, const int col, const int mine, const int inputa, const int inputb);//操作1
int FindMine2(char** a, char** b, const int row, const int col, const int mine, const int inputa, const int inputb);//操作9
int EditFlag(char** b, const int row, const int col, const int inputa, const int inputb);//2、3、4步骤操作的图形化使用

struct Board {
	int row;//行
	int col;//列
	int mine;//雷
}B;

struct Book {
	int win;//成功判断
	int lose;//失败判断
	int count;//操作数
	int count2;//记雷数
	int LeftCount;//左键计数
	int timeC;//时间
}L;
