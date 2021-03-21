#include "comm.h"


extern int mark;
int addstu(node_t *head)
{
    mark = 1;
    SYSERR(head,==,NULL,"head is NULL",-1);
    char flag[10] = "";
    while(flag[0] != 'n')
    {
        stu_t *stu1 = malloc(sizeof(stu_t));    //创建一个存储添加学员的空间 
        SYSERR(stu1,==,NULL,"stu1 is NULL",-1);

        system("clear");    //清屏
        //输入添加学员信息 
        printf("\t\t\t请输入学生信息！\n");
        putchar('\n');
        putchar('\n');

        printf("\t\t\t请输入姓名:");
        scanf("%s",stu1->name);
        setbuf(stdin,NULL);

        printf("\t\t\t请输入密码:");
        scanf("%s",stu1->pass);
        setbuf(stdin,NULL);

        printf("\t\t\t请输入学生年龄:");
        scanf("%d",&stu1->age);
        setbuf(stdin,NULL);

        printf("\t\t\t请输入班级号:");
        scanf("%d",&stu1->classid);
        setbuf(stdin,NULL);

        printf("\t\t\t请输入数学成绩:");
        scanf("%d",&stu1->gmath);
        setbuf(stdin,NULL);

        printf("\t\t\t请输入C语言成绩:");
        scanf("%d",&stu1->glang);
        setbuf(stdin,NULL);

        printf("\t\t\t请输入语文成绩:");
        scanf("%d",&stu1->gphil);
        setbuf(stdin,NULL);
        
        stu1->gsum = (stu1->gmath + stu1->gphil  + stu1->glang); //总分等于其他分数相加
        stu1->cid = getcid(head,cmp_cid);  //输入学号
        inser_head(head,stu1,sizeof(stu_t)); //学生信息插入链表
        setstuorder(head,cmp_gsum); //输入学生名次

        system("clear");  //请屏
        printf("\t\t\t\t新添加学生信息如下:\n");
        putchar('\n');
        printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
        find_show(head,stu1,cmp_cid); //查找到添加学生显示出来
        putchar('\n');

        //打印所有学员
        printf("\t\t\t\t所有学生信息如下:\n");
        putchar('\n');
        printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
        putchar('\n');
        node_show(head,show_all); //显示函数

        putchar('\n');
        putchar('\n');
        printf("\t\t是否继续添加学生(任意建继续 , 'n' 返回上一级):");
        scanf("%s",flag);

        bzero(stu1,sizeof(stu_t));
        free(stu1);
    }
    return 0;
}


int setstuorder(node_t *head,cmpfun_t cmpfun) //设置学生名次排序函数
{
    //先通过总分排序一波
    node_selete_sort(head,cmpfun);     //选择排序函数
    node_t *p ;
    int i = 1;
    for( p = head->next; p != head; p = p->next)
    {
       ((stu_t *)(p->data))->order = i;
       i++;
    }
    return 0;
}


int getcid(node_t *head,cmpfun_t cmpfun)    //返回一个学号
{
    node_selete_sort(head,cmpfun);     //选择排序函数找到最大的学号
    node_t *p = head->next;
    int num;
    if(p->data == NULL)         //如果链表里没有学员就返回1
    {
        return 1;
    }
    else
    {
        num = (((stu_t *)(p->data))->cid);  //返回最大学号加1
        return ++num;
    }
}


node_t *loadstu(void)
{
    FILE *fp = fopen(STUFILE,"r");      //打开文件
    node_t *head = node_init(); //链表初始化
    SYSERR(head,==,NULL,"head is NULL",NULL);

    if(fp == NULL)
    {
        return head;
    }

    stu_t *stu1 = malloc(sizeof(stu_t));    //创建一个存储添加学员的空间 
    SYSERR(stu1,==,NULL,"stu1 is NULL",NULL);
    bzero(stu1,sizeof(stu_t));

    int num = 0;
    while(num != -1)    //读取文件数据到结尾就退出
    {
        //读取文件信息
        num = fscanf(fp,"学号:%d\t姓名:%s\t密码:%s\t年龄:%d\t班级:%d\t数学:%d\tC语言:%d\t语文:%d\t总分:%d\t名次:%d\n",&stu1->cid,stu1->name,stu1->pass,&stu1->age,&stu1->classid,&stu1->gmath,&stu1->glang,&stu1->gphil,&stu1->gsum,&stu1->order);
        if(num == -1)   //判断是否读取到数据，读取失败退出循环
        {
            break;  
        }
        inser_head(head,stu1,sizeof(stu_t)); //读取到的学生信息插入链表
        bzero(stu1,sizeof(stu_t));
    }
    fclose(fp); //读取结束关闭文件
    free(stu1); //释放学员存储空间
    return head;    //读取结束返回链表
}


int savestu(node_t *head)   //链表中的数据存储到文件里
{
    FILE *fp = fopen(STUFILE,"w+");      //打开文件清空写
    SYSERR(fp,==,NULL,"open fp err",-1);    //判断文件是否打开成功
    stu_t *stu1;    //创建一个存储添加学员的空间 
    node_t *p = head->next;     //创建一个指针指向链表的下一级

    while(p != head)
    {
        stu1 = p->data;
        fprintf(fp,"学号:%d\t姓名:%s\t密码:%s\t年龄:%d\t班级:%d\t数学:%d\tC语言:%d\t语文:%d\t总分:%d\t名次:%d\n",stu1->cid,stu1->name,stu1->pass,stu1->age,stu1->classid,stu1->gmath,stu1->glang,stu1->gphil,stu1->gsum,stu1->order);
        p = p->next; 
        bzero(stu1,sizeof(stu_t));
    }
    
    fclose(fp); //读取结束关闭文件
    return 0;
}


float aver(node_t *head,int flag)  //计算平均分
{
    node_t *p = head->next;
    int num = 0,sum = 0;
    for( ; p != head; p = p->next)
    {
        if(flag == 1)
        {
            sum += ((stu_t *)(p->data))->gmath;
            num++;
        }

        else if(flag == 2)
        {
            sum += ((stu_t *)(p->data))->glang;
            num++;
        }

        else if(flag == 3)
        {
            sum += ((stu_t *)(p->data))->gphil;
            num++;
        }
    }
    return (float)sum / (float)num;
}


