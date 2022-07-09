#include<stdio.h>
#include<graphics.h>

//窗口宽度高度
enum My
{
	WIDTH = 480,
	HEIGHT = 700,

	//玩家子弹数量
	BULLLET_NUM = 15,
};

//飞机位置结构
struct Plance
{
	int x;
	int y;

	//定义飞机是否存活
	bool live;
}player,bull[BULLLET_NUM];

//背景图片加载
IMAGE bk;

//玩家图片加载
IMAGE img_role[2];

//子弹加载
IMAGE img_bull[2];

void loadImage()
{	
	//加载背景图片
	loadimage(&bk, "./img/background.png");

	//加载玩家图片
	loadimage(&img_role[0], "./img/me2.png");
	loadimage(&img_role[1], "./img/me3.png");

	//加载子弹
	loadimage(&img_bull[0], "./img/bullet2.png");
	loadimage(&img_bull[1], "./img/bullet3.png");
}

//游戏初始
void gameInit()
{
	player.x = (WIDTH / 2) - 20;
	player.y = HEIGHT - 120;
	player.live = true;

	//子弹初始化
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live = false;
	}
}

//游戏绘制函数
void gameDraw()
{
	//背景图片加载
	loadImage();
	putimage(0, 0, &bk);

	//玩家图片加载
	putimage(player.x, player.y, &img_role[1],NOTSRCERASE);
	putimage(player.x, player.y, &img_role[0],SRCINVERT);

	for (int i = 0; i < BULLLET_NUM; i++)
	{
		if (bull[i].live)
		{
			putimage(bull[i].x, bull[i].y, &img_bull[0], NOTSRCERASE);
			putimage(bull[i].x, bull[i].y, &img_bull[1], SRCINVERT);
		}
	}
}

//子弹发射判断
void createBullet()
{
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		if (!bull[i].live)
		{
			bull[i].x = player.x + 60;
			bull[i].y = player.y;
			bull[i].live = true;
			break;
		}
	}
}

void BulletMove()
{
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		if (bull[i].live)
		{
			bull[i].y -= 1;
			if (bull[i].y < 0)
			{
				bull[i].live = false;
			}
		}
	}
}

//玩家移动
void playerMove(int speed)
{	
	//W,S,A,D控制移动
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W'))
	{
		if (player.y > 0)
		{
			player.y -= speed;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))
	{
		if (player.y + 126 < HEIGHT)
		{
			player.y += speed;
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))
	{
		if (player.x + 60 > 0)
		{
			player.x -= speed;
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))
	{
		if (player.x + 60 < WIDTH)
		{
			player.x += speed;
		}
	}
	//空格发射子弹
	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState(VK_SPACE) && t2 - t1 > 100)
	{
		//创建一个子弹
		createBullet();
		t1 = t2;
	}
	t2 = GetTickCount();
}

int main()
{
	//创建图形窗口
	initgraph(WIDTH, HEIGHT);
	gameInit();

	//双缓冲绘图
	BeginBatchDraw();
	while (1)
	{
		gameDraw();
		FlushBatchDraw();
		playerMove(2);
		BulletMove();
	}
	EndBatchDraw();
	return 0;
}