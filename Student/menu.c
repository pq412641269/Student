#include "comm.h"

int menu(node_t *head)         //学生管理系统菜单
{
    int flag = 10;
    while(flag != 0)    //输入 0 退出循环
    {
        system("clear");    //清屏
        printf("\t\t\t欢迎使用学生管理系统！\n");
        putchar('\n');
        putchar('\n');

        printf("\t\t\t1.管理员登录\n");
        putchar('\n');
        printf("\t\t\t2.学生登录\n");
        putchar('\n');

        printf("\t\t\t0.退出系统\n");
        putchar('\n');
        printf("\t\t\t请选择:");
        scanf("%d",&flag);

        if(flag > 2 || flag < 0 ) //判断是否输入正确
        {
            printf("\t\t\t输入错误请重新输入\n");
            getchar();
            getchar();
        }
        else if(flag == 1)   //进入管理员登录
        {
            
            welcomeadmin_menu(head);  //管理员用户密码输入
        }
        else if(flag == 2)   //进入学生登录
        {
            welcomestu_menu(head);
        }
    }
    return 0;
}


int welcomeadmin_menu(node_t *head)
{
    //建立两个数组存储输入用户名密码
    char name[16] = "",passward[16] = "";

    int flag = 3;
    do
    {
        system("clear");  //请屏            
        printf("\t\t\t管理员登录\n");               //菜单
        putchar('\n');
        printf("\t\t\t请输入用户名以及密码\n");
        putchar('\n');
        printf("\t\t\t用户名:");
        scanf("%10s",name);
        printf("\t\t\t密码:");
        scanf("%10s",passward);

        if(strcmp(name,ADMINNAME) == 0 && strcmp(passward,ADMINPASS) == 0)      //判断用户名密码是否输入正确
        {
            admin_menu(head);   //进入管理员菜单
            return 0;
        }
        else
        {
            flag--;
            printf("\t\t\t用户名或者密码输入错误！您还有 %d 次输入机会！",flag);        //总共3次输入机会，打印剩余次数
            getchar();
            getchar();
        }
    }while(flag != 0);  //输入3次错误退出循环

    if(flag == 0)       //输入3次错误退出程序
    {
        exit(0);
    }
    return 0;
}


int welcomestu_menu(node_t *head)
{
    stu_t *stu1 = malloc(sizeof(stu_t));    
    SYSERR(stu1,==,NULL,"stu1 is NULL",-1);
    bzero(stu1,sizeof(stu_t));
    int flag = 3;
    node_t *p;

    do
    {
        system("clear");  //请屏            
        printf("\t\t\t学生登录\n");               //菜单
        putchar('\n');
        printf("\t\t\t请输入用户名以及密码\n");
        putchar('\n');
        printf("\t\t\t用户名:");
        scanf("%10s",stu1->name);
        printf("\t\t\t密码:");
        scanf("%10s",stu1->pass);

        if(NULL != node_find(head,stu1,cmp_name))     //判断是否有这个用户
        {
            
            p = node_find(head,stu1,cmp_name);

            if(strcmp(((stu_t *)(p->data))->pass,stu1->pass) == 0)        //判断密码是否正确
            {
                stu1 = p->data;
                stu_menu(head,stu1);     //学员菜单
                return 0;
            }
            else
            {
                flag--;
                printf("\t\t\t用户名或者密码输入错误！您还有 %d 次输入机会！",flag);        //总共3次输入机会，打印剩余次数
                getchar();
                getchar();

            }
        }
        else    //密码错误则打印
        {
            flag--;
            printf("\t\t\t用户名或者密码输入错误！您还有 %d 次输入机会！",flag);        //总共3次输入机会，打印剩余次数
            getchar();
            getchar();
        }
        bzero(stu1,sizeof(stu_t));

    }while(flag != 0);   //输入错误3次退出循环
    free(stu1);
    if(flag == 0)       //输入3次错误退出程序
    {
        exit(0);
    }
    return 0;
}


