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

void test1(int argc , char* argv[]){

    FILE *fp1 = fopen(argv[1],"r+");
    FILE *fp2 = fopen("file2","w+");
    #ifdef DEBUG
    errorCheck(fp1 ,NULL , "fopen");
    #endif

    char buf1[1024] = {0};
    size_t ret = fread(buf1,1,sizeof(buf1),fp1);
    cout<<ret<<endl;
    printf("%s \n", buf1);

    char buf2[1024] = "nihao";
    ret = fwrite(buf2,1,sizeof(buf2),fp2);
    ret = fwrite(buf2,sizeof(buf2),1,fp2);
    ret = fwrite(buf2,strlen(buf2),1,fp2);

    cout<<ret<<endl;
    fclose(fp1);
    fclose(fp2);
}
void test2(int argc , char* argv[]){
    int ret = chmod(argv[1],0777);
    errorCheck(ret ,-1, "chmod");
}
void test3(int argc , char* argv[]){
    
    //char path[1024] = {0};
    char*p = getcwd(NULL , 0);
    //char*p = getcwd(path , sizeof(path));
    errorCheck(p , NULL , "getcwd");
    printf("%s" , p);
}
void test5(int argc , char* argv[]){
    
    //char path[1024] = {0};
   
    printf("before chdir: ");
    char*p = getcwd(NULL , 0);
    printf("%s \n",p);
    //free(p);

    int ret  = chdir(argv[1]);
    errorCheck(ret , -1 , "chdir");

    printf("after chdir: ");
    p = getcwd(NULL , 0);
    printf("%s \n",p);
    //free(p);

    //printf("%s" , p);
}void test4(int argc , char* argv[]){
    
    int ret = mkdir(argv[1],0777);
    errorCheck(ret , -1,"mkdir");
}
// void test6(int argc , char* argv[]){
//     // if(argc != 2){
//     //     std::cerr<<"打开失败"<<endl;
//     // }
// #ifdef DEBGE
//     ARGS_CHECK(argc,2);
// #endif
//     ifstream ifs;
//     ifs.open(argv[1]);
//     //FILE *fp = fopen(argv[1],"r+");
// #ifdef DEBGE
//     if(!ifs)  cout<<"open file failed\n";
//     //ERROR_CHECK(fp,NULL,argv[1]); 
// #endif
    
//     //fread(buf,1,sizeof(buf),fp);
//     ifs.seekg(0,std::ios::end);
//     long length = ifs.tellg();
//     ifs.seekg(0);
//     char*  buf = new char[length+1]();
//     ifs.read(buf,length);
//     //ifs.
//     string str(buf);
//     cout<<length<<endl;
//     printf("aa");
//     printf("%s ", buf);
//     printf("aa\n");
//     cout<<str<<endl;
//     //fclose(fp);
//     ifs.close();
// }
#endif


// #include<vector>
// #include<iterator>
// #include<functional>
// #include<algorithm>
#if 0
int test1(){
    //ARGS_CHECK(argc,2);
    DIR * dirp = opendir("../File");
    if(dirp == NULL){
        printf("error \n");
        return -1;
    }
    //ERROR_CHECK(dirp,NULL,"opendir");
    struct dirent * pdirent;
    long loc;
    while((pdirent = readdir(dirp)) != NULL){
        printf("inode = %ld, reclen = %d, type = %d, name = %s\n",
               pdirent->d_ino, pdirent->d_reclen,
               pdirent->d_type,pdirent->d_name);
        if(strcmp("dir1" , pdirent->d_name) == 0){
            loc = telldir(dirp);
            printf("%ld\n",loc);
        }
        if(strcmp("file1" , pdirent->d_name) == 0){
            loc = telldir(dirp);
            printf("%ld\n",loc);
        }
    }
    
    //seekdir(dirp,loc);
    rewinddir(dirp);
    // The rewinddir() function resets the position of the directory stream dirp to the beginning of the directory.
    pdirent = readdir(dirp);
    printf("inode = %ld, reclen = %d, type = %d, name = %s\n",
        pdirent->d_ino, pdirent->d_reclen,
        pdirent->d_type,pdirent->d_name);
    closedir(dirp);
    return 0;
}

#endif

#if 0   //tree 

