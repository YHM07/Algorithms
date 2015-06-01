#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
 int m_socket_id=-1;
 
 /*��server�õ�����Ϣ*/ 
 int on_server_message(int length,const char * buffer)
 {
   printf("Receive Data From Server(%s)\n",buffer);
   return 0;
 }
 
 int main(int argc,char * argv[])
 {
 if(argc!=6)
 {
 printf("Usage:./%s server_ip server_port my_ip my_port my_id\n",argv[0]);
 return -1;
 }
 /*��ȡ���������*/
 in_addr_t server_ip=inet_addr(argv[1]);
 in_port_t server_port=htons(atoi(argv[2]));
 in_addr_t my_ip=inet_addr(argv[3]);
in_port_t my_port=htons(atoi(argv[4]));
 int my_id=atoi(argv[5]);
 /*����socket*/
 m_socket_id=socket(AF_INET,SOCK_STREAM,0);
 if(m_socket_id<0)
 {
 printf("init socket failed\n");
 return -1;
 }
 /*����socketѡ���ַ�ظ�ʹ�ã���ֹ����������˳����´�����ʱbindʧ��*/
 int is_reuse_addr=1;
 setsockopt(m_socket_id,SOL_SOCKET,SO_REUSEADDR,(const char*)&is_reuse_addr,sizeof(is_reuse_addr));
 
 /*��ָ��ip��port,��Ȼ�ᱻserver�ܾ�*/ 
 struct sockaddr_in my_addr;
 bzero(&my_addr,sizeof(my_addr));
 my_addr.sin_family=AF_INET;
 my_addr.sin_addr.s_addr=my_ip;
 my_addr.sin_port=my_port;
 if(bind(m_socket_id,(struct sockaddr*)&my_addr,sizeof(my_addr))<0)
 {
 printf("bind failed!\n");
 return -1;
 }
 
 /*����server*/
 struct sockaddr_in server_addr;
 bzero(&server_addr,sizeof(server_addr));
 server_addr.sin_family=AF_INET;
 server_addr.sin_addr.s_addr=server_ip;
 server_addr.sin_port=server_port;
 while(connect(m_socket_id,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
 {
	 perror("connect error");
 usleep(100*1000);/*sleep 100ms,Ȼ�����ԣ���֤����server�����Ǻ��𶼲���������*/
 } 
 printf ( "connect succeed\n" );
 
 /*��serverע��*/
 char reg_msg[50]={'\0'};
  snprintf(reg_msg,sizeof(reg_msg)-1,"reg:%d%s\n",my_id,"\t");
  send(m_socket_id,reg_msg,strlen(reg_msg)+1,0);
  
  /*����server��Ϣ��������Ϸ*/
  while(1)
  {
  char buffer[1024]={'\0'};
  int length=recv(m_socket_id,buffer,sizeof(buffer)-1,0);
  if(length>0)
  {
  /*on_server_message����-1�������յ�game over��Ϣ����������ѭ�����ر�socket,��ȫ�˳�����*/
  if(on_server_message(length,buffer)==-1)
  {
  break;
  } 
  }
  }
  /*�ر�socket*/
  close(m_socket_id);
  return 0; 
 }
