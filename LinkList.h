#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
typedef int ElementType;
struct Node;
typedef struct Node *PtrToNode;//定义一个指向结点的的结点类型的指针
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P,List L);
Position Find(ElementType X,List L);
void Delete(ElementType X,List L);
Position FindPrevious(ElementType X,List L);
void Insert(ElementType X,Position P,List L);
void DeleteList(List L);
Position Header(List L);
Position First(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);
#endif // LIST_H_INCLUDED
