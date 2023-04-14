/*#include <math.h>
#include <stdio.h>
int main()
{
	for (int i = 99; i < 1000; i++)
	{
		if (i == (i / 100) *( i / 100) *( i / 100) + ((i / 10) % 10) * ((i / 10) % 10) * ((i / 10) % 10) + (i % 10) * (i % 10) * (i % 10))
		{
			printf("%d\n", i);
		}
	}
	int i;
	scanf_s("%d", &i);
	return 0;
}


*/
/*
#include <graphics.h>

int main()
{
	initgraph(640, 480);
	 BeginBatchDraw();

	setlinecolor(WHITE);
	setfillcolor(RED);

	for (int i = 50; i < 600; i++)
	{
		cleardevice();
		circle(i, 100, 40);
		floodfill(i, 100, WHITE);
		 FlushBatchDraw();
		Sleep(10);
	}

	 EndBatchDraw();
	closegraph();
}
*/


#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//include "winres.h"

struct youkuli;
/*
int main()
{
	initgraph(1000, 600);
	int x_youkuli = 40, y_youkuli = 290;
	int g = 5;
	int v_x_youkuli = 10, v_y_youkuli = -20;
	IMAGE reimu;//(268,268);              //导入灵梦图片
	
	loadimage(NULL, _T("D:\\Backup\\Documents\\background.JPG")); //导入背景
	loadimage(&reimu, _T("D:\\Backup\\Documents\\reimu.jpg",TRUE));//导入灵梦图片
	while (1)
	{
		putimage(x_youkuli, y_youkuli, x_youkuli + 268,y_youkuli + 268, &reimu, 0,0);   //图像左上角坐标，图像右下角坐标，图像地址，绘制图像某一点右下角
		//putimage(0, 0, 268, 268, &reimu,100,100);
	}
	return 0;
}
*/
typedef  struct enen
{
	int distance = -10;    //距离恩恩的距离
	bool enen_exist = false;       //判断恩恩是否还在（未被清除）
} judge_enen;

//typedef 
struct like        //亲密度
{
	int like;         //亲密度
	char name_of_youkuli[256];    //油库里名字
	char number_of_youkuli[256];     //油库里编号（用于识别）
	char special_of_youkuli = 'null';  //油库里的特别之处（用于识别）
};//judge_like;
  struct youkuli
{
	char name[5];  //（种类）
	float age;
	int nature;       //渣滓度(数值)     y
	int Hp;           //体力（生命值）   y
	int strength;     //活力（活跃度）（强壮程度） y
	int happness;     //油库里的幸福度   y
	bool sleep = false;       //是否睡眠
	bool death = false;
	int hungry;       //饱食度          y
	int height;       //离地高度
	bool hat = true;         //有无头饰
	bool hair = true;        //有无头发
	char hand = 'null';        //手里有无东西，默认为null    //树枝，书， 食物，
	char mouth = 'null';       //嘴里有无东西，默认为null    //食物，树枝，小油库里，礼物，恩恩，
	bool peinipieni = false;     //是否长出佩妮佩妮，且未被切掉
	bool putrid = false;         //是否得了油梅
	bool smart = false;          //是否茄化  （可能是变胖变笨（痴呆）
	int knowledge;       //智力值（聪明程度）
	bool isyoukuli = true;      //是否没得非油，默认为true（没得）
	bool predator = false;       //是否为捕食种
	bool hurtten = false;        //是否正在被虐待
	bool broken = false;         //是否漏馅（破损严重）
	bool burn = false;           //是否被点燃
	bool need_yogurt = false;    //是否便秘
	bool teeth = true;          //是否还有牙齿
	bool eye = true;            //是否还有眼睛
	bool face = true;           //是否还有两腮
	struct judge_like;
	int heath = 1000;           //身体状况（用于调节生命值改变速度）(最大为1000)
	bool DOS = false;            //是否为DOS种
	int trust;           //对人类（玩家）的信任度（亲密度）（不害怕程度）

	int eatting_picky;    //肥舌度
	int number;          //编号【（是第几个生成的同种油库里）】  （是当前环境中第几只油库里）（用于区分）
	int died_youkuli_nearby = 0;          //周围环境中死亡油库里的数量
	char place_from;     //在哪里捕捉到的
	int isexisted = 0; //判断是否被生成，默认没有


	//待定，代码应该不是这么写的
	struct like every_like;
	//
	char special;
}youkuli[256][256];





