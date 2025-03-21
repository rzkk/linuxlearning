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
typedef struct{
    int length;
    char data[1000];
}train_t;
void test1(int argc , char* argv[]){

    argsCheck(argc , 3) ;
    if(fork()){ //父进程     接收文件名字，长度 ， 内容 
       

        int fdr_pipe = open(argv[1] , O_RDONLY);
        errorEqualCheck(fdr_pipe,-1 ," openpipe");
        wait(NULL);  // 父等子

        train_t train;
        //memset( &train , 0 , sizeof(train));
        read(fdr_pipe , &train.length, sizeof(train.length)); //read 的多少是能控制的
        read(fdr_pipe , train.data, train.length); // 这里接受的是没有 \0 的
        //train.data[train.length] = '\0'; //强行加上 \0 
        char path[1024] = {0};
        mkdir("dir1",0777);
        sprintf(path , "%s%s" ,"dir1/",train.data ); //因此这里拼的， 就会出问题

        //printf("%s\n",path);

        int fdw_file = open(path , O_RDWR|O_CREAT|O_TRUNC ,0666);
        errorEqualCheck(fdw_file,-1,"open");

        //char buf[1024] = {0};
        read(fdr_pipe , &train.length, sizeof(train.length)); //read 的多少是能控制的
        ssize_t sret = read(fdr_pipe , train.data, train.length);

        write(fdw_file, train.data,sret);


        close(fdr_pipe);
        close(fdw_file);

    }else{  // 子进程 发文件名字长度


        int fdw_pipe = open(argv[1] , O_WRONLY);  //写入pipe
        errorEqualCheck(fdw_pipe,-1 ," openpipe");

        train_t train;
        train.length =  strlen(argv[2]); //没有 \0 
        //printf("%ld %s ",strlen(argv[2]),argv[2] );

        memcpy(train.data  , argv[2] , train.length );
        //data.data = argv[2];
        //write(fdw_pipe , &train, sizeof(train) ); //文件名  全都发过去了， 包括后面的0
        write(fdw_pipe , &train.length, sizeof(train.length) );  //length + data正经数据
        write(fdw_pipe , train.data, train.length ); 

        int fdr_file = open(argv[2],O_RDONLY);
        errorEqualCheck(fdr_file,-1 ," openfile");

        //char buf[4096] = {0};
        ssize_t srret = read(fdr_file, train.data , sizeof(train.data));
        errorEqualCheck(srret,-1 ," read");

        train.length = srret;
        write(fdw_pipe , &train.length, sizeof(train.length) );  //length + data正经数据
        write(fdw_pipe , train.data, train.length ); 
        
        //ssize_t swret =write(fdw_pipe , &train, sizeof(train) ); //文件名


        close(fdr_file);
        close(fdw_pipe);
    }
}


#endif

