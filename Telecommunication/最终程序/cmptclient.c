#include <sys/types.h>
#include <sys/socket.h>                         // 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>                         // 包含AF_INET相关结构
#include <arpa/inet.h>                          // 包含AF_INET相关操作的函数
#include <unistd.h>
#include <string.h>
#include <time.h>
 
#define  PORT 80
#define  IP_ADDR "39.106.108.242"
 
#define SIZE 10240
 
int main()
{  
     
    struct tm *timeptr;
    time_t timeval;
    char tm[50];
    //(void)time(&timeval);
   
    //printf("the date is %s\n",ctime(&timeval));
   // printf("The time is %s\n",tm);
   
    int sockfd;                                 // 用于保存客户套接字标识符
    int len;                                    // 用于客户消息长度
    struct sockaddr_in address;                 // 定义客户套接字地址
 
    int result;
   
 
    sockfd = socket(AF_INET,SOCK_STREAM, 0);    // 定义套接字类型
    address.sin_family = AF_INET;               // 定义套接字地址中的域
   
    address.sin_addr.s_addr = inet_addr(IP_ADDR);                           // 定义套接字地址
   
    address.sin_port = htons(PORT);                 // 定义套接字端口
    char buf[100];                              // 定义要传送的消息
    memset(buf,0,100);
    char str[120];                     //存贮输入的语句
   
    char shmaddr[SIZE];                    //接受服务器发送的全部聊天数据 
    int i=0;
   
    //char myname[100];
    //char say[10]={"[-_-]"};
    //char blank[10] = {"     "};
    //printf("欢迎来到聊天室，请输入你的姓名:\n");
    //scanf("%s",myname);
   
   
  
   len = sizeof(address);
   result = connect(sockfd, (struct sockaddr *) &address, len); // 请求连接
 
   if (result == -1)  
    {
      perror("Connect failed");
      return 1;
    }
    printf("成功connect服务器:\n");
   
 
    pid_t pid;
   
    pid=fork();
    if(pid==-1)
    {
        printf("fork failed");
    }
   
    int sendbytes=0;
 
    if(pid==0)              //子进程用于发送数据
    {
       while(1)
        {            
                scanf("%s",str);
                (void)time(&timeval);
                strcpy(tm,ctime(&timeval));
 
                //strcpy(buf,myname);             //姓名传入buf中
                //strcat(buf,blank);
		//strcat(buf,tm);                 //时间传入buf中
                //strcat(buf,say);               
                strcat(buf,str);                //语句传入bufz中
               
                 if((sendbytes=write(sockfd, buf, 100))==-1)
                 {
                    perror("send to server failed:");
                 }  // 向服务器传送消息
 
                 usleep(1000);
                
                memset(buf,0,100);
                memset(tm,0,50);
        }      
    }
   
    if(pid>0)               //父进程用于接受消息并读取
    {
        while(1)
        {
            read(sockfd,shmaddr,SIZE);
          // printf("server send shmaddr=%s\n",shmaddr);
           
            if(*(shmaddr+i*100)!=0)
            {
                printf("%s\n",(shmaddr+i*100)) ;
                i++;
            	printf("\n");
            }
           
            usleep(1000);
        }
   
       
    }
    close(sockfd);
    return 0;
 
 
}
