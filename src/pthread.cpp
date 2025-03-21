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
void  threadErrorCheck(int argc , int num,const char * p){
    if(argc != num)
    {
        fprintf(stderr , "%s : %s\n",p, strerror(argc));
        //assert(0);
    }
}

#if 0

void * routine(void *p){
        printf("I am child pthread \n");
    return (void*)0;
}

void pthreadCreateTest(){
    pthread_t id;

    int ret = pthread_create(&id , NULL , routine , NULL);
    pthreadErrorCheck(ret, 0 , "pthread_create");
    printf("I am main pthread\n");
    //usleep(5);
}

void * routine2(void *p){
    while(1){
        sleep(1);
    }
    return (void*)0;
}

void pthreadManyTest(){
    int cnt = 0;
    while(1){
        pthread_t id;
        int ret = pthread_create(&id , NULL , routine2 , NULL);
        pthreadErrorCheck(ret, 0 , "pthread_create");
        if(ret != 0){
            printf("%d \n",cnt);
            break;
        }
        ++cnt;
    }
    
    //printf("I am main pthread\n");
    //usleep(5);
}
int global = 0;
void * routine3(void *p){
    global ++;
    printf("child  %d \n", global);
    return (void*)0;
}
void pthreadGlobalTest(){
  
    pthread_t id;
    int ret = pthread_create(&id , NULL , routine3 , NULL);
    pthreadErrorCheck(ret, 0 , "pthread_create");
    sleep(1);
    ++global;
    printf("main  %d \n", global);

   
}
void * routine4(void *arg){

    int * p = (int*)arg;
    printf("child  %d \n", *p);
    ++*p;
    return (void*)0;
}
void pthreadHeapTest(){
    int * p = (int*)malloc(sizeof(int));
    *p = 1000;
    pthread_t id;
    int ret = pthread_create(&id , NULL , routine4 , p);
    pthreadErrorCheck(ret, 0 , "pthread_create");
    sleep(1);
    ++(*p);
    printf("main  %d \n", *p);
    free(p);
}
void * routine5(void *arg){

    int * p = (int*)arg;
    printf("child  %d \n", *p);
    ++*p;
    return (void*)0;
}
void pthreadStackTest(){
   
    int i = 10000;
    pthread_t id;
    int ret = pthread_create(&id , NULL , routine5 , &i);
    pthreadErrorCheck(ret, 0 , "pthread_create");
    sleep(1);
    ++(i);
    printf("main  %d \n", i);
}

void * routine6(void *arg){

    long p = (long)arg;
    printf("child  %ld \n", p);
    ++p;
    return (void*)0;
}
void pthreadvoidTest(){
    long  l =10000;
    pthread_t id;
    int ret = pthread_create(&id , NULL , routine6 , (void *)l);
    pthreadErrorCheck(ret, 0 , "pthread_create");
   
    ++l;
    printf("main  %ld \n", l);
}


void * routine7(void *arg){

    int * p = (int*)arg;
    printf("child  %d \n", *p);
    ++*p;
    return (void*)0;
}
void pthreadFuncTest1(){  //栈上的
    int i = 10000;
    pthread_t id;
    int ret = pthread_create(&id , NULL , routine5 , &i);
    pthreadErrorCheck(ret, 0 , "pthread_create");
}

void * routine8(void *arg){

    int * p = (int*)arg;
    printf("child  %d \n", *p);
    ++*p;
    return (void*)0;
}
void pthreadFuncTest2(){  //堆上的提前free 了
    int *  p = (int *)malloc(sizeof(int));
    *p = 1000;
    pthread_t id;
    int ret = pthread_create(&id , NULL , routine8 , p);
    pthreadErrorCheck(ret, 0 , "pthread_create");
    
    free(p);
   
    printf("free executed \n"); 
    sleep(2);
}
#endif
#if 0
 //链表
 typedef struct node_s{
    int data;
    struct node_s *next;
 }node_t , *LinkList;

