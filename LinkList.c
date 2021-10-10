#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#define FatalError(Str) fprintf(stderr,"%s\n",Str),exit(1)
struct Node
{
    ElementType Element;
    Position Next;
};
List MakeEmpty(List L)//将表置空
{
    if(L!=NULL)
        DeleteList(L);//删除链表
    L=(List)malloc(sizeof(struct Node));//申请一个节点大小的空间
    if(L==NULL)
        FatalError("out of memory");//如果空间申请失败，则返回错误信息
    L->Next=NULL;//将链表置空，即将链表的头结点的指针域Next置空
    return L;
}
int IsEmpty(List L)
{
    return L->Next==NULL;//通过头结点指针域是否为空来判断链表是否为空
}
int IsLast(Position P,List L)
{
    return P->Next==NULL;//通过判断位置P对应结点的指针域是否为空来判断该结点是不是链表中的最后一个元素
}
Position Find(ElementType X,List L)
{
    Position P;//定义位置变量
    P=L->Next;//初始化P指向链表中的第一个元素所在的结点
    while(P->Next!=NULL && P->Element!=X)//如果P不是链表中的最后一个元素并且P指向的结点的元素值不是所查找的值时,P沿着链表继续向下寻找
    {
        P=P->Next;
    }
    return P;
}
void Delete(ElementType X,List L)
{
    Position P,Tempcell;
    P=FindPrevious(X,L);//找到元素X的前驱结点
    if(!IsLast(P,L))//如果结点P不是链表的最后一个结点
    {
        Tempcell=P->Next;//保存当前P指向的结点的Next域的值，即元素X所在结点
        P->Next=Tempcell->Next;//修改P的Next域的值为元素X所在结点的Next域的值，即让所删除元素所在结点的前驱元素的Next指向该结点的后继元素
        free(Tempcell);//释放存储该元素的结点的存储空间
    }
}
Position FindPrevious(ElementType X,List L)
{
    Position P;
    P=L;//初始化P指向链表的头结点
    while(P->Next!=NULL && P->Next->Element!=X)//如果P不是链表中的最后一个元素且P不是元素值X对应的结点的前驱结点
    {
        P=P->Next;//沿着链表向后移动P的位置
    }
    return P;
}
void Insert(ElementType X,Position P,List L)
{
    Position Tempcell;//定义一个变量
    Tempcell=(Position)malloc(sizeof(struct Node));//让变量Temocell指向申请的新的一个结点空间
    if(Tempcell==NULL)
    {
        FatalError("Out of space");//空间申请失败弹出异常
    }
    Tempcell->Element=X;//将要插入的元素值赋值给新建结点的元素域
    Tempcell->Next=P->Next;//让插入的位置P对应的结点的后继成为新结点的后继
    P->Next=Tempcell;//让插入的位置P对应的结点成为新结点的前驱
}
void DeleteList(List L)
{
    Position P,temp;
    P=L->Next;//初始化P指向链表中的第一个元素
    while(P!=NULL)//如果链表不为空
    {
        temp=P->Next;//通过临时结点依次将P指向的结点释放后将其后移
        free(P);
        P=temp;
    }
}
Position Header(List L)
{
    return L;//返回头结点
}
Position First(List L)
{
    return L->Next;//返回链表中的第一个元素所在位置
}
Position Advance(Position P)
{
    return P->Next;//返回某一位置P的后继位置
}
ElementType Retrieve(Position P)
{
   return P->Element;//返回某一位置P所在结点的元素值
}
void PrintList(const List L)
{
    Position P=Header(L);
    if(IsEmpty(L))
        printf("Empty List");
    else
    {
        do
        {
            P=Advance(P);
            printf("%d ",Retrieve(P));
        }while(!IsLast(P,L));
        printf("\n");
    }
}
int main()
{
    List L;
    L=MakeEmpty(NULL);
    Position P;
    P=Header(L);
    PrintList(L);
    for(int i=0;i<10;i++)
    {
        Insert(i,P,L);
        PrintList(L);
        P=Advance(P);
    }
    for(int i=0;i<10;i+=2)
    {
        Delete(i,L);
        printf("Delete %d  ",i);
    }
    for(int i=0;i<10;i++)
    {
        if((i%2==0)&&(Find(i,L)!=NULL))
           printf("find fails\n");
    }
    printf("Finish\n");
    PrintList(L);
    DeleteList(L);
    return 0;
}
