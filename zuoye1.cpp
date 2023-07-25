#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <time.h>
#include <easyx.h>
#include <conio.h>
#include <memory>
#include <map>
#include <string>
//#include <atlstr.h>
using std::vector;
#define screen_x 1000
#define screen_y 600
class youkuli;

enum mouse_status { do_nothing, pick_up, touching_ground, drop_down };//放到define_inf头文件里,需要改成youkuli_status或者分为两个枚举型

typedef std::pair<mouse_status, LPCTSTR> words_type;
class youkuli_words//储存文字
{
private:
	std::multimap<mouse_status, LPCTSTR> words;
public:
	youkuli_words()
	{
		
	}
	void push_in(mouse_status frist,LPCTSTR second)
	{
		this->words.insert(words_type(frist, second));
	}
	
	inline youkuli_words& operator>>(std::pair<mouse_status,LPCTSTR> added_word)
	{
		this->words.insert(added_word);
		return *this;
	}
	inline LPCTSTR get(mouse_status which)
	{
		auto tem_frist =this->words.find(which);
		if (this->words.end() == tem_frist)
		{
			return _T("???");
		}
		//auto range = this->words.equal_range(which);//返回的是两个迭代器
		int max_num = (rand () % this->words.count(which));
		for (int i = 0; i != max_num; i++)
		{
			tem_frist++;
		}
		return (*tem_frist).second;
	}
}youkuli_words_library;

int g = 2;
template <class T>
T youkuli_template{};
//std::map<LPCTSTR ,youkuli&> family;//文字(换成枚举型了)是指该油库里的身份（父亲，母亲，姐姐之类的）
enum which_family_member {mom,father,big_sister,small_sister,sister};
namespace interaction
{
	
	void wiping_face(youkuli&  one, youkuli&  another)
	{
		
		return;
	}
}



class _mouse_
{
private:
	ExMessage my_mouse = {EX_MOUSE};
	int status = pick_up;

public:
	bool is_pick_youkuli = false;
	inline void inter_status(mouse_status status)
	{
		this->status = status;
	}
	inline int get_status()
	{
		return this->status;
	}
	inline POINT get_place()
	{
		POINT tem_mouth = {this->my_mouse.x,this->my_mouse.y};
		return tem_mouth;
	}
	inline bool get_lbutton()
	{
		peekmessage(&this->my_mouse,EX_MOUSE);
		return this->my_mouse.lbutton;
	}
}mouse;
template<class T>

bool judge_inside (_mouse_ place_mouse, T youkuli_mouse,LONG range)
{
	//bool top_left = ((place_mouse.get_place().x - ))
	return true;
}

class all_picture//图库
{
protected:
	int status_youkuli;
	vector<IMAGE> body_normal_set;//无事发生时的图组
	vector<IMAGE> body_picked_up_set;//被拿起来时的图组
	vector<IMAGE> body_drop_down_set;//从高处落下后（从接触地面开始）的图组
	vector<IMAGE> body_touching_ground_set;//被按在地上拖行的图组

public:
	all_picture();
	//旧的>>重载，可能有问题，不确定
	/*
	all_picture* operator>> (LPCTSTR picture_place)
	{
		IMAGE* tem = new IMAGE;
		loadimage(tem, picture_place);
		this->body_set.push_back(*tem);
		delete tem;
		tem = nullptr;
		return this;
	}
	*/
	all_picture& operator>> (LPCTSTR picture_place)
	{
		IMAGE* tem = new IMAGE;
		loadimage(tem, picture_place);
		this->body_normal_set.push_back(*tem);
		delete tem;
		tem = nullptr;
		return *this;
	}
	size_t size()
	{
		switch (this->status_youkuli)
		{
		case do_nothing:
			return this->body_normal_set.size();
			break;
		case pick_up:
			return this->body_picked_up_set.size();
			break;
		case drop_down:
			return this->body_drop_down_set.size();
			break;
		case touching_ground:
			return this->body_touching_ground_set.size();
			break;
		default :
			return -1;
			break;
		}
	}
	IMAGE get_image(mouse_status which)
	{
		if (which >= this->size())
		{
			which = (mouse_status)(this->size() - 1);
		}
		switch (this->status_youkuli)
		{
		case do_nothing:
			return this->body_normal_set[which];
			break;
		case pick_up:
			return this->body_picked_up_set[which];
			break;
		case drop_down:
			return this->body_drop_down_set[which];
			break;
		case touching_ground:
			return this->body_touching_ground_set[which];
			break;
		default:
			return -1;
			break;
		}
	}
	inline void change_status(mouse_status status)
	{
		this->status_youkuli = status;
	}


};
class youkuli_body : public all_picture
{
public:
	//IMAGE hair;
	IMAGE body;
	//IMAGE eye;
	//IMAGE mouth;
	//IMAGE cheek;
	youkuli_body()
	{
		this->body = this->body_normal_set[0];
	}
	inline IMAGE* get_body()
	{
		return &(this->body);
	}
};