void InitList(LinkList  &list){    // 要加引用 ，否则值传递过来， list 改了跟list1 没关系
    list = (node_t*)malloc(sizeof(node_t));
    list->data = 0;
    list->next = NULL;
}
 void headInsert(LinkList & list , int data   ){
    node_t * pnew = (node_t *)malloc(sizeof(node_t));
    pnew->data = data;
    pnew->next = list->next;
    list->next = pnew;
    list->data++; 
 }
 void nodeInsert(LinkList & list ,int pos, int data   ){
    if(pos > list->data || pos < 0 ){
        printf("pos error\n");
    }
    node_t * p = list;
    while(pos){
        p = p->next;
        --pos;
    }
    node_t * pnew = (node_t *)malloc(sizeof(node_t));
    pnew->data = data;
    pnew->next = p->next;
    p->next = pnew;
    list->data++;
 }
 void tailInset(LinkList & list , int data   ){
    nodeInsert(list , list->data,data);
 }
 int length(LinkList &list){
    return list->data;
 }
void printList(LinkList &list){ 
    node_t * p = list->next;
    while(p){
        cout<<p->data<< " ";
        p = p->next;
    }
    cout<<endl;
}
 void linkListTest(){
    LinkList  list1 ;
    InitList(list1);
    tailInset(list1,0);
    headInsert(list1 , 1);
    headInsert(list1 , 2);
    headInsert(list1 , 3);
    headInsert(list1 , 4);
    nodeInsert(list1 , 3,5);
    tailInset(list1,6);
    tailInset(list1,7);
    printList(list1);
 }
 void * threadFunc(void *arg){
    LinkList list = (LinkList)arg;
    printf("I am child \n");
    printList(list);
    return NULL;
 }
void pthreadListTest(){
    LinkList  list1 ;
    InitList(list1);
    tailInset(list1 , 1);
    tailInset(list1 , 2);
    tailInset(list1 , 3);
    tailInset(list1 , 4);
    pthread_t tid;
    pthread_create(&tid,NULL ,  threadFunc , list1);
    sleep(1);  

}

#endif 
#if 0
void * threadFunc2(void *arg){
    int * pfd = (int *)arg;

    sleep(1);
    char buf[1024] = {0};
    lseek(*pfd , 0 , SEEK_SET);
    read(*pfd , buf,1024); // 共享同一个文件对象 ， 就是共享了偏移
    printf("I am child %s \n", buf);
    return NULL;
 }

void pthreadOpenFileTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;

    int fd = open(argv[1] , O_RDWR);
    errorEqualCheck(fd , -1,"open");

    pthread_t tid;
    pthread_create(&tid ,NULL , threadFunc2,&fd);

    write(fd , "hello",5);
    sleep(2);

}
void * threadFunc3(void *arg){
    
    pthread_exit((void*)123);
    //return (void*)5;
 }
void pthreadJoinTest(){
    pthread_t tid;
    pthread_create(& tid , NULL , threadFunc3, NULL);

    void * retval; 
    pthread_join(tid, &retval);


    printf("%ld \n", (long)retval);

}
#endif
#if 0
void * threadFunc4(void *arg){
    int cnt = 20;
    while(cnt --){
        //printf(" i still alive \n");
        ;
    }
    sleep(1);
    pthread_exit((void*)123);
    //return (void*)5;
 }
void pthreadCancelTest(){
    pthread_t tid;
    pthread_create(& tid , NULL , threadFunc4, NULL);

    pthread_cancel(tid);
    void * retval; 
    pthread_join(tid, &retval);
    printf("%ld \n", (long)retval);

}
#endif
#if 0
void freepint(void *arg){
    printf("free \n");
    free((int*)arg);
}
void closefd(void *arg){
    printf("close  fd \n");
    int * p = (int *)arg;
    close(*p);
}

void * threadFunc5(void *arg) {
    int * p1 = (int*)malloc(4);
    pthread_cleanup_push(freepint,p1);
    int * p2 = (int*)malloc(4);
    pthread_cleanup_push(freepint,p2);

    int  fd3 = open("file1",O_RDWR);
    pthread_cleanup_push(closefd,&fd3);

    pthread_cleanup_pop(1);  //弹出之后直接清理
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
    return NULL;
 }


void pthreadCleanTest(){
    pthread_t tid;
    pthread_create(&tid , NULL , threadFunc5, NULL);
    pthread_join(tid, NULL);
}

#endif

#if 0 

