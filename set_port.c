static int open_port(int fd,int comport)   
{     
/***********打开串口1****************/
    if(comport == 1)   
    {   
        fd = open("/dev/ttyAT1",O_RDWR|O_NOCTTY|O_NDELAY);   
    if(fd == -1){   
        perror("Can't Open Serial Port");   
        return -1;   
        }   
    }   
 /***********打开串口2****************/ 
    else if(comport == 2)   
    {   
        fd = open("/dev/ttyAT2",O_RDWR|O_NOCTTY|O_NDELAY);   
        if(fd == -1){   
            perror("Can't Open Serial Port");   
            return -1;   
        }   
    }   
/***********打开串口3****************/  
    else if(comport == 3)   
    {   
        fd = open("/dev/ttyAT3",O_RDWR|O_NOCTTY|O_NDELAY);   
        if(fd == -1){   
            perror("Can't Open Serial Port");   
            return -1;   
        }   
    }   
	if(comport == 1)
	{
		if(fcntl(fd,F_SETFL,FNDELAY) < 0)//非阻塞，覆盖前面open的属性
		{   
			printf("fcntl failed\n");   
		}   
		else{   
		printf("fcntl=%d\n",fcntl(fd,F_SETFL,FNDELAY));   
		} 
	}
	else
	{
		if(fcntl(fd,F_SETFL,0) < 0){   //阻塞，即使前面在open串口设备时设置的是非阻塞的，这里设为阻塞后，以此为准
		printf("fcntl failed\n");   
		}   
		else{   
		printf("fcntl=%d\n",fcntl(fd,F_SETFL,0));   
		} 
	}   
    if(isatty(STDIN_FILENO) == 0){ 
	  
    printf("standard input is not a terminal device\n");   
    }   
    else{   
		
        printf("isatty sucess!\n");   
    }  

    printf("fd-open=%d\n",fd);   
    return fd;   
}

