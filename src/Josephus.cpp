/*
 * =====================================================================================
 *
 *       Filename:  Josephus.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/19/2015 04:46:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  H.M.Yang,yangheming55@126.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include<iostream>
#include<malloc.h>
using namespace std; 
struct node 
{
	   int no; //代表编号结点的数据
	      int code;//代表密码结点的数据
		     node *next;//代表后一个结点的地址
};
int main() 
{ 
   int m,n,i,j;
   node *p,*q,*first;
   cout<<"请输入m的初始值 m:";
   cin>>m;
   cout<<"请输入人数 n:";
   cin>>n;
for(i=1;i<=n;i++)
{
if(i==1)
{
	first=p=(node*)malloc(sizeof(node));
if(p==0)
return 0;
}
else
{
q=(node*)malloc(sizeof(node));
if(q==0)
return 0;
p->next=q;
p=q;
   }
cout<<"请输入第 "<<i<<" 个人的密码: ";
cin>>(p->code);
p->no=i;
}
p->next=first; //让表尾指向表头形成循环链表
p=first;
cout<<"出列顺序为: ";
for (j=1;j<=n;j++)
{
for(i=1;i<m;i++,p=p->next);
m=p->code;
cout<<p->no<<" ";
p->no=p->next->no;
p->code=p->next->code;
q=p->next;
p->next=p->next->next;
free(q);
}
cout<<endl;
return 0;
}
