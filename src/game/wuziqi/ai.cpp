/**
 * @file ai.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 08/13/2016
 */
/*五子棋游戏的游戏模块的实现 
  zwdnet 
  2010年3月 
  zwdnet@163.com 
*/  
#include <iostream>
#include <vector>  
#include <string.h>
  
using namespace std;  
int X,Y;  
int colour;  
int N=15; //棋盘大小  
typedef struct node  
{  
    int x;  
    int y;  
}POINT;  
vector<vector<int> > board;  
//五子棋游戏类，进行游戏相关的操作  
  
class Game  
{  
private:  
    int Total; //落子总数，用于判断是否已经下满，下满则为和棋  
  
public: //供外界调用的接口  
    Game(); //构造函数，默认大小为15  
    ~Game(void);  
    void Init(void); //数据初始化  
   
    void Clear(void); //清空游戏数据  
    void Run(POINT & ps); //计算机走棋  
  
private://核心算法模块  
      
    //算法2  
    void Way(POINT & ps);  
    void SetScore(const int i, const int j, const int Who,  
                  vector<vector<int> > & State); //评分函数  
    int p_Score(int num, int bp[]); //实际的评分函数  
    bool first; //是否是第一步  
};  
  
Game::Game()  
{  
    Init();  
}  
  
Game::~Game(void)  
{  
}  
  
void Game::Init(void)  
{  
    vector<int> temp(N);  
    int i;  
    for (i = 0; i < N; i++)  
    {  
        board.push_back(temp);  
    }  
    first = true; //是否是第一步，算法二要用  
}  
  
void Game::Run(POINT & ps)  
{  
    Way(ps);  
}  
  
  
//算法2：只考虑当前情况，不递归的（贪心法)  
//参考Zhong_Zw的程序，下载自CSDN  
void Game::Way(POINT & ps)  
{  
    int i,j;  
    vector<vector<int> > HumanState, ComputerState;  
    vector<int> temp(N, 0);  
    int maxP = 0, maxC = 0; //计算机和人状态值的最大值  
    POINT ps1, ps2;  
    //如果是开局先走，下中央  
    if (Total == 0)  
    {  
        ps.x = N/2;  
        ps.y = N/2;  
    }  
    //初始化计算机和人的状态矩阵  
      
    for (i = 0; i < N; i++)  
    {  
        HumanState.push_back(temp);  
        ComputerState.push_back(temp);  
    }  
      
  
    for ( i = 0; i < N; i++)  
    {  
        for (j = 0; j < N; j++)  
        {  
            if (board[i][j] == -1)  
            {  
                SetScore(i, j, colour, HumanState);  
                SetScore(i, j, 3-colour, ComputerState);  
            }  
        }  
    }  
  
      
    for (i = 0; i < N; i++)  
    {  
        for (j = 0; j < N; j++)  
        {  
            if (HumanState[i][j] > maxP)  
            {  
                maxP = HumanState[i][j];  
                ps1.x = i;  
                ps1.y = j;  
            }  
            if (ComputerState[i][j] > maxC)  
            {  
                maxC = ComputerState[i][j];  
                ps2.x = i;  
                ps2.y = j;  
            }  
        }  
    }  
    if (maxP >= maxC)  
    {  
        ps.x = ps1.x;  
        ps.y = ps1.y;  
    }  
    else  
    {  
        ps.x = ps2.x;  
        ps.y = ps2.y;  
    }  
    X=ps.x;  
    Y=ps.y;  
}  
  