all_picture::all_picture()
{
	this->status_youkuli = do_nothing;
	this->body_normal_set.reserve(sizeof IMAGE * 7);
	this->body_picked_up_set.reserve(sizeof IMAGE * 9);
	this->body_drop_down_set.reserve(sizeof IMAGE * 31);
	this->body_touching_ground_set.reserve(sizeof IMAGE * 2);
	char load[] = "./all_gif2.png";
	//IMAGE* tem;
	//tem = new IMAGE;
	auto init_pic = []()
	{
		//std::shared_ptr<IMAGE> tem = std::make_shared<IMAGE>(1);
		IMAGE tem;
		loadimage(&tem, L"./all_gif2.png");//第一张坏了，到时候重新导出一张
		return tem;
	};
	//导入静止（现在是运动）状态的图片
	
	for (int i = 0; i != 7; i++)
	{
		//load[9] = '0' + i;
		//LPCTSTR tem_load[] = (LPCTSTR[])load;
		//loadimage(&(this->body_normal_set[0]), );//第一张坏了，到时候重新导出一张
		this->body_normal_set.push_back(init_pic());
	}
	
	loadimage(&(this->body_normal_set[0]), L"./all_gif2.png");//第一张坏了，到时候重新导出一张
	loadimage(&(this->body_normal_set[1]), L"./all_gif2.png");
	loadimage(&(this->body_normal_set[2]), L"./all_gif3.png");
	loadimage(&(this->body_normal_set[3]), L"./all_gif4.png");
	loadimage(&(this->body_normal_set[4]), L"./all_gif5.png");
	loadimage(&(this->body_normal_set[5]), L"./all_gif6.png");
	loadimage(&(this->body_normal_set[6]), L"./all_gif7.png");
	
	//导入被拿起来的图片()
	for (int i = 0; i != 8; i++)
	{
		this->body_picked_up_set.push_back(init_pic());
	}
	loadimage(&(this->body_picked_up_set[0]), L"./all_gif2.png");//第一张坏了，到时候重新导出一张
	loadimage(&(this->body_picked_up_set[1]), L"./all_gif5.png");
	loadimage(&(this->body_picked_up_set[2]), L"./all_gif2.png");
	loadimage(&(this->body_picked_up_set[3]), L"./all_gif5.png");
	loadimage(&(this->body_picked_up_set[4]), L"./all_gif2.png");
	loadimage(&(this->body_picked_up_set[5]), L"./all_gif5.png");
	loadimage(&(this->body_picked_up_set[6]), L"./all_gif2.png");
	loadimage(&(this->body_picked_up_set[7]), L"./all_gif5.png");
	//导入落在地上时的图片
	for (int i = 0; i != 31; i++)
	{
		this->body_drop_down_set.push_back(init_pic());
	}
	loadimage(&(this->body_drop_down_set[0]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[1]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[2]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[3]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[4]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[5]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[6]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[7]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[8]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[9]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[10]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[11]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[12]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[13]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[14]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[15]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[16]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[17]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[18]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[19]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[20]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[21]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[22]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[23]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[24]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[25]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[26]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[27]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[28]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[29]), L"./all_gif5.png");
	loadimage(&(this->body_drop_down_set[30]), L"./all_gif5.png");
	for (int i = 0; i != 2; i++)
	{
		this->body_touching_ground_set.push_back(init_pic());
	}
	loadimage(&(this->body_touching_ground_set[0]), L"./all_gif3.png");
	loadimage(&(this->body_touching_ground_set[1]), L"./all_gif3.png");
	//delete tem;
	//tem = nullptr;
}
class youkuli
{
protected:
	int num;
	int v_x;
	int v_y;
	POINT place;
	POINT mouse_place;
	youkuli_body body;
	bool ismove = false;
	bool is_left = true;//油库里是否向左运动（面向左）`
	bool is_pick_up = false;//是否被拿起
	bool is_health = true;
	bool is_too_high = false;//判断油库里是否应该收到摔落伤害
	int stiff_remaining_time = 0;//僵直状态剩余时间
	std::map<which_family_member, youkuli&>* which_family = nullptr;//指向此油库里所在的家庭map(可能会内存泄露)
	inline void flip_horizontal()//将图片水平翻转（水平镜像）
	{
		DWORD* tem_picture = GetImageBuffer(this->body.get_body());//身体原图片（将要被修改的）
		IMAGE base = *(this->body.get_body());//备用（不变的）
		DWORD* base_picture = GetImageBuffer(&base);//备用（不变的）
		int R = 0, G = 0, B = 0;
		int max = this->body.get_body()->getheight() * this->body.get_body()->getwidth();
		int i_for_tem = 0;//被改写的点的下角标
		int where_x = 0, where_y = 0;//不变的那个图的点的对应坐标
		while (i_for_tem < max)
		{
			if (where_x == this->body.get_body()->getwidth())//换行
			{
				where_x = 0;
				where_y++;
			}
			auto get_order = [&i_for_tem, this, &where_y]()//得到翻转后的下角标
			{
				return ((this->body.get_body()->getwidth() - (i_for_tem % this->body.get_body()->getwidth())) + where_y * this->body.get_body()->getwidth());
			};
			R = GetRValue(base_picture[get_order()]);
			G = GetGValue(base_picture[get_order()]);
			B = GetBValue(base_picture[get_order()]);
			tem_picture[i_for_tem] = RGB(R, G, B);
			where_x++;
			i_for_tem++;
		}
	}
	inline void cutout(IMAGE* picture_retouched,LONG x_top_left,LONG y_top_left)//抠图（直接展示）传入图片指针和图片左上角坐标（这很重要！）
	{
		DWORD* background = GetImageBuffer();
		DWORD* dword_set_retouched = GetImageBuffer(picture_retouched);
		int R = 0, G = 0, B = 0;
		int x_for_background = 0, y_for_background = 0, x_for_picture = 0, y_for_picture = 0;
		int max_y = picture_retouched->getheight(),max_x = picture_retouched->getwidth();
		while (y_for_picture < max_y)
		{
			if (x_for_picture == max_x)//picture_retouched换行
			{
				x_for_picture = 0;
				y_for_picture++;
			}
			auto get_order = [&x_for_picture,&y_for_picture,picture_retouched]()
			{
				return (x_for_picture ) + ( (y_for_picture) * picture_retouched->getwidth());
			};
			R = GetRValue(dword_set_retouched[get_order()]);
			G = GetGValue(dword_set_retouched[get_order()]);
			B = GetBValue(dword_set_retouched[get_order()]);
			if (0 == R && 0 == G && 0 == B)//点是黑色的
			{
				x_for_background = x_top_left + x_for_picture;
				y_for_background = y_top_left + y_for_picture;
				auto another_get_order = [&x_for_background,&y_for_background]()
				{
					return (x_for_background + ((y_for_background) * screen_x)) ;//    //后面的减一是为了防止数组越界（前面的？ 不减一就多出来一行了）
				};
				if (another_get_order() >= 0 && another_get_order() < screen_x * screen_y)//防止越界
				{
					R = GetRValue(background[another_get_order()]);//获取背景颜色
					G = GetGValue(background[another_get_order()]);
					B = GetBValue(background[another_get_order()]);
					dword_set_retouched[get_order()] = RGB(R, G, B);
				}
			}
			x_for_picture++;
		}
	}
	inline POINT update_mouse_place()
	{
		this->mouse_place = mouse.get_place();
		return this->mouse_place;
	}
public:
	int tem_ground;//油库里所站的地平线（只是为了便于观察，不会使用）
	youkuli()
	{
		this->num = -1;
		this->v_x = 0;
		this->v_y = 0;
		this->place = { (rand() % screen_x),(rand() % screen_y) };
		//this->tem_ground = this->place.y;
		this->tem_ground = screen_y - 300;
		this->mouse_place = this->update_mouse_place();
	}
	virtual void draw(void(how_to_move)(youkuli&, youkuli&) = nullptr) = 0;
	void change_velocity (int direction = ((rand() % 2) ? -1 : 1),bool is_using_random = true)//改变方向
	{
		if (((!is_using_random/*不使用随机数*/) || (is_using_random && !(rand() % 20)/*后面的是随机数，或许应该换种算法，并写成lambda表达式*/)) && !this->ismove && this->place.y >= this->tem_ground/*确保在地上才能有水平初速度，否则会踏空跳跃*/)//提供初速度
		{
			if (this->is_health)
			{
				this->v_x = direction * 10;
				if (this->v_x < 0)//图片水平翻转
				{
					this->is_left = true;
				}
				else if (this->v_x > 0)
				{
					this->is_left = false;
				}
				this->v_y = -10;
				this->ismove = true;
			}
			else if (0)//不健康(分情况讨论)
			{

			}
		}
	};
	int saying()
	{
			static int left_time = 0;
			static LPCTSTR tem_words;
			setfillcolor(WHITE);
			fillrectangle(this->place.x - 20, this->place.y - 80, this->place.x + 120, this->place.y - 20);
			setfillcolor(BLACK);
			if (0 != left_time)//持续
			{
				outtextxy(this->place.x + 10, this->place.y - 60, tem_words);
				left_time--;
				return false;
			}
			else//更换
			{
				tem_words = youkuli_words_library.get(do_nothing);
				left_time = 120;
				return true;
			}
	}
};

