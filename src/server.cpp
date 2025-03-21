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











#if 0 
void htonsTest(){
    short port = 0x1234; //小端
    short big_endian_port = htons(port); //小端 => 大端
    printf("%x \n", big_endian_port); 
}

void iptoaddrTest(){
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    char ip[] = "192.168.72.128";
    //inet_aton(ip,&addr.sin_addr);
    addr.sin_addr.s_addr = inet_addr(ip);
    printf("ip = %x  \n" , addr.sin_addr.s_addr);//ip = 8048a8c0 
}

int gethostbynameTest(){
    char buf[] = "www.cskaoyan.com";
    struct hostent * entry = gethostbyname(buf);
    if(entry == NULL){
        herror("gethostbyname");
        return -1;
    }

    printf("official name =   %s \n " , entry->h_name);

    for(int i =0;entry->h_addr_list[i] != NULL;++i){
        printf("\t alias = %s \n ", entry->h_addr_list[i]);
    } 

    for(int i =0;entry->h_addr_list[i] != NULL;++i){
        char ip[1024] = {0};
        inet_ntop( entry->h_addrtype , entry->h_addr_list[i] , ip , 1024 );
        printf(" ip = %s \n ", ip);
    } 

    return 0;
}
#endif

#if 0 // 单对单
void serverTest(int argc ,char * argv[]){
    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");

    listen(sockfd , 50);

    struct sockaddr_in clientAddr;

    //socklen 必须赋初值
    socklen_t socklen = sizeof(clientAddr);

    //新的描述符 , 通信文件描述符
    int netFd = accept(sockfd ,(struct sockaddr*)&clientAddr , &socklen );

    char ip[64] = {0};
    inet_ntop( AF_INET , &clientAddr.sin_addr , ip , 1024 );

    //printf("client ip = %s , port = %d \n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
    printf("client ip = %s , port = %d \n", ip, ntohs(clientAddr.sin_port));

    // char buf1[1024] = {0};
    // ret = recv(netFd , buf1 , sizeof(buf1) , 0);
    // printf(" %d , %s \n", ret, buf1);

    // char buf2[1024] ="how are you ";
    // send(netFd , buf2 ,  strlen(buf2) , 0);
    send(netFd , "hello" ,  5 , 0);
    send(netFd , "world" ,  5 , 0);
    char buf1[1024] = {0};
    ret = read(netFd , buf1 , sizeof(buf1) );
    printf(" %d , %s \n", ret, buf1);

    char buf2[1024] ="how are you ";
    write(netFd , buf2 ,  strlen(buf2) );
}


void azhenTest(int argc ,char * argv[]){  // 服务端
    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR,&reuse , sizeof(reuse));
    errorEqualCheck(ret, -1 , "setsockopt");
    ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");
    listen(sockfd , 50);
    struct sockaddr_in clientAddr;
    //socklen 必须赋初值
    socklen_t socklen = sizeof(clientAddr);
    //新的描述符 , 通信文件描述符
    int netFd = accept(sockfd ,NULL , NULL );

    fd_set rdset; // 只监听读事件
    char buf[4096] = {0};
    
    while(1){
        FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(netFd, &rdset);       //socket  和stdin 加入监听
        select(netFd+1 , &rdset , NULL ,NULL ,NULL);
        if(FD_ISSET(netFd,&rdset)){
            memset(buf,0,sizeof(buf));
            read(netFd,buf,sizeof(buf));
            printf("buf : %s \n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            //memset(buf,0,sizeof(buf));
            bzero(buf, sizeof(buf)); // 
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            write(netFd,buf,ret);
        }
    }
}
#endif


#if 1 // 客户端挂了， 让客户端直接重连

