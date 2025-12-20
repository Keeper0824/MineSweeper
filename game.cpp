#include"game.h"

int main()
{
	srand((unsigned int)time(NULL));//随机函数
	int flag = 0;
	while (flag == 0)
	{
		//重新初始化参数
		L.win = 0;
		L.lose = 0;
		L.count = 0;
		L.count2 = 0;
		L.LeftCount = 0;
		L.timeC = 0;

		Menuinit();//菜单初始化

		//难度选择
		initgraph(300, 500, 8);
		setbkcolor(BLACK);
		cleardevice();
		putimage(66, 25, &menu[1]);
		putimage(66, 150, &menu[2]);
		putimage(66, 275, &menu[3]);
		putimage(66, 400, &menu[4]);
		int num = SelectDifficulty();
		closegraph();

		//初始化界面
		initgraph(B.col * Size, 50 + B.row * Size, 8);
		setbkcolor(RGB(204, 204, 204));
		cleardevice();

		HWND sc = GetHWnd();
		switch (num)
		{
		case 1:
			SetWindowText(sc, "初级");
			break;
		case 2:
			SetWindowText(sc, "中级");
			break;
		case 3:
			SetWindowText(sc, "高级");
			break;
		case 4:
			SetWindowText(sc, "自定义");
			break;
		}

		//二维数组创建
		char** a = NULL;
		char** b = NULL;
		char** pa = NULL;
		a = Malloc2d(&pa, B.row + 2, B.col + 2);
		if (a == NULL)
		{
			printf("存储雷二维数组创建错误");
		}
		b = Malloc2d(&pa, B.row + 2, B.col + 2);
		if (b == NULL)
		{
			printf("玩家查看二维数组创建错误");
		}

		//初始化棋盘
		INIB(a, B.row + 2, B.col + 2, '.');//雷
		INIB(b, B.row + 2, B.col + 2, '.');//玩家查看
		Drawinit();

		//操作
		MouseSelectMode(a, b, B.row, B.col, B.mine);

		//释放二维数组
		Destroy(&a, B.row + 2, B.col + 2);
		Destroy(&b, B.row + 2, B.col + 2);
		if (L.win == 1 || L.lose == 1)
		{
			int re = MessageBox(NULL, "还想再玩一次嘛？", "提示", MB_RETRYCANCEL);
			if (re == IDRETRY)
			{
				flag = 0;
			}
			else if (re == IDCANCEL)
			{
				flag = 1;
			}
		}
	}
	//暂停
	//system("pause");
	closegraph();
	return 0;
}

int SelectDifficulty()//选择难度
{
	ExMessage msg;//获取鼠标信息
	while (1)
	{
		if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONUP)
		{
			if (msg.x >= 66 && msg.x <= 66 + 168 && msg.y >= 25 && msg.y <= 25 + 76)
			{
				B.row = 9;
				B.col = 9;
				B.mine = 10;
				return 1;
			}
			else if (msg.x >= 66 && msg.x <= 66 + 168 && msg.y >= 150 && msg.y <= 150 + 76)
			{
				B.row = 16;
				B.col = 16;
				B.mine = 40;
				return 2;
			}
			else if (msg.x >= 66 && msg.x <= 66 + 168 && msg.y >= 275 && msg.y <= 275 + 76)
			{
				B.row = 16;
				B.col = 30;
				B.mine = 99;
				return 3;
			}
			else if (msg.x >= 66 && msg.x <= 66 + 168 && msg.y >= 400 && msg.y <= 400 + 76)
			{
				int flag = 0;
				int row = 0;
				int col = 0;
				int mine = 0;
				closegraph();

				initgraph(300, 400, 8);
				setbkcolor(RGB(204, 204, 204));
				cleardevice();

				HWND hWnd = GetHWnd();
				SetWindowText(hWnd, "自定义难度选择");
				while (flag == 0)
				{
					char s[2];
					InputBox(s, 3, "请输入行数", "自定义难度选择", 0, 0, 1);
					sscanf(s, "%d", &row);
					if (row <= 24 && row > 3)
					{
						flag = 1;
					}
					if (row > 24)
					{
						MessageBox(hWnd, "亲~，你输入的太大啦！\n行数应大于3，小于25！", "提示", MB_OKCANCEL);
					}
					else if (row <= 3)
					{
						MessageBox(hWnd, "亲~，你输入的太小啦！\n行数应大于3，小于25！", "提示", MB_OKCANCEL);
					}
				}
				flag = 0;
				while (flag == 0)
				{
					char s[2];
					InputBox(s, 3, "请输入列数", "自定义难度选择", 0, 0, 0);
					sscanf(s, "%d", &col);
					if (col <= 30 && col > 3)
					{
						flag = 1;
					}
					if (col > 30)
					{
						MessageBox(hWnd, "亲~，你输入的太大啦！\n列数应大于3，小于31！", "提示", MB_OKCANCEL);
					}
					else if (col <= 3)
					{
						MessageBox(hWnd, "亲~，你输入的太小啦！\n列数应大于3，小于31！", "提示", MB_OKCANCEL);
					}
				}
				flag = 0;
				while (flag == 0)
				{
					char s[3];
					InputBox(s, 4, "请输入雷数", "自定义难度选择", 0, 0, 0);
					sscanf(s, "%d", &mine);
					if ((mine <= (row * col) - 1) && mine >= 1)
					{
						flag = 1;
					}
					if (mine > (row * col) - 1)
					{
						MessageBox(hWnd, "亲~，你输入的太大啦！\n雷数应大于1，小于列数乘行数！", "提示", MB_OKCANCEL);
					}
					else if (mine < 1)
					{
						MessageBox(hWnd, "亲~，你输入的太小啦！\n雷数应大于1，小于列数乘行数！", "提示", MB_OKCANCEL);

					}
				}
				B.row = row;
				B.col = col;
				B.mine = mine;
				return 4;
			}
		}
	}
}

