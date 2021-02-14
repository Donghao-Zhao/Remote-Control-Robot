#include <sys/types.h>
#include <sys/socket.h>                         // 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>                         // 包含AF_INET相关结构
#include <arpa/inet.h>                      // 包含AF_INET相关操作的函数
#include <unistd.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/shm.h>
 
#define PORT    80
#define MYKEY   12345
#define SIZE    10240
 
int main()
{  
    int shmid;
    char *shmaddr;                       //定义子进程共用的共享内存 
    shmid = shmget(MYKEY, SIZE, IPC_CREAT | 0600);  
    shmaddr= (char *) shmat(shmid, 0, 0);
   
    if(shmid==-1)
    {
        printf("shmid error\n");
    }
    memset(shmaddr,0,SIZE);
   
    int i=0;
    char buf[100];
    memset(buf,0,100);
   
   
    int server_sockfd,client_sockfd;   
    int server_len,client_len;
   
    struct sockaddr_in server_sockaddr,client_sockaddr;
   
   
    server_sockfd = socket(AF_INET,SOCK_STREAM, 0); // 定义套接字类型
   
    server_sockaddr.sin_family=AF_INET;
    server_sockaddr.sin_port=htons(PORT);
    server_sockaddr.sin_addr.s_addr=INADDR_ANY;
   
    server_len=sizeof(server_sockaddr);
   
    //允许重复使用本地地址和套接字绑定
    int j=1;
    setsockopt(server_sockfd,SOL_SOCKET,SO_REUSEADDR,&j,sizeof(j));
   
    //绑定端口
    if(bind(server_sockfd,(struct sockaddr *)&server_sockaddr,server_len)==-1)
    {
        perror("bind:");
        exit(1);       
    }
   
   
    if(listen(server_sockfd,5)==-1)
    {
        perror("listen:");
        exit(1);   
    }
    printf("Listening...\n");
   
    client_len=sizeof(client_sockaddr);
   
    pid_t ppid,pid;
  
   while(1)
   {  
    if((client_sockfd=accept(server_sockfd,(struct sockaddr *)&client_sockaddr,&client_len))==-1)
        {
             perror("accept error:");
             exit(1);
        }
   
    printf("%s登录服务器\n",inet_ntoa(client_sockaddr.sin_addr));
   
    ppid=fork();
   
    if(ppid==-1)
    {
        printf("fork 1 failed:");
    }
   
    if(ppid==0)                  //子进程用于接收客户端信息并发送
    {
        pid=fork();
        if(pid==-1)
        {
            printf("fork 2 failed:");
            exit(1);
        }
    
     int recvbytes;  
         
        if(pid==0)              //子子进程用于接收消息
        {  
            while(1)
            {
               
               if((recvbytes=recv(client_sockfd,buf,100,0))==-1)
               {
                    perror("read client_sockfd failed:");
                  
               }
               // printf("recvbytes=%d\n",recvbytes);
                usleep(10000);
               printf("client send buf=%s\n",buf);
               
                for(i=0;i<1000;i++)
                {
                    if(*(shmaddr+100*i)==0)
                    {
                        strcpy(shmaddr+100*i,buf);  
                        break;
                    
                    }
                }
               
               
            }
        }
       
        if(pid>0)               //子进程用于发送消息 
        {
           while(1)
            {
                if(*(shmaddr+i*100)!=0)
               {
                   // strcpy(&buf,shmaddr+100*i);
                
                  //  buf++;
                    write(client_sockfd,shmaddr,SIZE);
                   // send(client_sockfd,buf,strlen(buf),0);
                  
                 //   printf("the server is send buf=%c",buf);
                  //  printf("send client :%s\n",(shmaddr+i*100)) ;
                    i++;
                   
                }
            }
       
        }    
      
    }
   
   
    if(ppid>0)              //总父进程返回等待接收消息
    {
        close(client_sockfd);
    }
       
    
    }
 
}