void azhenTest(int argc ,char * argv[]){  // 服务端
    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR,&reuse , sizeof(reuse));
    errorEqualCheck(ret, -1 , "setsockopt");
    ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");
    listen(sockfd , 50);
    struct sockaddr_in clientAddr;
    //socklen 必须赋初值
    socklen_t socklen = sizeof(clientAddr);

    //新的描述符 , 通信文件描述符
    //int netFd = accept(sockfd ,NULL , NULL );

    //fd_set rdset; // 只监听读事件

    //手动把集合分开
    fd_set monitorSet; //监听集合 ， 监听netfd stdin的
    fd_set readySet;   //就绪集合  //监听是否有人连过来的
    FD_ZERO(&monitorSet);    
    FD_SET(sockfd, &monitorSet);  //没有客户端时， 监听连接
    char buf[4096] = {0};

    int netfd = -1; // 客户端不存在
    
    //将重置集合方到select 前， 用的 mempcy
    while(1){ //每次循环开始要设置监听集合 ，但是监听集合有两种可能性 =》两个集合 ，避免在while中if 

        //readySet 和monitorSet 一致
        memcpy( &readySet , &monitorSet , sizeof(monitorSet)); //monitorSet -> readySet

        // 每次select改的都是readySet  ， monitorSet不会随着select的调用而变化
        select(20 , &readySet , NULL ,NULL ,NULL); 
        if(FD_ISSET(sockfd,&readySet)){ //有人连接
            netfd =accept(sockfd ,NULL , NULL );
            printf("客户端上线\n");   
            FD_CLR(sockfd , &monitorSet); //有了客户端之后 ， 监听集合变成监听netfd stdin
            FD_SET(netfd, &monitorSet);
            FD_SET(STDIN_FILENO, &monitorSet);
        }
        if(netfd != -1 && FD_ISSET(netfd,&readySet)){
            memset(buf,0,sizeof(buf));
            ssize_t ret = read(netfd,buf,sizeof(buf));
            if(ret == 0){ // 断开连接的信息
                //客服端要断开了
                FD_SET(sockfd , &monitorSet); 
                FD_CLR(netfd, &monitorSet);
                FD_CLR(STDIN_FILENO, &monitorSet);
                close(netfd);
                netfd = -1;
                printf("客户端断开 , 服务器进入连接模式\n");
                continue;
            } 
            printf("客户端  : %s \n",buf);
        }
        if(netfd != -1 && FD_ISSET(STDIN_FILENO,&readySet)){
            bzero(buf, sizeof(buf)); // 
            ssize_t ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){ // ctrl + D  , 服务器主动断开现有连接， 打算进入等待新的连接状态
                FD_SET(sockfd , &monitorSet); 
                FD_CLR(netfd, &monitorSet);
                FD_CLR(STDIN_FILENO, &monitorSet);
                close(netfd);
                netfd = -1;
                printf("服务端断开 , 服务器进入连接模式\n");
                continue;
            } 
            write(netfd,buf,ret);
        }
    }
}


void azhenTest2(int argc ,char * argv[]){  // 服务端 // 废的代码
    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR,&reuse , sizeof(reuse));
    errorEqualCheck(ret, -1 , "setsockopt");
    ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");
    listen(sockfd , 50);
    struct sockaddr_in clientAddr;
    //socklen 必须赋初值
    socklen_t socklen = sizeof(clientAddr);

    fd_set monitorSet; //监听集合 ， 监听netfd stdin的
    FD_ZERO(&monitorSet);    
    FD_SET(sockfd, &monitorSet);  //没有客户端时， 监听连接
    char buf[4096] = {0};

    int netfd = -1; // 客户端不存在
    while(1){ 
        printf("301------------------\n");
        if(netfd != -1){
            FD_ZERO(&monitorSet);
            FD_SET(netfd, &monitorSet);
            FD_SET(STDIN_FILENO, &monitorSet);
        }
        select(20 , &monitorSet , NULL ,NULL ,NULL); 
        printf("308------------------\n");
        if(FD_ISSET(sockfd,&monitorSet)){ 
            printf("310------------------\n");
            netfd =accept(sockfd ,NULL , NULL );
            printf("客户端上线\n");   
            FD_ZERO( &monitorSet); 
            FD_SET(netfd, &monitorSet);
            FD_SET(STDIN_FILENO, &monitorSet);
        }
        printf("316------------------\n");
        if(FD_ISSET(netfd,&monitorSet)){
            printf("318------------------\n");
            memset(buf,0,sizeof(buf));
            ssize_t ret = read(netfd,buf,sizeof(buf));
            if(ret == 0){// 断开连接的信息
                //客服端要断开了
                FD_SET(sockfd , &monitorSet); 
                FD_CLR(netfd, &monitorSet);
                FD_CLR(STDIN_FILENO, &monitorSet);
                close(netfd);
                netfd = -1;
                printf("客户端断开 , 服务器进入连接模式\n");
                continue;
            }
            printf("客户端  : %s \n",buf);
        }
        printf("332------------------\n");
        if(FD_ISSET(STDIN_FILENO,&monitorSet)){
            bzero(buf, sizeof(buf)); // 
            ssize_t ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){ // ctrl + D  , 服务器主动断开现有连接， 打算进入等待新的连接状态
                FD_SET(sockfd , &monitorSet); 
                FD_CLR(netfd, &monitorSet);
                FD_CLR(STDIN_FILENO, &monitorSet);
                close(netfd);
                netfd = -1;
                printf("服务端断开 , 服务器进入连接模式\n");
                continue;
            } 
            write(netfd,buf,ret);
        }
        printf("347------------------\n");
    }
}
#endif

