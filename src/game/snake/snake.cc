/**
 * @file snake.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 08/13/2016
 */
/*
snake game for linux
author:	duxiulong	duxlong@live.cn
data:		2015/04/01
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define SNAKE_MAX_LEN		32
typedef struct
{
	int x;
	int y;
} loc_t;	//坐标信息

typedef struct
{
	int dre;	//行动方向
	int len;		//蛇的长度
	loc_t body[SNAKE_MAX_LEN]; //蛇身每一节的坐标
} snake_t; //蛇信息

enum
{
	MAP_NULL = 0,	//空块
	MAP_BLOCK ,		//障碍
	MAP_FOOD			//食物
};

#define MAP_MAX_SIZE		64
typedef struct
{
	int width;
	int height;
	int bmp[MAP_MAX_SIZE][MAP_MAX_SIZE];
} map_t;


//检查蛇身是否处于指定坐标上，是返回１，否返回０
static int check_snake_body_at(loc_t *loc, snake_t *s)
{
	int i;
	int rs = 0;
	
	//遍历蛇身，检查每一节是否与指定坐标匹配
	for (i = 0; i < s->len; i++)
	{
		if (loc->x == s->body[i].x && loc->y == s->body[i].y)
		{
			rs = 1;
			break;
		}
	}
	
	return rs;
}

//蛇身增长一节
static int snake_grow(loc_t *new_head, snake_t *s)
{
	int rs = 1;
	int i;
	
	//把原来蛇身都往后螺
	for (i = s->len; i > 0; i--)
	{
		s->body[i] = s->body[i - 1];
	}
	
	//记录新蛇头
	s->body[0] = *new_head;
	//蛇身长度加1
	s->len++;
	
	return rs;
}

//蛇向前移动一格
static int do_snake_move(loc_t *new_head, snake_t *s)
{
	int rs = 0;
	int i;
	
	for (i = s->len - 1; i > 0; i--)
	{
		//蛇移动时，后边一节跑到前面一节的位置
		s->body[i] = s->body[i - 1];
	}
	
	//记录新蛇头
	s->body[0] = *new_head;
	
	return rs;
}

//蛇按当前方向移动一格位置，返回０表成功，-1表失败, 1表示跎增长一节
static int snake_move(snake_t *s, map_t *m)
{
	int rs = -1;
	//定义上下左右x,y的变化
	int dx[4] = {0, 0, -1, 1};
	int dy[4] = {-1, 1, 0, 0};
	//新的蛇头与蛇尾
	loc_t new_head;	
	int type;
	
	
	//计算新蛇头的位置
	new_head.x = s->body[0].x + dx[s->dre];
	new_head.y = s->body[0].y + dy[s->dre];
	
	//检查移动后蛇头是否超出地图范围
	if (new_head.x < 0 || new_head.x >= m->width ||
		new_head.y < 0 || new_head.y >= m->height)
	{
		//超出范围刚移动失败
		goto EXIT;
	}
	
	//检查蛇头是否咬到蛇身
	if (1 == check_snake_body_at(&new_head, s))
	{
		//咬到蛇身移动失败
		goto EXIT;
	}
	
	type = m->bmp[new_head.y][new_head.x];
	if (MAP_BLOCK == type)
	{
		//如果移动位置是障碍则移动失败
		goto EXIT;
	}
	
	if (MAP_FOOD == type)
	{
		//如果移动位置是食物则蛇增加一点长度
		rs = snake_grow(&new_head, s);
	}
	else
	{
		//移动蛇的位置
		rs = do_snake_move(&new_head, s);
	}
	
EXIT:
	return rs;
}

//生成一个随机数，大于等于０小于max
static int make_rand_num(int max)
{
	int r = rand() % max;
	
	return r < 0 ? (-r) : r;
}

//随机在地图上生成一个障碍
static void make_one_block(map_t *m)
{
	int x;
	int y;
	int dre;
	int step;
	int i;
	int dx[4] = {0, 0, -1, 1};
	int dy[4] = {-1, 1, 0, 0};
	
	//随机生成障碍初始坐标
	x = make_rand_num(m->width);
	y = make_rand_num(m->height);
	//随机生成障碍长度
	step = 3 + make_rand_num(3);
	//随机生成障碍方向
	dre = make_rand_num(4);
	
	//生成障碍
	for (i = 0; i < step; i++)
	{
		//使用模除是为了防止益出
		int xp = (x + m->width * 2) % m->width;
		int yp = (y + m->height * 2) % m->height;
		
		//最上两行预留给蛇初始位置
		if (yp >= 2)
		{
			m->bmp[yp][xp] = MAP_BLOCK;
		}
		
		x += dx[dre];
		y += dy[dre];
	}
}

//生成地图障碍，blocks指定障碍个数
static void make_map_blocks(map_t *m, int blocks)
{
	int i;
	
	//以时间初始化随机数
	srand(time(NULL));
	
	for (i = 0; i < blocks; i++)
	{
		//一个一个生成障碍
		make_one_block(m);
	}
}

//初始化地图
static void init_map(map_t *m, int width, int height, int blocks)
{
	int x;
	int y;
	
	//设置地图大小
	m->width = width;
	m->height = height;
	
	//初始化地图位图
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			m->bmp[y][x] = MAP_NULL;
		}
	}

	//生成地图障碍	
	make_map_blocks(m, blocks);
}

//贪吃蛇初始化
static void int_snake(snake_t *s)
{
	s->dre = 3; //方向右
	
	//蛇长初始化为２节
	s->len = 2;
	s->body[0].x = 1;
	s->body[0].y = 0;
	s->body[1].x = 0;
	s->body[1].y = 0;
}

//生成食物
static int make_food(map_t *m, snake_t *s, loc_t *fc)
{
	int rs = 0;
	int trycnt = 1000000;
	
	while (trycnt-- > 0) //设置生成次数避免死循环
	{
		//随机生成一个地图范围内的位置
		fc->x = make_rand_num(m->width);
		fc->y = make_rand_num(m->height);
		
		//如果随机位置是障碍或者处于蛇身上，重新生成随机位置
		if (MAP_BLOCK == m->bmp[fc->y][fc->x] || check_snake_body_at(fc, s))
		{
			continue;
		}
		
		rs = 1;
		m->bmp[fc->y][fc->x] = MAP_FOOD;	//设置地图状态
		break;
	}
	
	return rs;
}

//显示地图
static void dsp_map(map_t *m)
{
	int x;
	int y;
	
	printf("\033[2J"); //清屏
	
	//显示上下边框
	for (x = 0; x < m->width + 2; x++)
	{
		printf("\033[%d;%dH", 1, x + 1);
		printf("\033[41m+");

		printf("\033[%d;%dH", m->height + 2, x + 1);
		printf("\033[41m+");			
	}
	//显示左右边框
	for (y = 0; y < m->height; y++)
	{
		printf("\033[%d;%dH", y + 2, 1);
		printf("\033[41m+");

		printf("\033[%d;%dH", y + 2, m->width + 2);
		printf("\033[41m+");				
	}
	
	//描绘地图
	for (y = 0; y < m->height; y++)
	{
		for (x = 0; x < m->width; x++)
		{
			//定位光标位置
			printf("\033[%d;%dH", y + 2, x + 2);
			
			if (MAP_BLOCK == m->bmp[y][x])
			{
				//障碍输出黑背景（显示一个空格）
				printf("\033[40m ");
			}
			else
			{
				//空地输出绿背景（显示一个空格）
				printf("\033[42m ");				
			}
		}
	}
}


//显示贪吃蛇
static void dsp_snake(snake_t *s, loc_t *tail)
{
	int i;
	
	for (i = 0; i < s->len; i++)
	{
		int x = s->body[i].x;
		int y= s->body[i].y;
		int ch = i ? '#' : '@'; //蛇头显示@，蛇身显示#
		
		//定位光标
		printf("\033[%d;%dH", y + 2, x + 2);
		//显示蛇身
		printf("\033[46m%c", ch);
	}
	
	if (tail) //移动后原抹掉蛇尾显示
	{
		//定位光标
		printf("\033[%d;%dH", tail->y + 2, tail->x + 2);
		//显示背景
		printf("\033[42m ");
	}
}

//显示食物
static void dsp_food(loc_t *fc, int dsp)
{
		//定位光标位置
		printf("\033[%d;%dH", fc->y + 2, fc->x + 2);
		
		if (dsp)	 //显示食物
		{
			printf("\033[43m*");
		}
		else //清除食物
		{
			printf("\033[42m ");
		}
}

static int get_char();

//执行游戏循环
static int run_game_loop(map_t *m, snake_t *s, loc_t *fc, int *dsp)
{
	int loop = 1;
	int rs = 0;
	int cnt = 0;			//计数
	int stm = 100;		//休眠时间（ms）
	int rcnt = 1000000 / stm / 2;	//0.5秒行动一次
	
	while (loop)
	{
		//获取键盘按键
		int ch = get_char();
		int dre = -1;
		
		if ('q' == ch) //按q退出游戏
		{
			loop = 0;
			rs = 0;
		}
		else if ('a' == ch) //按a向左
		{
			dre = 2;
		}
		else if ('d' == ch) //按a向右
		{
			dre = 3;
		}
		else if ('w' == ch) //向上
		{
			dre = 0;
		}
		else if ('s' == ch) //向下
		{
			dre = 1;
		}
		
		//修改跎的移动方向
		if (dre >= 0)
		{
			s->dre = dre;
		}
		
		//到了行动时间
		if (cnt++ >= rcnt)
		{
			int r;
			loc_t tail = s->body[s->len - 1]; //保存蛇尾位置
			
			//尝试向前移动一步
			r =  snake_move(s, m);
			if (-1 == r) //移动失败
			{
				loop = 0;
				rs = -1;
			}
			else if (1 == r) //吃到食物长一节
			{
				//蛇身长到最长，游戏结束
				if (s->len >= SNAKE_MAX_LEN)
				{
					loop = 0;
					rs = 0;
				}
				else
				{
					//重新生成食物
					make_food(m, s, fc);
					*dsp = 1;
					dsp_food(fc, 1);
					//重绘蛇身
					dsp_snake(s, NULL);
				}
			}
			else //正常移动
			{
				//重绘蛇身
				dsp_snake(s, &tail);
			}
			
			cnt = 0; //重置计数
		}
		
		//食物闪烁显示
		if (0 == cnt % 4)
		{
			*dsp = !*dsp;
			dsp_food(fc, *dsp);
		}
		//休眠一段时间
		usleep(stm);
	}
}

static int run_game(int width, int height, int blocks)
{
	map_t map;			//地图
	snake_t snake;		//贪吃蛇
	loc_t food = {-1, -1};	//食物位置
	int food_dsp = 0;		//食物显示状态
	
	//生成地图
	init_map(&map, width, height, blocks);
	//初始化贪吃蛇
	int_snake(&snake);
	
	//显示地图与蛇
	dsp_map(&map);
	dsp_snake(&snake, NULL);
	
	//生成食物并显示
	make_food(&map, &snake, &food);
	food_dsp = 1;
	dsp_food(&food, food_dsp);
	
	//执行游戏循环
	return run_game_loop(&map, &snake, &food, &food_dsp);
}

#define TTY_PATH				"/dev/tty"
#define STTY_US				"stty raw -echo -F "
#define STTY_DEF				"stty -raw echo -F "

//非阻塞方式获取键盘按键输入
static int get_char()
{
	fd_set rfds;
	struct timeval tv;
	int ch = -1;

	FD_ZERO(&rfds);
	//将标准输入文件名柄(0)加入文件查询集
	FD_SET(0, &rfds);
	tv.tv_sec = 0;
	tv.tv_usec = 10;
   
	//使用select查询
	if (select(1, &rfds, NULL, NULL, &tv) > 0)
	{
		//有键按下则返回
		ch = getchar();	
	}
	
	return ch;
}

int main(int argc, char *argv[])
{
	//设置非阻塞模式
	system(STTY_US TTY_PATH);
	//隐藏光标显示
	printf("\033[?25l");
	
	//运行一次游戏
	run_game(48, 24, 15);
	
	//恢复正常模式
	printf("\033[?25h");
	system(STTY_DEF TTY_PATH);
	
	return 0;
}