void dfs(DIR * dirp){
     if(readdir(dirp) == NULL){
         return;
     }
    struct dirent * pdirent = readdir(dirp);
    if(pdirent->d_type ==  DT_REG ){
        printf("    %s \n" , pdirent->d_name);
    }else {
        dfs((DIR *)(pdirent->d_ino));
    }
}
int  test1(){
    DIR * dirp = opendir("../File");
    if(dirp == NULL){
        printf("error \n");
        return -1;
    }
    struct dirent * pdirent;
    dfs(dirp);

    // while((pdirent = readdir(dirp)) != NULL){
    //     printf("inode = %ld, reclen = %d, type = %d, name = %s\n",
    //            pdirent->d_ino, pdirent->d_reclen,
    //            pdirent->d_type,pdirent->d_name);
        
    // }
    return 0;
}
#endif

#if 0 
int test1(){
    const char * filePathName  = "../File";
    DIR * dirp = opendir(filePathName);
    if(dirp == NULL){
        printf("error \n");
        return -1;
    }
    struct  dirent * pdirent;

    while((pdirent = readdir(dirp)) != NULL){
        // 文件名->路径
        char path[1024] = {0};
        sprintf(path,"%s%s%s",filePathName,"/",pdirent->d_name); //输出到字符串中
        struct stat statbuf; //申请空间
        int ret = stat(path, &statbuf);
        //ERROR_CHECK(ret,-1,"stat");
        if(ret == -1){
            perror("stat");
        }
        printf("%o %ld %d %d %ld %s %s \n", statbuf.st_mode,
                        statbuf.st_nlink,
                        statbuf.st_uid,
                        statbuf.st_gid,
                        statbuf.st_size,
                        ctime(&statbuf.st_mtime),
                        pdirent->d_name);
    }


    return 0;
}
#endif