void judge_youkuli_move_direction(int v_x_youkuli, int x_youkuli, int y_youkuli, IMAGE* youkuli_right, IMAGE* youkuli_left)   //根据油库里(左右)运动方向判断输出图片
{
	if (v_x_youkuli >= 0)
	{
		putimage(x_youkuli, y_youkuli, x_youkuli + 268, y_youkuli + 268, youkuli_right, 0, 0);
	}
	else
	{
		putimage(x_youkuli, y_youkuli, x_youkuli + 268, y_youkuli + 268, youkuli_left, 0, 0);
	}
}
char judge_arca(int(x_1), int(y_1), int(x_2), int(y_2), int* (x), int* (y), int r, int* v_x, int* v_y, int g)   //左上角，右下角，球坐标，球速度        //防越界,,加反弹
//返回值是为了判断哪里反弹了（可能）

{
	if (*x - r <= x_1)
	{
		*x = x_1 + r;
		*v_x = -*v_x;
		return 'x';
	}
	if (*x + r >= x_2)
	{
		*x = x_2 - r;
		*v_x = -*v_x;
		return 'x';
	}
	if (*y - r <= y_1)
	{
		*y = y_1 + r;
		*v_y = -*v_y;
		return 'y';
	}
	if (*y + r >= y_2)
	{

		*y = y_2 - r;
		*v_y = -*v_y;
		return 'y';
	}
	return 0;
}

void move_youkuli_jump(int* x, int* y, int r, int g, int* v_x_youkuli, int* v_y_youkuli, IMAGE *image_youkuli_right, IMAGE *image_youkuli_left, IMAGE* bk)   //g是重力加速度       油库里跳跃
//图片取地址是因为putimage需要地址
{
	//putimage(*x, *y, 134, 134, bk, 0, 0);
	int tem_y_ground = 300 + 2 * r;  //全局常量300,油库里的初始站立位置（y）
	int tem = (2 * (abs(*v_y_youkuli) / g)) + 1;
	for (int i = 1; i <= tem; i++)
	{
		int tem_place = judge_arca(0, 0, 1000, tem_y_ground, x, y, r, v_x_youkuli, v_y_youkuli, g);
		*x += *v_x_youkuli;
		*y += *v_y_youkuli;
		*v_y_youkuli += g;
		judge_youkuli_move_direction(*v_x_youkuli, *x, *y, image_youkuli_right, image_youkuli_left);
		FlushBatchDraw();
		Sleep(1000 / 6);
		putimage(*x, *y, 134, 134, bk, 0, 0);    //覆盖
	}
	*v_y_youkuli = -20;  //额外设置的全局常量，油库里的纵向速度（间接控制油库里站立地面的高度）
	int frist = 600; //rand() % 5000 + 2000;      //生成2000到5000的随机数
	Sleep(frist / 6);
}