#if 1 //聊天室

typedef struct{
    int isConnected; //0 未连接 ， 1 已连接
    int netfd;
    time_t lastActive;
}Con_t;
void serverTest(int argc ,char * argv[]){

    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR,&reuse , sizeof(reuse));
    errorEqualCheck(ret, -1 , "setsockopt");
    ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");
    listen(sockfd , 50);

    //accept 参数 ， 用来获取客户端IP+port
    //struct sockaddr_in clientAddr;
    //socklen 必须赋初值
    //socklen_t socklen = sizeof(clientAddr);

    //新的描述符 , 通信文件描述符
    //int netFd = accept(sockfd ,NULL , NULL );

    //fd_set rdset; // 只监听读事件

    //手动把集合分开
    fd_set monitorSet; //监听集合 ， 监听netfd stdin的
    fd_set readySet;   //就绪集合  //监听是否有人连过来的
    FD_ZERO(&monitorSet);    
    FD_SET(sockfd, &monitorSet);  //没有客户端时， 监听连接
   

    //需要设计一个数据结构存储 所有客户端的netfd 和 上一次活跃时间
    // int netfd[1024]; // 
    // time_t lastActive[1024];
    // for(int i =0;i<1024;++i){
    //     netfd[i] = -1;
    //     lastActive[i]
    // }
    Con_t client[1024];
    for(int i =0;i<1024;++i){
        client[i].isConnected = 0;
    }
    int curidx = 0; //下一次插入的netfd下标
    //建一个hash table : net->index  
    int fdToIndex[1024]; // 客户端不存在
    for(int i =0;i<1024;++i) fdToIndex[i] = -1;

    char buf[4096] = {0}; // 转发
    time_t now ;

    while(1){  // 事件循环
        memcpy( &readySet , &monitorSet , sizeof(monitorSet)); //monitorSet -> readySet
       
        struct timeval timeout;
        timeout.tv_sec = 1;
        timeout.tv_usec =0;
        // 每次select改的都是readySet  ， monitorSet不会随着select的调用而变化
        select(1024 , &readySet , NULL ,NULL ,&timeout); 
        
        now = time(NULL);
        printf("now  %s" , ctime(&now));
        if(FD_ISSET(sockfd,&readySet)){ //有人连接
            client[curidx].netfd =accept(sockfd ,NULL , NULL );
            client[curidx].isConnected = 1;
            client[curidx].lastActive = now;
            fdToIndex[ client[curidx].netfd ] = curidx;
            printf("%s 客户端%d上线 ,netfd = %d   \n" ,ctime(&now),curidx ,client[curidx].netfd);   
            //FD_CLR(sockfd , &monitorSet); //多个客户端加进来 ， 所有 sockfd 需要一直监听
            FD_SET(client[curidx].netfd, &monitorSet);
            //FD_SET(STDIN_FILENO, &monitorSet);   //服务端只有转发功能
            ++curidx;
        }
        //printf("------------------420\n");
        for(int i =0;i<curidx ;++i){
            if(FD_ISSET(client[i].netfd,&readySet) && client[i].isConnected == 1  ){
                memset(buf,0,sizeof(buf));
                printf("%s 客户端 %d 活跃  \n" ,ctime(&now), fdToIndex[ client[i].netfd] );   
                ssize_t ret = read(client[i].netfd,buf,sizeof(buf));
                if(ret == 0){ //对方主动断开了
                    printf("客户端 %d 主动断开 ,byebye \n ",fdToIndex[ client[i].netfd]);
                    close(client[i].netfd); 
                    FD_CLR( client[i].netfd , &monitorSet); //不监听就移除
                    fdToIndex[ client[i].netfd ] = -1;
                    client[i].isConnected = 0;
                    continue;
                }
                client[i].lastActive = now;
                for(int j =0; j < curidx; ++j ){
                    if(client[i].isConnected == 1 && i != j){ // 转发给还存在的， 以及排除自己
                        //printf("------------------435\n");
                        write(client[j].netfd , buf, ret); 
                    }
                }
            }
           // printf("------------------440\n");
        }

        for(int  i = 0;i<curidx ;++i){
            if(client[i].isConnected ==1 && now - client[i].lastActive > 10){
                printf("%s 客户端 %d 长时间不在 ,byebye \n ",ctime(&now) ,fdToIndex[ client[i].netfd]);
                close(client[i].netfd); 
                FD_CLR( client[i].netfd , &monitorSet); //不监听就移除
                fdToIndex[ client[i].netfd ] = -1;
                client[i].isConnected = 0;
               
            }
        }
       
    }
}

