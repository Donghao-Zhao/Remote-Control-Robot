#include <sys/types.h>
#include <sys/socket.h>                         // 包含套接字函数库
#include <stdio.h>
#include <netinet/in.h>                         // 包含AF_INET相关结构
#include <arpa/inet.h>                          // 包含AF_INET相关操作的函数
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <stdlib.h> /*标准函数库定义*/
#include <unistd.h> /*Unix 标准函数定义*/
#include <sys/stat.h>
#include <fcntl.h> /*文件控制定义*/
#include <termios.h> /*PPSIX 终端控制定义*/
#include <errno.h> /*错误号定义*/
 
#define  PORT 80
#define  IP_ADDR "39.106.108.242"
 
#define SIZE 10240
 
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)
{
	struct termios newtio,oldtio;
	/* 获取fd串口对应的termios结构体，这步主要是查询串口是否启动正常 */
	if  ( tcgetattr( fd,&oldtio)  !=  0) { 
		perror("SetupSerial 1");
		return -1;
	}
	//清空
	bzero( &newtio, sizeof( newtio ) );
	newtio.c_cflag  |=  CLOCAL | CREAD;	//配置成本地模式(本地连接、不改变端口所有者)、可读
	newtio.c_cflag &= ~CSIZE;		//清空数据位设置
	/* 选择数据位 */
	switch( nBits )
	{
	case 7:
		newtio.c_cflag |= CS7;
		break;
	case 8:
		newtio.c_cflag |= CS8;	
		break;
	}
	/* 选择校验位 */
	switch( nEvent )
	{
	case 'O':
		newtio.c_cflag |= PARENB;
		newtio.c_cflag |= PARODD;
		newtio.c_iflag |= (INPCK | ISTRIP);	//启用输入奇偶检测、去掉第八位
		break;
	case 'E': 
		newtio.c_iflag |= (INPCK | ISTRIP);
		newtio.c_cflag |= PARENB;
		newtio.c_cflag &= ~PARODD;
		break;
	case 'N':  
		newtio.c_cflag &= ~PARENB;
		break;
	}
	/* 选择波特率 */
	switch( nSpeed )
	{
	case 2400:
		cfsetispeed(&newtio, B2400);
		cfsetospeed(&newtio, B2400);
		break;
	case 4800:
		cfsetispeed(&newtio, B4800);
		cfsetospeed(&newtio, B4800);
		break;
	case 9600:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	case 115200:
		cfsetispeed(&newtio, B115200);
		cfsetospeed(&newtio, B115200);
		break;
	case 460800:
		cfsetispeed(&newtio, B460800);
		cfsetospeed(&newtio, B460800);
		break;
	default:
		cfsetispeed(&newtio, B9600);
		cfsetospeed(&newtio, B9600);
		break;
	}
	/* 选择停止位，貌似linux下不能设置(1.5 0.5)停止位 */
	if( nStop == 1 )
		newtio.c_cflag &=  ~CSTOPB;
	else if ( nStop == 2 )
		newtio.c_cflag |=  CSTOPB;
	newtio.c_cc[VTIME]  = 0;
	newtio.c_cc[VMIN] = 0;
	tcflush(fd,TCIFLUSH);
	/* 设置新配置 */
	if((tcsetattr(fd,TCSANOW,&newtio))!=0)
	{
		perror("com set error");
		return -1;
	}
//	printf("set done!\n\r");
	return 0;
}
 
int main(int argc,char* argv[])
{  
     int fd,wr_static;
	char *uart = argv[1];		//ttySAC代表开发板上的串口，对应iTop4412开发板上位uart3,可通过原理图查找序号
	char buff[10];		
	
	//printf("\r\nitop4412 uart writetest start\r\n");
	/* 打开串口，可读写，不将该设备作为此进程的控制终端，非阻塞方式操作 */
	if((fd = open(uart, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s is failed\n",uart);
	}
	else{
		printf("open %s is success\n",uart);
		set_opt(fd, 9600, 8, 'N', 1); //设置串口
	}
		
		
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
				if(strcmp((shmaddr+i*100),"w\n"))
				{
					printf("bingo\n");
					wr_static = write(fd,(shmaddr+i*100), strlen(shmaddr+i*100));   //发送串口流数据
				}
                i++;
            	//printf("\n");
            }
           
            usleep(1000);
        }
   
       
    }
    close(sockfd);
    return 0;
 
 
}