class reimu : public youkuli 

{
private:
	all_picture my_picture;//图库（所有图）body只是此时此刻绘制的图
	int which_picture;
public:
	reimu()
	{
		
		this->which_picture = 0;
		//this->body.body = this->my_picture.get_image(this->which_picture);
		this->num = 1;
	}
	
	void draw(void( how_to_move)(youkuli&, youkuli&));

};
void reimu::draw(void( how_to_move)(youkuli&, youkuli&))
{
	if (this->which_picture >= this->my_picture.size())//循环播放
	{
		this->which_picture = 0;
		this->my_picture.change_status(do_nothing);//初始化
	}

	//检测油库里的状态，从而更换图组(my_picture)
	//放在运动相关里面了 

	//运动相关
	
	auto judge_distance_is_in = [](POINT frist, POINT second, LONG distance) ->bool //油库里与鼠标
	{
		return (((frist.x - second.x) * (frist.x - second.x) + (frist.y - second.y) * (frist.x - second.y)) < (distance * distance));
	};
	if (this->stiff_remaining_time && !this->is_pick_up)//是否处于僵直状态且未正在被拿在手里
	{
		this->stiff_remaining_time--;
	}
	else if (this->stiff_remaining_time && !this->is_pick_up)//处于    ？？？好像不用
	{

	}
	else//改变运动状态
	{
		if (!mouse.get_lbutton())//鼠标左键未点击
		{
			if (this->is_pick_up)
			{
				this->is_pick_up = false;
				mouse.is_pick_youkuli = false;//松开了
				this->my_picture.change_status(do_nothing);
				this->which_picture = 0;//重新播放
				//////mouse.inter_status(do_nothing);
			}
			
			//auto &how= how_to_move;
			//how(0, 0);
			if (0)//this->is_pick_up)//保持被拾起状态（可能要改）
			{
				this->place = mouse.get_place();
			}
			else
			{
				this->change_velocity();
				//how_to_move(*this,*this);
			}
		}
		else
		{
			if (pick_up == mouse.get_status() && judge_distance_is_in(this->place, mouse.get_place(), 100) && (!mouse.is_pick_youkuli))//玩家选择“拾起油库里”&&鼠标是否在范围内&&是否有其他油库里被拿起来了
			{
				this->is_pick_up = true;
				mouse.is_pick_youkuli = true;//确保只能拿起一个
				this->place = mouse.get_place();
				this->my_picture.change_status(pick_up);//调整状态
				this->which_picture = 0;//重新播放
			}
			else if (this->is_pick_up && mouse.is_pick_youkuli)//也是确保只能拿起一个
			{
				this->my_picture.change_status(pick_up);
				if (mouse.get_place().y > this->tem_ground)//贴到地面了
				{
					this->my_picture.change_status(touching_ground);//还没有图片
					this->place.y = tem_ground;
					if (mouse.get_place().x < this->place.x)//改变油库里朝向
					{
						this->is_left = true;
					}
					else if (mouse.get_place().x > this->place.x)
					{
						this->is_left = false;
					}
					this->place.x = mouse.get_place().x;//更新位置
				}
				else
				{
					this->place = mouse.get_place();
				}
			}
			else//全部排除
			{
				//how_to_move;
				this->change_velocity();
			}
		}
	}

	//判断？
	if (this->place.y < this->tem_ground - 200)//高于危险高度200
	{
		this->is_too_high = true;
	}
	//if (this->v_y >= 8)//需要改成地平线高度位置
	if (this->place.y > this->tem_ground/*screen_y - 100*/)//落回地面
	{
		this->v_y = 0;
		this->place.y = this->tem_ground;//防穿模
		this->ismove = false;
		this->v_x = 0;
		if (this->is_too_high)//高度足以受到伤害
		{
			this->my_picture.change_status(drop_down);
			this->which_picture = 0;//重新播放
			this->is_too_high = false;
			this->stiff_remaining_time = 31;
		}
	}

	//绘制部分
	if (this->is_left)
	{
		this->cutout(this->body.get_body(), this->place.x, this->place.y);
		putimage(this->place.x, this->place.y, this->body.get_body());
	}
	else
	{
		this->flip_horizontal();
		this->cutout(this->body.get_body(), this->place.x, this->place.y);
		putimage(this->place.x, this->place.y, this->body.get_body());
	}
	//位置更新
	this->place.x += this->v_x;
	this->place.y += this->v_y;
	if (/*this->ismove && */ this->place.y < this->tem_ground/*screen_y - 100*/)//高于地平线
	{
		this->v_y += g;
	}
	++this->which_picture;
	this->body.body = this->my_picture.get_image((mouse_status)this->which_picture);
	if (1)
	{
		if (this->saying())
		{

		}
	}
}
class marisa : public youkuli
{
public:
	marisa()
	{
		this->num = 2;
	}
	void draw(void( how_to_move)(youkuli&, youkuli&));
};
void marisa::draw(void( how_to_move)(youkuli&, youkuli&))
{
	return;
}
class alice : public youkuli
{
public:
	alice()
	{
		this->num = 3;
	}
	void draw(void( how_to_move)(youkuli&, youkuli&));
};
void alice::draw(void( how_to_move)(youkuli&,youkuli&))
{
	return;
}
class place
{
protected:
	vector<class youkuli*> all_youkuli;//个体
	vector<std::map<which_family_member, youkuli&> > family;//家庭
	//全都从零开始
	//颗能生成的油库里种类
	reimu* a = new reimu();
	marisa* b = new marisa();
	alice* c = new alice();
	//
	int max_num_youkuli;//最多生成油库里的数量
	//int num_youkuli_form;//可生成油库里的种类(写死的) (直接写出来)
	void add_youkuli()
	{
		int num_youkuli = rand() % (this->max_num_youkuli + 1);
		for (int i = 0; i != num_youkuli; ++i)
		{
			switch (0)//rand() % 3)
			{
			case 0:
			{
				this->all_youkuli.push_back(this->a);
				this->a = new reimu();
			}
			break;
			case 1:
			{

				this->all_youkuli.push_back(this->b);
				this->b = new marisa();
			}
			break;
			case  2:
			{

				this->all_youkuli.push_back(this->c);
				this->c = new alice();
			}
			break;
			default:

				break;
			}
		}
	}
public:
	place()
	{
		this->max_num_youkuli = 9;
		this->all_youkuli.reserve(sizeof youkuli * this->max_num_youkuli);
		this->add_youkuli();
	}
	place(time_t seed)
	{
		this->max_num_youkuli = 9;
		this->all_youkuli.reserve(sizeof youkuli * this->max_num_youkuli);
		srand((unsigned int)seed);
		this->add_youkuli();
	}
	youkuli* get_youkuli(int which)//下角标
	{
		if (which <= this->all_youkuli.size())
		{
			return (this->all_youkuli[which]);
		}
	}
	void draw()
	{
		//绘制
		//putimage(0,0,this->picture);
		for (auto& one : this->all_youkuli)
		{
			//auto how_to_move = &(one->change_velocity);
			one->draw(&(interaction::wiping_face));//这合理吗？啊？这合理吗
		}
	}
};//place_example;


bool init()//游戏初始化，导入一些必要的东西
{
	youkuli_words_library >> words_type(do_nothing, (LPCTSTR)_T("油库里洗跌一跌捏"));
	youkuli_words_library >> words_type(do_nothing, (LPCTSTR)_T("油~"));
	youkuli_words_library >> words_type(do_nothing, (LPCTSTR)_T("油库气"));
	return true;
}

int main()
{
	place* room = new place(time(0));
	initgraph(screen_x, screen_y);
	BeginBatchDraw();
	int tem = 0;
	IMAGE* bk = new IMAGE;
	loadimage(bk, L"./test.jpg");
	init();
	while (1)
	{
		room->draw();
		/*for (int i = 0; i < 100000 * 5; i++)//延时
		{
			int a = time(0);
			tem = a;
		}*/
		Sleep((DWORD)1000.0 / 60);
		//_getch();
		setbkcolor(BLUE);
		FlushBatchDraw();
		cleardevice();
		//putimage(0, 0, bk);

	}
	return 0;
}