void visitBaiduTest(){
    //http 协议的请求
    const char query[]= "GET / HTTP/1.0\r\n"
                       "Host: www.baidu.com\r\n"
                        "\r\n";
    const char hostname[] = "www.baidu.com";
    struct hostent * entry = gethostbyname(hostname);
    if(entry == NULL){
        herror("gethostbyname");
        return ;
    }
    // for(int i =0;entry->h_addr_list[i] != NULL;++i){
    //     printf("alias = %s \n ", entry->h_addr_list[i]); // 0号就是第一个IP 
    // } 
    
    // for(int i =0;entry->h_addr_list[i] != NULL;++i){
    //     char ip[1024] = {0};
    //     inet_ntop( entry->h_addrtype , entry->h_addr_list[i] , ip , 1024 );
    //     printf(" ip = %s \n ", ip);
    // } 
    //("---------------------490\n");
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    memcpy(&addr.sin_addr, entry->h_addr_list[0] , sizeof(addr.sin_addr));

    //printf("ip = %s \n",inet_ntoa(addr.sin_addr));

    //printf("---------------------495\n");
    int sockfd = socket(AF_INET , SOCK_STREAM, 0);
    int ret = connect(sockfd , (struct sockaddr * )(&addr) , sizeof(addr));
    errorEqualCheck(ret ,-1, "connect");
    //printf("---------------------498\n");
    cout<<strlen(query)<<endl;
    ret = write(sockfd , query , strlen(query));
    errorEqualCheck(ret ,-1, "write");
    cout<<ret<<endl;
    //printf("---------------------500\n");
    char buf[4096] = {0};
    for(int i =0;i<1000;i++){
        bzero(buf,4096);
        ret =read(sockfd , buf, 4096);
        if(ret == 0) break;
        errorEqualCheck(ret ,-1, "read");
        printf("%s \n",buf);
        cout<<ret<<endl;
    }
   
    
}


#endif 


void udpServerTest(int argc ,char * argv[]){
    argsCheck(argc , 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = bind(sockfd ,(struct sockaddr*)(&serverAddr), sizeof(serverAddr) );
    errorEqualCheck(ret  , -1 ,"bind" );
    //第一次必须 是客户端先给服务端发 ， 因为客户端没有bind , 服务端不知道对面的ip和端口

    struct sockaddr_in clientAddr;   // 知道客户端的ip+ port , 方便回消息 
    socklen_t socklen = sizeof(clientAddr); 
    char buf[4096] = {0};
    recvfrom(sockfd , buf , 4096, 0,(struct sockaddr*)(&clientAddr),&socklen );
    printf("buf = %s  , ip = %s  port = %d  " , buf , inet_ntoa(clientAddr.sin_addr)  , ntohs(clientAddr.sin_port));

    sendto(sockfd ,"world ", 5, 0 ,(struct sockaddr*)(&clientAddr), sizeof(clientAddr) );
    sendto(sockfd ,"world ", 5, 0 ,(struct sockaddr*)(&clientAddr), sizeof(clientAddr) );

}

void udpServerTest1(int argc ,char * argv[]){  //即时聊天
    argsCheck(argc , 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

    int ret = bind(sockfd ,(struct sockaddr*)(&serverAddr), sizeof(serverAddr) );
    errorEqualCheck(ret  , -1 ,"bind" );
    //第一次必须 是客户端先给服务端发 ， 因为客户端没有bind , 服务端不知道对面的ip和端口

    struct sockaddr_in clientAddr;   // 知道客户端的ip+ port , 方便回消息 
    socklen_t socklen = sizeof(clientAddr); 
    char buf[4096] = {0};
    printf("-------------571\n");
    recvfrom(sockfd , buf , 4096, 0,(struct sockaddr*)(&clientAddr),&socklen );
    printf("buf = %s  , ip = %s  port = %d  \n" ,
         buf , inet_ntoa(clientAddr.sin_addr)  , ntohs(clientAddr.sin_port));

    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO , &rdset);
        FD_SET(sockfd, &rdset);

        select(sockfd+1 , &rdset , NULL ,NULL ,NULL);

        if(FD_ISSET(sockfd , &rdset) ){
            bzero(buf ,4096);
            ssize_t ret = recvfrom(sockfd , buf ,4096 , 0 , NULL, NULL);
            if(ret ==0){
                break;
            }
            printf("buf = %s" , buf  );
        }
        if(FD_ISSET(STDIN_FILENO , &rdset) ){
            bzero(buf ,4096);
            ssize_t ret =  read(STDIN_FILENO , buf ,4096 );
            if(ret == 0){//ctrl +D
                sendto(sockfd ,buf,0, 0 ,(struct sockaddr*)(&clientAddr), sizeof(clientAddr) );
                break;
            } 
            sendto(sockfd ,buf,strlen(buf), 0 ,(struct sockaddr*)(&clientAddr), sizeof(clientAddr) );
            //printf("buf = %s   ret = %d  \n" , buf  , ret );
        }
    }
}