char** Malloc2d(char*** a, const int row, const int col)//二维数组自定义
{
	//实现自定义二维数组的必需品
	*a = (char**)malloc(row * sizeof(char*));
	if (*a == NULL)
	{
		return NULL;
	}
	**a = (char*)malloc(row * col * sizeof(char));
	if (**a == NULL)
	{
		return NULL;
	}
	for (int i = 1; i < row; i++)
	{
		*(*a + i) = *(*a + i - 1) + col;
		if (*(*a + i) == NULL)
		{
			return NULL;
		}
	}
	return *a;
}

void Destroy(char*** a, const int row, const int col)//消除二维数组的内存
{
	free(*(*a + 0));
	(*(*a + 0)) = NULL;
	free(*a);
	*a = NULL;
}

void INIB(char** a, const int row, const int col, char set)//初始化棋盘
{
	int i = 0;
	int j = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (i == 0 || j == 0 || i == row - 1 || j == col - 1)
			{
				*(*(a + i) + j) = '#';
			}
			else
			{
				*(*(a + i) + j) = set;
			}
		}
	}
}

void Menuinit()
{
	int i = 0;
	char tmp[5] = { 0 };
	for (i = 0; i < 5; i++)
	{
		sprintf(tmp, "./menu/%d.png", i);
		loadimage(&menu[i], tmp, 168, 76);
	}
}

void Drawinit()
{
	int i = 0;
	char tmp[21] = { 0 };
	for (i = 0; i < 20; i++)
	{
		sprintf(tmp, "./image/%d.png", i);
		loadimage(&img[i], tmp, Size, Size);
	}
}

void SetMine(char** a, int row, int col,int c,int d)
{
	int count = B.mine;
	while (count)
	{
		//生成随机下标
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (a[x][y] == '.' && !(x == c && y == d))//防止重复布置雷
		{
			a[x][y] = '*';
			count--;
		}
	}
}

void TimeCount()
{
	end = clock();
	if (/*(((end - begin) % (CLOCKS_PER_SEC)) == 0) &&*/ L.count != 0)
	{
		//printf("%d s\n", (end - begin) / (CLOCKS_PER_SEC));
		L.timeC = (end - begin) / (CLOCKS_PER_SEC);
	}
	int j = L.timeC;
	char arr[999] = { 0 };
	settextstyle(30, 0, "黑体");
	settextcolor(RGB(166, 66, 102));
	_itoa(j, arr, 10);
	outtextxy(7 * (B.col * Size) / 32, 10, ("%s"" s", arr));
}