#if  0
void test1(){
    printf("pid %d  ppid  %d  \n" , getpid() , getppid());
}
void systemTest(){
    system("python3");
}
#endif 
#if  0
int g_a = 0;
int forkTest1(){

    if(fork()){  // 父亲
        while(1){
            sleep(1);
        }
       
    }else{
       return 0;
    }
    
}
void forkTest2(){

    printf("hello");
    fork(); 
    printf("world\n");
}
void forkTest3(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    // int fd1 =  open(argv[1] , O_RDWR);
    // //FILE * fp = fopen(argv[1] , "r+");
    // errorEqualCheck(fd1 , -1,"open");
    if(fork()){
        int fd1 =  open(argv[1] , O_RDWR);
        //FILE * fp = fopen(argv[1] , "r+");
        errorEqualCheck(fd1 , -1,"open");
        sleep(1);
        //fwrite("world" , 1 ,sizeof("world") ,fp);
        write(fd1, "world",5);
    }else{
        int fd1 =  open(argv[1] , O_RDWR);
        //FILE * fp = fopen(argv[1] , "r+");
        errorEqualCheck(fd1 , -1,"open");
        ///fwrite("hello" , 1 ,sizeof("hello") ,fp);
        write(fd1, "hello",5);
    }
}
void execlTest(){
    printf("peocess.cpp:pid  %d \n", getpid());
    sleep(1);
    char  * argv[] = {"./add","3","4",NULL};
    execv(  "add", argv);

    printf("打印不出来  %d \n", getpid());
}
int  forkTest4(){
    //argsCheck(argc , 2) ;
    int wstatus;
    if(fork()){
        wait(&wstatus);
        if(WIFEXITED(wstatus)){  //是否正常退出
            printf("%d "  , WEXITSTATUS(wstatus)); // 打印退出时状态
        }else if(WIFSIGNALED(wstatus)){  //异常退出
            printf("%d "  , WTERMSIG(wstatus));  //打印被哪个信号终止的
        }
    }else{
        abort(); 
    }
}
void gidTest(){

    if(fork()){
        printf("parent pid : %d , pgid :  %d , pgid of ppid : %d \n",
            getpid(), getpgid(0),getpgid(getppid()));
        wait(NULL);
    }else{
        setpgid(0,0);
        printf("child  pid : %d , pgid :  %d , pgid of ppid : %d \n",
            getpid(), getpgid(0),getpgid(getppid()));
        while(1){
            sleep(1);
        }
    }
}
void sidTest(){

    if(fork()){
        exit(0);
    }else{
        
        printf(" before  sid : %d \n",getsid(0) );
        setsid();
        printf(" after   sid : %d \n",getsid(0) );
    }
} 
#include<syslog.h>
void daemon(){

    //新建会话
    if(fork()){
        exit(0);
    }
    
    setsid();
    //关闭设备  所有进程都是孤儿
    for(int i =0;i< 64;i++){  //自己已经脱离终端了 将父打开的所有的设备都关闭 ， 不知道多少 ，遍历一下
        close(i);
    }

    //修改环境属性
    chdir("/");
    umask(0); 
} 
void daemonTest(){
    daemon(); //创建守护进程
    int i =0;
    while(1){
        syslog(LOG_INFO,"i am daemon , %d " , i++);
        sleep(2);
    }
}
#endif 

#if 1  //IPC

void popenTest(){
    // FILE * fp1 = popen("./tempTest","w");
    // errorEqualCheck(fp1 ,NULL,"popen");
    // //sleep(3);
    // fwrite("1 5" , 1,3,fp1);
    // pclose(fp1);

    FILE * fp = popen("./tempTest","r");
    errorEqualCheck(fp ,NULL,"popen");
    //sleep(3);
    char buf[1024] = {0};
    fread(buf , 1,sizeof(buf),fp);
    cout<<buf<<endl;
    pclose(fp);
}

void pipeTest(){
    int fds[2];
    pipe(fds);
    printf("%d %d \n " , fds[0],fds[1]);

    char buf[1024] = {0};

    write(fds[1] , "hello" , 5);   // 管道必须先写再读

    read(fds[0] , buf, sizeof(buf));

    printf("%s ",buf);
    close(fds[0]);
    close(fds[1]);
}
void pipeForkTest(){
    int fds1[2], fds2[2];
    pipe(fds2);
    pipe(fds1);
    //pipe1 :  父 -> 子
    //pipe2 :  父 <- 子 
    //如果两个都是先读 阻塞
    if(fork()){  // 父亲
        close(fds1[0]); //关 pipe1 的读
        close(fds2[1]); //关 pipe2 的写

        write(fds1[1] , "nihao" , 5);   // 管道必须先写再读
        char buf[1024] = {0};

        read(fds2[0] , buf, sizeof(buf));

        printf("parent  %s \n",buf);
    }else{  // 子
        close(fds1[1]); //关 pipe1 的写
        close(fds2[0]); //关 pipe2 的读
        
        //sleep(3);   // 导致父的读阻塞
        write(fds2[1] , "hello" , 5);  
        char buf[1024] = {0};
        read(fds1[0] , buf, sizeof(buf));
        printf("child   %s \n",buf);
    }
   
}

int num = 100000000;
void shmgetTest(){
    int shmid = shmget(IPC_PRIVATE , 4096 , IPC_CREAT|0600);
    errorEqualCheck(shmid, -1,"shmget");
    printf("%d \n" ,shmid);

    //*p = 0;
    if(fork()){
        int * p = (int*)shmat(shmid, NULL ,0);
        for(int i = 0;i<num;i++){
            ++*p;
        }
        wait(NULL);
        printf("%d \n",*p);
    }else{
        int * p = (int*)shmat(shmid, NULL ,0);
        for(int i = 0;i<num;i++){
            ++*p;
        }
    }
}
void shmgetDeleteTest(){
    int shmid = shmget(0x1234 , 4096 , IPC_CREAT|0600);
    errorEqualCheck(shmid, -1,"shmget");
    printf("%d \n" ,shmid);

    //*p = 0;
    if(fork()){
        int * p = (int*)shmat(shmid, NULL ,0);
        for(int i = 0;i<num;i++){
            ++*p;
        }
        //wait(NULL);
        while(1){
            sleep(1);
        }
        printf("%d \n",*p);
    }else{
        int * p = (int*)shmat(shmid, NULL ,0);
        for(int i = 0;i<num;i++){
            ++*p;
        }
        while(1){
            sleep(1);
        }
    }
}