typedef struct shareRes_s{
    int val;
    pthread_mutex_t mutex;
} shareRes_t;

int NUM = 100000000;
void * threadFunc1(void *arg) {
    shareRes_t *pshareRes = (shareRes_t*)arg;
    for(int i = 0;i<NUM ;++i){
        pthread_mutex_lock(&pshareRes->mutex);
            pshareRes->val ++;
        pthread_mutex_unlock(&pshareRes->mutex);
       
    }
    pthread_exit(NULL);
   
}
void raceConditionTest(){
    shareRes_t shareRes;
    //memset(&val , 0,sizeof(val));
    shareRes.val = 0;

    struct timeval beginTime , endTime;

    pthread_mutex_init(&shareRes.mutex , NULL);
    pthread_t tid;
    gettimeofday(&beginTime , NULL);
    pthread_create(&tid,NULL,threadFunc1 , &shareRes );
    for(int i = 0;i<NUM ;++i){
        pthread_mutex_lock(&shareRes.mutex);
        shareRes.val ++;
        pthread_mutex_unlock(&shareRes.mutex);
    }
    

    pthread_join(tid,NULL);
    printf("%d total time = %ld us \n",shareRes.val ,
         (endTime.tv_sec-beginTime.tv_sec)*1000*1000 +
         endTime.tv_usec -beginTime.tv_usec);
}

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void * threadFunc2(void *arg) {
    pthread_mutex_lock(&mutex);
    pthread_exit(NULL);
   
}
void deadLockTest(){

    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc2 , NULL );
    sleep(1);
   
    pthread_mutex_lock(&mutex);
    
    printf("unlock\n");
    pthread_mutex_unlock(&mutex);

    pthread_join(tid,NULL);
  
}


// void * threadFunc3(void *arg) {
//     pthread_mutex_lock(&mutex);
//     pthread_exit(NULL);
   
// }
void tryLockTest(){

    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  
    int ret = pthread_mutex_trylock(&mutex);
    pthreadErrorCheck(ret ,0,"frist");
  

    ret = pthread_mutex_trylock(&mutex);
    pthreadErrorCheck(ret ,0,"second");  // 不等于 0 ，报错

    pthread_mutex_unlock(&mutex);
}

// void * threadFunc3(void *arg) {
//     pthread_mutex_lock(&mutex);
//     pthread_exit(NULL);
   
// }
void errorLockTest(){

    pthread_mutex_t mutex ;
    pthread_mutexattr_t mutexattr; //锁属性类型
    pthread_mutexattr_init(&mutexattr); //初始化 锁属性
    pthread_mutexattr_settype(&mutexattr ,PTHREAD_MUTEX_ERRORCHECK ); //设置锁属性

    pthread_mutex_init(&mutex , &mutexattr); //mutex 检错类型的互斥锁

    int ret = pthread_mutex_lock(&mutex);
    pthreadErrorCheck(ret ,0,"frist");
  

    ret = pthread_mutex_lock(&mutex);
    pthreadErrorCheck(ret ,0,"second");  // 不等于 0 ，报错

    pthread_mutex_unlock(&mutex);
}



#endif

#if 0 

pthread_mutex_t mutex ;
void * threadFunc1(void *arg) {
    //pthread_mutex_t * pmutex = (pthread_mutex_t*)arg;
    pthread_mutex_lock(&mutex);
    pthread_exit(NULL);
   
}
void errorLockTest(){    // 测试别人锁的

   

    pthread_mutexattr_t mutexattr; //锁属性类型
    pthread_mutexattr_init(&mutexattr); //初始化 锁属性
    pthread_mutexattr_settype(&mutexattr ,PTHREAD_MUTEX_ERRORCHECK ); //设置锁属性
    pthread_mutex_init(&mutex , &mutexattr); //mutex 检错类型的互斥锁


    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc1 , &mutex );
    sleep(1);


    int ret = pthread_mutex_lock(&mutex);
    pthreadErrorCheck(ret ,0,"frist");
  
    ret = pthread_mutex_lock(&mutex);
    pthreadErrorCheck(ret ,0,"second");  // 不等于 0 ，报错

    pthread_mutex_unlock(&mutex);
}
#endif
#if 0 //while(1) 实现同步
typedef struct {
    int flag ;
    pthread_mutex_t mutex;
}shareRes_t;