void MineCount()
{
	int m = (B.mine - L.count2);
	char arr[2] = { NULL };
	sprintf(arr, "%d", m);
	settextstyle(30, 0, "黑体");
	settextcolor(RGB(166, 66, 102));
	outtextxy(24 * (B.col * Size) / 32, 10, arr);
	if ((B.mine - L.count2 <= 9) && (B.mine - L.count2 >= 0))
	{
		setlinestyle(PS_SOLID, 5);//设置线条样式
		setfillcolor(RGB(204, 204, 204));//设置填充颜色
		setlinecolor(RGB(204, 204, 204));//设置线条颜色
		solidrectangle((24 * (B.col * Size) / 32) + 15, 5, (B.col * Size), 45);
	}
	else if ((B.mine - L.count2 >= -9) && (B.mine - L.count2 <= 0))
	{
		setlinestyle(PS_SOLID, 5);//设置线条样式
		setfillcolor(RGB(204, 204, 204));//设置填充颜色
		setlinecolor(RGB(204, 204, 204));//设置线条颜色
		solidrectangle((24 * (B.col * Size) / 32) + 30, 5, (B.col * Size), 45);
	}
}

void DisplayA()
{
	printf("Game in progress\n");
	printf("%d ", L.count);
	printf("%d ", L.timeC);
	printf("%d ", L.LeftCount);
	printf("%d\n", B.mine - L.count2);
}

void DisplayB(char** a, const int row, const int col)//打印棋盘
{
	int i = 0;
	int j = 0;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			printf("%c", *(*(a + i) + j));
		}
		printf("\n");
	}
}

void DisplayChange(char** a, char** b, const int row, const int col)//打印最终棋盘
{
	int i = 0;
	int j = 0;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (a[i][j] == '*')
			{
				continue;
			}
			else
			{
				a[i][j] = b[i][j];
			}
		}
	}
}

void GameDraw(char** b, const int row, const int col)
{
	int i = 0;
	int j = 0;
	for (i = 1; i <= row; i++)
	{
		for (j = 1; j <= col; j++)
		{
			if (b[i][j] == '.')
			{
				putimage((j - 1) * Size, (i - 1) * Size + 50, &img[9]);
			}
			else if (b[i][j] == '!')
			{
				putimage((j - 1) * Size, (i - 1) * Size + 50, &img[10]);
			}
			else if (b[i][j] == '?')
			{
				putimage((j - 1) * Size, (i - 1) * Size + 50, &img[11]);
			}
			else if (b[i][j] == '*' && L.win == 0)
			{
				putimage((j - 1) * Size, (i - 1) * Size + 50, &img[13]);
			}
			else if (b[i][j] == '*' && L.win == 1)
			{
				putimage((j - 1) * Size, (i - 1) * Size + 50, &img[12]);
			}
			else if (b[i][j] >= '0' && b[i][j] <= '8')
			{
				putimage((j - 1) * Size, (i - 1) * Size + 50, &img[b[i][j] - '0']);
			}
			else
			{
				printf("ER");
			}
		}
	}
}

int get_minecount(char** a, int x, int y)//3x3找雷函数
{
	int count = 0;

	if (x > 0 && y > 0 && a[x - 1][y - 1] == '*')
		count++;
	if (x > 0 && a[x - 1][y] == '*')
		count++;
	if (x > 0 && y < B.col + 1 && a[x - 1][y + 1] == '*')
		count++;
	if (y > 0 && a[x][y - 1] == '*')
		count++;
	if (y < B.col + 1 && a[x][y + 1] == '*')
		count++;
	if (x < B.row + 1 && y > 0 && a[x + 1][y - 1] == '*')
		count++;
	if (x < B.row + 1 && a[x + 1][y] == '*')
		count++;
	if (x < B.row + 1 && y < B.col + 1 && a[x + 1][y + 1] == '*')
		count++;

	return count;
}