void handler1(int signum){
    printf("before signum = %d \n",signum);
    sleep(4);
    printf("after signum = %d \n",signum);
}

void signalTest(){
    signal(SIGINT , handler1);
    sleep(7);
}

void handler2(int signum){
    printf(" signum = %d \n",signum);
}
void signalrestartTest(){
    signal(SIGINT , handler2);
    char buf[1024] = {0};
    ssize_t sret = read(STDIN_FILENO , buf , sizeof(buf));
    printf("%ld  %s \n",sret , buf);
}
void handler3(int signum ){
    printf("before signum = %d \n",signum);
    sleep(4);
    printf("after signum = %d \n",signum);
}
void handler4(int signum ,siginfo_t * siginfo , void * p ){
    printf(" signum = %d  , uid = %d   %s \n",signum , siginfo->si_uid , (char *)p); //看谁发的信号

}
void sigactionTest(){
    struct sigaction act;
    memset(&act , 0 , sizeof(act));
    act.sa_sigaction = handler4;  //结构成员 sa_sigaction
    act.sa_flags = SA_RESTART | SA_SIGINFO; // SA_SIGINFO
    sigaction(SIGINT , &act,NULL);
    sigaction(SIGQUIT , &act,NULL);

    //sigemptyset(&act.sa_mask); //清空的是额外的， 调用2时屏蔽的2 不属于额外的
    // sigaddset(&act.sa_mask ,SIGINT );
    //sigaddset(&act.sa_mask ,SIGQUIT );
    //act.__sigaction_handler.sa_handler = handler3;
    //act.sa_mask  ;
    while(1){
        sleep(1);
    }
}
void handler5(int signum  ){
    printf(" signum = %d  \n",signum ); //看谁发的信号
    sleep(5);
    sigset_t pending;
    sigpending(&pending);

    if(sigismember(&pending , SIGINT)){
        printf("SIGINT is in pending \n");
    }else {
        printf("SIGINT is not in  pending \n");
    }
}


void sigprocmaskTest(){
    
    signal(SIGINT , handler1);
    sigset_t set;
    sigemptyset(&set); // 清空
    sigaddset(&set , SIGINT);
    
    sigprocmask(SIG_BLOCK , &set , NULL);
    sleep(5);

    sigset_t pending;
    sigpending(&pending);
    if(sigismember(&pending , SIGINT)){
        printf("SIGINT is in pending \n");
    }else {
        printf("SIGINT is not in  pending \n");
    }
    sigprocmask(SIG_UNBLOCK , &set , NULL);
}

void killTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;

    kill(atoi(argv[1]) , 9); // kill -9 argv[1]
}
void alarmHandler(int signum){
    time_t now = time(NULL);
    printf("%s \n" , ctime(&now));
}
void alarmTest(){
    
    signal(SIGALRM , alarmHandler);
    alarm(10);
    alarmHandler(0);
    while(1){
        sleep(1);
    }
}
void pauseTest(){

    signal(SIGALRM , alarmHandler);
    alarm(10);
    //alarmHandler(0);
    pause();
    printf("byebye\n");
}
void itimerHandler(int signum){
    time_t now = time(NULL);
    printf("now = %s \n" , ctime(&now));
}
void itimerTest(){
    signal(SIGALRM ,itimerHandler );
    struct  itimerval  itimer;
    itimer.it_interval.tv_sec = 1;
    itimer.it_interval.tv_usec = 0;
    itimer.it_value.tv_sec = 3;
    itimer.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL ,&itimer ,NULL );
    itimerHandler(0);
    while(1){
        sleep(1);
    }
}
#endif


int main(int argc , char* argv[]){
// #ifdef DEBUG
//     argsCheck(argc , 3) ;
// #endif
    //killTest(argc ,argv );
   //sigprocmaskTest();
   //pauseTest();
   itimerTest();

    return 0;
        
}

 