int admin_menu(node_t *head)       //管理员菜单
{
    int num = 10;

    do
    {

        stu_t *stu1 = malloc(sizeof(stu_t));    //创建一个空间存储要修改的学号   

        system("clear");  //请屏
        printf("\t\t\t欢迎您管理员！");
        putchar('\n');
        putchar('\n');

        printf("\t\t\t1.添加学生\n");   //打印菜单
        printf("\t\t\t2.删除学生\n");
        printf("\t\t\t3.修改学生信息\n");
        printf("\t\t\t4.查找学生\n");
        printf("\t\t\t5.显示全部学生\n");
        printf("\t\t\t0.返回主菜单\n");
        putchar('\n');

        printf("\t\t\t请选择:");
        scanf("%d",&num);
        if(num > 5 || num < 0)
        {
            printf("\t\t\t输入错误请重新输入");
            getchar();
            getchar();

        }
        switch(num)
        {
        case 1:

            addstu(head);
            break;

        case 2:

            del_stu_menu(head);  //删除学员菜单
            break;

        case 3:

            SYSERR(stu1,==,NULL,"stu1 is NULL",-1);
            bzero(stu1,sizeof(stu_t));
            system("clear");  //请屏
            printf("\t\t\t请输入要修改学员的学号:");
            scanf("%d",&stu1->cid);             //输入要修改的学号

            node_t *p = node_find(head,stu1,cmp_cid);

            if(p == NULL)          //判断是否找到要修改的学生
            {
                printf("\t\t\t无此学生！回车继续！");
                getchar();
                getchar();
                break;
            }

            updatestu_menu(head,stu1); //修改学员菜单
            bzero(stu1,sizeof(stu_t));
            break;

        case 4:

            findstu_menu(head);      //学生查找菜单
            break;

        case 5:

            showstu_menu(head);     //显示学员菜单
            break;

        default:
            break;
        }
        free(stu1); //释放stu1 

    }while(num != 0);
    return 0;
}


