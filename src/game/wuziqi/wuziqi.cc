/**
 * @file wuziqi.cc
 * @brief 
 * @author H.M.Yang,hmyang07@gmail.com
 * @version v1.0
 * @date 08/13/2016
 */

/************************************************************************* 
    > File Name: wuziqi.c 
    > Author: Baniel Gao 
    > Mail: createchance@163.com  
    > Blog: blog.csdn.net/createchance  
    > Created Time: Fri 06 Dec 2013 10:32:41 AM CST 
 ************************************************************************/  
#include <stdio.h>  
#include <stdlib.h>  
  
#define N 20  
  
void create_board(char (*board)[N]);  
void print_board(char (*board)[N]);  
void print_info(int flag,int person);  
int play_chess(char (*board)[N],int *person,int *x,int *y);  
int check_board(char (*board)[N],int *person,int x,int y);  
  
int main(void)  
{  
    char board[N][N];  
    int person = 0,flag = 0,x = 0,y = 0;  
  
   create_board(board);  
    while(1)  
    {  
        print_board(board);  
        print_info(flag,person);  
        if(flag == 1)  
        {  
            break;  
        }  
        if((flag=play_chess(board,&person,&x,&y)) == -1 || flag == 3)  
        {  
            continue;  
        }  
        else if(flag == 2)  
        {  
            return 0;  
        }  
        flag = check_board(board,&person,x,y);  
    }  
  
    return 0;  
}  
  
void create_board(char (*board)[N])  
{  
    int i,j;  
  
    for(i=0;i<N;i++)  
    {  
        for(j=0;j<N;j++)  
        {  
            board[i][j] = '-';  
        }  
    }  
  
    return;  
}  
  
void print_board(char (*board)[N])  
{  
    int i,j;  
  
    system("clear");  
    printf("\n------------------Welcome to play my chess! Version 1.0-----------------------\n");  
    printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n");  
    printf("#     ");  
    for(i=0;i<N;i++)  
    {  
        printf("%02d  ",i);  
    }  
    printf("#\n");  
    for(i=0;i<N;i++)  
    {  
        printf("#  %02d ",i);  
        for(j=0;j<N;j++)  
        {  
            printf("%-2c  ",board[i][j]);  
        }  
        printf("#\t|\n");  
    }  
    printf("# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #\n");  
  
    return;  
}  
  
void print_info(int flag,int person)  
{  
    if(flag == 1)  
    {  
        if(person == 0)  
        {  
//			system("echo -e '\033[32mWhite Win\033[0m'");
//			printf ( "\n" );
            printf("\033[32mWhite Win\033[0m!!\n");  
        }  
        else  
        {  
//			system("echo -e '\033[32mWhite Win\033[0m'");
//			printf ( "\n" );
            printf("\033[32mBLACK WIN\033[0m!!\n");  
        }  
    }  
    else  
    {  
        if(flag == -1)  
        {  
            printf("Error!Please input again!\n");  
        }  
        if(person == 0)  
        {  
            printf("WHITE play!(Press q to quit)\n");  
        }  
        else  
        {  
            printf("BLACK play!(Press q to quit)\n");  
        }  
    }  
  
    return;  
}  
  
int play_chess(char (*board)[N],int *person,int *x,int *y)  
{  
    char choice;  
  
    printf("Input position(x,y): ");  
    while((scanf("%d,%d",x,y) != 2) || *x < 0 || *x > N-1 || *y < 0 || *y > N-1)  
    {  
        choice = getchar();  
        if(choice == 'q' && getchar() == '\n')  
        {  
            return 2;  
        }  
        else if(choice == 'r' && getchar() == '\n')  
        {  
            if(board[*x][*y] == '-')  
            {  
                printf("You have already rescinded!\n");  
                return -1;  
            }  
            board[*x][*y] = '-';  
            *person = (*person + 1)%2;  
            return 3;  
        }  
        return -1;  
    }  
    if(board[*x][*y] != '-')  
    {  
        return -1;  
    }  
    if(*person == 0)  
    {  
        board[*x][*y] = 'X';  
    }  
    else  
    {  
        board[*x][*y] = 'O';  
    }  
  
    return 0;  
}  
  
int check_board(char (*board)[N],int *person,int x,int y)  
{  
    int i,j;  
    int pos_x = x,pos_y = y;  
    int cnt,sign;  
    int a[8][2] = {{0,1},{0,-1},{-1,0},{1,0},{-1,1},{-1,-1},{1,-1},{1,1}};  
  
    for(i=0;i<8;i++)  
    {  
        cnt = sign = 1;  
        j = 0;  
        while(1)  
        {  
            pos_x += sign*a[i][j];  
            pos_y += sign*a[i][j+1];  
            if((board[pos_x][pos_y] == board[x][y]) && pos_x >= 0 && pos_x <= N-1 && pos_y >= 0 && pos_y <= N-1)  
                cnt++;  
            else  
            {  
                if(sign == -1)  
                {  
                    break;  
                }  
                sign = -1;  
                pos_x = x;  
                pos_y = y;  
            }  
            if(cnt == 5)  
            {  
                return 1;  
            }  
        }     
    }  
    *person = (*person + 1)%2;  
  
    return 0;  
} 