void A(){
    printf("before A\n");

    sleep(1);

    printf("after A \n");
}
void B(){
    printf("before B\n");

    sleep(1);

    printf("after B \n");
}
//int flag = 0; // 0 : A未完成 1：A已经完成 
void * threadFunc(void *arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->flag == 1){
            pthread_mutex_unlock(&pshareRes->mutex);
            break; 
        }
        pthread_mutex_unlock(&pshareRes->mutex);
    }
    B();
    pthread_exit(NULL);
}

void syncTest(){
    shareRes_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex , NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc , &shareRes);
    sleep(2);
    A();
    pthread_mutex_lock(&shareRes.mutex);
    shareRes.flag = 1;
    pthread_mutex_unlock(&shareRes.mutex);
    pthread_join(tid, NULL);
}
#endif
#if 0 //condition variable 实现同步
typedef struct {
    int flag ;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;

void A(){
    printf("before A\n");

    sleep(1);

    printf("after A \n");
}
void B(){
    printf("before B\n");

    sleep(1);

    printf("after B \n");
}
//int flag = 0; // 0 : A未完成 1：A已经完成 
void * threadFunc(void *arg){
    //sleep(4);
    shareRes_t * pshareRes = (shareRes_t*)arg;
   
    pthread_mutex_lock(&pshareRes->mutex);
    if(pshareRes->flag == 0){  // 没做完 ， 等待
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pthread_mutex_unlock(&pshareRes->mutex); // 要保证有没有进if ,锁都要被解开
    
    B();
    pthread_exit(NULL);
}

void syncTest(){
    shareRes_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex , NULL);
    pthread_cond_init(&shareRes.cond,NULL);
    pthread_t tid;
    pthread_create(&tid, NULL, threadFunc , &shareRes);
    //sleep(2);
    A();
    pthread_mutex_lock(&shareRes.mutex);
    shareRes.flag = 1;
    pthread_cond_signal(&shareRes.cond);
    pthread_mutex_unlock(&shareRes.mutex);
    pthread_join(tid, NULL);
}
#endif


#if 0 
typedef struct {
    int ticket  ;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;
// void* sellWindow1(void *arg){
//     shareRes_t * pshareRes = (shareRes_t*)arg;
//     while(pshareRes->ticket > 0){
//         pthread_mutex_lock(&pshareRes->mutex);
//         printf("before window1 ---- %d \n" , pshareRes->ticket);
//         --pshareRes->ticket;
//         printf("after window1 ---- %d \n" , pshareRes->ticket);
//         pthread_mutex_unlock(&pshareRes->mutex);
//     }
//     pthread_exit(NULL);
// }
// void* sellWindow2(void * arg){
//     shareRes_t * pshareRes = (shareRes_t*)arg;
//     while(pshareRes->ticket > 0){  //读资源也要加锁
//         pthread_mutex_lock(&pshareRes->mutex);
//         printf("before window2 ---- %d \n" , pshareRes->ticket);
//         --pshareRes->ticket;
//         printf("after window2 ---- %d \n" , pshareRes->ticket);
//         pthread_mutex_unlock(&pshareRes->mutex);
//     }
//     pthread_exit(NULL);
// }
void* sellWindow1(void *arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    while(1){
        
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->ticket <= 0){
            pthread_mutex_unlock(&pshareRes->mutex);
            break;
        }  
        printf("before window1 ---- %d \n" , pshareRes->ticket);
        --pshareRes->ticket;
        printf("after window1 ---- %d \n" , pshareRes->ticket);
        if(pshareRes->ticket <= 10){
            pthread_cond_signal(&pshareRes->cond);
        }
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(1);
    }
   // sleep(1);
    pthread_exit(NULL);
}
void* sellWindow2(void * arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        if(pshareRes->ticket <= 0){
            pthread_mutex_unlock(&pshareRes->mutex);
            break;
        }
        printf("before window2 ---- %d \n" , pshareRes->ticket);
        --pshareRes->ticket;
        printf("after window2 ---- %d \n" , pshareRes->ticket);
        if(pshareRes->ticket <= 10){
            pthread_cond_signal(&pshareRes->cond);
        }
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(1);
    }
    
    pthread_exit(NULL);
}

