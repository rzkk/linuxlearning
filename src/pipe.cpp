#include"func.h"

void  errorCheck(int argc , int num,const char *errormsg){
    if(argc == num)
    {
        perror(errormsg);
        assert(0);
    }
   
}
void errorCheck(void * argc1 , void * argc2,const char *errormsg){
    if(argc1 == argc2)
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

void openPipeTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    int fdw = open(argv[1],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
    printf("write open\n");
    sleep(5);   //阻塞十秒 
    printf("sllp over \n");
    write(fdw,"hello",5);

    while(1){
        sleep(1);
    }
   
}
void closePipeTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    int fdw = open(argv[1],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
    printf("write open\n");
    
    sleep(3);
     //write (fdw,"hello",5);

    close(fdw);
    printf("write close\n");
   
}

void doublePipeTest(int argc , char* argv[]){
    argsCheck(argc , 3) ;

    int fdr = open(argv[1],O_WRONLY);
    errorCheck(-1,fdr,"pipe open");

    int fdw = open(argv[2],O_RDONLY);
    errorCheck(-1,fdw,"pipe open");

    printf("pipe connected\n");
}

#endif


#if 1  //聊天
void talkTest1(int argc , char* argv[]){
    argsCheck(argc , 3) ;
    int fdw = open(argv[1],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
    int fdr = open(argv[2],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    //cout<<"aqiang  conn ecte d "<<endl;
    printf("aqiang  conn ecte d \n");
    char buf[4096] = {0};


    while(1){
        //读azhen 
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));
        printf("buf =  %s \n",buf);

        //读stdin

        memset(buf,0,sizeof(buf));
        int ret =  read(STDIN_FILENO,buf,sizeof(buf));
        write(fdw,buf,ret);
    }
    close(fdr); close(fdw); 
}
void talkTest2(int argc , char* argv[]){
    argsCheck(argc , 3) ;
    int fdw = open(argv[1],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
    int fdr = open(argv[2],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    //cout<<"aqiang  conn ecte d "<<endl;
    printf("aqiang  connected \n");
    char buf[4096] = {0};
    fd_set rdset;
    struct timeval timeout;
    
    while(1){
        FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);       // pipe 的读端 和stdin 加入监听
        //select(fdr+1 , &rdset , NULL ,NULL ,NULL);
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;  //不能省略
        int ret = select(fdr+1 , &rdset , NULL ,NULL ,&timeout);
        if(ret == 0){
            time_t now = time(NULL); //获取当前时间
            printf("超时了 , %s \n", ctime(&now));//转日历时间
            continue;
        }
        if(FD_ISSET(fdr,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret = read(fdr,buf,sizeof(buf));
            if(ret == 0){
                printf("对方关闭\n");
                break;
            }    
                printf("buf : %s \n",buf);
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){  //ctrl + D : 发一个终止符 EOF 
                //printf("对方关闭\n");
                write(fdw,"nishigehaoren",ret);
                break; 
            }     
            write(fdw,buf,ret);
        }
    }

    close(fdr);close(fdw);
}
#endif 
#if 1 
void blockwriteTest(int argc , char* argv[]){
    // #ifdef DEBUG
    argsCheck(argc , 2) ;
    int fd = open(argv[1],O_WRONLY);
    errorCheck(-1,fd,"pipe open");
    printf("connected\n");
    char buf[512] = {0};
    int cnt = 0;

    for(int i =0;i<127;i++){
        write(fd , buf , 512);
    }

    while(1){
        write(fd , buf , 512);
        printf("write one  %d \n",cnt++);
    }
    
    close(fd);
}
#endif
#if 1 
void blockselectTest(int argc , char* argv[]){
    // #ifdef DEBUG
    argsCheck(argc , 2) ;
    int fd = open(argv[1],O_WRONLY);
    errorCheck(-1,fd,"pipe open");
    printf("connected\n");
    char buf[512] = {0};
    int cnt = 0;

    for(int i =0;i<127;i++){
        write(fd , buf , 512);
    }

    while(1){
        write(fd , buf , 512);
        printf("write one  %d \n",cnt++);
    }
    
    close(fd);
}
#endif

int main(int argc , char* argv[]){
// #ifdef DEBUG
//     argsCheck(argc , 3) ;
// #endif
    //myls2(argc ,argv );
    //mytree(argc ,argv );
    // test4(argc ,argv );
    // test5(argc ,argv );
    // test6(argc ,argv );
    //mycopy(argc ,argv );
    //compTest(argc ,argv );
    blockwriteTest(argc ,argv );
   
    return 0;           
}

