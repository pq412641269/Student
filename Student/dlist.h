#ifndef DLIST_H
#define DLIST_H

#include "comm.h"

typedef struct node
{
    struct node *next,*prev;
    void *data;
}node_t;  //创建链表

/************************                                             
 描述：初始化双向循环链表
 参数：无
 返回值：返回已经初始化好的链表
************************/
node_t *node_init(void); //链表初始化

/************************
 描述：将数据插入链表头部
 参数：head:需要插入的链表 data：需要插入的数据 size插入数据的大小
 返回值：成功返回 0 失败返回 -1
************************/
int inser_head(node_t *head,const void *data,int size); //头删
//显示数据
typedef void(*showfun_t)(const void *data); //显示函数指针

/************************
 描述：打印链表
 参数：head:需要显示的链表 showfun 显示函数指针
 返回值：成功返回 0 失败返回 -1
************************/
int node_show(node_t *head,showfun_t showfun); //显示函数

/************************
 描述：打印数据
 参数：data：需要打印的数据
 返回值：无
************************/
void show_all(const void *data); //打印学生信息
//查找
typedef int(*cmpfun_t)(const void *,const void *);  //比较函数指针

/************************
 描述：将数据插入链表头部
 参数：head:需要插入的链表 data：需要插入的数据 cmpfun 比较函数指针，>
 返回值：成功返回 0 失败返回 -1
************************/
node_t *node_find(node_t *head, const void *data,cmpfun_t cmpfuna); //查找函数 

/************************
 描述：查找链表数据并显示
 参数：head:链表 data：需要查找数据的结构体 cmpfun 比较函数指针，用与
 返回值：成功返回 0 失败返回 -1
************************/
int find_show(node_t *head,const void *data,cmpfun_t cmpfun); //查找显示

/************************
 描述：比较函数;
 参数：data1 需要比较数据1 data2 需要比较数据2;
 返回值：相同返回0; data1大于data2 及返回大于0的数;data1小于data2 及>
************************/
int cmp_name(const void *data1,const void *data2);      //姓名比较
int cmp_pass(const void *data1,const void *data2);       //密码比较
int cmp_cid(const void *data1,const void *data2);       //学号比较
int cmp_cid1(const void *data1,const void *data2);       //学号1比较
int cmp_classid(const void *data1,const void *data2);       //班级比较
int cmp_order(const void *data1,const void *data2);       //名次比较
int cmp_gmath(const void *data1,const void *data2);      //数学成绩比较
int cmp_glang(const void *data1,const void *data2);       //c语言成绩比较
int cmp_gphil(const void *data1,const void *data2);      //语文成绩比较
int cmp_gsum(const void *data1,const void *data2);      //总成绩比较
int node_selete_sort(node_t *head,cmpfun_t cmpfun);     //选择排序函数

/************************
 描述：链表选择排序
 参数：head:链表 cmpfun 比较函数
 返回值：成功返回 0 失败返回 -1
************************/
int node_update(node_t *head,const void *olddata,const void *newdata,int size,cmpfun_t cmpfun); //查找修改

/************************
 描述：查找并删除链表里数据
 参数：head:链表 data：需要删除的数据 cmpfun 比较函数
 返回值：成功返回 0 失败返回 -1
************************/
int node_find_del(node_t *head,const void *data,cmpfun_t cmpfun); //查找删除

/************************
 描述：查找并显示链表里相同类型的数据
 参数：head:链表 data：需要删除的数据 cmpfun 比较函数
 返回值：成功返回 0 失败返回 -1
************************/
int find1_show(node_t *head,const void *data,cmpfun_t cmpfun);   //循环打印

/************************
 描述：销毁链表
 参数：head:需要销毁的链表（二级指针）
 返回值：成功返回 0 失败返回 -1
************************/
int node_destory(node_t **head);  //销毁链表


#endif