void move_many_youkuli_jump(int x[], int y[], int r, int g, int* v_x_youkuli, int* v_y_youkuli, IMAGE *image_youkuli_right, IMAGE *image_youkuli_left, IMAGE* bk)
//批量油库里跳跃
/*
{
	const int number_number = sizeof(x) / sizeof(x[0]);//（计算油库里个数）
	for (int i = 0; i <= number_number; i++)
	{
		//putimage(x[i], y[i], 134, 134, bk, 0, 0);

	}
	int tem_y_ground = 300 + 2 * r;  //全局常量300,油库里的初始站立位置（y）
	int tem = (2 * (abs(*v_y_youkuli) / g)) + 1;//保证跳跃前后高度相同
	for (int i = 0; i <= number_number; i++)   //逐个油库里运动
	{
		int tem_place = judge_arca(0, 0, 1000, tem_y_ground, &x[i], &y[i], r, v_x_youkuli, v_y_youkuli, g);
		x[i] += *v_x_youkuli;
		y[i] += *v_y_youkuli;
		*v_y_youkuli += g;

		for (int j = 0; j <= tem; j++)  //单独一个油库里运动
		{
			judge_youkuli_move_direction(*v_x_youkuli, x[i], y[i], &image_youkuli_right,& image_youkuli_left);
		}

		//FlushBatchDraw();
		Sleep(100);
		//putimage(x[i], y[i], 134, 134, bk, 0, 0);    //覆盖
	}
	*v_y_youkuli = -20;  //额外设置的全局常量，油库里的纵向速度（间接控制油库里站立地面的高度）

	//int frist = rand() % 5000 + 2000;      //生成2000到5000的随机数
	Sleep(500);
}
*/
//批量油库里运动
{
	int number = sizeof(x) / sizeof(x[0]);
	for (int i = 0; i < number; i++)
	{
		move_youkuli_jump(&x[i], &y[i], r, g, v_x_youkuli, v_y_youkuli, image_youkuli_right, image_youkuli_left, bk);
	}
}
int main()
{
	/*
	//srand(time(0));
	youkuli frist , second;
	like frist_to_second;
	frist_to_second.like = 120;
	youkuli test_1;
	test_1.every_like.like = frist_to_second.like;
	printf_s("%d", test_1.every_like.like);


	ExMessage lmouse = {0,0,0,0,0,0,0,0};
	lmouse.lbutton = 0;
	initgraph(1000, 500);
	fillrectangle(20, 20, 300, 300);
	int add = 1;
	while (1)
	{
		
		bool place_mouse = (lmouse.x >= 20 && lmouse.x <= 300 && lmouse.y >= 20 && lmouse.y <= 300);
		//lmouse.lbutton = 
		//getmessage(&lmouse, WM_LBUTTONDOWN);
		peekmessage(&lmouse, WM_LBUTTONDOWN);
		setfillcolor(RED);
		if (
			lmouse.lbutton
			&&
			place_mouse
			)

		{
			fillcircle(lmouse.x, lmouse.y, 20);
		}
		for (int i = 0; i <= 5; i++)
		{
			fillcircle(++add, i, 20);
			Sleep(0.1);
		}
			
		

	}
		*/
	



	initgraph(1000, 600);
	//int x = 500, y = 300, r = 20;

	int x_youkuli = 40, y_youkuli = 290;

	//loadimage(NULL, _T("D:\\2345Downloads\ありす\体"));
	int g = 5;
	int v_x_youkuli = 20, v_y_youkuli = -20;
	//setbkcolor(RED);
	//cleardevice();
	//char locate_reimu;
	
	
	
		IMAGE reimu_right, reimu_left;              //导入灵梦图片
		IMAGE bk;                 //导入背景图片
		loadimage(NULL, _T("D:\\Backup\\Documents\\background.JPG")); //导入背景(不然图像显示不出来)
		loadimage(&bk, _T("D:\\Backup\\Documents\\background.JPG"));
		loadimage(&reimu_right, _T("D:\\Backup\\Documents\\reimu_right.jpg")); //导入灵梦面向右图片
		loadimage(&reimu_left, _T("D:\\Backup\\Documents\\reimu_left.jpg"));//导入灵梦面向左图片
	


	const int max_number_youkuli = 10;
	typedef int number[max_number_youkuli]; //用于赋值油库里各项数值的数组(生成默认十一份的数组)
	//有毛病
	int number_youkuli = 7; // rand() % max_number_youkuli + 1;  //生成1到10个油库里
	int test_nature[max_number_youkuli];                   //待生成的油库里的渣滓度（中括号里大于10就行）
	//youkuli test[max_number_youkuli];                     //生成油库里的最大数量（大于10就行）     //???
	number test_x_youkuli, test_y_youkuli;//各油库里的坐标（数组）
	for (int i = 0; i <= number_youkuli; i++)
	{
		test_nature[i] = rand() % 251 + 50;//在50到300生成渣滓度

		youkuli[1][i].nature = test_nature[i];    //赋值渣滓度
		//printf_s("%d\n", test[i].nature);   //显示渣滓度
		test_x_youkuli[i] = rand() % 501 + 50;   //生成位置
		test_y_youkuli[i] = 300;
	}
	IMAGE tem_bk;//临时背景
	while (1)
	{
		//srand(time(0));                                                        
		for (int i = 0; i <= number_youkuli; i++)  //显示油库里
		{
			//getimage(&tem_bk, 0, 0, 1000, 600);
			for (int j = 0; j <= number_youkuli; j++)
			{
				//putimage(*test_x_youkuli, *test_y_youkuli, 134, 134, &bk, 0, 0);

				move_many_youkuli_jump(test_x_youkuli, test_y_youkuli, 30, g, &v_x_youkuli, &v_y_youkuli, &reimu_right, &reimu_left, &bk);
				//putimage(*test_x_youkuli, *test_y_youkuli, 134, 134, &bk, *test_x_youkuli, *test_y_youkuli, 0);
				judge_youkuli_move_direction(v_x_youkuli, test_x_youkuli[j], test_y_youkuli[j], &reimu_right, &reimu_left);
			}
			//judge_youkuli_move_direction(v_x_youkuli, test_x_youkuli[i], test_y_youkuli[i], &reimu_right, &reimu_left);
			//putimage(0, 0, &bk);//&tem_bk);

		}

	}
}