int del_stu_menu(node_t *head)  //删除学员菜单
{
    stu_t *stu1 = malloc(sizeof(stu_t));    //创建一个空间存储要删除的学号   
    SYSERR(stu1,==,NULL,"stu1 is NULL",-1);
    bzero(stu1,sizeof(stu_t));

    system("clear");  //请屏
    printf("\t\t\t请输入要删除学员的学号:");
    scanf("%d",&stu1->cid);             //输入要删除的学号
    
    extern int mark;
    char ch[6] = "";
    int num = 11;
    putchar('\n');

    int flag = find_show(head,stu1,cmp_cid); //查找要删除的学生显示出来
    if(flag == -1)          //判断是否找到要删除的学生
    {
        printf("\t\t\t无此学生！回车继续！");
        getchar();
        getchar();
        return 0;
    }

    else if(flag == 0)           //判断是否找到要删除的学生
    {
        putchar('\n');
        printf("\t\t\t是否删除此学生(y/n):");
        scanf("%s",ch);

        if(ch[0] == 'y')        //判断是否要删除
        {
            num = node_find_del(head,stu1,cmp_cid); //查找删除
            if(num == 0)
            {
                mark = 1;
                printf("\t\t\t删除成功，回车继续！");
                getchar();
                getchar();
                return 0;
            }
            if(num == -1)
            {
                printf("\t\t\t删除失败，回车继续！");
                getchar();
                getchar();
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    free(stu1);     //释放空间
    return 0;
}


int updatestu_menu(node_t *head,stu_t *stu1)
{
    extern int mark;
    node_t *p;
    int num = 10;

    do
    {
        system("clear");  //请屏
        printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
        find_show(head,stu1,cmp_cid); //查找要修改的学生显示出来
        
        putchar('\n');
        printf("\t\t\t1.修改姓名\n");
        printf("\t\t\t2.修该年龄\n");
        printf("\t\t\t3.修改班级\n");
        printf("\t\t\t4.修改密码\n");
        putchar('\n');
        printf("\t\t\t0.返回上一级\n");
        putchar('\n');
        printf("\t\t\t请选择要修改的内容:");
        scanf("%d",&num);

        if(num > 4 || num < 0)      //判断数据是否输入正确
        {
            printf("\t\t\t输入错误请重新输入");
            getchar();
            getchar();

        }

        switch(num)
        {

        case 1:

            mark = 1;
            p = node_find(head,stu1,cmp_cid);
            stu1 = p->data;
            printf("\t\t\t请输入姓名(%s):",stu1->name);
            scanf("%s",stu1->name);
            node_update(head,p->data,stu1,sizeof(stu_t),cmp_cid);   //查找修改
            break;

        case 2:

            mark = 1;
            p = node_find(head,stu1,cmp_cid);
            stu1 = p->data;
            printf("\t\t\t请输入年龄(%d):",stu1->age);
            scanf("%d",&stu1->age);
            node_update(head,p->data,stu1,sizeof(stu_t),cmp_cid);   //查找修改
            break;

        case 3:

            mark = 1;
            p = node_find(head,stu1,cmp_cid);
            stu1 = p->data;
            printf("\t\t\t请输入班级(%d):",stu1->classid);
            scanf("%d",&stu1->classid);
            node_update(head,p->data,stu1,sizeof(stu_t),cmp_cid);   //查找修改
            break;

        case 4:

            mark = 1;
            p = node_find(head,stu1,cmp_cid);
            stu1 = p->data;
            printf("\t\t\t请输入密码(%s):",stu1->pass);
            scanf("%s",stu1->pass);
            node_update(head,p->data,stu1,sizeof(stu_t),cmp_cid);   //查找修改
            break;

        default:
            break;
        }
    }while(num != 0);
    return 0;
}


int findstu_menu(node_t *head)      //学生查找菜单
{
    stu_t *stu1 = malloc(sizeof(stu_t));    //创建一个空间存储要修改的学号   
    SYSERR(stu1,==,NULL,"stu1 is NULL",-1);
    bzero(stu1,sizeof(stu_t));
    node_t *p;

    int num = 11;
    do
    {
        system("clear");  //请屏
        printf("\t\t\t查找学生信息\n");
        putchar('\n');
        printf("\t\t\t1.根据学号查找\n");
        printf("\t\t\t2.根据姓名查找\n");
        printf("\t\t\t3.根据班级查找\n");
        putchar('\n');
        printf("\t\t\t0.返回上一级\n");
        putchar('\n');
        putchar('\n');
        printf("\t\t\t选择查找方式:");
        setbuf(stdin,NULL);
        scanf("%d",&num);

        if(num > 3 || num < 0)      //输入错误判断
        {
            printf("\t\t\t输入错误请重新输入");
            getchar();
            getchar();
            
        }

        switch(num)
        {
        case 1:
            
            printf("\t\t\t请输入学生学号:");
            setbuf(stdin,NULL);
            scanf("%d",&stu1->cid);

            p = node_find(head,stu1,cmp_cid); //判断是否有此学生
            if(p == NULL)          //判断是否找到要显示的学生
            {
                printf("\t\t\t无此学生！回车继续！");
                getchar();
                getchar();
                break;
            }
        
            system("clear");  //请屏
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
            find_show(head,stu1,cmp_cid);   //查找显示

            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        case 2:
            printf("\t\t\t请输入学生姓名:");
            setbuf(stdin,NULL);
            scanf("%s",stu1->name);

            p = node_find(head,stu1,cmp_name); //判断是否有此学生
            if(p == NULL)          //判断是否找到要显示的学生
            {
                printf("\t\t\t无此学生！回车继续！");
                getchar();
                getchar();
                break;
            }

            system("clear");  //请屏
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
            find1_show(head,stu1,cmp_name);   //查找显示
            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        case 3:
            printf("\t\t\t请输入学生班级:");
            setbuf(stdin,NULL);
            scanf("%d",&stu1->classid);
            p = node_find(head,stu1,cmp_classid); //判断是否有此学生

            if(p == NULL)          //判断是否找到要修改的学生
            {
                printf("\t\t\t无此班级！回车继续！");
                getchar();
                getchar();
                break;
            }

        
            system("clear");  //请屏
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
            find1_show(head,stu1,cmp_classid);   //查找显示

            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        default:
            break;
        }
    }while(num != 0);
    free(stu1);
    return 0;

}


int showstu_menu(node_t *head)      //显示学员菜单
{
    int num = 11;
    float aver1 = 0;
    do
    {
        system("clear");  //请屏
        printf("\t\t\t显示所有学生列表\n");
        putchar('\n');

        printf("\t\t\t1.按学号显示\n");
        printf("\t\t\t2.按名次显示\n");
        printf("\t\t\t3.按数学成绩显示\n");
        printf("\t\t\t4.按C语言成绩显示\n");
        printf("\t\t\t5.按语文成绩显示\n");

        putchar('\n');
        printf("\t\t\t0.返回上一级\n");
        putchar('\n');
        printf("\t\t\t请选择:");
        setbuf(stdin,NULL);
        scanf("%d",&num);

        if(num > 5 || num < 0)      //输入错误判断
        {
            printf("\t\t\t输入错误请重新输入!");
            getchar();
            getchar();
        }

        switch(num)
        {
        case 1:

            system("clear");  //请屏
            node_selete_sort(head,cmp_cid1);     //选择排序函数
            printf("\t\t\t按学号排序显示\n");
            putchar('\n');
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");

            node_show(head,show_all); //显示函数
            putchar('\n');
            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        case 2:
            system("clear");  //请屏
            node_selete_sort(head,cmp_order);     //选择排序函数
            printf("\t\t\t按名次排序显示\n");
            putchar('\n');
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");

            node_show(head,show_all); //显示函数
            putchar('\n');
            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        case 3:
            system("clear");  //请屏
            node_selete_sort(head,cmp_gmath);     //选择排序函数
            printf("\t\t\t按数学成绩排序显示\n");
            putchar('\n');
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");

            node_show(head,show_all); //显示函数
            putchar('\n');
            aver1 = aver(head,1);  //计算平均分
            printf("\t\t\t数学成绩平均分 = %f\n",aver1);
            putchar('\n');

            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        case 4:
            system("clear");  //请屏
            node_selete_sort(head,cmp_glang);     //选择排序函数
            printf("\t\t\t按C语言排序显示\n");
            putchar('\n');
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");

            node_show(head,show_all); //显示函数
            putchar('\n');
            aver1 = aver(head,2);  //计算平均分
            printf("\t\t\tC语言成绩平均分 = %f\n",aver1);
            putchar('\n');

            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;

        case 5:
            system("clear");  //请屏
            node_selete_sort(head,cmp_gphil);     //选择排序函数
            printf("\t\t\t按语文成绩排序显示\n");
            putchar('\n');
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");

            node_show(head,show_all); //显示函数
            putchar('\n');
            aver1 = aver(head,3);  //计算平均分
            printf("\t\t\t语文成绩平均分 = %f\n",aver1);
            putchar('\n');

            printf("\t\t\t回车继续！");
            getchar();
            getchar();
            break;
        default:
            break;
        }

    }while(num != 0);
    return 0;
}


int stu_menu(node_t *head,stu_t *stu1)     //学员菜单
{
    int num = 11;
    do
    {
        system("clear");  //请屏
        printf("\t\t\t欢迎 %s 同学!",stu1->name);
        putchar('\n');
        putchar('\n');
        putchar('\n');

        printf("\t\t\t1.查看信息\n");
        printf("\t\t\t2.修改信息\n");
        putchar('\n');
        printf("\t\t\t0.返回主界面\n");
        putchar('\n');
        printf("\t\t\t请选择:");
        
        setbuf(stdin,NULL);
        scanf("%d",&num);
        putchar('\n');

        if(num > 2 || num < 0)      //输入错误判断
        {
            printf("\t\t\t输入错误请重新输入!");
            getchar();
            getchar();
        }

        if(num == 1)
        {
            system("clear");  //请屏
            printf("\t\t\t %s 同学信息如下\n",stu1->name);
            putchar('\n');
            printf("\t\t学号   姓名      年龄    班级    数学    C语言   语文    总分    名次\n");
            find_show(head,stu1,cmp_cid);
            putchar('\n');
            printf("\t\t\t回车返回上一级");
            getchar();
            getchar();
        }

        if(num == 2)
        {
            updatestu_menu(head,stu1);
        }

    }while(num != 0);
    return 0;
}