#if 0   // ls 
void myls1(int argc , char* argv[]){
    DIR * dirp = opendir(argv[1]);
    errorCheck(dirp,NULL,"DIR");
    struct dirent * pdirent;
    long loc;
    while((pdirent = readdir(dirp)) != NULL){
        printf("%ld %d %d  %s \n",  pdirent->d_ino,
                                pdirent->d_reclen,   
                                pdirent->d_type,
                                pdirent->d_name);
        
        if(strcmp("dir1" , pdirent->d_name) == 0){  // C的字符串比较
           loc = telldir(dirp);
        }

        
    }
    printf("---------------------\n");
    //seekdir(dirp,loc); //回到dir1
    rewinddir(dirp); //回到最开头
    pdirent = readdir(dirp);  //再次打印
    printf("%ld %d %d  %s \n",  pdirent->d_ino,
        pdirent->d_reclen,   
        pdirent->d_type,
        pdirent->d_name);
     closedir(dirp);
}
void modeTostring(long st_mode ,char * modestr ){
    switch (st_mode & S_IFMT) {
        //case S_IFBLK:  modestr[0] = ;            break;
        //case S_IFCHR:  printf("character device\n");        break;
        case S_IFDIR:  modestr[0] = 'd';               break;
        //case S_IFIFO:  printf("FIFO/pipe\n");               break;
        case S_IFLNK:  modestr[0] = 'l';              break;
        case S_IFREG:  modestr[0] = '-';            break;
        //case S_IFSOCK: printf("socket\n");                  break;
        default:       modestr[0] = '?';                break;
        }
        int i = 2;
        while(i>=0){
            switch (st_mode & 007) {

            case 0:modestr[i*3+1] = '-';modestr[i*3+2] = '-';modestr[i*3+3] = '-';break;
            case 1:modestr[i*3+1] = '-';modestr[i*3+2] = '-';modestr[i*3+3] = 'x';break;
            case 2:modestr[i*3+1] = '-';modestr[i*3+2] = 'w';modestr[i*3+3] = '-';break;
            case 3:modestr[i*3+1] = '-';modestr[i*3+2] = 'w';modestr[i*3+3] = 'x';break;
            case 4:modestr[i*3+1] = 'r';modestr[i*3+2] = '-';modestr[i*3+3] = '-';break;
            case 5:modestr[i*3+1] = 'r';modestr[i*3+2] = '-';modestr[i*3+3] = 'x';break;
            case 6:modestr[i*3+1] = 'r';modestr[i*3+2] = 'w';modestr[i*3+3] = '-';break;
            case 7:modestr[i*3+1] = 'r';modestr[i*3+2] = 'w';modestr[i*3+3] = 'x';break;
                
            default:modestr[i*3+1] = '-';modestr[i*3+2] = '-';modestr[i*3+3] = '-' ;break;
            }
            st_mode >>= 3;
            i--;
        }
        //return 0;
}
void myls2(int argc , char* argv[]){
    DIR * dirp = opendir(argv[1]);
    errorCheck(dirp,NULL,"DIR");
    struct dirent * pdirent;
    const char *months[12] = {"mar" ,"mar" ,"mar" ,"mar" ,"mar" ,"mar" ,"mar" ,"mar"
        ,"mar" ,"mar" ,"mar" ,"mar"  };
    while((pdirent = readdir(dirp)) != NULL){
        char path[1024] = {0};
        char modestr[11] = {0};
        sprintf(path,"%s%s%s",argv[1],"/",pdirent->d_name);
        struct stat statbuf;
        int ret = stat(path,&statbuf);
        errorCheck(ret , -1,"266:stat");
        //struct passwd *pd = getpwuid(statbuf.st_uid);

        char timebuf[1024] ={0};
        struct tm* t =  localtime(&statbuf.st_mtime);
        sprintf(timebuf ,"%s %d %d%s%d" , months[t->tm_mon],
                                t->tm_mday,
                                t->tm_hour,
                                ":",
                                t->tm_min
                                     );
        //cout<<modeTostring(statbuf.st_mode,modestr)<<endl;;
        modeTostring(statbuf.st_mode,modestr);

        printf("%s %ld %s %s  %4ld %s %s \n", modestr,
                            statbuf.st_nlink,
                            //statbuf.st_uid,
                            getpwuid(statbuf.st_uid)->pw_name,
                            getgrgid(statbuf.st_gid)->gr_name,                           
                            statbuf.st_size, 
                            timebuf,
                            pdirent->d_name
                            ); 
    }
   
    closedir(dirp);
}
#endif
#if 0 
void DFStree(char* dirpath , int depth){
    DIR* pdir = opendir(dirpath);
    errorCheck(pdir ,NULL,"opendir:mytree");
    struct  dirent *pdirent;
    //printf("├─");
    while((pdirent = readdir(pdir)) != NULL){
        if(strcmp(pdirent->d_name ,".") == 0 || strcmp(pdirent->d_name ,"..") == 0 ){
            continue;
        }
        
        for(int i = 0; i<depth;i++){
            printf("-");
        }
        printf("%s \n",pdirent->d_name);
        if(pdirent->d_type == DT_DIR){
            char path[1024] ={0};
            sprintf(path,"%s%s%s",dirpath ,"/",pdirent->d_name );
            DFStree( path , depth +6);
        }
        // if(pdirent->d_type == DT_REG){
        //     continue;
        // }
    }
    closedir(pdir);
}

void mytree(int argc , char* argv[]){

    printf("%s\n",argv[1]);
    DFStree(argv[1],6 );
    
}
#endif

#if 0 //File Object
void test(int argc , char* argv[]){
    int fd = open(argv[1],O_RDWR|O_CREAT,0666);
    errorCheck(fd,-1,"open:test:file.cpp");
    
    char buf[1024] = {0};
    int ret = read(fd, buf,sizeof(buf)); // 指针偏移
    errorCheck(ret , -1,"ret:test:file.cpp");

    memset(buf,0,sizeof(buf));
     ret = read(fd, buf,sizeof(buf)); // 指针偏移
    errorCheck(ret , -1,"ret:test:file.cpp");

    cout<<ret<<endl;
}

void test2(int argc , char* argv[]){

    char buf[1024] = {0};
    int ret = read(0, buf,sizeof(buf)); // 指针偏移
    errorCheck(ret , -1,"ret:test:file.cpp");
    cout<<ret<<"  \n"<<buf<< endl;
}
void test3(int argc , char* argv[]){

    int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666);
    char buf[500] = "helloo";
    cout<<sizeof(buf)<<endl;
    int ret = write(fd, buf,sizeof(buf)); // 指针偏移  确实写入了五百，但是再\0之后的读不到了

    //errorCheck(ret , -1,"ret:test:file.cpp");
    cout<<ret<<endl;
   // ret = write(fd, "how are you",11); 

   // cout<<ret<<"  \n"<<buf<< endl;
}

