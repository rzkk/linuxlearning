// #include<iostream>

// using std::cout;
// using std::endl;

#if 0  // 输入重定向

void test1(){
    char buf[1024] = {0};
    
    scanf("%s",buf);
    cout<<buf<<endl;
}
#endif
#if 1
//#include<stdio.h>
#include "add.h"
//#define X 3
//#define ASSIGN(x,y) {x = y;}
#endif



int main(){
    
    printf( "add(2,3)",add(2,3) );
  
    return 0;
}