void epollTest(int argc ,char * argv[]){  // 服务端 入门级聊天室
    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR,&reuse , sizeof(reuse));
    errorEqualCheck(ret, -1 , "setsockopt");
    ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");
    listen(sockfd , 50);

    //struct sockaddr_in clientAddr;
    //socklen 必须赋初值
    //socklen_t socklen = sizeof(clientAddr);
    //新的描述符 , 通信文件描述符
    int netFd = accept(sockfd ,NULL , NULL );

    //fd_set rdset; // 只监听读事件
    int epfd = epoll_create(1);  // 创建epoll文件对象

    struct epoll_event events; //什么情况就绪， 就绪了怎么办
    events.events = EPOLLIN; // 读就绪
    events.data.fd = STDIN_FILENO; // 放自己的描述符
    epoll_ctl(epfd , EPOLL_CTL_ADD , STDIN_FILENO ,&events );
    events.events = EPOLLIN; // 读就绪
    events.data.fd = netFd; // 放自己的描述符
    epoll_ctl(epfd , EPOLL_CTL_ADD , netFd , &events);
    char buf[4096] = {0};
    while(1){
        // FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        // FD_SET(STDIN_FILENO, &rdset);
        // FD_SET(netFd, &rdset);       //socket  和stdin 加入监听

        // select(netFd+1 , &rdset , NULL ,NULL ,NULL); 
        struct epoll_event readyset[2];
        int readyNum = epoll_wait(epfd , readyset , 2 , -1);
 
        for(int i = 0;i< readyNum ;++i){
            if(readyset[i].data.fd == STDIN_FILENO){ // stdin 就绪
                bzero(buf, sizeof(buf)); // 
                ssize_t ret =  read(STDIN_FILENO,buf,sizeof(buf));
                if (ret == 0){
                    close(netFd);
                    printf("CTRL D 服务器断开,byebye \n");
                    break;
                }
                write(netFd,buf,ret);
            }else{
                memset(buf,0,sizeof(buf));
                ssize_t ret =  read(netFd,buf,sizeof(buf));
                if (ret == 0){
                    close(netFd);
                    printf("对方 客户端器端断开 , byebye  \n");
                    break;
                }
                printf("buf : %s \n",buf);
            }
        }
        // if(FD_ISSET(netFd,&rdset)){
        //     memset(buf,0,sizeof(buf));
        //     read(netFd,buf,sizeof(buf));
        //     printf("buf : %s \n",buf);
        // }
        // if(FD_ISSET(STDIN_FILENO,&rdset)){
        //     //memset(buf,0,sizeof(buf));
        //     bzero(buf, sizeof(buf)); // 
        //     int ret =  read(STDIN_FILENO,buf,sizeof(buf));
        //     write(netFd,buf,ret);
        // }
       
    }
}
void epollTest1(int argc ,char * argv[]){  // 服务端 断线重连
    argsCheck(argc , 3);
    
    // 监听文件描述符
    int sockfd = socket(AF_INET , SOCK_STREAM , 0 );
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int reuse = 1; // 允许重用
    int ret = setsockopt(sockfd , SOL_SOCKET , SO_REUSEADDR,&reuse , sizeof(reuse));
    errorEqualCheck(ret, -1 , "setsockopt");
    ret = bind(sockfd , (struct sockaddr *)&serverAddr, sizeof(serverAddr) );
    errorEqualCheck(ret, -1 , "bind");
    listen(sockfd , 50);


    //int netFd = accept(sockfd ,NULL , NULL );

    //监听集合 epoll_ctl 是一个一个监听放进 内核数据结构中 
    //一开始监听 sockfd 看有没人连过来
    int netfd = -1; //最开始没有客户端连入
    int epfd = epoll_create(1);    
    struct epoll_event events; //什么情况就绪， 就绪了怎么办
    events.events = EPOLLIN; // 读就绪
    events.data.fd = sockfd; // 放自己的描述符
    epoll_ctl(epfd , EPOLL_CTL_ADD , sockfd ,&events );

    char buf[4096] = {0};
    while(1){

        struct epoll_event readyset[1024]; //就绪集合
        int readyNum = epoll_wait(epfd , readyset , 1024 , -1);
 
        for(int i = 0;i< readyNum ;++i){
            if(readyset[i].data.fd == sockfd){ // stdin 就绪
                netfd = accept(sockfd ,NULL , NULL );
                printf("客户端已连接\n");
                epoll_ctl(epfd , EPOLL_CTL_DEL , sockfd ,NULL);
                events.events = EPOLLIN;
                events.data.fd = netfd;
                epoll_ctl(epfd , EPOLL_CTL_ADD , netfd ,&events );
                events.events = EPOLLIN;
                events.data.fd = STDIN_FILENO;
                epoll_ctl(epfd , EPOLL_CTL_ADD , STDIN_FILENO ,&events );
            }else if(netfd != -1 &&  readyset[i].data.fd == netfd){ 
                memset(buf,0,sizeof(buf));
                ssize_t ret =  read(netfd,buf,sizeof(buf));
                if(ret == 0){ 
                    epoll_ctl(epfd , EPOLL_CTL_DEL , netfd ,NULL);
                    epoll_ctl(epfd , EPOLL_CTL_DEL , STDIN_FILENO ,NULL);

                    events.events = EPOLLIN; // 读就绪
                    events.data.fd = sockfd; // 放自己的描述符
                    epoll_ctl(epfd , EPOLL_CTL_ADD , sockfd ,&events );
                    close(netfd); netfd = -1;
                    printf("客户端主动断开，进入重连模式 \n");
                    break;
                }
                printf("客户端 : %s \n",buf);
            }else if(netfd != -1 &&  readyset[i].data.fd == STDIN_FILENO){ 
                bzero(buf, sizeof(buf)); // 
                ssize_t ret =  read(STDIN_FILENO,buf,sizeof(buf));
                if(ret == 0){ 
                    epoll_ctl(epfd , EPOLL_CTL_DEL , netfd ,NULL);
                    epoll_ctl(epfd , EPOLL_CTL_DEL , STDIN_FILENO ,NULL);

                    events.events = EPOLLIN; // 读就绪
                    events.data.fd = sockfd; // 放自己的描述符
                    epoll_ctl(epfd , EPOLL_CTL_ADD , sockfd ,&events );
                    close(netfd); netfd = -1;
                    printf("服务端主动断开，服务端进入重连模式 \n");
                    break;
                }

                write(netfd,buf,ret);
            }//netfd != -1 是了 连接如果已经断开了， 但是又继续检查就绪集合
        } 
    }
}

void readNoBlockTest(int argc ,char * argv[]){
    int fd =open("file1" , O_RDWR);
    char buf[3] = {0};
    while(1){
        bzero(buf,3);
        ssize_t ret = read(fd , buf, 2);
        printf("%ld  %s \n" , ret , buf);
        if(ret ==0 ){
            break;
        }
    } 
}

void readBlockTest(int argc ,char * argv[]){
   
        int fd =open("1.pipe" , O_RDONLY);
        char buf[3] = {0};

        while(1){
            bzero(buf, 3);
            ssize_t ret = read(fd , buf, 2);
            printf("%ld  %s \n" , ret , buf);
            if(ret ==0 ){
               // break;
            }
            sleep(1);
        }
    
}

int main(int argc ,char * argv[]){
    readBlockTest(argc, argv);
    return 0;
}