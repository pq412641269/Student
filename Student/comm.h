#ifndef COMM_H
#define COMM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"      //学生链表
#include "student.h"    //学生函数头文件
#include "menu.h"       //菜单函数头文件


#define SYSERR(X,OPTION,Y,K,Z) if((X)OPTION(Y))\
                                {\
                                    printf("%s:%s:%d:%s\n",__FILE__,__func__,__LINE__,(K));\
                                    return Z;\
                                }
//安全检查宏

#define ADMINNAME "admin"   //管理员用户名
#define ADMINPASS "admin"   //管理员密码
    
#define STUFILE "student.dat" //学生数据存储文件


#define LOOPCOUNT 3         //管理员密码


int mark;       //定义一个全局变变量判断文件是否改动

#endif