void * addwindow(void * arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    if(pshareRes->ticket >  10){  //wait 只会执行一次 => 只加一次 ， 线程就终止了
        pthread_cond_wait(&pshareRes->cond,&pshareRes->mutex);
    }
    pshareRes->ticket += 10;
    pthread_mutex_unlock(&pshareRes->mutex); // 要保证有没有进if ,锁都要被解开 ， 这步之前一定是加锁的
    //进入if 解的是wait上的锁 ， 没进if 解的是上面的锁
    pthread_exit(NULL);
}

void sellTickTest(){
    shareRes_t shareRes;
    shareRes.ticket = 20;
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond,NULL);
    pthread_t tid1 ,tid2 , tid3;
    pthread_create(&tid1, NULL , sellWindow1 , &shareRes);
    pthread_create(&tid2, NULL , sellWindow2 , &shareRes);
    pthread_create(&tid3, NULL , addwindow , &shareRes);



    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

}

void timedwaitTest(){
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    
    struct timeval now;
    gettimeofday(&now,NULL);
    printf("%ld %ld  \n",now.tv_sec , now.tv_usec);
    pthread_mutex_lock(&mutex);
    struct timespec abstime;
    abstime.tv_sec = now.tv_sec +5;
    abstime.tv_nsec = 0;

    pthread_cond_timedwait(& cond,&mutex,&abstime);
    gettimeofday(&now,NULL);
    printf("%ld %ld  \n",now.tv_sec , now.tv_usec);
    

}
#endif
#if 0
typedef struct {
    int flag  ; // 0 没有 ， 1 牛肉 ， 2 酸菜
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;

void *classmate1(void * arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag != 1){
        printf("1 is not ready\n");
        pthread_cond_wait(&pshareRes->cond , &pshareRes->mutex);

    }
    pshareRes->flag = 0; //吃面
    printf("I got 1\n");
    pthread_mutex_unlock(&pshareRes->mutex);
    pthread_exit(NULL);
}
void *classmate2(void * arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag != 2){
        printf("2 is not ready\n");
        pthread_cond_wait(&pshareRes->cond , &pshareRes->mutex);

    }
    pshareRes->flag = 0; //吃面
    printf("I got 2\n");
    pthread_mutex_unlock(&pshareRes->mutex);
    pthread_exit(NULL);
}
void broadcastTest(){
    shareRes_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond,NULL);

    pthread_t tid1 ,tid2;
    pthread_create(&tid1,NULL ,classmate1 , &shareRes);
    pthread_create(&tid2,NULL ,classmate2 , &shareRes);

    while(1){
        int i=0;
        scanf("%d", &i);
        printf(" I priductor %d \n",i);  
        pthread_mutex_lock(&shareRes.mutex);
        shareRes.flag = i;
        pthread_cond_broadcast(&shareRes.cond);
        pthread_mutex_unlock(&shareRes.mutex);
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);

}
void * threadFunc(void *){
    pthread_exit(NULL);
}
void detachstateTest(){
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr , PTHREAD_CREATE_DETACHED); //不能别join
    pthread_t tid;
    //pthread_create(&tid, &attr, threadFunc,NULL);
    pthread_create(&tid, NULL, threadFunc,NULL);

    int ret = pthread_join(tid,NULL);
    threadErrorCheck(ret , 0,"pthread_join");
}
#endif 
#if 0 
void * threadFunc(void *){
    time_t now = time(NULL);
    char *p ;
    char buf[1024] = {0};
    p = ctime_r(&now, buf);
    printf("threadFunc before %s \n", p);

    sleep(5);
    printf("threadFunc after %s \n", p);
    pthread_exit(NULL);
}

void threadSafeTest(){
    pthread_t tid;
    pthread_create(&tid ,NULL, threadFunc,NULL);
    sleep(2);
    time_t now = time(NULL);
    char *p;
    char buf[1024] = {0};
    p = ctime_r(&now,buf);
    printf("before %s \n", p);
    pthread_join(tid,NULL);
}
#endif