void test4(int argc , char* argv[]){

    int fd = open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666);
    errorCheck(fd , -1,"open:test4:file.cpp");
    char buf[] = "1000000";
    write(fd, buf,strlen(buf));
    close(fd);
}
void test5(int argc , char* argv[]){
    int fd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    errorCheck(fd , -1,"open:test4:file.cpp");

    int num = 100000;
    write(fd, &num,sizeof(num));

    // int temp;
    // read(fd, &temp, sizeof(temp));
    // cout<<temp<<endl;
    close(fd);
   
}
void test6(int argc , char* argv[]){
    int fd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    errorCheck(fd , -1,"open:test4:file.cpp");
    int temp;
    read(fd, &temp, sizeof(temp));
    cout<<temp<<endl;
    close(fd);
}
#endif
#if 0 
void mycopy(int argc , char* argv[]){
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(fdr,-1,"open");
    int fdw = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0666);
    errorCheck(fdr,-1,"open");
    
    char buf[4096] = {0};
    int ret ;
    while( ( ret = read(fdr,buf , sizeof(buf)) ) != 0) {
        write(fdw,buf,ret);
        memset(buf,0,sizeof(buf));
    }
    close(fdr);
    close(fdw);
}
void compTest(int argc , char* argv[]){
    int fd1 = open(argv[1],O_RDONLY);
    errorCheck(fd1,-1,"open");
    int fd2 = open(argv[2],O_RDONLY);
    errorCheck(fd2,-1,"open");
    
    char buf1[4096] = {0};
    char buf2[4096] = {0};
    int ret1,ret2 ;
    while(1) {
        memset(buf1,0,sizeof(buf1));
        memset(buf2,0,sizeof(buf2));
        ret1= read(fd1,buf1 , sizeof(buf1));
        ret2= read(fd2,buf2 , sizeof(buf2));
        if(ret1 - ret2 != 0){
            cout<<"长度不相同\n";
            break;
        }
        if(memcmp(buf1,buf2,ret1) != 0){
            cout<<"内容不相同\n";
            break;
        }
        if(ret1 == 0){
            cout<<"相同\n"<<endl;
            break;
        }
    }
    close(fd1);
    close(fd2);
}
#endif

#if 0
void ftruncateTest(int argc , char* argv[]){
#ifdef DEBUG
    argsCheck(argc , 2) ;
#endif
    int fd = open(argv[1],O_RDWR);
    errorCheck(fd,-1,"open");

    int ret = ftruncate(fd,40960);
    errorCheck(ret ,-1, "ftruncate");

    close(fd);
}
void mmapTest(int argc , char* argv[]){
#ifdef DEBUG
    argsCheck(argc , 2) ;
#endif
    int fd = open(argv[1],O_RDWR);
    errorCheck(fd , -1 ,"open");

    int ret = ftruncate(fd, 10);
    errorCheck(ret , -1, "ftrunctae");
    
    char * p = (char*)mmap(NULL ,10,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0 );
    errorCheck(p,MAP_FAILED,"mmap");

    for(int i =0;i<10;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;
    p[5000] = 'V';
    for(int i =0;i<120;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;
    cout<<sizeof(p)<<endl;
    munmap(p,10);
    close(fd);
}
void lseekTest(int argc , char* argv[]){
#ifdef DEBUG
    argsCheck(argc , 2) ;
#endif
    int fd = open(argv[1],O_RDWR);
    errorCheck(fd , -1 ,"open");

    char ch ;
    while(1){
        ssize_t ret = read(fd, &ch,1);  //读了之后就会往后偏移
        if(ret == 0) break;

        if(ch >= 'a' && ch <= 'z'){
            ch -= 32;
            lseek(fd,-1, SEEK_CUR);
            write(fd,&ch,1);
        }
    }
}
void filenoTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    FILE * fp = fopen(argv[1], "r+");
    errorCheck(fp , NULL , "fopen");

    //write(3,"hello",5);
    write(fileno(fp),"word",5);
    fclose(fp);
}
void redirectTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;

    printf("see me\n"); 
    //close之前先打印换行
    close(STDOUT_FILENO);

    int fd  = open(argv[1], O_RDWR);
    errorCheck(fd , -1 , "fopen");
    cout<<fd<<endl;  // cout 也被重定向了
    printf("fd = %d \n",fd); 
    printf("can not see me\n"); 
    close(fd);
}
void dupTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;

    int oldfd  = open(argv[1], O_RDWR);
    errorCheck(oldfd , -1 , "fopen");
    cout<<oldfd<<endl;

    int newfd = dup(oldfd);
    cout<<newfd<<endl;

    write(oldfd,"hello ", 5);
    write(newfd,"world",5);

    close(oldfd);
    write(newfd,"nihao",5);

}
void dupRedrientTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;

    // int fd1  = open(argv[1], O_RDWR);
    // errorCheck(fd1 , -1 , "fopen");
    // printf("\n");
    // close(STDOUT_FILENO);

    // int fd2 = dup(fd1);  //找到最小的 ， 可用的  1
    // cout<<fd2<<endl;     // => 1

    // printf("you can not see me \n");

    int fd  = open(argv[1], O_RDWR);  // 3 
    errorCheck(fd , -1 , "fopen");
    printf("see me 1\n");
    
    dup2(STDOUT_FILENO, 10);  //先备份一下 1 , 10 指向输出设备
    dup2(fd , STDOUT_FILENO);  //3 , 1 指向磁盘空间
    printf("see me 2\n");

    dup2(10 , STDOUT_FILENO);  // 10 , 1 指向输出设备
    printf("see me 3\n");
    close(3);
}
#endif
#if 1

void openPipeTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    printf("read open\n");

    char buf[1024] = {0};
    ssize_t sret = read(fdr,buf,sizeof(buf));
    printf("%ld   %s\n",sret ,buf);
}
void closePipeTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    printf("read close\n");
    close(fdr);
    //char buf[1024] = {0};
    //ssize_t sret = read(fdr,buf,sizeof(buf));

    //printf("zuizuih    %ld   %s\n",sret ,buf);
    close(fdr);
}
void doublePipeTest(int argc , char* argv[]){
    argsCheck(argc , 3) ;
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");

    int fdw = open(argv[2],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");

    printf("file connected\n");
    close(fdr);
}
#endif
#if 0  ////stuent 类型写入文件，从文件读
typedef struct {
    int num;
    char nume[30];  //优先使用数组
    float score;
}stuent_t;

void stuentTTest(int argc , char* argv[]){
    argsCheck(argc , 2) ;
    int fd = open(argv[1],O_RDWR);
    errorCheck(-1,fd,"pipe open");

    stuent_t stu[3] = {{1,"xiaoli", 77} ,
                        {2,"xiao1iang", 88} ,
                        {3,"xiaowang", 99} };
    
    write(fd, stu , sizeof(stu));

    stuent_t buf[3];
    lseek(fd , 0, SEEK_SET);
    read(fd, buf , sizeof(stu));
    for(int i = 0; i< 3;i++){
        cout<<buf[i].num<<" "<<buf[i].nume<<" "<<buf[i].score<<endl;
    }
    close(fd);
}
#endif 
#if 0  //聊天

void talkTest1(int argc , char* argv[]){
    argsCheck(argc , 3) ;
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    int fdw = open(argv[2],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
  
    printf("azhen con nec ted\n");
   
    printf("00 azhen : \n"); 
    char buf[4096] = {0};
    while(1){
        //读stdin
        memset(buf,0,sizeof(buf));
        int ret =  read(STDIN_FILENO,buf,sizeof(buf));
        write(fdw,buf,ret);
        //读aqiang 
        memset(buf,0,sizeof(buf));
        read(fdr,buf,sizeof(buf));
        printf("buf : %s \n",buf);
    
    }

    close(fdr);close(fdw);
}
void talkTest2(int argc , char* argv[]){
    argsCheck(argc , 3) ;
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    int fdw = open(argv[2],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
    printf("azhen connected\n");

    char buf[4096] = {0};
    fd_set rdset;
    struct timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;  //不能省略
    while(1){
        FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);       // pipe 的读端 和stdin 加入监听
       
        int ret = select(fdr+1 , &rdset , NULL ,NULL ,&timeout);
        if(ret == 0){
            time_t now = time(NULL); //获取当前时间
            printf("aqiang超时了 , %s \n", ctime(&now));//转日历时间
            break;
        }
        if(FD_ISSET(fdr,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret = read(fdr,buf,sizeof(buf)); //aqiang 来了
            if(ret == 0){
                printf("对方关闭\n");
                break;
            }    
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;  //不能省略
            time_t now = time(NULL); 
            printf("buf : %s   %s\n",buf,ctime(&now));
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){  //ctrl + D : 发一个终止符 EOF 
                //printf("对方关闭\n");
                write(fdw,"nishigehaoren",13);
                break; 
            }    
            write(fdw,buf,ret);
        }
    }

    close(fdr);close(fdw);
}
void talkTest3(int argc , char* argv[]){
    argsCheck(argc , 3) ;
    int fdr = open(argv[1],O_RDONLY);
    errorCheck(-1,fdr,"pipe open");
    int fdw = open(argv[2],O_WRONLY);
    errorCheck(-1,fdw,"pipe open");
    printf("azhen connected\n");

    char buf[4096] = {0};
    fd_set rdset;
    struct timeval timeout;
    time_t aqianglast = time(NULL);
    while(1){
        FD_ZERO(&rdset);            //每次监听开始都要重置监听集合
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(fdr, &rdset);       // pipe 的读端 和stdin 加入监听
        timeout.tv_sec = 1;
        timeout.tv_usec = 0;  //不能省略
        int ret = select(fdr+1 , &rdset , NULL ,NULL ,&timeout);
        
        time_t now = time(NULL); //获取当前时间
        
        if(difftime(now , aqianglast ) >10 ){
            printf("aqiang超时了 , %s \n", ctime(&now));//转日历时间
            break;
        }
        if(ret == 0) continue;

        if(FD_ISSET(fdr,&rdset)){      //aqiang 来了
            memset(buf,0,sizeof(buf));
            int ret = read(fdr,buf,sizeof(buf));
            if(ret == 0){
                printf("对方关闭\n");
                break;
            }    
            aqianglast = now;
            printf("buf : %s   %s\n",buf,ctime(&now));
        }
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            memset(buf,0,sizeof(buf));
            int ret =  read(STDIN_FILENO,buf,sizeof(buf));
            if(ret == 0){  //ctrl + D : 发一个终止符 EOF 
                //printf("对方关闭\n");
                write(fdw,"nishigehaoren",13);
                break; 
            }    
            write(fdw,buf,ret);
        }
    }

    close(fdr);close(fdw);
}
#endif 

#if 0 
void blockwriteTest(int argc , char* argv[]){
    // #ifdef DEBUG
    argsCheck(argc , 2) ;
    int fd = open(argv[1],O_RDONLY);
    errorCheck(-1,fd,"pipe open");
    printf("connected\n");

    char buf[4096];
    sleep(30);

    while(1){
        read(fd , buf , 4096);
        printf("read one\n");
        sleep(2);
    }
    
    close(fd);
}
#endif

#if 0 
void blockselectTest(int argc , char* argv[]){
    // #ifdef DEBUG
    argsCheck(argc , 2) ;
    int fd1 = open(argv[1],O_RDWR);
    errorCheck(-1,fd1,"pipe open");

    int fd2 = open(argv[1],O_RDWR);
    errorCheck(-1,fd2,"pipe open");

    printf("pipe open \n");

    fd_set rdset ;
    fd_set wrset ;
    int cnt = 0;
    char buf[4096] = {0};

    while(1){
        FD_ZERO(&rdset); 
        FD_ZERO(&wrset);             
        FD_SET(fd1, &rdset);
        FD_SET(fd2, &wrset);       // pipe 的读端 和stdin 加入监听
        sleep(1);
        int ret = select(fd2+1 , &rdset , &wrset ,NULL ,NULL);
        
        if(FD_ISSET(fd1,&rdset)){
           
            read(fd1,buf,2048); //aqiang 来了
           
            printf("read ready cnt = %d   ret =  %d \n",cnt++ ,ret);
        }
        if(FD_ISSET(fd2,&wrset)){

            printf("write ready cnt = %d   ret =  %d \n",cnt++ ,ret);

            write(fd2,buf,4096);
        }
    }
}
#endif
#if 1
void  


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
    blockselectTest(argc ,argv );

    return 0;           
}

