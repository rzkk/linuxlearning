/*
 * @Author: rzk ruanzk2098@gmial.com
 * @Date: 2025-02-28 19:55:25
 * @LastEditors: rzk ruanzk2098@gmial.com
 * @LastEditTime: 2025-03-01 10:50:33
 * @FilePath: /linux/src/aux_files.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include"func.h"

int ARGS_CHECK(int argc,int num) 
{ 
    if(argc!=num){
        fprintf(stderr,"args error!\n");
        //cerr<<"args error!"<<endl;
        return -1;
    } 
    return 0;
}
int ERROR_CHECK(FILE * ret,FILE * num, char* msg) 
{
    if(ret == num){
        perror(msg);
         return -1;
    }
    return 0;
}