//评分函数  
void Game::SetScore(const int i, const int j, const int Who,  
                    vector<vector<int> > & State)  
{  
    int Another; //与要求的状态相对的另一方  
    int bp[2], k, num, max = 0, temp = 0;  
    if (Who == 1)  
    {  
        Another = 2;  
    }  
    else if (Who == 2)  
    {  
        Another = 1;  
    }  
    else  
    {  
        return;  
    }  
      
  
    //横向  
    //向右  
    bp[0] = 1; bp[1] = 1;  
    num = 0;  
    for (k = 1; k < N - i; k++)  
    {  
        if (board[i+k][j] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i+k][j] == -1)  
        {  
            bp[1] = 0;  
            break;  
        }  
        if (board[i+k][j] == Another)  
        {  
            bp[1] = 1;  
            break;  
        }  
    }  
    //向左  
    for (k = 1; k <= i; k++)  
    {  
        if (board[i-k][j] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i-k][j] == -1)  
        {  
            bp[0] = 0;  
            break;  
        }  
        if (board[i-k][j] == Another)  
        {  
            bp[0] = 1;  
            break;  
        }  
    }  
    //调用评分函数  
    temp = p_Score(num, bp);  
    max += temp;  
  
    //纵向  
    bp[0] = 1; bp[1] = 1;  
    num = 0;  
    //向下  
    for (k = 1; k < N - j; k++)  
    {  
        if (board[i][j+k] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i][j+k] == -1)  
        {  
            bp[1] = 0;  
            break;  
        }  
        if (board[i][j+k] == Another)  
        {  
            bp[1] = 1;  
            break;  
        }  
    }  
    //向上  
    for (k = 1; k <= j; k++)  
    {  
        if (board[i][j-k] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i][j-k] == -1)  
        {  
            bp[0] = 0;  
            break;  
        }  
        if (board[i][j-k] == Another)  
        {  
            bp[0] = 1;  
            break;  
        }  
    }  
    temp = p_Score(num, bp);  
    max += temp;  
  
    //从左上到右下  
    bp[0] = 1; bp[1] = 1;  
    num = 0;  
  
    //下  
    for (k = 1; k < N-i && k < N-j; k++)  
    {  
        if (board[i+k][j+k] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i+k][j+k] == -1)  
        {  
            bp[1] = 0;  
            break;  
        }  
        if (board[i+k][j+k] == Another)  
        {  
            bp[1] = 1;  
            break;  
        }  
    }  
    //上  
    for (k = 1; k <= j && k <= i; k++)  
    {  
        if (board[i-k][j-k] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i-k][j-k] == -1)  
        {  
            bp[0] = 0;  
            break;  
        }  
        if (board[i-k][j-k] == Another)  
        {  
            bp[0] = 1;  
            break;  
        }  
    }  
    temp = p_Score(num, bp);  
    max += temp;  
  
    //从右上到左下  
    bp[0] = 1; bp[1] = 1;  
    num = 0;  
    //下  
    for (k = 1; k < N-j && k <= i; k++)  
    {  
        if (board[i-k][j+k] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i-k][j+k] == -1)  
        {  
            bp[1] = 0;  
            break;  
        }  
        if (board[i-k][j+k] == Another)  
        {  
            bp[1] = 1;  
            break;  
        }  
    }  
    //上  
    for (k = 1; k <= j && k < N-i; k++)  
    {  
        if (board[i+k][j-k] == Who)  
        {  
            num++;  
            continue;  
        }  
        if (board[i+k][j-k] == -1)  
        {  
            bp[0] = 0;  
            break;  
        }  
        if (board[i+k][j-k] == Another)  
        {  
            bp[0] = 1;  
            break;  
        }  
    }  
    temp = p_Score(num, bp);  
    max += temp;  
  
    if (max > State[i][j])  
    {  
        State[i][j] = max;  
    }  
}  
  
//实际的评分函数  
int Game::p_Score(int num, int bp[])  
{  
    int max = 0;  
    if (num >= 4)  
    {  
        max += 10000; //成五  
    }  
    else if (num == 3)  
    {  
        if (bp[1] == 1 && bp[0] == 1) //不成五  
        {  
            max += 0;  
        }  
        else if (bp[1] == 0 && bp[0] == 0) //活四  
        {  
            max += 3000;  
        }  
        else  
        {  
            max += 900; //冲四  
        }  
    }  
    else if (num == 2)  
    {  
        if (bp[0] == 0 && bp[1] == 0)  
        {  
            max += 460; //活三  
        }  
        else if (bp[0] == 1 && bp[1] == 1)  
        {  
            max += 0; //不成五  
        }  
        else  
        {  
            max += 30; //死三  
        }  
    }  
    else if (num == 1)  
    {  
        if (bp[0] == 0 && bp[1] == 0)  
        {  
            max += 45;  //活二  
        }  
        else if (bp[0] == 1 && bp[1] == 1)  
        {  
            max += 0;  
        }  
        else  
        {  
            max += 5;  
        }  
    }  
    else if (num == 0)  
    {  
        if (bp[0] == 0 && bp[1] == 0)  
        {  
            max += 3;  
        }  
        else if (bp[0] == 1 && bp[1] == 1)  
        {  
            max += 0;  
        }  
        else  
        {  
            max += 1;  
        }  
    }  
    return max;  
}  
  
  
  
  
int main()   
{   
    char command[10]; //用于保存命令的字符串   
    Game wahaha;  
    wahaha.Init();  
    for (int i = 0; i < N; i++)   
        for (int j = 0; j < N; j++)   
            board[i][j] = -1; //棋盘初始化   
    cin >> command;   
            
    if(strcmp(command, "[START]") != 0)//读入第一条命令  
    {  
        return 0; //如果不是[START]则停止程序   
    }  
    cin >> colour; //读入己方颜色   
      
    POINT ps; //棋盘上每个格子的状态,-1为啥也没有，1为黑棋，2为白棋  
    while (true)   
    {   
        int rival_x, rival_y; //用于保存对手上一步落子点   
        cin >> command; //读入命令   
        if (strcmp(command, "[PUT]") != 0)  
            break; //如果不是[PUT]则停止程序   
        cin >> rival_x >> rival_y; //读入对手上一步落子点   
        if(colour == 1 && rival_x == -1 && rival_y == -1) //如果己方执黑且是第一步，则占据棋盘中心位置   
        {   
            board[N / 2][N / 2] = colour; //更新棋盘信息  
            cout << N / 2 << ' ' << N / 2 << endl; //输出  
            cout << flush; //刷新缓冲区   
        }  
        else   
        {  
            board[rival_x][rival_y] = 3 - colour;   
            //更新棋盘信息   
            do  
            {   
                wahaha.Run(ps);  
                if (board[X][Y] == -1) //如果该位置为空则占据该位置   
                {  
                    board[X][Y] = colour; //更新棋盘信息   
                    cout << X << ' ' << Y << endl; //输出   
                    cout << flush; //刷新缓冲区  
                    break; //结束循环   
                }  
            }  
            while (true);   
            //循环直至随机得到一个空位置   
        }  
        wahaha.~Game();  
    }  
    return 0;   
} 
