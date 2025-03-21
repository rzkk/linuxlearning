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


int main(int argc , char* argv[]){

   
   // argsCheck(argc,3);

    //int  a, b ;
    //scanf("%d %d",&a, &b);
   // printf("%d ,%d  ,%d \n",a,b,a+b);
    printf("helkloeword\n");
    return 0;           
}

