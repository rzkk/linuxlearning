#include<iostream>

#include"func.h"



void  errorEqualCheck(int argc , int num,const char *errormsg){
    if(argc == num)
    {
        perror(errormsg);
        assert(0);
    }
   
}
void errorEqualCheck(void * argc1 , void * argc2,const char *errormsg){
    if(argc1 == argc2)
    {
        perror(errormsg);
        assert(0);
       
    }
}

void errorUnequalCheck(void * argc1 , void * argc2,const char *errormsg){
    if(argc1 != argc2)
    {
        perror(errormsg);
        assert(0);
       
    }
}
void  errorUnequalCheck(int argc , int num,const char *errormsg){
    if(argc != num)
    {
        perror(errormsg);
        assert(0);
    }
   
}
void  argsCheck(int argc , int num){
    if(argc != num)
    {
        fprintf(stderr,"args error!\n");
        assert(0);
    }
 
}

















#if 1 



void clientTest(int argc ,char * argv[]){
    argsCheck(argc , 3);

    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;   // 地址结构
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");

    
    // char buf1[1024] ="hello world";
    // send(sockfd , buf1 ,  strlen(buf1) , 0);

    // char buf2[1024] = {0};
    // ret = recv(sockfd , buf2 , sizeof(buf2) , 0);
    // printf(" %d , %s \n", ret, buf2);

    char buf1[1024] ="hello world";
    write(sockfd , buf1 ,  strlen(buf1) );

    char buf2[1024] = {0};
    ret = read(sockfd , buf2 , sizeof(buf2) );
    printf(" %d , %s \n", ret, buf2);
   
}

void aqiangTest(int argc ,char * argv[]){   //客户端
    argsCheck(argc , 3); 

    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;   // 地址结构
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "connect");

    
    fd_set rdset; // 只监听读事件
    char buf[4096] = {0};
    
    while(1){
        FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);       //socket  和stdin 加入监听
        select(sockfd+1 , &rdset , NULL ,NULL ,NULL);
        if(FD_ISSET(sockfd,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret = read(sockfd,buf,sizeof(buf));
            if (ret == 0){
                close(sockfd);
                printf("服务器端断开 , byebye  \n");
                break;
            }
            printf("服务端 : %s \n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //memset(buf,0,sizeof(buf));
            bzero(buf, sizeof(buf)); // 
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if (ret == 0){
                close(sockfd);
                printf("客户端断开,byebye \n");
                break;
            }
            write(sockfd,buf,ret);
        }
    }
   
}

#endif


void udpclientTest(int argc ,char * argv[]){
    argsCheck(argc , 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    //第一次必须 是客户端先给服务端发 ， 因为客户端没有bind , 服务端不知道对面的ip和端口
    sendto(sockfd ,"nihao ", 5, 0 ,(struct sockaddr*)(&serverAddr), sizeof(serverAddr) );

    
    char buf[4096] = {0};
    recvfrom(sockfd , buf , 4096, 0,NULL,NULL );
    printf("buf = %s   \n" , buf  );
    sleep(1);
    bzero(buf,4096);
    recvfrom(sockfd , buf , 4096, 0,NULL,NULL );
    printf("buf = %s   \n" , buf  );


}

void udpclientTest1(int argc ,char * argv[]){
    argsCheck(argc , 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    //第一次必须 是客户端先给服务端发 ， 因为客户端没有bind , 服务端不知道对面的ip和端口
    sendto(sockfd ,"nihao", 5, 0 ,(struct sockaddr*)(&serverAddr), sizeof(serverAddr) );
   // printf("-------------182\n");
    fd_set rdset;
    char buf[4096] = {0};
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO , &rdset);
        FD_SET(sockfd, &rdset);

        select(sockfd+1 , &rdset , NULL ,NULL ,NULL);

        if(FD_ISSET(sockfd , &rdset) ){
            bzero(buf ,4096);
            ssize_t ret = recvfrom(sockfd , buf ,4096 , 0 , NULL, NULL);
            if(ret == 0){
                 break;
            }
            printf("buf = %s" , buf  );
        }
        if(FD_ISSET(STDIN_FILENO , &rdset) ){
            bzero(buf ,4096);
            ssize_t ret =  read(STDIN_FILENO , buf ,4096 );
            if(ret == 0){//ctrl +D
                sendto(sockfd ,buf,0, 0 ,(struct sockaddr*)(&serverAddr), sizeof(serverAddr) );
                break;
            } 
            sendto(sockfd ,buf,strlen(buf), 0 ,(struct sockaddr*)(&serverAddr), sizeof(serverAddr) );
            //printf("buf = %s   ret = %d  \n" , buf  , ret );
        }
    }

}


void epollTest(int argc ,char * argv[]){
    argsCheck(argc , 3); 

    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;   // 地址结构
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = connect(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "connect");

    
    fd_set rdset; // 只监听读事件
    char buf[4096] = {0};
    
    while(1){
        FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);       //socket  和stdin 加入监听
        select(sockfd+1 , &rdset , NULL ,NULL ,NULL);
        if(FD_ISSET(sockfd,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret = read(sockfd,buf,sizeof(buf));
            if (ret == 0){
                close(sockfd);
                printf("对面 服务器端断开 , byebye  \n");
                break;
            }
            printf("服务端 : %s \n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //memset(buf,0,sizeof(buf));
            bzero(buf, sizeof(buf)); // 
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if (ret == 0){
                close(sockfd);
                printf("ctrl d 客户端主动断开,byebye \n");
                break;
            }
            write(sockfd,buf,ret);
        }
    }
   

}

void readBlockTest(int argc ,char * argv[]){
 
    int fd =open("1.pipe" , O_WRONLY);

    write(fd, "howareyou" , 9);
    sleep(40);
    
    printf("sleep over \n");
    
}


int main(int argc ,char * argv[]){
    readBlockTest(argc, argv);
    return 0;
}