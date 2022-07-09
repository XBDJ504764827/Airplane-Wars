#include<stdio.h>
#include<graphics.h>

//���ڿ�ȸ߶�
enum My
{
	WIDTH = 480,
	HEIGHT = 700,

	//����ӵ�����
	BULLLET_NUM = 15,
};

//�ɻ�λ�ýṹ
struct Plance
{
	int x;
	int y;

	//����ɻ��Ƿ���
	bool live;
}player,bull[BULLLET_NUM];

//����ͼƬ����
IMAGE bk;

//���ͼƬ����
IMAGE img_role[2];

//�ӵ�����
IMAGE img_bull[2];

void loadImage()
{	
	//���ر���ͼƬ
	loadimage(&bk, "./img/background.png");

	//�������ͼƬ
	loadimage(&img_role[0], "./img/me2.png");
	loadimage(&img_role[1], "./img/me3.png");

	//�����ӵ�
	loadimage(&img_bull[0], "./img/bullet2.png");
	loadimage(&img_bull[1], "./img/bullet3.png");
}

//��Ϸ��ʼ
void gameInit()
{
	player.x = (WIDTH / 2) - 20;
	player.y = HEIGHT - 120;
	player.live = true;

	//�ӵ���ʼ��
	for (int i = 0; i < BULLLET_NUM; i++)
	{
		bull[i].x = 0;
		bull[i].y = 0;
		bull[i].live = false;
	}
}

//��Ϸ���ƺ���
void gameDraw()
{
	//����ͼƬ����
	loadImage();
	putimage(0, 0, &bk);

	//���ͼƬ����
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

//�ӵ������ж�
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

//����ƶ�
void playerMove(int speed)
{	
	//W,S,A,D�����ƶ�
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
	//�ո����ӵ�
	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState(VK_SPACE) && t2 - t1 > 100)
	{
		//����һ���ӵ�
		createBullet();
		t1 = t2;
	}
	t2 = GetTickCount();
}

int main()
{
	//����ͼ�δ���
	initgraph(WIDTH, HEIGHT);
	gameInit();

	//˫�����ͼ
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