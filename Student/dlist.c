#include "comm.h"


node_t *node_init(void) //链表初始化
{
    node_t *head = malloc(sizeof(node_t)); //创建链表空间
    //安全检查
    SYSERR(head,==,NULL,"maloc err",NULL);
    head->data = NULL;
    head->prev = head;  
    head->next = head;  
    return head;
}


int inser_head(node_t *head,const void *data,int size) //头插
{
    //安全检查
    SYSERR(head,==,NULL,"head is NULL",-1);
    SYSERR(data,==,NULL,"data is NULL",-1);
    SYSERR(size,<,1,"size nust >= 1 ",-1);
    
    //创建新的节点
    node_t *p = malloc(sizeof(node_t));
    SYSERR(p,==,NULL,"*p malloc err",-1);   //新建节点安全检查
    
    p->data = malloc(size);    //数据存储空间创建
    if(p->data == NULL)     //安全检查
    {   
        free(p);        //没有创建成功就释放空间
        printf("p->data malloc data err\n");
        return -1;
    }

    //数据拷贝
    memcpy(p->data,data,size);
    //更改指针指向
    p->next = head->next;
    p->prev = head;
    head->next = p;
    p->next->prev = p;
    return 0;
}


int node_show(node_t *head,showfun_t showfun)  //显示函数
{
    //安区检查
    SYSERR(head,==,NULL,"haed is NULL",-1);
    SYSERR(head->next,==,head,"haed is empty",-1);
    
    node_t *p = head->next; //创建指向下一级的执政
    while(p != head)
    {
        showfun(p->data);  //打印数据
        p = p->next; //指针指向下一级
    }
    return 0;
}


void show_all(const void *data) //打印学生信息
{
    const stu_t *stu1 = data;
    printf("\t\t%2d%10s%8d%8d%8d%8d%8d%8d%8d\n",stu1->cid,stu1->name,stu1->age,stu1->classid,stu1->gmath,stu1->glang,stu1->gphil,stu1->gsum,stu1->order);
    //打印学生：学号 姓名 年龄 班级 数学 C语言 语文 总分 名次
}


node_t *node_find(node_t *head, const void *data,cmpfun_t cmpfun) // 查找
{
    //安全检查
    SYSERR(head,==,NULL,"head is NULL",NULL);
    SYSERR(head->next,==,head,"haed is empty",NULL);
    SYSERR(data,==,NULL,"head is NULL",NULL);
    //创建一个节点
    node_t *p = head->next;
    
    while(p != head && p->data != NULL)
    {
        if(cmpfun(data,p->data) == 0)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}


int cmp_cid(const void *data1,const void *data2)       //学号比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu2->cid - stu1->cid;
}


int cmp_cid1(const void *data1,const void *data2)       //学号比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu1->cid - stu2->cid;
}


int cmp_name(const void *data1,const void *data2)      //姓名比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return strcmp(stu1->name,stu2->name);
}


int cmp_pass(const void *data1,const void *data2)       //密码比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return strcmp(stu1->pass,stu2->pass);
}


int cmp_classid(const void *data1,const void *data2)       //班级比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu1->classid - stu2->classid;
}


int cmp_order(const void *data1,const void *data2)       //名次比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu1->order - stu2->order;
}


int cmp_gmath(const void *data1,const void *data2)       //数学成绩比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu2->gmath - stu1->gmath;
}


int cmp_glang(const void *data1,const void *data2)       //c语言成绩比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu2->glang - stu1->glang;
}


int cmp_gphil(const void *data1,const void *data2)       //语文成绩比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu2->gphil - stu1->gphil;
}


int cmp_gsum(const void *data1,const void *data2)       //总成绩比较
{
    const stu_t *stu1 = data1;
    const stu_t *stu2 = data2;
    return stu2->gsum - stu1->gsum;
}


int node_selete_sort(node_t *head,cmpfun_t cmpfun)     //选择排序函数
{
    //安全检查
    SYSERR(head,==,NULL,"head is NULL",-1);
    SYSERR(head->next,==,head,"haed is empty",-1);
    node_t *i,*j,*min;  
    void *temp; //排序中间容器
    
    for(i = head->next; i->next != head; i = i->next)
    {
        min = i;
        for(j = i->next; j != head; j = j->next)
        {
            //遍历后面数值找到更小的值
            if(cmpfun(min->data,j->data) > 0)
            {
                //min 指向更小的值
                min = j;
            }
        }
        //如果min不等于i ，说明i比min，将i 与 min 的数据对调
        if(min != i)
        {
            temp = min->data;
            min->data = i->data;
            i->data = temp;
        }
    }
    return 0;
}


int node_update(node_t *head,const void *olddata,const void *newdata,int size,cmpfun_t cmpfun) //查找修改
{
    //安区检查
    SYSERR(newdata,==,NULL,"newdata is NULL",-1);
    //查找
    node_t *p = node_find(head,olddata,cmpfun);
    SYSERR(p,==,NULL,"not found",-1); //判断是否找到数据
    memcpy(p->data,newdata,size); //数据替换
    return 0;
}


int node_find_del(node_t *head,const void *data,cmpfun_t cmpfun) //查找删除
{   
    node_t *p = node_find(head,data,cmpfun);
    SYSERR(p,==,NULL,"no found",-1);
    //更改指向
    p->prev->next = p->next;
    p->next->prev = p->prev;
    //释放空间
    free(p->data);
    free(p);
    return 0;
}


int find_show(node_t *head,const void *data,cmpfun_t cmpfun)
{
    node_t *p = node_find(head,data,cmpfun);
    SYSERR(p,==,NULL,"no found",-1);
    show_all(p->data); //打印学生信息
    return 0;
}


int node_destory(node_t **head)  //销毁链表
{
    node_t *p = (*head)->next;
    node_t *q;
    //遍历销毁
    while(p != *head)
    {
        q = p;
        p = p->next;
        free(q->data);
        free(q);
    }
    //释放头文件
    free(*head);
    *head = NULL;
    return 0;
}


int find1_show(node_t *head,const void *data,cmpfun_t cmpfun)   //循环打印
{
    node_t *p = node_find(head,data,cmpfun);
    show_all(p->data); //打印学生信息
    while(1)
    {

        p = node_find(p,data,cmpfun);
        if(p == NULL)
        {
            break;
        }
        show_all(p->data); //打印学生信息
    }
    return 0;
}