#if 0  //ABC问题
typedef struct {
    int flag ; // 0 A 未完成 ， 1  A完成 B未完成， 2 B完成
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t;
void A(){
    printf("before A\n");

    sleep(1);

    printf("after A \n");
}
void B(){
    printf("before B\n");

    sleep(1);

    printf("after B \n");
}
void C(){
    printf("before C\n");

    sleep(1);

    printf("after C \n");
}
void *threadFunc(void * arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    pthread_mutex_lock(&pshareRes->mutex);
    while(pshareRes->flag != 1){
        pthread_cond_wait(&pshareRes->cond , &pshareRes->mutex);
    }
    pthread_mutex_unlock(&pshareRes->mutex);

    B();

    pthread_mutex_lock(&pshareRes->mutex);
    pshareRes->flag = 2; //吃面
    pthread_cond_signal(&pshareRes->cond);
    pthread_mutex_unlock(&pshareRes->mutex);

    pthread_exit(NULL);
}
void ABCTest(){
    shareRes_t shareRes;
    shareRes.flag = 0;
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond,NULL);

    pthread_t tid1 ;
    pthread_create(&tid1,NULL ,threadFunc , &shareRes);
    
    A();
    pthread_mutex_lock(&shareRes.mutex);
    shareRes.flag = 1;
    pthread_cond_signal(&shareRes.cond);
    pthread_mutex_unlock(&shareRes.mutex);


    pthread_mutex_lock(&shareRes.mutex);
    while(shareRes.flag != 2){
        pthread_cond_wait(&shareRes.cond , &shareRes.mutex);
    } 
    pthread_mutex_unlock(&shareRes.mutex);
    C(); //吃面
   

    pthread_join(tid1,NULL);

}
#endif
#include<queue>
typedef struct {

    std::queue<int>que; //队列共享资源
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shareRes_t; 
void * producer1(void * arg){   // 每一种线程做的事情都一样的
    shareRes_t * pshareRes = (shareRes_t*)arg;
    //sleep(5);
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        while(pshareRes->que.size() >= 10){   //超过10个不能生产
            pthread_cond_wait(&pshareRes->cond , &pshareRes->mutex);
        }
        int data = rand()%1000; //走到这里说明可以生产了
        pshareRes->que.push(data);  
        printf("生产 : data = %d    %d \n",data ,pshareRes->que.size() );

        pthread_cond_broadcast(&pshareRes->cond); //唤醒别人
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(3);
    }
}
void * comsumer1(void * arg){
    shareRes_t * pshareRes = (shareRes_t*)arg;
    sleep(5);
    while(1){
        pthread_mutex_lock(&pshareRes->mutex);
        while(pshareRes->que.size() <= 0){   //超过10个不能生产
            pthread_cond_wait(&pshareRes->cond , &pshareRes->mutex);
        }
        int data = pshareRes->que.front(); //走到这里说明可以生产了
        pshareRes->que.pop();  
        printf("消费 : data = %d    %d \n",data,pshareRes->que.size());

        pthread_cond_broadcast(&pshareRes->cond); //唤醒别人
        pthread_mutex_unlock(&pshareRes->mutex);
        sleep(1);
    }
 
  
}
void producerComsumerTest(){
    shareRes_t shareRes; //对列不用初始化
    pthread_mutex_init(&shareRes.mutex, NULL);
    pthread_cond_init(&shareRes.cond,NULL);


    for(int i =0;i< 8;++i){
        shareRes.que.push(rand()%1000);
    }
    //printf("---------------------\n");

    pthread_t tid1, tid2,tid3 ,tid4 ,tid5   ;
    pthread_create(&tid1,NULL ,producer1 , &shareRes);
    pthread_create(&tid2,NULL ,producer1 , &shareRes);
    pthread_create(&tid3,NULL ,producer1 , &shareRes);

    pthread_create(&tid4,NULL ,comsumer1 , &shareRes);
    pthread_create(&tid5,NULL ,comsumer1 , &shareRes);
   

    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    pthread_join(tid5,NULL);

}

//生产-消费问题
#if 1 




#endif 
int main(int argc , char* argv[]){
// #ifdef DEBUG
//     argsCheck(argc , 3) ;
// #endif

producerComsumerTest(); 
    
    return 0;
       
}