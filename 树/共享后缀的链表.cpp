





#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; /* 存储结点数据 */
    PtrToNode   Next; /* 指向下一个结点的指针 */
};
typedef PtrToNode List; /* 定义单链表类型 */

void ReadInput( List L1, List L2 ); /* 裁判实现，细节不表 */
void PrintSublist( PtrToNode StartP ); /* 裁判实现，细节不表 */
PtrToNode Suffix( List L1, List L2 );


PtrToNode Suffix( List L1, List L2 ){    
if (L1 == NULL || L2 == NULL) return NULL;        
List p = L1;    
List q = L2;        
while (p != q) {        
// 如果p走到末尾，就跳到L2的头部        
p = (p == NULL) ? L2 : p->Next;        
// 如果q走到末尾，就跳到L1的头部        
q = (q == NULL) ? L1 : q->Next;    
}        
// 最终p和q要么是同一个节点（交点），要么都是NULL（不相交）    
return p;
}
int main()
{
    List L1, L2;
    PtrToNode P;

    L1 = (List)malloc(sizeof(struct Node));
    L2 = (List)malloc(sizeof(struct Node));
    L1->Next = L2->Next = NULL;
    ReadInput( L1, L2 );
    P = Suffix( L1, L2 );
    PrintSublist( P );

    return 0;
}

/* 你的代码将被嵌在这里 */
