static int set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop)   
{   
    struct termios newtio;   
    struct termios oldtio;   
       
    if(tcgetattr(fd,&oldtio) != 0)   
    {   
        perror("SetupSerial 1");   
        return -1;   
    }   
       
    bzero(&newtio,sizeof(newtio));   
    newtio.c_cflag |= CLOCAL |CREAD;   
    newtio.c_cflag &= ~CSIZE;   
	
/***********数据位选择****************/    
    switch(nBits)   
    {   
        case 7:   
        newtio.c_cflag |= CS7;   
        break;   
        case 8:   
        newtio.c_cflag |= CS8;   
        break;       
    }   
/***********校验位选择****************/  
    switch(nEvent)   
    {   
        case 'O':   
        newtio.c_cflag |= PARENB;   
        newtio.c_cflag |= PARODD;   
        newtio.c_iflag |= (INPCK | ISTRIP);   
        	break;   
        case 'E':   
        newtio.c_iflag |= (INPCK |ISTRIP);   
        newtio.c_cflag |= PARENB;   
        newtio.c_cflag &= ~PARODD;   
        	break;   
    	 case 'N':   
        newtio.c_cflag &= ~PARENB;   
        	break;   
    }   
/***********波特率选择****************/   
    switch(nSpeed)   
    {   
        case 2400:   
        cfsetispeed(&newtio,B2400);   
        cfsetospeed(&newtio,B2400);   
        	break;   
    	 case 4800:   
        cfsetispeed(&newtio,B4800);   
        cfsetospeed(&newtio,B4800);   
        	break;   
    	 case 9600:   
        cfsetispeed(&newtio,B9600);   
        cfsetospeed(&newtio,B9600);   
        	break; 
    	 case 57600:   
        cfsetispeed(&newtio,B57600);   
        cfsetospeed(&newtio,B57600);   
        	break;   
    	 case 115200:   
        cfsetispeed(&newtio,B115200);   
        cfsetospeed(&newtio,B115200);   
        	break;   
     	 case 460800:   
        cfsetispeed(&newtio,B460800);   
        cfsetospeed(&newtio,B460800);   
        	break;             
    	 default:   
        cfsetispeed(&newtio,B9600);   
        cfsetospeed(&newtio,B9600);   
            	break;   
    }   
/***********停止位选择****************/  
    if(nStop == 1){   
        newtio.c_cflag &= ~CSTOPB;   
    }   
    else if(nStop ==2){   
        newtio.c_cflag |= CSTOPB;   
    }   
    newtio.c_cc[VTIME] = 1;   
    newtio.c_cc[VMIN] = FRAME_MAXSIZE;   //阻塞条件下有效
  
    tcflush(fd,TCIFLUSH);   
    if((tcsetattr(fd,TCSANOW,&newtio)) != 0)   
    {   
        perror("com set error");   
        return -1;   
    }   
    printf("set done!\n");   
    return 0;   
}   
