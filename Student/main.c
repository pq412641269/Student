#include "comm.h"



int main()
{
    extern int mark;
    mark = 0;
    node_t *head = loadstu(); //读取数据存储文件
    SYSERR(head,==,NULL,"head is NULL",-1);
    menu(head);         //学生管理系统菜单

    char ch[10];
    if(mark == 1)
    {
        system("clear");
        putchar('\n');
        putchar('\n');
        printf("\t\t\t发现文件有改动,是否保存文件:(y or n)");
        setbuf(stdin,NULL);
        scanf("%1s",ch);
        
        if(ch[0] == 'y')
        {
            savestu(head);   //链表中的数据存储到文件里
        }
        else
        {
            return 0;
        }
    }
    node_destory(&head); //销毁链表
    return 0;
}
