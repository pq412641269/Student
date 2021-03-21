#ifndef STUDENT_H
#define STUDENT_H

#include "comm.h"

typedef struct student  //学生结构体定义
{
    int cid;  //学号
    char name[32];  //学生姓名
    char pass[16];  //学生密码
    int age;        //学生年龄
    int gmath;      //学生数学成绩
    int glang;      //学生C语言成绩
    int gphil;      //学生语文成绩
    int gsum;       //学生总分
    int order;      //排序名次
    int classid;    //班级号
}stu_t;

/************************
 描述：添加学生函数
 参数：链表
 返回值：成功返回 0 失败返回 -1
************************/
int addstu(node_t *head); //添加学生

/************************
 描述：按总分排序并排名次
 参数：head:链表  cmpfun 比较函数
 返回值：成功返回 0 失败返回 -1
************************/
int setstuorder(node_t *head,cmpfun_t cmpfun); //设置学生名次排序函数

/************************
 描述：生成学号
 参数：head:链表 cmpfun 比较函数
 返回值：返回一个学号
************************/
int getcid(node_t *head,cmpfun_t cmpfun);  //设置学号

/************************
 描述：加载文件信息到链表
 参数：无
 返回值：返回返回加载好的链表
************************/
node_t *loadstu(void); //读取数据存储文件

/************************
 描述：保存链表信息到文件
 参数：head:链表 
 返回值：成功返回0 失败返回-1
************************/
int savestu(node_t *head);   //链表中的数据存储到文件里

/************************
 描述：计算平均分
 参数：head:链表 flag 1 = 计算数学平均分 2 = 计算c语言平均分 3 = 计算语文平均分
 返回值：返回一个学号
************************/
float aver(node_t *head,int flag);  //计算平均分

#endif