void open(char** a, char** b, int x, int y) //打开格子
{

	if (b[x][y] == '.' || b[x][y] == '?')
	{
		int count = get_minecount(a, x, y); //计算周围雷的数量
		b[x][y] = count + '0';//将数字写在该格子上
		a[x][y] = '-';
		if (count == 0) //周围没有雷，递归打开周围8个格子
		{
			if (x > 0 && y > 0 && a[x - 1][y - 1] != '-' && b[x - 1][y - 1] != '!')
				open(a, b, x - 1, y - 1);
			if (x > 0 && a[x - 1][y] != '-' && b[x - 1][y] != '!')
				open(a, b, x - 1, y);
			if (x > 0 && y < B.col && a[x - 1][y + 1] != '-' && b[x - 1][y + 1] != '!')
				open(a, b, x - 1, y + 1);
			if (y > 0 && a[x][y - 1] != '-' && b[x][y - 1] != '!')
				open(a, b, x, y - 1);
			if (y < B.col && a[x][y + 1] != '-' && b[x][y + 1] != '!')
				open(a, b, x, y + 1);
			if (x < B.row && y > 0 && a[x + 1][y - 1] != '-' && b[x + 1][y - 1] != '!')
				open(a, b, x + 1, y - 1);
			if (x < B.row && a[x + 1][y] != '-' && b[x + 1][y] != '!')
				open(a, b, x + 1, y);
			if (x < B.row && y < B.col && a[x + 1][y + 1] != '-' && b[x + 1][y + 1] != '!')
				open(a, b, x + 1, y + 1);
		}
	}
}

int MouseSelectMode(char** a, char** b, const int row, const int col, const int mine)
{
	ExMessage msg;//获取鼠标信息
	int num = 0;
	int sum = 0;
	int c = 0;
	int d = 0;
	GameDraw(b, row, col);
	while (1)
	{
		//Sleep(1);
		L.win = 0;
		if (L.lose == 1)//失败返回
		{
			return 0;
		}
		if (peekmessage(&msg, EM_MOUSE))
		{
			d = msg.x / (Size) + 1;
			if (msg.y - 50 < 0)
			{
				continue;
			}
			c = (msg.y - 50) / (Size)+1;
			switch (msg.message)
			{
			case WM_LBUTTONUP:
			{
				L.LeftCount++;
				FindMine(a, b, B.row, B.col, B.mine, c, d);			
				break;
			}
			case WM_RBUTTONUP:
			{
				EditFlag(b, B.row, B.col, c, d);
				break;
			}
			case WM_LBUTTONDBLCLK:
			case WM_MBUTTONDOWN:
			{
				FindMine2(a, b, B.row, B.col, B.mine, c, d);
				break;
			}
			default:
			{
				break;
			}
			}
		}
		MineCount();
		
		if (judgement(b, row, col, mine))
		{
			Win(a, b);
			return 0;
		}
		if (!L.lose && !L.win)
		{
			putimage((((B.col * Size) / 2) - 15), 10, &img[14]);
			TimeCount();
			GameDraw(b, row, col);
		}
	}
	return 0;
}

int judgement(char** b, const int row, const int col, const int mine) //判断是否赢得游戏
{
	int i = 0;
	int j = 0;
	int sum = 0;
	for (i = 1; i < row + 1; i++)
	{
		for (j = 1; j < col + 1; j++)
		{
			if (b[i][j] == '.' || b[i][j] == '!' || b[i][j] == '?')
			{
				sum++;
			}
		}
	}
	if (sum == mine)
	{
		return 1;
	}
	return 0;
}

int judgementLeftClick(char** b, const int x, const int y)
{
	if (b[x][y] == '.' || b[x][y] == '?')
	{
		return 1;
	}
	return 0;
}

int judgementDoubleClick(char** b, int x, int y)//判断双击操作是否正确
{
	int num = b[x][y] - '0';
	int count = 0;
	int i = 0;
	int j = 0;
	for (i = x - 1; i <= x + 1; i++)
	{
		for (j = y - 1; j <= y + 1; j++)
		{
			if (b[i][j] == '!')
			{
				count++;
			}
		}
	}
	if (count == num)
	{
		return 1;
	}
	return 0;
}

