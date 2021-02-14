#include <string.h>
#include <termios.h>
#include <stdio.h> /*标准输入输出定义*/
#include <stdlib.h> /*标准函数库定义*/
#include <unistd.h> /*Unix 标准函数定义*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> /*文件控制定义*/
#include <termios.h> /*PPSIX 终端控制定义*/
#include <errno.h> /*错误号定义*/

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

void main(int argc,char* argv[])
{
	int fd,wr_static;
	char *uart = argv[1];		//ttySAC代表开发板上的串口，对应iTop4412开发板上位uart3,可通过原理图查找序号
	char buf[10];		
	
	//printf("\r\nitop4412 uart writetest start\r\n");
	/* 打开串口，可读写，不将该设备作为此进程的控制终端，非阻塞方式操作 */
	if((fd = open(uart, O_RDWR|O_NOCTTY|O_NDELAY))<0){
		printf("open %s is failed\n",uart);
	}
	else{
		printf("open %s is success\n",uart);
		set_opt(fd, 9600, 8, 'N', 1); //设置串口
		while(1)
		{
			scanf("%s",buf);
			printf("buf = %s\n",buf);
			wr_static = write(fd,buf, strlen(buf));   //发送串口流数据
			if(wr_static<0)
				printf("write failed\n");
			else{
				printf("wr_static is %d\n",wr_static);
			}
			//sleep(1);		
		}
	}
	close(fd);	//释放串口设备资源
}
