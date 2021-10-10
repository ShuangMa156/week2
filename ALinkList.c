#include <stdio.h>
#include <stdlib.h>
#include "cursor.h"
#define SpaceSize 100
#define FatalError(Str) fprintf(stderr,"%s\n",Str),exit(1)
 struct Node
 {
     ElementType Element;//存放结点中的元素值
     Position Next;//存放下一个元素的地址，即游标（数组下标）
 };
struct Node CursorSpace[SpaceSize];//存储结点数据的数组，即链表
void InitializeCursorSpace(void)//初始化内容空间
{
    int i;
    for(i=0;i<SpaceSize;i++)
    {
        CursorSpace[i].Next=i+1;//通过依次指定每个结点的Next域为下一个结点
    }
    CursorSpace[SpaceSize-1].Next=0;
}
Position CursorAlloc(void)//申请结点空间
{
    Position P;
    P=CursorSpace[0].Next;//初始化游标位置为链表中可以申请结点空间的位置
    CursorSpace[0].Next=CursorSpace[P].Next;//
    return P;
}
void CursorFree(Position P)//释放结点空间
{
    CursorSpace[P].Next=CursorSpace[0].Next;
    CursorSpace[0].Next=P;//让P指向可以申请结点空间的一个结点
}
List MakeEmpty(List L)
{
    if(L!=0)
        DeleteList(L);
    L=CursorAlloc();//申请一个结点空间
    if(L==0)
        FatalError("Out of Memory");
    CursorSpace[L].Next=0;//让L指向的新申请的结点空间的Next域的值为空，即让该结点成为表头
    return L;
}
int IsEmpty(const List L)//判断表是否为空
{
    return CursorSpace[L].Next==0;
}
int IsLast(Position P,const List L)//判断位置P是否是表中的最后一个结点
{
    return CursorSpace[P].Next==0;
}
Position Find(ElementType X,const List L)//寻找某一元素值为X的结点在链表中的位置
{
    Position P;
    P=CursorSpace[L].Next;//初始化P指向链表中的第一个元素
    while(P && CursorSpace[CursorSpace[P].Next].Element!=X)//如果P不是链表中的最后一个结点并且没有找到元素值X所在的位置，则继续寻找下一个结点
    {
        P=CursorSpace[P].Next;
    }
    return P;
}
void Delete(ElementType X,List L)
{
    Position P,temp;
    P=FindPrevious(X,L);//初始化P为元素值X所在结点的前驱结点的位置
    if(!IsLast(P,L))
    {
        temp=CursorSpace[P].Next;//用临时结点变量保存元素X所在结点的信息
        CursorSpace[P].Next=CursorSpace[temp].Next;//让X所在结点的前驱结点的Next域指向X的后继结点
        CursorFree(temp);//释放临时结点
    }
}
Position FindPrevious(ElementType X,const List L)
{
    Position P;
    P=L;//初始化P指向表头
    while(CursorSpace[P].Next && CursorSpace[CursorSpace[P].Next].Element!=X)
    {
        P=CursorSpace[P].Next;//沿着链表向后移动P的位置直到P指向链表中的最后一个结点（没有找到）或者找到元素值X所在的结点
    }
    return P;
}
void Insert(ElementType X,List L,Position P)
{
    Position temp;//创建一个新结点
    temp=CursorAlloc();//申请空间
    if(temp==0)
        FatalError("Out of Space");
    CursorSpace[temp].Element=X;//将要插入的元素值赋值给新结点的元素域
    CursorSpace[temp].Next=CursorSpace[P].Next;//让新结点的Next域的地址指向插入位置的后继结点
    CursorSpace[P].Next=temp;//让新插入的结点成为插入位置所在结点的后继结点
}
void DeleteList(List L)
{
    Position P,temp;
    P=CursorSpace[L].Next;//初始化P的位置为链表中第一个元素所在的位置
    CursorSpace[L].Next=0;//让头结点后面为空，不指向任何结点
    while(P!=0)
    {
        temp=CursorSpace[P].Next;//用一个临时结点temp依次指向链表中的结点
        CursorFree(P);//释放节点P
        P=temp;//让P指向下一个结点
    }
}
Position Header(const List L)//寻找头结点
{
    return L;
}
Position First(const List L)//寻找链表中第一个元素所在结点
{
    return CursorSpace[L].Next;
}
Position Advance(const Position P)//寻找某一位置的后继结点
{
    return CursorSpace[P].Next;
}
ElementType Retrieve(const Position P)//寻找某一位置节点的元素值
{
    return CursorSpace[P].Element;
}
void PrintList(const List L)//打印链表
{
    Position P=Header(L);//让P指向头结点所在的位置
    if(IsEmpty(L))//判断链表是否为空
        printf("Empty List\n");
    else
    {
        do
        {
            P=Advance(P);//让P依次后移
            printf("%d ",Retrieve(P));//输出位置P对应结点的元素值
        }while(!IsLast(P,L));//循环条件：P不是链表中的最后一个元素所在的结点
        printf("\n");
    }
}
int main()
{
    List L;
    Position P;
    int i;
    InitializeCursorSpace();
    L=MakeEmpty(0);
    P=Header(L);
    PrintList(L);
    for(i=0;i<10;i++)
    {
        Insert(i,L,P);
        PrintList(L);
        P=Advance(P);//位置P后移
    }
    for(i=0;i<10;i+=2)
    {
        Delete(i,L);
    }
    for(i=0;i<10;i++)
    {
        if((i%2==0) && (Find(i,L)!=0))
            printf("Find Fails\n");
    }
    printf("Finished deletions\n");
    PrintList(L);
    DeleteList(L);
    return 0;
}