void Win(char** a, char** b)
{
	//printf("Game over, you win\n");
	//printf("%d ", L.count);
	//printf("%d\n", B.mine - L.count2);
	DisplayChange(a, b, B.row, B.col);
	//DisplayB(a, B.row, B.col);
	putimage((((B.col * Size) / 2) - 15), 10, &img[16]);
	L.win = 1;
	GameDraw(a, B.row, B.col);
	settextstyle(B.col * 2.7, 0, "黑体");
	setbkmode(TRANSPARENT);//设置透明
	settextcolor(RGB(255, 84, 140));
	char arr[] = "_ 乾杯！[]~(￣▽￣)~*";
	int width = (B.col * Size) / 2 - textwidth(arr) / 2;
	int height = (B.row * Size) / 2 - textheight(arr) / 2;
	outtextxy(width, height + 30, arr);
	HWND bk = GetHWnd();
	SetWindowText(bk, "_ 乾杯！[]~(￣▽￣)~*");
}

void Lose(char** a, char** b)
{
	//printf("Hit mine, you lose\n");
	//printf("%d ", L.count);
	//printf("%d\n", B.mine - L.count2);
	DisplayChange(a, b, B.row, B.col);
	putimage((((B.col * Size) / 2) - 15), 10, &img[15]);
	GameDraw(a, B.row, B.col);
	//putimage((((B.col * Size) / 2) - 15), 10, &img[15]);
	//DisplayB(a, B.row, B.col);
	settextstyle(B.col * 6.6, 0, "黑体");
	setbkmode(TRANSPARENT);//设置透明
	settextcolor(RED);
	char arr[] = "BOOM!!!";
	int width = (B.col * Size) / 2 - textwidth(arr) / 2;
	int height = (B.row * Size) / 2 - textheight(arr) / 2;
	outtextxy(width, height + 30, arr);
	HWND bk = GetHWnd();
	SetWindowText(bk, ":(");
	L.lose = 1;
}

int FindMine(char** a, char** b, const int row, const int col, const int mine, const int inputa, const int inputb)//1 操作找雷
{
	int i = inputa;
	int j = inputb;
	int num = 0;
	//scanf("%d", &i);
	//scanf("%d", &j);
	if ((i >= 1 && i <= row) && (j >= 1 && j <= col))
	{
		L.count++;
		if (judgementLeftClick(b, i, j))
		{
			if (a[i][j] == '*')
			{
				Lose(a, b);
				return 0;
			}
			else
			{
				if (L.LeftCount == 1)
				{
					SetMine(a, B.row, B.col, i, j);
					//printf("\n");
					//DisplayB(a, B.row, B.col);					
				}
				if (L.count == 1)
				{
					begin = clock();
				}
				open(a, b, i, j);
				return 0;
			}
		}
		else
		{
			if (L.LeftCount == 1)
			{
				L.LeftCount = 0;
			}
			return 0;
		}
	}
	else
	{
		if (L.LeftCount == 1)
		{
			L.LeftCount = 0;
		}
		return 0;
	}
}

int FindMine2(char** a, char** b, const int row, const int col, const int mine, const int inputa, const int inputb)//9 双击扫雷
{
	int i = inputa;
	int j = inputb;
	int sum = 0;
	int num = 0;
	//scanf("%d", &i);
	//scanf("%d", &j);
	if ((i >= 1 && i <= row) && (j >= 1 && j <= col))
	{
		int x = 0;
		int y = 0;
		L.count++;
		if (judgementDoubleClick(b, i, j))
		{
			for (x = -1; x <= 1; x++)
			{
				for (y = -1; y <= 1; y++)
				{
					if (a[i + x][j + y] == '*' && b[i + x][j + y] != '!')
					{
						Lose(a, b);
						return 0;
					}
				}
			}
			for (x = -1; x <= 1; x++)
			{
				for (y = -1; y <= 1; y++)
				{
					open(a, b, i + x, j + y);

				}
			}
		}
		else
		{
			L.count--;//后置添加，防止提前因错误操作启动计时器
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

int EditFlag(char** b, const int row, const int col, const int inputa, const int inputb)//2、3、4步骤操作的图形化使用
{
	int i = inputa;
	int j = inputb;
	int num = 0;
	char c = b[i][j];
	if ((i >= 1 && i <= row) || (j <= 1 && j >= col))
	{
		L.count++;
		if (L.count == 1)
		{
			begin = clock();
		}
		if (c == '!')
		{
			L.count2--;
			b[i][j] = '?';
		}
		if (c == '?')
		{
			b[i][j] = '.';
		}
		if (c == '.')
		{
			L.count2++;
			b[i][j] = '!';
		}
	}
	else
	{
		return 0;
	}
	return 0;
}
